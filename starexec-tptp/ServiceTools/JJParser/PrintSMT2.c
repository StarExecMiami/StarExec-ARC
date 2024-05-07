#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Tokenizer.h"
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Examine.h"
#include "ListStatistics.h"
#include "Modify.h"
#include "PrintTSTP.h"
#include "PrintSMT2.h"
#include <search.h>

//-------------------------------------------------------------------------------------------------

void SMT2EscapedString(FILE * Stream, const char *s) {
  const char *p;
    //p store where where are in the initial s
    //s store what part of s have not been printed yet
    //ref store the translation of special characters
    for(p=s;*p!='\0';p++) {
        switch (*p) {
        case '~':
        case '!':
        case '@':
        case '$':
        case '%':
        case '^':
        case '&':
        case '*':
        case '_':
        case '-':
        case '+':
        case '=':
        case '<':
        case '>':
        case '.':
        case '?':
        case '/':
          continue;
        default:
          if ( (*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') ||
               (*p >= '0' && *p <= '9') ) continue;
          //print the part of s that not have been printed yet
          // and print the strange character after.
          fprintf(Stream,"%.*s_c%i",(int)(p-s),s,(int)*p);
          s=p+1;
          break;
        }
    }
    //print the last part of s
    fputs(s,Stream);
}
//-------------------------------------------------------------------------------------------------

void SMT2SanitizeSymbol(FILE * Stream, char * StartOfSymbol, int Arity,
                        int Isvariable){
  //----Skip past the $ if not in full TSTP mode, e.g., oldtptp ??what does that mean?
        if (*StartOfSymbol == '$') {
          StartOfSymbol++;//Not robust but every printer do that
        }
        if (*StartOfSymbol == '-') {
          fprintf(Stream,"n");
          StartOfSymbol++;
        }
        if (isdigit(*StartOfSymbol)) {
          fprintf(Stream,"n");
        }
        if(Isvariable){
          fprintf(Stream,"?%s",StartOfSymbol);
        }else if (*StartOfSymbol == '\'' || *StartOfSymbol == '\"'){
          SMT2EscapedString(Stream,StartOfSymbol);
          fprintf(Stream,"__smt2_%i",Arity);
        } else if (!strcmp(StartOfSymbol,"true") || !strcmp(StartOfSymbol,"false")) {
          fprintf(Stream,"%s",StartOfSymbol);
        } else {
          fprintf(Stream,"%s__smt2_%i",StartOfSymbol,Arity);
        };

}

void SMT2PrintTerm(FILE * Stream,TERM Term) {

    int Arity;
    char * StartOfSymbol;
    int Index;

//----Propositions are un()ed
    if ((Arity = GetArity(Term)) > 0) {
        fprintf(Stream,"(");
    }

//----Print principal symbol
    if (!strcmp(GetSymbol(Term),"=")) {
        fprintf(Stream,"=");
    } else {
        StartOfSymbol = GetSymbol(Term);
        SMT2SanitizeSymbol(Stream,StartOfSymbol,GetArity(Term),
                           Term->Type == variable);
    }
//----Print arguments
    for (Index=0;Index < Arity;Index++) {
        fprintf(Stream," ");
        SMT2PrintTerm(Stream,Term->Arguments[Index]);
    }

    if ((Arity = GetArity(Term)) > 0) {
        fprintf(Stream,")");
    }
}
//-------------------------------------------------------------------------------------------------
char * SMT2ConnectiveToString(ConnectiveType Connective) {

    switch (Connective) {
        case disjunction:
            return("or");
            break;
        case conjunction:
            return("and");
            break;
        case nonequivalence:
            return("xor");
            break;
        case equivalence:
            return("=");
            break;
        case implication:
            return("=>");
            break;
        case negation:
            return("not");
            break;
        case universal:
            return("forall");
            break;
        case existential:
            return("exists");
            break;
        default:
            CodingError("Not a SMT2 connective");
            return(NULL);
            break;
    }
}
//----
static const char* uniq_sort = "sort__smt2";
const char * SMT2TypeToString( TERM Variable ){
  return uniq_sort;
}
//-------------------------------------------------------------------------------------------------
int SMT2Associative(ConnectiveType Connective) {
    return(Connective == disjunction || Connective == conjunction);
}
//-------------------------------------------------------------------------------------------------
void SMT2PrintFormula(FILE * Stream,FORMULA Formula,int Indent,int AlreadyIndented,int Pretty) {
    switch (Formula->Type) {
        case quantified:
            PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
            fprintf(Stream,"(%s (",SMT2ConnectiveToString(Formula->FormulaUnion.QuantifiedFormula.Quantifier));
            fprintf(Stream,"(?%s %s)",GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable),
            							SMT2TypeToString(Formula->FormulaUnion.QuantifiedFormula.Variable));
//----Here's where types will be printed, in a future TSTP
//----List variables for same quantifiers
            while (Pretty && Formula->FormulaUnion.QuantifiedFormula.Formula->Type == quantified &&
					Formula->FormulaUnion.QuantifiedFormula.Quantifier ==
					Formula->FormulaUnion.QuantifiedFormula.Formula->FormulaUnion.QuantifiedFormula.Quantifier) {
                Formula = Formula->FormulaUnion.QuantifiedFormula.Formula;
                fprintf(Stream," (?%s %s)", GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable),
                							SMT2TypeToString(Formula->FormulaUnion.QuantifiedFormula.Variable));
            }
            fprintf(Stream,") ");
//----If unary or atom, do on same line
            if ((Formula->FormulaUnion.QuantifiedFormula.Formula->Type ==unary) ||
            	(Formula->FormulaUnion.QuantifiedFormula.Formula->Type == atom)) {
                SMT2PrintFormula(Stream,Formula->FormulaUnion.QuantifiedFormula.Formula,Indent,Indent,Pretty);
            } else {
//----Otherwise on the next line
                fprintf(Stream,"%s",(Pretty?"\n":""));
//----If another quantified, no extra indent
                if (Formula->FormulaUnion.QuantifiedFormula.Formula->Type !=quantified) {
                    Indent += 4;
                }
                SMT2PrintFormula(Stream,Formula->FormulaUnion.QuantifiedFormula.Formula,Indent,0,Pretty);
            }
            fprintf(Stream,")");
            break;

        case binary:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            if( Formula->FormulaUnion.BinaryFormula.Connective==reverseimplication ){
				fprintf(Stream,"(=> ");
            	SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.RHS,Indent+4,Indent+4,Pretty);
            	fprintf(Stream,"\n");
            	SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,Indent+4,0,Pretty);
            } else if( Formula->FormulaUnion.BinaryFormula.Connective==negatedconjunction ){
              fprintf(Stream,"( not (and ");
            	SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,Indent+4,Indent+4,Pretty);
            	fprintf(Stream,"\n");
            	SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.RHS,Indent+4,0,Pretty);
                fprintf(Stream,")");
            } else if( Formula->FormulaUnion.BinaryFormula.Connective==negateddisjunction ){
              fprintf(Stream,"( not (or ");
            	SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,Indent+4,Indent+4,Pretty);
            	fprintf(Stream,"\n");
            	SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.RHS,Indent+4,0,Pretty);
                fprintf(Stream,")");
			}else{
				fprintf(Stream,"(%s ",SMT2ConnectiveToString(Formula->FormulaUnion.BinaryFormula.Connective));
				SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,Indent+4,Indent+4,Pretty);
				fprintf(Stream,"\n");
				while (SMT2Associative(Formula->FormulaUnion.BinaryFormula.Connective) &&
						Formula->FormulaUnion.BinaryFormula.RHS->Type == binary &&
						Formula->FormulaUnion.BinaryFormula.Connective == Formula->
						FormulaUnion.BinaryFormula.RHS->FormulaUnion.BinaryFormula.Connective) {
					Formula = Formula->FormulaUnion.BinaryFormula.RHS;
					SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,Indent+4,0,Pretty);
					fprintf(Stream,"\n");
				}
				SMT2PrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.RHS,Indent+4,0,Pretty);
			}
            fprintf(Stream,")");
            break;

        case unary:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            fprintf(Stream,"(%s ",SMT2ConnectiveToString(Formula->FormulaUnion.UnaryFormula.Connective));
            SMT2PrintFormula(Stream,Formula->FormulaUnion.UnaryFormula.Formula,Indent+4,Indent+4,Pretty);
            fprintf(Stream,")");
            break;

        case atom:
            PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
            SMT2PrintTerm(Stream,Formula->FormulaUnion.Atom);
            break;

        default:
            CodingError("Formula type unknown for printing SMT2");
            break;
    }

}

void SMT2PrintComment(FILE* Stream,const char * s){
    const char *p;
    //p store where where are in the initial s
    //s store what part of s have not been printed yet
    //ref store the translation of special characters
    for(p=s;*p!='\0';p++) {
      switch (*p) {
        case '\n':
          //print the part of s that not have been printed yet
          // and print the strange character after.
          fprintf(Stream,";%.*s\n",(int)(p-s),s);
          s=p+1;
          break;
        default:
          continue;
        }
    }
    //print the last part of s
    fprintf(Stream,";%s\n",s);
}


void SMT2PrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula){
    String Name;
    TERM SubStatus;

    switch (AnnotatedFormula->Syntax) {
        case comment:
            SMT2PrintComment(Stream,AnnotatedFormula->AnnotatedFormulaUnion.Comment);
            break;
        case blank_line:
            fprintf(Stream,"\n");
            break;
        case tptp_cnf:
            FOFify(AnnotatedFormula,universal);
            fprintf(Stream,"; %s %s\n",GetName(AnnotatedFormula,Name),StatusToString(GetRole(AnnotatedFormula,&SubStatus)));
            fprintf(Stream,"(assert ");
            SMT2PrintFormula(Stream,AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,0,0,1);
            fprintf(Stream," )\n");
            break;
        case tptp_fof:
            fprintf(Stream,"; %s %s\n",GetName(AnnotatedFormula,Name),StatusToString(GetRole(AnnotatedFormula,&SubStatus)));
            fprintf(Stream,"(assert ");
            SMT2PrintFormula(Stream,AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,0,0,1);
            fprintf(Stream,")\n");
            break;
        default:
            CodingError("Syntax unknown for printing SMT2");
            break;
    }
}

//-------------------------------------------------------------------------------------------------
void SMT2PrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head) {

    LISTNODE Node;
    int StartedThisPart;

    Node = Head;
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
		//DO_THIS
        Node = Node->Next;
    }
    StartedThisPart = 0;
    while (Node != NULL) {
        if ((StartedThisPart && !LogicalAnnotatedFormula(Node->AnnotatedFormula) &&
        	(Node->AnnotatedFormula->Syntax != comment ||
        	strstr(Node->AnnotatedFormula->AnnotatedFormulaUnion.Comment,"%--------------")== NULL)) ||
        	LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
            if (GetRole(Node->AnnotatedFormula,NULL) == conjecture) {
                fprintf(Stream,";----This is the conjecture with negated conjecture\n");
                Negate(Node->AnnotatedFormula,0);
            }
            SMT2PrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
            StartedThisPart = 1;
        }
        Node = Node->Next;
    }
    fprintf(Stream,"\n");
    fprintf(Stream,"(check-sat)\n");
}
//-------------------------------------------------------------------------------------------------
void SMT2PrintSignatureList(FILE * Stream,SYMBOLNODE Node,int Predicate) {

    char * StartOfSymbol;

    if (Node != NULL) {
        StartOfSymbol = GetSignatureSymbol(Node);
//----No SMT2 on interpeted terms
        if (strcmp(StartOfSymbol,"=") && 
strcmp(StartOfSymbol,"$true") && strcmp(StartOfSymbol,"$false")) {
          fprintf(Stream,"(declare-fun ");
          int arity = GetSignatureArity(Node);
          SMT2SanitizeSymbol(Stream,StartOfSymbol,arity, 0);
          fprintf(Stream," (");
          int i;
          for(i = 0; i < arity; ++i){
            fprintf(Stream," %s",uniq_sort);
          };
          fprintf(Stream," ) %s)\n", Predicate ? "Bool" : uniq_sort);
        }
        SMT2PrintSignatureList(Stream,Node->LastSymbol, Predicate);
        return SMT2PrintSignatureList(Stream,Node->NextSymbol, Predicate);
    }
    return;
}
//-------------------------------------------------------------------------------------------------
void SMT2PrintHeader(FILE * Stream,LISTNODE Head,SIGNATURE Signature) {

    LISTNODE Node;

    Node = Head;
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
        SMT2PrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
        Node = Node->Next;
    }
    fprintf(Stream,"(set-logic UF)\n");
    fprintf(Stream,"(declare-sort %s 0)\n",uniq_sort);

    fprintf(Stream,"; functions\n");
    SMT2PrintSignatureList(Stream,Signature->Functions,0);

    fprintf(Stream,"; predicates\n");
    SMT2PrintSignatureList(Stream,Signature->Predicates,1);

    fprintf(Stream,"\n");
}
//-------------------------------------------------------------------------------------------------

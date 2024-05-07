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
#include "PrintKIF.h"
//-------------------------------------------------------------------------------------------------
void KIFPrintTerm(FILE * Stream,TERM Term) {

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
//----Skip past the $ if not in full TSTP mode, e.g., oldtptp
    } else {
        StartOfSymbol = GetSymbol(Term);
        if (*StartOfSymbol == '$') {
            StartOfSymbol++;
        }
        fprintf(Stream,"%s%s",Term->Type == variable?"?":"",StartOfSymbol);
    }
//----Print arguments
    for (Index=0;Index < Arity;Index++) {
        fprintf(Stream," ");
        KIFPrintTerm(Stream,Term->Arguments[Index]);
    }

    if ((Arity = GetArity(Term)) > 0) {
        fprintf(Stream,")");
    }
}
//-------------------------------------------------------------------------------------------------
char * KIFConnectiveToString(ConnectiveType Connective) {

    switch (Connective) {
        case disjunction:
            return("or");
            break;
        case conjunction:
            return("and");
            break;
        case equivalence:
            return("<=>");
            break;
        case implication:
            return("=>");
            break;
        case reverseimplication:
            return("<=");
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
            CodingError("Not a KIF connective");
            return(NULL);
            break;
    }       
}
//-------------------------------------------------------------------------------------------------
int KIFAssociative(ConnectiveType Connective) {

    return(Connective == disjunction || Connective == conjunction);
}
//-------------------------------------------------------------------------------------------------
void KIFPrintFormula(FILE * Stream,FORMULA Formula,int Indent,
int AlreadyIndented,int Pretty) {

    switch (Formula->Type) {
        case quantified:
            PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
            fprintf(Stream,"(%s (",KIFConnectiveToString(
Formula->FormulaUnion.QuantifiedFormula.Quantifier));
            fprintf(Stream,"?%s",
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
//----Here's where types will be printed, in a future TSTP
//----List variables for same quantifiers
            while (Pretty && 
Formula->FormulaUnion.QuantifiedFormula.Formula->Type == quantified &&
Formula->FormulaUnion.QuantifiedFormula.Quantifier ==
Formula->FormulaUnion.QuantifiedFormula.Formula->FormulaUnion.QuantifiedFormula.Quantifier) {
                Formula = Formula->FormulaUnion.QuantifiedFormula.Formula;
                fprintf(Stream," ?%s",
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
            }
            fprintf(Stream,") ");
//----If unary or atom, do on same line
            if ((Formula->FormulaUnion.QuantifiedFormula.Formula->Type == 
unary) || (Formula->FormulaUnion.QuantifiedFormula.Formula->Type == atom)) {
                KIFPrintFormula(Stream,Formula->
FormulaUnion.QuantifiedFormula.Formula,Indent,Indent,Pretty);
            } else {
//----Otherwise on the next line
                fprintf(Stream,"%s",(Pretty?"\n":""));
//----If another quantified, no extra indent
                if (Formula->FormulaUnion.QuantifiedFormula.Formula->Type !=
quantified) {
                    Indent += 4;
                }
                KIFPrintFormula(Stream,Formula->
FormulaUnion.QuantifiedFormula.Formula,Indent,0,Pretty);
            }
            fprintf(Stream,")");
            break;

        case binary:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            fprintf(Stream,"(%s ",KIFConnectiveToString(
Formula->FormulaUnion.BinaryFormula.Connective));
            KIFPrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,
Indent+4,Indent+4,Pretty);
            fprintf(Stream,"\n");
            while (KIFAssociative(Formula->FormulaUnion.BinaryFormula.
Connective) && 
Formula->FormulaUnion.BinaryFormula.RHS->Type == binary &&
Formula->FormulaUnion.BinaryFormula.Connective == Formula->
FormulaUnion.BinaryFormula.RHS->FormulaUnion.BinaryFormula.Connective) {
                Formula = Formula->FormulaUnion.BinaryFormula.RHS;
                KIFPrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,
Indent+4,0,Pretty);
                fprintf(Stream,"\n");
            }
            KIFPrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.RHS,
Indent+4,0,Pretty);
            fprintf(Stream,")");
            break;

        case unary:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            fprintf(Stream,"(%s ",KIFConnectiveToString(
Formula->FormulaUnion.UnaryFormula.Connective));
            KIFPrintFormula(Stream,Formula->FormulaUnion.UnaryFormula.
Formula,Indent+4,Indent+4,Pretty);
            fprintf(Stream,")");
            break;

        case atom:
            PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
            KIFPrintTerm(Stream,Formula->FormulaUnion.Atom);
            break;

        default:
            CodingError("Formula type unknown for printing KIF");
            break;
    }

}
//-------------------------------------------------------------------------------------------------
void KIFPrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA 
AnnotatedFormula) {

    String Name;
    String Comment;

    switch (AnnotatedFormula->Syntax) {
        case comment:
            strcpy(Comment,AnnotatedFormula->AnnotatedFormulaUnion.Comment);
            Comment[0] = ';';
            fprintf(Stream,"%s\n",Comment);
            break;
        case blank_line:
            fprintf(Stream,"\n");
            break;
        case tptp_cnf:
            fprintf(Stream,"; %s, %s\n",GetName(AnnotatedFormula,Name),
StatusToString(GetRole(AnnotatedFormula,NULL)));
            fprintf(Stream,"( ");
            KIFPrintFormula(Stream,AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula,0,0,1);
            fprintf(Stream," ).\n");
            break;
        case tptp_fof:
            fprintf(Stream,"; %s, %s\n",GetName(AnnotatedFormula,Name),
StatusToString(GetRole(AnnotatedFormula,NULL)));
            KIFPrintFormula(Stream,AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula,0,0,1);
            fprintf(Stream,".\n");
            break;
        default:
            CodingError("Syntax unknown for printing KIF");
            break;
    }

}
//-------------------------------------------------------------------------------------------------
void KIFPrintHeader(FILE * Stream,LISTNODE Head,SIGNATURE Signature) {

    LISTNODE Node;

    Node = Head;
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
        KIFPrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
        Node = Node->Next;
    }

}
//-------------------------------------------------------------------------------------------------
void KIFPrintTailer(FILE * Stream) {

    fprintf(Stream,";--------------------------------------------------------------------------------------------------\n");
}
//-------------------------------------------------------------------------------------------------
void KIFPrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head) {

    LISTNODE Node;
    int StartedThisPart;

    Node = Head;
//----Skip header
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
        Node = Node->Next;
    }
    StartedThisPart = 0;
    while (Node != NULL) {
        if ((StartedThisPart && !LogicalAnnotatedFormula(
Node->AnnotatedFormula) && (Node->AnnotatedFormula->Syntax != comment ||
strstr(Node->AnnotatedFormula->AnnotatedFormulaUnion.Comment,"%--------------")
== NULL)) || LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
            if (GetRole(Node->AnnotatedFormula,NULL) == conjecture) {
                fprintf(Stream,
";----This is the conjecture with negated conjecture\n");
                Negate(Node->AnnotatedFormula,0);
            }
            KIFPrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
            StartedThisPart = 1;
        }
        Node = Node->Next;
    }
    fprintf(Stream,"\n");

}
//-------------------------------------------------------------------------------------------------

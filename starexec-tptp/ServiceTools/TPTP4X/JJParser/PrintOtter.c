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
#include "PrintOtter.h"
//-------------------------------------------------------------------------------------------------
char * OtterConnectiveToString(ConnectiveType Connective) {

    switch (Connective) {
        case disjunction:
            return("|");
            break;
        case conjunction:
            return("&");
            break;
        case equivalence:
            return("<->");
            break;
        case implication:
            return("->");
            break;
        case reverseimplication:
            return("<-");
            break;
        case negation:
            return("-");
            break;
        case universal:
            return("all");
            break;
        case existential:
            return("exists");
            break;
        default:
            CodingError("Not a Otter connective");
            return(NULL);
            break;
    }       
}
//-------------------------------------------------------------------------------------------------
int OtterAssociative(ConnectiveType Connective) {

    return(Connective == disjunction || Connective == conjunction);
}
//-------------------------------------------------------------------------------------------------
void OtterPrintFormula(FILE * Stream,SyntaxType Language,FORMULA Formula,int Indent,
int AlreadyIndented,int Pretty,ConnectiveType LastConnective,ConnectiveType NextConnective) {

    int NoIndent;
    int NoUndent;
    int ConnectiveIndent;

    switch (Formula->Type) {
        case quantified:
            PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
            fprintf(Stream,"( %s ",OtterConnectiveToString(
Formula->FormulaUnion.QuantifiedFormula.Quantifier));
            fprintf(Stream,"%s",GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
//----Here's where types will be printed, in a future TSTP
//----List variables for same quantifiers
            while (Pretty && 
Formula->FormulaUnion.QuantifiedFormula.Formula->Type == quantified &&
Formula->FormulaUnion.QuantifiedFormula.Quantifier ==
Formula->FormulaUnion.QuantifiedFormula.Formula->FormulaUnion.QuantifiedFormula.Quantifier) {
                Formula = Formula->FormulaUnion.QuantifiedFormula.Formula;
                fprintf(Stream," %s",
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
            }
            fprintf(Stream," ( ");
//----If unary or atom, do on same line
            if ((Formula->FormulaUnion.QuantifiedFormula.Formula->Type == 
unary) || (Formula->FormulaUnion.QuantifiedFormula.Formula->Type == atom)) {
                OtterPrintFormula(Stream,Language,Formula->
FormulaUnion.QuantifiedFormula.Formula,Indent,Indent,Pretty,
Formula->FormulaUnion.QuantifiedFormula.Quantifier,none);
            } else {
//----Otherwise on the next line
                fprintf(Stream,"%s",(Pretty?"\n":""));
//----If another quantified, no extra indent
                if (Formula->FormulaUnion.QuantifiedFormula.Formula->Type != quantified) {
                    Indent += 2;
                }
                OtterPrintFormula(Stream,Language,Formula->FormulaUnion.QuantifiedFormula.Formula,
Indent,0,Pretty,Formula->FormulaUnion.QuantifiedFormula.Quantifier,none);
            }
            fprintf(Stream," ) )");
            break;

        case binary:
            PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
//----No brackets for sequences of associative formulae and top level
            NoIndent = (Pretty &&
Formula->FormulaUnion.BinaryFormula.Connective == LastConnective && 
OtterAssociative(Formula->FormulaUnion.BinaryFormula.Connective))
|| LastConnective == outermost;
            NoUndent = (Pretty &&
Formula->FormulaUnion.BinaryFormula.Connective == NextConnective && 
OtterAssociative(Formula->FormulaUnion.BinaryFormula.Connective))
|| NextConnective == outermost;
            if (NoIndent || NoUndent) {
                ConnectiveIndent = Indent - 2 - strlen(OtterConnectiveToString(
Formula->FormulaUnion.BinaryFormula.Connective)) + 1;
                AlreadyIndented = Indent;
            } else {
                fprintf(Stream,"(%s",(Pretty?" ":""));
                ConnectiveIndent = Indent - strlen(OtterConnectiveToString(
Formula->FormulaUnion.BinaryFormula.Connective)) + 1;
                Indent = AlreadyIndented = Indent + 2;
            }
            OtterPrintFormula(Stream,Language,Formula->FormulaUnion.BinaryFormula.LHS,Indent,
AlreadyIndented,Pretty,none,Formula->FormulaUnion.BinaryFormula.Connective);
            fprintf(Stream,"%s",(Pretty?"\n":" "));
            PrintIndent(Stream,ConnectiveIndent,0,Pretty);
            fprintf(Stream,"%s ",OtterConnectiveToString(
Formula->FormulaUnion.BinaryFormula.Connective));
            OtterPrintFormula(Stream,Language,
Formula->FormulaUnion.BinaryFormula.RHS,Indent,AlreadyIndented,Pretty,
Formula->FormulaUnion.BinaryFormula.Connective,none);
            if (!NoIndent && !NoUndent) {
                fprintf(Stream,"%s)",(Pretty?" ":""));
            }
            break;

        case unary:
            PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
            AlreadyIndented = Indent;
            fprintf(Stream,"%s",OtterConnectiveToString(
Formula->FormulaUnion.UnaryFormula.Connective));
//----() on negated quantified formulae and negated negated
            if (Formula->FormulaUnion.UnaryFormula.Formula->Type == 
quantified || Formula->FormulaUnion.UnaryFormula.Formula->Type == unary ||
(Formula->FormulaUnion.UnaryFormula.Formula->Type == atom &&
!strcmp(GetSymbol(Formula->FormulaUnion.UnaryFormula.Formula->
FormulaUnion.Atom),"="))) {
                fprintf(Stream," ( ");
                Indent = AlreadyIndented = Indent + 4;
                NoIndent = 0;
            } else {
//----Assumes connective length one - could make it flexible
                Indent = AlreadyIndented = Indent + 2;
                NoIndent = 1;
            }
            OtterPrintFormula(Stream,Language,
Formula->FormulaUnion.UnaryFormula.Formula,Indent,AlreadyIndented,Pretty,
Formula->FormulaUnion.UnaryFormula.Connective,none);
            if (!NoIndent) {
                fprintf(Stream," )");
            }
            break;

        case atom:
            PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
//----Hack for $false and $true
            if (!strcmp(GetSymbol(Formula->FormulaUnion.Atom),"$true")) {
                fprintf(Stream,"$T");
            } else if (!strcmp(GetSymbol(Formula->FormulaUnion.Atom),"$false")) {
                fprintf(Stream,"$F");
            } else {
                PrintTSTPTerm(Stream,Language,Formula->FormulaUnion.Atom,-1,1,0);
            }
            break;

        default:
            CodingError("Formula type unknown for printing Otter");
            break;
    }

}
//-------------------------------------------------------------------------------------------------
void OtterPrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA 
AnnotatedFormula) {

    String Name;

    switch (AnnotatedFormula->Syntax) {
        case comment:
            fprintf(Stream,"%s\n",AnnotatedFormula->AnnotatedFormulaUnion.Comment);
            break;
        case blank_line:
            fprintf(Stream,"\n");
            break;
        case tptp_cnf:
            fprintf(Stream,"%% %s, %s\n",GetName(AnnotatedFormula,Name),
StatusToString(GetRole(AnnotatedFormula,NULL)));
            fprintf(Stream,"( ");
            OtterPrintFormula(Stream,tptp_cnf,AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
0,0,1,outermost,outermost);
            fprintf(Stream," ).\n");
            break;
        case tptp_fof:
            fprintf(Stream,"%% %s, %s\n",GetName(AnnotatedFormula,Name),
StatusToString(GetRole(AnnotatedFormula,NULL)));
            OtterPrintFormula(Stream,tptp_fof,AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
0,0,1,outermost,outermost);
            fprintf(Stream,".\n");
            break;
        default:
            CodingError("Syntax unknown for printing Otter");
            break;
    }

}
//-------------------------------------------------------------------------------------------------
void OtterPrintHeader(FILE * Stream,LISTNODE Head,SIGNATURE Signature) {

    LISTNODE Node;

    Node = Head;
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
        OtterPrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
        Node = Node->Next;
    }

    fprintf(Stream,"set(prolog_style_variables).\n");
//----Aaargh, if I don't use tptp_eq then = and equalish are equality.
//----If I use tptp_eq then = is not equality. Do this and use equal/2
//    fprintf(Stream,"set(tptp_eq).\n");
    fprintf(Stream,"set(auto).\n");
    fprintf(Stream,"clear(print_given).\n");
    fprintf(Stream,"\n");
}
//-------------------------------------------------------------------------------------------------
void OtterPrintTailer(FILE * Stream) {

    fprintf(Stream,"%%--------------------------------------------------------------------------------------------------\n");
}
//-------------------------------------------------------------------------------------------------
void OtterPrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head) {

    LISTNODE Node;
    int StartedThisPart;

    Node = Head;
//----Skip header
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
        Node = Node->Next;
    }
    StartedThisPart = 0;
    if (GetListSyntax(Head) == tptp_cnf) {
        fprintf(Stream,"list(usable).\n\n");
    } else {
        fprintf(Stream,"formula_list(usable).\n\n");
    }
    while (Node != NULL) {
        if ((StartedThisPart && !LogicalAnnotatedFormula(
Node->AnnotatedFormula) && (Node->AnnotatedFormula->Syntax != comment ||
strstr(Node->AnnotatedFormula->AnnotatedFormulaUnion.Comment,"%--------------")
== NULL)) || LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
            if (GetRole(Node->AnnotatedFormula,NULL) == conjecture) {
                fprintf(Stream,
"%%----This is the conjecture with negated conjecture\n");
                Negate(Node->AnnotatedFormula,0);
            }
            OtterPrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
            StartedThisPart = 1;
        }
        Node = Node->Next;
    }
    fprintf(Stream,"end_of_list.\n");
    fprintf(Stream,"\n");

}
//-------------------------------------------------------------------------------------------------

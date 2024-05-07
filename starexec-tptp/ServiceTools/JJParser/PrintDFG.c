#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Signature.h"
#include "Examine.h"
#include "Modify.h"
#include "PrintTSTP.h"
#include "PrintDFG.h"
//-------------------------------------------------------------------------------------------------
int DFGPrintSignatureList(FILE * Stream,SYMBOLNODE Node,int JustPrinted) {

    String LocalSymbol;
    char * StartOfSymbol;
    int NumberPrinted;
    int QuotedSymbol;

    if (Node != NULL) {
        NumberPrinted = DFGPrintSignatureList(Stream,Node->LastSymbol,JustPrinted);
        if (NumberPrinted > 0) {
            JustPrinted = 1;
        }
        strcpy(LocalSymbol,GetSignatureSymbol(Node));
        StartOfSymbol = LocalSymbol;
        if (*StartOfSymbol == '$') {
            StartOfSymbol++;
        }
//----No DFG on interpeted terms
        if (strcmp(StartOfSymbol,"=") && 
strcmp(StartOfSymbol,"true") && strcmp(StartOfSymbol,"false")) {
            if (JustPrinted) {
                fprintf(Stream,",");
            } 
            fprintf(Stream,"(");
            if (*StartOfSymbol == '-') {
                fprintf(Stream,"n");
                StartOfSymbol++;
            }
            if (isdigit(*StartOfSymbol)) {
                fprintf(Stream,"n");
            }
            if (*StartOfSymbol == '\'') {
                QuotedSymbol = 1;
                StartOfSymbol[strlen(StartOfSymbol)-1] = '\0';
            } else {
                QuotedSymbol = 0;
            }
            fprintf(Stream,"%s%s%s,%d)",StartOfSymbol,"__dfg",
QuotedSymbol?"'":"",GetSignatureArity(Node));
            NumberPrinted++;
            JustPrinted = 1;
        } 
        NumberPrinted += DFGPrintSignatureList(Stream,Node->NextSymbol,
JustPrinted);
    } else {
        NumberPrinted = 0;
    }
    return(NumberPrinted);
}
//-------------------------------------------------------------------------------------------------
void PrintFileDFGTerm(PRINTFILE Stream,TERM Term) {

    int Index;
    int Arity;
    char OpeningBracket,ClosingBracket;
    String LocalSymbol;
    char * StartOfSymbol;
    int QuotedSymbol;

//----Check if infix - or : 
    if (!strcmp(GetSymbol(Term),"-") || !strcmp(GetSymbol(Term),":")) {
        PrintFileDFGTerm(Stream,Term->Arguments[0]);
        PFprintf(Stream,"%s",GetSymbol(Term));
        PrintFileDFGTerm(Stream,Term->Arguments[1]);
    } else {
//----Check if a list
        if (GetSymbol(Term)[0] == '[') {
            OpeningBracket = '[';
            ClosingBracket = ']';
        } else {
//----Skip past the $ if not in full TSTP mode
            strcpy(LocalSymbol,GetSymbol(Term));
            StartOfSymbol = LocalSymbol;
            if (*StartOfSymbol == '$') {
                StartOfSymbol++;
            }
            if (*StartOfSymbol == '-') {
                PFprintf(Stream,"n");
                StartOfSymbol++;
            }
            if (isdigit(*StartOfSymbol)) {
                PFprintf(Stream,"n");
            }
            if (*StartOfSymbol == '\'') {
                QuotedSymbol = 1;
                StartOfSymbol[strlen(StartOfSymbol)-1] = '\0';
            } else {
                QuotedSymbol = 0;
            }
//----Convert = to equal
            if (!strcmp(StartOfSymbol,"=")) {
                PFprintf(Stream,"%s","equal");
            } else {
                PFprintf(Stream,"%s",StartOfSymbol);
            }
            if (Term->Type != variable && strcmp(StartOfSymbol,"=") && 
strcmp(StartOfSymbol,"true") && strcmp(StartOfSymbol,"false")) {
                PFprintf(Stream,"%s","__dfg");
            }
            PFprintf(Stream,"%s",QuotedSymbol?"'":"");
            OpeningBracket = '(';
            ClosingBracket = ')';
        }

        if ((Arity = GetArity(Term)) > 0 || OpeningBracket == '[') {
            PFprintf(Stream,"%c",OpeningBracket);
            if (Arity > 0) {
                PrintFileDFGTerm(Stream,Term->Arguments[0]);
                for (Index=1;Index < Arity;Index++) {
                    PFprintf(Stream,",");
                    PrintFileDFGTerm(Stream,Term->Arguments[Index]);
                }
            }
            PFprintf(Stream,"%c",ClosingBracket);
        }
    }
}
//-------------------------------------------------------------------------------------------------
void PrintDFGTerm(FILE * Stream,TERM Term) {

    PRINTFILE LocalStream;
        
    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileDFGTerm(LocalStream,Term);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
char * DFGConnectiveToString(ConnectiveType Connective) {

    switch (Connective) {
        case disjunction:
            return("or");
            break;
        case conjunction:
            return("and");
            break;
        case equivalence:
            return("equiv");
            break;
        case implication:
            return("implies");
            break;
        case reverseimplication:
            return("implied");
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
            CodingError("Not a DFG connective");
            return(NULL);
            break;
    }       
}
//-------------------------------------------------------------------------------------------------
void DFGPrintClause(FILE * Stream,FORMULA Formula,int Indent,
int AlreadyIndented) {

    switch (Formula->Type) {
        case binary:
            if (Formula->FormulaUnion.BinaryFormula.Connective != disjunction) {
                CodingError("Not a disjunction in DFG clause printing");
            }
            DFGPrintClause(Stream,Formula->FormulaUnion.BinaryFormula.LHS,
Indent,AlreadyIndented);
            fprintf(Stream,",\n");
            DFGPrintClause(Stream,Formula->FormulaUnion.BinaryFormula.RHS,
Indent,0);
            break;

        case unary:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            fprintf(Stream,"%s(",DFGConnectiveToString(
Formula->FormulaUnion.UnaryFormula.Connective));
            PrintDFGTerm(Stream,Formula->FormulaUnion.UnaryFormula.Formula->
FormulaUnion.Atom);
            fprintf(Stream,")");
            break;

        case atom:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            PrintDFGTerm(Stream,Formula->FormulaUnion.Atom);
            break;

        default:
            CodingError("Not a clause for DFG printing");
            break;
    }

}
//-------------------------------------------------------------------------------------------------
void DFGPrintFormula(FILE * Stream,FORMULA Formula,SyntaxType Syntax,int Indent,
int AlreadyIndented,int OrPrinted) {

    switch (Formula->Type) {
        case quantified:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            fprintf(Stream,"%s",DFGConnectiveToString(
Formula->FormulaUnion.QuantifiedFormula.Quantifier));
            fprintf(Stream,"([");
            fprintf(Stream,"%s",
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
//----Here's where types will be printed, in a future TSTP
//----List variables for same quantifiers
            while (
Formula->FormulaUnion.QuantifiedFormula.Formula->Type == quantified &&
Formula->FormulaUnion.QuantifiedFormula.Quantifier ==
Formula->FormulaUnion.QuantifiedFormula.Formula->FormulaUnion.QuantifiedFormula.Quantifier) {
                Formula = Formula->FormulaUnion.QuantifiedFormula.Formula;
                fprintf(Stream,",%s",
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
            }
            fprintf(Stream,"],\n");
            DFGPrintFormula(Stream,Formula->FormulaUnion.QuantifiedFormula.
Formula,Syntax,Indent+1,0,0);
            fprintf(Stream,")");
            break;

        case binary:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            fprintf(Stream,"%s(\n",DFGConnectiveToString(
Formula->FormulaUnion.BinaryFormula.Connective));
            if (Syntax == tptp_cnf) {
                DFGPrintClause(Stream,Formula,Indent+1,0);
            } else {
                DFGPrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,
Syntax,Indent+1,0,0);
                fprintf(Stream,",\n");
                DFGPrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.RHS,
Syntax,Indent+1,0,0);
            }
            fprintf(Stream,")");
            break;

        case unary:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
//----Fucking needs an or if unit - useless syntax
            if (Syntax == tptp_cnf) {
                fprintf(Stream,"or(\n");
                Indent++;
            }
            PrintIndent(Stream,Indent,0,1);
            fprintf(Stream,"%s(\n",DFGConnectiveToString(
Formula->FormulaUnion.UnaryFormula.Connective));
            DFGPrintFormula(Stream,Formula->FormulaUnion.UnaryFormula.Formula,
Syntax,Indent+1,0,1);
            if (Syntax == tptp_cnf) {
                fprintf(Stream,")");
            }
            fprintf(Stream,")");
            break;

        case atom:
            PrintIndent(Stream,Indent,AlreadyIndented,1);
            if (Syntax == tptp_cnf && !OrPrinted) {
                fprintf(Stream,"or(\n");
                PrintIndent(Stream,Indent+1,0,1);
            }
            PrintDFGTerm(Stream,Formula->FormulaUnion.Atom);
            if (Syntax == tptp_cnf && !OrPrinted) {
                fprintf(Stream,")");
            }
            break;

        default:
            CodingError("Formula type unknown for printing DFG");
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void DFGPrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA 
AnnotatedFormula) {

    String Name;

    switch (AnnotatedFormula->Syntax) {
        case comment:
            fprintf(Stream,"%s\n",
AnnotatedFormula->AnnotatedFormulaUnion.Comment);
            break;
        case blank_line:
            fprintf(Stream,"\n");
            break;
        case tptp_fof:
            fprintf(Stream,"formula(\n");
            DFGPrintFormula(Stream,AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula,tptp_fof,2,0,0);
            fprintf(Stream,",\n%s).\n",GetName(AnnotatedFormula,Name));
            break;
        case tptp_cnf:
            FOFify(AnnotatedFormula,universal);
            fprintf(Stream,"clause(\n");
            DFGPrintFormula(Stream,AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula,tptp_cnf,2,0,0);
            fprintf(Stream,",\n%s).\n",GetName(AnnotatedFormula,Name));
            break;
        default:
            CodingError("Syntax unknown for printing DFG");
            break;
    }

}
//-------------------------------------------------------------------------------------------------
void DFGPrintHeader(FILE * Stream,LISTNODE Head,SIGNATURE Signature) {

    LISTNODE Node;

    Node = Head;
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
        DFGPrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
        Node = Node->Next;
    }

    fprintf(Stream,"begin_problem(SomeProblem).\n");
    fprintf(Stream,"list_of_descriptions.\n");
    fprintf(Stream,"name({* BLAH *}).\n");
    fprintf(Stream,"author({* BLAH *}).\n");
    fprintf(Stream,"status(unknown).\n");
    fprintf(Stream,"description({* BLAH *}).\n");
    fprintf(Stream,"end_of_list.\n");
    fprintf(Stream,"list_of_symbols.\n");
    fprintf(Stream,"functions[");
    if (DFGPrintSignatureList(Stream,Signature->Functions,0) == 0) {
        fprintf(Stream,"(dummy_functor_never_used,0)");
    }
    fprintf(Stream,"].\n");
    fprintf(Stream,"predicates[");
    if (DFGPrintSignatureList(Stream,Signature->Predicates,0) == 0) {
        fprintf(Stream,"(dummy_predicate_never_used,0)");
    }
    fprintf(Stream,"].\n");
    fprintf(Stream,"end_of_list.\n");
    fprintf(Stream,"\n");
}
//-------------------------------------------------------------------------------------------------
void DFGPrintTailer(FILE * Stream) {

    fprintf(Stream,"end_problem.\n");
    fprintf(Stream,"%%--------------------------------------------------------------------------------------------------\n");
}
//-------------------------------------------------------------------------------------------------
void DFGPrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head) {

    LISTNODE Node;
    int StartedThisPart;
    SyntaxType Syntax;

    Syntax = GetListSyntax(Head);
//----Skip header
    Node = Head;
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
        Node = Node->Next;
    }
    StartedThisPart = 0;
    if (Syntax == tptp_cnf) {
        fprintf(Stream,"list_of_clauses(axioms,cnf).\n\n");
    } else {
        fprintf(Stream,"list_of_formulae(axioms).\n\n");
    }

    while (Node != NULL) {
        if ((StartedThisPart && !LogicalAnnotatedFormula(
Node->AnnotatedFormula) && (Node->AnnotatedFormula->Syntax != comment ||
strstr(Node->AnnotatedFormula->AnnotatedFormulaUnion.Comment,"%--------------")
== NULL)) ||
(LogicalAnnotatedFormula(Node->AnnotatedFormula) && 
GetRole(Node->AnnotatedFormula,NULL) != conjecture &&
GetRole(Node->AnnotatedFormula,NULL) != negated_conjecture)) {
            DFGPrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
            StartedThisPart = 1;
        }
        Node = Node->Next;
    }
    fprintf(Stream,"end_of_list.\n");
    fprintf(Stream,"\n");

    Node = Head;
    while (Node != NULL && !LogicalAnnotatedFormula(Node->AnnotatedFormula)) {
        Node = Node->Next;
    }
    StartedThisPart = 0;
    if (Syntax == tptp_cnf) {
        fprintf(Stream,"list_of_clauses(conjectures,cnf).\n\n");
    } else {
        fprintf(Stream,"list_of_formulae(conjectures).\n\n");
    }
    while (Node != NULL) {
        if ((StartedThisPart && !LogicalAnnotatedFormula(
Node->AnnotatedFormula) && (Node->AnnotatedFormula->Syntax != comment ||
strstr(Node->AnnotatedFormula->AnnotatedFormulaUnion.Comment,"%--------------")
== NULL)) ||
(LogicalAnnotatedFormula(Node->AnnotatedFormula) && 
(GetRole(Node->AnnotatedFormula,NULL) == conjecture ||
GetRole(Node->AnnotatedFormula,NULL) == negated_conjecture))) {
            if (!StartedThisPart && 
GetRole(Node->AnnotatedFormula,NULL) == conjecture) {
                fprintf(Stream,
"%%----This is the conjecture with negated conjecture\n");
            }
            DFGPrintAnnotatedTSTPNode(Stream,Node->AnnotatedFormula);
            StartedThisPart = 1;
        }
        Node = Node->Next;
    }
    fprintf(Stream,"end_of_list.\n");
    fprintf(Stream,"\n");
}
//-------------------------------------------------------------------------------------------------

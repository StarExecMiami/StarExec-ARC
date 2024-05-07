#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Tokenizer.h"
#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Signature.h"
#include "Examine.h"
#include "Modify.h"
#include "PrintTSTP.h"
#include "PrintLP.h"
//-------------------------------------------------------------------------------------------------
void LPPrintFormula(FILE * Stream,FORMULA Formula);
//-------------------------------------------------------------------------------------------------
char * TPTPtoLPSymbol(char * TPTPSymbol) {

    if (!strcmp(TPTPSymbol,"$i")) {
        return("κ");
    } else if (!strcmp(TPTPSymbol,"$o")) {
        return("Prop");
    } else if (!strcmp(TPTPSymbol,"$false")) {
        return("⊥");
    } else if (!strcmp(TPTPSymbol,"$true")) {
        return("⊤");
    } else if (!strcmp(TPTPSymbol,"$tType")) {
        return("TYPE");
    } else {
        return(TPTPSymbol);
    }
}
//-------------------------------------------------------------------------------------------------
char * LPConnectiveToString(ConnectiveType Connective) {

    String ErrorMessage;

    switch (Connective) {
        case disjunction:
            return("∨");
            break;
        case conjunction:
            return("∧");
            break;
        case equivalence:
            return("⇔");
            break;
        case implication:
            return("⇒");
            break;
        case reverseimplication:
            return("<=");
            break;
        case negation:
            return("¬");
            break;
        case universal:
            return("∀");
            break;
        case existential:
            return("∃");
            break;
        case equation:
            return("=");
            break;
        default:
            sprintf(ErrorMessage,"Connective %s unknown for printing LP",
ConnectiveToString(Connective));
            CodingError(ErrorMessage);
            return(NULL);
            break;
    }       
}
//-------------------------------------------------------------------------------------------------
void PrintLPArgumentSignature(FILE * Stream,FORMULA TypeSignature) {

    if (TypeSignature->Type == binary) {
        PrintLPArgumentSignature(Stream,TypeSignature->FormulaUnion.BinaryFormula.LHS);
        PrintLPArgumentSignature(Stream,TypeSignature->FormulaUnion.BinaryFormula.RHS);
    } else {
        fprintf(Stream,"%s → ",TPTPtoLPSymbol(GetSymbol(TypeSignature->FormulaUnion.Atom)));
    }
}
//-------------------------------------------------------------------------------------------------
int LPPrintSignatureList(FILE * Stream,SYMBOLNODE Node,LISTNODE Head,char * ResultType) {

    int NumberPrinted;
    int Index;
    String Symbol;
    FORMULA SearchingTypeFormula,MatchingTypeFormula;
    LISTNODE Searcher;

    if (Node != NULL) {
        NumberPrinted = LPPrintSignatureList(Stream,Node->LastSymbol,Head,ResultType);
        strcpy(Symbol,GetSignatureSymbol(Node));
//----Suppress interpreted symbols
        if (Symbol[0] != '$' && strcmp(Symbol,"=") && strcmp(Symbol,"!=")) {
            MatchingTypeFormula = NULL;
            Searcher = Head;
            while (Searcher != NULL && MatchingTypeFormula == NULL) {
                if (GetListNodeStatus(Searcher) == type) {
                    SearchingTypeFormula = GetListNodeFormula(Searcher);
                    if (
SearchingTypeFormula->Type == type_declaration &&
SearchingTypeFormula->FormulaUnion.BinaryFormula.Connective == typecolon &&
SearchingTypeFormula->FormulaUnion.BinaryFormula.LHS->Type == atom &&
!strcmp(Symbol,GetSymbol(SearchingTypeFormula->FormulaUnion.BinaryFormula.LHS->
FormulaUnion.Atom))) {
                        MatchingTypeFormula = SearchingTypeFormula;
                    }
                }
                Searcher = Searcher->Next;
            }
            fprintf(Stream,"constant symbol %s : ",Symbol);
//----Find the symbol's declaration
            if (MatchingTypeFormula != NULL) {
                MatchingTypeFormula = MatchingTypeFormula->FormulaUnion.BinaryFormula.RHS;
                if (MatchingTypeFormula->Type == binary) {
                    ResultType = GetSymbol(MatchingTypeFormula->FormulaUnion.BinaryFormula.RHS->
FormulaUnion.Atom);
                    MatchingTypeFormula = MatchingTypeFormula->FormulaUnion.BinaryFormula.LHS;
                    PrintLPArgumentSignature(Stream,MatchingTypeFormula);
                } else {
                    ResultType = GetSymbol(MatchingTypeFormula->FormulaUnion.Atom);
                }
            } else {
                for (Index = 0;Index < GetSignatureArity(Node);Index++) {
                    fprintf(Stream,"κ → ");
                }
            }
            fprintf(Stream,"%s ;\n",TPTPtoLPSymbol(ResultType));
            NumberPrinted++;
        }
        NumberPrinted += LPPrintSignatureList(Stream,Node->NextSymbol,Head,ResultType);
    } else {
        NumberPrinted = 0;
    }
    return(NumberPrinted);
}
//-------------------------------------------------------------------------------------------------
void LPPrintTerm(FILE * Stream,TERM Term) {

    int Index;
    String Symbol;
    String ErrorMessage;

    switch (Term->Type) {
        case formula:
            LPPrintFormula(Stream,Term->TheSymbol.Formula);
            break;
        case a_type:
        case atom_as_term:
        case function:
        case variable:
            strcpy(Symbol,GetSymbol(Term));
            if (!strcmp(Symbol,"=")) {
                fprintf(Stream,"(");
                LPPrintTerm(Stream,Term->Arguments[0]);
                fprintf(Stream," = ");
                LPPrintTerm(Stream,Term->Arguments[1]);
                fprintf(Stream,")");
            } else {
                if (GetArity(Term) > 0) {
                    fprintf(Stream,"(");
                }
                fprintf(Stream,"%s",TPTPtoLPSymbol(GetSymbol(Term)));
                for (Index=0;Index < GetArity(Term);Index++) {
                    fprintf(Stream," ");
                    LPPrintTerm(Stream,Term->Arguments[Index]);
                }
                if (GetArity(Term) > 0) {
                    fprintf(Stream,")");
                }
            }
            break;
        default:
            sprintf(ErrorMessage,"Term type %s unknown for printing LP",
TermTypeToString(Term->Type));
            CodingError(ErrorMessage);
            break;
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void LPPrintFormula(FILE * Stream,FORMULA Formula) {

    String ErrorMessage;

    fprintf(Stream,"(");
    switch (Formula->Type) {
        case quantified:
            fprintf(Stream,"%s (λ %s",
LPConnectiveToString(Formula->FormulaUnion.QuantifiedFormula.Quantifier),
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
            if (Formula->FormulaUnion.QuantifiedFormula.VariableType != NULL) {
                fprintf(Stream,":");
                LPPrintFormula(Stream,Formula->FormulaUnion.QuantifiedFormula.VariableType);
            }
            fprintf(Stream,", ");
            LPPrintFormula(Stream,Formula->FormulaUnion.QuantifiedFormula.Formula);
            fprintf(Stream,")");
            break;
        case binary:
            LPPrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS);
            fprintf(Stream," %s ",
LPConnectiveToString(Formula->FormulaUnion.BinaryFormula.Connective));
            LPPrintFormula(Stream,Formula->FormulaUnion.BinaryFormula.RHS);
            break;
        case unary:
            fprintf(Stream,"%s ",
LPConnectiveToString(Formula->FormulaUnion.UnaryFormula.Connective));
            LPPrintFormula(Stream,Formula->FormulaUnion.UnaryFormula.Formula);
            break;
        case atom:
            LPPrintTerm(Stream,Formula->FormulaUnion.Atom);
            break;
        case type_declaration:
            break;
        default:
            sprintf(ErrorMessage,"Formula type %s unknown for printing LP",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            break;
    }
    fprintf(Stream,")");
}
//-------------------------------------------------------------------------------------------------
void LPPrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula) {

    String ErrorMessage;

    switch (AnnotatedFormula->Syntax) {
        case comment:
            fprintf(Stream,"//----%s\n",AnnotatedFormula->AnnotatedFormulaUnion.Comment);
            break;
        case blank_line:
            fprintf(Stream,"\n");
            break;
        case tptp_tff:
            if (GetRole(AnnotatedFormula,NULL) == type) {
                break;
            }
        case tptp_fof:
            fprintf(Stream,"symbol %s : ϵ ",GetName(AnnotatedFormula,NULL));
            LPPrintFormula(Stream,AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula);
            fprintf(Stream," ;\n");
            break;
        case tptp_cnf:
            FOFify(AnnotatedFormula,universal);
            LPPrintAnnotatedTSTPNode(Stream,AnnotatedFormula);
            break;
        default:
            sprintf(ErrorMessage,"Syntax type %s unknown for printing LP",
SyntaxToString(AnnotatedFormula->Syntax));
            CodingError(ErrorMessage);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void LPPrintHeader(FILE * Stream,LISTNODE Head,SIGNATURE Signature) {

}
//-------------------------------------------------------------------------------------------------
void LPPrintTailer(FILE * Stream) {

}
//-------------------------------------------------------------------------------------------------
void LPPrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head) {

    while (Head != NULL) {
        LPPrintAnnotatedTSTPNode(Stream,Head->AnnotatedFormula);
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------

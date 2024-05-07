#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "Tokenizer.h"
#include "Examine.h"
#include "Modify.h"
#include "PrintTSTP.h"
#include "PrintDFG.h"
#include "PrintLP.h"
#include "PrintOtter.h"
#include "PrintKIF.h"
#include "PrintXML.h"
#include "PrintSMT2.h"
#include "PrintSUMO.h"
//-------------------------------------------------------------------------------------------------
static int PrintShortSymbols = 0;
//-------------------------------------------------------------------------------------------------
void SetPrintShortSymbols(int Choice) {

    PrintShortSymbols = Choice;
}
//-------------------------------------------------------------------------------------------------
char * GetPrintSymbol(TERM Term) {

    if (Term == NULL) {
        CodingError("Getting print symbol for NULL term");
    }

    if (Term->Type == variable) {
        if (PrintShortSymbols) {
            return(GetSignatureShortSymbol(Term->TheSymbol.Variable->VariableName));
        } else {
            return(GetSignatureSymbol(Term->TheSymbol.Variable->VariableName));
        }
    } else {
        if (PrintShortSymbols) {
            return(GetSignatureShortSymbol(Term->TheSymbol.NonVariable));
        } else {
            return(GetSignatureSymbol(Term->TheSymbol.NonVariable));
        }
    }
}
//-------------------------------------------------------------------------------------------------
PrintFormatType StringToPrintFormat(char * FormatString) {

    String ErrorMessage;

    if (!strcmp(FormatString,"tptp")) {
        return(tptp);
    }
    if (!strcmp(FormatString,"tptp:long")) {
        return(tptp);
    }
    if (!strcmp(FormatString,"tptp:raw")) {
        return(tptp);
    }
    if (!strcmp(FormatString,"tptp:short")) {
        return(tptp_short);
    }
    if (!strcmp(FormatString,"oldtptp")) {
        return(oldtptp);
    }
//----Foreign formats
    if (!strcmp(FormatString,"dfg")) {
        return(dfg);
    }
    if (!strcmp(FormatString,"lambdapi")) {
        return(lambdapi);
    }
    if (!strcmp(FormatString,"otter")) {
        return(otter);
    }
    if (!strcmp(FormatString,"kif")) {
        return(kif);
    }
    if (!strcmp(FormatString,"xml")) {
        return(xml);
    }
    if (!strcmp(FormatString,"xml_short")) {
        return(xml_short);
    }
    if (!strcmp(FormatString,"sumo")) {
        return(sumo);
    }
    if (!strcmp(FormatString,"smt2")) {
        return(smt2);
    }
    sprintf(ErrorMessage,"%s is not a known print format",FormatString);
    CodingError(ErrorMessage);
//----Will never get here because CodingError exits
    return(nonprinttype);
}
//-------------------------------------------------------------------------------------------------
char * PrintFormatToString(PrintFormatType Format) {

     switch (Format) {
        case tptp:
            return("tptp");
            break;
        case tptp_short:
            return("tptp:short");
            break;
        case oldtptp:
            return("oldtptp");
            break;
//----Foreign formats
        case dfg:
            return("dfg");
            break;
        case lambdapi:
            return("lambdapi");
            break;
        case otter:
            return("otter");
            break;
        case kif:
            return("kif");
            break;
        case xml:
            return("xml");
            break;
        case xml_short:
            return("xml_short");
            break;
        case sumo:
            return("sumo");
            break;
        default:
            CodingError("Not a print format");
//----Will never get here because CodingError exits
            return(NULL);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileIndent(PRINTFILE Stream,int Indent,int AlreadyIndented,int Pretty) {

    int Index;

    if (Pretty) {
        for (Index = AlreadyIndented+1;Index <= Indent;Index++) {
            PFprintf(Stream," ");
        }
    }
}
//-------------------------------------------------------------------------------------------------
void PrintIndent(FILE * Stream,int Indent,int AlreadyIndented,int Pretty) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileIndent(LocalStream,Indent,AlreadyIndented,Pretty);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintSpaces(PRINTFILE Stream,int Spaces) {

    int Index;
    for (Index=0;Index < Spaces;Index++) {
        PFprintf(Stream," ");
    }
}
//-------------------------------------------------------------------------------------------------
//----Local mutual recursion
int FlatFormula(FORMULA Formula);
int AtomicallyFlatFormula(FORMULA Formula);
int AtomFlatFormula(FORMULA Formula);
int FlatTerm(TERM Term);
int AtomicallyFlatTerm(TERM Term);
int Equation(FORMULA Formula,FORMULA * LHS,FORMULA * RHS);
//-------------------------------------------------------------------------------------------------
int TypeConnective(ConnectiveType Connective) {

    return(Connective == typecolon || Connective == subtype);
}
//-------------------------------------------------------------------------------------------------
int DefnConnective(ConnectiveType Connective) {

    return(Connective == assignmentsym);
}
//-------------------------------------------------------------------------------------------------
int IdConnective(ConnectiveType Connective) {

    return(Connective == identicalsym);
}
//-------------------------------------------------------------------------------------------------
int TypeDefnIdConnective(ConnectiveType Connective) {

    return(TypeConnective(Connective) || DefnConnective(Connective) || IdConnective(Connective));
}
//-------------------------------------------------------------------------------------------------
int FlatBinaryConnective(ConnectiveType Connective) {

    return(Connective == application || Connective == maparrow ||
Connective == xprodtype || Connective == uniontype);
}
//-------------------------------------------------------------------------------------------------
int FlatTermList(int NumberOfElements,TERMArray Elements) {

    int ElementNumber;

    if (NumberOfElements > 0 && Elements != NULL) {
        for (ElementNumber = 0; ElementNumber < NumberOfElements; ElementNumber++) {
            if (!FlatTerm(Elements[ElementNumber])) {
                return(0);
            }
        }
    }
    return(1);
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatTermList(int NumberOfElements,TERMArray Elements) {

    int ElementNumber;

    if (NumberOfElements > 0 && Elements != NULL) {
        for (ElementNumber = 0; ElementNumber < NumberOfElements; ElementNumber++) {
            if (!AtomicallyFlatTerm(Elements[ElementNumber])) {
                return(0);
            }
        }
    }
    return(1);
}
//-------------------------------------------------------------------------------------------------
int FlatTerm(TERM Term) {

    switch (Term->Type) {
        case connective:
            break;
        case atom_as_term:
        case function:
            return(FlatTermList(GetArity(Term),Term->Arguments));
            break;
        case a_type:
        case variable:
            return(1);
            break;
        case formula:
            return(FlatFormula(Term->TheSymbol.Formula));
            break;
        default:
            return(0);
            break;
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatTerm(TERM Term) {

    switch (Term->Type) {
        case connective:
            break;
        case atom_as_term:
        case function:
            return(AtomicallyFlatTermList(GetArity(Term),Term->Arguments));
            break;
        case a_type:
        case variable:
            return(1);
            break;
        case formula:
            return(AtomicallyFlatFormula(Term->TheSymbol.Formula));
            break;
        default:
            return(0);
            break;
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int VariableFormula(FORMULA Formula) {

    return(Formula->Type == atom && Formula->FormulaUnion.Atom->Type == variable);
}
//-------------------------------------------------------------------------------------------------
int SymbolFormula(FORMULA Formula) {

//----Atoms and FOL predicates are "symbols". Thus $ite() and $let() are in 
//----this category. Note tuples have arity -1 and are not "symbols".
    return(Formula->Type == atom || Formula->Type == ite_formula || Formula->Type == let_formula);
}
//-------------------------------------------------------------------------------------------------
int FlatSymbolFormula(FORMULA Formula) {

    return(Formula->Type == atom && FlatTermList(GetArity(Formula->FormulaUnion.Atom),
Formula->FormulaUnion.Atom->Arguments));
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatSymbolFormula(FORMULA Formula) {

    return(
(Formula->Type == atom && AtomicallyFlatTermList(
 GetArity(Formula->FormulaUnion.Atom),Formula->FormulaUnion.Atom->Arguments)) ||
Formula->Type == applied_connective);
}
// ->Type == formula &&
// !FlatITEFormula(Term->Arguments[ElementNumber]->TheSymbol.Formula) &&
// !FlatSymbolOrUnaryFormula(Term->Arguments[ElementNumber]->TheSymbol.Formula) &&
// !FlatTuple(Term->Arguments[ElementNumber]->TheSymbol.Formula) &&
// !FlatEquation(Term->Arguments[ElementNumber]->TheSymbol.Formula)) {
//-------------------------------------------------------------------------------------------------
int FlatITEFormula(FORMULA Formula) {

    return(Formula->Type == ite_formula &&
FlatFormula(Formula->FormulaUnion.ConditionalFormula.Condition) &&
FlatFormula(Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue) &&
FlatFormula(Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse));
}
//-------------------------------------------------------------------------------------------------
int UnaryFormula(FORMULA Formula) {

    return(Formula->Type == unary);
}
//-------------------------------------------------------------------------------------------------
int UnarySymbolFormula(FORMULA Formula) {

    return(UnaryFormula(Formula) && SymbolFormula(Formula->FormulaUnion.UnaryFormula.Formula));
}
//-------------------------------------------------------------------------------------------------
int FlatUnarySymbolFormula(FORMULA Formula) {

    return(UnaryFormula(Formula) && FlatSymbolFormula(Formula->FormulaUnion.UnaryFormula.Formula));
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatUnarySymbolFormula(FORMULA Formula) {

    return(UnaryFormula(Formula) && AtomicallyFlatSymbolFormula(
Formula->FormulaUnion.UnaryFormula.Formula));
}
//-------------------------------------------------------------------------------------------------
int LiteralFormula(FORMULA Formula) {

    return(SymbolFormula(Formula) ||
(UnarySymbolFormula(Formula) && Formula->FormulaUnion.UnaryFormula.Connective == negation));
}
//-------------------------------------------------------------------------------------------------
int LiteralOrTuple(FORMULA Formula) {

    return(LiteralFormula(Formula) || Formula->Type == tuple);
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatLiteralFormula(FORMULA Formula) {

    return(AtomicallyFlatSymbolFormula(Formula) ||
(AtomicallyFlatUnarySymbolFormula(Formula) && 
 Formula->FormulaUnion.UnaryFormula.Connective == negation));

}
//-------------------------------------------------------------------------------------------------
int FlatSymbolOrUnaryFormula(FORMULA Formula) {

    return(VariableFormula(Formula) || FlatSymbolFormula(Formula) || 
FlatUnarySymbolFormula(Formula));
}
//-------------------------------------------------------------------------------------------------
int UnitaryFormula(FORMULA Formula) {

    return(SymbolFormula(Formula) || Formula->Type == quantified);
}
//-------------------------------------------------------------------------------------------------
int PreUnitFormula(FORMULA Formula) {

    return(Formula->Type == unary || UnitaryFormula(Formula));
}
//-------------------------------------------------------------------------------------------------
int PositiveEquality(TERM Atom) {

    return(!strcmp(GetSymbol(Atom),"=") && GetArity(Atom) == 2);
}
//-------------------------------------------------------------------------------------------------
int NegatedEquality(FORMULA Formula) {

    return(UnaryFormula(Formula) && Formula->FormulaUnion.UnaryFormula.Connective == negation &&
Formula->FormulaUnion.UnaryFormula.Formula->Type == atom &&
PositiveEquality(Formula->FormulaUnion.UnaryFormula.Formula->FormulaUnion.Atom));
}
//-------------------------------------------------------------------------------------------------
int NegatedEquation(FORMULA Formula,FORMULA * LHS,FORMULA * RHS) {

    if (UnaryFormula(Formula) &&
Formula->FormulaUnion.UnaryFormula.Connective == negation && 
Equation(Formula->FormulaUnion.UnaryFormula.Formula,LHS,RHS)) {
        return(1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int Equation(FORMULA Formula,FORMULA * LHS,FORMULA * RHS) {

    if (Formula->Type == binary && Formula->FormulaUnion.BinaryFormula.Connective == equation) {
        if (LHS != NULL) {
            *LHS = Formula->FormulaUnion.BinaryFormula.LHS;
        }
        if (RHS != NULL) {
            *RHS = Formula->FormulaUnion.BinaryFormula.RHS;
        }
        return(1);
    } else {
        return(NegatedEquation(Formula,LHS,RHS));
    }
}
//-------------------------------------------------------------------------------------------------
int PreUnitEquation(FORMULA Formula) {
    
    FORMULA LHS;
    FORMULA RHS;

    return(Equation(Formula,&LHS,&RHS) && LiteralOrTuple(LHS) && LiteralOrTuple(RHS));
}
//-------------------------------------------------------------------------------------------------
int FlatEquation(FORMULA Formula) {
    
    FORMULA LHS;
    FORMULA RHS;

    return(Equation(Formula,&LHS,&RHS) && FlatSymbolFormula(LHS) && FlatSymbolFormula(RHS));
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatEquation(FORMULA Formula) {
    
    FORMULA LHS;
    FORMULA RHS;

    return(Equation(Formula,&LHS,&RHS) && AtomicallyFlatSymbolFormula(LHS) && 
AtomicallyFlatSymbolFormula(RHS));
}
//-------------------------------------------------------------------------------------------------
int TypeFormula(FORMULA Formula) {

    return(Formula->Type == type_declaration && 
TypeConnective(Formula->FormulaUnion.BinaryFormula.Connective));
}
//-------------------------------------------------------------------------------------------------
int DefnFormula(FORMULA Formula) {

    return(Formula->Type == assignment && 
DefnConnective(Formula->FormulaUnion.BinaryFormula.Connective));
}
//-------------------------------------------------------------------------------------------------
int IdFormula(FORMULA Formula) {

    return(Formula->Type == assignment && 
IdConnective(Formula->FormulaUnion.BinaryFormula.Connective));
}
//-------------------------------------------------------------------------------------------------
int TypeDefnIdFormula(FORMULA Formula) {

    return(TypeFormula(Formula) || DefnFormula(Formula) || IdFormula(Formula));
}
//-------------------------------------------------------------------------------------------------
int PolymorphicTypeFormula(FORMULA Formula) {

    return(Formula->Type == quantified && 
(Formula->FormulaUnion.QuantifiedFormula.Quantifier == pibinder ||
 Formula->FormulaUnion.QuantifiedFormula.Quantifier == sigmabinder));
}
//-------------------------------------------------------------------------------------------------
int FlatTypeDefnIdFormula(FORMULA Formula) {

    return(TypeDefnIdFormula(Formula) && FlatFormula(Formula->FormulaUnion.BinaryFormula.LHS) &&
FlatFormula(Formula->FormulaUnion.BinaryFormula.RHS));
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatTypeDefnIdFormula(FORMULA Formula) {

    return(TypeDefnIdFormula(Formula) && 
AtomicallyFlatFormula(Formula->FormulaUnion.BinaryFormula.LHS) &&
AtomicallyFlatFormula(Formula->FormulaUnion.BinaryFormula.RHS));
}
//-------------------------------------------------------------------------------------------------
int ApplicationFormula(FORMULA Formula) {

    return(Formula->Type == binary && 
Formula->FormulaUnion.BinaryFormula.Connective == application);
}
//-------------------------------------------------------------------------------------------------
int FlatFormulaList(int NumberOfElements,FORMULAArray Elements) {

    int ElementNumber;

    for (ElementNumber = 0; ElementNumber < NumberOfElements; ElementNumber++) {
        if (!FlatFormula(Elements[ElementNumber])) {
            return(0);
        }
    }
    return(1);
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatFormulaList(int NumberOfElements,FORMULAArray Elements) {

    int ElementNumber;

    for (ElementNumber = 0; ElementNumber < NumberOfElements; ElementNumber++) {
        if (!AtomicallyFlatFormula(Elements[ElementNumber])) {
            return(0);
        }
    }
    return(1);
}
//-------------------------------------------------------------------------------------------------
int AtomFlatFormulaList(int NumberOfElements,FORMULAArray Elements) {

    int ElementNumber;

    for (ElementNumber = 0; ElementNumber < NumberOfElements; ElementNumber++) {
        if (!AtomFlatFormula(Elements[ElementNumber])) {
            return(0);
        }
    }
    return(1);
}
//-------------------------------------------------------------------------------------------------
int FlatTuple(FORMULA Formula) {

    return(Formula->Type == tuple && FlatFormulaList(
Formula->FormulaUnion.TupleFormula.NumberOfElements,Formula->FormulaUnion.TupleFormula.Elements));
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatTuple(FORMULA Formula) {

    return(Formula->Type == tuple && AtomFlatFormulaList(
Formula->FormulaUnion.TupleFormula.NumberOfElements,Formula->FormulaUnion.TupleFormula.Elements));
}
//-------------------------------------------------------------------------------------------------
int BinaryFormula(FORMULA Formula) {

    return(Formula->Type == binary);
}
//-------------------------------------------------------------------------------------------------
int FlatBinaryFormula(FORMULA Formula) {

    return(BinaryFormula(Formula) &&
FlatBinaryConnective(Formula->FormulaUnion.BinaryFormula.Connective) &&
FlatFormula(Formula->FormulaUnion.BinaryFormula.LHS) &&
FlatFormula(Formula->FormulaUnion.BinaryFormula.RHS));
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatBinaryFormula(FORMULA Formula) {

    return(BinaryFormula(Formula) &&
FlatBinaryConnective(Formula->FormulaUnion.BinaryFormula.Connective) &&
AtomicallyFlatFormula(Formula->FormulaUnion.BinaryFormula.LHS) &&
AtomicallyFlatFormula(Formula->FormulaUnion.BinaryFormula.RHS));
}
//-------------------------------------------------------------------------------------------------
int FlatQuantifiedVariable(QuantifiedFormulaType QuantifiedFormula) {

    if (QuantifiedFormula.VariableType == NULL) {
        return(1);
    } else {
        return(FlatFormula(QuantifiedFormula.VariableType));
    }
}
//-------------------------------------------------------------------------------------------------
int QuantifiedFormula(FORMULA Formula) {

    return(Formula->Type == quantified);
}
//-------------------------------------------------------------------------------------------------
int FlatFormula(FORMULA Formula) {

    return(AtomicallyFlatFormula(Formula) || FlatBinaryFormula(Formula) || 
FlatTypeDefnIdFormula(Formula) || FlatTuple(Formula));
}
//-------------------------------------------------------------------------------------------------
int AtomicallyFlatFormula(FORMULA Formula) {

//----Was just FlatEquation(Formula) ... maybe that was better
    return(AtomicallyFlatLiteralFormula(Formula) || AtomicallyFlatEquation(Formula) || 
AtomicallyFlatTypeDefnIdFormula(Formula) || AtomicallyFlatTuple(Formula));
}
//-------------------------------------------------------------------------------------------------
int AtomFlatFormula(FORMULA Formula) {

    return(AtomicallyFlatLiteralFormula(Formula));
}
//-------------------------------------------------------------------------------------------------
int OutermostWithoutBrackets(FORMULA Formula) {

    return(QuantifiedFormula(Formula) || 
(UnaryFormula(Formula) && !NegatedEquation(Formula,NULL,NULL)) || TypeDefnIdFormula(Formula) ||
LiteralFormula(Formula) || FlatFormula(Formula));
}
//-------------------------------------------------------------------------------------------------
void PrintFileTSTPTerm(PRINTFILE Stream,SyntaxType Language,TERM Term,int Pretty,int Indent,
ConnectiveType LastConnective,int TSTPSyntaxFlag) {

    char OpeningBracket,ClosingBracket;
    char * StartOfSymbol;

//DEBUG printf("Printing term of type %s last connective %s indent %d\n",TermTypeToString(Term->Type),ConnectiveToString(LastConnective),Indent);
//----All THF and TFF (because of TFX) terms are formulae
    if ((Language == tptp_thf || Language == tptp_tff || Language == tptp_tcf) && 
Term->Type == formula) {
        PrintFileTSTPFormula(Stream,Language,Term->TheSymbol.Formula,Indent,Pretty,
LastConnective,1);
//----Check if a nested formula - no symbol
    } else if (Term->Type == nested_thf || Term->Type == nested_tff || 
Term->Type == nested_tcf || Term->Type == nested_fof || Term->Type == nested_cnf) {
        PFprintf(Stream,"$%s( ",SyntaxToString(NestedTermTypeToSyntax(Term->Type)));
//----Have to turn off pretty printing for nested formulae (so things come
//----out on one line), which means sequences of quantifiers are not listed
//----together. I'll live with it.
        PrintFileTSTPFormula(Stream,NestedTermTypeToSyntax(Term->Type),
Term->TheSymbol.NestedFormula->Formula,0,0,outermost,1);
        PFprintf(Stream," )");
    } else if (Term->Type == nested_fot) {
        PFprintf(Stream,"$fot(");
        PrintFileTSTPTerm(Stream,Language,Term->TheSymbol.NestedTerm->Term,Pretty,Indent,
outermost,TSTPSyntaxFlag);
        PFprintf(Stream,")");
//----Check if infix - or : (see also TSTPTermToString in Examine.c)
    } else if (!strcmp(GetSymbol(Term),"-") || !strcmp(GetSymbol(Term),":")) {
        PrintFileTSTPTerm(Stream,Language,Term->Arguments[0],Pretty,Indent,LastConnective,
TSTPSyntaxFlag);
        PFprintf(Stream,"%s",GetPrintSymbol(Term));
        PrintFileTSTPTerm(Stream,Language,Term->Arguments[1],Pretty,Indent,LastConnective,
TSTPSyntaxFlag);
//----If infix equality or inequality
    } else if (TSTPSyntaxFlag && !strcmp(GetSymbol(Term),"=") && GetArity(Term) == 2) {
        PrintFileTSTPTerm(Stream,Language,Term->Arguments[0],Pretty,Indent,LastConnective,1);
        PFprintf(Stream," ");
        if (TSTPSyntaxFlag == 2) {
            PFprintf(Stream,"!");
        }
        PFprintf(Stream,"= ");
        PrintFileTSTPTerm(Stream,Language,Term->Arguments[1],Pretty,Indent,LastConnective,1);
    } else {
//----Check if a list. Avoid [.] NTF short connectives
        if (GetSymbol(Term)[0] == '[' && GetSymbol(Term)[1] != '.') {
            OpeningBracket = '[';
            ClosingBracket = ']';
        } else if (GetSymbol(Term)[0] == '(') {
            OpeningBracket = '(';
            ClosingBracket = ')';
//----Weird case for () functor, no indent before the opening (
            Indent--;
        } else {
//----Otherwise assume an atom
            StartOfSymbol = GetPrintSymbol(Term);
//DEBUG printf("Print atomic, symbol %s arity %d\n",StartOfSymbol,GetArity(Term));
//----Skip past the $ if not in full TSTP mode, e.g., oldtptp
            if (!TSTPSyntaxFlag && *StartOfSymbol == '$') {
                StartOfSymbol++;
            }
//----If not TSTPSyntaxFlag or doesn't look like equality, then print = as equal
//----Not any more, because = is a term in THF
//             if ((!TSTPSyntaxFlag || GetArity(Term) != 2)  && 
// !strcmp(StartOfSymbol,"=")) {
//                 StartOfSymbol = "equal";
//             }
//----Strip leading + off positive numbers (cannot be a + in any other context)
            if (*StartOfSymbol == '+') {
                StartOfSymbol++;
            }
//----And now actually print what's left
            PFprintf(Stream,"%s",StartOfSymbol);
            OpeningBracket = '(';
            ClosingBracket = ')';
        }
        PrintFileTermList(Stream,Language,Term,Pretty,Indent,OpeningBracket,ClosingBracket,
OpeningBracket == '(' ? brackets : outermost,TSTPSyntaxFlag);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintStringTSTPTerm(char * PutOutputHere,SyntaxType Language,TERM Term,int Pretty,
int Indent,int TSTPSyntaxFlag) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenStringPrintFile(PutOutputHere)) != NULL) {
        PrintFileTSTPTerm(LocalStream,Language,Term,Pretty,Indent,outermost,TSTPSyntaxFlag);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintTSTPTerm(FILE * Stream,SyntaxType Language,TERM Term,int Indent,int Pretty,
int TSTPSyntaxFlag) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileTSTPTerm(LocalStream,Language,Term,Pretty,Indent,outermost,TSTPSyntaxFlag);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileTermList(PRINTFILE Stream,SyntaxType Language,TERM Term,int Pretty,int Indent,
char OpeningBracket,char ClosingBracket,ConnectiveType LastConnective,int TSTPSyntaxFlag) {

    int Arity,ElementNumber;
    int NeedNewLine = 0;

//DEBUG printf("Printing term list, arity %d opening bracket %c\n",GetArity(Term),OpeningBracket);
//----Need to check the args exist, because for type declarations they don't
    if (((Arity = GetArity(Term)) > 0  && Term->Arguments != NULL) || OpeningBracket == '[') {
        PFprintf(Stream,"%c",OpeningBracket);
        for (ElementNumber=0;ElementNumber < Arity;ElementNumber++) {
//DEBUG printf("Printing element %d, type %s, last connective %s\n",ElementNumber,FormulaTypeToString(Term->Arguments[ElementNumber]->Type),ConnectiveToString(LastConnective));
            if (ElementNumber > 0) {
                PFprintf(Stream,",");
            }
//----Only some formula arguments stay on the same line
            if (Pretty && 
LastConnective != brackets &&
//----Always a new line for $let and $ite
// ||
//  (Term->Arguments[ElementNumber]->Type == formula &&
//   (Term->Arguments[ElementNumber]->TheSymbol.Formula->Type == ite_formula ||
//    Term->Arguments[ElementNumber]->TheSymbol.Formula->Type == let_formula))) &&
!AtomicallyFlatTerm(Term->Arguments[ElementNumber]) &&
Term->Arguments[ElementNumber]->Type != non_logical_data && 
!NestedFormulaType(Term->Arguments[ElementNumber]->Type,1)) {
                PFprintf(Stream,"\n");
                PrintSpaces(Stream,Indent);
                NeedNewLine = 1;
            } else {
//----If we did if part last time, that means another newline please
                if (NeedNewLine) {
                    PFprintf(Stream,"\n");
                    PrintSpaces(Stream,Indent);
                }
                NeedNewLine = 0;
            }
            if (Term->Arguments[ElementNumber]->Type == formula &&
OutermostWithoutBrackets(Term->Arguments[ElementNumber]->TheSymbol.Formula)) {
                LastConnective = outermost;
            } else {
                LastConnective = none;
            }
            PrintFileTSTPTerm(Stream,Language,Term->Arguments[ElementNumber],Pretty,Indent,
LastConnective,TSTPSyntaxFlag);
        }
        PFprintf(Stream,"%c",ClosingBracket);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileFormulaeTuple(PRINTFILE Stream,SyntaxType Language,int NumberOfElements,
FORMULAArray FormulaTuple,int Pretty,int Indent,int TSTPSyntaxFlag) {

    int ElementNumber;
    int NeedSpace;
    ConnectiveType LastConnective;

    PFprintf(Stream,"[");
    if ((NeedSpace = !AtomFlatFormulaList(NumberOfElements,FormulaTuple))) {
        PFprintf(Stream," ");
    }
//----Need to () nested formula that are not flat, e.g., binaries.
    if (FlatFormula(FormulaTuple[0])) {
        LastConnective = outermost;
    } else {
        LastConnective = none;
    }
    PrintFileTSTPFormula(Stream,Language,FormulaTuple[0],Indent+2,Pretty,LastConnective,
TSTPSyntaxFlag);
    for (ElementNumber=1;ElementNumber < NumberOfElements;ElementNumber++) {
        PFprintf(Stream,",");
        if (Pretty && (!AtomFlatFormula(FormulaTuple[ElementNumber-1]) ||
!AtomFlatFormula(FormulaTuple[ElementNumber]))) {
            PFprintf(Stream,"\n");
            PrintSpaces(Stream,Indent+2);
        }
        if (FlatFormula(FormulaTuple[ElementNumber])) {
            LastConnective = outermost;
        } else {
            LastConnective = none;
        }
        PrintFileTSTPFormula(Stream,Language,FormulaTuple[ElementNumber],Indent+2,Pretty,
LastConnective,TSTPSyntaxFlag);
    }
    if (NeedSpace) {
        PFprintf(Stream," ");
    }
    PFprintf(Stream,"]");
}
//-------------------------------------------------------------------------------------------------
void PrintFileQuantifiedVariable(PRINTFILE Stream,SyntaxType Language,
QuantifiedFormulaType QuantifiedFormula,int Pretty,int Indent,int TSTPSyntaxFlag) {

    ConnectiveType FakeConnective;

//----Print existential count if there is one
    if (QuantifiedFormula.Quantifier == existential && 
QuantifiedFormula.ExistentialCount >= 0) {
        PFprintf(Stream,"%d:",QuantifiedFormula.ExistentialCount);
    }
    PFprintf(Stream,"%s",GetPrintSymbol(QuantifiedFormula.Variable));
    Indent += 2;
//----Here's where types are printed
    if (QuantifiedFormula.VariableType != NULL) {
        PFprintf(Stream,": ");
        if (LiteralFormula(QuantifiedFormula.VariableType) ||
FlatBinaryFormula(QuantifiedFormula.VariableType)) {
            FakeConnective = outermost;
        } else {
            FakeConnective = none;
        }
        PrintFileTSTPFormula(Stream,Language,QuantifiedFormula.VariableType,Indent,Pretty,
FakeConnective,TSTPSyntaxFlag);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileTSTPFormula(PRINTFILE Stream,SyntaxType Language,FORMULA Formula,int Indent,
int Pretty,ConnectiveType LastConnective,int TSTPSyntaxFlag) {
//----TSTPSyntaxFlag = 2 is the case of a negated equation or equality - the
//----former becomes <~> and the latter becomes !=.

    int NeedBrackets;
    int NeedNewLine;
    int ConnectiveIndent;
    int VariableIndent;
    int SideIndent;
    int LHSWasAppliedConnective;
    ConnectiveType Connective;
    ConnectiveType FakeConnective;
    FORMULA SideFormula;

    if (Formula == NULL) {
        CodingError("No TSTP formula to print");
        return;
    }
//DEBUG printf("Printing a formula of type %s, last connective was %s\n",FormulaTypeToString(Formula->Type),ConnectiveToString(LastConnective));
    switch (Formula->Type) {
        case tuple:
            PrintFileFormulaeTuple(Stream,Language,
Formula->FormulaUnion.TupleFormula.NumberOfElements,
Formula->FormulaUnion.TupleFormula.Elements,Pretty,Indent,TSTPSyntaxFlag);
            break;
        case sequent:
            PrintFileFormulaeTuple(Stream,Language,
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,
Formula->FormulaUnion.SequentFormula.LHS,Pretty,Indent,TSTPSyntaxFlag);
            if (Pretty) {
                PFprintf(Stream,"\n");
                PrintSpaces(Stream,Indent - 1 - 
strlen(ConnectiveToString(gentzenarrow)));
            }
            PFprintf(Stream,"%s ",ConnectiveToString(gentzenarrow));
            PrintFileFormulaeTuple(Stream,Language,
Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,
Formula->FormulaUnion.SequentFormula.RHS,Pretty,Indent,TSTPSyntaxFlag);
            break;
        case quantified:
            PFprintf(Stream,"%s",ConnectiveToString(
Formula->FormulaUnion.QuantifiedFormula.Quantifier));
            PrintSpaces(Stream,2 - strlen(ConnectiveToString(
Formula->FormulaUnion.QuantifiedFormula.Quantifier)));
            PFprintf(Stream,"[");
            VariableIndent = Indent + 3;
            PrintFileQuantifiedVariable(Stream,Language,Formula->FormulaUnion.QuantifiedFormula,
Pretty,Indent+4,TSTPSyntaxFlag);
            while (Pretty && 
//----Sequence of nested quantified formulae
Formula->FormulaUnion.QuantifiedFormula.Formula->Type == quantified &&
//----With the same quantifier
Formula->FormulaUnion.QuantifiedFormula.Quantifier ==
Formula->FormulaUnion.QuantifiedFormula.Formula->FormulaUnion.QuantifiedFormula.Quantifier) {
                PFprintf(Stream,",");
//----If current and next are flat stay on this line
                if (!FlatQuantifiedVariable(Formula->FormulaUnion.QuantifiedFormula) || 
!FlatQuantifiedVariable(Formula->FormulaUnion.QuantifiedFormula.Formula->
FormulaUnion.QuantifiedFormula)) {
                    PFprintf(Stream,"\n");
                    PrintSpaces(Stream,VariableIndent);
                }
                Formula = Formula->FormulaUnion.QuantifiedFormula.Formula;
                PrintFileQuantifiedVariable(Stream,Language,
Formula->FormulaUnion.QuantifiedFormula,Pretty,Indent+4,TSTPSyntaxFlag);
            }
            PFprintf(Stream,"] :");
//----If not pretty, or unary and atom, or atom, do on same line
            if (!Pretty || 
FlatSymbolOrUnaryFormula(Formula->FormulaUnion.QuantifiedFormula.Formula) ||
FlatEquation(Formula->FormulaUnion.QuantifiedFormula.Formula) || 
FlatBinaryFormula(Formula->FormulaUnion.QuantifiedFormula.Formula)) {
                PFprintf(Stream," ");
                PrintFileTSTPFormula(Stream,Language,
//TODO THIS 0 seems wrong
Formula->FormulaUnion.QuantifiedFormula.Formula,0,Pretty,none,TSTPSyntaxFlag);
            } else {
//----Otherwise on the next line
                PFprintf(Stream,"\n");
//----If another quantified, no extra indent
                if (Formula->FormulaUnion.QuantifiedFormula.Formula->Type != quantified) {
                    Indent += 2;
                }
                PrintSpaces(Stream,Indent);
                PrintFileTSTPFormula(Stream,Language,
Formula->FormulaUnion.QuantifiedFormula.Formula,Indent,Pretty,none,TSTPSyntaxFlag);
            }
            break;

        case binary:
        case assignment:
        case type_declaration:
            Connective = Formula->FormulaUnion.BinaryFormula.Connective;
//DEBUG printf("Printing %s with connective %s, last connective was %s, indent %d\n",FormulaTypeToString(Formula->Type),ConnectiveToString(Connective),ConnectiveToString(LastConnective),Indent);
//----No brackets for sequences of associative formulae and top level
            if (LastConnective == outermost || 
//----Sadly the old BNF required ()s around equations on the side of a binary, and too many
//----systems (E and Leo-III at least) have encoded that. Shitto, because new BNF does not
//----require them (but accepts them).
 (LastConnective == none && 
  (((Language == tptp_fof || Language == tptp_cnf || Language == tptp_tcf) && 
     PreUnitEquation(Formula)) ||
   TypeDefnIdFormula(Formula))) ||
 (Connective == LastConnective && Associative(Connective)) ||
 (LastConnective == brackets && Associative(Connective))) {
                NeedBrackets = 0;
                ConnectiveIndent = Indent - strlen(ConnectiveToString(Connective)) - 1;
            } else {
                NeedBrackets = 1;
                ConnectiveIndent = Indent - strlen(ConnectiveToString(Connective)) + 1;
                PFprintf(Stream,"( ");
                Indent += 2;
            }
//----If in a negated infix equality, use != and reset
            if (Connective == equation && TSTPSyntaxFlag == 2) {
                Connective = negequation;
                ConnectiveIndent--;
                TSTPSyntaxFlag = 1;
            } 
//----Need to force brackets for right associative operators
            SideFormula = Formula->FormulaUnion.BinaryFormula.LHS;
//DEBUG printf("Printing LHS %s with connective %s, last connective was %s, indent %d\n",FormulaTypeToString(SideFormula->Type),ConnectiveToString(Connective),ConnectiveToString(LastConnective),Indent);
            SideIndent = Indent;
            LHSWasAppliedConnective = SideFormula->Type == applied_connective;
            if ((Associative(Connective) && !FullyAssociative(Connective) && 
SideFormula->Type == binary &&
RightAssociative(SideFormula->FormulaUnion.BinaryFormula.Connective)) ||
//----Need ()s around complex sides of equations. The BNF says negations are complex.
//----Binary gets dealt with in recursion regarding associativity. But negated equations have
//----to be dealt with here because later they are kinda binary with TSTPSyntaxFlag = 2.
(Equation(Formula,NULL,NULL) && !LiteralOrTuple(SideFormula) && 
!NegatedEquation(SideFormula,NULL,NULL) && !BinaryFormula(SideFormula))) {
// (Equation(SideFormula,NULL,NULL) || !BinaryFormula(SideFormula)))) {
                FakeConnective = brackets;
                PFprintf(Stream,"( ");
                SideIndent += 2;
            } else if (Formula->Type == assignment) {
                FakeConnective = outermost;
            } else {
                FakeConnective = Connective;
            }
            PrintFileTSTPFormula(Stream,Language,SideFormula,SideIndent,Pretty,FakeConnective,
TSTPSyntaxFlag);
            if (FakeConnective == brackets) {
                PFprintf(Stream," )");
            }
//----No new line for sequences of @ and >, and flat equations. Seems redundant here.
            NeedNewLine = !FlatFormula(Formula) && !PreUnitEquation(Formula) &&
!TypeDefnIdFormula(Formula);
            if (Pretty && NeedNewLine) {
                PFprintf(Stream,"\n");
                PrintSpaces(Stream,ConnectiveIndent);
            } else if (Connective != typecolon && Connective != assignmentsym) {
                PFprintf(Stream," ");
            }
            PFprintf(Stream,"%s ",ConnectiveToString(Connective));
            SideFormula = Formula->FormulaUnion.BinaryFormula.RHS;
//DEBUG printf("Printing RHS %s with connective %s, last connective was %s, indent %d\n",FormulaTypeToString(SideFormula->Type),ConnectiveToString(Connective),ConnectiveToString(LastConnective),Indent);
//----If didn't need a new line, and a type dec or defn then new line if not flat RHS
            if (Pretty && !NeedNewLine && TypeDefnIdFormula(Formula) &&
(SideFormula->Type == tuple || SideFormula->Type == ite_formula ||
 SideFormula->Type == let_formula || PolymorphicTypeFormula(SideFormula))) {
// !FlatTypeDefnIdFormula(Formula)) {
// !AtomicallyFlatFormula(SideFormula)) {
// SideFormula->Type != tuple) {
                PFprintf(Stream,"\n");
                Indent += 2;
                PrintSpaces(Stream,Indent);
            }
//----If a : or := then no ()s required on RHS except if @ constructor
            SideIndent = Indent;
            if (TypeDefnIdConnective(Connective) && FlatFormula(SideFormula)) {
//----Why? := is very low precedence
//      && !ApplicationFormula(SideFormula)) {
                FakeConnective = outermost;
//----Need to force brackets for left associative operators
            } else {
                if (
(Associative(Connective) && !FullyAssociative(Connective) && SideFormula->Type == binary && 
 LeftAssociative(SideFormula->FormulaUnion.BinaryFormula.Connective)) ||
(Equation(Formula,NULL,NULL) && !LiteralOrTuple(SideFormula) && 
 !NegatedEquation(SideFormula,NULL,NULL) && !BinaryFormula(SideFormula)) ||
(LHSWasAppliedConnective)) {
// (Equation(SideFormula,NULL,NULL) || !BinaryFormula(SideFormula)))) {
                    FakeConnective = brackets;
                    PFprintf(Stream,"( ");
                    SideIndent += 2;
                } else {
                    FakeConnective = Connective;
                }
            }
            PrintFileTSTPFormula(Stream,Language,SideFormula,SideIndent,Pretty,FakeConnective,
TSTPSyntaxFlag);
            if (FakeConnective == brackets) {
                PFprintf(Stream," )");
            }
            if (NeedBrackets) {
                PFprintf(Stream," )");
            }
            break;

        case unary:
//----Special for infix negated equality
            if (TSTPSyntaxFlag && 
(NegatedEquation(Formula,NULL,NULL) || NegatedEquality(Formula))) {
                TSTPSyntaxFlag = 2;
                PrintFileTSTPFormula(Stream,Language,Formula->FormulaUnion.UnaryFormula.Formula,
Indent,Pretty,LastConnective,TSTPSyntaxFlag);
            } else {
                if (
!((Language == tptp_cnf || Language == tptp_fof) && UnarySymbolFormula(Formula)) &&
(!Pretty ||
 (!SymbolFormula(Formula->FormulaUnion.UnaryFormula.Formula) &&
  !UnaryFormula(Formula->FormulaUnion.UnaryFormula.Formula) &&
  !BinaryFormula(Formula->FormulaUnion.UnaryFormula.Formula) &&
  !QuantifiedFormula(Formula->FormulaUnion.UnaryFormula.Formula)) ||
Equation(Formula->FormulaUnion.UnaryFormula.Formula,NULL,NULL) || 
NegatedEquation(Formula->FormulaUnion.UnaryFormula.Formula,NULL,NULL) || 
NegatedEquality(Formula->FormulaUnion.UnaryFormula.Formula))) {
                    FakeConnective = brackets;
                } else {
                    FakeConnective = none;
                }
                PFprintf(Stream,"%s",ConnectiveToString(
Formula->FormulaUnion.UnaryFormula.Connective));
                switch (strlen(ConnectiveToString(Formula->FormulaUnion.UnaryFormula.Connective))) {
                    case 1:
                        ConnectiveIndent = 2;
                        break;
                    case 2:
                    case 3:
                        ConnectiveIndent = 4;
                        break;
                    case 4:
                    case 5:
                        ConnectiveIndent = 6;
                        break;
                    default:
                        CodingError("Weird length unary connective");
                }
                PrintSpaces(Stream,
ConnectiveIndent - strlen(ConnectiveToString(Formula->FormulaUnion.UnaryFormula.Connective)));
                Indent += ConnectiveIndent;
                if (FakeConnective == brackets) {
                    PFprintf(Stream,"( ");
                    Indent +=2;
                }
                PrintFileTSTPFormula(Stream,Language,Formula->FormulaUnion.UnaryFormula.Formula,
Indent,Pretty,FakeConnective,TSTPSyntaxFlag);
                if (FakeConnective == brackets) {
                    PFprintf(Stream," )");
                }
            }
            break;

        case atom:
        case applied_connective:
//DEBUG printf("Printing atom with symbol %s, last connective was %s, indent %d\n",GetSymbol(Formula->FormulaUnion.Atom),ConnectiveToString(LastConnective),Indent);
//----THF connectives in ()s are atoms
            NeedBrackets = Formula->FormulaUnion.Atom->Type == connective || 
//----Boolean variables need to be ()ed to when I read them I know they are formulae not terms
(Language != tptp_thf && Formula->FormulaUnion.Atom->Type == variable && 
 Formula->FormulaUnion.Atom->TheSymbol.Variable->Type == formula &&
//----Can't remember why I excluded case of preceding (
 LastConnective != brackets);
            FakeConnective = LastConnective;
            if (NeedBrackets) {
                PFprintf(Stream,"(");
                if (LastConnective == brackets) {
                    PFprintf(Stream," ");
                }
                FakeConnective = brackets;
            }
//----New {}ed connective symbols for NXF
            if (Formula->Type == applied_connective) {
                PFprintf(Stream,"{");
            }
            PrintFileTSTPTerm(Stream,Language,Formula->FormulaUnion.Atom,Pretty,Indent+2,
FakeConnective,TSTPSyntaxFlag);
            if (Formula->Type == applied_connective) {
                PFprintf(Stream,"}");
            }
            if (NeedBrackets) {
                if (LastConnective == brackets) {
                    PFprintf(Stream," ");
                }
                PFprintf(Stream,")");
            }
            break;

        case ite_formula:
            NeedNewLine = !FlatITEFormula(Formula);
            PFprintf(Stream,"$ite(");
            if (Pretty && NeedNewLine) {
                PFprintf(Stream,"\n");
                Indent += 2;
                PrintSpaces(Stream,Indent);
            }
            PrintFileTSTPFormula(Stream,Language,
Formula->FormulaUnion.ConditionalFormula.Condition,Indent,Pretty,OutermostWithoutBrackets(
Formula->FormulaUnion.ConditionalFormula.Condition) ? outermost : none,TSTPSyntaxFlag);
            PFprintf(Stream,",");
            if (Pretty && NeedNewLine) {
                PFprintf(Stream,"\n");
                PrintSpaces(Stream,Indent);
            }
            PrintFileTSTPFormula(Stream,Language,
Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue,Indent,Pretty,OutermostWithoutBrackets(
Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue) ? outermost : none,TSTPSyntaxFlag);
            PFprintf(Stream,",");
            if (Pretty && NeedNewLine) {
                PFprintf(Stream,"\n");
                PrintSpaces(Stream,Indent);
            }
            PrintFileTSTPFormula(Stream,Language,
Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse,Indent,Pretty,OutermostWithoutBrackets(
Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse) ? outermost : none,TSTPSyntaxFlag);
            if (NeedNewLine) {
                PFprintf(Stream," ");
            }
            PFprintf(Stream,")");
            break;

        case let_formula:
            PFprintf(Stream,"$let(");
            if (Pretty) {
                PFprintf(Stream,"\n");
                Indent += 2;
                PrintSpaces(Stream,Indent);
            }
            PrintFileTSTPFormula(Stream,Language,Formula->FormulaUnion.LetFormula.LetTypes,Indent,
Pretty,outermost,TSTPSyntaxFlag);
            PFprintf(Stream,",");
            if (Pretty) {
                PFprintf(Stream,"\n");
                PrintSpaces(Stream,Indent);
            }
            PrintFileTSTPFormula(Stream,Language,Formula->FormulaUnion.LetFormula.LetDefn,Indent,
Pretty,outermost,TSTPSyntaxFlag);
            PFprintf(Stream,",");
            if (Pretty) {
                PFprintf(Stream,"\n");
                PrintSpaces(Stream,Indent);
            }
            PrintFileTSTPFormula(Stream,Language,Formula->FormulaUnion.LetFormula.LetBody,Indent,
Pretty,OutermostWithoutBrackets(Formula->FormulaUnion.LetFormula.LetBody) ? outermost : none,
TSTPSyntaxFlag);
            PFprintf(Stream," )");
            break;

        default:
            CodingError("Formula type unknown for printing");
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void PrintTSTPFormula(FILE * Stream,SyntaxType Language,FORMULA Formula,int Indent,int Pretty,
ConnectiveType LastConnective,int TSTPSyntaxFlag) {

    PRINTFILE LocalStream;
                
    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileTSTPFormula(LocalStream,Language,Formula,Indent,Pretty,LastConnective,
TSTPSyntaxFlag);
        ClosePrintFile(LocalStream);
    }
}           
//-------------------------------------------------------------------------------------------------
void PrintFileAnnotatedTSTPFormula(PRINTFILE Stream,SyntaxType Language,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula,PrintFormatType Format,int Pretty) {

    switch (Language) {
        case tptp_tpi:
            PFprintf(Stream,"tpi");
            break;
        case tptp_thf:
            PFprintf(Stream,"thf");
            break;
        case tptp_tff:
            PFprintf(Stream,"tff");
            break;
        case tptp_tcf:
            PFprintf(Stream,"tcf");
            break;
        case tptp_fof:
            PFprintf(Stream,"fof");
            break;
        case tptp_cnf:
            PFprintf(Stream,"cnf");
            break;
        default:
            CodingError("Formula type unknown for printing");
            break;
    }
    PFprintf(Stream,"(%s,%s",AnnotatedTSTPFormula.Name,StatusToString(AnnotatedTSTPFormula.Status));
    if (Format == tptp && AnnotatedTSTPFormula.SubStatus != NULL) {
        PFprintf(Stream,"-");
        PrintFileTSTPTerm(Stream,Language,AnnotatedTSTPFormula.SubStatus,0,0,outermost,1);
    }
    PFprintf(Stream,",");

    if (Language == tptp_tpi) {
        PrintFileTSTPFormula(Stream,Language,AnnotatedTSTPFormula.FormulaWithVariables->Formula,
0,0,outermost,1);
    } else {
        if (Pretty) {
            PFprintf(Stream,"\n");
            PrintSpaces(Stream,4);
//----Things that start on a new line alone
            if (OutermostWithoutBrackets(AnnotatedTSTPFormula.FormulaWithVariables->Formula)) {
                PrintFileTSTPFormula(Stream,Language,
AnnotatedTSTPFormula.FormulaWithVariables->Formula,4,Pretty,outermost,1);
            } else {
//----Things that need ()s on the new line
                PrintFileTSTPFormula(Stream,Language,
AnnotatedTSTPFormula.FormulaWithVariables->Formula,4,Pretty,none,1);
            }
        } else {
            PrintFileTSTPFormula(Stream,Language,
AnnotatedTSTPFormula.FormulaWithVariables->Formula,0,Pretty,outermost,1);
        }
    }

//----Source and useful info are optional
    if (Format == tptp && AnnotatedTSTPFormula.Source != NULL) {
        PFprintf(Stream,",%s",(Pretty?"\n    ":""));
//----Still need full TSTP mode because formulae might appear in the source
//----of useful info
        PrintFileTSTPTerm(Stream,Language,AnnotatedTSTPFormula.Source,Pretty,4,outermost,1);
        if (AnnotatedTSTPFormula.UsefulInfo != NULL) {
            PFprintf(Stream,",%s",(Pretty?"\n    ":""));
            PrintFileTSTPTerm(Stream,Language,AnnotatedTSTPFormula.UsefulInfo,Pretty,-1,
outermost,1);
        }
    }
    PFprintf(Stream," ).\n");
}
//-------------------------------------------------------------------------------------------------
void PrintAnnotatedTSTPFormula(FILE * Stream,SyntaxType Language,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula,PrintFormatType Format,int Pretty) {

    PRINTFILE LocalStream;
                
    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileAnnotatedTSTPFormula(LocalStream,Language,AnnotatedTSTPFormula,Format,Pretty);
        ClosePrintFile(LocalStream);
    }
}           
//-------------------------------------------------------------------------------------------------
void PrintFileTPTPClause(PRINTFILE Stream,SyntaxType Language,FORMULA Formula,int Pretty,
int Indent,int AlreadyIndented,int NeedCommaNewline) {

//----Bypass the universal quantifiers (all outermost)
    while (Formula->Type == quantified &&  
Formula->FormulaUnion.QuantifiedFormula.Quantifier == universal) {
//DEBUG printf("drop quantifier\n");
        Formula = Formula->FormulaUnion.QuantifiedFormula.Formula;
    }

//-----Start formatting
    if (NeedCommaNewline) {
        PFprintf(Stream,",\n");
        AlreadyIndented = 0;
    }
    PrintFileIndent(Stream,Indent,AlreadyIndented,1);

//-----Print the literals
    switch (Formula->Type) {
        case atom:
        case applied_connective:
//----Print nothing for an empty clause
            if (strcmp(GetSymbol(Formula->FormulaUnion.Atom),"$false")) {
                PFprintf(Stream,"++");
                PrintFileTSTPTerm(Stream,Language,Formula->FormulaUnion.Atom,Pretty,-1,outermost,0);
            }
            break;
        case unary:
            if (Formula->FormulaUnion.UnaryFormula.Connective == negation) {
                PFprintf(Stream,"--");
                PrintFileTSTPTerm(Stream,Language,
Formula->FormulaUnion.UnaryFormula.Formula->FormulaUnion.Atom,Pretty,-1,outermost,0);
            } else {
                CodingError("Printing a non-clause as a clause");
            }
            break;
        case binary:
            if (Formula->FormulaUnion.BinaryFormula.Connective == disjunction) {
                PrintFileTPTPClause(Stream,Language,Formula->FormulaUnion.BinaryFormula.LHS,Pretty,
Indent,Indent,0);
                PrintFileTPTPClause(Stream,Language,Formula->FormulaUnion.BinaryFormula.RHS,Pretty,
Indent,0,1);
            } else {
                CodingError("Printing a non-clause as a clause");
            }
            break;
        default:
            CodingError("Printing a non-clause as a clause");
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void PrintTPTPClause(FILE * Stream,SyntaxType Language,FORMULA Formula,int Pretty,
int Indent,int AlreadyIndented,int NeedCommaNewline) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileTPTPClause(LocalStream,Language,Formula,Pretty,Indent,AlreadyIndented,
NeedCommaNewline);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileAnnotatedTPTPFormula(PRINTFILE Stream,SyntaxType Language,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula,int Pretty) {

    switch (Language) {
        case tptp_fof:
            PFprintf(Stream,"input_formula");
            break;
        case tptp_cnf:
            PFprintf(Stream,"input_clause");
            break;
        default:
            CodingError("Formula type unknown for printing");
            break;
    }
    PFprintf(Stream,"(%s,%s,%s",AnnotatedTSTPFormula.Name,
StatusToString(AnnotatedTSTPFormula.Status),(Pretty?"\n":""));
    switch (Language) {
        case tptp_fof:
            PFprintf(Stream,"    (");
            PrintFileTSTPFormula(Stream,tptp_fof,
AnnotatedTSTPFormula. FormulaWithVariables->Formula,6,Pretty,outermost,0);
            PFprintf(Stream," )");
            break;
        case tptp_cnf:
            PFprintf(Stream,"    [");
            PrintFileTPTPClause(Stream,Language,AnnotatedTSTPFormula.FormulaWithVariables->Formula,
Pretty,5,5,0);
            PFprintf(Stream,"]");
            break;
        default:
            CodingError("Formula type unknown for printing");
            break;
    }
    PFprintf(Stream,").\n");
}
//-------------------------------------------------------------------------------------------------
void PrintAnnotatedTPTPFormula(FILE * Stream,SyntaxType Language,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula,int Pretty) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileAnnotatedTPTPFormula(LocalStream,Language,AnnotatedTSTPFormula,Pretty);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileAnnotatedTSTPNode(PRINTFILE Stream,ANNOTATEDFORMULA AnnotatedFormula,
PrintFormatType Format,int Pretty) {

    if (AnnotatedFormula != NULL) {
        switch (AnnotatedFormula->Syntax) {
            case include:
                PrintFileTSTPTerm(Stream,AnnotatedFormula->Syntax,
AnnotatedFormula->AnnotatedFormulaUnion.Include,0,-1,outermost,0);
                PFprintf(Stream,".\n");
                break;
            case comment:
                PFprintf(Stream,"%s\n",AnnotatedFormula->AnnotatedFormulaUnion.Comment);
                break;
            case blank_line:
                PFprintf(Stream,"\n");
                break;
            case tptp_tpi:
            case tptp_thf:
            case tptp_tff:
            case tptp_tcf:
            case tptp_fof:
            case tptp_cnf:
                switch (Format) {
                    case tptp:
                    case tptp_short:
                        PrintFileAnnotatedTSTPFormula(Stream,AnnotatedFormula->Syntax,
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula,Format,Pretty);
                        break;
                    case oldtptp:
                        PrintFileAnnotatedTPTPFormula(Stream,AnnotatedFormula->Syntax,
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula,Pretty);
                        break;
                    default:
                        CodingError("Print format not known");
                        break;
                }
                break;
            default:
                CodingError("Annotated formula syntax unknown for printing");
                break;
        }
    }
}
//-------------------------------------------------------------------------------------------------
void PrintStringAnnotatedTSTPNode(char * PutOutputHere,ANNOTATEDFORMULA AnnotatedFormula,
PrintFormatType Format,int Pretty) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenStringPrintFile(PutOutputHere)) != NULL) {
        PrintFileAnnotatedTSTPNode(LocalStream,AnnotatedFormula,Format,Pretty);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula,
PrintFormatType Format,int Pretty) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileAnnotatedTSTPNode(LocalStream,AnnotatedFormula,Format,Pretty);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileAnnotatedTSTPNodeWithStatus(PRINTFILE Stream,ANNOTATEDFORMULA AnnotatedFormula,
PrintFormatType Format,int Pretty,StatusType Role) {

    StatusType OldRole;
    TERM OldSubRole;
    StatusType DesiredRole;

    if (!ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        CodingError("Trying to print a non-formula");
    }
    OldRole = GetRole(AnnotatedFormula,&OldSubRole);
    DesiredRole = Role == axiom ? axiom_like : Role;
    
//----Only set if not nonstatus, not type (hack), and not what we want
    if (Role != nonstatus && OldRole != type && !CheckRole(OldRole,DesiredRole)) {
        SetStatus(AnnotatedFormula,Role,OldSubRole);
    }
    PrintFileAnnotatedTSTPNode(Stream,AnnotatedFormula,Format,Pretty);
    SetStatus(AnnotatedFormula,OldRole,OldSubRole);
}
//-------------------------------------------------------------------------------------------------
void PrintAnnotatedTSTPNodeWithStatus(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula,
PrintFormatType Format,int Pretty,StatusType Status) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileAnnotatedTSTPNodeWithStatus(LocalStream,AnnotatedFormula,Format,Pretty,Status);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileListOfAnnotatedTSTPNodes(PRINTFILE Stream,SIGNATURE Signature,LISTNODE Head,
PrintFormatType Format,int Pretty) {

    switch (Format) {
        case tptp:
        case tptp_short:
        case oldtptp:
            while (Head != NULL) {
                PrintFileAnnotatedTSTPNode(Stream,Head->AnnotatedFormula,Format,Pretty);
//----Always a blank line after a logical, if pretty
                if (Pretty && 
((LogicalAnnotatedFormula(Head->AnnotatedFormula) &&
 (Head->Next == NULL || Head->Next->AnnotatedFormula->Syntax != blank_line)) ||
(TPIAnnotatedFormula(Head->AnnotatedFormula) &&
 (Head->Next == NULL || LogicalAnnotatedFormula(Head->Next->AnnotatedFormula))))) {
                    PFprintf(Stream,"\n");
                }
                Head = Head->Next;
            }
            break;
        case dfg:
            DFGPrintHeader(Stream->FileHandle,Head,Signature);
            DFGPrintListOfAnnotatedTSTPNodes(Stream->FileHandle,Head);
            DFGPrintTailer(Stream->FileHandle);
            break;
        case lambdapi:
            LPPrintHeader(Stream->FileHandle,Head,Signature);
            LPPrintListOfAnnotatedTSTPNodes(Stream->FileHandle,Head);
            LPPrintTailer(Stream->FileHandle);
            break;
        case otter:
            OtterPrintHeader(Stream->FileHandle,Head,Signature);
            OtterPrintListOfAnnotatedTSTPNodes(Stream->FileHandle,Head);
            OtterPrintTailer(Stream->FileHandle);
            break;
        case kif:
            KIFPrintListOfAnnotatedTSTPNodes(Stream->FileHandle,Head);
            break;
        case xml:
            XMLPrintListOfAnnotatedTSTPNodes(Stream->FileHandle,Head,CONTENT_XML,FALSE);
            break;
        case xml_short:
            XMLPrintListOfAnnotatedTSTPNodes(Stream->FileHandle,Head,CONTENT_TSTP,FALSE);
            break;
        case sumo:
            SUMOPrintListOfAnnotatedTSTPNodes(Stream->FileHandle,Head,Signature);
            break;
        case smt2:
            SMT2PrintHeader(Stream->FileHandle,Head,Signature);
            SMT2PrintListOfAnnotatedTSTPNodes(Stream->FileHandle,Head);
            break;
        case nonprinttype:
            CodingError("Not a print type for printing list of nodes");
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void PrintListOfAnnotatedTSTPNodes(FILE * Stream,SIGNATURE Signature,LISTNODE Head,
PrintFormatType Format,int Pretty) {

    PRINTFILE LocalStream;
            
    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileListOfAnnotatedTSTPNodes(LocalStream,Signature,Head,Format,Pretty);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintFileListOfAnnotatedTSTPNodesWithStatus(PRINTFILE Stream,SIGNATURE Signature,
LISTNODE Head,PrintFormatType Format,int Pretty,StatusType Status) {

    while (Head != NULL) {
        PrintFileAnnotatedTSTPNodeWithStatus(Stream,Head->AnnotatedFormula,Format,Pretty,Status);
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------
void PrintListOfAnnotatedTSTPNodesWithStatus(FILE * Stream,SIGNATURE Signature,LISTNODE Head,
PrintFormatType Format,int Pretty,StatusType Status) {

    PRINTFILE LocalStream;

    if ((LocalStream = OpenFILEPrintFile(Stream,NULL)) != NULL) {
        PrintFileListOfAnnotatedTSTPNodesWithStatus(LocalStream,Signature,Head,Format,Pretty,
Status);
        ClosePrintFile(LocalStream);
    }
}
//-------------------------------------------------------------------------------------------------

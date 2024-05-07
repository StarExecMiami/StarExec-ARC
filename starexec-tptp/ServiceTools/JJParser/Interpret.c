#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "PrintTSTP.h"
#include "Examine.h"
#include "Interpret.h"
//-------------------------------------------------------------------------------------------------
int FormulaTrueInInterpretation(FORMULA Formula,InterpretationType 
Interpretation) {

    int LHSInterpretation;
    int RHSInterpretation;

    switch (Formula->Type) {
        case quantified:
            return(FormulaTrueInInterpretation(Formula->FormulaUnion.
QuantifiedFormula.Formula,Interpretation));
            break;
        case binary:
//----A little inefficient, but WTF
            LHSInterpretation = FormulaTrueInInterpretation(Formula->
FormulaUnion.BinaryFormula.LHS,Interpretation);
            RHSInterpretation = FormulaTrueInInterpretation(Formula->
FormulaUnion.BinaryFormula.RHS,Interpretation);
            switch (Formula->FormulaUnion.BinaryFormula.Connective) {
                case disjunction:
                    return(LHSInterpretation || RHSInterpretation);
                    break;
                case conjunction:
                    return(LHSInterpretation && RHSInterpretation);
                    break;
                case equivalence:
                    return(LHSInterpretation == RHSInterpretation);
                    break;
                case implication:
                    return(!LHSInterpretation || (LHSInterpretation && 
RHSInterpretation));
                    break;
                case reverseimplication:
                    return(!RHSInterpretation || (RHSInterpretation && 
LHSInterpretation));
                    break;
                case nonequivalence:
                    return(LHSInterpretation != RHSInterpretation);
                    break;
                case negateddisjunction:
                    return(!(LHSInterpretation || RHSInterpretation));
                    break;
                case negatedconjunction:
                    return(!(LHSInterpretation && RHSInterpretation));
                    break;
                default:
                    CodingError(
"Illegal binary connective in FormulaTrueInInterpretation");
                    break;
            }
            break;
        case unary:
            if (Formula->FormulaUnion.UnaryFormula.Connective == negation) {
                return(!FormulaTrueInInterpretation(Formula->FormulaUnion.
UnaryFormula.Formula,Interpretation));
            } else {
                CodingError(
"Illegal unary connective in FormulaTrueInInterpretation");
            }
            break;
        case atom:
        case applied_connective:
            if (!strcmp(GetSymbol(Formula->FormulaUnion.Atom),"$true")) {
                return(1);
            } else if (!strcmp(GetSymbol(Formula->FormulaUnion.Atom),"$false")) {
                return(0);
            } else {
                return(Interpretation == positive);
            }
            break;
        default:
            CodingError("Unknown formula type FormulaTrueInInterpretation");
            break;
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int TrueAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

    FORMULA TheFormula;

    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
        TheFormula = AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula;
        return(TheFormula->Type == atom &&
!strcmp(GetSymbol(TheFormula->FormulaUnion.Atom),"$true"));
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int FalseAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

    FORMULA TheFormula;

    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
        TheFormula = AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula;
        return(TheFormula->Type == atom && !strcmp(GetSymbol(TheFormula->FormulaUnion.Atom),
"$false"));
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int AnnotatedFormulaTrueInInterpretation(ANNOTATEDFORMULA AnnotatedFormula,
InterpretationType Interpretation) {

    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
        return(FormulaTrueInInterpretation(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
Interpretation));
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int ListOfAnnotatedFormulaTrueInInterpretation(LISTNODE Head,
InterpretationType Interpretation) {

    while (Head != NULL) {
        if (AnnotatedFormulaTrueInInterpretation(Head->AnnotatedFormula,
Interpretation)) {
            Head = Head->Next;
        } else {
//DEBUG PrintAnnotatedTSTPNode(stdout,Head->AnnotatedFormula,tptp,1);
//DEBUG printf("is false in %d\n",Interpretation);
            return(0);
        }
    }

    return(1);
}
//-------------------------------------------------------------------------------------------------

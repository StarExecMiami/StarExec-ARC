#ifndef INTERPRET_H
#define INTERPRET_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
#include "Utilities.h"
//-------------------------------------------------------------------------------------------------
typedef enum {
    positive,
    negative
} InterpretationType;
//-------------------------------------------------------------------------------------------------
int TrueAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula);
int FalseAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula);
int AnnotatedFormulaTrueInInterpretation(ANNOTATEDFORMULA AnnotatedFormula,
InterpretationType Interpretation);
int ListOfAnnotatedFormulaTrueInInterpretation(LISTNODE Head,
InterpretationType Interpretation);
//-------------------------------------------------------------------------------------------------
#endif

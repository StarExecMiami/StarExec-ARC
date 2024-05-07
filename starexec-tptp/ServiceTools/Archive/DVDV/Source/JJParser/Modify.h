#ifndef MODIFY_H
#define MODIFY_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
#include "Utilities.h"
//-----------------------------------------------------------------------------
int SetStatus(ANNOTATEDFORMULA AnnotatedFormula,StatusType Status,
StatusType SubStatus);
void DeDoubleNegateFormula(FORMULA * Formula);
int DeDoubleNegate(ANNOTATEDFORMULA AnnotatedFormula);
void NegateFormula(FORMULA * Formula,int Simplify);
int Negate(ANNOTATEDFORMULA AnnotatedFormula,int Simplify);
void UniqueifyVariableNames(ANNOTATEDFORMULA AnnotatedFormula);
int RemoveVacuousQuantifiersFromAnnotatedFormula(
ANNOTATEDFORMULA AnnotatedFormula);
int UniversalFOFify(ANNOTATEDFORMULA AnnotatedFormula);
int RemoveUsefulInformationFromAnnotatedFormula(
ANNOTATEDFORMULA AnnotatedFormula,char * PrincipleSymbol);
int AddUsefulInformationToAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature,char * UsefulInformation);
//-----------------------------------------------------------------------------
#endif

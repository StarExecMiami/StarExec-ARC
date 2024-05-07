#ifndef MODIFY_H
#define MODIFY_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
#include "Utilities.h"
//-------------------------------------------------------------------------------------------------
int SetName(ANNOTATEDFORMULA AnnotatedFormula,char * Name);
int SetSyntax(ANNOTATEDFORMULA AnnotatedFormula,SyntaxType Syntax);
int SetStatus(ANNOTATEDFORMULA AnnotatedFormula,StatusType Status,TERM SubStatus);
void UninterpretNumbersInSignature(SIGNATURE Signature,int Quote);
void ShortenSymbolsInSignature(SIGNATURE Signature);
void AritizeSymbolsInSignature(SIGNATURE Signature);
void DequoteSymbolsInSignature(SIGNATURE Signature);
void ExpandListAssumptions(LISTNODE Head,SIGNATURE Signature);
void DeDoubleNegateFormula(FORMULA * Formula);
int DeDoubleNegate(ANNOTATEDFORMULA AnnotatedFormula);
void NegateFormula(FORMULA * Formula);
int Negate(ANNOTATEDFORMULA AnnotatedFormula,int Simplify);
int NegateListOfAnnotatedTSTPNodes(LISTNODE Head,int Simplify);
int NegateConjectures(LISTNODE Head,int Simplify);
void UniqueifyVariableNames(ANNOTATEDFORMULA AnnotatedFormula);
int RemoveVacuousQuantifiersFromAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula);
void QuantifyFormula(FORMULA * UnquantifiedFormula,ConnectiveType Quantifier,
VARIABLENODE VariableNode);
void Quantify(ANNOTATEDFORMULA AnnotatedFormula,ConnectiveType Quantifier);
void QuantifyList(LISTNODE Head,ConnectiveType Quantifier);
void FOFify(ANNOTATEDFORMULA AnnotatedFormula,ConnectiveType Quantifier);
void FOFifyList(LISTNODE Head,ConnectiveType Quantifier);
void RandomizeAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,unsigned int Seed);
void EnsureShortForm(ANNOTATEDFORMULA AnnotatedFormula,SIGNATURE Simplify);
void DoUpdateRecordInList(TERM TheList,SIGNATURE Signature,char * UsefulInformation,int DoRemove,
int DoAdd);
int RemoveNamedTermFromList(char * Name,TERM TheList,int MaxToRemove,SIGNATURE Signature);
int RemoveParentFromInferenceTerm(char * ParentName,TERM Source,SIGNATURE Signature);
int SetSourceFromString(ANNOTATEDFORMULA AnnotatedFormula,SIGNATURE Signature,char * StringSource);
void RemoveUsefulInformationFromAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature,char * PrincipleSymbol);
void AddUsefulInformationToAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature,char * UsefulInformation);
void UpdateUsefulInformationInAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature,char * UsefulInformation);
void StandardizeFormula(FORMULA * Formula);
void StandardizeAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula);
void StandardizeListOfAnnotatedTSTPNodes(LISTNODE Head);
//-------------------------------------------------------------------------------------------------
#endif

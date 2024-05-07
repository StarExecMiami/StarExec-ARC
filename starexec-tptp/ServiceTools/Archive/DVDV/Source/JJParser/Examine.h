#ifndef EXAMINE_H
#define EXAMINE_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
#include "Utilities.h"
//-----------------------------------------------------------------------------
int CheckAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SyntaxType ExpectedSyntax);
char * GetSymbol(TERM Term);
int GetArity(TERM Term);

char * TSTPTermToString(TERM Term,String PutTermHere);

int CountVariableUsageInFormula(FORMULA Formula,VARIABLENODE Variable,
int * QuantifiedOccurences);
void NormalizeSymbolUsage(char * SymbolUsage);
char * GetLiteralSymbolUsage(FORMULA Literal,char ** PutUsageHere,
char ** VariablesStartHere);
char * GetAnnotatedFormulaSymbolUsage(ANNOTATEDFORMULA AnnotatedTSTPFormula,
char ** PutUsageHere,char ** FunctorUsageStartsHere);
char * GetListOfAnnotatedFormulaSymbolUsage(LISTNODE ListNode,
char ** PutUsageHere,char ** FunctorUsageStartsHere);

int CountLiteralsOfPolarity(ANNOTATEDFORMULA AnnotatedFormula,int * Positive,
int * Negative);
int RangeRestrictedClause(ANNOTATEDFORMULA AnnotatedFormula);
int HornClause(ANNOTATEDFORMULA AnnotatedFormula);
int NonHornClause(ANNOTATEDFORMULA AnnotatedFormula);
int CountAnnotatedFormulaUniqueVariablesByUse(ANNOTATEDFORMULA 
AnnotatedFormula,int MinUse,int MaxUse,ConnectiveType Quantification);
int CountAnnotatedFormulaSingletons(ANNOTATEDFORMULA AnnotatedFormula);
int CountAnnotatedFormulaUniqueVariables(ANNOTATEDFORMULA AnnotatedFormula);
int CountAnnotatedFormulaTerms(ANNOTATEDFORMULA AnnotatedFormula);
int CountAnnotatedFormulaAtomsByPredicate(ANNOTATEDFORMULA AnnotatedFormula,
char * Predicate);
void GetFormulaConnectiveUsage(FORMULA Formula,
double * NumberOfFormulaNegations,double * NumberOfFormulaDisjunctions,
double * NumberOfFormulaConjunctions,double * NumberOfFormulaEquivalences,
double * NumberOfFormulaImplications,
double * NumberOfFormulaReverseImplications,
double * NumberOfFormulaXORs,double * NumberOfFormulaNORs,
double * NumberOfFormulaNANDs,double * NumberOfFormulaUniversals,
double * NumberOfFormulaExistentials);
int AnnotatedFormulaDepth(ANNOTATEDFORMULA AnnotatedFormula);
int MaxAnnotatedFormulaTermDepth(ANNOTATEDFORMULA AnnotatedFormula);
int SumAnnotatedFormulaTermDepth(ANNOTATEDFORMULA AnnotatedFormula);

SyntaxType GetSyntax(ANNOTATEDFORMULA AnnotatedFormula);
SyntaxType GetListSyntax(LISTNODE Head);
char * GetName(ANNOTATEDFORMULA AnnotatedFormula,String PutNameHere);
StatusType GetStatus(ANNOTATEDFORMULA AnnotatedFormula,StatusType * SubStatus);
FORMULA GetLiteralFromAnnotatedClauseByNumber(ANNOTATEDFORMULA Clause,
int Number);

char * GetSource(ANNOTATEDFORMULA AnnotatedFormula,char * PutInfoHere);
char * GetInferenceRule(ANNOTATEDFORMULA AnnotatedFormula,char * PutNameHere);
char * GetInferenceInfoTerm(ANNOTATEDFORMULA AnnotatedFormula,char * Symbol,
char * PutInfoHere);
char * GetParentNames(ANNOTATEDFORMULA AnnotatedFormula,char * PutNamesHere);
char * GetFileSourceNameAndNode(ANNOTATEDFORMULA AnnotatedFormula,
char * PutUsageHere);

char * GetUsefulInfoTerm(ANNOTATEDFORMULA AnnotatedFormula,char * Symbol,
String PutInfoHere);
//-----------------------------------------------------------------------------
#endif

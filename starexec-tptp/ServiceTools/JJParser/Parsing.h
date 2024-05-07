#ifndef PARSING_H
#define PARSING_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
#include "Tokenizer.h"
#include "Utilities.h"
#include "SystemOnTPTP.h"
//-------------------------------------------------------------------------------------------------
void SetAllowFreeVariables(int OnOff);
void SetAllowFOFNumbers(int OnOff);

void IncreaseVariableUseCount(VARIABLENODE Variable,int HowMuch);
void PrintVariableList(VARIABLENODE Variables,VARIABLENODE EndOfScope);

TERM NewTerm(void);
TERMWITHVARIABLES ParseTermWithVariables(READFILE Stream,SyntaxType Language,SIGNATURE Signature,
int VariablesMustBeQuantifiedAlready);
void FreeTerm(TERM * Term,SIGNATURE Signature,VARIABLENODE * Variables);
void FreeTermWithVariables(TERMWITHVARIABLES * TermWithVariables,SIGNATURE Signature);
TERM DuplicateTerm(TERM Original,ContextType Context,int ForceNewVariables);
TERMWITHVARIABLES DuplicateTermWithVariables(TERMWITHVARIABLES Original,SIGNATURE Signature,
int ForceNewVariables);
TERM ParseTerm(READFILE Stream,SyntaxType Language,ContextType Context,VARIABLENODE * EndOfScope,
TermType Type,ConnectiveType Quantification,
int * InfixNegatedAtom,int VariablesMustBeQuantifiedAlready);

FORMULA NewFormula(void);
void FreeFormula(FORMULA * Formula,SIGNATURE Signature,VARIABLENODE * Variables);
FORMULAWITHVARIABLES NewFormulaWithVariables(void);
FORMULA ParseAtom(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int VariablesMustBeQuantifiedAlready);
FORMULA ParseUnaryFormula(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int VariablesMustBeQuantifiedAlready);
FORMULA DuplicateFormula(FORMULA Original,ContextType Context,int ForceNewVariables);
int RightAssociative(ConnectiveType Connective);
int LeftAssociative(ConnectiveType Connective);
int Associative(ConnectiveType Connective);
int FullyAssociative(ConnectiveType Connective);
int Symmetric(ConnectiveType Connective);
void FreeFormulaWithVariables(FORMULAWITHVARIABLES * FormulaWithVariables,SIGNATURE Signature);
FORMULAWITHVARIABLES DuplicateFormulaWithVariables(FORMULAWITHVARIABLES riginal,
SIGNATURE Signature,int ForceNewVariables);
FORMULA DuplicateInternalFormulaWithVariables(FORMULA Original,ContextType OriginalContext);
FORMULA ParseFormula(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int AllowBinary,int AllowInfixEquality,
int VariablesMustBeQuantifiedAlready,ConnectiveType LastConnective);
FORMULAWITHVARIABLES ParseFormulaWithVariables(READFILE Stream,SyntaxType Language,
SIGNATURE Signature,int VariablesMustBeQuantifiedAlready);

ANNOTATEDFORMULA DuplicateAnnotatedFormula(ANNOTATEDFORMULA Original,
SIGNATURE Signature);
void FreeAnnotatedFormula(ANNOTATEDFORMULA * AnnotatedFormula,SIGNATURE Signature);
//----Not for the weak 
ANNOTATEDFORMULA ParseAnnotatedFormula(READFILE Stream,SIGNATURE Signature);
ANNOTATEDFORMULA ParseAndUseAnnotatedFormula(READFILE Stream,SIGNATURE 
Signature);

void GetIncludeParts(ANNOTATEDFORMULA AnnotatedFormula,String IncludeFile,String IncludeFilter);
LISTNODE ParseREADFILEOfFormulae(READFILE Stream,SIGNATURE Signature,int ExpandIncludes,
char * NameFilter);
LISTNODE ParseFILEOfFormulae(char * FileName,FILE * FileStream,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter);
LISTNODE GetIncludedAnnotatedFormulae(READFILE Stream,SIGNATURE Signature,int ExpandIncludes,
ANNOTATEDFORMULA AnnotatedFormula);
LISTNODE ParseFileOfHeader(char * FileName);
LISTNODE ParseFileOfFormulae(char * FileName,char * CurrentFileName,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter);
LISTNODE ParseStringOfFormulae(char * Content,SIGNATURE Signature,int ExpandIncludes,
char * NameFilter);
TERM ParseStringTerm(char * Content,SyntaxType Language,SIGNATURE Signature,
int VariablesMustBeQuantifiedAlready);
int ParseFileForSZSResults(char * FileName,SZSResultType * SZSResult,SZSOutputType * SZSOutput);
//-------------------------------------------------------------------------------------------------
#endif

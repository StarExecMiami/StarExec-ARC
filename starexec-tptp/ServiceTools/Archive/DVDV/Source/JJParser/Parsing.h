#ifndef PARSING_H
#define PARSING_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
#include "Tokenizer.h"
//-----------------------------------------------------------------------------
void IncreaseVariableUseCount(VARIABLENODE Variable,int HowMuch);

void PrintVariableList(VARIABLENODE Variables);
TERM NewTerm(void);
void FreeTerm(TERM * Term,VARIABLENODE * Variables);
TERM DuplicateTerm(TERM Original,ContextType Context,int ForceNewVariables);

FORMULA NewFormula(void);
void FreeFormula(FORMULA * Formula,VARIABLENODE * Variables);
FORMULAWITHVARIABLES NewFormulaWithVariables(void);
TERM ParseTerm(READFILE Stream,ContextType Context,VARIABLENODE * EndOfScope,
TermType Type,ConnectiveType Quantification,int * InfixNegatedAtom);
FORMULA ParseAtom(READFILE Stream,ContextType Context,VARIABLENODE * EndOfScope);
FORMULA ParseUnaryFormula(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope);
FORMULA DuplicateFormula(FORMULA Original,ContextType Context,
int ForceNewVariables);

void FreeFormulaWithVariables(FORMULAWITHVARIABLES * FormulaWithVariables);
FORMULAWITHVARIABLES DuplicateFormulaWithVariables(FORMULAWITHVARIABLES 
Original,SIGNATURE Signature,int ForceNewVariables);
FORMULA DuplicateInternalFormulaWithVariables(FORMULA Original,ContextType
OriginalContext);
FORMULAWITHVARIABLES ParseFormulaWithVariables(READFILE Stream,
SIGNATURE Signature);

//----Exported for use by main routine
ANNOTATEDFORMULA DuplicateAnnotatedFormula(ANNOTATEDFORMULA Original,
SIGNATURE Signature);
void FreeAnnotatedFormula(ANNOTATEDFORMULA * AnnotatedFormula);
ANNOTATEDFORMULA ParseAnnotatedFormula(READFILE Stream,SIGNATURE Signature);

LISTNODE NewListNode(ANNOTATEDFORMULA AnnotatedFormula);
void FreeListOfAnnotatedFormulae(LISTNODE * Head);
LISTNODE ParseFILEOfFormulae(FILE * FileStream,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter);
LISTNODE ParseFileOfFormulae(char * FileName,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter);
LISTNODE ParseStringOfFormulae(char * Content,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter);
TERM ParseStringTerm(char * Content,SIGNATURE Signature);
//-----------------------------------------------------------------------------
#endif

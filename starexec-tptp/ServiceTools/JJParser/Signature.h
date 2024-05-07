#ifndef SIGNATURE_H
#define SIGNATURE_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
//-------------------------------------------------------------------------------------------------
SIGNATURE NewSignature(void);
SIGNATURE NewSignatureWithTypes(void);
SIGNATURE DuplicateSignature(SIGNATURE Original);
void FreeSignature(SIGNATURE * Signature);
SYMBOLNODE RemoveSignatureNodeFromTree(SYMBOLNODE * OneToDeletePtr);
int RemovedUnusedSymbolsFromList(SYMBOLNODE * Symbols);
int RemovedUnusedSymbols(SIGNATURE Signature);
char * GetSignatureSymbol(SYMBOLNODE SymbolNode);
char * GetSignatureShortSymbol(SYMBOLNODE SymbolNode);
int GetSignatureArity(SYMBOLNODE SymbolNode);
void SetSignatureArity(SYMBOLNODE SymbolNode,int Arity);
int GetSignatureAppliedArity(SYMBOLNODE SymbolNode);
void SetSignatureAppliedArity(SYMBOLNODE SymbolNode,int Arity);
void IncreaseSymbolUseCount(SYMBOLNODE Symbol,int HowMuch);
int GetSignatureUses(SYMBOLNODE SymbolNode);
SYMBOLNODE IsSymbolInSignatureList(SYMBOLNODE List,char * Name,int Arity,READFILE Stream);
SYMBOLNODE * IsSymbolInSignatureListPointer(SYMBOLNODE * List,char * Name,int Arity,
READFILE Stream);
SYMBOLNODE InsertIntoSignatureList(SYMBOLNODE * List,char * Name,int Arity,int AppliedArity,
int InternalSymbol,READFILE Stream);
SYMBOLNODE InsertIntoSignature(SIGNATURE Signature,TermType Type,char * Name,int Arity,
int AppliedArity,int InternalSymbol,READFILE Stream);
SYMBOLNODE MoveSignatureNode(SYMBOLNODE * FromList,SYMBOLNODE * ToList,char * Name,int Arity,
READFILE Stream);
SYMBOLNODE NextInSignatureTree(SYMBOLNODE SignatureTree,SYMBOLNODE Current);
void ListSignatureBySearch(SYMBOLNODE SignatureTree);
void PrintSignatureTree(SYMBOLNODE SignatureTree);
void PrintSignature(SIGNATURE Signature);
char * GetSignatureSymbolUsage(SIGNATURE Signature,char ** PutUsageHere,
char ** FunctorUsageStartsHere);
void GetSignatureSymbolUsageStatistics(SYMBOLNODE SignatureNode,int * NumberOfSymbols,
int * NumberOfSymbolsArity0,int * NumberOfDefinedSymbols,int * MinSymbolArity,
int * MaxSymbolArity);
void GetSignatureTypeUsageStatistics(SYMBOLNODE SignatureNode,int * NumberOfTypes,
int * NumberOfUserTypes,int * NumberOfMathTypes);
//-------------------------------------------------------------------------------------------------
#endif

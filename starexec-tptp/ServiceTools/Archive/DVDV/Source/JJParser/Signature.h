#ifndef SIGNATURE_H
#define SIGNATURE_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
//-----------------------------------------------------------------------------
void FreeSignature(SIGNATURE * Signature);
SIGNATURE NewSignature(void);
char * GetSignatureSymbol(SYMBOLNODE SymbolNode);
int GetSignatureArity(SYMBOLNODE SymbolNode);
void IncreaseSymbolUseCount(SYMBOLNODE Symbol,int HowMuch);
SYMBOLNODE InsertIntoSignatureList(SYMBOLNODE * List,char * Name,int Arity);
SYMBOLNODE InsertIntoSignature(SIGNATURE Signature,TermType Type,
char * Name,int Arity);
void PrintSignature(SIGNATURE Signature);
//-----------------------------------------------------------------------------
#endif

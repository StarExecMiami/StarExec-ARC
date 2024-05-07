#ifndef PRINTSMT2_H
#define PRINTSMT2_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
//-------------------------------------------------------------------------------------------------
void SMT2PrintFormula(FILE * Stream,FORMULA Formula,int Indent,int AlreadyIndented,int Pretty);
void SMT2PrintHeader(FILE * Stream,LISTNODE Head,SIGNATURE Signature);
void SMT2PrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head);
//-------------------------------------------------------------------------------------------------
#endif
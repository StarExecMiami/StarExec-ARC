#ifndef PRINTKIF_H
#define PRINTKIF_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
//-------------------------------------------------------------------------------------------------
void KIFPrintFormula(FILE * Stream,FORMULA Formula,int Indent,
int AlreadyIndented,int Pretty);
void KIFPrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head);
//-------------------------------------------------------------------------------------------------
#endif


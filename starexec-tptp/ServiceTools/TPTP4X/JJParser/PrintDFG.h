#ifndef PRINTDFG_H
#define PRINTDFG_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
//-------------------------------------------------------------------------------------------------
void DFGPrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head);
void DFGPrintHeader(FILE * Stream,LISTNODE Head,SIGNATURE Signature);
void DFGPrintTailer(FILE * Stream);
//-------------------------------------------------------------------------------------------------
#endif


#ifndef PRINTOtter_H
#define PRINTOtter_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
//-------------------------------------------------------------------------------------------------
void OtterPrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head);
void OtterPrintHeader(FILE * Stream,LISTNODE Head,SIGNATURE Signature);
void OtterPrintTailer(FILE * Stream);
//-------------------------------------------------------------------------------------------------
#endif


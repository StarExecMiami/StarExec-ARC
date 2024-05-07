#ifndef LISTSTATISTICS_H
#define LISTSTATISTICS_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
#include "Statistics.h"
//-------------------------------------------------------------------------------------------------
int ListCount(SIGNATURE Signature,LISTNODE List,CountType WhatToCount);
int HeadListCount(SIGNATURE Signature,HEADLIST HeadListHead,CountType WhatToCount);
int ListMaximal(SIGNATURE Signature,LISTNODE List,MaximizeType WhatToMaximize);

//---- Broken SymbolStatisticsType GetListSymbolUsageStatistics(HEADLIST HeadList);
StatisticsType GetListStatistics(LISTNODE ListHead,SIGNATURE Signature);
void PrintListStatistics(FILE * Stream,StatisticsType Statistics);
//-------------------------------------------------------------------------------------------------
#endif

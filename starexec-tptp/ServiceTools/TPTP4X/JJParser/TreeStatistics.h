#ifndef TREESTATISTICS_H
#define TREESTATISTICS_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
#include "Statistics.h"

typedef struct {
    SZSOutputType Type;
    StatisticsType FormulaeStatistics;
    int ForestDepth;
    int ForestLeaves;
    int FiniteDomainSize;
} SolutionStatisticsType;
//-------------------------------------------------------------------------------------------------
SolutionStatisticsType GetSolutionStatistics(LISTNODE Head,SIGNATURE Signature,
ROOTLIST * RootListHead,SZSResultType ClaimedSZSResult,SZSOutputType ClaimedSZSOutput);
void PrintSolutionStatistics(FILE * Stream,SolutionStatisticsType Statistics);
//-------------------------------------------------------------------------------------------------
#endif

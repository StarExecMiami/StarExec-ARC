#ifndef TREESTATISTICS_H
#define TREESTATISTICS_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
#include "Statistics.h"

typedef struct {
    double NumberOfFormulae;
    double NumberOfFormulaeExpanded;
    double TreeDepth;
    double NumberOfAtoms; //----Doubles as NumberOfLiterals
    double NumberOfAtomsExpanded;  //----Doubles as NumberOfLiteralsExpanded

//----Not for pure CNF
    double MaxFormulaDepth;
    double AverageFormulaDepth;

//----Not for pure FOF
    double NumberOfClauses;
    double NumberOfClausesExpanded;
    double MaxClauseSize;
    double AverageClauseSize;

    double MaxTermDepth;
    double AverageTermDepth;
} TreeStatisticsRecordType;
//-----------------------------------------------------------------------------
TreeStatisticsRecordType * GetTreeStatistics(ROOTLIST RootListHead,
TreeStatisticsRecordType * Statistics);
void PrintTreeStatistics(FILE * Stream,TreeStatisticsRecordType Statistics);
//-----------------------------------------------------------------------------
#endif

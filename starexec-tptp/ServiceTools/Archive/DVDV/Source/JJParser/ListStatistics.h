#ifndef LISTSTATISTICS_H
#define LISTSTATISTICS_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
#include "Statistics.h"

typedef struct {
    double NumberOfFormulae;
    double NumberOfUnitFormulae;  //----Doubles as NumberOfUnitClauses;
    double NumberOfAtoms;  //----Doubles as NumberOfLiterals;
    double NumberOfEqualityAtoms;  //----Doubles as NumberOfEqualityLiterals

//----Not used for pure CNF
    double MaxFormulaDepth;
    double AverageFormulaDepth;
    double NumberOfConnectives;
    double NumberOfNegations;
    double NumberOfDisjunctions;
    double NumberOfConjunctions;
    double NumberOfEquivalences;
    double NumberOfImplications;
    double NumberOfReverseImplications;
    double NumberOfXORs;
    double NumberOfNORs;
    double NumberOfNANDs;
    double NumberOfUniversals;
    double NumberOfExistentials;

//----Not used for pure FOF
    double NumberOfClauses;
    double NumberOfHornClauses;
    double NumberOfRRClauses;
    double MaxClauseSize;
    double AverageClauseSize;

    double NumberOfPredicates;
    double NumberOfPropositions;
    double MinPredicateArity;
    double MaxPredicateArity;
    double NumberOfFunctors;
    double NumberOfConstants;
    double MinFunctorArity;
    double MaxFunctorArity;
    double NumberOfVariables;
    double NumberOfSingletons;
    double MaxTermDepth;
    double AverageTermDepth;
} ListStatisticsRecordType;
//-----------------------------------------------------------------------------
int ListCount(LISTNODE List,CountType WhatToCount);
int ListMaximal(LISTNODE List,MaximizeType WhatToMaximize);

ListStatisticsRecordType * GetListStatistics(LISTNODE ListHead,
ListStatisticsRecordType * Statistics);
void PrintListStatistics(FILE * Stream,ListStatisticsRecordType Statistics);
//-----------------------------------------------------------------------------
#endif

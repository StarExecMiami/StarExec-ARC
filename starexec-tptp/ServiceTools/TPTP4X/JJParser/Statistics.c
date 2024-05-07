#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "Statistics.h"
//-------------------------------------------------------------------------------------------------
void InitializeFormulaStatistics(FormulaStatisticsType * FormulaStatistics) {

    FormulaStatistics->NumberOfFormulae = 0;
    FormulaStatistics->NumberOfTHF = 0;
    FormulaStatistics->NumberOfTFF = 0;
    FormulaStatistics->NumberOfFOF = 0;
    FormulaStatistics->NumberOfCNF = 0;

    FormulaStatistics->NumberOfTypeFormulae = 0;
    FormulaStatistics->NumberOfDefnFormulae = 0;
    FormulaStatistics->NumberOfSequents = 0;
    FormulaStatistics->NumberOfUnitFormulae = 0;  
    FormulaStatistics->NumberOfAtoms = 0;
    FormulaStatistics->NumberOfEqualityAtoms = 0;
    FormulaStatistics->NumberOfConnectiveAtoms = 0;
    FormulaStatistics->NumberOfAppliedConnectives = 0;
    FormulaStatistics->NumberOfIndexedConnectives = 0;
    FormulaStatistics->NumberOfVariableAtoms = 0;
    FormulaStatistics->NumberOfNestedFormulae = 0;

    FormulaStatistics->MaxFormulaAtoms = 0;
    FormulaStatistics->AverageFormulaAtoms = 0;
    FormulaStatistics->MaxFormulaDepth = 0;
    FormulaStatistics->AverageFormulaDepth = 0;
    FormulaStatistics->MaxTermDepth = 0;
    FormulaStatistics->AverageTermDepth = 0;

    FormulaStatistics->NumberOfTuples = 0;
    FormulaStatistics->NumberOfITEs = 0;
    FormulaStatistics->NumberOfLets = 0;
    FormulaStatistics->NumberOfMathAtoms = 0;
    FormulaStatistics->NumberOfMathTerms = 0;
    FormulaStatistics->NumberOfNumbers = 0;

    FormulaStatistics->NumberOfHornClauses = 0;
    FormulaStatistics->NumberOfRRClauses = 0;
}
//-------------------------------------------------------------------------------------------------
void InitializeSymbolStatistics(SymbolStatisticsType * SymbolStatistics) {

    SymbolStatistics->NumberOfTypes = 0;
    SymbolStatistics->NumberOfUserTypes = 0;
    SymbolStatistics->NumberOfMathTypes = 0;
    SymbolStatistics->NumberOfPredicates = 0;
    SymbolStatistics->NumberOfPropositions = 0;
    SymbolStatistics->NumberOfUserPredicates = 0;
    SymbolStatistics->MinPredicateArity = 0;
    SymbolStatistics->MaxPredicateArity = 0;
    SymbolStatistics->NumberOfFunctors = 0;
    SymbolStatistics->NumberOfConstants = 0;
    SymbolStatistics->NumberOfUserFunctors = 0;
    SymbolStatistics->MinFunctorArity = 0;
    SymbolStatistics->MaxFunctorArity = 0;
    SymbolStatistics->NumberOfVariables = 0;
    SymbolStatistics->NumberOfSingletons = 0;
    SymbolStatistics->NumberOfBooleanVariables = 0;
}
//-------------------------------------------------------------------------------------------------
void InitializeConnectiveStatistics(ConnectiveStatisticsType * ConnectiveStatistics) {

	ConnectiveStatistics->NumberOfConnectives = 0;
    ConnectiveStatistics->NumberOfTypeConnectives = 0;

//----Only THF connectives
    ConnectiveStatistics->NumberOfPis = 0;
    ConnectiveStatistics->NumberOfSigmas = 0;
    ConnectiveStatistics->NumberOfChoices = 0;
    ConnectiveStatistics->NumberOfDescriptions = 0;
    ConnectiveStatistics->NumberOfApplications = 0;
    ConnectiveStatistics->NumberOfEqualitySymbols = 0;
    ConnectiveStatistics->NumberOfTypedEqualitySymbols = 0;
    ConnectiveStatistics->NumberOfTypeConnectives = 0;
    ConnectiveStatistics->NumberOfMaparrows = 0;
    ConnectiveStatistics->NumberOfXprods = 0;
    ConnectiveStatistics->NumberOfUnions = 0;
    ConnectiveStatistics->NumberOfLambdas = 0;

//----Only TFF
    ConnectiveStatistics->NumberOfSubtypes = 0;

//----Only NTF
    ConnectiveStatistics->NumberOfNTFConnectives = 0;

//----Not for CNF
    ConnectiveStatistics->NumberOfNegations = 0;
    ConnectiveStatistics->NumberOfDisjunctions = 0;
    ConnectiveStatistics->NumberOfConjunctions = 0;
    ConnectiveStatistics->NumberOfEquivalences = 0;
    ConnectiveStatistics->NumberOfImplications = 0;
    ConnectiveStatistics->NumberOfReverseImplications = 0;
    ConnectiveStatistics->NumberOfXors = 0;
    ConnectiveStatistics->NumberOfNors = 0;
    ConnectiveStatistics->NumberOfNands = 0;
    ConnectiveStatistics->NumberOfUniversals = 0;
    ConnectiveStatistics->NumberOfExistentials = 0;
    ConnectiveStatistics->NumberOfPiBinders = 0;
    ConnectiveStatistics->NumberOfSigmaBinders = 0;
    ConnectiveStatistics->NumberOfDescriptionBinders = 0;
    ConnectiveStatistics->NumberOfChoiceBinders = 0;

    ConnectiveStatistics->NumberOfTypedVariables = 0;
    ConnectiveStatistics->NumberOfMathVariables = 0;
    ConnectiveStatistics->NumberOfGlobalTypeDecs = 0;
    ConnectiveStatistics->NumberOfGlobalDefns = 0;
}
//-------------------------------------------------------------------------------------------------
void InitializeStatistics(StatisticsType * Statistics) {

    InitializeFormulaStatistics(&(Statistics->FormulaStatistics));
    InitializeSymbolStatistics(&(Statistics->SymbolStatistics));
    InitializeConnectiveStatistics(&(Statistics->ConnectiveStatistics));
}
//-------------------------------------------------------------------------------------------------
void AddOnConnectiveStatistics(ConnectiveStatisticsType * ConnectiveStatistics,
ConnectiveStatisticsType MoreConnectiveStatistics) {

    ConnectiveStatistics->NumberOfConnectives += MoreConnectiveStatistics.NumberOfConnectives;

    ConnectiveStatistics->NumberOfEqualitySymbols += 
MoreConnectiveStatistics.NumberOfEqualitySymbols;
    ConnectiveStatistics->NumberOfTypeConnectives += 
MoreConnectiveStatistics.NumberOfTypeConnectives;
    ConnectiveStatistics->NumberOfPis += MoreConnectiveStatistics.NumberOfPis;
    ConnectiveStatistics->NumberOfSigmas += MoreConnectiveStatistics.NumberOfSigmas;
    ConnectiveStatistics->NumberOfChoices += MoreConnectiveStatistics.NumberOfChoices;
    ConnectiveStatistics->NumberOfDescriptions += MoreConnectiveStatistics.NumberOfDescriptions;
    ConnectiveStatistics->NumberOfApplications += MoreConnectiveStatistics.NumberOfApplications;
    ConnectiveStatistics->NumberOfTypedEqualitySymbols += 
MoreConnectiveStatistics.NumberOfTypedEqualitySymbols;
    ConnectiveStatistics->NumberOfMaparrows += MoreConnectiveStatistics.NumberOfMaparrows;
    ConnectiveStatistics->NumberOfXprods += MoreConnectiveStatistics.NumberOfXprods;
    ConnectiveStatistics->NumberOfUnions += MoreConnectiveStatistics.NumberOfUnions;
    ConnectiveStatistics->NumberOfLambdas += MoreConnectiveStatistics.NumberOfLambdas;

//----Only TFF
    ConnectiveStatistics->NumberOfSubtypes += MoreConnectiveStatistics.NumberOfSubtypes;

//----Only NTF
    ConnectiveStatistics->NumberOfNTFConnectives += MoreConnectiveStatistics.NumberOfNTFConnectives;

//----Not for CNF
    ConnectiveStatistics->NumberOfNegations += MoreConnectiveStatistics.NumberOfNegations;
    ConnectiveStatistics->NumberOfDisjunctions += MoreConnectiveStatistics.NumberOfDisjunctions;
    ConnectiveStatistics->NumberOfConjunctions += MoreConnectiveStatistics.NumberOfConjunctions;
    ConnectiveStatistics->NumberOfEquivalences += MoreConnectiveStatistics.NumberOfEquivalences;
    ConnectiveStatistics->NumberOfImplications += MoreConnectiveStatistics.NumberOfImplications;
    ConnectiveStatistics->NumberOfReverseImplications += 
MoreConnectiveStatistics.NumberOfReverseImplications;
    ConnectiveStatistics->NumberOfXors += MoreConnectiveStatistics.NumberOfXors;
    ConnectiveStatistics->NumberOfNors += MoreConnectiveStatistics.NumberOfNors;
    ConnectiveStatistics->NumberOfNands += MoreConnectiveStatistics.NumberOfNands;
    ConnectiveStatistics->NumberOfUniversals += MoreConnectiveStatistics.NumberOfUniversals;
    ConnectiveStatistics->NumberOfExistentials += MoreConnectiveStatistics.NumberOfExistentials;
    ConnectiveStatistics->NumberOfPiBinders += MoreConnectiveStatistics.NumberOfPiBinders;
    ConnectiveStatistics->NumberOfSigmaBinders += MoreConnectiveStatistics.NumberOfSigmaBinders;
    ConnectiveStatistics->NumberOfDescriptionBinders +=
MoreConnectiveStatistics.NumberOfDescriptionBinders;
    ConnectiveStatistics->NumberOfChoiceBinders += MoreConnectiveStatistics.NumberOfChoiceBinders;

    ConnectiveStatistics->NumberOfTypedVariables += MoreConnectiveStatistics.NumberOfTypedVariables;
    ConnectiveStatistics->NumberOfMathVariables += MoreConnectiveStatistics.NumberOfMathVariables;
    ConnectiveStatistics->NumberOfGlobalTypeDecs += MoreConnectiveStatistics.NumberOfGlobalTypeDecs;
    ConnectiveStatistics->NumberOfGlobalDefns += MoreConnectiveStatistics.NumberOfGlobalDefns;
}
//-------------------------------------------------------------------------------------------------

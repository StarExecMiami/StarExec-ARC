#ifndef STATISTICS_H
#define STATISTICS_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"

typedef enum {
    nodes,
    thf_nodes,
    tff_nodes,
    tcf_nodes,
    fof_nodes,
    cnf_nodes,
    leaves,
//----For CNF problems
    horn_clauses,
    rr_clauses,

//----General
//----Whole annotated formulae
    unit_formulae,
    type_formulae,
    defn_formulae,
    sequent_formulae,
//----Within formulae
    atoms,
    equality_atoms,
    connective_atoms,      //----In THF, things like (&) 
    applied_connectives,   //----In NTF, things like {$box}
    indexed_connectives,   //----In NTF, applied_connectives with an index, like {$box(#agent)}
    variable_atoms,
    terms,
    variables,
    singletons,
    tuples,
    ite_forms,
    let_forms,
    math_atoms,
    math_terms,
    math_variables,
    numbers,
    nested_formulae, //----Not including boolean variables
    boolean_variables,
    formula_depth,
    term_depth,
    count_nothing
} CountType;

typedef enum {
    depth,
    literals,
    max_term_depth,
    max_formula_depth,
    maximize_nothing
} MaximizeType;

typedef struct {
    int NumberOfFormulae;
    int NumberOfTHF;
    int NumberOfTFF;
    int NumberOfTCF;
    int NumberOfFOF;
    int NumberOfCNF;

    int NumberOfTypeFormulae;
    int NumberOfDefnFormulae;
    int NumberOfSequents;
    int NumberOfUnitFormulae;  //----Doubles as NumberOfUnitClauses;
    int NumberOfAtoms;  //----Doubles as NumberOfLiterals;
    int NumberOfEqualityAtoms;  //----Doubles as NumberOfEqualityLiterals
    int NumberOfConnectiveAtoms;
    int NumberOfAppliedConnectives;
    int NumberOfIndexedConnectives;
    int NumberOfVariableAtoms;
    int NumberOfNestedFormulae;

    int MaxFormulaAtoms;
    double AverageFormulaAtoms;
    int MaxFormulaDepth;
    double AverageFormulaDepth;
    int MaxTermDepth;
    double AverageTermDepth;
    int NumberOfTuples;
    int NumberOfITEs;
    int NumberOfLets;
    int NumberOfMathAtoms;
    int NumberOfMathTerms;
    int NumberOfNumbers;

//----Only for CNF
    int NumberOfHornClauses;
    int NumberOfRRClauses;
} FormulaStatisticsType;

typedef struct {
    int NumberOfTypes;
    int NumberOfUserTypes;
    int NumberOfMathTypes;
    int NumberOfPredicates;  //----Doubles as number of symbols
    int NumberOfPropositions; 
    int NumberOfUserPredicates;
    int MinPredicateArity;
    int MaxPredicateArity;
    int NumberOfFunctors;
    int NumberOfConstants;
    int NumberOfUserFunctors;
    int MinFunctorArity;
    int MaxFunctorArity;
    int NumberOfVariables;
    int NumberOfSingletons;
    int NumberOfBooleanVariables;
} SymbolStatisticsType;

typedef struct {
    int NumberOfConnectives;
    int NumberOfTypeConnectives;

//----Only THF connectives
    int NumberOfPis;
    int NumberOfSigmas;
    int NumberOfChoices;
    int NumberOfDescriptions;
    int NumberOfApplications;
    int NumberOfMaparrows;
    int NumberOfXprods;
    int NumberOfUnions;
    int NumberOfEqualitySymbols;  //----Use of = as a term
    int NumberOfTypedEqualitySymbols;  //----Use of @= as a term

//----Only TFF
    int NumberOfSubtypes;

//----Only NTF
    int NumberOfNTFConnectives;

//----Not for CNF
    int NumberOfNegations;
    int NumberOfDisjunctions;
    int NumberOfConjunctions;
    int NumberOfEquivalences;
    int NumberOfImplications;
    int NumberOfReverseImplications;
    int NumberOfXors;
    int NumberOfNors;
    int NumberOfNands;

//----Variable binders
    int NumberOfUniversals;
    int NumberOfExistentials;
    int NumberOfLambdas;
    int NumberOfPiBinders;
    int NumberOfSigmaBinders;
    int NumberOfChoiceBinders;
    int NumberOfDescriptionBinders;

    int NumberOfTypedVariables;  //----Not a symbol, but counted by :s
    int NumberOfMathVariables;  //----Not a symbol, but counted by quantifications
    int NumberOfGlobalTypeDecs; //----Not a symbol, but counted by :s
    int NumberOfGlobalDefns; //----Not a symbol, but counted by :=s
} ConnectiveStatisticsType;

typedef struct {
    FormulaStatisticsType FormulaStatistics;
    SymbolStatisticsType SymbolStatistics;
    ConnectiveStatisticsType ConnectiveStatistics;
} StatisticsType;
//-------------------------------------------------------------------------------------------------
void InitializeStatistics(StatisticsType * Statistics);
void InitializeFormulaStatistics(FormulaStatisticsType * FormulaStatistics);
void InitializeSymbolStatistics(SymbolStatisticsType * SymbolStatistics);
void InitializeConnectiveStatistics(ConnectiveStatisticsType * ConnectiveStatistics);
void AddOnConnectiveStatistics(ConnectiveStatisticsType * ConnectiveStatistics,
ConnectiveStatisticsType MoreConnectiveStatistics);
//-------------------------------------------------------------------------------------------------
#endif

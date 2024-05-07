#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Examine.h"
#include "Parsing.h"
#include "Statistics.h"
#include "ListStatistics.h"
//-----------------------------------------------------------------------------
int ListCount(LISTNODE List,CountType WhatToCount) {

    int Counter;

    Counter = 0;
    while (List != NULL) {
//----Ignore comments
        if (CheckAnnotatedFormula(List->AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(List->AnnotatedFormula,tptp_cnf)) {
            switch (WhatToCount) {
                case nodes:
                    Counter += 1;
                    break;
                case fof_nodes:
                    if (GetSyntax(List->AnnotatedFormula) == tptp_fof) {
                        Counter += 1;
                    }
                    break;
                case cnf_nodes:
                    if (GetSyntax(List->AnnotatedFormula) == tptp_cnf) {
                        Counter += 1;
                    }
                    break;
                case count_horn_clauses:
                    if (NonHornClause(List->AnnotatedFormula)) {
                        Counter += 1;
                    }
                    break;
                case unit_formulae:
                    if (CountAnnotatedFormulaAtomsByPredicate(
List->AnnotatedFormula,"") == 1) {
                        Counter += 1;
                    }
                    break;
                case count_rr_clauses:
                    if (RangeRestrictedClause(List->AnnotatedFormula)) {
                        Counter += 1;
                    }
                    break;
                case atoms:
                    Counter += CountAnnotatedFormulaAtomsByPredicate(
List->AnnotatedFormula,"");
                    break;
                case equality_atoms:
                    Counter += CountAnnotatedFormulaAtomsByPredicate(
List->AnnotatedFormula,"$equal");
                    break;
                case terms:
                    Counter += CountAnnotatedFormulaTerms(List->
AnnotatedFormula);
                    break;
                case count_variables:
                    Counter += CountAnnotatedFormulaUniqueVariables(List->
AnnotatedFormula);
                    break;
                case count_singletons:
                    Counter += CountAnnotatedFormulaSingletons(List->
AnnotatedFormula);
                    break;
                case count_formula_depth:
                    Counter += AnnotatedFormulaDepth(List->AnnotatedFormula);
                    break;
                case count_term_depth:
                    Counter += SumAnnotatedFormulaTermDepth(List->
AnnotatedFormula);
                    break;
                default:
                    printf("ERROR: Don't know what to count in list\n");
                    return(-1);
                    break;
            }
        }
        List = List->Next;
    }
    
    return(Counter);
}
//-----------------------------------------------------------------------------
int HeadListCount(HEADLIST HeadListHead,CountType WhatToCount) {

    int Counter;

    Counter = 0;
    while (HeadListHead != NULL) {
        if (HeadListHead->TheList != NULL) {
            Counter += ListCount(HeadListHead->TheList,WhatToCount);
        }
        HeadListHead = HeadListHead->Next;
    }

    return(Counter);
}
//-----------------------------------------------------------------------------
int ListMaximal(LISTNODE List,MaximizeType WhatToMaximize) {

    int Maximal;

    Maximal = -1;
    while (List != NULL) {
//----Ignore comments
        if (CheckAnnotatedFormula(List->AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(List->AnnotatedFormula,tptp_cnf)) {
            switch (WhatToMaximize) {
                case literals:
                    Maximal = MaximumOfInt(Maximal,
CountAnnotatedFormulaAtomsByPredicate(List->AnnotatedFormula,""));
                    break;
                case term_depth:
                    Maximal = MaximumOfInt(Maximal,
MaxAnnotatedFormulaTermDepth(List->AnnotatedFormula));
                    break;
                case formula_depth:
                    Maximal = MaximumOfInt(Maximal,AnnotatedFormulaDepth(
List->AnnotatedFormula));
                    break;
                default:
                    printf("ERROR: Unknown thing to maximize in list\n");
                    return(-1);
                    break;
            }
        }
        List = List->Next;
    }

    return(Maximal);
}
//-----------------------------------------------------------------------------
int HeadListMaximal(HEADLIST HeadListHead,MaximizeType WhatToMaximize) {

    int Maximal;
    int NextMaximal;

    Maximal = 0;
    while (HeadListHead != NULL) {
        if (HeadListHead->TheList != NULL) {
            NextMaximal = ListMaximal(HeadListHead->TheList,WhatToMaximize);
        } else {
            NextMaximal = -1;
        }
        Maximal = MaximumOfInt(NextMaximal,Maximal);
        HeadListHead = HeadListHead->Next;
    }   
    
    return(Maximal);
}
//-----------------------------------------------------------------------------
void AnalyseSymbolList(char * SymbolList,double * NumberOfSymbols,
double * NumberOfArity0,double * MinArity,double * MaxArity) {

    char * SymbolRecord;
    char * RecordRestart;
    char * SymbolField;
    char * FieldRestart;
    int Arity;

    *NumberOfSymbols = 0;
    *NumberOfArity0 = 0;
    *MinArity = -1;
    *MaxArity = -1;

    SymbolRecord = strtok_r(SymbolList,"\n",&RecordRestart);
    while (SymbolRecord != NULL) {
        (*NumberOfSymbols)++;
        SymbolField = strtok_r(SymbolRecord,"/",&FieldRestart);
        SymbolField = strtok_r(NULL,"/",&FieldRestart);
        Arity = atoi(SymbolField);
        if (Arity == 0) {
            (*NumberOfArity0)++;
        }
        if (*MinArity == -1 || Arity < *MinArity) {
            *MinArity = Arity;
        }
        if (*MaxArity == -1 || Arity > *MaxArity) {
            *MaxArity = Arity;
        }
        SymbolRecord = strtok_r(NULL,"\n",&RecordRestart);
    }
}
//-----------------------------------------------------------------------------
void GetListSymbolUsageStatistics(HEADLIST HeadList,
double * NumberOfPredicates,double * NumberOfPropositions,
double * MinPredicateArity,double * MaxPredicateArity,
double * NumberOfFunctors,double * NumberOfConstants,
double * MinFunctorArity, double * MaxFunctorArity) {

    char * PredicateCollector;
    char * FunctorCollector;
    char * OneUsage;
    char * FunctorsStart;
    int PredicateCollectorLength = STRINGLENGTH;
    int FunctorCollectorLength = STRINGLENGTH;
    LISTNODE ListNode;

    PredicateCollector = (char *)Malloc(sizeof(String));
    strcpy(PredicateCollector,"");
    FunctorCollector = (char *)Malloc(sizeof(String));
    strcpy(FunctorCollector,"");

//----Go down list collecting
    while (HeadList != NULL) {
        ListNode = HeadList->TheList;
        OneUsage = (char *)Malloc(sizeof(String));
        strcpy(OneUsage,"");
        GetListOfAnnotatedFormulaSymbolUsage(ListNode,&OneUsage,&FunctorsStart);
        ExtendString(&FunctorCollector,FunctorsStart,&FunctorCollectorLength);
        *FunctorsStart = '\0';
        ExtendString(&PredicateCollector,OneUsage,&PredicateCollectorLength);
        Free((void **)&OneUsage);
        HeadList = HeadList->Next;
    }

    NormalizeSymbolUsage(FunctorCollector);
    NormalizeSymbolUsage(PredicateCollector);
    AnalyseSymbolList(FunctorCollector,NumberOfFunctors,NumberOfConstants,
MinFunctorArity,MaxFunctorArity);
    AnalyseSymbolList(PredicateCollector,NumberOfPredicates,
NumberOfPropositions,MinPredicateArity,MaxPredicateArity);

    Free((void **)&FunctorCollector);
    Free((void **)&PredicateCollector);
}
//-----------------------------------------------------------------------------
void GetListConnectiveUsageStatistics(HEADLIST HeadList,
double * NumberOfConnectives,double * NumberOfNegations,
double * NumberOfDisjunctions,double * NumberOfConjunctions,
double * NumberOfEquivalences,double * NumberOfImplications,
double * NumberOfReverseImplications,double * NumberOfXORs,
double * NumberOfNORs,double * NumberOfNANDs,double * NumberOfUniversals,
double * NumberOfExistentials) {

    LISTNODE ListNode;
    double NumberOfFormulaNegations;
    double NumberOfFormulaDisjunctions;
    double NumberOfFormulaConjunctions;
    double NumberOfFormulaEquivalences;
    double NumberOfFormulaImplications;
    double NumberOfFormulaReverseImplications;
    double NumberOfFormulaXORs;
    double NumberOfFormulaNORs;
    double NumberOfFormulaNANDs;
    double NumberOfFormulaUniversals;
    double NumberOfFormulaExistentials;

//----Initialize all counters
    *NumberOfConnectives = 0;
    *NumberOfNegations = 0;
    *NumberOfDisjunctions = 0;
    *NumberOfConjunctions = 0;
    *NumberOfEquivalences = 0;
    *NumberOfImplications = 0;
    *NumberOfReverseImplications = 0;
    *NumberOfXORs = 0;
    *NumberOfNORs = 0;
    *NumberOfNANDs = 0;
    *NumberOfUniversals = 0;
    *NumberOfExistentials = 0;

//----Go down list collecting
    while (HeadList != NULL) {
        ListNode = HeadList->TheList;
        while (ListNode != NULL) {
//----Ignore comments
            if (CheckAnnotatedFormula(ListNode->AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(ListNode->AnnotatedFormula,tptp_cnf)) {
                NumberOfFormulaNegations = 0;
                NumberOfFormulaDisjunctions = 0;
                NumberOfFormulaConjunctions = 0;
                NumberOfFormulaEquivalences = 0;
                NumberOfFormulaImplications = 0;
                NumberOfFormulaReverseImplications = 0;
                NumberOfFormulaXORs = 0;
                NumberOfFormulaNORs = 0;
                NumberOfFormulaNANDs = 0;
                NumberOfFormulaUniversals = 0;
                NumberOfFormulaExistentials = 0;
                GetFormulaConnectiveUsage(ListNode->AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
&NumberOfFormulaNegations,&NumberOfFormulaDisjunctions,
&NumberOfFormulaConjunctions,&NumberOfFormulaEquivalences,
&NumberOfFormulaImplications,&NumberOfFormulaReverseImplications,
&NumberOfFormulaXORs,&NumberOfFormulaNORs,&NumberOfFormulaNANDs,
&NumberOfFormulaUniversals,&NumberOfFormulaExistentials);
                *NumberOfConnectives += (NumberOfFormulaNegations +
NumberOfFormulaDisjunctions + NumberOfFormulaConjunctions + 
NumberOfFormulaEquivalences + NumberOfFormulaImplications +
NumberOfFormulaReverseImplications + NumberOfFormulaXORs +
NumberOfFormulaNORs + NumberOfFormulaNANDs);
                *NumberOfNegations += NumberOfFormulaNegations;
                *NumberOfDisjunctions += NumberOfFormulaDisjunctions;
                *NumberOfConjunctions += NumberOfFormulaConjunctions;
                *NumberOfEquivalences += NumberOfFormulaEquivalences;
                *NumberOfImplications += NumberOfFormulaImplications;
                *NumberOfReverseImplications += 
NumberOfFormulaReverseImplications;
                *NumberOfXORs += NumberOfFormulaXORs;
                *NumberOfNORs += NumberOfFormulaNORs;
                *NumberOfNANDs += NumberOfFormulaNANDs;
                *NumberOfUniversals += NumberOfFormulaUniversals;
                *NumberOfExistentials += NumberOfFormulaExistentials;
            }
            ListNode = ListNode->Next;
        }
        HeadList = HeadList->Next;
    }
}
//-----------------------------------------------------------------------------
ListStatisticsRecordType * GetListStatistics(LISTNODE ListHead,
ListStatisticsRecordType * Statistics) {

    HeadListType HeadListNode;
    double NumberOfTerms;

//----Make a single node for list of lists
    HeadListNode.TheList = ListHead;
    HeadListNode.Next = NULL;

    Statistics->NumberOfFormulae = HeadListCount(&HeadListNode,nodes);
    Statistics->NumberOfUnitFormulae = HeadListCount(&HeadListNode,
unit_formulae);
    Statistics->NumberOfAtoms = HeadListCount(&HeadListNode,atoms);
    Statistics->NumberOfEqualityAtoms = HeadListCount(&HeadListNode,
equality_atoms);

    Statistics->MaxFormulaDepth = HeadListMaximal(&HeadListNode,formula_depth);
    if (Statistics->NumberOfFormulae > 0) {
        Statistics->AverageFormulaDepth = HeadListCount(&HeadListNode,
count_formula_depth) / Statistics->NumberOfFormulae;
    } else {
        Statistics->AverageFormulaDepth = 0.0;
    }
    GetListConnectiveUsageStatistics(&HeadListNode,
&Statistics->NumberOfConnectives,
&Statistics->NumberOfNegations,&Statistics->NumberOfDisjunctions,
&Statistics->NumberOfConjunctions,&Statistics->NumberOfEquivalences,
&Statistics->NumberOfImplications,&Statistics->NumberOfReverseImplications,
&Statistics->NumberOfXORs,&Statistics->NumberOfNORs,&Statistics->NumberOfNANDs,
&Statistics->NumberOfUniversals,&Statistics->NumberOfExistentials);

    Statistics->NumberOfClauses = HeadListCount(&HeadListNode,cnf_nodes);
    Statistics->NumberOfHornClauses = HeadListCount(&HeadListNode,
count_horn_clauses);
    Statistics->NumberOfRRClauses = HeadListCount(&HeadListNode,
count_rr_clauses);
    Statistics->MaxClauseSize = HeadListMaximal(&HeadListNode,literals);
    if (Statistics->NumberOfAtoms > 0) {
        Statistics->AverageClauseSize = Statistics->NumberOfAtoms /
Statistics->NumberOfClauses;
    } else {
        Statistics->AverageClauseSize = 0.0;
    }

    GetListSymbolUsageStatistics(&HeadListNode,&Statistics->NumberOfPredicates,
&Statistics->NumberOfPropositions,&Statistics->MinPredicateArity,
&Statistics->MaxPredicateArity,&Statistics->NumberOfFunctors,
&Statistics->NumberOfConstants,&Statistics->MinFunctorArity,
&Statistics->MaxFunctorArity);
    Statistics->NumberOfVariables = HeadListCount(&HeadListNode,
count_variables);
    Statistics->NumberOfSingletons = HeadListCount(&HeadListNode,
count_singletons);
    Statistics->MaxTermDepth = HeadListMaximal(&HeadListNode,term_depth);
    if ((NumberOfTerms = HeadListCount(&HeadListNode,terms)) > 0) {
        Statistics->AverageTermDepth = HeadListCount(&HeadListNode,
count_term_depth) / NumberOfTerms;
    } else {
        Statistics->AverageTermDepth = 0.0;
    }

    return(Statistics);
}
//-----------------------------------------------------------------------------
void PrintMinMaxArity(FILE * Stream,double Arity) {

    if (Arity == -1) {
        fprintf(Stream,"-");
    } else {
        fprintf(Stream,"%.0f",Arity);
    }
}
//-----------------------------------------------------------------------------
void PrintListStatistics(FILE * Stream,ListStatisticsRecordType Statistics) {

    if (Statistics.NumberOfFormulae > Statistics.NumberOfClauses) {
        fprintf(Stream,
"%% Syntax   : Number of formulae    : %4.0f (%4.0f unit)\n",
Statistics.NumberOfFormulae,Statistics.NumberOfUnitFormulae);
    }

    if (Statistics.NumberOfClauses > 0) {
        if (Statistics.NumberOfFormulae > Statistics.NumberOfClauses) {
            fprintf(Stream,"%%            ");
        } else {
            fprintf(Stream,"%% Syntax   : ");
        }
        fprintf(Stream,
"Number of clauses     : %4.0f (%4.0f non-Horn;%4.0f unit;%4.0f RR)\n",
Statistics.NumberOfClauses,Statistics.NumberOfHornClauses,
Statistics.NumberOfUnitFormulae,Statistics.NumberOfRRClauses);
    }

    fprintf(Stream,
"%%            Number of atoms       : %4.0f (%4.0f equality)\n",
Statistics.NumberOfAtoms,Statistics.NumberOfEqualityAtoms);

    if (Statistics.NumberOfFormulae > Statistics.NumberOfClauses) {
        fprintf(Stream,
"%%            Maximal formula depth : %4.0f (%4.0f average)\n",
Statistics.MaxFormulaDepth,Statistics.AverageFormulaDepth);
    }
    if (Statistics.NumberOfClauses > 0) {
        fprintf(Stream,
"%%            Maximal clause size   : %4.0f (%4.0f average)\n",
Statistics.MaxClauseSize,Statistics.AverageClauseSize);
    }

    if (Statistics.NumberOfFormulae > Statistics.NumberOfClauses) {
        fprintf(Stream,
"%%            Number of connectives : %4.0f (%4.0f ~  ;%4.0f  |;%4.0f  &)\n",
Statistics.NumberOfConnectives,Statistics.NumberOfNegations,
Statistics.NumberOfDisjunctions,Statistics.NumberOfConjunctions);
        fprintf(Stream,
"%%                                         (%4.0f <=>;%4.0f =>;%4.0f <=)\n",
Statistics.NumberOfEquivalences,Statistics.NumberOfImplications,
Statistics.NumberOfReverseImplications);
        fprintf(Stream,
"%%                                         (%4.0f <~>;%4.0f ~|;%4.0f ~&)\n",
Statistics.NumberOfXORs,Statistics.NumberOfNORs,Statistics.NumberOfNANDs);
    }

//----Symbols
    fprintf(Stream,
"%%            Number of predicates  : %4.0f (%4.0f propositional; ",
Statistics.NumberOfPredicates,Statistics.NumberOfPropositions);
    PrintMinMaxArity(Stream,Statistics.MinPredicateArity);
    fprintf(Stream,"-");
    PrintMinMaxArity(Stream,Statistics.MaxPredicateArity);
    fprintf(Stream," arity)\n");
    fprintf(Stream,
"%%            Number of functors    : %4.0f (%4.0f constant; ",
Statistics.NumberOfFunctors,Statistics.NumberOfConstants);
    PrintMinMaxArity(Stream,Statistics.MinFunctorArity),
    fprintf(Stream,"-");
    PrintMinMaxArity(Stream,Statistics.MaxFunctorArity);
    fprintf(Stream," arity)\n");

//----Variables
    fprintf(Stream,
"%%            Number of variables   : %4.0f (%4.0f singleton",
Statistics.NumberOfVariables,Statistics.NumberOfSingletons);

    if (Statistics.NumberOfFormulae > Statistics.NumberOfClauses) {
        fprintf(Stream,";%4.0f !;%4.0f ?)\n",
Statistics.NumberOfUniversals,Statistics.NumberOfExistentials);
    } else {
        fprintf(Stream,")\n");
    }

//----Terms
    fprintf(Stream,
"%%            Maximal term depth    : %4.0f (%4.0f average)\n",
Statistics.MaxTermDepth,Statistics.AverageTermDepth); 
}
//-----------------------------------------------------------------------------

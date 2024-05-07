#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Examine.h"
#include "Parsing.h"
#include "Tree.h"
#include "TreeStatistics.h"
//-----------------------------------------------------------------------------
double TreeCount(TREENODE Tree,CountType WhatToCount,int Expand) {

    double Counter;
    int Index;

    if (!Tree->Visited) {
        switch (WhatToCount) {
            case nodes:
                Counter = 1;
                break;
            case fof_nodes:
                if (GetSyntax(Tree->AnnotatedFormula) == tptp_fof) {
                    Counter = 1;
                } else {
                    Counter = 0;
                }
                break;
            case cnf_nodes:
                if (GetSyntax(Tree->AnnotatedFormula) == tptp_cnf) {
                    Counter = 1;
                } else {
                    Counter = 0;
                }
                break;
            case atoms:
                Counter = CountAnnotatedFormulaAtomsByPredicate(Tree->
AnnotatedFormula,"");
                break;
            case terms:
                Counter = CountAnnotatedFormulaTerms(Tree->AnnotatedFormula);
                break;
            case count_formula_depth:
                Counter = AnnotatedFormulaDepth(Tree->AnnotatedFormula);
                break;
            case count_term_depth:
                Counter = SumAnnotatedFormulaTermDepth(Tree->AnnotatedFormula);
                break;
            default:
                printf("ERROR: Don't know what to count in tree\n");
                return(-1);
                break;
        }
    
        for (Index = 0; Index < Tree->NumberOfParents; Index++) {
            Counter += TreeCount(Tree->Parents[Index],WhatToCount,Expand);
        }
//----Save value for future visits
        Tree->StatisticsCache = Counter;
        Tree->Visited = 1;

    } else {
        if (Expand) {
            Counter = Tree->StatisticsCache;
        } else {
            Counter = 0;
        }
    }

    return(Counter);
}
//-----------------------------------------------------------------------------
double RootListCount(ROOTLIST RootListHead,CountType WhatToCount,int Expand) {

    double Counter;

    Counter = 0;
    ResetRootListVisited(RootListHead);
    while (RootListHead != NULL) {
        if (RootListHead->TheTree != NULL) {
            Counter += TreeCount(RootListHead->TheTree,WhatToCount,Expand);
        }
        RootListHead = RootListHead->Next;
    }

    return(Counter);
}
//-----------------------------------------------------------------------------
double TreeMaximal(TREENODE Tree,MaximizeType WhatToMaximize) {

    double Maximal;
    int Index;
    double NextMaximal;

//----Check if known value. his relies on never having a value of 0.
    if (!Tree->Visited) {
        switch (WhatToMaximize) {
            case depth:
                Maximal = 0;
                break;
            case literals:
                Maximal = CountAnnotatedFormulaAtomsByPredicate(
Tree->AnnotatedFormula,"");
                break;
            case term_depth:
                Maximal = MaxAnnotatedFormulaTermDepth(Tree->AnnotatedFormula);
                break;
            case formula_depth:
                Maximal = AnnotatedFormulaDepth(Tree->AnnotatedFormula);
                break;
            default:
                printf("ERROR: Unknown thing to maximize in tree\n");
                return(-1);
                break;
        }

        for (Index = 0; Index < Tree->NumberOfParents; Index++) {
            NextMaximal = TreeMaximal(Tree->Parents[Index],WhatToMaximize);
            Maximal = MaximumOfDouble(NextMaximal,Maximal);
        }
        switch (WhatToMaximize) {
            case depth:
//----Only count depth if there are some parents
                if (Tree->NumberOfParents > 0) {
                    Maximal++;
                }
                break;
            case literals:
                break;
            case term_depth:
                break;
            case formula_depth:
                break;
            default:
                printf("ERROR: Unknown thing to maximize in tree\n");
                return(-1);
                break;
        }
        Tree->StatisticsCache = Maximal;
        Tree->Visited = 1;
    } else {
        Maximal = Tree->StatisticsCache;
    }

    return(Maximal);
}
//-----------------------------------------------------------------------------
double RootListMaximal(ROOTLIST RootListHead,MaximizeType WhatToMaximize) {

    double Maximal;
    double NextMaximal;

    Maximal = 0;
    ResetRootListVisited(RootListHead);
    while (RootListHead != NULL) {
        if (RootListHead->TheTree != NULL) {
            NextMaximal = TreeMaximal(RootListHead->TheTree,WhatToMaximize);
        } else {
            NextMaximal = -1;
        }
        Maximal = MaximumOfDouble(NextMaximal,Maximal);
        RootListHead = RootListHead->Next;
    }   
    
    return(Maximal);
}
//-----------------------------------------------------------------------------
int TreeHasCycle(TREENODE Root) {

    int Index;

//----A real tree out there? (1 = black)
    if (Root->Visited == 1) {
        return(0);
    } 
//----Been here before? (-1 = grey)
    if (Root->Visited == -1) {
        return(1);
    }
//----Try all children
    Root->Visited = -1;
    for (Index = 0; Index < Root->NumberOfParents; Index++) {
        if (TreeHasCycle(Root->Parents[Index])) {
            return(1);
        }
    }
    Root->Visited = 1;
    return(0);
}
//-----------------------------------------------------------------------------
int RootListHasCycle(ROOTLIST RootListHead) {

    ResetRootListVisited(RootListHead);
    while (RootListHead != NULL) {
        if (TreeHasCycle(RootListHead->TheTree)) {
            return(1);
        }
        RootListHead = RootListHead->Next;
    }
    return(0);
}
//-----------------------------------------------------------------------------
TreeStatisticsRecordType * GetTreeStatistics(ROOTLIST RootListHead,
TreeStatisticsRecordType * Statistics) {

    if (RootListHasCycle(RootListHead)) {
        printf("ERROR: Cycle in a tree\n");
        return(NULL);
    }

    Statistics->NumberOfFormulae = RootListCount(RootListHead,nodes,0);
    Statistics->NumberOfFormulaeExpanded = RootListCount(RootListHead,nodes,1);
    Statistics->TreeDepth = RootListMaximal(RootListHead,depth);
    Statistics->NumberOfAtoms = RootListCount(RootListHead,atoms,0);
    Statistics->NumberOfAtomsExpanded = RootListCount(RootListHead,atoms,1);
    Statistics->MaxFormulaDepth = RootListMaximal(RootListHead,formula_depth);
    Statistics->AverageFormulaDepth = RootListCount(RootListHead,
count_formula_depth,0) / Statistics->NumberOfFormulae;

    Statistics->NumberOfClauses = RootListCount(RootListHead,cnf_nodes,0);
    if (Statistics->NumberOfClauses > 0) {
        Statistics->NumberOfClausesExpanded = RootListCount(RootListHead,
cnf_nodes,1);
        Statistics->MaxClauseSize = RootListMaximal(RootListHead,literals);
        Statistics->AverageClauseSize = Statistics->NumberOfAtoms /
Statistics->NumberOfClauses;
    }

    Statistics->MaxTermDepth = RootListMaximal(RootListHead,term_depth);
    Statistics->AverageTermDepth = RootListCount(RootListHead,
count_term_depth,0) / RootListCount(RootListHead,terms,0);

    return(Statistics);
}
//-----------------------------------------------------------------------------
void PrintTreeStatistics(FILE * Stream,TreeStatisticsRecordType Statistics) {

    if (Statistics.NumberOfFormulae > Statistics.NumberOfClauses) {
        fprintf(Stream,
"%% Statistics : Number of formulae    : %4.0f (%4.0f expanded)\n",
Statistics.NumberOfFormulae,Statistics.NumberOfFormulaeExpanded);
    }
    if (Statistics.NumberOfClauses > 0) {
        if (Statistics.NumberOfFormulae > Statistics.NumberOfClauses) {
            fprintf(Stream,"%%              ");
        } else {
            fprintf(Stream,"%% Statistics : ");
        }
        fprintf(Stream,
"Number of clauses     : %4.0f (%4.0f expanded)\n",
Statistics.NumberOfClauses,Statistics.NumberOfClausesExpanded);
    }

    fprintf(Stream,
"%%              Depth                 : %4.0f\n",Statistics.TreeDepth);
    fprintf(Stream,
"%%              Number of atoms       : %4.0f (%4.0f expanded)\n",
Statistics.NumberOfAtoms,Statistics.NumberOfAtomsExpanded);
    if (Statistics.NumberOfClauses > 0) {
        fprintf(Stream,
"%%              Maximal clause size   : %4.0f (%4.0f average)\n",
Statistics.MaxClauseSize,Statistics.AverageClauseSize);
    }

    if (Statistics.NumberOfFormulae > Statistics.NumberOfClauses) {
        fprintf(Stream,
"%%              Maximal formula depth : %4.0f (%4.0f average)\n",
Statistics.MaxFormulaDepth,Statistics.AverageFormulaDepth);
    }

    fprintf(Stream,
"%%              Maximal term depth    : %4.0f (%4.0f average)\n",
Statistics.MaxTermDepth,Statistics.AverageTermDepth);
}
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "List.h"
#include "Tree.h"
#include "Statistics.h"
#include "TreeStatistics.h"
#include "ListStatistics.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
void XCPUHandler(int TheSignal) {

    printf("ERROR: MakeListStats ran out of CPU time\n");
    exit(EXIT_FAILURE);

}
//-----------------------------------------------------------------------------
void SetTimeLimit(int TimeLimit) {

    struct rlimit ResourceLimits;

//----Limit the memory. Need to get old one for hard limit field
    if (getrlimit(RLIMIT_CPU,&ResourceLimits) == -1) {
        perror("TimeLimitedRun - Getting resource limit:");
        exit(-1);
    }
//----Set new CPU limit in ms (sent in secs)
    ResourceLimits.rlim_cur = TimeLimit; //---- -1 because its weird
    if (setrlimit(RLIMIT_CPU,&ResourceLimits) == -1) {
        printf("ERROR: MakeTreeStats cannot set time limit\n");
        exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    LISTNODE Head;
    SIGNATURE Signature;
    StatisticsType Statistics;
    int ArgOffset;
    int ExpandIncludes;
    long TimeLimit;

    ArgOffset = 0;

    if (argc > ArgOffset+2 && !strcmp(argv[ArgOffset+1],"-t")) {
        TimeLimit = atoi(argv[ArgOffset+2]);
        ArgOffset += 2;
    } else {
        TimeLimit = RLIM_INFINITY;
    }

    if (argc > ArgOffset+1 && !strcmp(argv[ArgOffset+1],"-i")) {
        ArgOffset += 1;
        ExpandIncludes = 0;
    } else {
        ExpandIncludes = 1;
    }

    if (argc <= ArgOffset+1) {
        printf("Usage: MakeListStats [-t <time limit>] [-i] <TPTP file name>\n");
        return(0);
    }

    SetTimeLimit(TimeLimit);
    if (signal(SIGXCPU,XCPUHandler) == SIG_ERR) {
        printf("ERROR: MakeListStats cannot set XCPU handler\n");
        exit(EXIT_FAILURE);
    }

    Signature = NewSignatureWithTypes();
    SetNeedForNonLogicTokens(0);
    // SetAllowFreeVariables(1);
//DEBUG printf("PROGRESS: about to read\n");
    if ((Head = ParseFileOfFormulae(argv[ArgOffset+1],NULL,Signature,ExpandIncludes,NULL)) != 
NULL) {
        RemoveAnnotatedFormulaWithRole(&Head,Signature,logic);
        RemovedUnusedSymbols(Signature);
//DEBUG printf("PROGRESS: read complete\n");
        Statistics = GetListStatistics(Head,Signature);
//DEBUG printf("PROGRESS: statistics complete\n");
        PrintListStatistics(stdout,Statistics);
//DEBUG printf("PROGRESS: printing complete\n");
        FreeListOfAnnotatedFormulae(&Head,Signature);
        assert(Head == NULL);
        FreeSignature(&Signature);
    } else {
        printf("%% Syntax   : WARNING: No formulae parsed from %s\n",argv[1]);
    }

    return(0);
}
//-----------------------------------------------------------------------------

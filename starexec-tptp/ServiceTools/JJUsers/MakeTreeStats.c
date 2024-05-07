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
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
void XCPUHandler(int TheSignal) {

    printf("ERROR: MakeTreeStats ran out of CPU time\n");
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

    int ArgOffset;
    long TimeLimit;
    LISTNODE Head;
    SIGNATURE Signature;
    ROOTLIST RootListHead;
    SolutionStatisticsType Statistics;
    SZSResultType SZSResult;
    SZSOutputType SZSOutput;

    ArgOffset = 0;

    if (argc > ArgOffset+2 && !strcmp(argv[ArgOffset+1],"-t")) {
        TimeLimit = atoi(argv[ArgOffset+2]);
        ArgOffset += 2;
    } else {
        TimeLimit = RLIM_INFINITY;
    }

    if (argc <= ArgOffset+1) {
        printf("Usage: MakeTreeStats [-t <time limit>] <TSTP file name>\n");
        return(0);
    }

    SetTimeLimit(TimeLimit);
    if (signal(SIGXCPU,XCPUHandler) == SIG_ERR) {
        printf("ERROR: MakeTreeStats cannot set XCPU handler\n");
        exit(EXIT_FAILURE);
    }

    ParseFileForSZSResults(argv[ArgOffset+1],&SZSResult,&SZSOutput);
//DEBUG printf("The file claims SZS status %s and SZS output %s\n",SZSResultToUserString(SZSResult),SZSOutputToUserString(SZSOutput));
    Signature = NewSignatureWithTypes();
    SetNeedForNonLogicTokens(0);
    SetAllowFreeVariables(1);
    if ((Head = ParseFileOfFormulae(argv[ArgOffset+1],NULL,Signature,1,NULL)) != NULL) {
        RemovedUnusedSymbols(Signature);
        Statistics = GetSolutionStatistics(Head,Signature,&RootListHead,SZSResult,SZSOutput);
//DEBUG printf("Try print root list\n");
//DEBUG PrintRootList(stdout,RootListHead);
//DEBUG PrintSolutionStatistics(stdout,Statistics);
        if (Statistics.Type != Non && Statistics.Type != nonszsoutput) {
            PrintSolutionStatistics(stdout,Statistics);
        } else {
            printf("ERROR: MakeTreeStats fails\n");
        }
        FreeRootList(&RootListHead,1,Signature);
        assert(RootListHead == NULL);
    } else {
        printf("ERROR: Parsing solution fails\n");
    }
    FreeListOfAnnotatedFormulae(&Head,Signature);
    FreeSignature(&Signature);
    assert(Head == NULL);

    return(0);
}
//-----------------------------------------------------------------------------

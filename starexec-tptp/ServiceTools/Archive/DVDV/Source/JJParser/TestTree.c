#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "Tree.h"
#include "TreeStatistics.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    LISTNODE Head;
    SIGNATURE Signature;
    ROOTLIST RootListHead;
    char * PutNamesHere;
    TreeStatisticsRecordType Statistics;
    ANNOTATEDFORMULA AnnotatedFormula;

    PutNamesHere = (char *)Malloc(sizeof(String));
    Signature = NewSignature();
    SetNeedForNonLogicTokens(0);
    Head = ParseFileOfFormulae(argv[1],Signature,1,NULL);
//    PrintListOfAnnotatedTSTPNodes(stdout,Head,tptp);
    GetAllNames(Head,&PutNamesHere);
    printf("All names are \n%s\n",PutNamesHere);
    GetRootNames(Head,&PutNamesHere);
    printf("Root names are %s\n",PutNamesHere);
//DEBUG printf("about to build root list\n");
    RootListHead = BuildRootList(Head);
//DEBUG printf("built root list\n");
    PrintRootList(stdout,RootListHead);

    if (GetTreeStatistics(RootListHead,&Statistics) != NULL) {
//DEBUG printf("got stats\n");
        PrintTreeStatistics(stdout,Statistics);
    }
    exit(EXIT_SUCCESS);

    if ((AnnotatedFormula = GetAnnotatedFormulaFromRootListByName(RootListHead,
"2")) != NULL) {
        printf("Found number 94\n");
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    } else {
        printf("Did not find number 94\n");
    }
    PrintRootList(stdout,RootListHead);

    FreeListOfAnnotatedFormulae(&Head);
    assert(Head == NULL);
    FreeRootList(&RootListHead);

    return(0);
}
//-----------------------------------------------------------------------------

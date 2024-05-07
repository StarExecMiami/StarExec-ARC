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
#include "List.h"
#include "TreeStatistics.h"
#include "PrintTSTP.h"
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    LISTNODE Head,LeafListHead;
    SIGNATURE Signature;
    ROOTLIST RootListHead;
    TreeStatisticsRecordType Statistics;

    Signature = NewSignature();
    SetNeedForNonLogicTokens(0);
    Head = ParseFileOfFormulae(argv[1],NULL,Signature,1,NULL);

//    PrintListOfAnnotatedTSTPNodes(stdout,Signature,Head,tptp,1);

printf("about to build root list\n");
    RootListHead = BuildRootList(Head);
printf("built root list\n");
    PrintRootList(stdout,RootListHead);

//----Test output in postorder
    PrintRootListAnnotatedNodesInPostOrder(stdout,RootListHead);

//----Test extraction of leaves
    printf("---- Leaves ignoring duplicates ----\n");
    LeafListHead = GetLeafList(RootListHead,1);
    PrintListOfAnnotatedTSTPNodes(stdout,Signature,LeafListHead,tptp,1);
    printf("---- Leaves not ignoring duplicates ----\n");
    LeafListHead = GetLeafList(RootListHead,0);
    PrintListOfAnnotatedTSTPNodes(stdout,Signature,LeafListHead,tptp,1);

    if (GetTreeStatistics(RootListHead,&Statistics) != NULL) {
//DEBUG printf("got stats\n");
        PrintTreeStatistics(stdout,Statistics);
    }

    FreeRootList(&RootListHead,1);
    FreeListOfAnnotatedFormulae(&Head);
    FreeSignature(&Signature);
    assert(Head == NULL);

    return(0);
}
//-------------------------------------------------------------------------------------------------

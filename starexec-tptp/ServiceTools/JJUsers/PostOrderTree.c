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
#include "TreeStatistics.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    LISTNODE Head;
    SIGNATURE Signature;
    ROOTLIST RootListHead;

    Signature = NewSignature();
    SetNeedForNonLogicTokens(0);
    if ((Head = ParseFileOfFormulae(argv[1],NULL,Signature,1,NULL)) == NULL) {
        printf("ERROR: Could not read derivation formulae\n");
        exit(EXIT_FAILURE);
    }
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,Head,tptp,1);
    if ((RootListHead = BuildRootList(Head)) == NULL) {
        printf("ERROR: Could not build derivation tree\n");
        exit(EXIT_FAILURE);
    }
//DEBUG PrintRootList(stdout,RootListHead);
    PrintRootListAnnotatedNodesInPostOrder(stdout,RootListHead);
    FreeListOfAnnotatedFormulae(&Head);
    assert(Head == NULL);
    FreeRootList(&RootListHead,1);

    return(0);
}
//-----------------------------------------------------------------------------

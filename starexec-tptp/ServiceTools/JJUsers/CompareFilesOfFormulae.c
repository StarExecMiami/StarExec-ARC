#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "Compare.h"
#include "Modify.h"
#include "List.h"
#include "Tree.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    SIGNATURE Signature;
    LISTNODE Head1 = NULL;
    LISTNODE Head2 = NULL;
    LISTNODE Combined = NULL;
    int ArgOffset;
    int Negate[] = {0,0};

//----One signature for all testing
    Signature = NewSignature();

//----Read from file or stdin or command line
    SetNeedForNonLogicTokens(0);
    ArgOffset = 0;
//----Negate first or second formula
    while (argc >= ArgOffset+2 && strstr(argv[ArgOffset+1],"-n") == 
argv[ArgOffset+1]) {
        if (strlen(argv[ArgOffset+1]) == 3) {
            Negate[argv[ArgOffset+1][2]-'1'] = 1;
        } else {
            printf("ERROR: Illegal -n flag %s\n",argv[ArgOffset+1]);
            exit(EXIT_FAILURE);
        }
        ArgOffset++;
    }
//DEBUG printf("Negate 1st and 2nd = %d %d\n",Negate[0],Negate[1]);
    if (argc >= ArgOffset+4 && !strcmp(argv[ArgOffset+1],"-f")) {
        Head1 = ParseStringOfFormulae(argv[ArgOffset+2],Signature,1,NULL);
        Head2 = ParseStringOfFormulae(argv[ArgOffset+3],Signature,1,NULL);
    } else if (argc >= ArgOffset+3) {
        Head1 = ParseFileOfFormulae(argv[ArgOffset+1],NULL,Signature,1,NULL);
        Head2 = ParseFileOfFormulae(argv[ArgOffset+2],NULL,Signature,1,NULL);
    } else {
        printf("ERROR: Usage: %s -nN <file> <file>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

//----Negate lists as requested
    if (Negate[0]) {
        if (!NegateListOfAnnotatedTSTPNodes(Head1,1)) {
            printf("ERROR: Could not negate first list\n");
            exit(EXIT_FAILURE);
        }
    }
    if (Negate[1]) {
        if (!NegateListOfAnnotatedTSTPNodes(Head2,1)) {
            printf("ERROR: Could not negate first list\n");
            exit(EXIT_FAILURE);
        }
    }

//----Get the two lists into a merged list. This makes the nodes of duplicate
//----annotated formulae in Head2 point to the annotated nodes from Head1.
//DEBUG printf("----------Head1\n");
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,Head1,tptp,1);
//DEBUG printf("----------Head2\n");
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,Head2,tptp,1);
    Combined = DuplicateListOfNodes(Head1,0);
    Combined = MergeInListOfAnnotatedFormulaeByFields(&Combined,&Head2,0,0,2);

//----Compare them
    switch (SetRelationshipListOfAnnotatedFormulae(Head1,Head2,1)) {
        case 0:
            printf("}{\n");  //----Disjoint
            break;
        case 1:
            printf("{}\n");  //----Intersecting
            break;
        case 2:
            printf(">>\n");  //----Superset
            break;
        case 3:
            printf("==\n");  //----Equal
            break;
        case 4:
            printf("<<\n");  //----Subset
            break;
        default:
            CodingError("Non-existent set relationship");
            break;
    }

//----Free Willie!
    FreeListOfAnnotatedFormulae(&Head1);
    FreeListOfAnnotatedFormulae(&Head2);
    FreeListOfAnnotatedFormulae(&Combined);
    FreeSignature(&Signature);
    return(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------

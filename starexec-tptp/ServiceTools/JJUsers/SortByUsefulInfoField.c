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
    LISTNODE Head = NULL;
    int InvertOrder;

//----One signature for all testing
    Signature = NewSignature();

//----Check output form flag
    if (argc < 3) {
        printf("Usage: %s <field name> <field type> <file name>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

//----Check sort options
    InvertOrder = argv[2][0] == '-';
    if ((InvertOrder && strlen(argv[2]) < 2) || strlen(argv[2]) < 1 ||
(argv[2][InvertOrder] != 's' && argv[2][InvertOrder] != 'd' && argv[2][InvertOrder] != 'f')) {
        printf("Usage: %s <field name> <field type> <file name>\n",argv[0]);
        printf("    <field type> %c is invalid, must be [-]s or [-]d or [-]f\n",
argv[2][0]);
        exit(EXIT_FAILURE);
    }

//----Read from file or stdin
    SetNeedForNonLogicTokens(0);
    if (argc > 3) {
        Head = ParseFileOfFormulae(argv[3],NULL,Signature,1,NULL);
    } else {
        Head = ParseFILEOfFormulae(stdin,Signature,1,NULL);
    }

//----Sort
    SortByUsefulInfoField(&Head,argv[1],argv[2][InvertOrder],InvertOrder);
    PrintListOfAnnotatedTSTPNodes(stdout,Signature,Head,tptp,1);

//----Free Willie!
    FreeListOfAnnotatedFormulae(&Head);
    FreeSignature(&Signature);
    return(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------

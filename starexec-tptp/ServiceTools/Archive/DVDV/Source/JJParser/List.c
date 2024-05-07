#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Examine.h"
#include "List.h"
//-----------------------------------------------------------------------------
LISTNODE * GetNodeFromListByNumber(LISTNODE * Head,int Number) {

    do {
//----Skip non-formula records
        while ((*Head) != NULL && 
(*Head)->AnnotatedFormula->Syntax != tptp_fof &&
(*Head)->AnnotatedFormula->Syntax != tptp_cnf) {
            Head = &((*Head)->Next);
        }
//----Is it the one we want?
        if ((*Head) != NULL) {
            if(Number == 1) {
                return(Head);
            } else {
//----If not, move on
                Head = &((*Head)->Next);
                Number--;
            }
        }
    } while ((*Head) != NULL);

    return(NULL);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA GetAnnotatedFormulaFromListByNumber(LISTNODE Head,int Number) {

    LISTNODE * NodePointer;

    if ((NodePointer = GetNodeFromListByNumber(&Head,Number)) !=
NULL) {
        assert((*NodePointer) != NULL);
        return((*NodePointer)->AnnotatedFormula);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
//----The first parameter is a pointer to the pointer to the node in the real 
//----data structure, so that the function can return a pointer to the real
//----pointer in the data structure. This would not be possible if a pointer 
//----to the node were received, as then it would be in a local variable and
//----not be anything in the data structure.
LISTNODE * GetNodeFromListByAnnotatedFormulaName(LISTNODE * Head,
char * Name) {

    String FormulaName;

    do {
//----Skip non-formula records
        while ((*Head) != NULL && 
(*Head)->AnnotatedFormula->Syntax != tptp_fof &&
(*Head)->AnnotatedFormula->Syntax != tptp_cnf) {
            Head = &((*Head)->Next);
        }
//----Is it the one we want?
        if ((*Head) != NULL) {
            if (!strcmp(GetName((*Head)->AnnotatedFormula,FormulaName),Name)) {
                return(Head);
            } else {
//----If not, move on
                Head = &((*Head)->Next);
            }
        }
    } while ((*Head) != NULL);

    return(NULL);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA GetAnnotatedFormulaFromListByName(LISTNODE Head, char * Name) {

    LISTNODE * NodePointer;

    if ((NodePointer = GetNodeFromListByAnnotatedFormulaName(&Head,Name)) !=
NULL) {
        assert((*NodePointer) != NULL);
        return((*NodePointer)->AnnotatedFormula);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------

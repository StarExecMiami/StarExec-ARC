#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Examine.h"
#include "List.h"
#include "PrintTSTP.h"
#include "tptp4X.h"
//-------------------------------------------------------------------------------------------------
void RandomizeFormulaeBelowIncludes(LISTNODE * Head) {

    LISTNODE * FirstLogical;

    FirstLogical = Head;
    while (*FirstLogical != NULL &&
!LogicalAnnotatedFormula((*FirstLogical)->AnnotatedFormula)) {
        FirstLogical = &((*FirstLogical)->Next);
    }
    
    RandomizeListOfAnnotatedFormulae(FirstLogical,1);
}
//-------------------------------------------------------------------------------------------------
void RandomizeCommutativeFormulae(LISTNODE * Head) {

    LISTNODE * Target;
    LISTNODE Randomized;
    LISTNODE * AddHere;

    Randomized = NULL;
    AddHere = &Randomized;
//----Move all includes to front
    Target = Head;
    while (*Target != NULL) {
        if (
(*Target)->AnnotatedFormula->Syntax == include ||
( LogicalAnnotatedFormulaWithRole((*Target)->AnnotatedFormula,type) ||
  LogicalAnnotatedFormulaWithRole((*Target)->AnnotatedFormula,definition))) {
            *AddHere = *Target;
            *Target = (*Target)->Next;
            (*AddHere)->Next = NULL;
            AddHere = &((*AddHere)->Next);
        } else {
            Target = &((*Target)->Next);
        }
    }

//----Randomize the rest
    RandomizeListOfAnnotatedFormulae(Head,1);
    *AddHere = *Head;
    *Head = Randomized;
}
//-------------------------------------------------------------------------------------------------

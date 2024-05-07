#ifndef LIST_H
#define LIST_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
//-----------------------------------------------------------------------------
LISTNODE * GetNodeFromListByNumber(LISTNODE * Head,int Number);
ANNOTATEDFORMULA GetAnnotatedFormulaFromListByNumber(LISTNODE Head,int Number);
LISTNODE * GetNodeFromListByAnnotatedFormulaName(LISTNODE * Head,
char * Name);
ANNOTATEDFORMULA GetAnnotatedFormulaFromListByName(LISTNODE Head, char * Name);
//-----------------------------------------------------------------------------
#endif

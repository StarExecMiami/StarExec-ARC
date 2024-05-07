/*-----------------------------------------------------------------------------
 * FILE: dvdvSplit.c
 * AUTHOR: Diego Belfiore
 *
 * The functions in this file are used for model checking of split clauses.
 * No structural checks are performed here.
 *---------------------------------------------------------------------------*/
#include "dvdv.h"

//-----------------------------------------------------------------------------
SplitType 
GetSplitType(ANNOTATEDFORMULA anfBuffer) 
{
  String 
    parentNames,
    previousName
    ;
  char *currentName;
  short nameCount;

  /*--------------------------------------------------------------
   * Split type depends on the number of parents a split node has.
   * They are recognized in the following form:
   * [ (False Clause), (Parent), (Antikid Sibling) ]
   * The return type is based on the number of parents it has.
   *--------------------------------------------------------------*/  

  currentName = NULL;
  strcpy(previousName, "");
  GetParentNames(anfBuffer, parentNames);
  currentName = strtok(parentNames, "\n");
  nameCount = 0;
  while(currentName != NULL) {
    if (strcmp(previousName, currentName) != 0) 
      nameCount++;
    strcpy(previousName, currentName);
    currentName = strtok(NULL, "\n");
  }
  if (nameCount == 1)
    return LeftChild;
  else if (nameCount == 2)
    return RightChild;
  else if (nameCount == 3)
    return AntiKid;
  else
    return Undefined;
}
//-----------------------------------------------------------------------------
SPLITPARENTLIST 
GetSplitParentList(ANNOTATEDFORMULA anfBuffer, SplitType type) 
{
  SPLITPARENTLIST list;
  String 
    parentNames,
    previousName
    ;
  char *currentName;

  if (anfBuffer == NULL || type == Undefined)
    return NULL;

  list = NewSplitParentList();
  currentName = NULL;
  strcpy(previousName, "");
  GetParentNames(anfBuffer, parentNames);

  /*------------------------------------------------
   * Parent list must be parsed carefully in order
   * to avoid listing duplicate entries as a 
   * component of the parent list.
   *----------------------------------------------*/

  currentName = strtok(parentNames, "\n");
  if (type == LeftChild) {
    strcpy(list->Parent, currentName);
  }
  else {
    strcpy(list->FalseClause, currentName);
  }
  if (type == RightChild || type == AntiKid) {
    strcpy(previousName, currentName);
    while(strcmp(previousName, currentName) == 0 && currentName != NULL) {
      strcpy(previousName, currentName);
      currentName = strtok(NULL, "\n");
    }
    strcpy(list->Parent, currentName);
  }
  if (type == AntiKid) {
    strcpy(previousName, currentName);
    while(strcmp(previousName, currentName) == 0 && currentName != NULL) {
      strcpy(previousName, currentName);
      currentName = strtok(NULL, "\n");
    }
    strcpy(list->AntiKidOf, currentName);
  }

  return list;
}
//-----------------------------------------------------------------------------


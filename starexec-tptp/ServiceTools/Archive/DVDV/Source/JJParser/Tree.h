#ifndef TREE_H
#define TREE_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
//-----------------------------------------------------------------------------
void ResetRootListVisited(ROOTLIST RootListHead);
char * GetAllNames(LISTNODE Head,char ** Names);
char * GetRootNames(LISTNODE Head,char ** Names);
ROOTLIST BuildRootList(LISTNODE Head);
void FreeRootList(ROOTLIST * Head);

void DFS(FILE * Stream,TREENODE Root);
void PrintRootList(FILE * Stream,ROOTLIST RootList);

TREENODE * GetNodeFromTreeByAnnotatedFormulaName(TREENODE * Root,char * Name);
ANNOTATEDFORMULA GetAnnotatedFormulaFromTreeByName(TREENODE Root,char * Name);
TREENODE * GetNodeFromRootListByAnnotatedFormulaName(ROOTLIST RootListHead,
char * Name);
ANNOTATEDFORMULA GetAnnotatedFormulaFromRootListByName(ROOTLIST Head,
char * Name);
//-----------------------------------------------------------------------------
#endif

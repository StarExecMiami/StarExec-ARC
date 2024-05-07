#ifndef TREE_H
#define TREE_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
//-------------------------------------------------------------------------------------------------
void SetUserData(TREENODE TreeNode,void * UserData);
void * GetUserData(TREENODE TreeNode);

void ResetTreeVisited(TREENODE Tree);
void ResetRootListVisited(ROOTLIST RootListHead);
LISTNODE GetListWithAxiomAncestorLeaves(ROOTLIST RootListHead,int IgnoreDuplicates);
LISTNODE GetSyntaxLeafList(ROOTLIST RootListHead,int IgnoreDuplicates,SyntaxType Syntax);
void GetRootLeafList(TREENODE Root,LISTNODE * LeafListHead,int IgnoreDuplicates);
LISTNODE GetLeafList(ROOTLIST RootListHead,int IgnoreDuplicates);
int GetRootLemmaList(TREENODE Root,LISTNODE * LeafListHead,int NoDuplicates);
ROOTLIST GetFalseNodes(ROOTLIST RootListHead,LISTNODE Head);
ROOTLIST GetFalseRootList(ROOTLIST RootListHead);
TREENODE GetFalseRootNode(ROOTLIST RootListHead);
LISTNODE GetRootList(LISTNODE Head,SIGNATURE Signature);
void AddRootNode(ROOTLIST * From,ROOTLIST Next,TREENODE TheTree);
ROOTLIST BuildRootList(LISTNODE Head,SIGNATURE Signature);
void FreeRootList(ROOTLIST * Head,int MustFreeTree,SIGNATURE Signature);

TREENODE AnnotatedFormulaInTrees(ROOTLIST RootListHead,ANNOTATEDFORMULA LookingForThis);

void DFS(FILE * Stream,TREENODE Root);
void PrintRootList(FILE * Stream,ROOTLIST RootList);
void PrintRootListAnnotatedNodesInPostOrder(FILE * Stream,ROOTLIST RootListHead);
void ListTreeAnnotatedNodesInPostOrder(TREENODE TreeRoot,LISTNODE * AddNextHere);
LISTNODE ListRootListAnnotatedNodesInPostOrder(ROOTLIST RootListHead);

ROOTBTREE * GetNodeFromRootBTreeByAnnotatedFormulaName(ROOTBTREE * Root,char * Name);
ROOTBTREE AddRootBTreeNode(ROOTBTREE * Root,TREENODE TreeNode);
void FreeRootBTree(ROOTBTREE * Root,int MustFreeTree,SIGNATURE Signature);
void PrintRootBTreeOfAnnotatedFormulae(ROOTBTREE Root);
//-------------------------------------------------------------------------------------------------
#endif

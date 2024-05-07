#ifndef LIST_H
#define LIST_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
//-------------------------------------------------------------------------------------------------
void ResetListVisited(LISTNODE Head);
int ListLength(LISTNODE Head);
LISTNODE GetLogicNode(LISTNODE Head);
LISTNODE NewListNode(ANNOTATEDFORMULA AnnotatedFormula);
void AddListNode(LISTNODE * From,LISTNODE Next,ANNOTATEDFORMULA AnnotatedFormulae);
LISTNODE DuplicateListOfNodes(LISTNODE Head,int KeepNonLogicNodes);
LISTNODE DuplicateListOfAnnotatedFormulae(LISTNODE Head,SIGNATURE Signature);
void FreeAListNode(LISTNODE * ToDelete,SIGNATURE Signature);
void FreeListOfAnnotatedFormulae(LISTNODE * Head,SIGNATURE Signature);
LISTNODE AppendListsOfAnnotatedTSTPNodes(LISTNODE List1,LISTNODE List2);
LISTNODE * GetLastNext(LISTNODE * Head);

char * GetAllNames(LISTNODE Head,char ** Names);
int UniquelyNamed(LISTNODE Head);
LISTNODE * GetNodeFromListByNumber(LISTNODE * Head,int Number);
ANNOTATEDFORMULA GetAnnotatedFormulaFromListByNumber(LISTNODE Head,int Number);
LISTNODE * GetNodeFromListByAnnotatedFormulaName(LISTNODE * Head,char * Name);
ANNOTATEDFORMULA GetAnnotatedFormulaFromListByName(LISTNODE Head, char * Name);
int GetNodesForNames(LISTNODE Head,StringParts ParentNames,int NumberOfParents,
LISTNODE * ParentList,SIGNATURE Signature);
LISTNODE * GetNodeFromListByAnnotatedFormula(LISTNODE * Head,ANNOTATEDFORMULA AnnotatedFormula);

void RemoveAnnotatedFormulaWithRole(LISTNODE * Head,SIGNATURE Signature,StatusType Role);
LISTNODE SelectListOfAnnotatedFormulaeWithRole(LISTNODE * Head,StatusType DesiredStatus,
int DeletedSelected,SIGNATURE Signature);
LISTNODE GetListOfAnnotatedFormulaeWithRole(LISTNODE Head,StatusType DesiredStatus,
SIGNATURE Signature);
LISTNODE GetListWithSyntaxType(LISTNODE Head,SyntaxType DesiredSyntax);
LISTNODE SelectListOfAnnotatedFormulaeWithParents(LISTNODE * Head,int DeletedSelected,
SIGNATURE Signature);

int SetRelationshipListOfAnnotatedFormulae(LISTNODE Set1,LISTNODE Set2,int AllowCommutation);
LISTNODE MergeInListOfAnnotatedFormulaeByFields(LISTNODE * MainList,LISTNODE * MergeList,
int SameName,int SameRole,int SameFormula,SIGNATURE Signature);

LISTNODE SlowSortByUsefulInfoField(LISTNODE * Head,char * FieldName,char DataType,int InvertOrder);
LISTNODE SortByUsefulInfoField(LISTNODE * Head,char * FieldName,char DataType,int InvertOrder);
void RandomizeAnnotatedFormulaeInList(LISTNODE Head,unsigned int Seed);
void RandomizeListOrder(LISTNODE * Head,unsigned int Seed);
void RandomizeListOfAnnotatedFormulae(LISTNODE * Head,unsigned int Seed);

void ResetBTreeVisited(BTREENODE Root);
BTREENODE * GetNodeFromBTreeByAnnotatedFormulaName(BTREENODE * Root,char * Name);
BTREENODE AddBTreeNode(BTREENODE * Root,ANNOTATEDFORMULA AnnotatedFormula);
BTREENODE ListToBTree(LISTNODE Head);
void FreeBTreeOfAnnotatedFormulae(BTREENODE * Root,SIGNATURE Signature);
void PrintBTreeOfAnnotatedFormulae(BTREENODE Root);
int BTreeDepth(BTREENODE Root);
//-------------------------------------------------------------------------------------------------
#endif

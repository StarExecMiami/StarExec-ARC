#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Examine.h"
#include "Parsing.h"
#include "List.h"
#include "Tree.h"
//-----------------------------------------------------------------------------
void ResetTreeVisited(TREENODE Tree) {

    int Index;

    if (Tree != NULL && Tree->Visited) {
        Tree->Visited = 0;
        for (Index = 0; Index < Tree->NumberOfParents; Index++) {
            ResetTreeVisited(Tree->Parents[Index]);
        }
    }
}
//-----------------------------------------------------------------------------
void ResetRootListVisited(ROOTLIST RootListHead) {

    while (RootListHead != NULL) {
        if (RootListHead->TheTree != NULL) {
            ResetTreeVisited(RootListHead->TheTree);
        }
        RootListHead = RootListHead->Next;
    }
}
//-----------------------------------------------------------------------------
LISTNODE GetLogicNode(LISTNODE Head) {

    while (Head != NULL && Head->AnnotatedFormula->Syntax != tptp_fof &&
Head->AnnotatedFormula->Syntax != tptp_cnf) {
        Head = Head->Next;
    }

    return(Head);
}
//-----------------------------------------------------------------------------
//----Second must be address of malloced String so it can be realloced 
//----if necessary
char * GetAllNames(LISTNODE Head,char ** Names) {

    String Name;
    int NamesMax = STRINGLENGTH;

    strcpy(*Names,"");
    while ((Head = GetLogicNode(Head)) != NULL) {
        GetName(Head->AnnotatedFormula,Name);
        strcat(Name,"\n");
        ExtendString(Names,Name,&NamesMax);
        Head = Head->Next;
    }

    return(*Names);
}
//-----------------------------------------------------------------------------
//----Second must be address of a malloced String so it can be realloced 
//----if necessary
char * GetRootNames(LISTNODE Head,char ** Names) {

    String ParentNames;
    String NameCR;
    char * ParentName;
    char * ParentInAllNames;

    GetAllNames(Head,Names);
    while ((Head = GetLogicNode(Head)) != NULL) {
        GetParentNames(Head->AnnotatedFormula,ParentNames);
        ParentName = strtok(ParentNames,"\n");
        while (ParentName != NULL) {
            strcpy(NameCR,ParentName);
            strcat(NameCR,"\n");
            if ((ParentInAllNames = strstr(*Names,NameCR)) != NULL &&
(ParentInAllNames == *Names || ParentInAllNames[-1] == '\n')) {
                strcpy(ParentInAllNames,strchr(ParentInAllNames,'\n')+1);
            }
            ParentName = strtok(NULL,"\n");
        }
        Head = Head->Next;
    }

    return(*Names);
}
//-----------------------------------------------------------------------------
ROOTLIST NewRootList(void) {

    ROOTLIST RootList;

    RootList = (ROOTLIST)Malloc(sizeof(RootListType));
    RootList->TheTree = NULL;
    RootList->Next = NULL;

    return(RootList);
}
//-----------------------------------------------------------------------------
TREENODE NewTreeNode(void) {

    TREENODE TreeNode;

    TreeNode = (TREENODE)Malloc(sizeof(TreeNodeType));
    TreeNode->NumberOfUses = 0;
    TreeNode->AnnotatedFormula = NULL;
    TreeNode->NumberOfParents = 0;
    TreeNode->Parents = NULL;
    TreeNode->Visited = 0;
    TreeNode->StatisticsCache = 0;
    return(TreeNode);
}
//-----------------------------------------------------------------------------
TREENODE * NewParentsList(int NumberOfParents) {

    TREENODE * ParentsList;
    int Index;

    ParentsList = (TREENODE *)Malloc(NumberOfParents * sizeof(TREENODE));
    for (Index = 0; Index < NumberOfParents; Index++) {
        ParentsList[Index] = NULL;
    }

    return(ParentsList);
}
//-----------------------------------------------------------------------------
void FreeTree(TREENODE * Tree) {

    int Index;

    if (*Tree != NULL) {
//----If no more uses then free it up
        if (--((*Tree)->NumberOfUses) == 0) {
//----Recursively do parents first
            if ((*Tree)->NumberOfParents > 0) {
                for (Index = 0; Index < (*Tree)->NumberOfParents; Index++) {
                    FreeTree(&((*Tree)->Parents[Index]));
                }
                Free((void **)&((*Tree)->Parents));
            }
            FreeAnnotatedFormula(&((*Tree)->AnnotatedFormula));
            Free((void **)Tree);
        }
    }
}
//-----------------------------------------------------------------------------
void FreeRootList(ROOTLIST * Head) {

    if (*Head != NULL) {
//----Recursively do rest first
        if ((*Head)->Next != NULL) {
            FreeRootList(&((*Head)->Next));
        }
        FreeTree(&((*Head)->TheTree));
        Free((void **)Head);
    }
}
//-----------------------------------------------------------------------------
TREENODE InTree(TREENODE ATree,char * RootName) {

    String TreeNodeName;
    int ParentIndex;
    TREENODE AncestorNode;

    if (ATree != NULL) {
//----Is this the one?
        if (!strcmp(RootName,GetName(ATree->AnnotatedFormula,TreeNodeName))) {
            return(ATree);
        } else {
//----Look in subtrees
            for (ParentIndex = 0; ParentIndex < ATree->NumberOfParents;
ParentIndex++) {
                if ((AncestorNode = InTree(ATree->Parents[ParentIndex],
RootName)) != NULL) {
                    return(AncestorNode);
                }
            }
        }
    } 

    return(NULL);
}
//-----------------------------------------------------------------------------
TREENODE InTrees(ROOTLIST RootListHead,char * RootName) {

    TREENODE TreeNode;

    while (RootListHead != NULL) {
        if ((TreeNode = InTree(RootListHead->TheTree,RootName)) != NULL) {
            return(TreeNode);
        } else {
            RootListHead = RootListHead->Next;
        }
    }
    return(NULL);
}
//-----------------------------------------------------------------------------
int CountParents(char * ParentNames) {

    int NumberOfParents;
    int Index;

    NumberOfParents = 0;
    for (Index = 0; Index < (int)strlen(ParentNames); Index++) {
        if (ParentNames[Index]  == '\n') {
            NumberOfParents++;
        }
    }

    return(NumberOfParents);
}
//-----------------------------------------------------------------------------
TREENODE InAllTreeNodes(ROOTLIST Head,String RootName) {

    String TreeNodeName;

    while (Head != NULL) {
        if (Head->TheTree != NULL &&
!strcmp(RootName,GetName(Head->TheTree->AnnotatedFormula,TreeNodeName))) {
            return(Head->TheTree);
        }
        Head = Head->Next;
    }

    return(NULL);
}
//-----------------------------------------------------------------------------
int RemoveTheoryParents(char * ParentNames) {

    int NumberOfTheoryParents;
    char * TheoryParent;
    char * EndOfTheoryParent;

    NumberOfTheoryParents = 0;
    while ((TheoryParent = strstr(ParentNames,"theory(")) != NULL) {
        NumberOfTheoryParents++;
        if ((EndOfTheoryParent = strchr(TheoryParent,'\n')) == NULL) {
            CodingError("Broken parent name list in RemoveTheoryParents\n");
        }
        strcpy(TheoryParent,EndOfTheoryParent+1);
    }
    return(NumberOfTheoryParents);
}
//-----------------------------------------------------------------------------
//----Using a reference parameter rather than returning so that the linking
//----is done immediately to allow search what we have done already
TREENODE BuildTree(LISTNODE Head,ROOTLIST RootListHead,char * RootName,
TREENODE * TheTree,ROOTLIST * AllTreeNodes) {

    LISTNODE * PointerToListNode;
    ROOTLIST LinearNode;
    String ParentNames;
    int ParentIndex;
    char * ParentName;
    char * NextParentName;
    StatusType SubStatus;

//DEBUG printf("Building tree for root %s \n",RootName);
    if (((*TheTree) = InAllTreeNodes(*AllTreeNodes,RootName)) != NULL) {
        (*TheTree)->NumberOfUses++;
    } else {
//----Find node in list of nodes
        if ((PointerToListNode = GetNodeFromListByAnnotatedFormulaName(&Head,
RootName)) == NULL) {
            printf("ERROR: Could not find %s in list of nodes\n",RootName);
            return(NULL);
        }

//DEBUG printf("making the tree node for %s\n",RootName);
//----Make new tree node
        (*TheTree) = NewTreeNode();
        (*TheTree)->NumberOfUses = 1;
        (*TheTree)->AnnotatedFormula = (*PointerToListNode)->AnnotatedFormula;
        (*TheTree)->AnnotatedFormula->NumberOfUses++;

//----Add to linear list
        LinearNode = NewRootList();
        LinearNode->TheTree = *TheTree;
        LinearNode->Next = *AllTreeNodes;
        *AllTreeNodes = LinearNode;
        
//----Do parents if derived
        if (GetStatus((*TheTree)->AnnotatedFormula,&SubStatus) == derived ||
SubStatus == derived) {
            GetParentNames((*TheTree)->AnnotatedFormula,ParentNames);
//DEBUG printf("All parents are %s\n",ParentNames);
            RemoveTheoryParents(ParentNames);
//DEBUG printf("Non-theory parents are %s\n",ParentNames);
            if (((*TheTree)->NumberOfParents = CountParents(ParentNames)) == 
0) {
//DEBUG printf("There are no parents\n");
                (*TheTree)->Parents = NULL;
            } else {
//DEBUG printf("Parents are %s\n",ParentNames);
                (*TheTree)->Parents = NewParentsList((*TheTree)->NumberOfParents);
                ParentIndex = 0;
                ParentName = strtok_r(ParentNames,"\n",&NextParentName);
                while (ParentName != NULL) {
                    if (BuildTree(Head,RootListHead,ParentName,
&((*TheTree)->Parents[ParentIndex]),AllTreeNodes) == NULL) {
//DEBUG printf("ERROR: Could not build parent trees for %s\n",RootName);
                        FreeTree(TheTree);
                        return(NULL);
                    }
                    ParentName = strtok_r(NULL,"\n",&NextParentName);
                    ParentIndex++;
                }
                assert(ParentIndex == (*TheTree)->NumberOfParents);
            }
        } else {
            (*TheTree)->NumberOfParents = 0;
            (*TheTree)->Parents = NULL;
        }
    }
    return(*TheTree);
}
//-----------------------------------------------------------------------------
ROOTLIST BuildRootList(LISTNODE Head) {

    ROOTLIST RootListHead;
    ROOTLIST * NextRootList;
    ROOTLIST AllTreeNodes;
    ROOTLIST LinearNode;
    char * RootNames;
    char * RootName;
    char * NextRootName;

    AllTreeNodes = NULL;
    RootListHead = NULL;
    NextRootList = &RootListHead;
    RootNames = (char *)Malloc(sizeof(String));
    GetRootNames(Head,&RootNames);
    RootName = strtok_r(RootNames,"\n",&NextRootName);
    while (RootName != NULL) {
        *NextRootList = NewRootList();
        if (BuildTree(Head,RootListHead,RootName,&((*NextRootList)->TheTree),
&AllTreeNodes) == NULL) {
            printf("ERROR: Could not build tree for root %s\n",RootName);
            FreeRootList(&RootListHead);
            RootName = NULL;
        } else {
            NextRootList = &((*NextRootList)->Next);
            RootName = strtok_r(NULL,"\n",&NextRootName);
        }
    }
    Free((void **)&RootNames);

//----Free linear list
    while (AllTreeNodes != NULL) {
        LinearNode = AllTreeNodes;
        AllTreeNodes = AllTreeNodes->Next;
        Free((void **)&LinearNode);
    }

    return(RootListHead);
}
//-----------------------------------------------------------------------------
void DFSWithIndent(FILE * Stream,TREENODE Root,char * Indent) {

    String Name;
    String NewIndent;
    int Index;

    fprintf(Stream,"%s%s (%d uses, %d visited)\n",Indent,
GetName(Root->AnnotatedFormula,Name),Root->NumberOfUses,Root->Visited);
    strcpy(NewIndent,Indent);
    strcat(NewIndent,"  ");
    if (Root->Parents != NULL) {
        for (Index=0;Index < Root->NumberOfParents; Index++) {
            DFSWithIndent(Stream,Root->Parents[Index],NewIndent);
        }
    }

}
//-----------------------------------------------------------------------------
void DFS(FILE * Stream,TREENODE Root) {

    DFSWithIndent(Stream,Root,"");

}
//-----------------------------------------------------------------------------
void PrintRootList(FILE * Stream,ROOTLIST RootListHead) {

    while (RootListHead != NULL) {
        if (RootListHead->TheTree == NULL) {
            fprintf(Stream,"Empty tree\n");
        } else {
           DFS(Stream,RootListHead->TheTree);
        }
        RootListHead = RootListHead->Next;
    }
}
//-----------------------------------------------------------------------------
TREENODE * GetNodeFromTreeByAnnotatedFormulaName(TREENODE * Root,char * Name) {

    int ParentIndex;
    TREENODE * FoundNode;

//----Check things are OK
    if (*Root == NULL || 
(!CheckAnnotatedFormula((*Root)->AnnotatedFormula,tptp_fof) && 
!CheckAnnotatedFormula((*Root)->AnnotatedFormula,tptp_cnf))) {
        CodingError("Searching a broken tree\n");
    }

//----If already been here, then no
    if ((*Root)->Visited) {
        return(NULL);
    }

//----Is it this one?
    if (!strcmp((*Root)->AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name,Name)) {
        return(Root);
    } 

//----Look at each parent
    (*Root)->Visited = 1;
    for (ParentIndex = 0;ParentIndex < (*Root)->NumberOfParents;
ParentIndex++) {
        if ((FoundNode = GetNodeFromTreeByAnnotatedFormulaName(
&((*Root)->Parents[ParentIndex]),Name)) != NULL) {
            return(FoundNode);
        }
    }

//----Otherwise not found
    return(NULL);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA GetAnnotatedFormulaFromTreeByName(TREENODE Root,char * Name) {

    TREENODE * NodePointer;
    
    ResetTreeVisited(Root);

    if ((NodePointer = GetNodeFromTreeByAnnotatedFormulaName(&Root,Name)) !=
NULL) {
        assert((*NodePointer) != NULL);
        ResetTreeVisited(Root);
        return((*NodePointer)->AnnotatedFormula);
    } else {
        ResetTreeVisited(Root);
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
TREENODE * GetNodeFromRootListByAnnotatedFormulaName(ROOTLIST RootListHead,
char * Name) {

    TREENODE  * NodePointer;
    ROOTLIST IteratorHead;

    ResetRootListVisited(RootListHead);
    IteratorHead = RootListHead;
    while (IteratorHead != NULL) {
        if ((NodePointer = GetNodeFromTreeByAnnotatedFormulaName(
&(IteratorHead->TheTree),Name)) != NULL) {
            ResetRootListVisited(RootListHead);
            return(NodePointer);
        }
        IteratorHead = IteratorHead->Next;
    }
    ResetRootListVisited(RootListHead);
    return(NULL);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA GetAnnotatedFormulaFromRootListByName(ROOTLIST Head,
char * Name) {

    TREENODE * NodePointer;

    if ((NodePointer = GetNodeFromRootListByAnnotatedFormulaName(Head,Name)) !=
NULL) {
        assert((*NodePointer) != NULL);
        return((*NodePointer)->AnnotatedFormula);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Examine.h"
#include "Interpret.h"
#include "Parsing.h"
#include "List.h"
#include "PrintTSTP.h"
#include "Tree.h"
//-------------------------------------------------------------------------------------------------
void SetUserData(TREENODE TreeNode,void * UserData) {

    TreeNode->UserData = UserData;
}
//-------------------------------------------------------------------------------------------------
void * GetUserData(TREENODE TreeNode) {

    return(TreeNode->UserData);
}
//-------------------------------------------------------------------------------------------------
void ResetTreeVisited(TREENODE Tree) {

    int Index;

    if (Tree != NULL && Tree->Visited) {
        Tree->Visited = 0;
        for (Index = 0; Index < Tree->NumberOfParents; Index++) {
            ResetTreeVisited(Tree->Parents[Index]);
        }
    }
}
//-------------------------------------------------------------------------------------------------
void ResetRootListVisited(ROOTLIST RootListHead) {

    while (RootListHead != NULL) {
        if (RootListHead->TheTree != NULL) {
            ResetTreeVisited(RootListHead->TheTree);
        }
        RootListHead = RootListHead->Next;
    }
}
//-------------------------------------------------------------------------------------------------
//----Returns 1/0 if all ancestors are not conjectures
int GetRootListWithAxiomAncestorLeaves(TREENODE Root,LISTNODE * ListSoFar,
LISTNODE * AddHere,int IgnoreDuplicates) {

    int AllAxiomAncestors;
    int Index;

    if (Root == NULL) {
        CodingError("Empty tree for GetRootListWithAxiomAncestorLeaves\n");
    }

//----If ignoring duplicates and we've already been here, just see if we
//----kept this boy to return the result
    if (IgnoreDuplicates && Root->Visited) {
        return(GetNodeFromListByAnnotatedFormula(ListSoFar,Root->
AnnotatedFormula) != NULL);
    }
//----Otherwise mark that we've been here and continue
    Root->Visited = 1;

//----If no parent check type - still can be part of theory
    if (Root->NumberOfParents == 0) {
        if (CheckRole(GetRole(Root->AnnotatedFormula,NULL),axiom_like)) {
//----If allowing duplicates or not already in the list
            if (!IgnoreDuplicates || GetNodeFromListByAnnotatedFormula(
ListSoFar,Root->AnnotatedFormula) == NULL) {
//----Add to the list
                AddListNode(AddHere,NULL,Root->AnnotatedFormula);
            }
//DEBUG printf("%s is axiom-like\n",GetName(Root->AnnotatedFormula,NULL));
            return(1);
        } else {
//DEBUG printf("%s is not axiom-like\n",GetName(Root->AnnotatedFormula,NULL));
            return(0);
        }
    } else {
//----Otherwise do parents recursively
        AllAxiomAncestors = 1;
        for (Index=0;Index<Root->NumberOfParents;Index++) {
            AllAxiomAncestors *= GetRootListWithAxiomAncestorLeaves(
Root->Parents[Index],ListSoFar,AddHere,IgnoreDuplicates);
//DEBUG if (!AllAxiomAncestors) printf("%s just lost axiom-like parents\n",GetName(Root->AnnotatedFormula,NULL));

//----Move down to end of list to ensure all parents before descendants
            while ((*AddHere) != NULL) {
                AddHere = &((*AddHere)->Next);
            }
        }
//----Add this one if all axiom ancestors
        if (AllAxiomAncestors) {
//DEBUG printf("%s has axiom-like ancestors\n",GetName(Root->AnnotatedFormula,NULL));
            if (!IgnoreDuplicates || GetNodeFromListByAnnotatedFormula(
ListSoFar,Root->AnnotatedFormula) == NULL) {
                AddListNode(AddHere,NULL,Root->AnnotatedFormula);
            }
        }
        return(AllAxiomAncestors);
    }
}
//-------------------------------------------------------------------------------------------------
LISTNODE GetListWithAxiomAncestorLeaves(ROOTLIST RootListHead,
int IgnoreDuplicates) {

    LISTNODE ListWithoutConjectureAncestor;
    LISTNODE * AddHere;

    ListWithoutConjectureAncestor = NULL;
    ResetRootListVisited(RootListHead);
    AddHere = &ListWithoutConjectureAncestor;
    while (RootListHead != NULL) {
//----Put theory onto growing list
        GetRootListWithAxiomAncestorLeaves(RootListHead->TheTree,
&ListWithoutConjectureAncestor,AddHere,IgnoreDuplicates);
//----Move down to end of list to ensure all parents before descendants
        while ((*AddHere) != NULL) {
            AddHere = &((*AddHere)->Next);
        }
        RootListHead = RootListHead->Next;
    }
    return(ListWithoutConjectureAncestor);
}
//-------------------------------------------------------------------------------------------------
int AllParentsHaveSyntax(TREENODE Root,SyntaxType Syntax) {

    int Index;

    for (Index=0;Index<Root->NumberOfParents;Index++) {
        if (GetSyntax(Root->Parents[Index]->AnnotatedFormula) != Syntax) {
            return(0);
        }
    }
    return(1);
}
//-------------------------------------------------------------------------------------------------
void GetRootSyntaxLeafList(TREENODE Root,LISTNODE * LeafListHead,
int IgnoreDuplicates,SyntaxType Syntax) {

    int Index;

    if (Root == NULL) {
        CodingError("Empty tree for GetRootSyntaxLeafList\n");
    }

//----If ignoring duplicates and we've already been here, nothing to do
    if (IgnoreDuplicates && Root->Visited) {
        return;
    }
//----Otherwise mark that we've been here and continue
    Root->Visited = 1;

//----If this node has the syntax we want, and it is a real leaf or not all 
//----the parents have the syntax we want
    if (GetSyntax(Root->AnnotatedFormula) == Syntax &&
(Root->NumberOfParents == 0 || !AllParentsHaveSyntax(Root,Syntax))) {
//----If allowing duplicates or not already in the list
        if (!IgnoreDuplicates || GetNodeFromListByAnnotatedFormula(
LeafListHead,Root->AnnotatedFormula) == NULL) {
//----Add to the list
            AddListNode(LeafListHead,(*LeafListHead),
Root->AnnotatedFormula);
        }
    } else {
//----If wrong syntax, or not a leaf, or all parents have the syntax we want
        for (Index=0;Index<Root->NumberOfParents;Index++) {
            GetRootSyntaxLeafList(Root->Parents[Index],LeafListHead,
IgnoreDuplicates,Syntax);
        }
    }
}
//-------------------------------------------------------------------------------------------------
LISTNODE GetSyntaxLeafList(ROOTLIST RootListHead,int IgnoreDuplicates,
SyntaxType Syntax) {

    LISTNODE LeafListHead;

    LeafListHead = NULL;
    ResetRootListVisited(RootListHead);
    while (RootListHead != NULL) {
        GetRootSyntaxLeafList(RootListHead->TheTree,&LeafListHead,
IgnoreDuplicates,Syntax);
        RootListHead = RootListHead->Next;
    }
    return(LeafListHead);
}
//-------------------------------------------------------------------------------------------------
//----Beware, this does not reset the visited tag, so if using it repeatedly
//----you may want to do that - depends on the application.
void GetRootLeafList(TREENODE Root,LISTNODE * LeafListHead,
int IgnoreDuplicates) {

    int Index;

    if (Root == NULL) {
        CodingError("Empty tree for GetRootLeafList\n");
    }

//----If ignoring duplicates and we've already been here, nothing to do
    if (IgnoreDuplicates && Root->Visited) {
        return;
    }
//----Otherwise mark that we've been here and continue
    Root->Visited = 1;

    if (Root->NumberOfParents == 0) {
        if (!IgnoreDuplicates || GetNodeFromListByAnnotatedFormula(
LeafListHead,Root->AnnotatedFormula) == NULL) {
            AddListNode(LeafListHead,(*LeafListHead),Root->AnnotatedFormula);
        }
    } else {
        for (Index=0;Index<Root->NumberOfParents;Index++) {
            GetRootLeafList(Root->Parents[Index],LeafListHead,IgnoreDuplicates);
        }
    }
}
//-------------------------------------------------------------------------------------------------
LISTNODE GetLeafList(ROOTLIST RootListHead,int IgnoreDuplicates) {

    LISTNODE LeafListHead;

    LeafListHead = NULL;
    ResetRootListVisited(RootListHead);
    while (RootListHead != NULL) {
        GetRootLeafList(RootListHead->TheTree,&LeafListHead,IgnoreDuplicates);
        RootListHead = RootListHead->Next;
    }
    return(LeafListHead);
}
//-------------------------------------------------------------------------------------------------
int DoGetRootLemmaList(TREENODE Root,LISTNODE * LeafListHead,int Duplicates) {

    int Index;
    int LemmaIndex;
    int OnConjecturePath;

//----If already known to be on conjecture path, no need to go up there
    if (Root->Visited) {
        return(1);
//----If conjecture not found then search parents recursively
    } else if (GetRole(Root->AnnotatedFormula,NULL) == conjecture) {
        return(1);
    } else {
        OnConjecturePath = 0;
        for (Index=0;Index<Root->NumberOfParents;Index++) {
            if (DoGetRootLemmaList(Root->Parents[Index],LeafListHead,
Duplicates)) {
                OnConjecturePath = 1;
//----Add all other parents as lemmas
                for (LemmaIndex=0;LemmaIndex<Root->NumberOfParents;
LemmaIndex++) {
//----Index is parent on path to conjecture - don't take him
                    if (LemmaIndex != Index && 
//----Also reject those on another path to the conjecture
!DoGetRootLemmaList(Root->Parents[LemmaIndex],LeafListHead,Duplicates) &&
//----Duplicates may not be needed
(Duplicates || GetNodeFromListByAnnotatedFormula(LeafListHead,Root->
Parents[LemmaIndex]->AnnotatedFormula) == NULL)) {
                        AddListNode(LeafListHead,(*LeafListHead),
Root->Parents[LemmaIndex]->AnnotatedFormula);
                    }
                }
            }
        }
        Root->Visited = OnConjecturePath;
        return(OnConjecturePath);
    }
}
//-------------------------------------------------------------------------------------------------
int GetRootLemmaList(TREENODE Root,LISTNODE * LeafListHead,int Duplicates) {

    ResetTreeVisited(Root);
    return(DoGetRootLemmaList(Root,LeafListHead,Duplicates));
}
//-------------------------------------------------------------------------------------------------
ROOTLIST GetFalseNodes(ROOTLIST RootListHead,LISTNODE Head) {

    ROOTLIST FalseList;
    TREENODE FalseNode;

    FalseList = NULL;
    while (Head != NULL) {
        if (FalseAnnotatedFormula(Head->AnnotatedFormula)) {
            if ((FalseNode = AnnotatedFormulaInTrees(RootListHead,
Head->AnnotatedFormula)) == NULL) {
                CodingError("False node is not in any tree");
            } else {
                AddRootNode(&FalseList,FalseList,FalseNode);
            }
        }
        Head = Head->Next;
    }
    return(FalseList);
}
//-------------------------------------------------------------------------------------------------
ROOTLIST GetFalseRootList(ROOTLIST RootListHead) {

    ROOTLIST FalseRootList;

    FalseRootList = NULL;
    while (RootListHead != NULL) {
        if (FalseAnnotatedFormula(RootListHead->TheTree->AnnotatedFormula)) {
            AddRootNode(&FalseRootList,FalseRootList,RootListHead->TheTree);
        }
        RootListHead = RootListHead->Next;
    }

    return(FalseRootList);
}
//-------------------------------------------------------------------------------------------------
TREENODE GetFalseRootNode(ROOTLIST RootListHead) {

    while (RootListHead != NULL) {
        if (FalseAnnotatedFormula(RootListHead->TheTree->AnnotatedFormula)) {
            return(RootListHead->TheTree);
        }
        RootListHead = RootListHead->Next;
    }

    return(NULL);
}
//-------------------------------------------------------------------------------------------------
LISTNODE GetRootList(LISTNODE Head,SIGNATURE Signature) {

    LISTNODE RootList;
    char * AllParentNames;
    int NumberOfParents;
    StringParts ParentNames;
    int ParentNumber;
    LISTNODE * Remover;
    String ParentName;
    BTREENODE ParentTree;

    RootList = DuplicateListOfNodes(Head,0);
    ParentTree = NULL;

//----For every node in the derivation list
    while ((Head = GetLogicNode(Head)) != NULL) {
//DEBUG printf("remove parents of %s\n",GetName(Head->AnnotatedFormula,NULL));
        AllParentNames = GetParentNames(Head->AnnotatedFormula,NULL);
        NumberOfParents = Tokenize(AllParentNames,ParentNames,"\n");
//----Remove all parents - they are not roots
        for (ParentNumber = 0;ParentNumber< NumberOfParents;ParentNumber++) {
//DEBUG printf("    remove parent %s\n",ParentNames[ParentNumber]);
//----Check if not already removed
            if (GetNodeFromBTreeByAnnotatedFormulaName(&ParentTree,
ParentNames[ParentNumber]) == NULL) {
//----Find in linear list and move to tree
                Remover = &RootList;
                while (*Remover != NULL && strcmp(ParentNames[ParentNumber],
GetName((*Remover)->AnnotatedFormula,ParentName))) {
                    Remover = &((*Remover)->Next);
                }
//----If found then remove from list and add to tree
                if (*Remover != NULL) {
                    AddBTreeNode(&ParentTree,(*Remover)->AnnotatedFormula);
                    FreeAListNode(Remover,Signature);
                }
            }
        }
        Free((void **)&AllParentNames);
        Head = Head->Next;
    }
//----Free the tree of parents
    FreeBTreeOfAnnotatedFormulae(&ParentTree,Signature);

    return(RootList);
}
//-------------------------------------------------------------------------------------------------
TREENODE * NewParentsList(int NumberOfParents) {

    TREENODE * ParentsList;
    int Index;

    ParentsList = (TREENODE *)Malloc(NumberOfParents * sizeof(TREENODE));
    for (Index = 0; Index < NumberOfParents; Index++) {
        ParentsList[Index] = NULL;
    }

    return(ParentsList);
}
//-------------------------------------------------------------------------------------------------
TREENODE NewTreeNode(ANNOTATEDFORMULA AnnotatedFormula) {

    TREENODE TreeNode;

    TreeNode = (TREENODE)Malloc(sizeof(TreeNodeType));
    TreeNode->NumberOfUses = 1;
    TreeNode->AnnotatedFormula = AnnotatedFormula;
    TreeNode->AnnotatedFormula->NumberOfUses++;
    TreeNode->NumberOfParents = 0;
    TreeNode->Parents = NULL;
    TreeNode->Visited = 0;
    TreeNode->UserData = NULL;
    return(TreeNode);
}
//-------------------------------------------------------------------------------------------------
ROOTLIST NewRootNode(TREENODE TheTree) {

    ROOTLIST RootList;

    RootList = (ROOTLIST)Malloc(sizeof(RootListType));
    RootList->Last = NULL;
    RootList->Next = NULL;
    RootList->TheTree = TheTree;
    if (RootList->TheTree != NULL) {
        RootList->TheTree->NumberOfUses++;
    }

    return(RootList);
}
//-------------------------------------------------------------------------------------------------
void AddRootNode(ROOTLIST * From,ROOTLIST Next,TREENODE TheTree) {

    ROOTLIST NewNode;

    NewNode = NewRootNode(TheTree);
    NewNode->Next = Next;
    *From = NewNode;
}
//-------------------------------------------------------------------------------------------------
void FreeTree(TREENODE * Tree,SIGNATURE Signature) {

    int Index;
//DEBUG String FormulaName;

    if (*Tree != NULL) {
//DEBUG printf("enter %s with %d uses\n",GetName((*Tree)->AnnotatedFormula,FormulaName),(*Tree)->NumberOfUses);

//----Recursively do parents first
        if (!(*Tree)->Visited) {
            (*Tree)->Visited = 1;
            if ((*Tree)->NumberOfParents > 0) {
//DEBUG printf("do the %d parents of %s\n",(*Tree)->NumberOfParents,FormulaName);
                for (Index = 0; Index < (*Tree)->NumberOfParents; Index++) {
                    FreeTree(&((*Tree)->Parents[Index]),Signature);
                }
                (*Tree)->NumberOfParents = 0;;
                Free((void **)&((*Tree)->Parents));
            }
        }

        --((*Tree)->NumberOfUses);
//DEBUG printf("%d more uses for %s\n",(*Tree)->NumberOfUses,FormulaName);

//----If no more uses then free it up
        if ((*Tree)->NumberOfUses == 0) {
//DEBUG printf("and now free memory for %s\n",FormulaName);
            FreeAnnotatedFormula(&((*Tree)->AnnotatedFormula),Signature);
            if ((*Tree)->UserData != NULL) {
                Free((void **)&((*Tree)->UserData));
            }
            Free((void **)Tree);
        }
    }
}
//-------------------------------------------------------------------------------------------------
void FreeRootNode(ROOTLIST * FreeThis,int MustFreeTree,SIGNATURE Signature) {

    if (MustFreeTree) {
        FreeTree(&((*FreeThis)->TheTree),Signature);
    } else {
//----Simply decrement the direct node counter
        (*FreeThis)->TheTree->NumberOfUses--;
    }
    Free((void **)FreeThis);
}
//-------------------------------------------------------------------------------------------------
void FreeARootNode(ROOTLIST * ToDelete,int MustFreeTree,SIGNATURE Signature) {

    ROOTLIST NextOne;

    if (ToDelete == NULL || *ToDelete == NULL) {
        CodingError("Deleting non-existent root node");
    }

    NextOne = (*ToDelete)->Next;
    FreeRootNode(ToDelete,MustFreeTree,Signature);
    *ToDelete = NextOne;
}
//-------------------------------------------------------------------------------------------------
void FreeRootList(ROOTLIST * Head,int MustFreeTree,SIGNATURE Signature) {

    if (MustFreeTree) {
        ResetRootListVisited(*Head);
    }
    while(*Head != NULL) {
        FreeARootNode(Head,MustFreeTree,Signature);
    }
}
//-------------------------------------------------------------------------------------------------
TREENODE DoAnnotatedFormulaInTree(TREENODE ATree,ANNOTATEDFORMULA 
LookingForThis) {

    int ParentIndex;
    TREENODE AncestorNode;

    if (ATree != NULL) {
        if (!ATree->Visited) {
//----Is this the one?
            if (ATree->AnnotatedFormula == LookingForThis) {
                return(ATree);
            } else {
//----Look in subtrees
                for (ParentIndex = 0; ParentIndex < ATree->NumberOfParents;
ParentIndex++) {
                    if ((AncestorNode = DoAnnotatedFormulaInTree(ATree->
Parents[ParentIndex],LookingForThis)) != NULL) {
                        return(AncestorNode);
                    }
                }
            }
            ATree->Visited = 1;
        } else {
            return(NULL);
        }
    } 

    return(NULL);
}
//-------------------------------------------------------------------------------------------------
TREENODE AnnotatedFormulaInTree(TREENODE ATree,ANNOTATEDFORMULA 
LookingForThis) {

    TREENODE TreeNodeFound;

    ResetTreeVisited(ATree);
    TreeNodeFound = DoAnnotatedFormulaInTree(ATree,LookingForThis);
    ResetTreeVisited(ATree);
    return(TreeNodeFound);
}
//-------------------------------------------------------------------------------------------------
TREENODE AnnotatedFormulaInTrees(ROOTLIST RootListHead,ANNOTATEDFORMULA 
LookingForThis) {

    TREENODE TreeNode;

    while (RootListHead != NULL) {
        if ((TreeNode = AnnotatedFormulaInTree(RootListHead->TheTree,
LookingForThis)) != NULL) {
            return(TreeNode);
        } else {
            RootListHead = RootListHead->Next;
        }
    }
    return(NULL);
}
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
TREENODE InListOfTreeNodes(ROOTLIST Head,ANNOTATEDFORMULA LookingForThis) {

    while (Head != NULL) {
        if (Head->TheTree != NULL && Head->TheTree->AnnotatedFormula ==
LookingForThis) {
            return(Head->TheTree);
        }
        Head = Head->Next;
    }

    return(NULL);
}
//-------------------------------------------------------------------------------------------------
//----Using a reference parameter rather than returning so that the linking
//----is done immediately to allow search what we have done already
TREENODE BuildTree(LISTNODE * NodesNotInTree,char * Name,TREENODE * TheTree,
ROOTBTREE * BTreeOfTreeNodes,SIGNATURE Signature) {

    ROOTBTREE * InTree;
    LISTNODE * PtrToNodeInList;
    char * AllParentNames;
    StringParts ParentNames;
    int ParentIndex;
    String ErrorMessage;

//DEBUG printf("Building tree for root %s \n",Name);fflush(stdout);
//----Try link to an existing node in the tree
    if ((InTree = GetNodeFromRootBTreeByAnnotatedFormulaName(BTreeOfTreeNodes,
Name)) != NULL) {
//DEBUG printf("already in tree\n");fflush(stdout);
        *TheTree = (*InTree)->TheTree;
        (*TheTree)->NumberOfUses++;
        return(*TheTree);

//----Make new tree node
    } else {
//DEBUG printf("making the tree node\n");fflush(stdout);
        if ((PtrToNodeInList = GetNodeFromListByAnnotatedFormulaName(
NodesNotInTree,Name)) == NULL) {
            sprintf(ErrorMessage,"Could not find formula named %s",Name);
            ReportError("SemanticError",ErrorMessage,0);
            return(NULL);
        }
        (*TheTree) = NewTreeNode((*PtrToNodeInList)->AnnotatedFormula);

//----Add to binary tree
        AddRootBTreeNode(BTreeOfTreeNodes,*TheTree);
//----Remove from nodes not in tree
        FreeAListNode(PtrToNodeInList,Signature);

//----Do parents if derived 
        if (DerivedAnnotatedFormula((*TheTree)->AnnotatedFormula)) {
            AllParentNames = GetNodeParentNames((*TheTree)->AnnotatedFormula,
NULL);
//DEBUG printf("Parents are %s\n",AllParentNames);fflush(stdout);
            if (((*TheTree)->NumberOfParents = Tokenize(AllParentNames,
ParentNames,"\n")) == 0) {
//DEBUG printf("There are no parents\n");fflush(stdout);
//----Derived but no parents - for tautologies which are inferred from nothing
                (*TheTree)->Parents = NULL;
            } else {
//DEBUG printf("Make list for the %d parents\n",(*TheTree)->NumberOfParents);fflush(stdout);
                (*TheTree)->Parents = NewParentsList((*TheTree)->NumberOfParents);
//DEBUG printf("Loop for parents\n");fflush(stdout);
                for (ParentIndex = 0;ParentIndex < (*TheTree)->NumberOfParents;
ParentIndex++) {
//DEBUG printf("Dealing with parent %s\n",ParentNames[ParentIndex]);fflush(stdout);
                    if (BuildTree(NodesNotInTree,ParentNames[ParentIndex],
&((*TheTree)->Parents[ParentIndex]),BTreeOfTreeNodes,Signature) == NULL) {
//DEBUG printf("ERROR: Could not build parent trees\n");fflush(stdout);
                        return(NULL);
                    }
                }
            }
            Free((void **)&AllParentNames);
        } else {
            (*TheTree)->NumberOfParents = 0;
            (*TheTree)->Parents = NULL;
        }
    }
    return(*TheTree);
}
//-------------------------------------------------------------------------------------------------
ROOTLIST BuildRootList(LISTNODE Head,SIGNATURE Signature) {

    LISTNODE NodesNotInTree;
    ROOTBTREE BTreeOfTreeNodes;
    ROOTLIST RootListHead;
    ROOTLIST * NextRootList;
    LISTNODE RootAnnotatedFormulae;
    LISTNODE RootAnnotatedFormulaNode;
    String RootName;
    String ErrorMessage;

//----This is the binary tree of all tree nodes
    BTreeOfTreeNodes = NULL;
//----This is the list of tree roots
    RootListHead = NULL;
//----This is the list of root formulae
    RootAnnotatedFormulae = NULL;

//----List of nodes not yet in tree
    NodesNotInTree = DuplicateListOfNodes(Head,0);
//----Keep a pointer to last link field in the list of tree roots
    NextRootList = &RootListHead;
//----Find all the root annotated formulae - each will start a tree
    RootAnnotatedFormulae = GetRootList(Head,Signature);
    RootAnnotatedFormulaNode = RootAnnotatedFormulae;
    while (RootAnnotatedFormulaNode != NULL) {
        GetName(RootAnnotatedFormulaNode->AnnotatedFormula,RootName);
        *NextRootList = NewRootNode(NULL);
        if (BuildTree(&NodesNotInTree,RootName,&((*NextRootList)->TheTree),&BTreeOfTreeNodes,
Signature) == NULL) {
            sprintf(ErrorMessage,"Could not build tree for root %s",RootName);
            ReportError("InputError",ErrorMessage,0);
            FreeListOfAnnotatedFormulae(&RootAnnotatedFormulae,Signature);
            FreeRootBTree(&BTreeOfTreeNodes,0,Signature);
            FreeRootList(&RootListHead,1,Signature);
            FreeListOfAnnotatedFormulae(&NodesNotInTree,Signature);
            return(NULL);
        } else {
            NextRootList = &((*NextRootList)->Next);
        }
        RootAnnotatedFormulaNode = RootAnnotatedFormulaNode->Next;
    }

//----Free list of root annotated formulae
    FreeListOfAnnotatedFormulae(&RootAnnotatedFormulae,Signature);
//----Free binary tree
    FreeRootBTree(&BTreeOfTreeNodes,0,Signature);
//----Should be none left not in tree
    if (NodesNotInTree != NULL) {
        ReportError("InputError","Could not build root list",0);
        FreeRootList(&RootListHead,1,Signature);
        FreeListOfAnnotatedFormulae(&NodesNotInTree,Signature);
        return(NULL);
    }

    return(RootListHead);
}
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
void DFS(FILE * Stream,TREENODE Root) {

    DFSWithIndent(Stream,Root,"");
}
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
void PrintTreeAnnotatedNodesInPostOrder(FILE * Stream,TREENODE TreeRoot) {

    int Index;

//----Don't print twice
    if (!TreeRoot->Visited) {
        TreeRoot->Visited = 1;
        if (TreeRoot->Parents != NULL) {
            for (Index=0;Index < TreeRoot->NumberOfParents; Index++) {
                PrintTreeAnnotatedNodesInPostOrder(Stream,
TreeRoot->Parents[Index]);
            }
        }
        PrintAnnotatedTSTPNode(Stream,TreeRoot->AnnotatedFormula,tptp,1);
        fprintf(Stream,"\n");
    }
}
//-------------------------------------------------------------------------------------------------
void PrintRootListAnnotatedNodesInPostOrder(FILE * Stream,
ROOTLIST RootListHead) {

    ResetRootListVisited(RootListHead);
    while (RootListHead != NULL) {
        PrintTreeAnnotatedNodesInPostOrder(Stream,RootListHead->TheTree);
        RootListHead = RootListHead->Next;    
    }
    ResetRootListVisited(RootListHead);
}
//-------------------------------------------------------------------------------------------------
void ListTreeAnnotatedNodesInPostOrder(TREENODE TreeRoot,
LISTNODE * AddNextHere) {

    int Index;

//----Don't list twice
    if (!TreeRoot->Visited) {
        TreeRoot->Visited = 1;
        if (TreeRoot->Parents != NULL) {
            for (Index=0;Index < TreeRoot->NumberOfParents; Index++) {
                ListTreeAnnotatedNodesInPostOrder(TreeRoot->Parents[Index],
AddNextHere);
//----Move down to end
                while (*AddNextHere != NULL) {
                    AddNextHere = &((*AddNextHere)->Next);
                }
            }
        }
        AddListNode(AddNextHere,NULL,TreeRoot->AnnotatedFormula);
    }
}
//-------------------------------------------------------------------------------------------------
LISTNODE ListRootListAnnotatedNodesInPostOrder(ROOTLIST RootListHead) {

    LISTNODE PostOrderList;
    LISTNODE * AddNextHere;

    ResetRootListVisited(RootListHead);
    AddNextHere = &PostOrderList;
    while (RootListHead != NULL) {
        ListTreeAnnotatedNodesInPostOrder(RootListHead->TheTree,AddNextHere);
//----Move down to end
        while (*AddNextHere != NULL) {
            AddNextHere = &((*AddNextHere)->Next);
        }
        RootListHead = RootListHead->Next;    
    }
    ResetRootListVisited(RootListHead);
    return(PostOrderList);
}
//-------------------------------------------------------------------------------------------------
//----All the code below here is for binary trees of tree nodes
//-------------------------------------------------------------------------------------------------
//----Search in binary root tree by annotated formula name
ROOTBTREE * GetNodeFromRootBTreeByAnnotatedFormulaName(ROOTBTREE * Root,
char * Name) {

    int Comparison;
        
    if (*Root == NULL) {
        return(NULL);
    } else {
        Comparison = strcmp((*Root)->TheTree->AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name,Name);
        if (Comparison == 0) {
            return(Root); 
        } else if (Comparison > 0) {
            return(GetNodeFromRootBTreeByAnnotatedFormulaName(&((*Root)->Last),
Name));     
        } else {
            return(GetNodeFromRootBTreeByAnnotatedFormulaName(&((*Root)->Next),
Name));     
        }
    }   
}
//-------------------------------------------------------------------------------------------------
ROOTBTREE AddRootBTreeNode(ROOTBTREE * Root,TREENODE TreeNode) {

    int Comparison;

    if (*Root == NULL) {
        *Root = NewRootNode(TreeNode);
        return(*Root);
    } else {
//----Check if already there
        if ((*Root)->TheTree == TreeNode) {
            return(*Root);
        } else {
            Comparison = strcmp((*Root)->TheTree->AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name,TreeNode->AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
            if (Comparison == 0) {
                return(NULL);
            } else if (Comparison > 0) {
                return(AddRootBTreeNode(&((*Root)->Last),TreeNode));
            } else {
                return(AddRootBTreeNode(&((*Root)->Next),TreeNode));
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------
void FreeRootBTree(ROOTBTREE * Root,int MustFreeTree,SIGNATURE Signature) {

    if (Root == NULL) {
        CodingError("Trying to free a non-existent binary root tree");
    }

    if (*Root != NULL) {
        FreeRootBTree(&((*Root)->Last),MustFreeTree,Signature);
        FreeRootBTree(&((*Root)->Next),MustFreeTree,Signature);
        FreeRootNode(Root,MustFreeTree,Signature);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintRootBTreeOfAnnotatedFormulae(ROOTBTREE Root) {

    if (Root != NULL) {
        PrintRootBTreeOfAnnotatedFormulae(Root->Last);
        PrintAnnotatedTSTPNode(stdout,Root->TheTree->AnnotatedFormula,tptp,1);
        PrintRootBTreeOfAnnotatedFormulae(Root->Next);
    }
}
//-------------------------------------------------------------------------------------------------

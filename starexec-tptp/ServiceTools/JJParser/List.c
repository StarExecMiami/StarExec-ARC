#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Modify.h"
#include "Examine.h"
#include "Compare.h"
#include "Parsing.h"
#include "PrintTSTP.h"
#include "List.h"
//-------------------------------------------------------------------------------------------------
void ResetListVisited(LISTNODE Head) {

    while (Head != NULL) {
        Head->Visited = 0;
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------
int ListLength(LISTNODE Head) {

    int Length;

    Length = 0;
    while (Head != NULL) {
        Length++;
        Head = Head->Next;
    }

    return(Length);
}
//-------------------------------------------------------------------------------------------------
//----Skip comments, blank lines, etc
LISTNODE GetLogicNode(LISTNODE Head) {

    while (Head != NULL && !LogicalAnnotatedFormula(Head->AnnotatedFormula)) {
        Head = Head->Next;
    }

    return(Head);
}
//-------------------------------------------------------------------------------------------------
LISTNODE NewListNode(ANNOTATEDFORMULA AnnotatedFormula) {

    LISTNODE NewNode;

    NewNode = (LISTNODE)Malloc(sizeof(ListNodeType));
    NewNode->Last = NULL;
    NewNode->Next = NULL;
    NewNode->AnnotatedFormula = AnnotatedFormula;
    NewNode->AnnotatedFormula->NumberOfUses++;

    return(NewNode);
}
//-------------------------------------------------------------------------------------------------
//----Pushes new node onto the front
void AddListNode(LISTNODE * From,LISTNODE Next,ANNOTATEDFORMULA AnnotatedFormulae) {

    LISTNODE NewNode;

    NewNode = NewListNode(AnnotatedFormulae);
    NewNode->Next = Next;
    *From = NewNode;
}
//-------------------------------------------------------------------------------------------------
//----This one duplicates the list of nodes, using the same annotated formulae
LISTNODE DuplicateListOfNodes(LISTNODE Head,int KeepNonLogicNodes) {

    LISTNODE DuplicateList;
    LISTNODE * Current;
    LISTNODE Target;

    DuplicateList = NULL;
    Current = &DuplicateList;
    Target = Head;
    if (!KeepNonLogicNodes) {
        Target = GetLogicNode(Target);
    }
    while (Target != NULL) {
        AddListNode(Current,NULL,Target->AnnotatedFormula);
        Current = &((*Current)->Next);
        Target = Target->Next;
        if (!KeepNonLogicNodes) {
            Target = GetLogicNode(Target);
        }
    }

    return(DuplicateList);
}
//-------------------------------------------------------------------------------------------------
//----This one also duplicates the annotated formula
LISTNODE DuplicateListOfAnnotatedFormulae(LISTNODE Head,SIGNATURE Signature) {

    LISTNODE DuplicateList;
    LISTNODE * Current;

    DuplicateList = NULL;
    Current = &DuplicateList;
    while (Head != NULL) {
//DEBUG printf("duplicating %s\n",GetName((Head)->AnnotatedFormula,NULL));
        AddListNode(Current,NULL,DuplicateAnnotatedFormula(Head->AnnotatedFormula,Signature));
//DEBUG printf("duplicated %s\n",GetName((*Current)->AnnotatedFormula,NULL));
        Current = &((*Current)->Next);
        Head = Head->Next;
    }

    return(DuplicateList);
}
//-------------------------------------------------------------------------------------------------
//----Simply does the memory deallocation for a list node. Not for users, who
//----should use FreeAListNode() below.
static void FreeListNode(LISTNODE * FreeThis,SIGNATURE Signature) {

//DEBUG printf("freeing ...\n"); PrintAnnotatedTSTPNode(stdout,(*FreeThis)->AnnotatedFormula,tptp,1); printf("it has %d uses\n",(*FreeThis)->AnnotatedFormula->NumberOfUses);
    FreeAnnotatedFormula(&((*FreeThis)->AnnotatedFormula),Signature);
    Free((void **)FreeThis);
}
//-------------------------------------------------------------------------------------------------
//----Frees a list node is a list, and updates the linking
void FreeAListNode(LISTNODE * ToDelete,SIGNATURE Signature) {

    LISTNODE NextOne;

    if (ToDelete == NULL || *ToDelete == NULL) {
        CodingError("Deleting non-existent node");
    }

    NextOne = (*ToDelete)->Next;
    FreeListNode(ToDelete,Signature);
    *ToDelete = NextOne;
}
//-------------------------------------------------------------------------------------------------
void FreeListOfAnnotatedFormulae(LISTNODE * Head,SIGNATURE Signature) {

//----Used to do this recursively, but run out of stack
    while (*Head != NULL) {
        FreeAListNode(Head,Signature);
    }
}
//-------------------------------------------------------------------------------------------------
LISTNODE AppendListsOfAnnotatedTSTPNodes(LISTNODE List1,LISTNODE List2) {

    LISTNODE LastNode;

    LastNode = List1;
    if (LastNode == NULL) {
        return(List2);
    } else {
        while (LastNode->Next != NULL) {
            LastNode = LastNode->Next;
        }
        LastNode->Next = List2;
        return(List1);
    }
}
//-------------------------------------------------------------------------------------------------
LISTNODE * GetLastNext(LISTNODE * Head) {

    while (*Head != NULL) {
        Head = &((*(*Head)).Next);
    }
    return(Head);
}
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
int UniquelyNamed(LISTNODE Head) {

    char * AllNames;
    StringParts Names;
    int NumberOfNames;
    int OKSoFar;
    int Original;
    int Copy;

    AllNames = (char *)Malloc(sizeof(String));
    GetAllNames(Head,&AllNames);
    NumberOfNames = Tokenize(AllNames,Names,"\n");
    OKSoFar = 1;

    for (Original = 0;OKSoFar && Original < NumberOfNames;Original++) {
        for (Copy = Original+1;OKSoFar && Copy < NumberOfNames;Copy++) {
            if (!strcmp(Names[Original],Names[Copy])) {
                OKSoFar = 0;
            }
        }
    }
    Free((void **)&AllNames);

    return(OKSoFar);
}
//-------------------------------------------------------------------------------------------------
LISTNODE * GetNodeFromListByNumber(LISTNODE * Head,int Number) {

    do {
//----Skip non-formula records
        while ((*Head) != NULL && !LogicalAnnotatedFormula((*Head)->AnnotatedFormula)) {
            Head = &((*Head)->Next);
        }
//----Is it the one we want?
        if ((*Head) != NULL) {
            if (Number == 1) {
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
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA GetAnnotatedFormulaFromListByNumber(LISTNODE Head,int Number) {

    LISTNODE * NodePointer;

    if ((NodePointer = GetNodeFromListByNumber(&Head,Number)) != NULL) {
        assert((*NodePointer) != NULL);
        return((*NodePointer)->AnnotatedFormula);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
//----The first parameter is a pointer to the pointer to the node in the real 
//----data structure, so that the function can return a pointer to the real
//----pointer in the data structure. This would not be possible if a pointer 
//----to the node were received, as then it would be in a local variable and
//----not be anything in the data structure.
//----Set SameFormula to 2 to allow commutation of = & | => <= <=> <~>
LISTNODE * GetNodeFromListByAnnotatedFormulaFields(LISTNODE * Head,ANNOTATEDFORMULA Target,
int SameName,int SameRole,int SameFormula) {

//----Cannot get non-logical
    if (!ReallyAnAnnotatedFormula(Target)) {
//DEBUG printf("FUCK 1\n");
        return(NULL);
    }
//----Search down the list for the one that I want, oo, oo, ooo
    do {
//DEBUG printf("DO\n");
//----Skip non-formula records
        while ((*Head) != NULL && !ReallyAnAnnotatedFormula((*Head)->AnnotatedFormula)) {
//DEBUG printf("SKIP\n");
            Head = &((*Head)->Next);
        }
//DEBUG printf("SEARCH 1 for %s\n",GetName(Target,NULL));
//----Is it the one we want?
        if ((*Head) != NULL) {
//DEBUG printf("SEARCH 2 is it %s\n",GetName((*Head)->AnnotatedFormula,NULL));
            if (
(!SameName || !strcmp(GetName((*Head)->AnnotatedFormula,NULL),GetName(Target,NULL))) &&
(!SameRole || GetRole(Target,NULL) == GetRole((*Head)->AnnotatedFormula,NULL)) &&
(!SameFormula || SameFormulaInAnnotatedFormulae(Target,(*Head)->AnnotatedFormula,1,SameFormula))) {
                return(Head);
            } else {
//----If not, move on
                Head = &((*Head)->Next);
            }
        }
    } while ((*Head) != NULL);

    return(NULL);
}
//-------------------------------------------------------------------------------------------------
LISTNODE * GetNodeFromListByAnnotatedFormulaName(LISTNODE * Head,char * Name) {

    AnnotatedFormulaType AnnotatedFormula;
    FormulaWithVariablesType FakeFormula;

//----Fake logical node for searching by name
    AnnotatedFormula.NumberOfUses = 0;
    AnnotatedFormula.Syntax = tptp_fof;
    AnnotatedFormula.AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = Name;
    AnnotatedFormula.AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status = nonstatus;
    AnnotatedFormula.AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables = 
&FakeFormula;
    AnnotatedFormula.AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source = NULL;
    AnnotatedFormula.AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo = NULL;

    return(GetNodeFromListByAnnotatedFormulaFields(Head,&AnnotatedFormula,1,0,0));
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA GetAnnotatedFormulaFromListByName(LISTNODE Head,char * Name) {

    LISTNODE * NodePointer;

    if ((NodePointer = GetNodeFromListByAnnotatedFormulaName(&Head,Name)) != NULL) {
//DEBUG printf("FOUND %s\n",Name);
        assert((*NodePointer) != NULL);
        assert((*NodePointer)->AnnotatedFormula != NULL);
        return((*NodePointer)->AnnotatedFormula);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
int GetNodesForNames(LISTNODE Head,StringParts ParentNames,int NumberOfParents,
LISTNODE * ParentList,SIGNATURE Signature) {

    int ParentNumber;
    ANNOTATEDFORMULA ParentAnnotatedFormula;

    *ParentList = NULL;
    for (ParentNumber = 0;ParentNumber < NumberOfParents;ParentNumber++) {
        if ((ParentAnnotatedFormula = GetAnnotatedFormulaFromListByName(Head,
ParentNames[ParentNumber])) == NULL) {
            FreeListOfAnnotatedFormulae(ParentList,Signature);
            return(0);
        } else {
            AddListNode(ParentList,NULL,ParentAnnotatedFormula);
            ParentList = &((*ParentList)->Next);
        }
    }
    return(1);
}
//-------------------------------------------------------------------------------------------------
LISTNODE * GetNodeFromListByAnnotatedFormula(LISTNODE * Head,ANNOTATEDFORMULA
AnnotatedFormula) {

    while ((*Head) != NULL) {
        if ((*Head)->AnnotatedFormula == AnnotatedFormula) {
            return(Head);
        }
        Head = &((*Head)->Next);
    }

    return(NULL);
}
//-------------------------------------------------------------------------------------------------
void RemoveAnnotatedFormulaWithRole(LISTNODE * Head,SIGNATURE Signature,StatusType Role) {

    while (*Head != NULL) {
        if (GetRole((*Head)->AnnotatedFormula,NULL) == Role) {
// printf("Removing %s",GetName((*Head)->AnnotatedFormula,NULL));
            FreeAListNode(Head,Signature);
        } else {
            Head = &((*Head)->Next);
        }
    }
}
//-------------------------------------------------------------------------------------------------
//----This one can remove those with the desired type
LISTNODE SelectListOfAnnotatedFormulaeWithRole(LISTNODE * Head,StatusType DesiredRole,
int DeletedSelected,SIGNATURE Signature) {

    LISTNODE ListWithRole;
    LISTNODE * AddHere;
    StatusType Role;

    ListWithRole = NULL;
    AddHere = &ListWithRole;
    while (*Head != NULL) {
        if (ReallyAnAnnotatedFormula((*Head)->AnnotatedFormula)) {
            Role = GetRole((*Head)->AnnotatedFormula,NULL);
            if (CheckRole(Role,DesiredRole)) {
                AddListNode(AddHere,NULL,(*Head)->AnnotatedFormula);
                AddHere = &((*AddHere)->Next);
//----Delete if requested
                if (DeletedSelected) {
                    FreeAListNode(Head,Signature);
                } else {
//----Move along if not deleted
                    Head = &(*Head)->Next;
                }
            } else {
//----Move along if role is not right
                Head = &(*Head)->Next;
            }
        } else {
//----Move along if not logical
            Head = &(*Head)->Next;
        }
    }
    return(ListWithRole);
}
//-------------------------------------------------------------------------------------------------
//----For backwards compatitibility
LISTNODE GetListOfAnnotatedFormulaeWithRole(LISTNODE Head,StatusType DesiredRole,SIGNATURE 
Signature) {

    return(SelectListOfAnnotatedFormulaeWithRole(&Head,DesiredRole,0,Signature));
}
//-------------------------------------------------------------------------------------------------
LISTNODE GetListWithSyntaxType(LISTNODE Head,SyntaxType DesiredSyntax) {

    LISTNODE ListWithSyntaxType;
    LISTNODE * AddHere;

    ListWithSyntaxType = NULL;
    AddHere = &ListWithSyntaxType;
    while (Head != NULL) {
        if (GetSyntax(Head->AnnotatedFormula) == DesiredSyntax) {
            AddListNode(AddHere,NULL,Head->AnnotatedFormula);
            AddHere = &((*AddHere)->Next);
        }
        Head = Head->Next;
    }
    return(ListWithSyntaxType);
}
//-------------------------------------------------------------------------------------------------
LISTNODE SelectListOfAnnotatedFormulaeWithParents(LISTNODE * Head,int DeletedSelected,
SIGNATURE Signature) {

    LISTNODE ListWithRole;
    LISTNODE * AddHere;

    ListWithRole = NULL;
    AddHere = &ListWithRole;
    while (*Head != NULL) {
        if (DerivedAnnotatedFormula((*Head)->AnnotatedFormula)) {
            AddListNode(AddHere,NULL,(*Head)->AnnotatedFormula);
            AddHere = &((*AddHere)->Next);
//----Delete if requested
            if (DeletedSelected) {
                FreeAListNode(Head,Signature);
            } else {
//----Move along if not deleted
                Head = &(*Head)->Next;
            }
        } else {
//----Move along if not derived
            Head = &(*Head)->Next;
        }
    }
    return(ListWithRole);
}
//-------------------------------------------------------------------------------------------------
//----0 means empty intersection, 1 means non-empty intersection, 2 means Set1
//----is a superset of Set2, 3 means they are equal, 4 means Set2 is a subset
//----of Set2. Assumes all lists have been merged!
int SetRelationshipListOfAnnotatedFormulae(LISTNODE Set1,LISTNODE Set2,
int AllowCommutation) {

    LISTNODE Target;
    int Set1SuperSet2 = 1;
    int Set2SuperSet1 = 1;
    int HaveIntersection = 0;

    Target = Set1;
    while ((Set2SuperSet1 || !HaveIntersection) && Target != NULL) {
        if (GetNodeFromListByAnnotatedFormula(&Set2,Target->AnnotatedFormula)
== NULL) {
            Set2SuperSet1 = 0;
        } else {
            HaveIntersection = 1;
        }
        Target = Target->Next;
    }
    Target = Set2;
    while (Set1SuperSet2 && Target != NULL) {
        if (GetNodeFromListByAnnotatedFormula(&Set1,Target->AnnotatedFormula)
== NULL) {
            Set1SuperSet2 = 0;
        } 
        Target = Target->Next;
    }

    if (!HaveIntersection && !Set1SuperSet2 && !Set2SuperSet1) {
        return(0);
    } 
    if (!Set1SuperSet2 && !Set2SuperSet1) {
        return(1);
    }
    if (Set1SuperSet2 && !Set2SuperSet1) {
        return(2);
    }
    if (!Set1SuperSet2 && Set2SuperSet1) {
        return(4);
    }
    if (Set1SuperSet2 && Set2SuperSet1) {
        return(3);
    }
    return(-1);
}
//-------------------------------------------------------------------------------------------------
//----If SameFormula = 1, then check modulo variable naming, if 2 then allow
//----commutation of operators (not fully implemented yet)
LISTNODE MergeInListOfAnnotatedFormulaeByFields(LISTNODE * MainList,LISTNODE * MergeList,
int SameName,int SameRole,int SameFormula,SIGNATURE Signature) {

    LISTNODE Target;
    LISTNODE NewMergeList;
    LISTNODE * AddMergeHere;
    LISTNODE * AddMainHere;
    LISTNODE * FoundNode;

//----Find end of MainList
    if (*MainList == NULL) {
        AddMainHere = MainList;
    } else {
        Target = *MainList;
        while (Target->Next != NULL) {
           Target = Target->Next;
        }
        AddMainHere = &(Target->Next);
    }
//----Move all in MergeList into MainList
    NewMergeList = NULL;
    AddMergeHere = &NewMergeList;
    Target = (*MergeList);
    while ((Target = GetLogicNode(Target)) != NULL) {
//----If already in the MainList, add to end of new merge list
        if ((FoundNode = GetNodeFromListByAnnotatedFormulaFields(MainList,
Target->AnnotatedFormula,SameName,SameRole,SameFormula)) != NULL) {
            AddListNode(AddMergeHere,NULL,(*FoundNode)->AnnotatedFormula);
            AddMergeHere = &((*AddMergeHere)->Next);
        } else {
//----Otherwise add the annotated formula to end of the MainList
            AddListNode(AddMainHere,NULL,Target->AnnotatedFormula);
            AddMainHere = &((*AddMainHere)->Next);
//----And add to the NewMergeList
            AddListNode(AddMergeHere,NULL,Target->AnnotatedFormula);
            AddMergeHere = &((*AddMergeHere)->Next);
        }
        Target = Target->Next;
    }
//----Free the old MergeList and assign the new one
    FreeListOfAnnotatedFormulae(MergeList,Signature);
    *MergeList = NewMergeList;
//----Return the new MainList
    return(*MainList);
}
//-------------------------------------------------------------------------------------------------
int CompareAnnotatedFormulaeByUsefulInfoField(ANNOTATEDFORMULA Larger,
ANNOTATEDFORMULA Smaller,char * FieldName,char DataType,int InvertOrder) {

//----Stay with String for now - can goto malloced if necessary
    String LargerInfo;
    String SmallerInfo;
    float LargerNumber;
    float SmallerNumber;
    int Order;

    if (GetUsefulInfoTerm(Larger,FieldName,1,LargerInfo) != NULL &&
GetUsefulInfoTerm(Smaller,FieldName,1,SmallerInfo) != NULL &&
ExtractTermArguments(LargerInfo) && ExtractTermArguments(SmallerInfo)) {
        switch (DataType) {
            case 's':
                if (!InvertOrder) {
                    return(strcmp(LargerInfo,SmallerInfo));
                } else {
                    return(strcmp(SmallerInfo,LargerInfo));
                }
                break;
            case 'd':
            case 'f':
                LargerNumber = atof(LargerInfo);
                SmallerNumber = atof(SmallerInfo);
                if (LargerNumber > SmallerNumber) {
                    Order = 1;
                } else if (LargerNumber == SmallerNumber)  {
                    Order = 0;
                } else {
                    Order = -1;
                }
                if (InvertOrder) {
                    Order *= -1;
                }
                return(Order);
                break;
            default:
                CodingError("Comparing useful info data by unknown type");
                return(0);
                break;
        }
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
//----Uses insertion sort :-(
LISTNODE SlowSortByUsefulInfoField(LISTNODE * Head,char * FieldName,
char DataType,int InvertOrder) {

    LISTNODE * Unsorted;
    LISTNODE * InsertionPoint;
    LISTNODE ToMove;

    Unsorted = Head;
    while (*Unsorted != NULL) {
        InsertionPoint = Head;
        while (InsertionPoint != Unsorted &&
//----Move insertion point along as far as possible to keep stable, hence !>
CompareAnnotatedFormulaeByUsefulInfoField((*InsertionPoint)->AnnotatedFormula,
(*Unsorted)->AnnotatedFormula,FieldName,DataType,InvertOrder) <= 0) {
            InsertionPoint = &((*InsertionPoint)->Next);
        }
//----If InsertionPoint has not reached the Unsorted, move around. This also
//----moves the Unsorted point along
        if (InsertionPoint != Unsorted) {
            ToMove = *Unsorted;
            *Unsorted = ToMove->Next;
            ToMove->Next = *InsertionPoint;
            *InsertionPoint = ToMove;
        } else {
//----Unsorted stays at end, move along
            Unsorted = &((*Unsorted)->Next);
        }
    }
    return(*Head);
}
//-------------------------------------------------------------------------------------------------
char * QSortFieldName;
char QSortDataType;
int QSortInvertOrder;

int QSortGreaterAnnotatedFormulaByUsefulInfoField(const void * Larger,
const void * Smaller) {

// printf("comparing two ANNOTATEDFORMULA ...\n");
// PrintAnnotatedTSTPNode(stdout,*((ANNOTATEDFORMULA *)Larger),tptp,1);
// PrintAnnotatedTSTPNode(stdout,*((ANNOTATEDFORMULA *)Smaller),tptp,1);
// printf("Their comparson is %d\n",GreaterAnnotatedFormulaByUsefulInfoField(
// *((ANNOTATEDFORMULA *)Larger),*((ANNOTATEDFORMULA *)Smaller),QSortFieldName,
// QSortDataType,QSortInvertOrder));

    return(CompareAnnotatedFormulaeByUsefulInfoField(
*((ANNOTATEDFORMULA *)Larger),*((ANNOTATEDFORMULA *)Smaller),QSortFieldName,
QSortDataType,QSortInvertOrder));
} 
//-------------------------------------------------------------------------------------------------
LISTNODE SortByUsefulInfoField(LISTNODE * Head,char * FieldName,char DataType,
int InvertOrder) {

    extern char * QSortFieldName;
    extern char QSortDataType;
    extern int QSortInvertOrder;
    ANNOTATEDFORMULA * AnnotatedFormulaArray;
    LISTNODE Target;
    int ArraySize;
    int ArrayCapacity;

    ArrayCapacity = 256;
    AnnotatedFormulaArray = (ANNOTATEDFORMULA *)Malloc(ArrayCapacity * 
sizeof(ANNOTATEDFORMULA));

    ArraySize = 0;
    Target = *Head;
    while (Target != NULL) {
        if (ArraySize == ArrayCapacity) {
            ArrayCapacity *= 2;
            AnnotatedFormulaArray = (ANNOTATEDFORMULA *)Realloc(
AnnotatedFormulaArray,ArrayCapacity * sizeof(ANNOTATEDFORMULA));
        }
        AnnotatedFormulaArray[ArraySize++] = Target->AnnotatedFormula;
        Target = Target->Next;
    }

    QSortFieldName = FieldName;
    QSortDataType = DataType;
    QSortInvertOrder = InvertOrder;
    qsort(AnnotatedFormulaArray,ArraySize,sizeof(ANNOTATEDFORMULA),
QSortGreaterAnnotatedFormulaByUsefulInfoField);

    ArraySize = 0;
    Target = *Head;
    while (Target != NULL) {
        Target->AnnotatedFormula = AnnotatedFormulaArray[ArraySize++];
        Target = Target->Next;
    }

    Free((void **)&AnnotatedFormulaArray);
    return(*Head);
}
//-------------------------------------------------------------------------------------------------
void RandomizeAnnotatedFormulaeInList(LISTNODE Head,unsigned int Seed) {

    SeedRand(Seed);
    while (Head != NULL) {
        RandomizeAnnotatedFormula(Head->AnnotatedFormula,0);
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------
//----Nasty quadratic randomizing
void SlowRandomizeListOrder(LISTNODE * Head,unsigned int Seed) {

    LISTNODE RandomizedList;
    long RandomPosition;
    long Index;
    LISTNODE * PointerToOneToMove;
    LISTNODE OneToMove;

    SeedRand(Seed);
    RandomizedList = NULL;
    while (*Head != NULL) {
        RandomPosition = RandomInRange(0,ListLength(*Head)-1,0);
        PointerToOneToMove = Head;
        for (Index = 0; Index < RandomPosition;Index++) {
            PointerToOneToMove = &((*PointerToOneToMove)->Next);
        }
        OneToMove = *PointerToOneToMove;
        *PointerToOneToMove = OneToMove->Next;
        if (RandomizedList == NULL) {
            OneToMove->Next = NULL;
        } else {
            OneToMove->Next = RandomizedList;
        }
        RandomizedList = OneToMove;
    }
    *Head = RandomizedList;
}
//-------------------------------------------------------------------------------------------------
void RandomizeListOrder(LISTNODE * Head,unsigned int Seed) {

    LISTNODE SplitHigh;
    LISTNODE SplitLow;
    LISTNODE MoveNode;

//----Empty lists and lists of one node are done
    if (*Head == NULL || (*Head)->Next == NULL) {
        return;
    } else {
        SeedRand(Seed);
        SplitHigh = NULL;
        SplitLow = NULL;
        while (*Head != NULL) {
            MoveNode = *Head;
            *Head = MoveNode->Next;
            if (RandomInRange(0,1,0)) {
                MoveNode->Next = SplitHigh;
                SplitHigh = MoveNode;
            } else {
                MoveNode->Next = SplitLow;
                SplitLow = MoveNode;
            }
        }
        RandomizeListOrder(&SplitHigh,0);
        RandomizeListOrder(&SplitLow,0);
        if (SplitLow == NULL) {
            *Head = SplitHigh;
        } else {
            *Head = SplitLow;
            while (SplitLow->Next != NULL) {
                SplitLow = SplitLow->Next;
            }
            SplitLow->Next = SplitHigh;
        }
    }
}
//-------------------------------------------------------------------------------------------------
void RandomizeListOfAnnotatedFormulae(LISTNODE * Head,unsigned int Seed) {

    SeedRand(Seed);
    RandomizeListOrder(Head,0);
    RandomizeAnnotatedFormulaeInList(*Head,0);
}
//-------------------------------------------------------------------------------------------------
//----All the code below here is for binary trees of formulae
//-------------------------------------------------------------------------------------------------
void ResetBTreeVisited(BTREENODE Root) {

    if (Root != NULL) {
        Root->Visited = 0;
        ResetBTreeVisited(Root->Last);
        ResetBTreeVisited(Root->Next);
    }
}
//-------------------------------------------------------------------------------------------------
//----Search in binary tree by annotated formula name
BTREENODE * GetNodeFromBTreeByAnnotatedFormulaName(BTREENODE * Root,char * Name) {

    int Comparison;
        
    if (*Root == NULL) {
        return(NULL);
    } else {
        Comparison = strcmp((*Root)->AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.Name,Name);
        if (Comparison == 0) {
            return(Root);
        } else if (Comparison > 0) {
            return(GetNodeFromBTreeByAnnotatedFormulaName(&((*Root)->Last),Name));
        } else {
            return(GetNodeFromBTreeByAnnotatedFormulaName(&((*Root)->Next),Name));
        }
    }
} 
//-------------------------------------------------------------------------------------------------
BTREENODE AddBTreeNode(BTREENODE * Root,ANNOTATEDFORMULA AnnotatedFormula) {

    int Comparison;

    if (!LogicalAnnotatedFormula(AnnotatedFormula)) {
        CodingError("Adding a non-logical formula to a binary tree");
    }
    if (*Root == NULL) {
        *Root = NewListNode(AnnotatedFormula);
        return(*Root);
    } else {
//----Check if already there
        if ((*Root)->AnnotatedFormula == AnnotatedFormula) {
            return(*Root);
        } else {
            Comparison = strcmp((*Root)->AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name,AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
            if (Comparison == 0) {
                return(NULL);
            } else if (Comparison > 0) {
                return(AddBTreeNode(&((*Root)->Last),AnnotatedFormula));
            } else {
                return(AddBTreeNode(&((*Root)->Next),AnnotatedFormula));
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------
BTREENODE ListToBTree(LISTNODE Head) {

    BTREENODE Root;

    Root = NULL;
    while (Head != NULL) {
        if (AddBTreeNode(&Root,Head->AnnotatedFormula) == NULL) {
            CodingError("Adding duplicate named formula to binary tree");
        }
        Head = Head->Next;
    }
    return(Root);
}
//-------------------------------------------------------------------------------------------------
void FreeBTreeOfAnnotatedFormulae(BTREENODE * Root,SIGNATURE Signature) {

    if (Root == NULL) {
        CodingError("Trying to free a non-existent binary tree");
    }

    if (*Root != NULL) {
        FreeBTreeOfAnnotatedFormulae(&((*Root)->Last),Signature);
        FreeBTreeOfAnnotatedFormulae(&((*Root)->Next),Signature);
        FreeListNode(Root,Signature);
    }
}
//-------------------------------------------------------------------------------------------------
void PrintBTreeOfAnnotatedFormulae(BTREENODE Root) {

    if (Root != NULL) {
        PrintBTreeOfAnnotatedFormulae(Root->Last);
        PrintAnnotatedTSTPNode(stdout,Root->AnnotatedFormula,tptp,1);
        PrintBTreeOfAnnotatedFormulae(Root->Next);
    }
}
//-------------------------------------------------------------------------------------------------
int BTreeDepth(BTREENODE Root) {

    int LastDepth;
    int NextDepth;

    if (Root == NULL) {
        return(0);
    } else {
        LastDepth = BTreeDepth(Root->Last);
        NextDepth = BTreeDepth(Root->Next);
        return(1 + (LastDepth > NextDepth ? LastDepth : NextDepth));
    }
}
//-------------------------------------------------------------------------------------------------

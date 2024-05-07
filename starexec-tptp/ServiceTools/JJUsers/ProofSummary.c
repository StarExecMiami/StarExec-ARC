#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "Compare.h"
#include "Modify.h"
#include "List.h"
#include "Tree.h"
#include "PrintTSTP.h"
#include "Interpret.h"
//-------------------------------------------------------------------------------------------------
typedef enum {tptpform,parentform,longform,shortform,lemmaform} OutputFormType;
//-------------------------------------------------------------------------------------------------
void ProcessCommandLine(int argc,char * argv[],OutputFormType * OutputForm,
char ** DerivationFileName) {

    char OptionChar;

    *OutputForm = shortform;
    *DerivationFileName = "--";

    while ((OptionChar = getopt(argc,argv,"f:h"))
!= -1) {
        switch (OptionChar) {
            case 'f':
                if  (!strcmp(optarg,"tptp")) {
                    *OutputForm = tptpform;
                } else if  (!strcmp(optarg,"parents")) {
                    *OutputForm = parentform;
                } else if  (!strcmp(optarg,"fof")) {
                    *OutputForm = longform;
                } else if  (!strcmp(optarg,"prolog")) {
                    *OutputForm = shortform;
                } else if  (!strcmp(optarg,"lemmavine")) {
                    *OutputForm = lemmaform;
                } else {
                    printf("ERROR: Illegal output form\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
            case '?':
                printf("Usage: %s <options> <derivation file>\n",argv[0]);
                printf("<options> are ...\n");
                printf("-f             - set output form (prolog)\n");
                printf("   tptp        - Leaves and Theorem in TPTP format\n");
                printf("   parents     - Leaves in TPTP format\n");
                printf("   fof         - Theorem in TPTP format\n");
                printf("   prolog      - proved(ConjectureName,[AxiomLeaves]).\n");
                printf("   lemmavine   - Lemmas in TPTP format\n");
                printf("-h             - print this help\n");
                printf("<derivation file> is ... (--)\n");
                printf("  Any normal file name\n");
                printf("  -- for stdin\n");
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("ERROR: Something wrong in getopt\n");
                exit(EXIT_FAILURE);
                break;
        }       
    }       

//----Check for problem file name
    if (argv[optind] != NULL) {
        *DerivationFileName = argv[optind];
    }
}
//-------------------------------------------------------------------------------------------------
char * SetOriginalName(ANNOTATEDFORMULA AnnotatedFormula,char * Name) {

    SuperString Source;
    char * StartOfName;

//----Default is the formula's name
    GetName(AnnotatedFormula,Name);
//----Try get the original name from a file source
    if (GetFileSourceNameAndNode(AnnotatedFormula,Source) != NULL) {
        StartOfName = strchr(Source,'\n')+1;
        if (strcmp(StartOfName,"unknown")) {
            strcpy(Name,strchr(Source,'\n')+1);
            SetName(AnnotatedFormula,Name);
        }
    } 
    return(Name);
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA GetInferredForTree(SIGNATURE Signature,ROOTLIST TargetTree,LISTNODE * Leaves,
ANNOTATEDFORMULA * RefutationRoot) {

    LISTNODE Conjectures = NULL;
    ANNOTATEDFORMULA Inferred;
    TREENODE FalseRootNode;

//----Check if a refutation
    if ((FalseRootNode = GetFalseRootNode(TargetTree)) != NULL) {
        *RefutationRoot = FalseRootNode->AnnotatedFormula;
//----For refutations extract the conjecture from the leaves
        Conjectures = SelectListOfAnnotatedFormulaeWithRole(Leaves,conjecture,1,Signature);
        if (Conjectures != NULL) {
//DEBUG printf("============ Conjectures\n");
//----If one conjecture inferred is the conjecture
            if (Conjectures->Next != NULL) {
//DEBUG printf("ERROR: Not one conjecture in FOF derivation");
                exit(EXIT_FAILURE);
            }
            Inferred = Conjectures->AnnotatedFormula;
            printf("%% The conjecture was proved by contradiction\n");
        } else {
//----If no conjectures, then the false is inferred
            Inferred = TargetTree->TheTree->AnnotatedFormula;
            printf("%% A contradiction was found without a conjecture\n");
        }
    } else {
//----The inferred is the root
        Inferred = TargetTree->TheTree->AnnotatedFormula;
        printf("%% The conjecture was proved directly\n");
        *RefutationRoot = NULL;
    } 
    FreeListOfAnnotatedFormulae(&Conjectures,Signature);
    return(Inferred);
}
//-------------------------------------------------------------------------------------------------
void PrintSummary(LISTNODE Leaves,ANNOTATEDFORMULA Inferred,
OutputFormType OutputForm,SIGNATURE Signature) {

    SuperString ParentList;
    SuperString InferenceTerm;
    LISTNODE Target = NULL;
    int NumberOfParents;
    SuperString Name;

//----Generate parent list as a string for either output form
    strcpy(ParentList,"[");
    Target = Leaves;
    NumberOfParents = 0;
    while (Target != NULL) {
//----Avoid case of the inferred being the only node, which makes it a leaf too
        if (Target->AnnotatedFormula != Inferred) {
            if (NumberOfParents > 0) {
                strcat(ParentList,",");
            }
            SetOriginalName(Target->AnnotatedFormula,Name);
            strcat(ParentList,Name);
            NumberOfParents++;
//----Output parent if in parent or tptp form
            if (OutputForm == tptpform || OutputForm == parentform || OutputForm == lemmaform) {
                if (OutputForm == lemmaform) {
                    FOFify(Target->AnnotatedFormula,universal);
                    if (DerivedAnnotatedFormula(Target->AnnotatedFormula)) {
                        SetStatus(Target->AnnotatedFormula,lemma,NULL);
                    }
                }
                PrintAnnotatedTSTPNode(stdout,Target->AnnotatedFormula,tptp,1);
                printf("\n");
            }
        }
        Target = Target->Next;
    }
    strcat(ParentList,"]");

//----Set the inferred to it's theorem form
    SetOriginalName(Inferred,Name);
    SetStatus(Inferred,theorem,NULL);
    sprintf(InferenceTerm,"inference(summary,[status(thm)],%s)",ParentList);
    SetSourceFromString(Inferred,Signature,InferenceTerm);

//----Print the inferred
    if (OutputForm == tptpform || OutputForm == longform) {
        PrintAnnotatedTSTPNode(stdout,Inferred,tptp,1);
        printf("\n");
    } 
    if (OutputForm == shortform) {
        if (FalseAnnotatedFormula(Inferred)) {
            printf("proved(%s,%s).\n","$false",ParentList);
        } else {
            printf("proved(%s,%s).\n",GetName(Inferred,Name),ParentList);
        }
    } 
}
//-------------------------------------------------------------------------------------------------
void AddUndischargedAssumptions(ANNOTATEDFORMULA Inferred,LISTNODE Leaves,
LISTNODE * Lemmas) {

    TERM FormulaAssumptionsTerm;
    char * FormulaAssumptions;
    StringParts AssumptionNames;
    int NumberofAssumptions;
    int AssumptionNumber;
    ANNOTATEDFORMULA Assumption;

    if ((FormulaAssumptionsTerm = GetInferenceInfoTERM(Inferred,
"assumptions")) != NULL) {
        FormulaAssumptions = ExtractAssumptionsList(FormulaAssumptionsTerm);
//DEBUG printf("FormulaAssumptions are %s\n",FormulaAssumptions);
    } else {
//DEBUG printf("The formula has no assumptions\n");
        FormulaAssumptions = NULL;
    }
    NumberofAssumptions = Tokenize(FormulaAssumptions,AssumptionNames,",");
    for (AssumptionNumber = 0; AssumptionNumber < NumberofAssumptions;
AssumptionNumber++) {
        if ((Assumption = GetAnnotatedFormulaFromListByName(Leaves,
AssumptionNames[AssumptionNumber])) == NULL) {
            printf("ERROR: Missing assumption %s\n",
AssumptionNames[AssumptionNumber]);
            exit(EXIT_FAILURE);
        }
        AddListNode(Lemmas,(*Lemmas)->Next,Assumption);
    }

    if (FormulaAssumptions != NULL) {
        Free((void **)&FormulaAssumptions);
    }
}
//-------------------------------------------------------------------------------------------------
void RemoveDischargedAssumptions(SIGNATURE Signature,ANNOTATEDFORMULA Inferred,LISTNODE * Leaves) {

    TERM FormulaAssumptionsTerm;
    char * FormulaAssumptions;
    String LeafName;

    if ((FormulaAssumptionsTerm = GetInferenceInfoTERM(Inferred,
"assumptions")) != NULL) {
        FormulaAssumptions = ExtractAssumptionsList(FormulaAssumptionsTerm);
    } else {
//DEBUG printf("The formula has no assumptions\n");
        FormulaAssumptions = NULL;
    }
//----Move down the leaves list, and for each assumption remove if not in
//----assumptions list
    while (*Leaves != NULL) {
        GetName((*Leaves)->AnnotatedFormula,LeafName);
        strcat(LeafName,",");
        if (GetRole((*Leaves)->AnnotatedFormula,NULL) == assumption &&
(FormulaAssumptions == NULL || strstr(FormulaAssumptions,LeafName) == NULL)) {
            FreeAListNode(Leaves,Signature);
        } else {
            Leaves = &((*Leaves)->Next);
        }
    }
    if (FormulaAssumptions != NULL) {
        Free((void **)&FormulaAssumptions);
    }
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    OutputFormType OutputForm;
    char * DerivationFileName;
    SIGNATURE Signature;
    LISTNODE Head;
    ROOTLIST RootListHead;
    ROOTLIST TargetTree;
    LISTNODE Leaves;
    LISTNODE Lemmas;
    ANNOTATEDFORMULA Inferred;
    ANNOTATEDFORMULA RefutationRoot;

    ProcessCommandLine(argc,argv,&OutputForm,&DerivationFileName);
//----Read from file or stdin
    Signature = NewSignature();
    SetNeedForNonLogicTokens(0);
    Head = ParseFileOfFormulae(DerivationFileName,NULL,Signature,1,NULL);
//DEBUG printf("============ All of them\n");
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,Head,tptp,1);

//----Build tree
    RootListHead = BuildRootList(Head,Signature);

    printf("%% SZS status Success for %s\n",DerivationFileName);
    printf("%% SZS output start Summary\n");
    TargetTree = RootListHead;
    while (TargetTree != NULL) {
        ResetRootListVisited(RootListHead);
        Leaves = NULL;
        GetRootLeafList(TargetTree->TheTree,&Leaves,1);
//DEBUG printf("============ Leaves\n");
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,Leaves,tptp,1);
        Inferred = GetInferredForTree(Signature,TargetTree,&Leaves,&RefutationRoot);
        Lemmas = NULL;
        if (OutputForm == lemmaform) {
            if (!GetRootLemmaList(TargetTree->TheTree,&Lemmas,0)) {
                printf("ERROR: Could not extract vine of lemmas\n");
                exit(EXIT_FAILURE);
            }
//DEBUG printf("============ Lemmas before adding assumptions\n");
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,Lemmas,tptp,1);
//             AddUndischargedAssumptions(RefutationRoot == NULL ?
// Inferred:RefutationRoot,Leaves,&Lemmas);
        }
        if (OutputForm == lemmaform) {
            PrintSummary(Lemmas,Inferred,OutputForm,Signature);
            FreeListOfAnnotatedFormulae(&Lemmas,Signature);
        } else {
            RemoveDischargedAssumptions(Signature,Inferred,&Leaves);
//DEBUG printf("============ Leaves\n");
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,Leaves,tptp,1);
            PrintSummary(Leaves,Inferred,OutputForm,Signature);
        }
        FreeListOfAnnotatedFormulae(&Leaves,Signature);
        TargetTree = TargetTree->Next;
    }
    printf("%% SZS output end Summary\n");

//----Free Willie!
    FreeRootList(&RootListHead,1,Signature);
    FreeListOfAnnotatedFormulae(&Head,Signature);
    FreeSignature(&Signature);
    return(EXIT_SUCCESS);
}
//-------------------------------------------------------------------------------------------------

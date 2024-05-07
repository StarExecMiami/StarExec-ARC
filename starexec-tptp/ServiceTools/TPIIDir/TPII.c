#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "ParseTSTP.h"
#include "Signature.h"
#include "Examine.h"
#include "Modify.h"
#include "List.h"
#include "SystemOnTPTP.h"
#include "PrintTSTP.h"
#include "TPII.h"
//-------------------------------------------------------------------------------------------------
int Interpret(OptionsType Options,char * FileName,LISTNODE * LogicalFormulae,
LISTNODE ** AddLogicalHere,SIGNATURE Signature,char * IncludeFilter,GroupNamesType GroupNames,
int * NumberOfGroups);
//-------------------------------------------------------------------------------------------------
void DeleteTemporaryFiles(void) {

    int FileNumber;
    extern TemporaryFileNamesArray MktempFileNames;
    extern int NumberOfTemporaryFileNames;
    extern int GlobalQUIT;

    GlobalQUIT = 0;
//----Stop any ATP systems that are running
    kill(0,SIGQUIT);

    if (NumberOfTemporaryFileNames > 0) {
        sleep(1);
    }
    for (FileNumber = 0;FileNumber < NumberOfTemporaryFileNames;FileNumber++) {
        if (access(MktempFileNames[FileNumber],F_OK) == 0) {
            RemoveFile(MktempFileNames[FileNumber]);
        }
    }
}
//-------------------------------------------------------------------------------------------------
void exit_SZS_NoSuccess(void) {

    printf("%% SZS status Error\n");
    exit(EXIT_FAILURE);
}
//-------------------------------------------------------------------------------------------------
//----Return the first index for files in argv
int ProcessCommandLine(int argc,char * argv[],OptionsType * Options) {

    int OptionChar;
    
    Options->Quietness = 2;

    while ((OptionChar = getopt(argc,argv,"q:h")) != -1) {
        switch (OptionChar) {
            case 'q':
                Options->Quietness = atoi(optarg);
                break; 
            case 'h':
            case '?':
                printf("Usage: %s <options> <files>\n",argv[0]);
                printf("<options> are ...\n");
                printf("  -q<quietness>   - control amount of output (1)\n");
                printf("  -h              - print this help\n");
                printf("<files> are ...\n");
                printf("  Any normal file name\n");
                printf("  A TPTP problem name\n");
                printf("  -- for stdin\n");
                exit_SZS_NoSuccess();
                break;
            default:
                printf("ERROR: Something wrong in getopt\n");
                exit_SZS_NoSuccess();
                break;
        }
    }
//----Backup to -- for stdin input to JJParser
    if (!strcmp(argv[optind-1],"--")) {
        optind--;
    }

//----Echo if in verbose mode
    if (Options->Quietness == 0) {
        printf("Command line options:\n");
        printf("    Quietness %d\n",Options->Quietness);
    }

    return(optind);
}
//-------------------------------------------------------------------------------------------------
READFILE OpenInputREADFILE(OptionsType Options,char * FileName) {

    READFILE InputStream; 

    if ((InputStream = OpenReadFile(FileName,NULL)) != NULL) {
        return(InputStream);
    } else {
        printf("ERROR: Cannot open %s for reading\n",FileName);
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
void CommandDetailsError(char * CommandName,StatusType Command,
FORMULA CommandDetails) {

    printf("ERROR: Incorrect argument for TPI command %s,%s - ",
CommandName,StatusToString(Command));
    PrintTSTPFormula(stdout,tptp,CommandDetails,0,0,none,1);
    printf("\n");
    exit_SZS_NoSuccess();
}
//-------------------------------------------------------------------------------------------------
//----Checks this is an atom - propositional or $getenv or $getargv
void CheckCommandDetailsAtom(char * CommandName,StatusType Command,
FORMULA CommandDetails,TERM Atom) {

//----If an atom is expected it must not have arguments, or it must be a 
//----$getenv/$getargv with 1 argument
    if (GetArity(Atom) != 0 &&
!((!strcmp(GetSymbol(Atom),"$getenv") || !strcmp(GetSymbol(Atom),"$getargv")) 
&& GetArity(Atom) == 1 && GetArity(Atom->Arguments[0]) == 0)) {
        CommandDetailsError(CommandName,Command,CommandDetails);
    }
}
//-------------------------------------------------------------------------------------------------
void CheckCommandDetailsType(char * CommandName,StatusType Command,
FORMULA CommandDetails,FormulaTypeType ExpectedDetailsType,
int MustBeAtomic) {

//----Error if unexpected type
    if (CommandDetails->Type != ExpectedDetailsType) {
        CommandDetailsError(CommandName,Command,CommandDetails);
    }
    if (MustBeAtomic && ExpectedDetailsType == atom) {
        CheckCommandDetailsAtom(CommandName,Command,CommandDetails,
CommandDetails->FormulaUnion.Atom);
    }
}
//-------------------------------------------------------------------------------------------------
char * GetGetValue(char * GetFunction,char * GetArgument) {

    int CommandLinePosition;
    char * OriginalSymbol;
    extern char ** FirstArgument;
    extern int NumberOfArguments;

//----If it's $getargv get from command line
    if (!strcmp(GetFunction,"$getargv")) {
//----Anything malformed becomes 0 - yak. Note we use Perl style counting,
//----so argv[0] is the first after the "required" bits.
        CommandLinePosition = atoi(GetArgument);
        if (CommandLinePosition < NumberOfArguments) {
            OriginalSymbol = FirstArgument[CommandLinePosition];
        } else {
            printf("ERROR: There is no argument %d\n",CommandLinePosition);
            exit_SZS_NoSuccess();
        }
//----Otherwise take from environment
    } else if (!strcmp(GetFunction,"$getenv")) {
//----If the environment valriable had no value, make an empty string to return
        if ((OriginalSymbol = getenv(GetArgument)) == NULL) {
            OriginalSymbol = "";
        }
    } else {
        OriginalSymbol = NULL;
    }
    return(OriginalSymbol);
}
//-------------------------------------------------------------------------------------------------
//----The returned memory is malloced. The user code is expected to free
//----the memory when done.
char * GetAtomSymbol(TERM Atom) {

    char * OriginalSymbol;
    char * CopiedSymbol;
    char * GetArgument;
    char * GetTerm;
    char * Close;
    String Rest;
    String Mover;

//----Get a pointer to the original principle symbol
    OriginalSymbol = GetSymbol(Atom);
//----If it's $getenv or $getargv then it will have been parsed, so pull 
//----out the argument environment variable.
    if (!strcmp(OriginalSymbol,"$getenv") || 
!strcmp(OriginalSymbol,"$getargv")) {
        GetArgument = GetAtomSymbol(Atom->Arguments[0]);
        OriginalSymbol = GetGetValue(OriginalSymbol,GetArgument);
        Free((void **)&GetArgument);
        CopiedSymbol = (char *)Malloc(strlen(OriginalSymbol)+1);
        strcpy(CopiedSymbol,OriginalSymbol);
    } else {
//----Otherwise assume it's a simple atomic term (constant)
        CopiedSymbol = (char *)Malloc(strlen(OriginalSymbol)+1);
        strcpy(CopiedSymbol,OriginalSymbol);
//----Convert any $getenv and $getargv terms therein. They will not have 
//----been parsed, so extract string by hand.
        while ((GetTerm = strstr(CopiedSymbol,"$getenv(")) != NULL ||
(GetTerm = strstr(CopiedSymbol,"$getargv(")) != NULL) {
            if (strstr(GetTerm,"$getenv(") == GetTerm) {
                GetArgument = GetTerm+strlen("$getenv(");
            } else {
                GetArgument = GetTerm+strlen("$getargv(");
            }
            *(GetArgument - 1) = '\0';
            Close = strchr(GetArgument,')');
            strcpy(Rest,Close+1);
            *Close= '\0';
            OriginalSymbol = GetGetValue(GetTerm,GetArgument);
            *GetTerm = '\0';
//----Replace the $getenv term by its value
            CopiedSymbol = (char *)Realloc(CopiedSymbol,
strlen(CopiedSymbol)+strlen(OriginalSymbol)+strlen(Rest)+1);
            strcat(CopiedSymbol,OriginalSymbol);
            strcat(CopiedSymbol,Rest);
        }
    } 
//----Remove any ''s from parsing
    if (CopiedSymbol[0] == '\'') {
        strcpy(Mover,CopiedSymbol+1);
        Mover[strlen(Mover)-1] = '\0';
        strcpy(CopiedSymbol,Mover);
    }
    return(CopiedSymbol);
}
//-------------------------------------------------------------------------------------------------
//----The returned memory is malloced. The user code is expected to free
//----the memory when done.
char * GetCommandDetailsAtom(FORMULA CommandDetails) {

    assert(CommandDetails->Type == atom);
    return(GetAtomSymbol(CommandDetails->FormulaUnion.Atom));
}
//-------------------------------------------------------------------------------------------------
void GetCommandDetailsEqualityAtoms(char * CommandName,StatusType Command,
FORMULA CommandDetails, char ** LHS,char ** RHS) {

    assert(!strcmp(GetSymbol(CommandDetails->FormulaUnion.Atom),"="));
    CheckCommandDetailsAtom(CommandName,Command,CommandDetails,
CommandDetails->FormulaUnion.Atom->Arguments[0]);
    CheckCommandDetailsAtom(CommandName,Command,CommandDetails,
CommandDetails->FormulaUnion.Atom->Arguments[1]);
    *LHS = GetAtomSymbol(
CommandDetails->FormulaUnion.Atom->Arguments[0]);
    *RHS = GetAtomSymbol(CommandDetails->FormulaUnion.Atom->Arguments[1]);
}
//-------------------------------------------------------------------------------------------------
int LogicalFormulaInGroup(LISTNODE LogicalFormula,char * GroupName) {

    int OccurenceNumber;
    TERM GroupTerm;

    OccurenceNumber = 1;
    while ((GroupTerm = GetUsefulInfoTERM(LogicalFormula->AnnotatedFormula,
"tpi_group",OccurenceNumber)) != NULL) {
        if (!strcmp(GetSymbol(GroupTerm->Arguments[0]),GroupName)) {
            return(1);
        }
        OccurenceNumber++;
    }
    return(0);
 }
//-------------------------------------------------------------------------------------------------
int ActiveLogicalFormula(LISTNODE LogicalFormula) {

    TERM GroupTerm;

    if ((GroupTerm = GetUsefulInfoTERM(LogicalFormula->AnnotatedFormula,
"tpi_state",1)) != NULL) {
        if (!strcmp(GetSymbol(GroupTerm->Arguments[0]),"active")) {
            return(1);
        } else {
            return(0);
        }
    } else {
        printf("ERROR: Cannot get state for formula %s\n",
GetName(LogicalFormula->AnnotatedFormula,NULL));
        exit_SZS_NoSuccess();
        return(0);
    }
 }
//-------------------------------------------------------------------------------------------------
LISTNODE GetListOfActiveLogicalFormulaeInGroups(LISTNODE LogicalFormulae,char * Groups) {

    LISTNODE LogicalFormulaeInGroups;
    LISTNODE * AddLogicalHere;
    LISTNODE SelectLogicalFormula;
    char * GroupName;
    String LocalGroups;

    strcpy(LocalGroups,Groups);
    LogicalFormulaeInGroups = NULL;
    AddLogicalHere = &LogicalFormulaeInGroups;
    GroupName = strtok(LocalGroups,",");
    while (GroupName != NULL) {
        Trim(GroupName);
        SelectLogicalFormula = LogicalFormulae;
        while (SelectLogicalFormula != NULL) {
            if (ActiveLogicalFormula(SelectLogicalFormula) &&
(!strcmp(GroupName,"tpi") || 
(!strcmp(GroupName,"tpi_premises") && 
 CheckRole(GetRole(SelectLogicalFormula->AnnotatedFormula,NULL),axiom_like)) ||
(!strcmp(GroupName,"tpi_conjectures") &&
 (CheckRole(GetRole(SelectLogicalFormula->AnnotatedFormula,NULL),conjecture) || 
 CheckRole(GetRole(SelectLogicalFormula->AnnotatedFormula,NULL),negated_conjecture))) ||
LogicalFormulaInGroup(SelectLogicalFormula,GroupName))) {
                AddListNode(AddLogicalHere,NULL,SelectLogicalFormula->AnnotatedFormula);
                AddLogicalHere = &((*AddLogicalHere)->Next);
            }
            SelectLogicalFormula = SelectLogicalFormula->Next;
        }
        GroupName = strtok(NULL,",");
    }
    return(LogicalFormulaeInGroups);
}
//-------------------------------------------------------------------------------------------------
void SetTPIState(ANNOTATEDFORMULA AnnotatedFormula,SIGNATURE Signature,
char * State) {

    String StateTag;

    RemoveUsefulInformationFromAnnotatedFormula(AnnotatedFormula,Signature,"tpi_state");
    sprintf(StateTag,"tpi_state(%s)",State);
    AddUsefulInformationToAnnotatedFormula(AnnotatedFormula,Signature,StateTag);
}
//-------------------------------------------------------------------------------------------------
void SetTPIStateForCommand(char * CommandName,StatusType Command,FORMULA CommandDetails,
LISTNODE LogicalFormulae,SIGNATURE Signature,char * State) {

    LISTNODE * NodePointer;
    char * FormulaName;

    CheckCommandDetailsType(CommandName,Command,CommandDetails,atom,1);
    FormulaName = GetCommandDetailsAtom(CommandDetails);
    if ((NodePointer = GetNodeFromListByAnnotatedFormulaName(&LogicalFormulae,
FormulaName)) != NULL) {
        SetTPIState((*NodePointer)->AnnotatedFormula,Signature,State);
    } else {
        printf("ERROR: Cannot set state for non-existent formula %s\n",FormulaName);
        exit_SZS_NoSuccess();
    }
    Free((void **)&FormulaName);
}
//-------------------------------------------------------------------------------------------------
void SetTPIStateForGroup(char * CommandName,StatusType Command,FORMULA CommandDetails,
LISTNODE LogicalFormulae,SIGNATURE Signature,char * State) {

    char * GroupName;

    CheckCommandDetailsType(CommandName,Command,CommandDetails,atom,1);
    GroupName = GetCommandDetailsAtom(CommandDetails);
    while (LogicalFormulae != NULL) {
        if (LogicalFormulaInGroup(LogicalFormulae,GroupName)) {
            SetTPIState(LogicalFormulae->AnnotatedFormula,Signature,State);
        }
        LogicalFormulae = LogicalFormulae->Next;
    }
    Free((void **)&GroupName);
}
//-------------------------------------------------------------------------------------------------
int FindGroupNumber(char * GroupName,GroupNamesType GroupNames,int NumberOfGroups) {

    int GroupNumber;

    for (GroupNumber=0; GroupNumber < NumberOfGroups; GroupNumber++) {
        if (!strcmp(GroupName,GroupNames[GroupNumber])) {
            return(GroupNumber);
        }
    }
    return(-1);
}
//-------------------------------------------------------------------------------------------------
void DoStartGroup(char * StartedGroupName,GroupNamesType GroupNames,int * NumberOfGroups) {

    if (FindGroupNumber(StartedGroupName,GroupNames,*NumberOfGroups) >= 0) {
        printf("ERROR: Started an already started group %s\n",StartedGroupName);
        Free((void **)&StartedGroupName);
        exit_SZS_NoSuccess();
    } else {
        GroupNames[*NumberOfGroups] = StartedGroupName;
        (*NumberOfGroups)++;
    }
}
//-------------------------------------------------------------------------------------------------
void DoEndGroup(int GroupNumber,GroupNamesType GroupNames,int * NumberOfGroups) {

    Free((void **)&(GroupNames[GroupNumber]));
    while (GroupNumber < *NumberOfGroups - 1) {
        GroupNames[GroupNumber] = GroupNames[GroupNumber+1];
        GroupNumber++;
    }
    (*NumberOfGroups)--;
}
//-------------------------------------------------------------------------------------------------
void EndAllGroups(GroupNamesType GroupNames,int * NumberOfGroups) {

    while (*NumberOfGroups > 0) {
        DoEndGroup(*NumberOfGroups - 1,GroupNames,NumberOfGroups);
    }
}
//-------------------------------------------------------------------------------------------------
int TPIInput(OptionsType Options,char * CommandName,FORMULA CommandDetails,char * FileName,
LISTNODE * LogicalFormulae,LISTNODE ** AddLogicalHere,SIGNATURE Signature,
GroupNamesType GroupNames,int * NumberOfGroups) {

    int Continue;
    int MallocedFileName;
    char * GroupName;
    int ThisGroupNumber;

    if (FileName == NULL) {
        CheckCommandDetailsType(CommandName,tpi_execute,CommandDetails,atom,0);
//----Look for equality
        if (!strcmp(GetSymbol(CommandDetails->FormulaUnion.Atom),"=")) {
            GetCommandDetailsEqualityAtoms(CommandName,tpi_input,CommandDetails,&GroupName,
&FileName);
//DEBUG printf("Input group and file %s %s\n",GroupName,FileName);
        } else {
            GroupName = NULL;
            FileName = GetCommandDetailsAtom(CommandDetails);
//DEBUG printf("Input file %s\n",FileName);
        }
        MallocedFileName = 1;
    } else {
        MallocedFileName = 0;
    }
    if (GroupName != NULL) {
//DEBUG printf("Start group %s\n",GroupName);
        DoStartGroup(GroupName,GroupNames,NumberOfGroups);
        ThisGroupNumber = (*NumberOfGroups) - 1;
    }
    Continue = Interpret(Options,FileName,LogicalFormulae,AddLogicalHere,
Signature,"all",GroupNames,NumberOfGroups);
    if (GroupName != NULL) {
//DEBUG printf("End group %s\n",GroupNames[*NumberOfGroups - 1]);
        DoEndGroup(ThisGroupNumber,GroupNames,NumberOfGroups);
    }
    if (MallocedFileName) {
        Free((void **)&FileName);
    }
    return(Continue);
}
//-------------------------------------------------------------------------------------------------
void TPIOutput(char * CommandName,FORMULA CommandDetails,LISTNODE LogicalFormulae,
SIGNATURE Signature) {

    LISTNODE LogicalFormulaeToPrint;
    char * OutputFileName;
    char * GroupToOutput;
    int GroupNameMalloced;
    FILE * OutputHandle;

    CheckCommandDetailsType(CommandName,tpi_output,CommandDetails,atom,0);
//----Look for equality for group
    if (!strcmp(GetSymbol(CommandDetails->FormulaUnion.Atom),"=")) {
        GetCommandDetailsEqualityAtoms(CommandName,tpi_output,CommandDetails,&OutputFileName,
&GroupToOutput);
        GroupNameMalloced = 1;
    } else {
        GroupToOutput = "tpi";
        GroupNameMalloced = 0;
        OutputFileName = GetCommandDetailsAtom(CommandDetails);
    }
    if (strlen(OutputFileName) == 0 || strlen(GroupToOutput) == 0) {
        CommandDetailsError(CommandName,tpi_output,CommandDetails);
    }

    LogicalFormulaeToPrint = GetListOfActiveLogicalFormulaeInGroups(LogicalFormulae,GroupToOutput);
    if (!strcmp(OutputFileName,"stdout")) {
        PrintListOfAnnotatedTSTPNodes(stdout,Signature,LogicalFormulaeToPrint,tptp,1);
    } else {
        if ((OutputHandle = fopen(OutputFileName,"w")) == NULL) {
            printf("ERROR: Cannot open output file %s\n",OutputFileName);
            exit_SZS_NoSuccess();
        }
        PrintListOfAnnotatedTSTPNodes(OutputHandle,Signature,LogicalFormulaeToPrint,tptp,1);
        fclose(OutputHandle);
    }
    FreeListOfAnnotatedFormulae(&LogicalFormulaeToPrint,Signature);
    Free((void **)&OutputFileName);
    if (GroupNameMalloced) {
        Free((void **)&GroupToOutput);
    }
}
//-------------------------------------------------------------------------------------------------
void TPIActivate(char * CommandName,FORMULA CommandDetails,LISTNODE LogicalFormulae,
SIGNATURE Signature) {

    SetTPIStateForCommand(CommandName,tpi_activate,CommandDetails,LogicalFormulae,Signature,
"active");
}
//-------------------------------------------------------------------------------------------------
void TPIDeactivate(char * CommandName,FORMULA CommandDetails,LISTNODE LogicalFormulae,
SIGNATURE Signature) {

    SetTPIStateForCommand(CommandName,tpi_deactivate,CommandDetails,LogicalFormulae,Signature,
"inactive");
}
//-------------------------------------------------------------------------------------------------
void TPIDelete(char * CommandName,FORMULA CommandDetails,LISTNODE * LogicalFormulae,
SIGNATURE Signature,LISTNODE ** AddLogicalHere) {

    LISTNODE * NodePointer;
    char * FormulaName;

    CheckCommandDetailsType(CommandName,tpi_delete,CommandDetails,atom,1);
    FormulaName = GetCommandDetailsAtom(CommandDetails);
    if ((NodePointer = GetNodeFromListByAnnotatedFormulaName(LogicalFormulae, FormulaName)) != 
NULL) {
        if (*AddLogicalHere == &((*NodePointer)->Next)) {
            *AddLogicalHere = NodePointer;
        }
        FreeAListNode(NodePointer,Signature);
    } else {
        printf("ERROR: Cannot delete non-existent formula %s\n",FormulaName);
        exit_SZS_NoSuccess();
    }
}
//-------------------------------------------------------------------------------------------------
void TPISetRole(char * CommandName,FORMULA CommandDetails,LISTNODE LogicalFormulae,
SIGNATURE Signature) {

    char * FormulaName;
    char * NewRoleString;
    ANNOTATEDFORMULA AnnotatedFormula;
    StatusType NewRole;

    if (CommandDetails->Type != atom || strcmp(GetSymbol(CommandDetails->FormulaUnion.Atom),"=")) {
        CommandDetailsError(CommandName,tpi_set_role,CommandDetails);
    }
    GetCommandDetailsEqualityAtoms(CommandName,tpi_set_role,CommandDetails,&FormulaName,
&NewRoleString);
    if ((AnnotatedFormula = GetAnnotatedFormulaFromListByName(LogicalFormulae,
FormulaName)) == NULL || 
(NewRole = StringToStatus(NewRoleString)) == nonstatus ||
!SetStatus(AnnotatedFormula,NewRole,NULL)) {
        CommandDetailsError(CommandName,tpi_set_role,CommandDetails);
    }
    Free((void **)&FormulaName);
    Free((void **)&NewRoleString);
}
//-------------------------------------------------------------------------------------------------
void TPIStartGroup(char * CommandName,FORMULA CommandDetails,
GroupNamesType GroupNames,int * NumberOfGroups) {

    char * StartedGroupName;

    CheckCommandDetailsType(CommandName,tpi_start_group,CommandDetails,atom,1);
    assert(*NumberOfGroups < MAX_GROUPS);
    StartedGroupName = GetCommandDetailsAtom(CommandDetails);
    DoStartGroup(StartedGroupName,GroupNames,NumberOfGroups);
}
//-------------------------------------------------------------------------------------------------
void TPIEndGroup(char * CommandName,FORMULA CommandDetails,
GroupNamesType GroupNames,int * NumberOfGroups) {

    char * EndedGroupName;
    int GroupNumber;

    CheckCommandDetailsType(CommandName,tpi_end_group,CommandDetails,atom,1);
    EndedGroupName = GetCommandDetailsAtom(CommandDetails);
    if ((GroupNumber = FindGroupNumber(EndedGroupName,GroupNames,*NumberOfGroups)) >= 0) {
        DoEndGroup(GroupNumber,GroupNames,NumberOfGroups);
        Free((void **)&EndedGroupName);
    } else {
        Free((void **)&EndedGroupName);
        printf("ERROR: Ended unstarted group %s\n",EndedGroupName);
        exit_SZS_NoSuccess();
    }
}
//-------------------------------------------------------------------------------------------------
void TPIActivateGroup(char * CommandName,FORMULA CommandDetails,LISTNODE * LogicalFormulae,
SIGNATURE Signature) {

    SetTPIStateForGroup(CommandName,tpi_activate_group,CommandDetails,*LogicalFormulae,Signature,
"active");
}
//-------------------------------------------------------------------------------------------------
void TPIDeactivateGroup(char * CommandName,FORMULA CommandDetails,LISTNODE * LogicalFormulae,
SIGNATURE Signature) {

    SetTPIStateForGroup(CommandName,tpi_deactivate_group,CommandDetails,*LogicalFormulae,Signature,
"inactive");
}
//-------------------------------------------------------------------------------------------------
void TPIDeleteGroup(char * CommandName,FORMULA CommandDetails,char * GroupName,
LISTNODE * LogicalFormulae,SIGNATURE Signature,LISTNODE ** AddLogicalHere) {

    int MallocedGroupName;

    if (GroupName == NULL) {
        CheckCommandDetailsType(CommandName,tpi_delete_group,CommandDetails,atom,1);
        GroupName = GetCommandDetailsAtom(CommandDetails);
        MallocedGroupName = 1;
    } else {
        MallocedGroupName = 0;
    }
    if (!strcmp(GroupName,"tpi")) {
        FreeListOfAnnotatedFormulae(LogicalFormulae,Signature);
        *AddLogicalHere = LogicalFormulae;
    } else {
        while (*LogicalFormulae != NULL) {
            if (LogicalFormulaInGroup(*LogicalFormulae,GroupName)) {
                if (*AddLogicalHere == &((*LogicalFormulae)->Next)) {
                    *AddLogicalHere = LogicalFormulae;
                }
                FreeAListNode(LogicalFormulae,Signature);
            } else {
                LogicalFormulae = &((*LogicalFormulae)->Next);
            }
        }
    }
    if (MallocedGroupName) {
        Free((void **)&GroupName);
    }
}
//-------------------------------------------------------------------------------------------------
void TPISetenv(char * CommandName,FORMULA CommandDetails) {

    char * EnvironmentVariable;
    char * EnvironmentVariableValue;

    if (CommandDetails->Type != atom || strcmp(GetSymbol(CommandDetails->FormulaUnion.Atom),"=")) {
        CommandDetailsError(CommandName,tpi_setenv,CommandDetails);
    }
    GetCommandDetailsEqualityAtoms(CommandName,tpi_setenv,CommandDetails,&EnvironmentVariable,
&EnvironmentVariableValue);
    if (strlen(EnvironmentVariable) == 0) {
        CommandDetailsError(CommandName,tpi_setenv,CommandDetails);
    }
    setenv(EnvironmentVariable,EnvironmentVariableValue,1);
    Free((void **)&EnvironmentVariable);
    Free((void **)&EnvironmentVariableValue);
}
//-------------------------------------------------------------------------------------------------
void TPIWaitenv(char * CommandName,FORMULA CommandDetails) {

    char * EnvironmentVariables[MAX_WAITENV_VARIABLES];
    int NumberOfWaitenvVariables;
    int NeedToWait;
    int Index;

    NumberOfWaitenvVariables = 0;
    while (CommandDetails->Type == binary) {
        CheckCommandDetailsType(CommandName,tpi_waitenv,
CommandDetails->FormulaUnion.BinaryFormula.LHS,atom,1);
        EnvironmentVariables[NumberOfWaitenvVariables] = 
GetCommandDetailsAtom(CommandDetails->FormulaUnion.BinaryFormula.LHS);
        CommandDetails = CommandDetails->FormulaUnion.BinaryFormula.RHS;
        NumberOfWaitenvVariables++;
    }
    CheckCommandDetailsType(CommandName,tpi_waitenv,CommandDetails,atom,1);
    EnvironmentVariables[NumberOfWaitenvVariables] = GetCommandDetailsAtom(CommandDetails);
    NumberOfWaitenvVariables++;

    NeedToWait = 1;
    while (NeedToWait) {
        for (Index = 0; NeedToWait && Index < NumberOfWaitenvVariables;Index++) {
            if (getenv(EnvironmentVariables[Index]) != NULL) {
                NeedToWait = 0;
            }
        }
        if (NeedToWait) {
            sleep(1);
        }
    }

    while (--NumberOfWaitenvVariables >= 0) {
        Free((void **)&(EnvironmentVariables[NumberOfWaitenvVariables]));
    }
}
//-------------------------------------------------------------------------------------------------
void TPIUnsetenv(char * CommandName,FORMULA CommandDetails) {

    char * EnvironmentVariable;

    CheckCommandDetailsType(CommandName,tpi_unsetenv,CommandDetails,atom,1);
    EnvironmentVariable = GetCommandDetailsAtom(CommandDetails);
    unsetenv(EnvironmentVariable);
    Free((void **)&EnvironmentVariable);
}
//-------------------------------------------------------------------------------------------------
//----Groups contains a comma separated list of group names to write to a
//----temporary file, whose name gets stored in FileName. Note this inserts
//----\0 into Groups, i.e., it's destructive.
void WriteActiveLogicalFormulaeToFile(SIGNATURE Signature,LISTNODE LogicalFormulae,char * Groups,
char * FileName) {

    extern TemporaryFileNamesArray MktempFileNames;
    extern int NumberOfTemporaryFileNames;
    LISTNODE LogicalFormulaeInGroups;

    LogicalFormulaeInGroups = GetListOfActiveLogicalFormulaeInGroups(
LogicalFormulae,Groups);
//----Save formulae to file
    if (MakeProblemFile(TEMP_DIRECTORY,TEMP_TEMPLATE,NULL,FileName,
LogicalFormulaeInGroups,nonstatus,NULL,nonstatus)) {
//----Add to list of files to delete at exit
        if (NumberOfTemporaryFileNames == MAX_TEMPORARY_FILENAMES) {
            printf("ERROR: No more space for storing temporary file names\n");
            exit_SZS_NoSuccess();
        }
        strcpy(MktempFileNames[NumberOfTemporaryFileNames],FileName);
        NumberOfTemporaryFileNames++;
        FreeListOfAnnotatedFormulae(&LogicalFormulaeInGroups,Signature);
    } else {
        printf("ERROR: Could not write logical formulae to file\n");
        exit_SZS_NoSuccess();
    }
}
//-------------------------------------------------------------------------------------------------
//----Replace $getgroups commands in ExecuteCommand by names of files
//----containing the formulae. If GropsUsed is not null, record their names.
void ReplaceLogicalFormulaeGroups(SIGNATURE Signature,LISTNODE LogicalFormulae,
char * ExecuteCommand,char * GroupsUsed,char * CommandName) {

    char * GetGroups;
    char * Groups;
    char * Close;
    String FileName;
    String Suffix;

    if (GroupsUsed != NULL) {
        strcpy(GroupsUsed,"");
    }
    while ((GetGroups = strstr(ExecuteCommand,"$getgroups(")) != NULL) {
        Groups = GetGroups + strlen("$getgroups(");
        if ((Close = strchr(Groups,')')) == NULL) {
            printf("ERROR: Could not find groups in %s of command %s\n",
GetGroups,CommandName);
            exit_SZS_NoSuccess();
        }
        *GetGroups = '\0';
        *Close = '\0';
        strcpy(Suffix,++Close);
        
        if (GroupsUsed != NULL) {
            if (strlen(GroupsUsed) > 0) {
                strcat(GroupsUsed,",");
            }
            strcat(GroupsUsed,Groups);
        }
        WriteActiveLogicalFormulaeToFile(Signature,LogicalFormulae,Groups,FileName);
        ExecuteCommand = (char *)Realloc(ExecuteCommand,
strlen(ExecuteCommand)+strlen(FileName)+strlen(Close)+1);
        strcat(ExecuteCommand,FileName);
        strcat(ExecuteCommand,Suffix);
    }
}
//-------------------------------------------------------------------------------------------------
void TPIExecute(OptionsType Options,char * CommandName,FORMULA CommandDetails,
SIGNATURE Signature,LISTNODE LogicalFormulae,char * FilterOutputFileName,char * GroupsUsed,
pthread_mutex_t * ThreadMutex,pthread_cond_t * ThreadCondition) {

    char * EnvironmentVariable;
    char * ExecuteCommand;
    String FileName;
    FILE * ProcessHandle;
    String OutputLine;
    char * SubstringPosition;
    char * NextSubstringPosition;
    String SZSResultStatus;
    String SZSOutputStatus;
    int TimeLimit;
    int Quietness;
    int KeepOutputFile;
    String OutputFileName;

    strcpy(FileName,"");

    if (CommandDetails == NULL) {
        printf("ERROR: \"execute,self\" is not available in TPII\n");
        exit_SZS_NoSuccess();
        ExecuteCommand = (char *)Malloc(5);
        strcpy(ExecuteCommand,"self");
    } else {
        CheckCommandDetailsType(CommandName,tpi_execute,CommandDetails,atom,0);
//----Look for equality for environment variable
        if (!strcmp(GetSymbol(CommandDetails->FormulaUnion.Atom),"=")) {
            GetCommandDetailsEqualityAtoms(CommandName,tpi_execute,
CommandDetails,&EnvironmentVariable,&ExecuteCommand);
            if (strlen(EnvironmentVariable) == 0) {
                CommandDetailsError(CommandName,tpi_execute,CommandDetails);
            }
            strcpy(SZSResultStatus,"Unknown");
            strcpy(SZSOutputStatus,"None");
        } else {
            EnvironmentVariable = NULL;
            ExecuteCommand = GetCommandDetailsAtom(CommandDetails);
        }
    }

//----If a SystemOnTPTP format system, do that
    if (strchr(ExecuteCommand,'/') == NULL && 
strstr(ExecuteCommand,"---") != NULL) {
//----Check there's a space (which will have the time limit after)
        if ((SubstringPosition = strchr(ExecuteCommand,' ')) == NULL) {
            CommandDetailsError(CommandName,tpi_execute,CommandDetails);
        }
        *SubstringPosition = '\0';
        SubstringPosition++;
//----Next should be the $getgroups for the problem file. Only one allowed
//----in SystemOnTPTP case.
        if ((NextSubstringPosition = strchr(SubstringPosition,' ')) == NULL) {
            CommandDetailsError(CommandName,tpi_execute,CommandDetails);
        }
        *NextSubstringPosition = '\0';
        NextSubstringPosition++;
//----Check there is a time limit
        if ((TimeLimit = atoi(SubstringPosition)) == 0) {
            CommandDetailsError(CommandName,tpi_execute,CommandDetails);
        }
//----Check there is a $getgroups
        if ((SubstringPosition = strstr(NextSubstringPosition,"$getgroups(")) 
== NULL) {
            CommandDetailsError(CommandName,tpi_execute,CommandDetails);
        }
        SubstringPosition += strlen("$getgroups(");
        if ((NextSubstringPosition = strchr(SubstringPosition,')')) == NULL) {
            CommandDetailsError(CommandName,tpi_execute,CommandDetails);
        }
        *NextSubstringPosition = '\0';
//----Save groups used if needed, as for filter
        if (GroupsUsed != NULL) {
            strcpy(GroupsUsed,SubstringPosition);
        }
//----All is well, output logical formulae to file
        WriteActiveLogicalFormulaeToFile(Signature,LogicalFormulae,SubstringPosition,FileName);
//----Decide where to send output, stdout or FilterOutputFileName
        KeepOutputFile = Options.Quietness < 2;
        strcpy(OutputFileName,"stdout");
        Quietness = Options.Quietness;
        if (FilterOutputFileName != NULL) {
            strcpy(OutputFileName,FilterOutputFileName);
            KeepOutputFile = 1;
            Quietness = -1;
        } 

//----If doing an execute_async, release the main thread
        if (ThreadMutex != NULL && ThreadCondition != NULL) {
            pthread_mutex_lock(ThreadMutex);
            pthread_cond_signal(ThreadCondition);
            pthread_mutex_unlock(ThreadMutex);
        }
        SystemOnTPTPGetResult(Quietness,FileName,ExecuteCommand,TimeLimit,
"",NULL,"",KeepOutputFile,NULL,OutputFileName,NULL,SZSResultStatus,
SZSOutputStatus,1);
    } else {
//----Otherwise do directly. Replace $getgroups terms.
        ReplaceLogicalFormulaeGroups(Signature,LogicalFormulae,ExecuteCommand,
GroupsUsed,CommandName);
//----If there is a FilterOutputFileName then output is redirected to that
        if (FilterOutputFileName != NULL) {
            ExecuteCommand = (char *)Realloc(ExecuteCommand,
strlen(ExecuteCommand) + strlen(FilterOutputFileName) + 4);
            strcat(ExecuteCommand," > ");
            strcat(ExecuteCommand,FilterOutputFileName);
        }
        if ((ProcessHandle = popen(ExecuteCommand,"r")) == NULL) {
            printf("ERROR: Could not execute %s\n",ExecuteCommand);
            exit_SZS_NoSuccess();
        }
//----If this is in a new thread, release the condition variable
        if (ThreadMutex != NULL && ThreadCondition != NULL) {
            pthread_mutex_lock(ThreadMutex);
            pthread_cond_signal(ThreadCondition);
            pthread_mutex_unlock(ThreadMutex);
        }
//----Watch the stdout from the process
        while (fgets(OutputLine,STRINGLENGTH,ProcessHandle) != NULL) {
//----Look for SZS status if needed
            if (EnvironmentVariable != NULL && 
!strcmp(SZSResultStatus,"Unknown") && 
(SubstringPosition = strstr(OutputLine,"SZS status")) != NULL) {
                strcpy(SZSResultStatus,
SubstringPosition+strlen("SZS status")+1);
                if ((SubstringPosition = strchr(SZSResultStatus,' ')) != NULL) {
                    *SubstringPosition = '\0';
                }
            }
            fputs(OutputLine,stdout);
        }
        pclose(ProcessHandle);
    }
    if (strlen(FileName) > 0) {
        RemoveFile(FileName);
    }
    if (EnvironmentVariable != NULL) {
        setenv(EnvironmentVariable,SZSResultStatus,1);
        Free((void **)&EnvironmentVariable);
    }
    Free((void **)&ExecuteCommand);
}
//-------------------------------------------------------------------------------------------------
void * ExecuteThread(void * ThreadData) {

    ExecuteDataType * ExecuteData;
    
    ExecuteData = (ExecuteDataType *)ThreadData;

    TPIExecute((OptionsType)ExecuteData->Options,
(char *)ExecuteData->CommandName,
(FORMULA)ExecuteData->CommandDetails,
(SIGNATURE)ExecuteData->Signature,
(LISTNODE)ExecuteData->LogicalFormulae,NULL,NULL,
(pthread_mutex_t *)ExecuteData->ThreadMutex,
(pthread_cond_t *)ExecuteData->ThreadCondition);

    Free(&ThreadData);
    return(NULL);
}
//-------------------------------------------------------------------------------------------------
void TPIExecuteAsync(OptionsType Options,char * CommandName,FORMULA CommandDetails,
SIGNATURE Signature,LISTNODE LogicalFormulae) {

    pthread_t AsyncThread;
    pthread_mutex_t ThreadMutex;
    pthread_cond_t ThreadCondition;
    ExecuteDataType * ExecuteData;

    pthread_mutex_init(&ThreadMutex,NULL);
    pthread_cond_init(&ThreadCondition,NULL);

    ExecuteData = (ExecuteDataType *)Malloc(sizeof(ExecuteDataType));
    ExecuteData->Options = Options;
    ExecuteData->CommandName = CommandName;
    ExecuteData->CommandDetails = CommandDetails;
    ExecuteData->Signature = Signature;
    ExecuteData->LogicalFormulae = LogicalFormulae;
    ExecuteData->ThreadMutex = &ThreadMutex;
    ExecuteData->ThreadCondition = &ThreadCondition;

//----Lock the mutex so the async thread can't signal the condition variable
//----before this thread gets to wait (below).
    pthread_mutex_lock(&ThreadMutex);
    if (pthread_create(&AsyncThread,NULL,ExecuteThread,ExecuteData) != 0) {
        printf("ERROR: Could not start thread for TPI command %s,%s - ",
CommandName,StatusToString(tpi_execute_async));
        exit_SZS_NoSuccess();
    }
    if (pthread_detach(AsyncThread) != 0) {
        printf("ERROR: Could not detach thread for TPI command %s,%s - ",
CommandName,StatusToString(tpi_execute_async));
        exit_SZS_NoSuccess();
    }
    pthread_cond_wait(&ThreadCondition,&ThreadMutex);
    pthread_mutex_unlock(&ThreadMutex);
}
//-------------------------------------------------------------------------------------------------
void TPIWrite(char * CommandName,FORMULA ToWrite) {

    char * ToWriteAtom;

    if (ToWrite->Type == atom) {
        ToWriteAtom = GetCommandDetailsAtom(ToWrite);
        printf("%s",ToWriteAtom);
        Free((void **)&ToWriteAtom);
    } else {
        CheckCommandDetailsType(CommandName,tpi_write,ToWrite,binary,0);
        TPIWrite(CommandName,ToWrite->FormulaUnion.BinaryFormula.LHS);
        printf(" ");
        TPIWrite(CommandName,ToWrite->FormulaUnion.BinaryFormula.RHS);
    }
}
//-------------------------------------------------------------------------------------------------
char * TPIMktemp(char * CommandName,FORMULA CommandDetails) {

    char * EnvironmentVariable;
    int Handle;
    extern TemporaryFileNamesArray MktempFileNames;
    extern int NumberOfTemporaryFileNames;

    if (NumberOfTemporaryFileNames == MAX_TEMPORARY_FILENAMES) {
        printf("ERROR: No more space for storing temporary file names\n");
        exit_SZS_NoSuccess();
    }
    if (CommandDetails != NULL) {
        CheckCommandDetailsType(CommandName,tpi_mktemp,CommandDetails,atom,1);
        EnvironmentVariable = GetCommandDetailsAtom(CommandDetails);
    } else {
        EnvironmentVariable = NULL;
    }
    strcpy(MktempFileNames[NumberOfTemporaryFileNames],TEMP_DIRECTORY);
    strcat(MktempFileNames[NumberOfTemporaryFileNames],"/");
    strcat(MktempFileNames[NumberOfTemporaryFileNames],TEMP_TEMPLATE);
    if ((Handle = mkstemp(MktempFileNames[NumberOfTemporaryFileNames])) == -1) {
        printf("ERROR: Could not create temporary file name\n");
        exit_SZS_NoSuccess();
        return(NULL);
    }
    close(Handle);
    NumberOfTemporaryFileNames++;
    if (EnvironmentVariable != NULL) {
        setenv(EnvironmentVariable,MktempFileNames[NumberOfTemporaryFileNames],
1);
        Free((void **)&EnvironmentVariable);
    }
    return(MktempFileNames[NumberOfTemporaryFileNames-1]);
}
//-------------------------------------------------------------------------------------------------
int TPIAssert(char * CommandName,FORMULA Assertion) {

    FORMULA PositiveAssertion;
    char * LHS;
    char * RHS;
    int AssertionTrue;

    if (Assertion->Type == unary) {
        PositiveAssertion = Assertion->FormulaUnion.UnaryFormula.Formula;
    } else {
        PositiveAssertion = Assertion;
    }

    if (PositiveAssertion->Type != atom ||
strcmp(GetSymbol(PositiveAssertion->FormulaUnion.Atom),"=")) {
        CommandDetailsError(CommandName,tpi_assert,Assertion);
    }
    GetCommandDetailsEqualityAtoms(CommandName,tpi_assert,PositiveAssertion,
&LHS,&RHS);
    AssertionTrue = !strcmp(LHS,RHS);
    if (PositiveAssertion != Assertion) {
        AssertionTrue = !AssertionTrue;
    }
    Free((void **)&LHS);
    Free((void **)&RHS);

    if (!AssertionTrue) {
        printf("%% Assertion failed at TPI command %s - ",CommandName);
        PrintTSTPFormula(stdout,tptp,Assertion,0,0,none,1);
        printf("\n");
        return(EXIT_FAILURE);
    } else {
        return(EXIT_SUCCESS);
    }
}
//-------------------------------------------------------------------------------------------------
int TPIClean(char * CommandName,FORMULA CommandDetails) {

    if (strcmp(GetSymbol(CommandDetails->FormulaUnion.Atom),"clean")) {
        CommandDetailsError(CommandName,tpi_clean,CommandDetails);
    }
    DeleteTemporaryFiles();
    return(EXIT_SUCCESS);
}
//-------------------------------------------------------------------------------------------------
int TPIExit(char * CommandName,FORMULA ExitCode) {

    if (strcmp(GetSymbol(ExitCode->FormulaUnion.Atom),"exit")) {
        CommandDetailsError(CommandName,tpi_exit,ExitCode);
    }
    if (GetArity(ExitCode->FormulaUnion.Atom) == 1) {
        return(atoi(GetSymbol(ExitCode->FormulaUnion.Atom->Arguments[0])));
    } else {
        return(EXIT_SUCCESS);
    }
}
//-------------------------------------------------------------------------------------------------
void TPIFilter(OptionsType Options,char * CommandName,FORMULA CommandDetails,
LISTNODE * LogicalFormulae,SIGNATURE Signature,LISTNODE ** AddLogicalHere,
GroupNamesType GroupNames,int * NumberOfGroups) {

    char * FilterOutputFileName;
    String GroupsUsed;
    char * GroupName;

    FilterOutputFileName = TPIMktemp(CommandName,NULL);
    TPIExecute(Options,CommandName,CommandDetails,Signature,*LogicalFormulae,FilterOutputFileName,
GroupsUsed,NULL,NULL);
    GroupName = strtok(GroupsUsed,",");
    while (GroupName != NULL) {
        Trim(GroupName);
        TPIDeleteGroup(CommandName,NULL,GroupName,LogicalFormulae,Signature,AddLogicalHere);
        GroupName = strtok(NULL,",");
    }
    TPIInput(Options,CommandName,NULL,FilterOutputFileName,LogicalFormulae,
AddLogicalHere,Signature,GroupNames,NumberOfGroups);
}
//-------------------------------------------------------------------------------------------------
void TPIGenerate(OptionsType Options,char * CommandName,FORMULA CommandDetails,
LISTNODE * LogicalFormulae,SIGNATURE Signature,LISTNODE ** AddLogicalHere,
GroupNamesType GroupNames,int * NumberOfGroups) {

    char * GenerateOutputFileName;

    GenerateOutputFileName = TPIMktemp(CommandName,NULL);
    TPIExecute(Options,CommandName,CommandDetails,Signature,*LogicalFormulae,
GenerateOutputFileName,NULL,NULL,NULL);
    TPIInput(Options,CommandName,NULL,GenerateOutputFileName,LogicalFormulae,AddLogicalHere,
Signature,GroupNames,NumberOfGroups);
}
//-------------------------------------------------------------------------------------------------
int InterpretCommand(OptionsType Options,ANNOTATEDFORMULA AnnotatedFormula,
LISTNODE * LogicalFormulae,LISTNODE ** AddLogicalHere,SIGNATURE Signature,
GroupNamesType GroupNames,int * NumberOfGroups) {

    char * CommandName;
    StatusType Command;
    FORMULA CommandDetails;
    int Continue;
    extern int ExitSuccessValue;

    Continue = 1;
    CommandName = GetName(AnnotatedFormula,NULL);
    Command = AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Status;
    CommandDetails = AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula;

//DEBUG PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,0);

//----Go directly because GetRole does not do it for TPI
    switch (Command) {
        case tpi_input:
            Continue = TPIInput(Options,CommandName,CommandDetails,NULL,
LogicalFormulae,AddLogicalHere,Signature,GroupNames,NumberOfGroups);
            break;
        case tpi_output:
            TPIOutput(CommandName,CommandDetails,*LogicalFormulae,Signature);
            break;
        case tpi_activate:
            TPIActivate(CommandName,CommandDetails,*LogicalFormulae,Signature);
            break;
        case tpi_deactivate:
            TPIDeactivate(CommandName,CommandDetails,*LogicalFormulae,
Signature);
            break;
        case tpi_delete:
            TPIDelete(CommandName,CommandDetails,LogicalFormulae,Signature,
AddLogicalHere);
        case tpi_set_role:
            TPISetRole(CommandName,CommandDetails,*LogicalFormulae,Signature);
            break;
        case tpi_start_group:
            TPIStartGroup(CommandName,CommandDetails,GroupNames,NumberOfGroups);
            break;
        case tpi_end_group:
            TPIEndGroup(CommandName,CommandDetails,GroupNames,NumberOfGroups);
            break;
        case tpi_activate_group:
            TPIActivateGroup(CommandName,CommandDetails,LogicalFormulae,
Signature);
            break;
        case tpi_deactivate_group:
            TPIDeactivateGroup(CommandName,CommandDetails,LogicalFormulae,
Signature);
            break;
        case tpi_delete_group:
            TPIDeleteGroup(CommandName,CommandDetails,NULL,LogicalFormulae,
Signature,AddLogicalHere);
            break;
        case tpi_setenv:
            TPISetenv(CommandName,CommandDetails);
            break;
        case tpi_waitenv:
            TPIWaitenv(CommandName,CommandDetails);
            break;
        case tpi_unsetenv:
            TPIUnsetenv(CommandName,CommandDetails);
            break;
        case tpi_set_logic:
            break;
        case tpi_execute:
            TPIExecute(Options,CommandName,CommandDetails,Signature,*LogicalFormulae,
NULL,NULL,NULL,NULL);
            break;
        case tpi_execute_async:
            TPIExecuteAsync(Options,CommandName,CommandDetails,Signature,*LogicalFormulae);
            break;
        case tpi_filter:
            TPIFilter(Options,CommandName,CommandDetails,LogicalFormulae,
Signature,AddLogicalHere,GroupNames,NumberOfGroups);
            break;
        case tpi_generate:
            TPIGenerate(Options,CommandName,CommandDetails,LogicalFormulae,
Signature,AddLogicalHere,GroupNames,NumberOfGroups);
            break;
        case tpi_mktemp:
            TPIMktemp(CommandName,CommandDetails);
            break;
        case tpi_assert:
            if ((ExitSuccessValue = TPIAssert(CommandName,CommandDetails)) ==
EXIT_FAILURE) {
                Continue = 0;
            }
            break;
        case tpi_write:
            TPIWrite(CommandName,CommandDetails);
            printf("\n");
            break;
        case tpi_exit:
            ExitSuccessValue = TPIExit(CommandName,CommandDetails);
            Continue = 0;
            break;
        default:
            printf("ERROR: Unknown TPI command\n");
            exit_SZS_NoSuccess();
            break;
    }
    return(Continue);
}
//-------------------------------------------------------------------------------------------------
void AddGroupTags(ANNOTATEDFORMULA AnnotatedFormula,SIGNATURE Signature,
GroupNamesType GroupNames,int NumberOfGroups) {

    int GroupNumber;
    String GroupTag;

    for (GroupNumber = 0; GroupNumber < NumberOfGroups; GroupNumber++) {
        sprintf(GroupTag,"tpi_group(%s)",GroupNames[GroupNumber]);
        AddUsefulInformationToAnnotatedFormula(AnnotatedFormula,Signature,
GroupTag);
    }
}
//-------------------------------------------------------------------------------------------------
int Interpret(OptionsType Options,char * FileName,LISTNODE * LogicalFormulae,
LISTNODE ** AddLogicalHere,SIGNATURE Signature,char * IncludeFilter,GroupNamesType GroupNames,
int * NumberOfGroups) {

    ANNOTATEDFORMULA AnnotatedFormula;
    READFILE InputStream; 
    SyntaxType ThisNodeType;
    String NewIncludeFile;
    String NewIncludeFilter;
    int Continue;
    extern int GlobalQUIT;

    Continue = 1;
    if ((InputStream = OpenInputREADFILE(Options,FileName)) != NULL) {
        NextToken(InputStream);
//----Reading formulae one-by-one
        while (!GlobalQUIT && Continue && !CheckTokenType(InputStream,endeof)) {
            AnnotatedFormula = ParseAnnotatedFormula(InputStream,Signature);
            ThisNodeType = GetSyntax(AnnotatedFormula);
            if (ThisNodeType == include) {
                GetIncludeParts(AnnotatedFormula,NewIncludeFile,
NewIncludeFilter);
                FreeTerm(&(AnnotatedFormula->AnnotatedFormulaUnion.Include),Signature,NULL);
                Free((void **)&AnnotatedFormula);
                Continue = Interpret(Options,NewIncludeFile,LogicalFormulae,
AddLogicalHere,Signature,NewIncludeFilter,GroupNames,NumberOfGroups);
            } else if (LogicalAnnotatedFormula(AnnotatedFormula)) {
//----Need to add group tags here
                AddGroupTags(AnnotatedFormula,Signature,GroupNames,
*NumberOfGroups);
                SetTPIState(AnnotatedFormula,Signature,"active");
                AddListNode(*AddLogicalHere,NULL,AnnotatedFormula);
                *AddLogicalHere = &((**AddLogicalHere)->Next);
            } else if (ThisNodeType == tptp_tpi) {
//DEBUG printf("NEED TO INTERPRET\n");
//DEBUG PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,0);
//DEBUG printf("FOR LIST\n");
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,*LogicalFormulae,tptp,1);
//DEBUG printf("END OF FOR LIST\n");
//DEBUG fflush(stdout);
                Continue = InterpretCommand(Options,AnnotatedFormula,
LogicalFormulae,AddLogicalHere,Signature,GroupNames,NumberOfGroups);
                FreeAnnotatedTSTPFormula(&AnnotatedFormula,Signature);
            } else {
                CodingError("Unknown syntax for TPII\n");
                exit_SZS_NoSuccess();
            }
        }
        CloseReadFile(InputStream);
    } else {
        exit_SZS_NoSuccess();
    }
    return(Continue);
}
//-------------------------------------------------------------------------------------------------
void SIGQUITHandler(int Signal) {

    extern int GlobalQUIT;
    
    GlobalQUIT = 1;
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    OptionsType Options;
    int ArgvFileIndex;
    String FileName;
    LISTNODE LogicalFormulae;
    LISTNODE * AddLogicalHere;
    SIGNATURE Signature;
    GroupNamesType GroupNames;
    int NumberOfGroups;
    int Continue;
    extern int ExitSuccessValue;
    extern TemporaryFileNamesArray MktempFileNames;
    extern int NumberOfTemporaryFileNames;
    extern char ** FirstArgument;
    extern int NumberOfArguments;
    extern int GlobalQUIT;

    ArgvFileIndex = ProcessCommandLine(argc,argv,&Options);

    SetNeedForNonLogicTokens(0);
    SetAllowFreeVariables(0);
    LogicalFormulae = NULL;
    Signature = NewSignature();
    NumberOfGroups = 0;
    Continue = 1;
    AddLogicalHere = &LogicalFormulae;
    NumberOfTemporaryFileNames = 0;
    ExitSuccessValue = 0;
    FirstArgument = NULL;
    GlobalQUIT = 0;

    atexit(DeleteTemporaryFiles);
//----Set SIGQUITHandler
    if (signal(SIGQUIT,SIGQUITHandler) == SIG_ERR) {
        printf("ERROR: Could not set SIGQUIT handler\n");
        exit_SZS_NoSuccess();
    }

//----Do file on command line
    if (ArgvFileIndex < argc) {
        strcpy(FileName,argv[ArgvFileIndex++]);
        FirstArgument = &(argv[ArgvFileIndex]);
        NumberOfArguments = argc - ArgvFileIndex;
        Continue = Interpret(Options,FileName,&LogicalFormulae,&AddLogicalHere,Signature,"all",
GroupNames,&NumberOfGroups);
    }
//----If still going, do an execute,self
    if (!GlobalQUIT && Continue) {
        TPIExecute(Options,"implicit",NULL,Signature,LogicalFormulae,NULL,NULL,NULL,NULL);
    }
    FreeListOfAnnotatedFormulae(&LogicalFormulae,Signature);
    assert(LogicalFormulae == NULL);
//DEBUG PrintSignature(Signature);
//----Clean and delete the signature (should be empty here)
    FreeSignature(&Signature);
//----End any groups that the user forgot to end
    EndAllGroups(GroupNames,&NumberOfGroups);
    printf("%% SZS status Success\n");
    fflush(stdout);

    return(ExitSuccessValue);
}
//-------------------------------------------------------------------------------------------------
TemporaryFileNamesArray MktempFileNames;
int NumberOfTemporaryFileNames;
int ExitSuccessValue;
char ** FirstArgument;
int NumberOfArguments;
int GlobalQUIT;
//-------------------------------------------------------------------------------------------------

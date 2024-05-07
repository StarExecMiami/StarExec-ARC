#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "Modify.h"
#include "List.h"
#include "Statistics.h"
#include "ListStatistics.h"
#include "PrintTSTP.h"
#include "AddEquality.h"
#include "FOFify.h"
#include "Randomize.h"
#include "NumberNames.h"
#include "tptp4X.h"
//-------------------------------------------------------------------------------------------------
void ReformatFile(OptionsType Options,char * FileName,char * IncludeFilter,
char * IncludingFileName,int RemoveHeader,FILE * OutputHandle);
//-------------------------------------------------------------------------------------------------
//----Return the first index for files in argv
int ProcessCommandLine(int argc,char * argv[],OptionsType * Options) {

    int OptionChar;
    char * Colon;

    Options->Quietness = 1;
    strcpy(Options->OutputDirectory,"-");
    Options->Format = tptp;
    Options->Pretty = 1;
    Options->AllowFreeVariables = 0;
    Options->AllowDuplicateNames = 0;
    Options->ExpandIncludes = 0;
    Options->KeepNonLogicals = 1;
    Options->Warnings = 0;
    Options->SZSStatusReporting = 0;
    strcpy(Options->Transformations,"");
    Options->PrintDelayMin = 0;
    Options->PrintDelayMax = 0;
    Options->CPUTimeLimit = 0;
    Options->WCTimeLimit = 0;

    while ((OptionChar = getopt(argc,argv,"q:d:f:r:t:u:l:VNxcwzvh")) != -1) {
        switch (OptionChar) {
            case 'q':
                Options->Quietness = atoi(optarg);
                break;
            case 'd':
                strcpy(Options->OutputDirectory,optarg);
                break;
            case 'f':
                Options->Format = StringToPrintFormat(optarg);
//----If not a TPTP format, then non-logicals get stripped, and includes are
//----expanded
                if (Options->Format != tptp && Options->Format != tptp_short &&
Options->Format != oldtptp) {
                    Options->ExpandIncludes = 1;
                }
                break;
            case 't':
                strcpy(Options->Transformations,optarg);
//----If adding equality then must expand includes to full signature
                if (strstr(optarg,"add_equality") != NULL) {
                    Options->ExpandIncludes = 1;
                }
//----If shortening symbols then must expand includes and set printing option
                if (strstr(optarg,"shorten") != NULL) {
                    Options->ExpandIncludes = 1;
//NEW version of shorten
                    SetPrintShortSymbols(1);
                }
//----If fofifying, then must tolerate free variables
                if (strstr(optarg,"fofify") != NULL) {
                    Options->AllowFreeVariables = 1;
                }
//----If randomizing then must remove non-logicals
                if (strstr(optarg,"randomize") != NULL) {
                    Options->KeepNonLogicals = 0;
                }
                break;
            case 'u':
                Options->Pretty = strcmp("machine",optarg) ? 1 : 0;
                break;
            case 'r':
                if ((Colon = strchr(optarg,':')) !=  NULL) {
//----Random delay
                    *Colon = '\0';
                    Options->PrintDelayMin = atoi(optarg);
                    Options->PrintDelayMax = atoi(Colon+1);
                } else {
//----Fixed delay
                    Options->PrintDelayMin = atoi(optarg);
                    Options->PrintDelayMax = Options->PrintDelayMin;
                }
                break;
            case 'V':
                Options->AllowFreeVariables = 1;
                break;
            case 'N':
                Options->AllowDuplicateNames = 1;
                break;
            case 'x':
                Options->ExpandIncludes = 1;
                break;
            case 'c':
                Options->KeepNonLogicals = 0;
                break;
            case 'w':
                Options->Warnings = 1;
                break;
            case 'z':
                Options->SZSStatusReporting = 1;
//----Set in JJParser
                SetSZSStatusReporting(1);
                break;
            case 'l':
                if ((Colon = strchr(optarg,':')) !=  NULL) {
//----Random delay
                    *Colon = '\0';
                    Options->CPUTimeLimit = atoi(optarg);
                    Options->WCTimeLimit = atoi(Colon+1);
                }
                break;
            case 'v':
                printf("TPTP4X %s\n",VERSION_NUMBER);
                exit(0);
                break;
            case 'h':
            case '?':
                printf("Usage: %s <options> <files>\n",argv[0]);
                printf("<options> are ...\n");
                printf("  -q<quietness>   - control amount of output (1)\n");
                printf("  -d<directory>   - output directory (stdout)\n");
                printf("  -f<format>      - output format (tptp)\n");
                printf("    tptp          - long tptp format\n");
                printf("    tptp:short    - short tptp format\n");
                printf("    oldtptp       - old tptp format\n");
                printf("  -t<transform>   - transform the formulae (none)\n");
                printf("    add_equality  - adds all axioms of equality\n");
                printf("        :rstfp    - adds selected axioms of equality\n");
                printf("    fofify -V     - make universally quantified fof\n");
                printf("    fofify:! -V   - universally quantify fof\n");
                printf("    noint         - rename integers to constants\n");
                printf("    donum         - convert numbers to distinct objects\n");
                printf("    shorten       - rename symbols to short meaningless names\n");
                printf("    aritize       - make function and predicate names unique by arity\n");
                printf("    dequote       - make function and predicate names unquoted\n");
                printf("    shortennamesN - shorten formula names to N characters\n");
                printf("    numbernamesN  - add N digit extension to formula names\n");
                printf("    uniquenamesN  - add N digit extension to duplicate formula names\n");
                printf("    randomize     - randomize formulae and their order\n");
                printf("    negate_conjectures - negate all conjectures\n");
                printf("    single_conjectures - burst out multiple conjectures\n");
                printf("    stdfof        - rewrite <=, <~>, ~|, and ~&\n");
                printf("  -u<user>        - user type (human)\n");
                printf("    human         - pretty printed with indenting\n");
                printf("    machine       - one line per formula\n");
                printf("  -r<delay>       - delay between formula output (none)\n");
                printf("    fixed         - fixed delay of that many milliseconds\n");
                printf("    min:max       - random delay from min to max milliseconds\n");
                printf("    (Compatible only with one-at-a-time options.)\n");
                printf("  -V              - allow free variables (no)\n");
                printf("  -N              - allow duplicate formula names (no)\n");
                printf("  -x              - expand includes (no)\n");
                printf("  -c              - clean away non-logicals (no)\n");
                printf("  -w              - warnings (no)\n");
                printf("  -z              - SZS ontology status output (no)\n");
                printf("  -l<CPU:WC>      - CPU and Wall Clock time limits, 0 is none (none)\n");
                printf("  -v              - print version number\n");
                printf("  -h              - print this help\n");
                printf("<files> are ...\n");
                printf("  Any normal file name\n");
                printf("  A TPTP problem name\n");
                printf("  -- for stdin\n");
                exit(EXIT_SUCCESS);
                break;
            default:
                CodingError("Something wrong in getopt");
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
        printf("    OutputDirectory %s\n",Options->OutputDirectory);
        printf("    Format %s\n",PrintFormatToString(Options->Format));
        printf("    Pretty %d\n",Options->Pretty);
        printf("    AllowFreeVariables %d\n",Options->AllowFreeVariables);
        printf("    AllowDuplicateNames %d\n",Options->AllowDuplicateNames);
        printf("    ExpandIncludes %d\n",Options->ExpandIncludes);
        printf("    KeepNonLogicals %d\n",Options->KeepNonLogicals);
        printf("    Warnings %d\n",Options->Warnings);
        printf("    SZSStatusReporting %d\n",Options->SZSStatusReporting);
    }

    return(optind);
}
//-------------------------------------------------------------------------------------------------
READFILE OpenInputREADFILE(OptionsType Options,char * FileName,
char * IncludingFileName) {

    READFILE InputStream;
    String ErrorMessage;

    if ((InputStream = OpenReadFile(FileName,IncludingFileName)) != NULL) {
        return(InputStream);
    } else {
        sprintf(ErrorMessage,"Cannot open %s for reading\n",FileName);
        ReportError("OSError",ErrorMessage,0);
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
void MakeOutputFileName(OptionsType Options,char * FileName,char * Uniquifier,
String OutputFileName) {

    char * SlashDotP;

//----If relative to current or not absolute, start with cwd
    if (Options.OutputDirectory[0] == '.' || Options.OutputDirectory[0] != '/') {
        if (getcwd(OutputFileName,STRINGLENGTH) == NULL) {
            ReportError("OSError","Cannot get cwd",1);
        }
    } else {
        strcpy(OutputFileName,"");
    }
//----If the user specified directory does not start with /, add one
    if (Options.OutputDirectory[0] != '/') {
        strcat(OutputFileName,"/");
    }
//----If user output directory is not ., add it on
    if (!(strlen(Options.OutputDirectory) == 1 && Options.OutputDirectory[0] == '.')) {
        strcat(OutputFileName,Options.OutputDirectory);
    }
//----If the directory does not end with /, add one
    if (OutputFileName[strlen(OutputFileName)-1] != '/') {
        strcat(OutputFileName,"/");
    }
//----Get basename of file name, and add it on
    if ((SlashDotP = strrchr(FileName,'/')) == NULL) {
        strcat(OutputFileName,FileName);
    } else {
        strcat(OutputFileName,SlashDotP+1);
    }
//----Clobber .p extension
    if ((SlashDotP = strstr(OutputFileName,".p")) != NULL) {
        *SlashDotP = '\0';
    }
//----Add unique index if positive
    if (Uniquifier != NULL) {
        strcat(OutputFileName,"_");
        strcat(OutputFileName,Uniquifier);
    }
//----Output format extension
    strcat(OutputFileName,".");
    strcat(OutputFileName,PrintFormatToString(Options.Format));
}
//-------------------------------------------------------------------------------------------------
FILE * OpenOutputFILE(OptionsType Options,char * FileName,char * Uniquifier,
String OutputFileName) {

    FILE * OutputHandle;
    String ErrorMessage;

    if (strcmp(Options.OutputDirectory,"-")) {
        MakeOutputFileName(Options,FileName,Uniquifier,OutputFileName);
        if ((OutputHandle = fopen(OutputFileName,"w")) == NULL) {
            sprintf(ErrorMessage,"Cannot open output file %s\n",OutputFileName);
            ReportError("OSError",ErrorMessage,1);
            return(NULL);
        }
    } else {
        OutputHandle = stdout;
        strcpy(OutputFileName,"-");
    }

    return(OutputHandle);
}
//-------------------------------------------------------------------------------------------------
void CloseAndReportOutputFile(OptionsType Options,char * FileName,FILE * OutputHandle,
String OutputFileName) {

    if (OutputHandle != stdout) {
        fclose(OutputHandle);
        printf("%s -> %s\n",FileName,OutputFileName);
    }
}
//-------------------------------------------------------------------------------------------------
void ReformatAnnotatedFormula(OptionsType Options,READFILE Stream,SIGNATURE Signature,
ANNOTATEDFORMULA AnnotatedFormula,FILE * OutputHandle,char * IncludeFilter,
SyntaxType * LastNodeType) {

    String NewIncludeFile;
    String NewIncludeFilter;
    SuperString FormulaName;
    SyntaxType ThisNodeType;

    ThisNodeType = GetSyntax(AnnotatedFormula);
    GetName(AnnotatedFormula,FormulaName);
//----Blank line after every formula
    if (Options.Pretty &&
(*LastNodeType == tptp_thf ||
 *LastNodeType == tptp_tff || *LastNodeType == tptp_tcf ||
 *LastNodeType == tptp_fof || *LastNodeType == tptp_cnf ||
(*LastNodeType == tptp_tpi && ThisNodeType != tptp_tpi)) &&
ThisNodeType != blank_line) {
        printf("\n");
    }

//----Expand includes if necessary
    if (Options.ExpandIncludes && ThisNodeType == include) {
        GetIncludeParts(AnnotatedFormula,NewIncludeFile,NewIncludeFilter);
        ReformatFile(Options,NewIncludeFile,NewIncludeFilter,Stream->FileName,1,OutputHandle);
    } else if (LogicalAnnotatedFormula(AnnotatedFormula)) {
//----Check if it passes the include filter
        if (!strcmp(IncludeFilter,"all") || RemoveNameFromList(FormulaName,IncludeFilter)) {
            PrintAnnotatedTSTPNode(OutputHandle,AnnotatedFormula,Options.Format,Options.Pretty);
        }
    } else if (!Options.Pretty && ThisNodeType == blank_line) {
//----No blank lines if not pretty
    } else if(*LastNodeType != blank_line || ThisNodeType != blank_line) {
//----Skip double blank lines
        PrintAnnotatedTSTPNode(OutputHandle,AnnotatedFormula,Options.Format,Options.Pretty);
    }
    *LastNodeType = ThisNodeType;
    fflush(stdout);
}
//-------------------------------------------------------------------------------------------------
unsigned long long GetTimeInMillis() {

    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return(tv.tv_sec * 1000ULL + tv.tv_usec / 1000);
}
//-------------------------------------------------------------------------------------------------
void ProcessFormulaeOneByOne(OptionsType Options,READFILE InputStream,SIGNATURE Signature,
char * IncludeFilter,int RemoveHeader,int NumberNamesIndex,int MaximalNameLength,
char * NumberNamesFormat,FILE * OutputHandle) {

    char * NamesBuffer;
    int NamesBufferSize;
    ANNOTATEDFORMULA AnnotatedFormula;
    SyntaxType LastNodeType;
    unsigned long long LastPrintTime,PrintDelay,TimeToWait;

    LastNodeType = nontype;
    LastPrintTime = GetTimeInMillis();

//----Memory for recording formulae names
    if (!Options.AllowDuplicateNames) {
        NamesBuffer = (char *)Malloc(sizeof(String));
        NamesBuffer[0] = '\0';
        NamesBufferSize = sizeof(String);
    }
//----Reading formulae one-by-one
    while (!CheckTokenType(InputStream,endeof)) {
        AnnotatedFormula = ParseAndUseAnnotatedFormula(InputStream,Signature);
//----Remove header (from included files)
        if (GetSyntax(AnnotatedFormula) == comment && RemoveHeader &&
strstr(AnnotatedFormula->AnnotatedFormulaUnion.Comment,"% File     :") ==
AnnotatedFormula->AnnotatedFormulaUnion.Comment) {
            do {
                FreeAnnotatedFormula(&AnnotatedFormula,Signature);
                AnnotatedFormula = ParseAndUseAnnotatedFormula(InputStream,Signature);
            } while (GetSyntax(AnnotatedFormula) == blank_line ||
(GetSyntax(AnnotatedFormula) == comment && strstr(AnnotatedFormula->
AnnotatedFormulaUnion.Comment,"%---------------------------------") !=
AnnotatedFormula->AnnotatedFormulaUnion.Comment));
        } else {
//----Shorten this name
            if (MaximalNameLength > 0 && LogicalAnnotatedFormula(AnnotatedFormula)) {
                ShortenName(AnnotatedFormula,MaximalNameLength);
            }
//----Add name index
            if (strstr(Options.Transformations,"numbernames") != NULL &&
LogicalAnnotatedFormula(AnnotatedFormula)) {
                AddNameIndex(AnnotatedFormula,NumberNamesIndex++,NumberNamesFormat);
            }
//----Now check for uniqueness
            if (!Options.AllowDuplicateNames) {
                CheckOneDuplicateName(AnnotatedFormula,
strstr(Options.Transformations,"uniquenames") != NULL,&NamesBuffer,&NamesBufferSize,
NumberNamesFormat,&NumberNamesIndex);
            }
//----FOFify done before counting and output
            if (strstr(Options.Transformations,"fofify") != NULL) {
                FOFifyAnnotatedFormula(Options,AnnotatedFormula);
            }
//----Remove non-standard connectives
            if (strstr(Options.Transformations,"stdfof") != NULL) {
                StandardizeAnnotatedFormula(AnnotatedFormula);
            }
//----Output
            if (Options.Quietness < 3) {
                if (Options.PrintDelayMax > 0 && LogicalAnnotatedFormula(AnnotatedFormula)) {
                    if (Options.PrintDelayMin == Options.PrintDelayMax) {
                        PrintDelay = Options.PrintDelayMax;
                    } else {
                        PrintDelay = Options.PrintDelayMin + random() *
(Options.PrintDelayMax - Options.PrintDelayMin) / RAND_MAX;
                    }
                    TimeToWait = PrintDelay - (GetTimeInMillis() - LastPrintTime);
                    if (TimeToWait > 0) {
                        usleep(TimeToWait * 1000);
                    }
                    LastPrintTime = GetTimeInMillis();
                }
                ReformatAnnotatedFormula(Options,InputStream,Signature,AnnotatedFormula,
OutputHandle,IncludeFilter,&LastNodeType);
            }
        }
        FreeAnnotatedFormula(&AnnotatedFormula,Signature);
    }
//----Free names buffer
    if (!Options.AllowDuplicateNames) {
        Free((void **)&NamesBuffer);
    }
}
//-------------------------------------------------------------------------------------------------
void ProcessFormulaeAllTogether(OptionsType Options,READFILE InputStream,SIGNATURE Signature,
char * IncludeFilter,int RemoveHeader,int NumberNamesIndex,int MaximalNameLength,
char * NumberNamesFormat,FILE * OutputHandle) {

    LISTNODE AllAnnotatedFormulae;
    int NumberOfFOF;
    int NumberOfCNF;
    LISTNODE EqualityAxioms;
    LISTNODE Conjectures;
    LISTNODE ThisConjecture;
    LISTNODE * LastNext;
    String OutputFileName;
    String ErrorMessage;;

    if (strstr(Options.Transformations,"noint") != NULL ||
strstr(Options.Transformations,"donum") != NULL) {
        SetAllowFOFNumbers(1);
    }
    AllAnnotatedFormulae = ParseREADFILEOfFormulae(InputStream,Signature,Options.ExpandIncludes,
NULL);
    RemovedUnusedSymbols(Signature);
    SetAllowFOFNumbers(0);
//----Shorten names
    if (MaximalNameLength > 0) {
        ShortenNames(AllAnnotatedFormulae,MaximalNameLength);
    }
//----Index names
    if (strstr(Options.Transformations,"numbernames") != NULL) {
        NumberNames(Options,AllAnnotatedFormulae,NumberNamesFormat);
    }
//----Check for duplicate formula names
    if (!Options.AllowDuplicateNames) {
        CheckDuplicateNames(AllAnnotatedFormulae,
strstr(Options.Transformations,"uniquenames") != NULL,NumberNamesFormat,&NumberNamesIndex);
    }
//----Randomizing done before all else, no worry
    if (strstr(Options.Transformations,"randomize") != NULL) {
        RandomizeCommutativeFormulae(&AllAnnotatedFormulae);
    }
//----Deintegerizing done on the signature
    if (strstr(Options.Transformations,"noint") != NULL) {
        UninterpretNumbersInSignature(Signature,0);
    }
    if (strstr(Options.Transformations,"donum") != NULL) {
        UninterpretNumbersInSignature(Signature,1);
    }
//----Aritizing done on the signature
    if (strstr(Options.Transformations,"aritize") != NULL) {
        AritizeSymbolsInSignature(Signature);
    }
//----Dequoting done on the signature
    if (strstr(Options.Transformations,"dequote") != NULL) {
        DequoteSymbolsInSignature(Signature);
    }
//----Shortening symbols names done on the signature
    if (strstr(Options.Transformations,"shorten") != NULL) {
        ShortenSymbolsInSignature(Signature);
    }
//----FOFify done before equality
    if (strstr(Options.Transformations,"fofify") != NULL) {
        FOFifyListOfAnnotatedFormulae(Options,AllAnnotatedFormulae);
    }
//----Negate all conjectures
    if (strstr(Options.Transformations,"negate_conjectures") != NULL) {
        NegateConjectures(AllAnnotatedFormulae,0);
    }
//----Remove non-standard connectives
    if (strstr(Options.Transformations,"stdfof") != NULL) {
        StandardizeListOfAnnotatedTSTPNodes(AllAnnotatedFormulae);
    }
//----Count number of each type
    NumberOfFOF = ListCount(Signature,AllAnnotatedFormulae,fof_nodes);
    NumberOfCNF = ListCount(Signature,AllAnnotatedFormulae,cnf_nodes);
    if (strstr(Options.Transformations,"add_equality") != NULL &&
(EqualityAxioms = AddEqualityAxioms(Options,Signature,NumberOfFOF,NumberOfCNF)) != NULL) {
        AllAnnotatedFormulae = AppendListsOfAnnotatedTSTPNodes(AllAnnotatedFormulae,
EqualityAxioms);
    }
    if (Options.Quietness < 3) {
//----Burst out conjectures
        if (strstr(Options.Transformations,"single_conjectures") != NULL) {
            Conjectures = SelectListOfAnnotatedFormulaeWithRole(&AllAnnotatedFormulae,conjecture,
1,Signature);
            LastNext = GetLastNext(&AllAnnotatedFormulae);
            while (Conjectures != NULL) {
                if ((OutputHandle = OpenOutputFILE(Options,InputStream->FileName,
GetName(Conjectures->AnnotatedFormula,NULL),OutputFileName)) != NULL) {
                    ThisConjecture = Conjectures;
                    Conjectures = Conjectures->Next;
                    ThisConjecture->Next = NULL;
                    *LastNext = ThisConjecture;
                    PrintListOfAnnotatedTSTPNodes(OutputHandle,Signature,AllAnnotatedFormulae,
Options.Format,Options.Pretty);
//----Close the output file
                    CloseAndReportOutputFile(Options,InputStream->FileName,OutputHandle,
OutputFileName);
                    *LastNext = NULL;
                } else {
                    sprintf(ErrorMessage,"Could not open output for %s\n",InputStream->FileName);
                    ReportError("OSError",ErrorMessage,1);
                }
                FreeAListNode(&ThisConjecture,Signature);
            }
            FreeListOfAnnotatedFormulae(&Conjectures,Signature);
        } else {
            PrintListOfAnnotatedTSTPNodes(OutputHandle,Signature,AllAnnotatedFormulae,
Options.Format,Options.Pretty);
        }
    }
    FreeListOfAnnotatedFormulae(&AllAnnotatedFormulae,Signature);
}
//-------------------------------------------------------------------------------------------------
void ReformatFile(OptionsType Options,char * FileName,char * IncludeFilter,
char * IncludingFileName,int RemoveHeader,FILE * OutputHandle) {

    SIGNATURE Signature;
    READFILE InputStream;
    int MaximalNameLength;
    int NumberNamesIndex;
    String NumberNamesFormat;

    if ((InputStream = OpenInputREADFILE(Options,FileName,
IncludingFileName)) != NULL) {
        NextToken(InputStream);
//----New signature for each file
        Signature = NewSignature();
//----Data for indexing names
        if (strstr(Options.Transformations,"numbernames") != NULL ||
strstr(Options.Transformations,"uniquenames") != NULL) {
            MakeNumberNamesFormat(Options,NumberNamesFormat);
            NumberNamesIndex = 1;
        }
        if (strstr(Options.Transformations,"shortennames") != NULL) {
            MaximalNameLength = GetMaximalNameLength(Options);
        } else {
            MaximalNameLength = -1;
        }
//----Check if formulae can be processed one-by-one (useful for huge files)
        if ((Options.Format == tptp || Options.Format == tptp_short ||
Options.Format == oldtptp) &&
//----noint and aritize modify the signature, so must read it all
strstr(Options.Transformations,"noint") == NULL &&
strstr(Options.Transformations,"donum") == NULL &&
strstr(Options.Transformations,"aritize") == NULL &&
strstr(Options.Transformations,"dequote") == NULL &&
//----Need them all at once to randomize order
strstr(Options.Transformations,"randomize") == NULL &&
//----Need all to negate all conjectures
strstr(Options.Transformations,"negate_conjectures") == NULL &&
//----Need all formulae to burst out conjectures
strstr(Options.Transformations,"single_conjectures") == NULL &&
//----Must expand includes for shorten to get full signature
//NEW version of shorten, but if includes are expanded then need to do
//----that before printing to get one signature
!(strstr(Options.Transformations,"shorten") != NULL &&
  Options.ExpandIncludes) &&
//----Must expand includes for equality to get full signature
strstr(Options.Transformations,"add_equality") == NULL) {
            ProcessFormulaeOneByOne(Options,InputStream,Signature,
IncludeFilter,RemoveHeader,NumberNamesIndex,MaximalNameLength,
NumberNamesFormat,OutputHandle);
        } else {
            ProcessFormulaeAllTogether(Options,InputStream,Signature,
IncludeFilter,RemoveHeader,NumberNamesIndex,MaximalNameLength,
NumberNamesFormat,OutputHandle);
        }
        CloseReadFile(InputStream);
//----Clean and delete the signature (should be empty here)
        FreeSignature(&Signature);
    } else {
        fclose(OutputHandle);
        ReportError("OSError","Could not open input file",1);
    }
}
//-------------------------------------------------------------------------------------------------
void XCPUHandler(int TheSignal) {

    printf("ERROR: Ran out of CPU time\n");
    exit(EXIT_FAILURE);
}
//-------------------------------------------------------------------------------------------------
void ALRMHandler(int TheSignal) {

    printf("ERROR: Ran out of WC time\n");
    exit(EXIT_FAILURE);
}
//-------------------------------------------------------------------------------------------------
void SetTimeLimits(OptionsType Options) {

    struct rlimit ResourceLimits;

    if (Options.CPUTimeLimit > 0) {
//----Limit the memory. Need to get old one for hard limit field
        if (getrlimit(RLIMIT_CPU,&ResourceLimits) == -1) {
            perror("Getting resource limit:");
            exit(EXIT_FAILURE);
        }
//----Set new CPU limit 
        ResourceLimits.rlim_cur = Options.CPUTimeLimit;
        if (setrlimit(RLIMIT_CPU,&ResourceLimits) == -1) {
            perror("Cannot set CPU time limit\n");
            exit(EXIT_FAILURE);
        }
        if (signal(SIGXCPU,XCPUHandler) == SIG_ERR) {
            perror("Could not set SIGXCPU handler");
            exit(EXIT_FAILURE);
        }
    }
    if (Options.WCTimeLimit > 0) {
        alarm(Options.WCTimeLimit);
        if (signal(SIGALRM,ALRMHandler) == SIG_ERR) {
            perror("Could not set SIGALRM handler");
            exit(EXIT_FAILURE);
        }
    }
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    OptionsType Options;
    int ArgvFileIndex;
    FILE * OutputHandle;
    String FileName;
    String OutputFileName;
    String ErrorMessage;;

    ArgvFileIndex = ProcessCommandLine(argc,argv,&Options);
    SetTimeLimits(Options);

    SetNeedForNonLogicTokens(Options.KeepNonLogicals);
    SetAllowFreeVariables(Options.AllowFreeVariables);
    SetWarnings(Options.Warnings);
    srandom(time(NULL));

//----Do each file on command line
    while (ArgvFileIndex < argc) {
        strcpy(FileName,argv[ArgvFileIndex++]);
//----If bursting conjectures, files are opened later
        if (strstr(Options.Transformations,"single_conjectures") == NULL) {
            if ((OutputHandle = OpenOutputFILE(Options,FileName,NULL,OutputFileName)) != NULL) {
                ReformatFile(Options,FileName,"all",NULL,0,OutputHandle);
//----Close the output file
                CloseAndReportOutputFile(Options,FileName,OutputHandle,OutputFileName);
            } else {
                sprintf(ErrorMessage,"Could not open output for %s\n",FileName);
                ReportError("OSError",ErrorMessage,1);
            }
        } else {
            ReformatFile(Options,FileName,"all",NULL,0,NULL);
        }
    }

    return(EXIT_SUCCESS);
}
//-------------------------------------------------------------------------------------------------

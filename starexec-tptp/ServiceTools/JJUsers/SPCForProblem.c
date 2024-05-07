#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "DataTypes.h"
#include "Utilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "List.h"
#include "Tree.h"
#include "TreeStatistics.h"
#include "ListStatistics.h"
#include "PrintTSTP.h"
#include "SystemOnTPTP.h"

char * IsFOFEPRCommandFromTPTPHome = "SPCs/IsFOFEPR";
char * IsFOFEPRCommandFlags = " -q --";
char * DefaultTPTPHome = "/home/tptp";
//-------------------------------------------------------------------------------------------------
void XCPUHandler(int TheSignal) {

    printf("ERROR: MakeTreeStats ran out of CPU time\n");
    exit(EXIT_FAILURE);

}
//-------------------------------------------------------------------------------------------------
void DetermineEqualityPresence(StatisticsType Statistics,String SPC) {

    if (Statistics.FormulaStatistics.NumberOfEqualityAtoms == 0) {
        strcat(SPC,"_NEQ");
    } else {
        strcat(SPC,"_EQU");
    }
}
//-------------------------------------------------------------------------------------------------
void DetermineArithmeticPresence(StatisticsType Statistics,String SPC) {

    if (
Statistics.FormulaStatistics.NumberOfMathAtoms > 0 ||
Statistics.FormulaStatistics.NumberOfMathTerms > 0 ||
Statistics.FormulaStatistics.NumberOfNumbers > 0 ||
Statistics.ConnectiveStatistics.NumberOfMathVariables > 0 ||
Statistics.SymbolStatistics.NumberOfMathTypes > 0) {
        strcat(SPC,"_ARI");
    } else {
        strcat(SPC,"_NAR");
    }
}
//-------------------------------------------------------------------------------------------------
void DetermineTHFSPC(StatisticsType Statistics,String SPC) {

    DetermineEqualityPresence(Statistics,SPC);
    DetermineArithmeticPresence(Statistics,SPC);
}
//-------------------------------------------------------------------------------------------------
void DetermineTFFSPC(StatisticsType Statistics,String SPC) {

//DEBUG printf("NumberOfMathPredicates %.0f NumberOfEqualityAtoms %.0f NumberOfPredicates %.0f NumberOfMathFunctions %.0f NumberOfNumbers %.0f NumberOfFunctors %.0f\n",Statistics.NumberOfMathPredicates,Statistics.NumberOfEqualityAtoms,Statistics.NumberOfPredicates,Statistics.NumberOfMathFunctions,Statistics.NumberOfNumbers,Statistics.NumberOfFunctors);

    if (Statistics.SymbolStatistics.NumberOfPredicates == 
Statistics.SymbolStatistics.NumberOfPropositions) {
        strcat(SPC,"_PRP");
//    } else if (FOFEPRProblem(Statistics,Head,Signature)) {
//        strcat(SPC,"_EPR");
//    } else {
//        strcat(SPC,"_RFO");
//        DetermineEqualityPresence(Statistics,SPC);
//        DetermineArithmeticPresence(Statistics,SPC);
    }

    DetermineEqualityPresence(Statistics,SPC);
    DetermineArithmeticPresence(Statistics,SPC);
}
//-------------------------------------------------------------------------------------------------
int FOFEPRProblem(StatisticsType Statistics,LISTNODE Head,SIGNATURE Signature) {

    String IsFOFEPRCommand;
    char * TPTPHome;
    FILE* SendHandle;
    int Status;

//----Functions and (variables or equality) => NO
    if (
Statistics.SymbolStatistics.MaxFunctorArity > 0 &&
(Statistics.SymbolStatistics.NumberOfVariables > 0 || 
 Statistics.FormulaStatistics.NumberOfEqualityAtoms > 0)) {
        return(0);
    }

    if ((TPTPHome = getenv("TPTP_HOME")) == NULL) {
        TPTPHome = DefaultTPTPHome;
    }
    strcpy(IsFOFEPRCommand,TPTPHome);
    strcat(IsFOFEPRCommand,"/");
    strcat(IsFOFEPRCommand,IsFOFEPRCommandFromTPTPHome);
//----Check if the test for EPR even exists
    if (eaccess(IsFOFEPRCommand,X_OK) == 0) {
        strcat(IsFOFEPRCommand,IsFOFEPRCommandFlags);
        if ((SendHandle = popen(IsFOFEPRCommand,"w")) == NULL) {
            printf("ERROR: Could not run %s\n",IsFOFEPRCommand);
            exit(EXIT_FAILURE);
        }
        PrintListOfAnnotatedTSTPNodes(SendHandle,Signature,Head,tptp,1);
        Status = pclose(SendHandle);
        if (WIFEXITED(Status)) {
//DEBUG printf("%s exited normally with status %d -- %d\n",IsFOFEPRCommand,Status,WEXITSTATUS(Status));
            Status = WEXITSTATUS(Status);
        } else {
//DEBUG printf("%s exited abnormally\n",IsFOFEPRCommand);
//DEBUG printf("========%d\n",Status);
            exit(EXIT_FAILURE);
        }
        if (Status != 0 && Status != 1) {
            printf("ERROR: Invalid status returned from %s\n",IsFOFEPRCommand);
            exit(EXIT_FAILURE);
        }
        return(Status == 1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
void DetermineFOFSPC(LISTNODE Head,SIGNATURE Signature,
StatisticsType Statistics,String SPC) {

    if (Statistics.SymbolStatistics.NumberOfPredicates == 
Statistics.SymbolStatistics.NumberOfPropositions) {
        strcat(SPC,"_PRP");
    } else {
        if (FOFEPRProblem(Statistics,Head,Signature)) {
            strcat(SPC,"_EPR");
        } else {
            strcat(SPC,"_RFO");
        }
        if (Statistics.FormulaStatistics.NumberOfEqualityAtoms == 0) {
            strcat(SPC,"_NEQ");
        } else if (Statistics.FormulaStatistics.NumberOfEqualityAtoms == 
Statistics.FormulaStatistics.NumberOfAtoms) {
            strcat(SPC,"_PEQ");
        } else {
            strcat(SPC,"_SEQ");
        }
    }
}
//-------------------------------------------------------------------------------------------------
void DetermineCNFSPC(StatisticsType Statistics,String SPC) {

    if (Statistics.SymbolStatistics.NumberOfPredicates == 
Statistics.SymbolStatistics.NumberOfPropositions) {
        strcat(SPC,"_PRP");
    } else {
        if (
Statistics.SymbolStatistics.MaxFunctorArity < 1 ||
(Statistics.SymbolStatistics.NumberOfVariables == 0 && 
 Statistics.FormulaStatistics.NumberOfEqualityAtoms == 0)) {
            strcat(SPC,"_EPR");
        } else {
            strcat(SPC,"_RFO");
        }
        if (strstr(SPC,"_UNS_") != NULL || strstr(SPC,"_UNK_") != NULL ||
strstr(SPC,"_OPN_") != NULL) {
            if (Statistics.FormulaStatistics.NumberOfEqualityAtoms == 
Statistics.FormulaStatistics.NumberOfAtoms) {
                strcat(SPC,"_PEQ");
                if (Statistics.FormulaStatistics.NumberOfFormulae == 
Statistics.FormulaStatistics.NumberOfUnitFormulae) {
                    strcat(SPC,"_UEQ");
                } else {
                    strcat(SPC,"_NUE");
                }
            } else {
                if (Statistics.FormulaStatistics.NumberOfEqualityAtoms == 0) {
                   strcat(SPC,"_NEQ");
                } else {
                    strcat(SPC,"_SEQ");
                }
                if (Statistics.FormulaStatistics.NumberOfCNF == 
Statistics.FormulaStatistics.NumberOfHornClauses) {
                    strcat(SPC,"_HRN");
                } else {
                    strcat(SPC,"_NHN");
                }
            }
        } else if (strstr(SPC,"_SAT_") != NULL) {
            if (Statistics.FormulaStatistics.NumberOfEqualityAtoms == 0) {
               strcat(SPC,"_NEQ");
            } else if (
Statistics.FormulaStatistics.NumberOfEqualityAtoms == 
Statistics.FormulaStatistics.NumberOfAtoms && 
Statistics.FormulaStatistics.NumberOfFormulae ==
Statistics.FormulaStatistics.NumberOfUnitFormulae) {
                strcat(SPC,"_PEQ_UEQ");
            } else {
                strcat(SPC,"_EQU_NUE");
            }
        } else {
            printf("ERROR: No SPC for CNF problem with SPC starting %s\n",SPC);
            exit(EXIT_FAILURE);
        }
    }
}
//-------------------------------------------------------------------------------------------------
//----Determine if THM or SAT based on existence of a conjecture
void DetermineProvabability(char * Status,int HasAConjecture,String SPC) {

    if (Status != NULL) {
        strcat(SPC,Status);
    } else if (HasAConjecture) {
//----Assume a provable conjecture or a satisfiable set of formulae
        strcat(SPC,"THM");
    } else {
        strcat(SPC,"SAT");
    }
}
//-------------------------------------------------------------------------------------------------
//----Here it is done right, as opposed to SPCForTPTPProblem which puts
//----Unknowns without a conjecture into NKC.
void DetermineSPC(LISTNODE Head,SIGNATURE Signature,SyntaxType Syntax,StatisticsType Statistics,
char * Status,int HasAConjecture,String SPC) {

    String SyntaxTypes;
    char * ASyntax;
    char * CRPosition;
    char * Classicality;

//----Check if non-classical
    if (
Statistics.FormulaStatistics.NumberOfAppliedConnectives > 0 ||
Statistics.ConnectiveStatistics.NumberOfNTFConnectives > 0) {
        Classicality = "N";
    } else {
        Classicality = "T";
    }

//----Separate CNF and FOF and THF and TFF
    if (Syntax == tptp_thf) {
        strcpy(SPC,Classicality);
//DEBUG printf("PiB %.0f TE %.0f Pi %.0f Sig %.0f Ch %.0f De %.0f\n",
//DEBUG Statistics.ConnectiveStatistics.NumberOfPiBinders,
//DEBUG Statistics.ConnectiveStatistics.NumberOfTypedEquations,
//DEBUG Statistics.ConnectiveStatistics.NumberOfPis,
//DEBUG Statistics.ConnectiveStatistics.NumberOfSigmas,
//DEBUG Statistics.ConnectiveStatistics.NumberOfChoices,
//DEBUG Statistics.ConnectiveStatistics.NumberOfDescriptions);
        if (
Statistics.ConnectiveStatistics.NumberOfPiBinders > 0 ||
Statistics.ConnectiveStatistics.NumberOfSigmaBinders > 0 ||
Statistics.ConnectiveStatistics.NumberOfTypedEqualitySymbols > 0 ||
Statistics.ConnectiveStatistics.NumberOfPis > 0 ||
Statistics.ConnectiveStatistics.NumberOfSigmas > 0 ||
Statistics.ConnectiveStatistics.NumberOfChoices > 0 ||
Statistics.ConnectiveStatistics.NumberOfDescriptions > 0) {
            strcat(SPC,"H1_");
        } else {
            strcat(SPC,"H0_");
        }
        DetermineProvabability(Status,HasAConjecture,SPC);
        DetermineTHFSPC(Statistics,SPC);

    } else if (Syntax == tptp_tff) {
        strcpy(SPC,Classicality);
//DEBUG printf("NF %d BV %d Tu %d ITE %d Let %d\n",
//DEBUG Statistics.FormulaStatistics.NumberOfNestedFormulae,
//DEBUG Statistics.SymbolStatistics.NumberOfBooleanVariables,
//DEBUG Statistics.FormulaStatistics.NumberOfTuples,
//DEBUG Statistics.FormulaStatistics.NumberOfITEs,
//DEBUG Statistics.FormulaStatistics.NumberOfLets);
        if (
//----All non-classical are N
!strcmp(Classicality,"N") ||
Statistics.FormulaStatistics.NumberOfNestedFormulae > 0 ||
Statistics.SymbolStatistics.NumberOfBooleanVariables > 0 ||
Statistics.FormulaStatistics.NumberOfTuples > 0 ||
Statistics.FormulaStatistics.NumberOfITEs > 0 ||
Statistics.FormulaStatistics.NumberOfLets > 0) {
            strcat(SPC,"X");
        } else {
            strcat(SPC,"F");
        }
        if (Statistics.ConnectiveStatistics.NumberOfPiBinders > 0) {
            strcat(SPC,"1_");
        } else {
            strcat(SPC,"0_");
        }
        DetermineProvabability(Status,HasAConjecture,SPC);
        DetermineTFFSPC(Statistics,SPC);

    } else if (Syntax == tptp_fof) {
        strcpy(SPC,"FOF_");
        DetermineProvabability(Status,HasAConjecture,SPC);
        DetermineFOFSPC(Head,Signature,Statistics,SPC);
    } else if (Syntax == tptp_cnf) {
        strcpy(SPC,"CNF_");
        if (Status != NULL) {
            strcat(SPC,Status);
        } else {
//----Assume an unsatisfiable set
            strcat(SPC,"UNS");
        }
        DetermineCNFSPC(Statistics,SPC);

    } else if (Syntax == tptp_mixed) {
        strcpy(SPC,"MIX_");
        GetListSyntaxTypes(Head,SyntaxTypes);
        ASyntax = SyntaxTypes;
//----Convert it all to uppercase
        while (*ASyntax != '\0') {
            *ASyntax = toupper(*ASyntax);
            ASyntax++;
        }
        ASyntax = SyntaxTypes;
        while (*ASyntax != '\0' && (CRPosition = strchr(ASyntax,'\n')) != NULL) {
            *CRPosition = '\0';
            if (!strcmp(ASyntax,"THF")) {
                strcat(SPC,"TH0");
            } else if (!strcmp(ASyntax,"TFF")) {
                if (Statistics.ConnectiveStatistics.NumberOfPiBinders > 0) {
                    strcat(SPC,"TF1");
                } else {
                    strcat(SPC,"TF0");
                }
            } else {
                strcat(SPC,ASyntax);
            }
            strcat(SPC,"_");
            ASyntax = CRPosition+1;
        }
        DetermineProvabability(Status,HasAConjecture,SPC);
    } else {
        strcpy(SPC,"UNK");
    }
}
//-------------------------------------------------------------------------------------------------
char * GetStatusFromHeader(char * FileName,SIGNATURE Signature) {

    LISTNODE Header;
    LISTNODE Target;
    String StatusLine;
    char * Status = NULL;

    SetNeedForNonLogicTokens(1);
    if ((Header = ParseFileOfHeader(FileName)) != NULL) {
        Target = Header;
        while (Target != NULL && Status == NULL) {
            if (
GetSyntax(Target->AnnotatedFormula) == comment &&
strstr(Target->AnnotatedFormula->AnnotatedFormulaUnion.Comment,"% Status ") != NULL &&
(Status = strchr(Target->AnnotatedFormula->AnnotatedFormulaUnion.Comment,':')) != NULL) {
                strcpy(StatusLine,Status+2);
                while (StatusLine[strlen(StatusLine)-1] == ' ') {
                    StatusLine[strlen(StatusLine)-1] = '\0';
                }
                Status = SZSResultToString(StringToSZSResult(StatusLine));
            }
            Target = Target->Next;
        }
        FreeListOfAnnotatedFormulae(&Header,Signature);
    }
    return(Status);
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    LISTNODE Head;
    SIGNATURE Signature;
    StatisticsType Statistics;
    String SPC;
    char * Status;

    if (argc == 1) {
        printf("Usage: SPCForProblem <file name>\n");
        return(0);
    }

    if (signal(SIGXCPU,XCPUHandler) == SIG_ERR) {
        printf("ERROR: MakeTreeStats cannot set XCPU handler\n");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGTERM,XCPUHandler) == SIG_ERR) {
        printf("ERROR: MakeTreeStats cannot set SIGTERM handler\n");
        exit(EXIT_FAILURE);
    }

    Signature = NewSignatureWithTypes();
    SetNeedForNonLogicTokens(0);
    if ((Head = ParseFileOfFormulae(argv[1],NULL,Signature,1,NULL)) != NULL) {
        RemoveAnnotatedFormulaWithRole(&Head,Signature,logic);
        RemovedUnusedSymbols(Signature);
        Statistics = GetListStatistics(Head,Signature);
        Status = GetStatusFromHeader(argv[1],Signature);
        DetermineSPC(Head,Signature,GetListSyntax(Head),Statistics,Status,ThereIsAConjecture(Head),
SPC);
        printf("%s\n",SPC);
        FreeListOfAnnotatedFormulae(&Head,Signature);
        assert(Head == NULL);
    } else {
        printf("ERROR: Could not parse %s\n",argv[1]);
    }

    FreeSignature(&Signature);
    return(0);
}
//-------------------------------------------------------------------------------------------------

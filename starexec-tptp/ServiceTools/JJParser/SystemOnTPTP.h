#ifndef SYSTEMONTPTP_H
#define SYSTEMONTPTP_H
//-------------------------------------------------------------------------------------------------
#include <unistd.h>
#include <curl/curl.h>

#include "DataTypes.h"
#include "PrintTSTP.h"
//-------------------------------------------------------------------------------------------------
typedef enum {
    SZS,
    SUC,
    UNP,SAP,ESA,
    SAT,FSA,THM,EQV,TAC,WEC,ETH,TAU,WTC,WTH,
    CAX,SCA,TCA,WCA,
    CUP,CSP,ECS,
    CSA,CTH,CEQ,UNC,WCC,ECT,FUN,UNS,WUC,WCT,
    SCC,UCA,
    NOC,
    NOS,
    OPN,UNK,ASS,
    STP,ERR,OSE,INE,SYE,SEE,TYE,
    FOR,USR,RSO,TMO,MMO,GUP,INC,IAP,INP,NTT,NTY,
    nonszsresult
} SZSResultType;

typedef SZSResultType * SZSResultArray;

typedef enum {
    LDa,
    Sol,
    Prf,Der,Ref,CRf,
    Int,HIn,DIn,FIn,IIn,RIn,TIn,
    Mod,DMo,HMo,FMo,IMo,RMo,TMo,Sat,
    Lof,Lth,Lfo,Lcn,
    NSo,IPr,IRf,ICf,Ass,
    Non,
    nonszsoutput
} SZSOutputType;

typedef SZSOutputType * SZSOutputArray;

typedef struct {
    SZSResultType TLA;
    char * TLAString;
    char * UserString;
} SZSResultTripleType;

typedef struct {
    SZSOutputType TLA;
    char * TLAString;
    char * UserString;
} SZSOutputTripleType;
//-------------------------------------------------------------------------------------------------
#ifndef TPTP_HOME
    #define TPTP_HOME "/home/tptp"
#endif
#define SYSTEM_ON_TPTP "SystemExecution/SystemOnTPTP"
#define SYSTEM_ON_TPTP_FORMREPLYURL "https://tptp.cs.miami.edu/cgi-bin/SystemOnTPTPFormReply"
//-------------------------------------------------------------------------------------------------
SZSResultType StringToSZSResult(char * SZSResult);
char * SZSResultToUserString(SZSResultType SZSResult);
char * SZSResultToString(SZSResultType SZSResult);
int StringIsASZSResult(char * PossibleResult);
int StringIsASZSResultTLA(char * PossibleResultTLA);
SZSOutputType StringToSZSOutput(char * SZSOutput);
char * SZSOutputToUserString(SZSOutputType SZSOutput);
char * SZSOutputToString(SZSOutputType SZSOutput);
int StringIsASZSOutput(char * PossibleOutput);
int StringIsASZSOutputTLA(char * PossibleOutputTLA);
int SZSIsA(SZSResultType SZSResult,SZSResultType DesiredResult);
int SZSOutputIsA(SZSOutputType SZSOutput,SZSOutputType DesiredOutput);

void SystemOnTPTPFileName(char * Directory,char * BaseName,char * Extension,String FileName);
int MakeProblemFile(char * FilesDirectory,char * BaseName,char * Extension,String ProblemFileName,
LISTNODE Head,StatusType AxiomsStatus,ANNOTATEDFORMULA Conjecture,StatusType ConjectureStatus);
int SystemOnTPTPAvailable(void);
int SystemOnTPTP(LISTNODE Axioms,ANNOTATEDFORMULA Conjecture,char * PositiveChecker,
char * PositiveResult,int TestNegative,char * NegativeChecker,char * NegativeResult,int TimeLimit,
char * SystemOutputPrefix,char * OptionalFlags,int KeepOutputFiles,char * FilesDirectory,
char * UsersOutputFileName,String OutputFileName,int LocalSoT);
size_t ReadCallback(void * TheReturnedData,size_t ElementSize,size_t NumberOfElements,
void * DataWriteHandle);
CURL * InitializeRemoteSoT();
FILE * StartRemoteSoT(char * QuietnessFlag,int QuietnessLevel,char * ProblemFileName,
char * ATPSystem,int TimeLimit,char * X2TSTPFlag,curl_mime * MultipartForm);
int SystemOnTPTPGetResult(int QuietnessLevel,char * ProblemFileName,char * ATPSystem,int TimeLimit,
char * X2TSTPFlag,char * SystemOutputPrefix,char * OptionalFlags,int KeepOutputFiles,
char * FilesDirectory,char * UsersOutputFileName,char * OutputFileName,char * PutResultHere,
char * PutOutputHere,int LocalSoT);
SZSResultType SZSSystemOnTPTP(LISTNODE Axioms,ANNOTATEDFORMULA Conjecture,char * System,
SZSResultType DesiredResult,int QuietnessLevel,int TimeLimit,char * X2TSTPFlag,
char * SystemOutputPrefix,char * OptionalFlags,int KeepOutputFiles,char * FilesDirectory,
char * UsersOutputFileName,String OutputFileName,SZSOutputType * SZSOutput,int LocalSoT);

LISTNODE ApplyExternalProgram(LISTNODE Head,StatusType AsStatus,ANNOTATEDFORMULA Conjecture,
const char * ExecuteFormatString,SIGNATURE Signature);
//-------------------------------------------------------------------------------------------------
#endif

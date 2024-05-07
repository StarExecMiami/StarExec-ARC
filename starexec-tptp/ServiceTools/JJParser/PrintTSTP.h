#ifndef PRINTTSTP_H
#define PRINTTSTP_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"

typedef enum {
    tptp,
    tptp_short,
    oldtptp,
    dfg,
    lambdapi,
    otter,
    kif,
    xml,
    xml_short,
    sumo,
    smt2,
    nonprinttype
} PrintFormatType;
//-------------------------------------------------------------------------------------------------
PrintFormatType StringToPrintFormat(char * String);
char * PrintFormatToString(PrintFormatType Format);

void SetPrintShortSymbols(int Choice);
void PrintIndent(FILE * Stream,int Indent,int AlreadyIndented,int Pretty);
void PrintStringTSTPTerm(char * PutOutputHere,SyntaxType Language,TERM Term,int Pretty,int Indent,
int TSTPSyntaxFlag);
void PrintTSTPTerm(FILE * Stream,SyntaxType Language,TERM Term,int Indent,int Pretty,
int TSTPSyntaxFlag);
void PrintFileTermList(PRINTFILE Stream,SyntaxType Language,TERM Term,int Pretty,int Indent,
char OpeningBracket,char ClosingBracket,ConnectiveType LastConnective,int TSTPSyntaxFlag);
void PrintFileTSTPFormula(PRINTFILE Stream,SyntaxType Language,FORMULA Formula,
int Indent,int Pretty,ConnectiveType LastConnective,int TSTPSyntaxFlag);
void PrintTSTPFormula(FILE * Stream,SyntaxType Language,FORMULA Formula,int Indent,int Pretty,
ConnectiveType LastConnective,int TSTPSyntaxFlag);
void PrintAnnotatedTSTPFormula(FILE * Stream,SyntaxType Syntax,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula,PrintFormatType Format,int Pretty);
void PrintStringAnnotatedTSTPNode(char * PutOutputHere,ANNOTATEDFORMULA 
AnnotatedFormula,PrintFormatType Format,int Pretty);
void PrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula,PrintFormatType Format,
int Pretty);
void PrintAnnotatedTSTPNodeWithStatus(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula,
PrintFormatType Format,int Pretty,StatusType Status);
void PrintListOfAnnotatedTSTPNodes(FILE * Stream,SIGNATURE Signature,LISTNODE Head,
PrintFormatType Format,int Pretty);
void PrintListOfAnnotatedTSTPNodesWithStatus(FILE * Stream,SIGNATURE Signature,LISTNODE Head,
PrintFormatType Format,int Pretty,StatusType Status);
//-------------------------------------------------------------------------------------------------
#endif

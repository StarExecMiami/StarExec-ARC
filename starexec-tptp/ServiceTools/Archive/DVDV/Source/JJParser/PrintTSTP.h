#ifndef PRINTTSTP_H
#define PRINTTSTP_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"

typedef enum {
    tptp,
    tptp_short,
    oldtptp
} PrintFormatType;
//-----------------------------------------------------------------------------
PrintFormatType StringToPrintFormat(char * String);
char * PrintFormatToString(PrintFormatType Format);

void PrintTSTPTerm(FILE * Stream,TERM Term,int TSTPSyntaxFlag);
void PrintTSTPFormula(FILE * Stream,FORMULA Formula,int Indent,
int AlreadyIndented,int Pretty,ConnectiveType LastConnective,
ConnectiveType NextConnective,int TSTPSyntaxFlag);
void PrintAnnotatedTSTPFormula(FILE * Stream,SyntaxType Syntax,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula,PrintFormatType Format,
int Pretty);
void PrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula,
PrintFormatType Format,int Pretty);
void PrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head,
PrintFormatType Format);
//-----------------------------------------------------------------------------
#endif

#ifndef FILEUTILITIES_H
#define FILEUTILITIES_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
#include <stdarg.h>
//-------------------------------------------------------------------------------------------------
void PathBasename(char * Path,String Basename,char * Suffix);
char * CleanTheFileName(char * OriginalFileName,char * CleanFileName);
FILE * OpenFileInMode(String FileName,char * Mode);

READFILE OpenReadFile(char * OriginalFileName,char * CurrentFileName);
READFILE OpenFILEReadFile(char * FileName,FILE * OpenStream);
READFILE OpenStringReadFile(char * Content);
void CloseReadFile(READFILE Stream);

PRINTFILE OpenFILEPrintFile(FILE * OpenStream,char * FileName);
PRINTFILE OpenStringPrintFile(char * Content);
PRINTFILE OpenPrintFile(char * OriginalFileName);
void ClosePrintFile(PRINTFILE Stream);
void PFprintf(PRINTFILE Stream,char * Format,...);

void RemoveFile(String FileName);
void RemoveFileDirectory(String FileName);
//--------------------------------------------------------------------------------------------------
#endif

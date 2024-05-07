#ifndef TPTP4X_H
#define TPTP4X_H
//-----------------------------------------------------------------------------
//----v6.4.0.0 (TPTP version.internal development number)
//----v6.4.0.1 - Fixed bug in SMT2 output
//----v6.4.0.2 - Added verion numbering
//----v6.4.0.3 - Added -r option
//----v6.4.0.4 - Added -t doint option
//----v7.4.0.1 - Fixed include relative to current directory
//----v8.1.0.1 - So many changes that I have not kept this up to date
#define VERSION_NUMBER "v8.1.0.1"

typedef struct {
    int Quietness;
    PrintFormatType Format;
    int KeepNonLogicals;
    int AllowFreeVariables;
    int AllowDuplicateNames;
    int Pretty;
    int ExpandIncludes;
    int Warnings;
    int SZSStatusReporting;
    String OutputDirectory;
    String Transformations;
    int PrintDelayMin,PrintDelayMax;
    int CPUTimeLimit,WCTimeLimit;
} OptionsType;
//-----------------------------------------------------------------------------
#endif


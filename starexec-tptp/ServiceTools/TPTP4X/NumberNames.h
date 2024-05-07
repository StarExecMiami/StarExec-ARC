#ifndef NUMBERNAMES_H
#define NUMBERNAMES_H
#include "tptp4X.h"
//-----------------------------------------------------------------------------
int GetMaximalNameLength(OptionsType Options);
char * MakeNumberNamesFormat(OptionsType Options,String Format);
void ShortenName(ANNOTATEDFORMULA AnnotatedFormula,int MaximalNameLength);
void ShortenNames(LISTNODE Head,int MaximalNameLength);
void AddNameIndex(ANNOTATEDFORMULA AnnotatedFormula,int Index,char * Format);
void NumberNames(OptionsType Options,LISTNODE Head,char * Format);
void CheckOneDuplicateName(ANNOTATEDFORMULA AnnotatedFormula,
int FixDuplicateNames,char ** NamesBuffer,int * NamesBufferSize,
char * NumberNamesFormat,int * NumberNamesIndex);
void CheckDuplicateNames(LISTNODE Head,int FixDuplicateNames,
char * NumberNamesFormat,int * NumberNamesIndex);
//-----------------------------------------------------------------------------
#endif


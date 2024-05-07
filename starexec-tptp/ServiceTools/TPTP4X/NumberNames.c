#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Examine.h"
#include "Modify.h"
#include "PrintTSTP.h"
#include "tptp4X.h"
//-------------------------------------------------------------------------------------------------
int GetMaximalNameLength(OptionsType Options) {

    String NumberNamesPart;
    int MaximalLength;

    strcpy(NumberNamesPart,"");
    if (strstr(Options.Transformations,"shortennames") != NULL) {
        strcpy(NumberNamesPart,strstr(Options.Transformations,"shortennames"));
    }
    if (strlen(NumberNamesPart) > 0) {
        if (strchr(NumberNamesPart,'+') != NULL) {
            *(strchr(NumberNamesPart,'+')) = '\0';
        }
        MaximalLength = atoi(&(NumberNamesPart[12]));
    } else {
        MaximalLength = -1;
    }
    return(MaximalLength);
}
//-------------------------------------------------------------------------------------------------
char * MakeNumberNamesFormat(OptionsType Options,String Format) {

    String NumberNamesPart;
    int FieldWidth;

    strcpy(NumberNamesPart,"");
    if (strstr(Options.Transformations,"numbernames") != NULL) {
        strcpy(NumberNamesPart,strstr(Options.Transformations,"numbernames"));
    }
    if (strstr(Options.Transformations,"uniquenames") != NULL) {
        strcpy(NumberNamesPart,strstr(Options.Transformations,"uniquenames"));
    }
    if (strlen(NumberNamesPart) > 0) {
        if (strchr(NumberNamesPart,'+') != NULL) {
            *(strchr(NumberNamesPart,'+')) = '\0';
        }
        FieldWidth = atoi(&(NumberNamesPart[11]));
        sprintf(Format,"%%s_%%0%dd",FieldWidth);
        return(Format);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
void ShortenName(ANNOTATEDFORMULA AnnotatedFormula,int MaximalNameLength) {

    SuperString Name;

    GetName(AnnotatedFormula,Name);
    if (strlen(Name) > MaximalNameLength) {
        Name[MaximalNameLength] = '\0';
        SetName(AnnotatedFormula,Name);
    }
}
//-------------------------------------------------------------------------------------------------
void ShortenNames(LISTNODE Head,int MaximalNameLength) {

    while (Head != NULL) {
        if (LogicalAnnotatedFormula(Head->AnnotatedFormula)) {
            ShortenName(Head->AnnotatedFormula,MaximalNameLength);
        }
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------
void AddNameIndex(ANNOTATEDFORMULA AnnotatedFormula,int Index,char * Format) {

    SuperString OldName;
    SuperString MidName;
    SuperString NewName;

    GetName(AnnotatedFormula,OldName);
//----Previously quoted and number names have to be quoted (now)
    if (OldName[0] == '\'' || isdigit(OldName[0])) {
        if (OldName[0] == '\'') {
            strcpy(MidName,&OldName[1]);
            MidName[strlen(MidName) - 1] = '\0';
        } else {
            strcpy(MidName,OldName);
        }
        NewName[0] = '\'';
        sprintf(&NewName[1],Format,MidName,Index);
        strcat(NewName,"'");
    } else {
        sprintf(NewName,Format,OldName,Index);
    }
    assert(SetName(AnnotatedFormula,NewName));
}
//-------------------------------------------------------------------------------------------------
void NumberNames(OptionsType Options,LISTNODE Head,char * Format) {

    int Index = 1;

    while (Head != NULL) {
        AddNameIndex(Head->AnnotatedFormula,Index++,Format);
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------
void CheckOneDuplicateName(ANNOTATEDFORMULA AnnotatedFormula,
int FixDuplicateNames,char ** NamesBuffer,int * NamesBufferSize,
char * NumberNamesFormat,int * NumberNamesIndex) {

    char * Name;

    if ((Name = GetName(AnnotatedFormula,NULL)) != NULL) {
        if (NameInList(Name,*NamesBuffer)) {
            if (FixDuplicateNames) {
                AddNameIndex(AnnotatedFormula,*NumberNamesIndex,NumberNamesFormat);
                (*NumberNamesIndex)++;
            } else {
                printf("ERROR: Duplicate annotated formula name \"%s\"\n",
Name);
                Free((void **)NamesBuffer);
                exit(EXIT_FAILURE);
            }
        }
//----Record the name (possibly changed by now)
        ExtendString(NamesBuffer,GetName(AnnotatedFormula,NULL),
NamesBufferSize);
        ExtendString(NamesBuffer,"\n",NamesBufferSize);
    }
}
//-------------------------------------------------------------------------------------------------
void CheckDuplicateNames(LISTNODE Head,int FixDuplicateNames,
char * NumberNamesFormat,int * NumberNamesIndex) {

    char * NamesBuffer;
    int NamesBufferSize;

//----malloced memory for names
    NamesBuffer = (char *)Malloc(sizeof(String));
    NamesBuffer[0] = '\0';
    NamesBufferSize = sizeof(String);

    while (Head != NULL) {
        CheckOneDuplicateName(Head->AnnotatedFormula,FixDuplicateNames,
&NamesBuffer,&NamesBufferSize,NumberNamesFormat,NumberNamesIndex);
        Head = Head->Next;
    }
    Free((void **)&NamesBuffer);
}
//-------------------------------------------------------------------------------------------------

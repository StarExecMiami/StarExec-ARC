#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Utilities.h"
//-----------------------------------------------------------------------------
void CodingError(char * ErrorMessage) {

    printf("ERROR: (JJ misuse): %s\n",ErrorMessage);
    exit(-1);
}
//-----------------------------------------------------------------------------
void ChangeStringIndex(int* Index,int Change) {

    *Index += Change;
    if (*Index < 0 || *Index >= STRINGLENGTH) {
        printf("ERROR: String index %d out of bounds\n",*Index);
        exit(-1);
    }
}
//-----------------------------------------------------------------------------
void ExtendString(char ** ToExtend,char * ByThis, int * AllocatedLength) {

//----Check if more memory is required
    while ((int)strlen(*ToExtend) + (int)strlen(ByThis) + 1 > 
*AllocatedLength) {
        if ((*ToExtend = (char *)Realloc((void *)*ToExtend,
*AllocatedLength+STRINGLENGTH)) == NULL) {
            printf("ERROR: Cannot realloc in ExtendString\n");
            exit(-1);
        }
        *AllocatedLength += STRINGLENGTH;
    }
    strcat(*ToExtend,ByThis);
}
//-----------------------------------------------------------------------------
void Free(void ** Memory) {

    assert(*Memory != NULL);
    free(*Memory);
    *Memory = NULL;
}
//-----------------------------------------------------------------------------
void * Malloc(int Size) {

    void * Memory;

    if ((Memory = malloc(Size)) == NULL) {
        perror("Malloc");
        exit(-1);
    }

    return(Memory);
}
//-----------------------------------------------------------------------------
void * Realloc(void * OldMemory,int Size) {

    void * Memory;

    if ((Memory = realloc(OldMemory,Size)) == NULL) {
        perror("Malloc");
        exit(-1);
    }

    return(Memory);
}
//-----------------------------------------------------------------------------
char * CopyHeapString(char * String) {

    char * NewString;

//DEBUG printf("MM %d\n",strlen(String)+1);
    NewString = (char *)Malloc(strlen(String)+1);
    strcpy(NewString,String);
    return(NewString);
}
//-----------------------------------------------------------------------------
int MaximumOfInt(int I1,int I2) {

    return(I1 >= I2 ? I1 : I2);
}
//-----------------------------------------------------------------------------
double MaximumOfDouble(double D1,double D2) {

    return(D1 >= D2 ? D1 : D2);
}
//-----------------------------------------------------------------------------
int NameInList(char * Name,char * List) {

    String CRNameCR;

    if (List == NULL || !strcmp(List,"all")) {
        return(1);
    }

    strcpy(CRNameCR,"\n");
    strcat(CRNameCR,Name);
    strcat(CRNameCR,"\n");
    return((strstr(List,&CRNameCR[1]) == List) ||
(strstr(List,CRNameCR) != NULL));

}
//-----------------------------------------------------------------------------

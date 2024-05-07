#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/times.h>
#include "Utilities.h"
//-------------------------------------------------------------------------------------------------
static int SZSStatusReporting = 0;
//-------------------------------------------------------------------------------------------------
int GetSZSStatusReporting(void) {

    return(SZSStatusReporting);
}
//-------------------------------------------------------------------------------------------------
void SetSZSStatusReporting(int UseSZSStatusReporting) {

    SZSStatusReporting = UseSZSStatusReporting;
}
//-------------------------------------------------------------------------------------------------
void ReportError(const char * SZSStatus,char * ErrorDetails,int Exit) {

    if (SZSStatusReporting) {
        printf("%% SZS status %s : %s\n",SZSStatus,ErrorDetails);
    } else {
        printf("ERROR: %s\n",ErrorDetails);
    }
    if (Exit) {
        exit(EXIT_FAILURE);
    }
}
//-------------------------------------------------------------------------------------------------
void CodingError(char * ErrorMessage) {

    printf("ERROR: (JJ misuse): %s\n",ErrorMessage);
    exit(EXIT_FAILURE);
}
//-------------------------------------------------------------------------------------------------
void ChangeStringIndex(int* Index,int Change) {

    *Index += Change;
    if (*Index < 0 || *Index >= STRINGLENGTH) {
        CodingError("String index out of bounds");
    }
}
//-------------------------------------------------------------------------------------------------
void Free(void ** Memory) {

    assert(*Memory != NULL);
    free(*Memory);
    *Memory = NULL;
}
//-------------------------------------------------------------------------------------------------
void * Malloc(size_t Size) {

    void * Memory;

    if ((Memory = malloc(Size)) == NULL) {
        perror("Malloc");
        exit(EXIT_FAILURE);
    }

    return(Memory);
}
//-------------------------------------------------------------------------------------------------
void * Realloc(void * OldMemory,size_t Size) {

    void * Memory;

    if (Size > 0 && (Memory = realloc(OldMemory,Size)) == NULL) {
        perror("Realloc");
        CodingError("Realloc failed");
    }

    return(Memory);
}
//-------------------------------------------------------------------------------------------------
void ExtendString(char ** ToExtend,char * ByThis, int * AllocatedLength) {

//----Check if more memory is required
    while (*ToExtend == NULL ||
(int)strlen(*ToExtend) + (int)strlen(ByThis) + 1 > *AllocatedLength) {
        *ToExtend = (char *)Realloc((void *)*ToExtend,*AllocatedLength+STRINGLENGTH);
        if (*AllocatedLength == 0) {
            strcpy(*ToExtend,"");
        }
        *AllocatedLength += STRINGLENGTH;
    }
    strcat(*ToExtend,ByThis);
}
//-------------------------------------------------------------------------------------------------
void MakeBuffer(char ** Buffer,int * BufferSize) {

    *Buffer = (char *)Malloc(sizeof(String));
    (*Buffer)[0] = '\0';
    *BufferSize = sizeof(String);
}
//-------------------------------------------------------------------------------------------------
void ExtendAndFree(char ** Buffer,char * WithThisToFree,int * BufferSize) {

    ExtendString(Buffer,WithThisToFree,BufferSize);
    Free((void **)&WithThisToFree);
}
//-------------------------------------------------------------------------------------------------
char * BufferReturn(char ** Buffer,char * UserBuffer) {

//----Check if user provided memory or not
    if (UserBuffer != NULL) {
        strcpy(UserBuffer,*Buffer);
        Free((void **)Buffer);
        return(UserBuffer);
    } else {
        return(*Buffer);
    }
}
//-------------------------------------------------------------------------------------------------
char * CopyHeapString(char * String) {

    char * NewString;

    if (String == NULL) {
        return(NULL);
    } else {
// printf("MM %ld for ==%s==\n",strlen(String)+1,String);
        NewString = (char *)Malloc(sizeof(char) * (strlen(String)+1));
        strcpy(NewString,String);
        return(NewString);
    }
}
//-------------------------------------------------------------------------------------------------
int MinimumOfInt(int I1,int I2) {

    return(I1 <= I2 ? I1 : I2);
}
//-------------------------------------------------------------------------------------------------
double MinimumOfDouble(double D1,double D2) {

    return(D1 <= D2 ? D1 : D2);
}
//-------------------------------------------------------------------------------------------------
int MaximumOfInt(int I1,int I2) {

    return(I1 >= I2 ? I1 : I2);
}
//-------------------------------------------------------------------------------------------------
double MaximumOfDouble(double D1,double D2) {

    return(D1 >= D2 ? D1 : D2);
}
//-------------------------------------------------------------------------------------------------
void SeedRand(int Seed) {

    struct tms TimesBuffer;

    if (Seed) {
        srand(times(&TimesBuffer));
    }
}
//-------------------------------------------------------------------------------------------------
long RandomInRange(long Lowest,long Highest,int Seed) {

    SeedRand(Seed);
    return(Lowest + lround((rand()-1)/(double)(RAND_MAX-1) * (Highest-Lowest)));
}
//-------------------------------------------------------------------------------------------------
int NameInList(char * Name,char * List) {

    SuperString CRNameCR;

    if (List == NULL || !strcmp(List,"all")) {
        return(1);
    }

    strcpy(CRNameCR,"\n");
    strcat(CRNameCR,Name);
    strcat(CRNameCR,"\n");
    return((strstr(List,&CRNameCR[1]) == List) || (strstr(List,CRNameCR) != NULL));

}
//-------------------------------------------------------------------------------------------------
int RemoveNameFromList(char * Name,char * List) {

    SuperString CRNameCR;
    char * Start;
    SuperString Shortened;

    strcpy(CRNameCR,"\n");
    strcat(CRNameCR,Name);
    strcat(CRNameCR,"\n");
    if ((Start = strstr(List,&CRNameCR[1])) != List) {
        if ((Start = strstr(List,CRNameCR)) != NULL) {
            Start++;
        }
    }
    if (Start != NULL) {
        strcpy(Shortened,List);
        strcpy(Shortened+(Start-List),strchr(Start,'\n')+1);
        strcpy(List,Shortened);
        return(1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int Tokenize(char * BigString,StringParts SmallParts,char * Delimiters) {

    int NumberOfParts;

    if (BigString == NULL) {
        return(0);
    }

//DEBUG printf("About to tokenize ==%s==\n",BigString);
    NumberOfParts = 0;
    SmallParts[NumberOfParts] = strtok(BigString,Delimiters);
    while (SmallParts[NumberOfParts] != NULL) {
//DEBUG printf("part is ==%s==\n",SmallParts[NumberOfParts]);
        NumberOfParts++;
        if (NumberOfParts == MAX_STRING_PARTS) {
            CodingError("Ran out of string parts");
        }
        SmallParts[NumberOfParts] = strtok(NULL,Delimiters);
    }

    return(NumberOfParts);
}
//-------------------------------------------------------------------------------------------------
int UniquifyStringParts(StringParts Parts) {

    int Found,Current,Other,Shift;

    Current = 0;
    while (Parts[Current] != NULL) {
        Found = 0;
        Other = Current + 1;
        while (Parts[Other] != NULL) {
            if (!strcmp(Parts[Current],Parts[Other])) {
                Found = 1;
                Shift = Other;
                do {
                    Parts[Shift] = Parts[Shift+1];
                    Shift++;
                } while (Parts[Shift] != NULL);
            } else {
                Other++;
            }
        }
        if (!Found) {
            Current++;
        }
    }
    return(Current);
}
//-------------------------------------------------------------------------------------------------
void PrintTimeStamp(char * Message) {

    static clock_t LastTime = 0;
    clock_t ThisTime;

    if ((ThisTime = clock()) == (clock_t)-1) {
        printf("ERROR: Cannot PrintTimeStamp %s\n",Message == NULL ? "" :
Message);
    } else {
        if (Message != NULL) {
            printf("%s: ",Message);
        }
        printf("Time delta: %f\n",((double)(ThisTime-LastTime))/CLOCKS_PER_SEC);
        LastTime = ThisTime;
    }
}
//-------------------------------------------------------------------------------------------------
void Trim(char * TheString) {

    char * IntoString;

    IntoString = TheString;
    while (isspace(*IntoString)) {
        IntoString++;
    }
    memmove(TheString,IntoString,strlen(IntoString)+1);
    IntoString = TheString + strlen(TheString) - 1;
    while (isspace(*IntoString)) {
        IntoString--;
    }
    *(++IntoString) = '\0';
}
//-------------------------------------------------------------------------------------------------
void StringToLower(char * TheString) {

    int Index;

    Index = 0;
    while (TheString[Index] != '\0') {
        TheString[Index] = tolower(TheString[Index]);
        Index++;
    }
}
//-------------------------------------------------------------------------------------------------

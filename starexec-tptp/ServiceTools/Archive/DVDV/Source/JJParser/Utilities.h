#ifndef UTILITIES_H
#define UTILITIES_H
//-----------------------------------------------------------------------------
#define STRINGLENGTH 1024
#define SUPERSTRINGLENGTH 10240

typedef char String[STRINGLENGTH];
typedef char SuperString[SUPERSTRINGLENGTH];
//-----------------------------------------------------------------------------
void CodingError(char * ErrorMessage);

void ChangeStringIndex(int* Index,int Change);
void ExtendString(char ** ToExtend,char * ByThis, int * AllocatedLength);
void Free(void ** Memory);
void * Malloc(int Size);
void * Realloc(void * OldMemory,int Size);

char * CopyHeapString(char * String);
int MaximumOfInt(int I1,int I2);
double MaximumOfDouble(double D1,double D2);
int NameInList(char * Name,char * List);
//-----------------------------------------------------------------------------
#endif

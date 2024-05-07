#ifndef TPTP4X_H
#define TPTP4X_H
//-----------------------------------------------------------------------------
#define MAX_GROUPS 1024
#define TEMP_DIRECTORY "/tmp"
#define TEMP_TEMPLATE "TPIIXXXXXX"
#define MAX_TEMPORARY_FILENAMES 128
#define MAX_WAITENV_VARIABLES 128
#define MAX_GET_GROUPS 128;
//-----------------------------------------------------------------------------
typedef struct {
    int Quietness;
} OptionsType;

typedef char * GroupNamesType[MAX_GROUPS];

typedef String TemporaryFileNamesArray[MAX_TEMPORARY_FILENAMES];

typedef struct {
    OptionsType Options;
    char * CommandName;
    FORMULA CommandDetails;
    SIGNATURE Signature;
    LISTNODE LogicalFormulae;
    pthread_mutex_t * ThreadMutex;
    pthread_cond_t * ThreadCondition;
} ExecuteDataType;
//-----------------------------------------------------------------------------
#endif


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/param.h>
#include <sys/types.h>
#include <pwd.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Tokenizer.h"
#include "FileUtilities.h"
//--------------------------------------------------------------------------------------------------
READFILE NewReadFile(void) {

    READFILE Stream;

    Stream = (READFILE)(Malloc(sizeof(ReadFile)));

    Stream->FileName = NULL;
    Stream->FileHandle = NULL;
    Stream->Line = 1;
    Stream->Character = 0;
    Stream->StringFileContent = NULL;
    Stream->Overshot = 0;
    Stream->StringOffset = 0;
    Stream->CurrentCharacter = 0;
    Stream->CurrentToken = NULL;
    Stream->Auxilliary = NULL;
    Stream->NeedNonLogicTokens = GetNeedForNonLogicTokens();
    Stream->Warnings = GetWarnings();

    return(Stream);
}
//--------------------------------------------------------------------------------------------------
PRINTFILE NewPrintFile(void) {

    PRINTFILE Stream;

    Stream = (PRINTFILE)(Malloc(sizeof(PrintFile)));

    Stream->FileName = NULL;
    Stream->FileHandle = NULL;
    Stream->StringFileContent = NULL;

    return(Stream);
}
//--------------------------------------------------------------------------------------------------
void PathBasename(char * Path,String Basename,char * Suffix) {

    char * Slash;

//----Take from after the last slash
    if ((Slash = strrchr(Path,'/')) == NULL) {
        strcpy(Basename,Path);
    } else {
        strcpy(Basename,Slash+1);
    }
//----Chop off the suffix
    if (Suffix != NULL && (Slash = strstr(Basename,Suffix)) != NULL &&
!strcmp(Slash,Suffix)) {
        *Slash = '\0';
    }
}
//-------------------------------------------------------------------------------------------------
char * ExpandFileName(char * FileName,String ExpandedFileName) {

    char * Home;
    char * Slash;
    char * UserName;
    struct passwd *PasswdEntry;

//----If first character of filename is ~, expand to $HOME
    if (FileName[0] == '~' && FileName[1] == '/') {
        if ((Home = getenv("HOME")) != NULL) {
            strcpy(ExpandedFileName,Home);
            strcat(ExpandedFileName,&(FileName[1]));
            return(ExpandedFileName);
        }
        return(NULL);
    } 

//----Another user's home
    if (FileName[0] == '~' && isalpha(FileName[1])) {
        if ((Slash = strchr(FileName,'/')) != NULL && strlen(Slash+1) > 0) {
            UserName = strtok(FileName+1,"/");
            if ((PasswdEntry = getpwnam(UserName)) != NULL) {
                strcpy(ExpandedFileName,PasswdEntry->pw_dir);
                strcat(ExpandedFileName,Slash);
                return(ExpandedFileName);
            }
        }
        return(NULL);
    } 

//----Absolute
    if ((FileName[0] == '.' || FileName[0] =='/')) {
        strcpy(ExpandedFileName,FileName);
        return(ExpandedFileName);
    }

//----Otherwise no expansion (NULL is error case, "" is not expanded case)
    strcpy(ExpandedFileName,"");
    return(ExpandedFileName);
}
//-------------------------------------------------------------------------------------------------
char * ExpandAndFindFileName(char * FileName,char * IncludingFileName,String ExpandedFileName) {

    char * Paths[] = {
        "",
        "Problems",
        "Axioms"
    };
    int NumberOfPaths = sizeof(Paths)/sizeof(char *);
    char * Extensions[] = {
        "",
        ".p",
        ".tptp",
        ".ax",
        ".eq" };
    int NumberOfExtensions = sizeof(Extensions)/sizeof(char *);

    int PathIndex;
    int ExtensionIndex;
    String TPTPDirectory;
    String Domain;
    int DomainOnOff;
    char * BaseName;
    char * Slash;
    char * Home;
    struct passwd *PasswdEntry;

//DEBUG printf("Start looking for ---%s--- relative to ---%s---\n",FileName,IncludingFileName);
//----Expand ~ and ~user
    if (ExpandFileName(FileName,ExpandedFileName) == NULL) {
        return(NULL);
    } 

//----If expanded to something it should be found
    if (strlen(ExpandedFileName) > 0) {
//----See if already found
        if (access(ExpandedFileName,R_OK) == 0) {
            return(ExpandedFileName);
        } else {
            return(NULL);
        }
    }

//----Otherwise we have to search
//----Try the base directory of the including file 
    if (IncludingFileName != NULL) {
//DEBUG printf("Look relative to %s\n",IncludingFileName);
        strcpy(ExpandedFileName,IncludingFileName);
        if ((Slash = strrchr(ExpandedFileName,'/')) != NULL) {
            *(++Slash) = '\0';
            strcat(ExpandedFileName,FileName);
            if (access(ExpandedFileName,R_OK) == 0) {
//DEBUG printf("Found it relative to %s\n",IncludingFileName);
                return(ExpandedFileName);
            }
        }
    }

//----If the including file has no name, use CWD
    if (IncludingFileName == NULL) {
        getcwd(ExpandedFileName,MAXPATHLEN);
//DEBUG printf("Look relative to CWD %s\n",ExpandedFileName);
        strcat(ExpandedFileName,"/");
        strcat(ExpandedFileName,FileName);
//----This short cut does not provide a full file name
// strcpy(ExpandedFileName,FileName);
        if (access(ExpandedFileName,R_OK) == 0) {
//DEBUG printf("Found it relative to %s\n",ExpandedFileName);
            return(ExpandedFileName);
        }
    }

//----Try the TPTP directory, and TPTP variations
//DEBUG printf("Look relative to TPTP\n");
    strcpy(TPTPDirectory,"");
    Home = getenv("TPTP");
    if (Home == NULL) {
        Home = getenv("TPTP_HOME");
//----If no TPTP_HOME, try the tptp user (aaargh)
        if (Home == NULL && (PasswdEntry = getpwnam("tptp")) != NULL) {
            Home = PasswdEntry->pw_dir;
        }
//----Now look in the TPTP directory from there
        if (Home != NULL) {
            strcpy(TPTPDirectory,Home);
            strcat(TPTPDirectory,"/TPTP");
        }
    } else {
        strcpy(TPTPDirectory,Home);
    }
        
    if (strlen(TPTPDirectory) > 0) {
//----Extract domain and make the path
        if ((Slash = strrchr(FileName,'/')) == NULL) {
            BaseName = FileName;
        } else {
            BaseName = Slash+1;
        }
        strncpy(Domain,BaseName,3);
        Domain[3] = '\0';
//----Check various extensions and paths
        for (PathIndex=0;PathIndex < NumberOfPaths;PathIndex++) {
            for (DomainOnOff=0; DomainOnOff <= 1; DomainOnOff++) {
                for (ExtensionIndex=0;ExtensionIndex < NumberOfExtensions;ExtensionIndex++) {
                    strcpy(ExpandedFileName,TPTPDirectory);
                    if (strcmp(Paths[PathIndex],"")) {
                        strcat(ExpandedFileName,"/");
                        strcat(ExpandedFileName,Paths[PathIndex]);
                    }
                    if (DomainOnOff) {
                        strcat(ExpandedFileName,"/");
                        strcat(ExpandedFileName,Domain);
                    }
                    strcat(ExpandedFileName,"/");
                    strcat(ExpandedFileName,FileName);
                    strcat(ExpandedFileName,Extensions[ExtensionIndex]);
//DEBUG printf("look for ==%s===\n",ExpandedFileName);
                    if (access(ExpandedFileName,R_OK) == 0) {
                        return(ExpandedFileName);
                    }
                }
            }
        }
    }

    return(NULL);
}
//-------------------------------------------------------------------------------------------------
char * CleanTheFileName(char * OriginalFileName,char * CleanFileName) {

//    int Index;
    String NewName;

//----Removed quotes around file name
    strcpy(CleanFileName,OriginalFileName);
    if ((CleanFileName[0] == '\'' || CleanFileName[0] == '\"') && 
CleanFileName[0] == CleanFileName[strlen(CleanFileName)-1]) {
        strcpy(NewName,&CleanFileName[1]);
        NewName[strlen(NewName)-1] = '\0';
        strcpy(CleanFileName,NewName);
    }
//----Remove nasty characters
//    for (Index = 0; Index < strlen(CleanFileName); Index++) {
//        if (!isalnum(CleanFileName[Index])) {
//            CleanFileName[Index] = '_';
//        }
//    }
    return(CleanFileName);
}
//-------------------------------------------------------------------------------------------------
FILE * OpenFileInMode(String FileName,char * Mode) {
    
    FILE * Stream;
    String ErrorMessage;
    
    if ((Stream = fopen(FileName,Mode)) == NULL) {
        perror("Opening file");
        sprintf(ErrorMessage,"Could not open file %s in %s mode",FileName,Mode);
        ReportError("OSError",ErrorMessage,0);
        return(NULL);
    } else {
        return(Stream);
    }
}   
//-------------------------------------------------------------------------------------------------
PRINTFILE OpenFILEPrintFile(FILE * OpenStream,char * FileName) {

    PRINTFILE Stream;
        
    if (OpenStream == NULL) {
        return(NULL);
    }

    Stream = NewPrintFile();
    Stream->FileHandle = OpenStream;
    Stream->FileName = FileName;

    return(Stream);
}
//-------------------------------------------------------------------------------------------------
PRINTFILE OpenStringPrintFile(char * Content) {

    PRINTFILE Stream;

    if (Content == NULL) {
        return(NULL);
    }

    Stream = NewPrintFile();
    Stream->StringFileContent = Content;

    return(Stream);
}
//-------------------------------------------------------------------------------------------------
PRINTFILE OpenPrintFile(char * OriginalFileName) {

    String FileName;
    PRINTFILE Stream;

    CleanTheFileName(OriginalFileName,FileName);

//----If the filename is "--" use stdout
    if (!strcmp(FileName,"--")) {
        return(OpenFILEPrintFile(stdout,"stdout"));
    }

    if (ExpandFileName(OriginalFileName,FileName) == NULL) {
        return(NULL);
    }

    Stream = NewPrintFile();
    if ((Stream->FileHandle = OpenFileInMode(FileName,"w")) == NULL) {
        Free((void **)&Stream);
        return(NULL);
    }
//----Record the file name
    Stream->FileName = CopyHeapString(FileName);

    return(Stream);
}
//-------------------------------------------------------------------------------------------------
void ClosePrintFile(PRINTFILE Stream) {

    if (Stream->FileHandle != NULL) {
//----If a file name, then close the file
        if (Stream->FileName != NULL) {
            Free((void **)&(Stream->FileName));
            fclose(Stream->FileHandle);
        }
//----Else a string file - do nothing - leave to user
    } 
    Free((void **)&Stream);
}
//-------------------------------------------------------------------------------------------------
void PFprintf(PRINTFILE Stream,char * Format,...) {

    va_list Data;
    String LocalContent;

    va_start(Data,Format);
//----Find out if FILE or String
    if (Stream->FileHandle != NULL) {
        vfprintf(Stream->FileHandle,Format,Data);
    }
    if (Stream->StringFileContent != NULL) {
        if (vsnprintf(LocalContent,STRINGLENGTH,Format,Data) >= STRINGLENGTH) {
            CodingError("Component buffer overflow in string directed printf");
        } else {
//----Extremely dangerous - cannot tell if there's anough memory
            strcat(Stream->StringFileContent,LocalContent);
        }
    }
    va_end(Data);
}
//-------------------------------------------------------------------------------------------------
READFILE OpenFILEReadFile(char * FileName,FILE * OpenStream) {

    READFILE Stream;

    if (OpenStream == NULL) {
        return(NULL);
    }

    Stream = NewReadFile();
    Stream->FileName = CopyHeapString(FileName);
    Stream->FileHandle = OpenStream;

    return(Stream);
}
//-------------------------------------------------------------------------------------------------
READFILE OpenStringReadFile(char * Content) {

    READFILE Stream;

    if (Content == NULL) {
        return(NULL);
    }

    Stream = NewReadFile();
    Stream->StringFileContent = CopyHeapString(Content);
    Stream->StringOffset = 0;

    return(Stream);
}
//-------------------------------------------------------------------------------------------------
READFILE OpenReadFile(char * OriginalFileName,char * IncludingFileName) {

    String FinalFileName;
    String FileName;
    READFILE Stream;

    CleanTheFileName(OriginalFileName,FileName);

//----If the filename is "--" use stdin
    if (!strcmp(FileName,"--")) {
        return(OpenFILEReadFile(FileName,stdin));
    }

    if (ExpandAndFindFileName(FileName,IncludingFileName,FinalFileName) == NULL) {
        return(NULL);
    }

    Stream = NewReadFile();

    if ((Stream->FileHandle = OpenFileInMode(FinalFileName,"r")) == NULL) {
        Free((void **)&Stream);
        return(NULL);
    }

//----Record the file name
    Stream->FileName = CopyHeapString(FinalFileName);

////----Copy the base directory across if none there
//    if (strlen(BaseDirectory) == 0) {
////----If current file is relative, find out current
//        if (FinalFileName[0] != '/') {
//            getcwd(BaseDirectory,MAXPATHLEN);
//            strcat(BaseDirectory,"/");
//            strcat(BaseDirectory,FinalFileName);
//        } else {
//            strcpy(BaseDirectory,FinalFileName);
//        }
////----Lop off file name
//        if ((LastSlash = strrchr(BaseDirectory,'/')) != NULL) {
//            *LastSlash = '\0';
//        } else {
//            CodingError("Setting the base directory, no slash");
//        }
//    }

    return(Stream);
}
//-------------------------------------------------------------------------------------------------
void CloseReadFile(READFILE Stream) {

    assert((Stream->FileHandle != NULL || Stream->StringFileContent != NULL) &&
(Stream->FileHandle == NULL || Stream->StringFileContent == NULL));

    if (Stream->FileHandle != NULL) {
//----If a file name, then close the file
        if (Stream->FileName != NULL) {
            Free((void **)&(Stream->FileName));
            fclose(Stream->FileHandle);
        }
//----Else a string file
    } else if (Stream->StringFileContent != NULL) {
        Free((void **)&(Stream->StringFileContent));
    } 
    FreeToken(&(Stream->CurrentToken));
    FreeToken(&(Stream->Auxilliary));
    Free((void **)&Stream);
}
//-------------------------------------------------------------------------------------------------
void RemoveFile(String FileName) {

    String ErrorMessage;

    if (unlink(FileName) == -1) {
        perror("Deleting file/directory");
        sprintf(ErrorMessage,"Could not delete %s",FileName);
        ReportError("OSError",ErrorMessage,0);
    }
}
//-------------------------------------------------------------------------------------------------
void RemoveFileDirectory(String FileName) {

    char * Slash;

    if ((Slash = strchr(FileName,'/')) == NULL) {
        CodingError("Removing non-directory");
    }
    RemoveFile(FileName);
    *Slash = '\0';
    RemoveFile(FileName);
}
//-------------------------------------------------------------------------------------------------

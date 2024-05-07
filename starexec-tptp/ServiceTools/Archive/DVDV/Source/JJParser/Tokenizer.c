#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <pwd.h>
#include "Tokenizer.h"
#include "Utilities.h"
//-----------------------------------------------------------------------------
//----Static for all, which really needs to be passed in when a stream is
//----opened, rather than being set here and copied from here (Yaaaack)
static int NeedNonLogicTokens = 0;
//-----------------------------------------------------------------------------
void CharacterError(READFILE Stream) {

    printf("ERROR: Line %d Char %d Character \"%c\"\n",
Stream->Line,Stream->Character,CurrentCharacter(Stream));
    exit(-1);
}
//-----------------------------------------------------------------------------
//---- Function Character returns the following values depending on the 
//---- Operation value:
//---- -1 : Read into static, return that one
//---- 0 : Return the static
//---- 1 : Return the static, & read next from File into static
int Character(READFILE Stream,int Operation) {

    int Auxilliary;

    assert((Stream->FileHandle != NULL || Stream->StringFileContent != NULL) &&
(Stream->FileHandle == NULL || Stream->StringFileContent == NULL));

    switch (Operation) {
        case 1:
//----Read into static, return it
            if (Stream->CurrentCharacter == '\n') {
                Stream->Line++;
                Stream->Character = 0;
            }
            if (Stream->FileHandle != NULL) {
                Stream->CurrentCharacter = fgetc(Stream->FileHandle);
            } else if (Stream->StringFileContent != NULL) {
                Stream->CurrentCharacter = 
Stream->StringFileContent[Stream->StringOffset];
                Stream->StringOffset++;
//----Convert end of string to end of file
                if (Stream->CurrentCharacter == '\0') {
                    Stream->CurrentCharacter = EOF;
                }
            } else {
                CharacterError(Stream);
            }
            Stream->Character++;
            return(Stream->CurrentCharacter);
            break;
        case 0:
//----Return static
            return(Stream->CurrentCharacter);
            break;
       case -1:
//----Return static, read next into static
            Auxilliary = Stream->CurrentCharacter;
            if (Stream->CurrentCharacter == '\n') {
                Stream->Line++;
                Stream->Character = 0;
            }
            if (Stream->FileHandle != NULL) {
                Stream->CurrentCharacter = fgetc(Stream->FileHandle);
            } else if (Stream->StringFileContent != NULL) {
                Stream->CurrentCharacter = 
Stream->StringFileContent[Stream->StringOffset];
                Stream->StringOffset++;
//----Convert end of string to end of file
                if (Stream->CurrentCharacter == '\0') {
                    Stream->CurrentCharacter = EOF;
                }
            } else {
                CharacterError(Stream);
            }
            Stream->Character++;
            return(Auxilliary);
            break;
       default:
            return(EOF);
            break;
    }
}
//-----------------------------------------------------------------------------
void SetNeedForNonLogicTokens(int OnOff) {

    NeedNonLogicTokens = OnOff;
}
//-----------------------------------------------------------------------------
int GetNeedForNonLogicTokens(READFILE Stream) {

    return(Stream->NeedNonLogicTokens);
}
//-----------------------------------------------------------------------------
StatusType StringToStatus(char * String) {

    if (!strcmp(String,"initial")) {
        return(initial);
    }
    if (!strcmp(String,"derived")) {
        return(derived);
    }
    if (!strcmp(String,"axiom")) {
        return(axiom);
    }
    if (!strcmp(String,"definition")) {
        return(definition);
    }
    if (!strcmp(String,"knowledge")) {
        return(knowledge);
    }
    if (!strcmp(String,"assumption")) {
        return(assumption);
    }
    if (!strcmp(String,"hypothesis")) {
        return(hypothesis);
    }
    if (!strcmp(String,"conjecture")) {
        return(conjecture);
    }
    if (!strcmp(String,"negated_conjecture")) {
        return(negated_conjecture);
    }
    if (!strcmp(String,"lemma")) {
        return(lemma);
    }
    if (!strcmp(String,"theorem")) {
        return(theorem);
    }
    if (!strcmp(String,"plain")) {
        return(plain);
    }
    if (!strcmp(String,"unknown")) {
        return(unknown);
    }
    printf("ERROR: String %s not a status\n",String);
    exit(-1);
}
//-----------------------------------------------------------------------------
char * StatusToString(StatusType Status) {

     switch (Status) {
        case initial:
            return("initial");
            break;
        case derived:
            return("derived");
            break;
        case axiom:
            return("axiom");
            break;
        case definition:
            return("definition");
            break;
        case knowledge:
            return("knowledge");
            break;
        case assumption:
            return("assumption");
            break;
        case hypothesis:
            return("hypothesis");
            break;
        case conjecture:
            return("conjecture");
            break;
        case negated_conjecture:
            return("negated_conjecture");
            break;
        case lemma:
            return("lemma");
            break;
        case theorem:
            return("theorem");
            break;
        case plain:
            return("plain");
            break;
        case unknown:
            return("unknown");
            break;
        default:
            printf("ERROR: Not a status\n");
            exit(-1);
    }
}
//-----------------------------------------------------------------------------
ConnectiveType StringToConnective(char * String) {

    if (!strcmp(String,"|")) {
        return(disjunction);
    }
    if (!strcmp(String,"&")) {
        return(conjunction);
    }
    if (!strcmp(String,"<=>")) {
        return(equivalence);
    }
    if (!strcmp(String,"=>")) {
        return(implication);
    }
    if (!strcmp(String,"<=")) {
        return(reverseimplication);
    }
    if (!strcmp(String,"<~>")) {
        return(nonequivalence);
    }
    if (!strcmp(String,"~|")) {
        return(negateddisjunction);
    }
    if (!strcmp(String,"~&")) {
        return(negatedconjunction);
    }
    if (!strcmp(String,"~")) {
        return(negation);
    }
    if (!strcmp(String,"--")) {
        return(negation);
    }
    if (!strcmp(String,"!")) {
        return(universal);
    }
    if (!strcmp(String,"?")) {
        return(existential);
    }
    printf("ERROR: String %s not a connective\n",String);
    exit(-1);
}
//-----------------------------------------------------------------------------
char * ConnectiveToString(ConnectiveType Connective) {

    switch (Connective) {
        case disjunction:
            return("|");
            break;
        case conjunction:
            return("&");
            break;
        case equivalence:
            return("<=>");
            break;
        case implication:
            return("=>");
            break;
        case reverseimplication:
            return("<=");
            break;
        case nonequivalence:
            return("<~>");
            break;
        case negateddisjunction:
            return("~|");
            break;
        case negatedconjunction:
            return("~&");
            break;
        case negation:
            return("~");
            break;
        case universal:
            return("!");
            break;
        case existential:
            return("?");
            break;
        default:
            printf("ERROR: Not a connective\n");
            exit(-1);
    }
}
//-----------------------------------------------------------------------------
TOKEN BuildToken(TokenType TypeToken,char * LocalValue) {

    TOKEN NewToken;

    NewToken = (TOKEN)(Malloc(sizeof(ReadToken)));
    NewToken->KindToken = TypeToken;
    NewToken->NameToken = CopyHeapString(LocalValue);

//DEBUG printf("token built is ==%s==\n",NewToken->NameToken);
    return(NewToken);
}
//-----------------------------------------------------------------------------
TOKEN CloneToken(TOKEN TokenCopy) {

    return(BuildToken(TokenCopy->KindToken,TokenCopy->NameToken));
}
//---------------------------------------------------------------------------
void FreeToken(TOKEN * Pointer) {

    if (*Pointer != NULL) {
        Free((void **)&((*Pointer)->NameToken));
        Free((void **)Pointer);
    }
}
//-----------------------------------------------------------------------------
void IncrementTokenIndex(READFILE Stream,int* Index) {

    (*Index)++;
    if (*Index >= SUPERSTRINGLENGTH) {
        printf("ERROR: Token too long\n");
        CharacterError(Stream);
    }
}
//-----------------------------------------------------------------------------
TOKEN GetNextToken(READFILE Stream) {

    int CurrentChar,PreviousChar;
    int Index;
//----static so it doesn't have to get allocated everytime (very often!)
    static SuperString LocalValue;

//DEBUG printf("char was ==%c==\n",CurrentCharacter(Stream));
    if (Stream->Overshot) {
//DEBUG printf("overshot\n");
        CurrentChar = CurrentCharacter(Stream);
    } else {
//DEBUG printf("get next\n");
        CurrentChar = NextCharacter(Stream);
    }
    Stream->Overshot = 0;

//----Skip whitespace
    while (isspace(CurrentChar)) {
        PreviousChar = CurrentChar;
        CurrentChar = NextCharacter(Stream);
//----Check for a blank line, if required
        if (!Stream->IgnoreBlankLines && Stream->NeedNonLogicTokens && 
PreviousChar == '\n' && CurrentChar == '\n') {
            Stream->Overshot = 1;
            return(BuildToken(blank_line_token,""));
        }
    }

//DEBUG printf("char is ==%c==\n",CurrentChar);
    switch (CurrentChar) {
        case '/':
//----This is the code if /*..*/ comments should not be trashed
//            Index = 0;
//            LocalValue[Index++] = CurrentChar;
            PreviousChar = CurrentChar;
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '*') {
//                LocalValue[Index] = CurrentChar;
                while (CurrentChar != EOF && (CurrentChar != '/' || 
PreviousChar != '*')) {
                    PreviousChar = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
//                    IncrementTokenIndex(Stream,&Index);
//                    LocalValue[Index] = CurrentChar;
                }
                if (CurrentChar == '/') {
//----Add eoln if it's there
                    CurrentChar = NextCharacter(Stream);
                    if (CurrentChar == '\n') {
//                        IncrementTokenIndex(Stream,&Index);
//                        LocalValue[Index] = CurrentChar;
                    } else {
                        Stream->Overshot = 1;
                    }
//                    IncrementTokenIndex(Stream,&Index);
//                    LocalValue[Index] = '\0';
//                  if (Stream->NeedNonLogicTokens) {
//                      return(BuildToken(comment_token,LocalValue));
//                  } else {
//                      return(GetNextToken(Stream));
//                  }
                    return(GetNextToken(Stream));
                } else {
                    CharacterError(Stream);
                    return(NULL);
                }
            } else {
                CharacterError(Stream);
                return(NULL);
            }
            break;
        case '%':
        case '#':
            if (Stream->NeedNonLogicTokens) {
                Index = 0;
                LocalValue[Index] = CurrentChar;
                while (CurrentChar != '\n' && CurrentChar != EOF) {
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                    LocalValue[Index] = CurrentChar;
                } 
                IncrementTokenIndex(Stream,&Index);
                LocalValue[Index] = '\0';
                return(BuildToken(comment_token,LocalValue));
            } else {
//----Do all sequences of comments (recursive approach gave stack overflow)
                do {
                    while (CurrentChar != '\n' && CurrentChar != EOF) {
                        CurrentChar = NextCharacter(Stream);
                    }
                    CurrentChar = NextCharacter(Stream);
                } while (CurrentChar == '%' || CurrentChar == '#');
                Stream->Overshot = 1;
                return(GetNextToken(Stream));
            }
            break;
        case '\'':
            Index = 0;
            LocalValue[Index] = CurrentChar;
            do {
                CurrentChar = NextCharacter(Stream);
                IncrementTokenIndex(Stream,&Index);
                LocalValue[Index] = CurrentChar;
            } while (CurrentChar != '\'');
            IncrementTokenIndex(Stream,&Index);
            LocalValue[Index] = '\0';
            return(BuildToken(lower_word,LocalValue));
            break;
        case '(':
            return(BuildToken(punctuation,"("));
            break;
        case ')':
            return(BuildToken(punctuation,")"));
            break;
        case '[':
            return(BuildToken(punctuation,"["));
            break;
        case ']':
            return(BuildToken(punctuation,"]"));
            break;
        case '!':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '=') {
                return(BuildToken(lower_word,"$notequal"));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(quantifier,"!"));
            }
            break;
        case '?':
            return(BuildToken(quantifier,"?"));
            break;
        case '.':
            return(BuildToken(punctuation,"."));
            break;
        case ':':
            return(BuildToken(punctuation,":"));
            break;
        case ',':
            return(BuildToken(punctuation,","));
            break;
        case '<':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '='){
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == '>') {
                    return(BuildToken(binary_connective,"<=>"));
                } else {
                    Stream->Overshot = 1;
                    return(BuildToken(binary_connective,"<="));
                }
            } else {
                if (CurrentChar == '~') {
                    CurrentChar = NextCharacter(Stream);
                    if (CurrentChar == '>') {
                        return(BuildToken(binary_connective,"<~>"));
                    } else {
                        CharacterError(Stream);
                        return(NULL);
                    }
                } else {
                    CharacterError(Stream);
                    return(NULL);
                }
            }
            break;
        case '=':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '>') {
                return(BuildToken(binary_connective,"=>"));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(lower_word,"$equal"));
            }
            break;
        case '~':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '|') {
                return(BuildToken(binary_connective,"~|"));
            } else {
                if (CurrentChar == '&') {
                    return(BuildToken(binary_connective,"~&"));
                } else {
                    Stream->Overshot = 1;
                    return(BuildToken(unary_connective,"~"));
                }
            }
            break;
        case '+':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '+') {
                return(BuildToken(unary_connective,"++"));
            } else {
                CharacterError(Stream);
                return(NULL);
            }
            break;
        case '-':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '-') {
                return(BuildToken(unary_connective,"--"));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(punctuation,"-"));
            }
            break;
        case '|':
            return(BuildToken(binary_connective,"|"));
            break;
        case '&':
            return(BuildToken(binary_connective,"&"));
            break;
        case EOF:
            return(BuildToken(endeof,""));
            break;
        default:
            Index = 0;
            if (CurrentChar == '$' || islower(CurrentChar)) {
                do {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                } while (isalnum(CurrentChar) || (CurrentChar=='_'));
                LocalValue[Index] = '\0';
                Stream->Overshot = 1;
//----Ensure $ words have some length
                if (LocalValue[0] == '$' && !isalnum(LocalValue[1])) {
                    CharacterError(Stream);
                    return(NULL);
                }
//----Replace equal by $equal for now (can remove in future)
                if (!strcmp(LocalValue,"equal")) {
                    strcpy(LocalValue,"$equal");
                }
                return(BuildToken(lower_word,LocalValue));
            } else if (isupper(CurrentChar)) {
                do {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                } while (isalnum(CurrentChar) || (CurrentChar=='_'));
                LocalValue[Index] = '\0';
                Stream->Overshot = 1;
                return(BuildToken(upper_word,LocalValue));
            } else if (isdigit(CurrentChar)) {
                do {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                } while (isdigit(CurrentChar) || CurrentChar == '.');
                LocalValue[Index] = '\0';
                Stream->Overshot = 1;
                return(BuildToken(number,LocalValue));
            } else {
                CharacterError(Stream);
                return(NULL);
            }
            break;
    }
}
//-----------------------------------------------------------------------------
TOKEN Token(READFILE Stream, int Operation) {

//----Can't return the current token with a NULL file
    assert(!(Stream == NULL && Operation != 0));

    switch (Operation) {
        case 2:
            FreeToken(&(Stream->Auxilliary));
            FreeToken(&(Stream->CurrentToken));
            return((TOKEN)NULL);
            break;
        case 1:
//----Read into static, return it
//DEBUG if (Stream->CurrentToken != NULL ) printf("Had %s\n",CurrentToken->NameToken);
            FreeToken(&(Stream->Auxilliary));
            FreeToken(&(Stream->CurrentToken));
            Stream->CurrentToken = GetNextToken(Stream);
//DEBUG printf("Have %s\n",Stream->CurrentToken->NameToken);
            return(Stream->CurrentToken);
            break;
        case 0:
//----Return static
            FreeToken(&(Stream->Auxilliary));
            if (Stream->CurrentToken == NULL) {
                Stream->CurrentToken = GetNextToken(Stream);
                return(Stream->CurrentToken);
            } else {
//DEBUG printf("CT ==%s==\n",Stream->CurrentToken->NameToken);
                return(Stream->CurrentToken);
            }
            break;
        case -1:
//----Return static, read next into static
            FreeToken(&(Stream->Auxilliary));
            if (Stream->CurrentToken == NULL) {
                Stream->CurrentToken = GetNextToken(Stream);
            }
            Stream->Auxilliary = Stream->CurrentToken;
            Stream->CurrentToken = GetNextToken(Stream);
//DEBUG printf("%s\n",Stream->Auxilliary->NameToken);
            return(Stream->Auxilliary);
            break;
       default:
            return((TOKEN)NULL);
            break;
    }
}
//---------------------------------------------------------------------------
void TokenError(READFILE Stream) {

    printf("ERROR: Line %d Char %d Token \"%s\"\n",
Stream->Line,Stream->Character,CurrentToken(Stream)->NameToken);
    exit(-1);
}
//-----------------------------------------------------------------------------
int CheckTokenType(READFILE Stream,TokenType Type) {

    TOKEN ThisToken;

    ThisToken = CurrentToken(Stream);
    if (ThisToken == NULL) {
        CodingError("No token");
    }

    return((ThisToken->KindToken == Type) ||
(Type == atomic && (ThisToken->KindToken == lower_word || 
ThisToken->KindToken == number)));
}
//------------------------------------------------------------------------------
int CheckToken(READFILE Stream,TokenType Type,char * Value) {

//DEBUG printf("Current type = %d Require %d\n",CurrentToken(Stream)->KindToken,Type);
//DEBUG printf("Current value = %s Require %s\n",CurrentToken(Stream)->NameToken,Value);
    return(CheckTokenType(Stream,Type) && 
!strcmp(CurrentToken(Stream)->NameToken,Value));
}
//------------------------------------------------------------------------------
int TakeTokenType(READFILE Stream,TokenType Type) {

    if (CheckTokenType(Stream,Type)) {
        TakeCurrentToken(Stream);
        return(1);
    } else {
        TokenError(Stream);
        return(0);
    }
}
//------------------------------------------------------------------------------
int TakeToken(READFILE Stream,TokenType Type,char * Value) {

    if (CheckTokenType(Stream,Type) && 
!strcmp(CurrentToken(Stream)->NameToken,Value)) {
        TakeCurrentToken(Stream); 
        return(1);
    } else {
        TokenError(Stream);
        return(0);
    }
}
//------------------------------------------------------------------------------
void EnsureTokenType(READFILE Stream,TokenType Type) {

    if (!CheckTokenType(Stream,Type)) {
        TokenError(Stream);
    }
}
//------------------------------------------------------------------------------
void EnsureToken(READFILE Stream,TokenType Type,char * Value) {

    if (!CheckToken(Stream,Type,Value)) {
        TokenError(Stream);
    }
}
//------------------------------------------------------------------------------
int AcceptTokenType(READFILE Stream,TokenType Type) {

    if (CheckTokenType(Stream,Type)) {
        NextToken(Stream); 
        return(1);
    } else {
        TokenError(Stream);
        return(0);
    }
} 
//------------------------------------------------------------------------------
int AcceptToken(READFILE Stream,TokenType Type,char * Value) {

    if (CheckTokenType(Stream,Type) && 
!strcmp(CurrentToken(Stream)->NameToken,Value)) {
        NextToken(Stream); 
        return(1);
    } else {
        TokenError(Stream);
        return(0);
    }
} 
//------------------------------------------------------------------------------
int NextThenAcceptTokenType(READFILE Stream,TokenType Type) {
 
    NextToken(Stream); 
    return(AcceptTokenType(Stream,Type));
    
} 
//------------------------------------------------------------------------------
int NextThenAcceptToken(READFILE Stream,TokenType Type,char * Value) {
 
    NextToken(Stream); 
    return(AcceptToken(Stream,Type,Value));
} 
//------------------------------------------------------------------------------
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
    Stream->NeedNonLogicTokens = NeedNonLogicTokens;
    Stream->IgnoreBlankLines = 0;

    return(Stream);
}
//------------------------------------------------------------------------------
READFILE OpenFILEFile(FILE * OpenStream) {

    READFILE Stream;

    Stream = NewReadFile();

    if ((Stream->FileHandle = OpenStream) == NULL) {
        Free((void **)&Stream);
        return(NULL);
    }

    return(Stream);
}
//-----------------------------------------------------------------------------
char * ExpandFileName(char * FileName,char * BaseDirectory,
String ExpandedFileName) {

    char * Home;
    struct passwd *PasswdEntry;
    char * UserName;
    char * Slash;

//----If first character of filename is ~, expand to $HOME
    if (FileName[0] == '~' && FileName[1] == '/') {
        if ((Home = getenv("HOME")) != NULL) {
            strcpy(ExpandedFileName,Home);
            strcat(ExpandedFileName,&(FileName[1]));
            if (access(ExpandedFileName,R_OK) == 0) {
                return(ExpandedFileName);
            }
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
                if (access(ExpandedFileName,R_OK) == 0) {
                    return(ExpandedFileName);
                } 
            }
        }
        return(NULL);
    } 

//----Absolute
    if ((FileName[0] == '.' || FileName[0] =='/')) {
        strcpy(ExpandedFileName,FileName);
        if (access(ExpandedFileName,R_OK) == 0) {
            return(ExpandedFileName);
        } 
        return(NULL);
    }

//----Otherwise we have to search
//----Try the base directory of the including file
    strcpy(ExpandedFileName,BaseDirectory);
    strcat(ExpandedFileName,"/");
    strcat(ExpandedFileName,FileName);
    if (access(ExpandedFileName,R_OK) == 0) {
        return(ExpandedFileName);
    } 

//----Try the TPTP directory
    if ((Home = getenv("TPTP")) != NULL) {
        strcpy(ExpandedFileName,Home);
        strcat(ExpandedFileName,"/");
        strcat(ExpandedFileName,FileName);
        if (access(ExpandedFileName,R_OK) == 0) {
            return(ExpandedFileName);
        }
    }

//----Try local
    strcpy(ExpandedFileName,FileName);
    if (access(ExpandedFileName,R_OK) == 0) {
        return(ExpandedFileName);
    }

//----Try tptp user directory
    if ((PasswdEntry = getpwnam("tptp")) != NULL) {
        strcpy(ExpandedFileName,PasswdEntry->pw_dir);
        strcat(ExpandedFileName,"/TPTP/");
        strcat(ExpandedFileName,FileName);
        if (access(ExpandedFileName,R_OK) == 0) {
            return(ExpandedFileName);
        } 
    }

    return(NULL);
}
//-----------------------------------------------------------------------------
READFILE OpenFile(char * OriginalFileName) {

    String FinalFileName;
    String FileName;
    READFILE Stream;
    static char BaseDirectory[MAXPATHLEN] = "";
    char *LastSlash;

//----Clean up file name
    strcpy(FileName,OriginalFileName);
    if ((FileName[0] == '\'' || FileName[0] == '\"') && 
FileName [0] == FileName[strlen(FileName)-1]) {
        strcpy(FileName,&FileName[1]);
        FileName[strlen(FileName)-1] = '\0';
    }

//----If the filename is "--" use stdin
    if (!strcmp(FileName,"--")) {
        return(OpenFILEFile(stdin));
    }

    if (ExpandFileName(FileName,BaseDirectory,FinalFileName) == NULL) {
        return(NULL);
    }

    Stream = NewReadFile();

    if ((Stream->FileHandle = fopen(FinalFileName,"r")) == NULL) {
        Free((void **)&Stream);
        return(NULL);
    }

//----Record the file name
    Stream->FileName = CopyHeapString(FinalFileName);

//----Copy the base directory across if none there
    if (strlen(BaseDirectory) == 0) {
//----If current file is relative, find out current
        if (FinalFileName[0] != '/') {
            getcwd(BaseDirectory,MAXPATHLEN);
            strcat(BaseDirectory,"/");
            strcat(BaseDirectory,FinalFileName);
        } else {
            strcpy(BaseDirectory,FinalFileName);
        }
//----Lop off file name
        if ((LastSlash = strrchr(BaseDirectory,'/')) != NULL) {
            *LastSlash = '\0';
        } else {
            CodingError("Setting the base directory, no slash");
        }
    }

    return(Stream);
}
//-----------------------------------------------------------------------------
READFILE OpenStringFile(char * Content) {

    READFILE Stream;

    if (Content == NULL) {
        return(NULL);
    }

    Stream = NewReadFile();
    Stream->StringFileContent = CopyHeapString(Content);
    Stream->StringOffset = 0;

    return(Stream);
}
//-----------------------------------------------------------------------------
int EndFile(TOKEN CurrentToken) {

    return(CurrentToken->KindToken == endeof);
}
//-----------------------------------------------------------------------------
void CloseFile(READFILE Stream) {

    assert((Stream->FileHandle != NULL || Stream->StringFileContent != NULL) &&
(Stream->FileHandle == NULL || Stream->StringFileContent == NULL));

    if (Stream->FileHandle != NULL) {
//----If a file name, then close the file
        if (Stream->FileName != NULL) {
            fclose(Stream->FileHandle);
            Free((void **)&(Stream->FileName));
        }
//----Else a string file
    } else if (Stream->StringFileContent != NULL) {
        Free((void **)&(Stream->StringFileContent));
    } 
    Free((void **)&Stream);
}
//-----------------------------------------------------------------------------

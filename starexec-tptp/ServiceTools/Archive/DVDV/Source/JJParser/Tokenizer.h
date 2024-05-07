#ifndef TOKENIZER_H
#define TOKENIZER_H

//-----------------------------------------------------------------------------
#include "DataTypes.h"
//-----------------------------------------------------------------------------
#define NextCharacter(Stream) Character(Stream,1)
#define CurrentCharacter(Stream) Character(Stream,0)
#define CurrentCharacterMove(Stream) Character(Stream,-1)
#define NextToken(Stream) Token(Stream,1)
#define CurrentToken(Stream) Token(Stream,0)
#define CurrentTokenMove(Stream) Token(Stream,-1)
#define TakeCurrentToken(Stream) Token(Stream,2)

typedef enum {
    punctuation,
    number,
    lower_word,
    atomic,
    upper_word,
    quantifier,
    unary_connective,
    binary_connective,
//----Non-logic tokens
    comment_token,
    blank_line_token,
    error,
    endeof
} TokenType;

typedef struct {
    TokenType KindToken;
    char * NameToken;
} ReadToken;

typedef ReadToken * TOKEN;

typedef struct {
    char * FileName;
    FILE * FileHandle;
    int Line;
    int Character;
//----Content for a string file
    char * StringFileContent;
//----Overshot by one character or not
    int Overshot;
//----Index of next character to use
    int StringOffset;
//----Current character and token
    int CurrentCharacter;
    TOKEN CurrentToken;
    TOKEN Auxilliary;
//----Whether or not non-logicals are needed
    int NeedNonLogicTokens;
    int IgnoreBlankLines;
} ReadFile;

typedef ReadFile * READFILE;
//-----------------------------------------------------------------------------
int Character(READFILE CurrentFile,int Operation);
void SetNeedForNonLogicTokens(int OnOff);
int GetNeedForNonLogicTokens(READFILE Stream);
ConnectiveType StringToConnective(char * String);
char * ConnectiveToString(ConnectiveType Connective);
StatusType StringToStatus(char * String);
char * StatusToString(StatusType Status);
TOKEN GetNextToken(READFILE CurrentFile);
void FreeToken(TOKEN * Pointer);
TOKEN Token(READFILE CurrentFile, int Operation);
TOKEN CloneToken(TOKEN TokenCopy);
READFILE OpenFile(char * namefile);
READFILE OpenFILEFile(FILE * OpenStream);
READFILE OpenStringFile(char * Content);
int EndFile(TOKEN CurrentToken);
void CloseFile(READFILE Stream);

int CheckTokenType(READFILE Stream,TokenType Type);
int CheckToken(READFILE Stream,TokenType Type,char * Value);
int TakeTokenType(READFILE Stream,TokenType Type);
int TakeToken(READFILE Stream,TokenType Type,char * Value);
void EnsureTokenType(READFILE Stream,TokenType Type);
void EnsureToken(READFILE Stream,TokenType Type,char * Value);
int AcceptTokenType(READFILE Stream,TokenType Type);
int AcceptToken(READFILE Stream,TokenType Type,char * Value);
int NextThenAcceptTokenType(READFILE Stream,TokenType Type);
int NextThenAcceptToken(READFILE Stream,TokenType Type,char * Value);
//------------------------------------------------------------------------------
#endif

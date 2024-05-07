#ifndef TOKENIZER_H
#define TOKENIZER_H
//-------------------------------------------------------------------------------------------------
#include "DataTypes.h"
//-------------------------------------------------------------------------------------------------
#define NextCharacter(Stream) Character(Stream,1)
#define CurrentCharacter(Stream) Character(Stream,0)
#define CurrentCharacterMove(Stream) Character(Stream,-1)
#define NextToken(Stream) Token(Stream,1)
#define CurrentToken(Stream) Token(Stream,0)
#define CurrentTokenMove(Stream) Token(Stream,-1)
#define TakeCurrentToken(Stream) Token(Stream,2)
//-------------------------------------------------------------------------------------------------
int GetNeedForNonLogicTokens(void);
void SetNeedForNonLogicTokens(int OnOff);
int GetStreamNeedForNonLogicTokens(READFILE Stream);
int GetWarnings(void);
int SetWarnings(int GiveWarnings);
int GetStreamWarnings(READFILE Stream);
int SetStreamWarnings(READFILE Stream,int GiveWarnings);
int EndFile(TOKEN CurrentToken);

int Character(READFILE CurrentFile,int Operation);
StatusType StringToStatus(char * String);
char * StatusToString(StatusType Status);
ConnectiveType StringToConnective(char * String);
char * ConnectiveToString(ConnectiveType Connective);
SyntaxType StringToSyntax(char * String);
char * TokenTypeToString(TokenType Type);
char * SyntaxToString(SyntaxType Syntax);
char * TermTypeToString(TermType Type);
SyntaxType NestedTermTypeToSyntax(TermType Type);
char * FormulaTypeToString(FormulaTypeType Type);
TOKEN GetNextToken(READFILE CurrentFile);
void FreeToken(TOKEN * Pointer);
TOKEN Token(READFILE CurrentFile, int Operation);
TOKEN CloneToken(TOKEN TokenCopy);
void FreeToken(TOKEN * Pointer);

void SetTokenType(READFILE Stream,TokenType Type);
int CheckTokenType(READFILE Stream,TokenType Type);
void TokenWarning(READFILE Stream,char * Message);
void TokenError(READFILE Stream,char * Message);
int CheckToken(READFILE Stream,TokenType Type,char * Value);
int TakeTokenType(READFILE Stream,TokenType Type);
int TakeToken(READFILE Stream,TokenType Type,char * Value);
void EnsureTokenType(READFILE Stream,TokenType Type);
void EnsureTokenNotType(READFILE Stream,TokenType NotType);
void EnsureToken(READFILE Stream,TokenType Type,char * Value);
int AcceptTokenType(READFILE Stream,TokenType Type);
int AcceptToken(READFILE Stream,TokenType Type,char * Value);
int NextThenAcceptTokenType(READFILE Stream,TokenType Type);
int NextThenAcceptToken(READFILE Stream,TokenType Type,char * Value);
//--------------------------------------------------------------------------------------------------
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Signature.h"
#include "Utilities.h"
#include "DataTypes.h"
//-----------------------------------------------------------------------------
SIGNATURE NewSignature(void) {

    SIGNATURE Signature;

    Signature = (SIGNATURE)Malloc(sizeof(SignatureType));
    Signature->Variables = NULL;
    Signature->Functions = NULL;
    Signature->Predicates = NULL;
    Signature->NonLogicals = NULL;

    return(Signature);
}
//-----------------------------------------------------------------------------
void FreeSignatureList(SYMBOLNODE * Symbols) {

    SYMBOLNODE ToFree;

    while ((*Symbols) != NULL) {
        assert((*Symbols)->NumberOfUses == 0);
        ToFree = *Symbols;
        *Symbols = (*Symbols)->NextSymbol;
        Free((void **)&(ToFree->NameSymbol));
        Free((void **)&ToFree);
    }
}
//-----------------------------------------------------------------------------
void FreeSignature(SIGNATURE * Signature) {

    FreeSignatureList(&((*Signature)->Variables));
    assert((*Signature)->Variables == NULL);
    FreeSignatureList(&((*Signature)->Functions));
    assert((*Signature)->Functions == NULL);
    FreeSignatureList(&((*Signature)->Predicates));
    assert((*Signature)->Predicates == NULL);
    FreeSignatureList(&((*Signature)->NonLogicals));
    assert((*Signature)->NonLogicals == NULL);

    Free((void **)Signature);
}
//-----------------------------------------------------------------------------
char * GetSignatureSymbol(SYMBOLNODE SymbolNode) {

    return(SymbolNode->NameSymbol);
}
//-----------------------------------------------------------------------------
int GetSignatureArity(SYMBOLNODE SymbolNode) {

    return(SymbolNode->Arity);
}
//-----------------------------------------------------------------------------
int GetSignatureUses(SYMBOLNODE SymbolNode) {

    return(SymbolNode->NumberOfUses);
}
//-----------------------------------------------------------------------------
void IncreaseSymbolUseCount(SYMBOLNODE Symbol,int HowMuch) {

    Symbol->NumberOfUses += HowMuch;
}
//-----------------------------------------------------------------------------
SYMBOLNODE IsSymbolInSignatureList(SYMBOLNODE List,char * Name,int Arity) {

    while (List != NULL && !(!strcmp(GetSignatureSymbol(List),Name) &&
GetSignatureArity(List) == Arity)) {
        List = List->NextSymbol;
    }

    return(List);
}
//-----------------------------------------------------------------------------
SYMBOLNODE InsertIntoSignatureList(SYMBOLNODE * List,char * Name,int Arity) {

    SYMBOLNODE Symbol;

    if ((Symbol = IsSymbolInSignatureList(*List,Name,Arity)) != NULL) {
        IncreaseSymbolUseCount(Symbol,1);
        return(Symbol);
    } else {
//----Add at front
        Symbol = (SYMBOLNODE)Malloc(sizeof(SymbolNodeType));
        Symbol->NameSymbol = CopyHeapString(Name);
        Symbol->NumberOfUses = 1;
        Symbol->Arity = Arity;
        Symbol->NextSymbol = *List;
        *List = Symbol;
        return(Symbol);
    }
}
//-----------------------------------------------------------------------------
SYMBOLNODE InsertIntoSignature(SIGNATURE Signature,TermType Type,
char * Name,int Arity) {

    switch (Type) {
        case variable:
            return(InsertIntoSignatureList(&(Signature->Variables),Name,Arity));
            break;
        case function:
            return(InsertIntoSignatureList(&(Signature->Functions),Name,Arity));
            break;
        case predicate:
            return(InsertIntoSignatureList(&(Signature->Predicates),Name,
Arity));
            break;
        case non_logical_data:
            return(InsertIntoSignatureList(&(Signature->NonLogicals),Name,
Arity));
            break;
        default:
            printf("ERROR: Unknown type for signature\n");
            exit(-1);
    }
}
//-----------------------------------------------------------------------------
void PrintSignatureList(SYMBOLNODE List) {

    while (List != NULL) {
        printf("%s/%d(%d) ",GetSignatureSymbol(List),GetSignatureArity(List),
GetSignatureUses(List));
        List = List->NextSymbol;
    }
}
//-----------------------------------------------------------------------------
void PrintSignature(SIGNATURE Signature) {

    printf("Variables:  ");
    PrintSignatureList(Signature->Variables);
    printf("\n");
    printf("Functions:  ");
    PrintSignatureList(Signature->Functions);
    printf("\n");
    printf("Predicates: ");
    PrintSignatureList(Signature->Predicates);
    printf("\n");
    printf("NonLogical: ");
    PrintSignatureList(Signature->NonLogicals);
    printf("\n");
}
//-----------------------------------------------------------------------------

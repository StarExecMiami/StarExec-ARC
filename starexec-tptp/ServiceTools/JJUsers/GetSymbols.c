#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "Compare.h"
#include "Modify.h"
#include "List.h"
#include "Tree.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
typedef enum {byformula,all} CollectionType;
//-----------------------------------------------------------------------------
void PrologFormat(char * Name,char * Predicates,char * Functors) {

    char * Symbol;
    int Counter;

    printf("symbols(%s,[",Name);
    Counter = 0;
    Symbol = strtok(Functors,"\n");
    while (Symbol != NULL) {
        if (++Counter > 1) {
            printf(",");
        }
        printf("%s",Symbol);
        Symbol = strtok(NULL,"\n");
    }
    *Functors = '\0';
    printf("],[");
    Counter = 0;
    Symbol = strtok(Predicates,"\n");
    while (Symbol != NULL) {
        if (++Counter > 1) {
            printf(",");
        }
        printf("%s",Symbol);
        Symbol = strtok(NULL,"\n");
    }
    printf("]).\n");
}
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    SIGNATURE Signature;
    LISTNODE Head;
    int ArgOffset;
    int NoError;
    CollectionType Collection;
    LISTNODE Target;
    char * Symbols;
    char * Predicates;
    char * Functors;
    char * Variables;
    char * Types;
    SuperString Name;

//----Were we given any arguments at all?  If not, die.
    if (argc == 1) {
        printf("Usage: GetSymbols TPTP-SOURCE\n");
        exit(EXIT_FAILURE);
    }
//----Check output form flag
    ArgOffset = 1;
    Collection = byformula;;
    NoError = 0;
    while (argv[ArgOffset][0] == '-' && strcmp(argv[ArgOffset],"--")) {
        if  (!strcmp(argv[ArgOffset],"-all")) {
            Collection = all;
            ArgOffset++;
        } else if (!strcmp(argv[ArgOffset],"-formula")) {
            Collection = byformula;
            ArgOffset++;
        } else if (!strcmp(argv[ArgOffset],"-noerror")) {
            NoError = 1;
            ArgOffset++;
        } else {
            printf("Unknown option %s\n",argv[ArgOffset]);
            ArgOffset++;
        }
    }

//----Read from file or stdin
    Signature = NewSignature();
    SetNeedForNonLogicTokens(0);
    if (argc - ArgOffset > 0) {
        Head = ParseFileOfFormulae(argv[ArgOffset],NULL,Signature,1,NULL);
    } else {
        Head = ParseFILEOfFormulae("--",stdin,Signature,1,NULL);
    }
//----Empty file is not always an error, but we need some warning
    if (Head == NULL && !NoError) {
        printf("ERROR: No symbols found\n");
        FreeSignature(&Signature);
        exit(EXIT_FAILURE);
    }

    switch (Collection) {
        case byformula:
            Target = Head;
            while (Target != NULL) {
                Symbols = (char *)Malloc(sizeof(String));
                Predicates = GetAnnotatedFormulaSymbolUsage(Target->
AnnotatedFormula,&Symbols,&Functors,&Variables,&Types);
                PrologFormat(GetName(Target->AnnotatedFormula,Name),Predicates,
Functors);
                Free((void **)&Symbols);
                Target = Target->Next;
            }
            break;
        case all:
            Symbols = (char *)Malloc(sizeof(String));
            Predicates = GetListOfAnnotatedFormulaSymbolUsage(Head,
&Symbols,&Functors,&Variables,&Types);
            PrologFormat("all",Predicates,Functors);
            Free((void **)&Symbols);
            break;
    }

    FreeListOfAnnotatedFormulae(&Head,Signature);
    FreeSignature(&Signature);
    return(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------

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
//-------------------------------------------------------------------------------------------------
typedef enum {all,realvariables,nonvariables,predicates,functions,types} SymbolTypes;

typedef struct TypingTag {
    BinaryFormulaType * Typing;
    struct TypingTag * Next;
} TypingNodeType;

typedef TypingNodeType * TYPINGNODE;
//-------------------------------------------------------------------------------------------------
//----TypeCollector must be address of a malloced String
int GetDeclaredTypes(LISTNODE Head,char ** TypeCollector,TYPINGNODE * TypingListHead) {

    FORMULA Formula;
    BinaryFormulaType * TypingFormula;
    int TypeCollectorLength = STRINGLENGTH;
    TYPINGNODE TypingNode;
    TYPINGNODE * AddTypingNodeHere;
    char * TypedCollector;
    int TypedCollectorLength = STRINGLENGTH;
    char * SubtypedCollector;
    int SubtypedCollectorLength = STRINGLENGTH;
    int NumberOfErrors;

    NumberOfErrors = 0;
    strcpy(*TypeCollector,"$int\n$rat\n$real\n$i\n$o\n$tType\n");

    TypedCollector = (char *)Malloc(sizeof(String));
    strcpy(TypedCollector,"");
    SubtypedCollector = (char *)Malloc(sizeof(String));
    strcpy(SubtypedCollector,"");

    AddTypingNodeHere = TypingListHead;

    while (Head != NULL) {
//----Is it a type formula
        if (LogicalAnnotatedFormula(Head->AnnotatedFormula) && 
GetRole(Head->AnnotatedFormula,NULL) == type) {
            Formula = Head->AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
FormulaWithVariables->Formula;
//DEBUG printf("In a type formula it is %s\n",FormulaTypeToString(Formula->Type));
            if (Formula->Type == type_declaration) {
//----If it's a type declaration, then we're interested. (It could be a subtype
//----or what else?)
                if (Formula->FormulaUnion.BinaryFormula.Connective == typecolon) {
                    TypingFormula = &(Formula->FormulaUnion.BinaryFormula);
//----First check if a type has been declared (of type $tType)
                    if (TypingFormula->RHS->Type == atom &&
!strcmp(GetSymbol(TypingFormula->RHS->FormulaUnion.Atom),"$tType")) {
printf("Found a type %s\n",GetSymbol(TypingFormula->LHS->FormulaUnion.Atom));
                        ExtendString(TypeCollector,
GetSymbol(TypingFormula->LHS->FormulaUnion.Atom),&TypeCollectorLength);
                        ExtendString(TypeCollector,"\n",&TypeCollectorLength);
                    }

//----Either way, collect this binary formula into a list for later checking
                    TypingNode = (TYPINGNODE)Malloc(sizeof(TypingNodeType));
                    TypingNode->Typing = TypingFormula;
                    TypingNode->Next = NULL;
                    *AddTypingNodeHere = TypingNode;
                    AddTypingNodeHere = &(TypingNode->Next);
//----Check for duplicate typing (overloading)
                    if (NameInList(GetSymbol(
TypingFormula->LHS->FormulaUnion.Atom),TypedCollector)) {
                        printf("ERROR: Multiple types for %s\n",
GetSymbol(TypingFormula->LHS->FormulaUnion.Atom));
                        NumberOfErrors++;
                    } else {
                        ExtendString(&TypedCollector,GetSymbol(
TypingFormula->LHS->FormulaUnion.Atom),&TypedCollectorLength);
                        ExtendString(&TypedCollector,"\n",&TypedCollectorLength);
                    }
                } else if (Formula->FormulaUnion.BinaryFormula.Connective == subtype) {
                    TypingFormula = &(Formula->FormulaUnion.BinaryFormula);
//----Check both types have been declared
                    if (!NameInList(GetSymbol(TypingFormula->LHS->FormulaUnion.Atom),
TypedCollector)) {
                        printf("ERROR: No type for %s\n",
GetSymbol(TypingFormula->LHS->FormulaUnion.Atom));
                        NumberOfErrors++;
                    } 
                    if (!NameInList(GetSymbol(
TypingFormula->RHS->FormulaUnion.Atom),TypedCollector)) {
                        printf("ERROR: No type for %s\n",
GetSymbol(TypingFormula->RHS->FormulaUnion.Atom));
                        NumberOfErrors++;
                    } 
//----Check subtype has only one supertype
                    if (NameInList(GetSymbol(
TypingFormula->LHS->FormulaUnion.Atom),SubtypedCollector)) {
                        printf("ERROR: Multiple supertypes for %s\n",
GetSymbol(TypingFormula->LHS->FormulaUnion.Atom));
                        NumberOfErrors++;
                    } else {
                        ExtendString(&SubtypedCollector,GetSymbol(
TypingFormula->LHS->FormulaUnion.Atom),&SubtypedCollectorLength);
                        ExtendString(&SubtypedCollector,"\n",
&SubtypedCollectorLength);
                    }
                } else {
                    printf("ERROR: Unknown binary type connective\n");
                    PrintAnnotatedTSTPNode(stdout,Head->AnnotatedFormula,
tptp,1);
                }
            } else {
                printf("ERROR: Something not a type declaration in a type formula\n");
                PrintAnnotatedTSTPNode(stdout,Head->AnnotatedFormula,tptp,1);
            }
        }
        Head = Head->Next;
    }
    Free((void **)&SubtypedCollector);

//DEBUG TypingNode = *TypingListHead;
//DEBUG while (TypingNode != NULL) {
//DEBUG PrintTSTPFormula(stdout,tptp_fof,TypingNode->Typing->LHS,0,1,outermost,1);
//DEBUG printf("\n");
//DEBUG PrintTSTPFormula(stdout,tptp_fof,TypingNode->Typing->RHS,0,1,outermost,1);
//DEBUG printf("\n\n");
//DEBUG TypingNode = TypingNode->Next;
//DEBUG }
    return(NumberOfErrors);
}
//-------------------------------------------------------------------------------------------------
int CheckEachSymbolIsTyped(TYPINGNODE TypingsListHead,SYMBOLNODE Symbols,int * NumberOfSymbols) {

    char * StartOfSymbol;
    TYPINGNODE TypingNode;
    int NumberOfErrors;

    NumberOfErrors = 0;
    if (Symbols != NULL) {
        NumberOfErrors += CheckEachSymbolIsTyped(TypingsListHead,Symbols->LastSymbol,
NumberOfSymbols);
        (*NumberOfSymbols)++;
        StartOfSymbol = Symbols->NameSymbol;
//DEBUG printf("looking for ==%s==\n",StartOfSymbol);
//----Predefined symbols don't have to be typed
        if (StartOfSymbol[0] == '\'' || islower(StartOfSymbol[0])) {
//----Search for the symbol in the LHS of a typing node
            TypingNode = TypingsListHead;
            while (TypingNode != NULL && strcmp(StartOfSymbol,
GetSymbol(TypingNode->Typing->LHS->FormulaUnion.Atom))) {
                TypingNode = TypingNode->Next;
            }
            if (TypingNode == NULL) {
                printf("ERROR: No type for %s\n",StartOfSymbol);
                NumberOfErrors++;
            } else {
printf("Found the type of %s\n",StartOfSymbol);
            }
        }
        NumberOfErrors += CheckEachSymbolIsTyped(TypingsListHead,Symbols->NextSymbol,
NumberOfSymbols);
    }
    return(NumberOfErrors);
}
//-------------------------------------------------------------------------------------------------
int CheckEachVariableIsTypedInFormula(char * Types,FORMULA Formula,int * NumberOfSymbols) {

    int NumberOfErrors;
    int Dummy;
    QuantifiedFormulaType * QuantifiedFormula;
    String ErrorMessage;
    TERM TheAtom;
    int ArgumentIndex;

    NumberOfErrors = 0;
    switch(Formula->Type) {
        case quantified:
            (*NumberOfSymbols)++;
            QuantifiedFormula = &(Formula->FormulaUnion.QuantifiedFormula);
//DEBUG printf("After variable %s there are %d\n",GetSymbol(QuantifiedFormula->Variable),*NumberOfSymbols);
//ALSO CHECK IF THE TYPE EXISTS IF ATOMIC BROKEN
            if (QuantifiedFormula->VariableType == NULL) {
                printf("ERROR: No type for %s in\n    ",
GetSymbol(QuantifiedFormula->Variable));
                PrintTSTPFormula(stdout,tptp_fof,Formula,4,1,outermost,1);
                printf("\n");
                NumberOfErrors++;
            } 
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,QuantifiedFormula->Formula,
NumberOfSymbols);
            break;
        case type_declaration:
        case binary:
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Formula->FormulaUnion.BinaryFormula.LHS,NumberOfSymbols);
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Formula->FormulaUnion.BinaryFormula.RHS,NumberOfSymbols);
            break;
        case unary:
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Formula->FormulaUnion.UnaryFormula.Formula,NumberOfSymbols);
            break;
        case atom:
//DEBUG printf("Atom %s\n",GetSymbol(Formula->FormulaUnion.Atom));
//----Dig for nested formulae
            TheAtom = Formula->FormulaUnion.Atom;
            if (TheAtom->Type == formula) {
//DEBUG printf("dig into the formula atom\n");
                NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
TheAtom->TheSymbol.Formula,NumberOfSymbols);
            } else if ((TheAtom->Type == atom_as_term || TheAtom->Type == function) &&
TheAtom->Arguments != NULL) {
//DEBUG printf("dig into the arguments\n");
                for (ArgumentIndex = 0;ArgumentIndex < GetArity(TheAtom);ArgumentIndex++) {
                    if (TheAtom->Arguments[ArgumentIndex]->Type == formula) {
                        NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
TheAtom->Arguments[ArgumentIndex]->TheSymbol.Formula,NumberOfSymbols);
                    }
                }
            } else {
//DEBUG printf("No need to dig further\n");
            }
            break;
        case ite_formula:
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Formula->FormulaUnion.ConditionalFormula.Condition,NumberOfSymbols);
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue,NumberOfSymbols);
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse,NumberOfSymbols);
            break;
        case let_formula:
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Formula->FormulaUnion.LetFormula.LetDefn,&Dummy);
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Formula->FormulaUnion.LetFormula.LetBody,NumberOfSymbols);
            break;
        default:
            sprintf(ErrorMessage,
"ERROR: Unknown formula type %s in CheckEachVariableIsTypedInFormula\n",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            break;
    }
    return(NumberOfErrors);
}
//-------------------------------------------------------------------------------------------------
int CheckEachVariableIsTyped(char * Types,LISTNODE Head,int * NumberOfVariables) {

    int NumberOfErrors;

    NumberOfErrors = 0;
    while (Head != NULL) {
        if (LogicalAnnotatedFormula(Head->AnnotatedFormula)) {
            NumberOfErrors += CheckEachVariableIsTypedInFormula(Types,
Head->AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
NumberOfVariables);
        }
        Head = Head->Next;
    }
    return(NumberOfErrors);
}
//-------------------------------------------------------------------------------------------------
void DoCheckTyping(LISTNODE Head,char * FileName,SymbolTypes WhatToCheck,SIGNATURE Signature) {

    char * Types;
    TYPINGNODE TypingsListHead;
    TYPINGNODE TypingNode;
    int NumberOfErrors;
    int NumberOfSymbols;

//----Get all the types (and ensure $o, $i, and $tType are there)
    Types = (char *)Malloc(sizeof(String));
    TypingsListHead = NULL;
    NumberOfErrors = GetDeclaredTypes(Head,&Types,&TypingsListHead);

    NumberOfErrors = 0;
    NumberOfSymbols = 0;
    switch (WhatToCheck) {
        case all:
            NumberOfErrors += CheckEachSymbolIsTyped(TypingsListHead,Signature->Predicates,
&NumberOfSymbols);
//DEBUG printf("%d predicates\n",NumberOfSymbols);
            NumberOfErrors += CheckEachSymbolIsTyped(TypingsListHead,Signature->Functions,
&NumberOfSymbols);
//DEBUG printf("%d predicates and functions\n",NumberOfSymbols);
            NumberOfErrors +=  CheckEachVariableIsTyped(Types,Head,&NumberOfSymbols);
//DEBUG printf("%d predicates and functions and variables\n",NumberOfSymbols);
            break;
        case realvariables:
            NumberOfErrors += CheckEachVariableIsTyped(Types,Head,&NumberOfSymbols);
            break;
        case nonvariables:
            NumberOfErrors += CheckEachSymbolIsTyped(TypingsListHead,Signature->Predicates,
&NumberOfSymbols);
            NumberOfErrors += CheckEachSymbolIsTyped(TypingsListHead,Signature->Functions,
&NumberOfSymbols);
            break;
        case predicates:
            NumberOfErrors += CheckEachSymbolIsTyped(TypingsListHead,Signature->Predicates,
&NumberOfSymbols);
            break;
        case functions:
            NumberOfErrors += CheckEachSymbolIsTyped(TypingsListHead,Signature->Functions,
&NumberOfSymbols);
            break;
        case types:
            printf("%s",Types);
            break;
        default:
            printf("ERROR: How the fuck did I get here?\n");
            break;
    }
    printf("%s: %d symbols checked, %d errors\n",FileName,NumberOfSymbols,NumberOfErrors);

    while (TypingsListHead != NULL) {
        TypingNode = TypingsListHead;
        TypingsListHead = TypingsListHead->Next;
        Free((void **)&TypingNode);
    }
    Free((void **)&Types);
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    SIGNATURE Signature;
    LISTNODE Head;
    int ArgOffset;
    SymbolTypes WhatToCheck;

//----Check output form flag
    ArgOffset = 1;
    WhatToCheck = all;
    while (argv[ArgOffset][0] == '-' && strcmp(argv[ArgOffset],"--")) {
        if  (!strcmp(argv[ArgOffset],"-all")) {
            WhatToCheck = all;
            ArgOffset++;
        } else if (!strcmp(argv[ArgOffset],"-variables")) {
            WhatToCheck = realvariables;
            ArgOffset++;
        } else if (!strcmp(argv[ArgOffset],"-nonvariables")) {
            WhatToCheck = nonvariables;
            ArgOffset++;
        } else if (!strcmp(argv[ArgOffset],"-predicates")) {
            WhatToCheck = predicates;
            ArgOffset++;
        } else if (!strcmp(argv[ArgOffset],"-functions")) {
            WhatToCheck = functions;
            ArgOffset++;
        } else if (!strcmp(argv[ArgOffset],"-types")) {
            WhatToCheck = types;
            ArgOffset++;
        } else {
            printf("Unknown option %s\n",argv[ArgOffset]);
            ArgOffset++;
        }
    }

//----Read from file or stdin
    SetNeedForNonLogicTokens(0);
    if (argc - ArgOffset > 0) {
        while (argc - ArgOffset > 0) {
            Signature = NewSignatureWithTypes();
            Head = ParseFileOfFormulae(argv[ArgOffset],NULL,Signature,1,NULL);
            RemovedUnusedSymbols(Signature);
            DoCheckTyping(Head,argv[ArgOffset],WhatToCheck,Signature);
            FreeListOfAnnotatedFormulae(&Head,Signature);
            FreeSignature(&Signature);
            ArgOffset++;
        }
    } else {
        Signature = NewSignatureWithTypes();
        Head = ParseFILEOfFormulae("--",stdin,Signature,1,NULL);
        RemovedUnusedSymbols(Signature);
        DoCheckTyping(Head,"stdin",WhatToCheck,Signature);
        FreeListOfAnnotatedFormulae(&Head,Signature);
        FreeSignature(&Signature);
    }

    return(EXIT_SUCCESS);
}
//-------------------------------------------------------------------------------------------------

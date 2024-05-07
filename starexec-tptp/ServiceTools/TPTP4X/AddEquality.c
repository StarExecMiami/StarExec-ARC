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
#include "Modify.h"
#include "List.h"
#include "ListStatistics.h"
#include "PrintTSTP.h"
#include "ParseTSTP.h"
#include "tptp4X.h"
//-------------------------------------------------------------------------------------------------
LISTNODE MakeBlankLine(void) {

    static ANNOTATEDFORMULA BlankLine = NULL;

//----Make it once only and reuse
    if (BlankLine == NULL) {
        BlankLine = NewAnnotatedFormula(blank_line);
    }

    return(NewListNode(BlankLine));
    
}
//-------------------------------------------------------------------------------------------------
LISTNODE MakeReflexivity(SyntaxType Syntax,SIGNATURE Signature) {

    String Axiom;

    if (Syntax == tptp_fof) {
        sprintf(Axiom,"fof(reflexivity,axiom,\n    (! [X] : (X = X) )).");
    }
    if (Syntax == tptp_cnf) {
        sprintf(Axiom,"cnf(reflexivity,axiom,\n    ( X = X )).");
    }
//DEBUG printf("The string reflexivity is ==%s==\n",Axiom);
    return(ParseStringOfFormulae(Axiom,Signature,0,NULL));
}
//-------------------------------------------------------------------------------------------------
LISTNODE MakeSymmetry(SyntaxType Syntax,SIGNATURE Signature) {

    String Axiom;

    if (Syntax == tptp_fof) {
        sprintf(Axiom,"fof(symmetry,axiom,\n    (! [X,Y] : ((X = Y) => (Y = X)))).");
    }
    if (Syntax == tptp_cnf) {
        sprintf(Axiom,"cnf(symmetry,axiom,\n    ((X != Y) | (Y = X))).");
    }
//DEBUG printf("The string symmetry is ==%s==\n",Axiom);
    return(ParseStringOfFormulae(Axiom,Signature,0,NULL));
}
//-------------------------------------------------------------------------------------------------
LISTNODE MakeTransitivity(SyntaxType Syntax,SIGNATURE Signature) {

    String Axiom;

    if (Syntax == tptp_fof) {
        sprintf(Axiom,"fof(transitivity,axiom,\n    (! [X,Y,Z] : ( ((X = Y) & (Y = Z) ) => (X = Z)))).");
    }
    if (Syntax == tptp_cnf) {
        sprintf(Axiom,"cnf(transitivity,axiom,\n    ((X != Y) | (Y != Z) | (X = Z))).");
    }
//DEBUG printf("The string transitivity is ==%s==\n",Axiom);
    return(ParseStringOfFormulae(Axiom,Signature,0,NULL));
}
//-------------------------------------------------------------------------------------------------
void MakeTermSubstitutionPair(char * Symbol,int Arity,int Position,
String TermX,String TermY,String Variables) {

    String IndexString;
    int Index;

    sprintf(TermX,"%s(",Symbol);
    sprintf(TermY,"%s(",Symbol);
    strcpy(Variables,"");
    for (Index=1;Index <= Arity;Index++) {
        if (Index > 1) {
            strcat(TermX,",");
            strcat(TermY,",");
            strcat(Variables,",");
        }
        if (Index == Position) {
            strcat(TermX,"X");
            strcat(TermY,"Y");
            strcat(Variables,"X,Y");
        } else {
            strcat(TermX,"Z");
            strcat(TermY,"Z");
            strcat(Variables,"Z");
            sprintf(IndexString,"%d",Index);
            strcat(TermX,IndexString);
            strcat(TermY,IndexString);
            strcat(Variables,IndexString);
        }
    }
    strcat(TermX,")");
    strcat(TermY,")");

//DEBUG printf("pair %d of %d for %s are ==%s==%s==\n",Position,Arity,Symbol,TermX,TermY);
}
//-------------------------------------------------------------------------------------------------
LISTNODE MakeFunctionSubstitution(char * Symbol,int Arity,int Position,SyntaxType Syntax,
SIGNATURE Signature) {

    SuperString Axiom;
    SuperString TermX,TermY,Variables;
    SuperString AxiomName;
    SuperString TransformedSymbol;

    strcpy(TransformedSymbol,"");
 
    MakeTermSubstitutionPair(Symbol,Arity,Position,TermX,TermY,Variables);

    if (Symbol[0] != '\'') {
        sprintf(AxiomName,"%s_substitution_%d",Symbol,Position);
    }
    else {
        strncat(TransformedSymbol,Symbol,strlen(Symbol) - 1); // Copy without trailing single quote
        sprintf(AxiomName,"%s_substitution_%d'",TransformedSymbol,Position);
    }

    if (Syntax == tptp_fof) {
        sprintf(Axiom,"fof(%s,axiom,\n    (! [%s] : ( (X = Y) => (",AxiomName,Variables);
        strcat(Axiom,TermX);
        strcat(Axiom," = ");
        strcat(Axiom,TermY);
        strcat(Axiom,")))).");
    }
    if (Syntax == tptp_cnf) {
        sprintf(Axiom,"cnf(%s,axiom,\n    ((X != Y) | (%s = %s))).",AxiomName,TermX,TermY);
    }
//DEBUG printf("The string axiom is ==%s==\n",Axiom);

    return(ParseStringOfFormulae(Axiom,Signature,0,NULL));
}
//-------------------------------------------------------------------------------------------------
LISTNODE MakePredicateSubstitution(char * Symbol,int Arity,int Position,
SyntaxType Syntax,SIGNATURE Signature) {

    String Axiom;
    String TermX,TermY,Variables;
    String AxiomName;
    String TransformedSymbol;

    strcpy(TransformedSymbol,"");

    MakeTermSubstitutionPair(Symbol,Arity,Position,TermX,TermY,Variables);

    if (Symbol[0] != '\'') {
        sprintf(AxiomName,"%s_substitution_%d",Symbol,Position);
    }
    else {
        strncat(TransformedSymbol,Symbol,strlen(Symbol) - 1); // Copy without trailing single quote
        sprintf(AxiomName,"%s_substitution_%d'",TransformedSymbol,Position);
    }

    if (Syntax == tptp_fof) {
        sprintf(Axiom,"fof(%s,axiom,\n    (![%s] : ( ((X = Y) & %s ) => %s))).",AxiomName,Variables,TermX,TermY);
    }
    if (Syntax == tptp_cnf) {
        sprintf(Axiom,"cnf(%s,axiom,\n    ((X != Y) | ~%s | %s)).",AxiomName,TermX,TermY);
    }
//DEBUG printf("The string axiom is ==%s==\n",Axiom);

    return(ParseStringOfFormulae(Axiom,Signature,0,NULL));

}
//-------------------------------------------------------------------------------------------------
void AppendNode(OptionsType Options,LISTNODE ** LastPointer,LISTNODE Node) {

    **LastPointer = Node;
    *LastPointer = &((**LastPointer)->Next);
//----Add blank line if keeping those
    if (Options.Pretty) {
        **LastPointer = MakeBlankLine();
        *LastPointer = &((**LastPointer)->Next);
    }
}
//-------------------------------------------------------------------------------------------------
LISTNODE MakeEqualityFormulae(OptionsType Options,char * SymbolUsage,char * Functors,
SyntaxType Syntax,SIGNATURE Signature,char * WhatEquality) {

    LISTNODE EqualityFormulae;
    LISTNODE * AddHere;
    char * Symbol;
    char * NextSymbol;
    char * Slash;
    int Arity;
    int Index;

    EqualityFormulae = NULL;
    AddHere = &EqualityFormulae;
//----Add a leading blank line if being pretty
    if (Options.Pretty && !Options.KeepNonLogicals) {
        *AddHere = MakeBlankLine();
        AddHere = &((*AddHere)->Next);
    }
    if (strchr(WhatEquality,'r') != NULL) {
        AppendNode(Options,&AddHere,MakeReflexivity(Syntax,Signature));
    }
    if (strchr(WhatEquality,'s') != NULL) {
        AppendNode(Options,&AddHere,MakeSymmetry(Syntax,Signature));
    }
    if (strchr(WhatEquality,'t') != NULL) {
        AppendNode(Options,&AddHere,MakeTransitivity(Syntax,Signature));
    }

    if (strchr(WhatEquality,'f') != NULL) {
        Symbol = strtok_r(Functors,"\n",&NextSymbol);
        while (Symbol != NULL) {
            // Search in the backward direction because Symbol name may also contain '/' characters
            Slash = strrchr(Symbol,'/');
            *Slash = '\0';
            Slash = strrchr(Symbol,'/');
            *Slash = '\0';
            Arity = atoi(Slash + 1);
            for (Index=1;Index <= Arity;Index++) {
//DEBUG printf("Making function substitution for %s position %d\n",Symbol,Index);
                AppendNode(Options,&AddHere,MakeFunctionSubstitution(Symbol,
Arity,Index,Syntax,Signature));
            }
            Symbol = strtok_r(NULL,"\n",&NextSymbol);
        }
        *Functors = '\0';
    }
    if (strchr(WhatEquality,'p') != NULL) {
        Symbol = strtok_r(SymbolUsage,"\n",&NextSymbol);
        while (Symbol != NULL) {
            // Search in the backward direction because Symbol name may also contain '/' characters
            Slash = strrchr(Symbol,'/');
            *Slash = '\0';
            Slash = strrchr(Symbol,'/');
            *Slash = '\0';
            Arity = atoi(Slash + 1);
            for (Index=1;Index <= Arity;Index++) {
                if (strcmp(Symbol,"$equal") && strcmp(Symbol,"=")) {
//DEBUG printf("Making predicate substitution for %s position %d\n",Symbol,Arity);
                    AppendNode(Options,&AddHere,MakePredicateSubstitution(
Symbol,Arity,Index,Syntax,Signature));
                }
            }
            Symbol = strtok_r(NULL,"\n",&NextSymbol);
        }
    }

    return(EqualityFormulae);
}
//-------------------------------------------------------------------------------------------------
LISTNODE AddEqualityAxioms(OptionsType Options,SIGNATURE Signature, int NumberOfFOF,
int NumberOfCNF) {

    LISTNODE EqualityFormulae;
    char * SymbolUsage;
    char * Functors;
    String AddEqualityPart;
    String WhatEquality;

//----Decide what equality axioms are wanted
    if (strstr(Options.Transformations,"add_equality") == NULL) {
        return(NULL);
    }

    strcpy(AddEqualityPart,strstr(Options.Transformations,"add_equality"));
    if (strchr(AddEqualityPart,'+') != NULL) {
        *(strchr(AddEqualityPart,'+')) = '\0';
    }
    if (strchr(Options.Transformations,':') !=  NULL) {
        strcpy(WhatEquality,strchr(AddEqualityPart,':')+1);
    } else {
        strcpy(WhatEquality,"rstfp");
    }

//----Find out what predicates and functors are used
    SymbolUsage = (char *)Malloc(sizeof(String));
    GetSignatureSymbolUsage(Signature,&SymbolUsage,&Functors);
//----Add equality only if equality predicate is present
    if (strstr(SymbolUsage,"=/2/") == NULL) {
        EqualityFormulae  = NULL;
    } else {
        if (NumberOfFOF > 0 && NumberOfCNF == 0) {
            EqualityFormulae = MakeEqualityFormulae(Options,SymbolUsage,
Functors,tptp_fof,Signature,WhatEquality);
        } else if (NumberOfFOF == 0 && NumberOfCNF > 0) {
            EqualityFormulae = MakeEqualityFormulae(Options,SymbolUsage,
Functors,tptp_cnf,Signature,WhatEquality);
        } else {
            fprintf(stderr, "ERROR: Cannot add equality for empty or mixed types\n");
            exit(EXIT_FAILURE);
        }
    }
    Free((void **)&SymbolUsage);
    return(EqualityFormulae);
}
//-------------------------------------------------------------------------------------------------

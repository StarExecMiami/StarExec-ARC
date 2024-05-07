#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "ParseTSTP.h"
#include "PrintTSTP.h"
#include "Tokenizer.h"
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Parsing.h"
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA NewAnnotatedFormula(SyntaxType Syntax) {

    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = (ANNOTATEDFORMULA)Malloc(sizeof(AnnotatedFormulaType));
    AnnotatedFormula->Syntax = Syntax;
    AnnotatedFormula->NumberOfUses = 0;

    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA NewAnnotatedTSTPFormula(SyntaxType Syntax) {

    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = NewAnnotatedFormula(Syntax);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = NULL;
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status = 
nonstatus;
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.SubStatus = 
nonstatus;
    AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables = NULL;
    AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source = NULL;
    AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo = NULL;
    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------
void FreeAnnotatedTSTPFormula(ANNOTATEDFORMULA * AnnotatedFormula) {

    Free((void **)&((*AnnotatedFormula)->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name));
    assert((*AnnotatedFormula)->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name == NULL);
    FreeFormulaWithVariables(&((*AnnotatedFormula)->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables));
    assert((*AnnotatedFormula)->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables == NULL);
    FreeTerm(&((*AnnotatedFormula)->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),NULL);
    FreeTerm(&((*AnnotatedFormula)->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo),NULL);
    Free((void **)AnnotatedFormula);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA DuplicateAnnotatedTSTPFormula(ANNOTATEDFORMULA Original,
SIGNATURE Signature,int ForceNewVariables) {

    ContextType Context;
    ANNOTATEDFORMULA AnnotatedFormula;

    if (Original == NULL) {
        CodingError("Duplicating a NULL formula\n");
    }
    AnnotatedFormula = NewAnnotatedTSTPFormula(Original->Syntax);

    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = 
CopyHeapString(Original->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status = 
Original->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status;
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.SubStatus = 
Original->AnnotatedFormulaUnion.AnnotatedTSTPFormula.SubStatus;
    AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables =
DuplicateFormulaWithVariables(Original->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables,Signature,
ForceNewVariables);

//----Create context for duplicating non-logical stuff
    Context.Variables = NULL;
    Context.Signature = Signature;
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source =
DuplicateTerm(Original->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source,
Context,0);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo =
DuplicateTerm(Original->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo,
Context,0);

    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA ParseAnnotatedTSTPFormula(READFILE Stream,
SIGNATURE Signature) {

    ContextType Context;
    ANNOTATEDFORMULA AnnotatedFormula;

    if (CheckToken(Stream,lower_word,"fof")) {
        AcceptToken(Stream,lower_word,"fof");
        AnnotatedFormula = NewAnnotatedTSTPFormula(tptp_fof);
    } else {
        AcceptToken(Stream,lower_word,"cnf");
        AnnotatedFormula = NewAnnotatedTSTPFormula(tptp_cnf);
    }
    AnnotatedFormula->NumberOfUses = 1;
    AcceptToken(Stream,punctuation,"(");
    EnsureTokenType(Stream,atomic);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = 
CopyHeapString(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,atomic);
    AcceptToken(Stream,punctuation,",");
    EnsureTokenType(Stream,lower_word);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status = 
StringToStatus(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,lower_word);
//----Check for substatus
    if (CheckToken(Stream,punctuation,"-")) {
        AcceptToken(Stream,punctuation,"-");
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.SubStatus =
StringToStatus(CurrentToken(Stream)->NameToken);
        AcceptTokenType(Stream,lower_word);
    }
    AcceptToken(Stream,punctuation,",");
    AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables = 
ParseFormulaWithVariables(Stream,Signature);

//----Create context for duplicating non-logical stuff
    Context.Variables = NULL;
    Context.Signature = Signature;
//----Check if source and useful info are there
    if (CheckToken(Stream,punctuation,",")) {
        AcceptToken(Stream,punctuation,",");
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source =
ParseTerm(Stream,Context,Context.Variables,non_logical_data,none,NULL);
        if (CheckToken(Stream,punctuation,",")) {
            AcceptToken(Stream,punctuation,",");
            AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo =
ParseTerm(Stream,Context,NULL,non_logical_data,none,NULL);
        }
    }

    AcceptToken(Stream,punctuation,")");
    TakeToken(Stream,punctuation,".");

    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------

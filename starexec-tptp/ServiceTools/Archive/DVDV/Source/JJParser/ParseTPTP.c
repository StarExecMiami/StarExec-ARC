#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "ParseTPTP.h"
#include "Tokenizer.h"
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "ParseTSTP.h"
//-----------------------------------------------------------------------------
FORMULA ParseLiterals(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope) {

    FORMULA Formula;
    FORMULA BinaryFormula;

//----Check for an empty clause
    if (CheckToken(Stream,punctuation,"]")) {
        Formula = NewFormula();
        Formula->Type = atom;
        Formula->FormulaUnion.Atom = NewTerm();
        Formula->FormulaUnion.Atom->Type = predicate;
        Formula->FormulaUnion.Atom->TheSymbol.NonVariable = 
InsertIntoSignature(Context.Signature,predicate,"$false",0);
        Formula->FormulaUnion.Atom->Arguments = NULL;
        return(Formula);
    }

//----Regular old style literals
    if (CheckToken(Stream,unary_connective,"++")) {
        NextToken(Stream);
        Formula = ParseAtom(Stream,Context,EndOfScope);
    } else {
        EnsureToken(Stream,unary_connective,"--");
        Formula = ParseUnaryFormula(Stream,Context,EndOfScope);
    }

//----See if any more
    if (CheckToken(Stream,punctuation,",")) {
        AcceptToken(Stream,punctuation,",");
        BinaryFormula = NewFormula();
        BinaryFormula->Type = binary;
        BinaryFormula->FormulaUnion.BinaryFormula.Connective = disjunction;
        BinaryFormula->FormulaUnion.BinaryFormula.LHS = Formula;
        BinaryFormula->FormulaUnion.BinaryFormula.RHS = ParseLiterals(Stream,
Context,EndOfScope);
        return(BinaryFormula);
    } else {
        return(Formula);
    }
}
//-----------------------------------------------------------------------------
FORMULAWITHVARIABLES ParseTPTPClauseWithVariables(READFILE Stream,
SIGNATURE Signature) {

    FORMULAWITHVARIABLES TPTPClauseWithVariables;
    ContextType Context;
    VARIABLENODE EndOfScope;

    EndOfScope = NULL;

    AcceptToken(Stream,punctuation,"[");
    TPTPClauseWithVariables = NewFormulaWithVariables();

//----Create a context for the parsing
    Context.Variables = &(TPTPClauseWithVariables->Variables);
    Context.Signature = Signature;

    TPTPClauseWithVariables->Formula = ParseLiterals(Stream,Context,
&EndOfScope);
    AcceptToken(Stream,punctuation,"]");

    return(TPTPClauseWithVariables);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA ParseAnnotatedTPTPClause(READFILE Stream,
SIGNATURE Signature) {

    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = NewAnnotatedTSTPFormula(tptp_cnf);
    AcceptToken(Stream,lower_word,"input_clause");
    AcceptToken(Stream,punctuation,"(");
    EnsureTokenType(Stream,lower_word);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = 
CopyHeapString(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,lower_word);
    AcceptToken(Stream,punctuation,",");
    EnsureTokenType(Stream,lower_word);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status = 
StringToStatus(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,lower_word);
    AcceptToken(Stream,punctuation,",");
    AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables = 
ParseTPTPClauseWithVariables(Stream,Signature);
    AcceptToken(Stream,punctuation,")");
    TakeToken(Stream,punctuation,".");

    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA ParseAnnotatedTPTPFormula(READFILE Stream,
SIGNATURE Signature) {

    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = NewAnnotatedTSTPFormula(tptp_fof);
    AcceptToken(Stream,lower_word,"input_formula");
    AcceptToken(Stream,punctuation,"(");
    EnsureTokenType(Stream,lower_word);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = 
CopyHeapString(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,lower_word);
    AcceptToken(Stream,punctuation,",");
    EnsureTokenType(Stream,lower_word);
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status = 
StringToStatus(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,lower_word);
    AcceptToken(Stream,punctuation,",");
    AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables = 
ParseFormulaWithVariables(Stream,Signature);
    AcceptToken(Stream,punctuation,")");
    AcceptToken(Stream,punctuation,".");

    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------

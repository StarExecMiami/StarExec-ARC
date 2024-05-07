#ifndef PARSETSTP_H
#define PARSETSTP_H
//-----------------------------------------------------------------------------
#include "Tokenizer.h"
#include "DataTypes.h"
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA NewAnnotatedFormula(SyntaxType Syntax);
ANNOTATEDFORMULA NewAnnotatedTSTPFormula(SyntaxType Syntax);
void FreeAnnotatedTSTPFormula(ANNOTATEDFORMULA * AnnotatedFormula);
ANNOTATEDFORMULA DuplicateAnnotatedTSTPFormula(ANNOTATEDFORMULA Original,
SIGNATURE Signature,int ForceNewVariables);
ANNOTATEDFORMULA ParseAnnotatedTSTPFormula(READFILE Stream,
SIGNATURE Signature);
//-----------------------------------------------------------------------------
#endif

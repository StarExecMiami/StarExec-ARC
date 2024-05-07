#ifndef PARSETPTP_H
#define PARSETPTP_H
//-----------------------------------------------------------------------------
#include "DataTypes.h"
#include "Tokenizer.h"
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA ParseAnnotatedTPTPClause(READFILE Stream,
SIGNATURE Signature);
ANNOTATEDFORMULA ParseAnnotatedTPTPFormula(READFILE Stream,
SIGNATURE Signature);
//-----------------------------------------------------------------------------
#endif

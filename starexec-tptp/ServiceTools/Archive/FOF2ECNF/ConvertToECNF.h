//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef CONVERT_TO_ECNF_H
#define CONVERT_TO_ECNF_H
//-----------------------------------------------------------------------------
#include <iostream.h>
#include "jjheader.h"
//-----------------------------------------------------------------------------
void ConvertToECNF (LISTNODE *, SIGNATURE, bool);

void MoveOutQuantifiers (FORMULA *);
void SimplifyFormula (FORMULA *, ContextType);
void MoveInNegation (FORMULA *);
void DistributeDisjunctions (FORMULA *, ContextType);
void SplitFormula (LISTNODE *, ContextType);

void ConvertImplication (FORMULA *);
void ConvertReverseImplication (FORMULA *);
void ConvertEquivalence (FORMULA *, ContextType);

LISTNODE NewListNode ();
FORMULA NewBinaryFormula (FORMULA, FORMULA, ConnectiveType);

void DeNegateBinaryFormula (FORMULA * Formula);
void DeNegateQuantifier (FORMULA * Formula);
void DeNegateFormula (FORMULA * Formula);

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

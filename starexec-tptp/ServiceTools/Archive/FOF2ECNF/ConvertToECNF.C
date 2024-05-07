//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/* 
   Author: Steven Trac
   File: ConvertToECNF.C
   Note: File used to convert first order form to existential clause normal
         form. 
*/
//-----------------------------------------------------------------------------
#include "ConvertToECNF.h"
//-----------------------------------------------------------------------------
void FOF2ECNF (LISTNODE *, SIGNATURE, bool);
FORMULA FindNextQ (FORMULA *);
bool FindDoC (FORMULA *, ContextType);
void DDDoC (FORMULA *, ContextType);
void DuplicateAndSplitAnnotatedFormula(LISTNODE *, FORMULA *, ContextType);
bool OneSidedExistential (FORMULA, VARIABLENODE);
//-----------------------------------------------------------------------------
void ConvertToECNF (LISTNODE * Head, SIGNATURE Signature, bool split_formula) {
  //loop through all the formulae, converting one at a time using FOF2ECNF
  LISTNODE * CurrentNode;

  CurrentNode = Head;
  do {
    FOF2ECNF (CurrentNode, Signature, split_formula);
    if ((*CurrentNode)->Next != NULL) CurrentNode = (&(*CurrentNode)->Next);
    else break;
  }
  while (1);
}

//-----------------------------------------------------------------------------
void FOF2ECNF (LISTNODE * Node, SIGNATURE Signature, bool split_formula) {

  FORMULA * Formula;
  ContextType Context;

  Context.Signature = Signature;
  Context.Variables = &(*Node)->AnnotatedFormula->AnnotatedFormulaUnion.
    AnnotatedTSTPFormula.FormulaWithVariables->Variables;
  Formula = &(*Node)->AnnotatedFormula->AnnotatedFormulaUnion.
    AnnotatedTSTPFormula.FormulaWithVariables->Formula,
  //Step 1. Simplify, remove <=, =>, <=>, <~>.
  SimplifyFormula(Formula, Context);
  //Step 2. Move negations in.
  MoveInNegation(Formula);
  //Step 3a. Make all the variables unique
  UniqueifyVariableNames((*Node)->AnnotatedFormula);
  //Step 3b. Move quantifiers out.
  MoveOutQuantifiers(Formula);
  //Step 4. Distribute disjunctions
  // (a | (b & c)) becomes  (a | b) & (a | c)
  DistributeDisjunctions(Formula, Context);
  //Step 5. if split_formula is set to true, split the formula
  if (split_formula) SplitFormula(Node, Context);
}

//-----------------------------------------------------------------------------
void SplitFormula (LISTNODE * Node, ContextType Context) {
  /* Travel down formula, find first formula after the last quantifier.
     If this variable is a conjunction, split formula by LHS and RHS */
  VARIABLENODE Variable;
  FORMULA *CurrentF;
  ConnectiveType Quantifier;

  CurrentF = &(*Node)->AnnotatedFormula->AnnotatedFormulaUnion.
    AnnotatedTSTPFormula.FormulaWithVariables->Formula;
  assert(*CurrentF != NULL);
  do {
    if ((*CurrentF)->Type == quantified) {
      /* Current formula is a quantifier, move down
	 If quantifier is an existential, check to make sure it belongs 
	 to either LHS or RHS of the first conjunction found, not both. If 
	 variable is used on both sides, then this formula can not be split.*/
      Quantifier = (*CurrentF)->FormulaUnion.QuantifiedFormula.Quantifier;
      if (Quantifier == existential) {
	Variable = (*CurrentF)->FormulaUnion.QuantifiedFormula.Variable->
	  TheSymbol.Variable;
	if (!OneSidedExistential(*CurrentF, Variable))
	  //existential has variables on both sides of first conjunction
	  return;
      }
      CurrentF = &(*CurrentF)->FormulaUnion.QuantifiedFormula.Formula;
    }
    else { 
      /* Current formula is not a quantifier.  
	 If current formula is a conjunction, split formula.*/
      if ((*CurrentF)->Type != binary) return; //conjunction not found
      if ((*CurrentF)->FormulaUnion.BinaryFormula.Connective != conjunction)
	return; //conjunction not found
      DuplicateAndSplitAnnotatedFormula(Node, CurrentF, Context);
      //Formula has been split, restart from the top of formula again.
      CurrentF = &(*Node)->AnnotatedFormula->AnnotatedFormulaUnion.
	AnnotatedTSTPFormula.FormulaWithVariables->Formula;
    }
  }
  while (true);
}

//-----------------------------------------------------------------------------
bool OneSidedExistential (FORMULA Formula, VARIABLENODE Variable) {

  FORMULA CurrentF, RHS, LHS;

  CurrentF = Formula;
  /* Find first nonquantifier, if not conjunction return false.
     Go down LHS of conjunction and count variable use, similar for RHS
     If one side is 0, return true */
  do {
    if (CurrentF->Type == quantified)
      CurrentF = CurrentF->FormulaUnion.QuantifiedFormula.Formula;
    else { 
      if (CurrentF->Type != binary) return false;
      if (CurrentF->FormulaUnion.BinaryFormula.Connective != conjunction) 
	return false;
      RHS = CurrentF->FormulaUnion.BinaryFormula.RHS;
      LHS = CurrentF->FormulaUnion.BinaryFormula.LHS;
      if ((CountVariableUsageInFormula(RHS, Variable, NULL) == 0) ||
	  (CountVariableUsageInFormula(LHS, Variable, NULL) == 0))
	return true;
      else
	return false;
    }
  }
  while (true);
}

//-----------------------------------------------------------------------------
void DuplicateAndSplitAnnotatedFormula (LISTNODE * Node, FORMULA * Formula, 
					ContextType Context) {
  /* First remove the conjunction, and replace by the RHS.
     Duplicate this annotated formula and create a new list node.
     Connect this new_list_node->next to node->next, and node->next to 
     new_list_node.
     Now that the Annotated formula with the RHS is duplicated, delete
     this formula, and replace by the LHS. */

  ANNOTATEDFORMULA Original, Copy;
  FORMULA LHS, RHS;
  LISTNODE NewNode;
  String NewName;

  assert((*Formula)->Type == binary &&
	 (*Formula)->FormulaUnion.BinaryFormula.Connective == conjunction);
  LHS = (*Formula)->FormulaUnion.BinaryFormula.LHS;
  RHS = (*Formula)->FormulaUnion.BinaryFormula.RHS;
  Original = (*Node)->AnnotatedFormula;
  //free the conjunction
  Free((void**)Formula);
  //replace by RHS
  *Formula = RHS;
  //Duplicate this annotated formula
  NewNode = NewListNode();
  NewNode->AnnotatedFormula = DuplicateAnnotatedFormula(Original,Context.Signature);
  //add _L to original name
  strcpy(NewName, Original->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
  strcat(NewName, "_L");
  Free((void**)&Original->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
  Original->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = CopyHeapString(NewName);
  //add _L to original name
  Copy = NewNode->AnnotatedFormula;
  strcpy(NewName, Copy->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
  strcat(NewName, "_R");
  Free((void**)&Copy->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
  Copy->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = CopyHeapString(NewName);
  //add node to the list nodes
  NewNode->Next = (*Node)->Next;
  (*Node)->Next = NewNode;
  //free the original RHS
  FreeFormula(&RHS, Context.Variables);
  //replace by the LHS
  *Formula = LHS;
}

//-----------------------------------------------------------------------------
void DistributeDisjunctions (FORMULA * Formula, ContextType Context) {

  bool disjunction_found;

  do {
    disjunction_found = FindDoC (Formula, Context);
  }
  while (disjunction_found);
}

//-----------------------------------------------------------------------------
bool FindDoC (FORMULA * Formula, ContextType Context) {
  //Find Disjunction over Conjunction, duplicate and maybe split formula.
  ConnectiveType Connective;
  FORMULA *LHS, *RHS;

  switch ((*Formula)->Type) {
  case binary:
    //find disjunction over conjunction
    //not a quantifier, continue finding next quantifier in lhs, then rhs
    Connective = (*Formula)->FormulaUnion.BinaryFormula.Connective;
    LHS = &(*Formula)->FormulaUnion.BinaryFormula.LHS;
    RHS = &(*Formula)->FormulaUnion.BinaryFormula.RHS;
    if (Connective == disjunction && 
	((*LHS)->FormulaUnion.BinaryFormula.Connective == conjunction ||
	 (*RHS)->FormulaUnion.BinaryFormula.Connective == conjunction)) {
      //found disjunction over conjunction
      DDDoC (Formula, Context);
      return true;
    }
    else {
      if (FindDoC (LHS, Context)) return true;
      else return FindDoC (RHS, Context);
    }
    break;
  case quantified:
    return FindDoC(&(*Formula)->FormulaUnion.QuantifiedFormula.Formula,Context);
    break;
  case unary:
    //not a quantifier, continue finding next quantifier after negation
    return FindDoC(&(*Formula)->FormulaUnion.UnaryFormula.Formula, Context);
    break;
  default:
    assert ((*Formula)->Type == atom || (*Formula)->Type == nonformulatype);
    return false; //at the bottom lvl, do nothing 
    break;
  }
}

//-----------------------------------------------------------------------------
void DDDoC (FORMULA * Formula, ContextType Context) {

  //Distribute and Duplicate Disjunction over Conjunction
  FORMULA *LHS, *RHS, *SLHS, *SRHS;
  FORMULA *TBDFormula, *SplitFormula, DupFormula, BinaryFormula;

  LHS = &(*Formula)->FormulaUnion.BinaryFormula.LHS;
  RHS = &(*Formula)->FormulaUnion.BinaryFormula.RHS;
  assert((*Formula)->FormulaUnion.BinaryFormula.Connective == disjunction);
  //change top to conjunction
  (*Formula)->FormulaUnion.BinaryFormula.Connective = conjunction;

  if ((*LHS)->FormulaUnion.BinaryFormula.Connective == conjunction) {
    // (a & b) | (c) becomes (a | c) & (b | d), where d is a dup of c
    //change to disjunction
    TBDFormula = RHS;
    SplitFormula = LHS;
  }
  else {
    // (a) | (b & c) becomes (a | b) & (d | c), where d is a dup of a
    assert ((*RHS)->FormulaUnion.BinaryFormula.Connective == conjunction);
    TBDFormula = LHS;
    SplitFormula = RHS;
  }
  /* SLHS - Split Left Hand Side
     SRHS - Split Right Hand Side
     TBDFormula - To Be Duped Formula
     DupFormula - Duping of TBDFormula
     Disjunction 1 - (SLHS | TBDFormula)
     Disjunction 2 - (SRHS | DupFormula)
     Conjunction - (Disjunction 1 & Disjunction 2) */
  (*SplitFormula)->FormulaUnion.BinaryFormula.Connective = disjunction;
  SLHS = &(*SplitFormula)->FormulaUnion.BinaryFormula.LHS;
  SRHS = &(*SplitFormula)->FormulaUnion.BinaryFormula.RHS;
  DupFormula = DuplicateInternalFormulaWithVariables(*TBDFormula, Context);
  //Create a new conjunction with SRHS as new LHS, and Dup as new RHS
  BinaryFormula = NewBinaryFormula(*SRHS, DupFormula, disjunction);
  //Flip the SRHS and RHS so (a | b) & c is now (a | c) ...
  *SRHS = *TBDFormula;
  *TBDFormula = BinaryFormula;
}

//-----------------------------------------------------------------------------
void MoveOutQuantifiers (FORMULA * Formula) {
  
  FORMULA *CurrentF, QuantifiedFormula;
  CurrentF = Formula;
  
  do {
    if ((*CurrentF)->Type == quantified) {
      //current formula is already a quantifier, move down
      QuantifiedFormula = *CurrentF;
      CurrentF = &(QuantifiedFormula->FormulaUnion.QuantifiedFormula.Formula);
    }
    else { 
      /* Current formula is not a quantifier, find one down the list
	 if none exists, NULL is returned, if a quantifier exists, put 
	 quantifier in front of current formula, and move down  */
      QuantifiedFormula = FindNextQ (CurrentF); 
      if (QuantifiedFormula != NULL) {
	QuantifiedFormula->FormulaUnion.QuantifiedFormula.Formula = *CurrentF;
	*CurrentF = QuantifiedFormula;
      }
      else { /* No quantifier is left */ }
    }
  }
  while (QuantifiedFormula != NULL);
}

//-----------------------------------------------------------------------------
FORMULA FindNextQ (FORMULA * Formula) {
  /* First start from root and find the next quantifier.
     From this position, start to find the next quantifier, this quantifier
     will go in the place of the non-quantifier.
     Continue till there are no more quantifiers. */
  FORMULA NextFormula = NULL;

  switch ((*Formula)->Type) {
  case quantified:
    //stop recursion, remove quantifier, start backtracking
    NextFormula = *Formula;
    (*Formula) = (NextFormula)->FormulaUnion.QuantifiedFormula.Formula;
    return NextFormula;
    break;
  case binary:
    //not a quantifier, continue finding next quantifier in lhs, then rhs
    NextFormula = FindNextQ (&(*Formula)->FormulaUnion.BinaryFormula.LHS);
    if (NextFormula != NULL) {
      //found quantifier in lhs, backtrack
      return NextFormula;
    }
    //find next in rhs
    return (FindNextQ (&(*Formula)->FormulaUnion.BinaryFormula.RHS));
  case unary:
    //not a quantifier, continue finding next quantifier after negation
    return (FindNextQ (&(*Formula)->FormulaUnion.UnaryFormula.Formula));
  default:
    assert ((*Formula)->Type == atom || (*Formula)->Type == nonformulatype);
    return NULL;
    //at the bottom lvl, do nothing 
    break;
  }
}

//-----------------------------------------------------------------------------
void SimplifyFormula (FORMULA * Formula, ContextType Context) {

  FORMULA CurrentFormula;
  CurrentFormula = *Formula;
  assert (Formula != NULL);
  int Simplify = 1;

  switch (CurrentFormula->Type) {
  case binary:
    assert (CurrentFormula->FormulaUnion.BinaryFormula.LHS != NULL && 
	    CurrentFormula->FormulaUnion.BinaryFormula.RHS != NULL);
    switch (CurrentFormula->FormulaUnion.BinaryFormula.Connective) {
    case disjunction:
    case conjunction:
    case negateddisjunction:
    case negatedconjunction:
      //do nothing
      break;
    case implication:
      ConvertImplication (Formula);
      break;
    case equivalence:
      ConvertEquivalence(Formula, Context);
      break;
    case reverseimplication:
      ConvertReverseImplication (Formula);
      break;
    case nonequivalence:
      //remove nonequivalence,add negation, change to equivalence
      CurrentFormula->FormulaUnion.BinaryFormula.Connective = equivalence;
      NegateFormula(Formula, Simplify);
      Formula = &(*Formula)->FormulaUnion.UnaryFormula.Formula;
      break;
    default:
      //no other binary connectives to deal with for now
      break;
    }
    assert((*Formula)->Type == binary);
    SimplifyFormula (&(*Formula)->FormulaUnion.BinaryFormula.LHS, Context);
    SimplifyFormula (&(*Formula)->FormulaUnion.BinaryFormula.RHS, Context);
    break;
  case quantified:
    //Do nothing, continue down into formula
    SimplifyFormula (&(*Formula)->FormulaUnion.QuantifiedFormula.Formula, 
		     Context);
    break;
  case unary:
    //Do nothing, continue down into formula
    SimplifyFormula (&(*Formula)->FormulaUnion.UnaryFormula.Formula, Context);
    break;
  default:
    assert (CurrentFormula->Type == atom || 
	    CurrentFormula->Type == nonformulatype);
    //at the bottom lvl, do nothing 
    break;
  }
}

//-----------------------------------------------------------------------------
LISTNODE NewListNode () {
  
  LISTNODE ListNode;
  
  ListNode = (LISTNODE)Malloc(sizeof(ListNodeType));
  ListNode->AnnotatedFormula = NULL;
  ListNode->Next = NULL;
  return (ListNode);
}

//-----------------------------------------------------------------------------
void ConvertImplication (FORMULA * Formula) {
  //remove implications, convert implication to disjunction,
  // (a => b) becomes (~a | b) 
  (*Formula)->FormulaUnion.BinaryFormula.Connective = disjunction;
  NegateFormula(&(*Formula)->FormulaUnion.BinaryFormula.LHS, 1);
}

//-----------------------------------------------------------------------------
void ConvertReverseImplication (FORMULA * Formula) {
  //remove reverse implication, convert reverseimplication to disjunction
  // (a <= b) becomes (a | ~b) 
  (*Formula)->FormulaUnion.BinaryFormula.Connective = disjunction;
  NegateFormula(&(*Formula)->FormulaUnion.BinaryFormula.RHS, 1);
}

//-----------------------------------------------------------------------------
void ConvertEquivalence (FORMULA * Formula, ContextType Context) {
  //Formula is at an equivalence.  Break into <= and =>. 
  FORMULA NewFormula, BinaryFormula;
  assert ((*Formula)->Type == binary);
  assert ((*Formula)->FormulaUnion.BinaryFormula.LHS != NULL);
  assert ((*Formula)->FormulaUnion.BinaryFormula.RHS != NULL);
  assert ((*Formula)->FormulaUnion.BinaryFormula.Connective == equivalence);
  //duplicate formula to form a => b and a <= b, connect with conjunction
  (*Formula)->FormulaUnion.BinaryFormula.Connective = implication;
  NewFormula = DuplicateInternalFormulaWithVariables(*Formula, Context);
  NewFormula->FormulaUnion.BinaryFormula.Connective = reverseimplication;
  BinaryFormula = NewBinaryFormula (*Formula, NewFormula, conjunction);
  (*Formula) = BinaryFormula;
}

//-----------------------------------------------------------------------------
void MoveInNegation (FORMULA * Formula) {

  FORMULA CurrentFormula, NextFormula;

  CurrentFormula = *Formula;
  assert (CurrentFormula != NULL);
  switch (CurrentFormula->Type) {
  case binary:
    assert (CurrentFormula->FormulaUnion.BinaryFormula.LHS != NULL && 
	    CurrentFormula->FormulaUnion.BinaryFormula.RHS != NULL);
    switch (CurrentFormula->FormulaUnion.BinaryFormula.Connective) {
    case disjunction:
      break;
    case conjunction:
      //do nothing
      break;
    case implication:
    case equivalence:
    case reverseimplication:
    case nonequivalence:
      //no more implications,equivalence/nonequivalence,reverse implication
      assert(false);
      break;      
    case negateddisjunction:
    case negatedconjunction:
      DeNegateBinaryFormula (Formula);
      break;
    default:
      //no other binary connectives to deal with for now
      break;
    }
    MoveInNegation (&(*Formula)->FormulaUnion.BinaryFormula.LHS);
    MoveInNegation (&(*Formula)->FormulaUnion.BinaryFormula.RHS);
    break;
  case quantified:
    //Do nothing, continue down into formula
    MoveInNegation (&(*Formula)->FormulaUnion.QuantifiedFormula.Formula);
    break;
  case unary:
    //move negations in
    NextFormula = CurrentFormula->FormulaUnion.UnaryFormula.Formula;
    assert (NextFormula != NULL);
    assert (CurrentFormula->FormulaUnion.UnaryFormula.Connective == negation);
    switch (NextFormula->Type) {
    case unary:
      //double negation, remove both
      if (NextFormula->FormulaUnion.UnaryFormula.Connective == negation) {
	DeDoubleNegateFormula(Formula);
	MoveInNegation (Formula);
      }	
      else
	MoveInNegation (&((*Formula)->FormulaUnion.UnaryFormula.Formula));
      break;
    case quantified:
      //denegate the quantifier
      DeNegateQuantifier(Formula);
      MoveInNegation (Formula);
      break;
    case binary:
      switch (NextFormula->FormulaUnion.BinaryFormula.Connective) {
      case implication:
      case reverseimplication:
      case equivalence:
      case nonequivalence:
	//no more implications,equivalence/nonequivalence,reverse implication
	assert(false);
	break;
      case conjunction:
      case disjunction:
      case negatedconjunction:
      case negateddisjunction:
	DeNegateBinaryFormula(Formula);
	MoveInNegation (Formula);
	break;
      default:
	//should not reach here
	assert(false);
	break;
	break;
      }
    default:
      break; //nothing to do
    }
    break;
  default:
    assert ((*Formula)->Type == atom || (*Formula)->Type == nonformulatype);
    //at the bottom lvl, do nothing 
    break;
  }
}

//-----------------------------------------------------------------------------
FORMULA NewBinaryFormula (FORMULA LHS, FORMULA RHS, ConnectiveType Connective) {
  /*Creates a new binary formula using the connective passed, and the 
    formulas will be the LHS and RHS of the new binary formula.*/
  FORMULA BinaryFormula;

  assert (LHS != NULL && RHS != NULL);
  BinaryFormula = NewFormula();
  BinaryFormula->Type = binary;
  BinaryFormula->FormulaUnion.BinaryFormula.Connective = Connective;
  BinaryFormula->FormulaUnion.BinaryFormula.LHS = LHS;
  BinaryFormula->FormulaUnion.BinaryFormula.RHS = RHS;
  return BinaryFormula;
}

//-----------------------------------------------------------------------------
void DeNegateBinaryFormula (FORMULA * Formula) {
  /* DeNegate the binary formula by converting the connective to a new
     binary connective once the formula is DeNegated. */
  int Simplify = 1;
  FORMULA BinaryFormula, RHS;
  ConnectiveType Connective;

  //only binary formulas we denegate are neg.disjunction and neg.conjunction
  if ((*Formula)->Type == binary) {
    Connective = (*Formula)->FormulaUnion.BinaryFormula.Connective;
    if (Connective == negatedconjunction || Connective == negateddisjunction) {
      if (Connective == negatedconjunction)
      // ~(a & b)  becomes (~a | ~b)
	(*Formula)->FormulaUnion.BinaryFormula.Connective = disjunction;
      else  //Connective == negateddisjunction, ~(a | b) becomes (~a & ~b)
	(*Formula)->FormulaUnion.BinaryFormula.Connective = conjunction;
      NegateFormula(&(BinaryFormula->FormulaUnion.BinaryFormula.LHS),Simplify);
      NegateFormula(&(BinaryFormula->FormulaUnion.BinaryFormula.RHS),Simplify);
    }
  }
  if ((*Formula)->Type == unary && 
      (*Formula)->FormulaUnion.UnaryFormula.Connective == negation) {
    BinaryFormula = (*Formula)->FormulaUnion.UnaryFormula.Formula;
    if (BinaryFormula->Type == binary) {
      Connective = BinaryFormula->FormulaUnion.BinaryFormula.Connective;
      switch (Connective) {
      case implication:
	//convert implication to conjunction
	BinaryFormula->FormulaUnion.BinaryFormula.Connective = conjunction;
	//move existing negation to RHS (saves freeing and creating negation)
	RHS = BinaryFormula->FormulaUnion.BinaryFormula.RHS;
	(*Formula)->FormulaUnion.UnaryFormula.Formula = RHS;
	BinaryFormula->FormulaUnion.BinaryFormula.RHS = *Formula;
	*Formula = BinaryFormula;
	break;
      case conjunction:
      case disjunction:
	if (Connective == conjunction) 
	  //convert conjunction to disjunction
	  BinaryFormula->FormulaUnion.BinaryFormula.Connective = disjunction;
	else
	  //convert disjunction to conjunction
	  BinaryFormula->FormulaUnion.BinaryFormula.Connective = conjunction;
	//add negation to LHS
	NegateFormula(&BinaryFormula->FormulaUnion.BinaryFormula.LHS, 
		      Simplify);
	//move existing negation to RHS (saves freeing and creating negation)
	RHS = BinaryFormula->FormulaUnion.BinaryFormula.RHS;
	(*Formula)->FormulaUnion.UnaryFormula.Formula = RHS;
	BinaryFormula->FormulaUnion.BinaryFormula.RHS = *Formula;
	*Formula = BinaryFormula;	
	break;
      case negatedconjunction:
	BinaryFormula->FormulaUnion.BinaryFormula.Connective = conjunction;
	DeNegateFormula(Formula);
	break;
      case negateddisjunction:
	BinaryFormula->FormulaUnion.BinaryFormula.Connective = disjunction;
	DeNegateFormula(Formula);
	break;
      case nonequivalence:
	BinaryFormula->FormulaUnion.BinaryFormula.Connective = equivalence;
	DeNegateFormula(Formula);
	break;
      case equivalence:
	//nothing for now
	break;
      default:
	break;
      }      
    }
  }
}

//-----------------------------------------------------------------------------
void DeNegateQuantifier (FORMULA * Formula) {
  /* DeNegate the quantifier, switch universal to existenstial (or vice-versa),
     and then move the negation in. */
  FORMULA QuantifiedFormula, NextFormula;

  if ((*Formula)->Type == unary && 
      (*Formula)->FormulaUnion.UnaryFormula.Connective == negation) {
    QuantifiedFormula = (*Formula)->FormulaUnion.UnaryFormula.Formula;
    if (QuantifiedFormula->Type == quantified) {
      NextFormula = QuantifiedFormula->FormulaUnion.QuantifiedFormula.Formula;
      if (QuantifiedFormula->FormulaUnion.QuantifiedFormula.Quantifier == 
	  existential)
	QuantifiedFormula->FormulaUnion.QuantifiedFormula.Quantifier = 
	  universal;
      else {
	assert(QuantifiedFormula->FormulaUnion.QuantifiedFormula.Quantifier = 
	       universal);
	QuantifiedFormula->FormulaUnion.QuantifiedFormula.Quantifier = 
	  existential;
      }
      //move negation after quantifier (saves creating and deleting negation
      (*Formula)->FormulaUnion.UnaryFormula.Formula = NextFormula;
      QuantifiedFormula->FormulaUnion.QuantifiedFormula.Formula = *Formula;
      *Formula = QuantifiedFormula;
    }
  }
}

//-----------------------------------------------------------------------------
void DeNegateFormula (FORMULA * Formula) {
  //remove negation
  FORMULA NegatedFormula;

  if ((*Formula)->Type == unary && 
      (*Formula)->FormulaUnion.UnaryFormula.Connective == negation) {
    NegatedFormula = *Formula;
    (*Formula) = NegatedFormula->FormulaUnion.UnaryFormula.Formula;
    Free((void**)&NegatedFormula);
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

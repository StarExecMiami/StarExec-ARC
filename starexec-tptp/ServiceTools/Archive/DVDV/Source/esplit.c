/*-----------------------------------------------------------------------------
 * FILE: esplit.c
 * AUTHOR: Diego Belfiore
 *
 * Defines the E split verification functions.
 * --------------------------------------------------------------------------*/
#include "dvdv.h"
//-----------------------------------------------------------------------------
LISTNODE make_esplit_axiom (ANNOTATEDFORMULA f,
                           SIGNATURE sig);

LISTNODE make_esplit_axiom_list (LISTNODE axioms,
                                 LISTNODE *first_split,
                                 SIGNATURE sig);

int check_variable_uniqueness (LISTNODE axiom_set,
                               LISTNODE *first_split,
                               ARGUMENTLIST arg_list,
                               SIGNATURE signature);

FORMULA add_epred_formula(FORMULA f, FORMULA *list, 
                          int *list_size, int *last_index);

LISTNODE find_next_esplit_tail(LISTNODE head);

FORMULA insert_epred_tail (FORMULA f, FORMULA *list,
                           int *list_size, int *last_index);
//-----------------------------------------------------------------------------
int check_variable_uniqueness (LISTNODE axiom_set,
                               LISTNODE *first_split,
                               ARGUMENTLIST arg_list,
                               SIGNATURE signature)
{
  LISTNODE tail;
  FORMULA *list;
  FORMULA f, dup;
  int list_size, last_index;

  list_size = 8;
  last_index = 0;
  list = (FORMULA *) malloc(sizeof(FORMULA *) * list_size);

  tail = *first_split;
  while ((tail = find_next_esplit_tail(tail)) != NULL) {
    f = (tail->AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
         FormulaWithVariables->Formula);
    if ((dup = insert_epred_tail(f, list, &list_size, &last_index)) != NULL) {
      printf("STRUCTURAL ERROR: Predicate \"");
      PrintTSTPFormula(stdout, dup, 1, 0, 1, none, none, 1);
      printf("\" is already used in proof. \n");
      return FAILURE;
    }
    tail = tail->Next;
  }

  free(list);
  return SUCCESS;
}
//-----------------------------------------------------------------------------
FORMULA insert_epred_tail (FORMULA f, FORMULA *list,
                           int *list_size, int *last_index)
{
  FORMULA pred;

  if (f->Type == unary) {
    pred = f->FormulaUnion.UnaryFormula.Formula;
    if (add_epred_formula(pred, list, list_size, last_index) != NULL)
      return pred;

    return NULL;
  }

  pred = f->FormulaUnion.BinaryFormula.LHS->FormulaUnion.UnaryFormula.Formula;
  if (add_epred_formula(pred, list, list_size, last_index) != NULL)
    return pred;

  return insert_epred_tail(f->FormulaUnion.BinaryFormula.RHS, list,
                           list_size, last_index);
}
//-----------------------------------------------------------------------------
/** Inserts f and returns NULL if f is not in list. Returns pointer
    to formula otherwise. */
FORMULA add_epred_formula(FORMULA f, FORMULA *list, 
                          int *list_size, int *last_index)
{
  int i;

  if (*last_index == *list_size - 1) {
    *list_size *= 2;
    realloc(list, *list_size);
  }
  for (i = 0; i < *last_index; i++) {
    if (strcmp(list[i]->FormulaUnion.Atom->TheSymbol.NonVariable->NameSymbol,
               f->FormulaUnion.Atom->TheSymbol.NonVariable->NameSymbol) == 0)
      return list[i];
  }

  list[(*last_index)++] = f;
  return NULL;
}
//-----------------------------------------------------------------------------
LISTNODE find_next_esplit_tail(LISTNODE head)
{
  LISTNODE i;
  String inf_rule, inf_info_term;

  i = head;
  while (1) {
    if (i == NULL)
      return NULL;

    GetInferenceRule(i->AnnotatedFormula, inf_rule);
    if (GetInferenceInfoTerm(i->AnnotatedFormula, 
                             inf_rule, inf_info_term) == NULL)
      strcpy(inf_info_term, "UNKNOWN");
    if (strncmp (inf_info_term, "split(esplit", 12) == 0)
      break;
    i = i->Next;
  }
  while (1) {
    if (i == NULL)
      return NULL;

    GetInferenceRule(i->Next->AnnotatedFormula, inf_rule);
    if (GetInferenceInfoTerm(i->Next->AnnotatedFormula, 
                             inf_rule, inf_info_term) == NULL)
      strcpy(inf_info_term, "UNKNOWN");
    if (strncmp (inf_info_term, "split(esplit", 12) != 0)
      break;
    i = i->Next;
  }
  return i;
}
//-----------------------------------------------------------------------------
int geoff_esplit_check (LISTNODE axiom_set,
                        LISTNODE *first_split,
                        ARGUMENTLIST arg_list,
                        SIGNATURE signature)
{
  int verified;
  LISTNODE list, i, prev;
  FILE *obl_stream;
  String f_name;
  String obl_fname, anf_name;
  String inf_rule, inf_info_term;
  
  if (check_variable_uniqueness(axiom_set, first_split, 
                                arg_list, signature) != SUCCESS)
    return FAILURE;
  
  verified = SUCCESS;
  list = make_esplit_axiom_list(axiom_set, first_split, signature);
  prev = i = *first_split;
  while (1) {
    GetName(i->AnnotatedFormula, f_name);
    GetInferenceRule(i->AnnotatedFormula, inf_rule);
    if (GetInferenceInfoTerm(i->AnnotatedFormula, 
                             inf_rule, inf_info_term) == NULL)
      strcpy(inf_info_term, "UNKNOWN");
    if (strncmp (inf_info_term, "split(esplit", 12) != 0)
      break;

    GetName(i->AnnotatedFormula, anf_name);
    sprintf(obl_fname,"%s/Derived/Obligations/%s_%s.obl", 
            arg_list->baseDirectory, anf_name, arg_list->host_pid_name);
    obl_stream = s_fopen(obl_fname, "w");      
    PrintListOfAnnotatedTSTPNodes(obl_stream, list, tptp);
    SetStatus(i->AnnotatedFormula, conjecture, nonstatus);
    PrintAnnotatedTSTPNode(obl_stream, i->AnnotatedFormula, tptp, 1);
    fclose(obl_stream);

    if ((verified = run_systems (arg_list, anf_name, obl_fname)) != TRUE) {
      printf ("%% esplit node \'%s\' FAILED verification. \n", f_name);
      break;
    }

    printf ("%% esplit node \'%s\' passed verification. \n", f_name);
    prev = i;
    i = i->Next;
  }
  FreeListOfAnnotatedFormulae(&list);
  *first_split = prev;
  return verified;
}
//-----------------------------------------------------------------------------
LISTNODE make_esplit_axiom_list (LISTNODE axioms,
                                 LISTNODE *first_split,
                                 SIGNATURE sig)
{
  LISTNODE list, head, i;
  String inf_rule, inf_info_term;
  String p_name_list;
  char *p_name;

  GetParentNames((*first_split)->AnnotatedFormula, p_name_list);
  p_name = strtok(p_name_list, "\n");
  head = NewListNode(GetAnnotatedFormulaFromListByName(axioms, p_name));
  SetStatus(head->AnnotatedFormula, axiom, nonstatus);
  list = make_esplit_axiom((*first_split)->AnnotatedFormula, sig);
  head->Next = list;
  i = (*first_split)->Next;
  while (1) {
    GetInferenceRule (i->Next->AnnotatedFormula, inf_rule);
    if (GetInferenceInfoTerm (i->Next->AnnotatedFormula, inf_rule, 
                              inf_info_term) == NULL)
      strcpy(inf_info_term, "UNKNOWN");
    if (strncmp (inf_info_term, "split(esplit", 12) != 0)
      break;

    list->Next = make_esplit_axiom(i->AnnotatedFormula, sig);
    list = list->Next;
    i = i->Next;
  }
  list->Next = NULL;

  return head;
}
//-----------------------------------------------------------------------------
/** Turns [!: C_i](C_i | t_i) into [!: C_i](~C_i <=> t_i) */

LISTNODE make_esplit_axiom (ANNOTATEDFORMULA f,
                           SIGNATURE sig)
{
  LISTNODE node;
  FORMULA the_formula;
  ANNOTATEDFORMULA ax;

  ax = DuplicateAnnotatedFormula(f, sig);
  the_formula = (ax->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
                 FormulaWithVariables->Formula);

  while (the_formula->Type == quantified) 
    the_formula = the_formula->FormulaUnion.QuantifiedFormula.Formula;
  
  if (the_formula->Type != binary || 
      the_formula->FormulaUnion.BinaryFormula.Connective != disjunction) {
      printf("ERROR: Formula is not in a FOFified clause. \n");
      exit(-1);
  }

  the_formula->FormulaUnion.BinaryFormula.Connective = equivalence;
  NegateFormula(&(the_formula->FormulaUnion.BinaryFormula.RHS),1);
  SetStatus(ax, axiom, nonstatus);
  node = NewListNode(ax);

  return node;
}
//-----------------------------------------------------------------------------

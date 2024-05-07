/*----------------------------------------------------------------------------
 * FILE: structure_check.c
 * AUTHOR: Diego Belfiore
 *
 * Defines functions used for structural verification
 *--------------------------------------------------------------------------*/
#include "dvdv.h"

int
is_antikid (ANNOTATEDFORMULA the_formula)
{
  String split_info;
  String inference_type;
  assert (the_formula != NULL);

  if (GetInferenceInfoTerm (the_formula, "status", inference_type) == NULL)
    strcpy (inference_type, "unknown");
  if (strcmp (inference_type, "status(split)") == 0)
    {
      get_split_info (the_formula, split_info);
      if (split_info[strlen(split_info) - 1] == 'a')
        return TRUE;
    }
  return FALSE;
}
//-----------------------------------------------------------------------------
int
is_false_clause (ANNOTATEDFORMULA the_formula)
{
  char *info_string;
  char *other_usage;

  info_string = (char *) malloc (sizeof (String));
  GetAnnotatedFormulaSymbolUsage (the_formula, &info_string, &other_usage);
  if (strcmp (info_string, "$false/0/1\n") == 0) {
    free (info_string);
    return TRUE;
  }
  else {
    free (info_string);
    return FALSE;
  }
}
//-----------------------------------------------------------------------------
void
get_split_info (ANNOTATEDFORMULA the_formula,
		String put_info_here)
{ /* Retrieves split information found in the position() argument of the
   * node's source. Some string combination of l, r, and a characters. */
  TERM split_info;

  split_info = (the_formula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
		Source->Arguments[1]->Arguments[1]->Arguments[1]->
		Arguments[0]->Arguments[0]);		 
  TSTPTermToString (split_info, put_info_here);
}
//-----------------------------------------------------------------------------
tree_queue
build_history_queue (TREENODE the_node)
{ /* Breadth-first traversal through subtree rooted at the_node.
   * Returns every ancestor of this root. Doesn't follow false clauses
   * or antikids. */
  int parent;
  tree_queue the_queue;
  tq_node queue_iterator;

  the_queue = new_tree_queue ();
  add_tq_node (&the_queue, the_node);
  for (queue_iterator = the_queue->head; queue_iterator != NULL;
       queue_iterator = queue_iterator->next)
    {
      for (parent = 0; parent < queue_iterator->the_node->NumberOfParents;
           parent++)
        { /* Shouldn't follow antikids or false clauses. This would create
           * bogus results in structural verification.  */
          if (is_antikid ((queue_iterator->the_node->Parents[parent])->
                          AnnotatedFormula) == FALSE &&
              is_false_clause((queue_iterator->the_node->Parents[parent])->
                              AnnotatedFormula) == FALSE) 
            {
              add_tq_node (&the_queue, queue_iterator->the_node->
                           Parents[parent]);
            }
        }
    }
  return the_queue;
}
//-----------------------------------------------------------------------------
void
build_history_string (tree_queue the_queue,
		      String put_history_here)
{
  String split_info;
  String inference_type;
  String formula_name;
  tq_node queue_iterator;

  strcpy (split_info, "");
  strcpy (inference_type, "");
  strcpy (formula_name, "");
  for (queue_iterator = the_queue->head; queue_iterator != NULL;
       queue_iterator = queue_iterator->next)
    {
      GetInferenceInfoTerm (queue_iterator->the_node->AnnotatedFormula,
			    "status", inference_type);
      if (strcmp (inference_type, "status(split)") == 0)
	{
	  get_split_info (queue_iterator->the_node->AnnotatedFormula,
			  split_info);
	  strcat (put_history_here, split_info);
	  strcat (put_history_here, "$");
	}
    }
  strcat (put_history_here, "\0");
}
//-----------------------------------------------------------------------------
int
verify_history_string (char *history)
{ /* Takes a String array as an argument and returns the build history table
   * with the number of entries it has.  */
  int word_count;
  int history_iterator;
  int entry_index;
  int entry_length;
  int structure_fault;
  char *history_chopper;
  String *history_table;

  structure_fault = FALSE;
  for (word_count = 0, history_iterator = 0; 
       history[history_iterator] != '\0'; history_iterator++) {
    if (history[history_iterator] == '$')
      word_count++;
  }
  
  history_table = malloc (word_count * sizeof (String));
  assert (history_table != NULL);
  history_chopper = NULL;
  history_iterator = 0;
  history_chopper = strtok (history, "$");
  while (history_chopper != NULL) {
    strcpy (history_table[history_iterator], history_chopper);
    history_iterator++;
    history_chopper = strtok (NULL, "$");
  }
  for (entry_index = 0; entry_index < word_count && structure_fault == FALSE; 
       entry_index++) {
    entry_length = strlen (history_table[entry_index]);
    for (history_iterator = 0; history_iterator < word_count;
         history_iterator++) {
      if (strncmp (history_table[entry_index], 
                   history_table[history_iterator], entry_length - 1) == 0) {
        if ((history_table[entry_index][entry_length-1] == 'l' &&
             history_table[history_iterator][entry_length-1] == 'r') ||  
            (history_table[entry_index][entry_length-1] == 'r' &&
             history_table[history_iterator][entry_length-1] == 'l'))
          {  
            structure_fault = TRUE;
            break;
          }
      }
    }
  }
  free (history_table);
  return structure_fault;
}
//-----------------------------------------------------------------------------
tree_queue
build_root_list (ROOTLIST root_list, LISTNODE head)
{
  tree_queue the_queue;
  LISTNODE iterator;
  TREENODE *new_node;
  String name;
  
  the_queue = new_tree_queue ();
  assert (root_list != NULL);
  for (iterator = head; iterator != NULL; iterator = iterator->Next) {
    if (is_false_clause (iterator->AnnotatedFormula) == TRUE) { 
      GetName (iterator->AnnotatedFormula, name);
      new_node = GetNodeFromRootListByAnnotatedFormulaName (root_list, name);
      assert (new_node != NULL);
      add_tq_node (&the_queue, *new_node);
    }
  }
  return the_queue;
}
//-----------------------------------------------------------------------------
tree_queue
find_roots (ROOTLIST root_list, LISTNODE false_root)
{
  int parent;
  tree_queue the_queue;
  tq_node queue_iterator;
  String formula_name;
  TREENODE * node;

  the_queue = new_tree_queue ();
  GetName (false_root->AnnotatedFormula, formula_name);
  node = GetNodeFromRootListByAnnotatedFormulaName (root_list, formula_name);
  add_tq_node (&the_queue, *node);
  for (queue_iterator = the_queue->head; queue_iterator != NULL;
       queue_iterator = queue_iterator->next) {
    for (parent = 0; parent < queue_iterator->the_node->NumberOfParents;
         parent++) { 
          if (is_antikid ((queue_iterator->the_node->Parents[parent])->
                          AnnotatedFormula) == FALSE) { 
            add_tq_node (&the_queue, queue_iterator->the_node->
                         Parents[parent]);
          }
    }
  }
  return the_queue;
}
//-----------------------------------------------------------------------------
int
starL_starR_failure (TREENODE false_clause)
{ /* Performs the *l *r verification for one false clause. 
   * Returns TRUE if there's a structure fault and FALSE if everything is
   * okay. */
  String history_string;
  String formula_name;
  int structure_fault;
  tree_queue the_queue;

  strcpy (history_string, "");
  GetName (false_clause->AnnotatedFormula, formula_name);
  the_queue = build_history_queue (false_clause);
  build_history_string (the_queue, history_string);
  structure_fault = FALSE;
  structure_fault =  verify_history_string (history_string);
  return structure_fault;
}
//-----------------------------------------------------------------------------
int
verify_starL_starR (tree_queue false_list)
{ /* Performs *l *r verification on every false clause in the proof.
   * Returns TRUE if there are no structure faults, 
   * and FALSE otherwise.
   * Prints the false node that causes the structural failure. */
  tq_node c_false;         /* Proof forest iterator. */
  int structure_fault;     /* TRUE if there's a structure fault. */
  int structure_sound;     /* TRUE if no structure fault occurs. */

  structure_fault = FALSE;
  structure_sound = TRUE;
  for (c_false = false_list->head; c_false != NULL; c_false = c_false->next) {
    structure_fault = starL_starR_failure (c_false->the_node);
    if (structure_fault == TRUE) {
      printf ("%% Structural failure detected: the following node is \n"
              "derived using both left and right split siblings. \n");
      PrintAnnotatedTSTPNode (stdout, c_false->the_node->AnnotatedFormula, 
                              tptp, 1);
      structure_sound = FALSE;
      break;
    }
  }
  return structure_sound;
}
//-----------------------------------------------------------------------------
tq_node 
node_in_queue (TREENODE the_node, tree_queue the_queue)
{ /* Returns a pointer to the_node's position in the_queue if it has already
   * been added, and NULL otherwise  */
  tq_node c_node;            /* Node iterator. */

  for (c_node = the_queue->head; c_node != NULL; c_node = c_node->next) {
    if (c_node->the_node == the_node) {
      return c_node;
      break;
    }
  }
  return NULL;
}
//-----------------------------------------------------------------------------
int
verify_split_completion (LISTNODE head, ROOTLIST root_list)
{ /* Verifies that all splits that must be completed are completed.
   * return TRUE if all splits are completed. */
  int root_count;              /* Number of clauses in false_ancestor_list  */
  int c_root_number;               /* Used to iterate false_ancestor_list. */
  int all_splits_completed;
  int node_not_found;
  tq_node c_root;                      /* Root iterator. */
  tq_node c_node;                      /* Node iterator. */
  tq_node c_split;                     /* Current split to check. */
  TREENODE c_split_sibling;            /* Current sibling to verify. */
  tree_queue false_list;               /* List of false clauses. */
  tree_queue * false_ancestor_list;    /* Ancestor lists for false clauses. */
  tree_queue distinguished_false_list; /* Distinguished false ancestor list. */
  tree_queue split_clause_list;        /* All split clauses in the proof. */
  tree_queue split_completion_list;   /* All splits that should be complete. */

  all_splits_completed = TRUE;
  false_list = build_root_list (root_list, head);  
  for (c_root = false_list->head, root_count = 0; c_root != NULL; 
       c_root = c_root->next) {
    root_count++;
  }
  false_ancestor_list = (tree_queue*) malloc (sizeof (tree_queue_type) * 
                                              root_count);
  for (c_root = false_list->head, root_count = 0; c_root != NULL; 
       c_root = c_root->next, root_count++) { 
    false_ancestor_list[root_count] = build_history_queue (c_root->the_node);
  }
  distinguished_false_list = build_distinguished_ancestor_list (head,
                                                                root_list);
  if (distinguished_false_list == NULL) {
    printf ("%% ERROR: No distinguished false clause found. \n");
    return FALSE;
  }
  split_completion_list = new_tree_queue ();
  for (c_node = distinguished_false_list->head; c_node != NULL;
       c_node = c_node->next) {
    if (is_split_clause (c_node->the_node->AnnotatedFormula) == TRUE) {
      add_tq_node (&split_completion_list, c_node->the_node);
    }
  }
  split_clause_list = build_split_clause_list (head, root_list);
  for (c_split = split_completion_list->head; c_split != NULL;
       c_split = c_split->next) { 
    c_split_sibling = get_split_sibling_from_list (c_split, 
                                                   split_clause_list);
    if (c_split_sibling == NULL) { 
      printf ("%% Split sibling of \n");
      PrintAnnotatedTSTPNode (stdout, c_split->the_node->AnnotatedFormula, 
                              tptp, 1);
      printf ("was not found but is required in the proof. \n");
      all_splits_completed = FALSE;
      break;
    }
    node_not_found = TRUE;
    for (c_root_number = 0; c_root_number < root_count; c_root_number++) {
      if (node_in_queue (c_split_sibling, 
                         false_ancestor_list[c_root_number]) != NULL) {
        node_not_found = FALSE;
        break;
      }
    }
    if (node_not_found == TRUE) {
      all_splits_completed = FALSE;
      break;
    }
  }
  clear_tree_queue (&false_list);
  clear_tree_queue (&distinguished_false_list);
  clear_tree_queue (&split_clause_list);
  clear_tree_queue (&split_completion_list);
  for (c_root_number = 0; c_root_number < root_count; c_root_number++)
    clear_tree_queue (&(false_ancestor_list[c_root_number]));
  free (false_ancestor_list);

  return all_splits_completed;
}
//-----------------------------------------------------------------------------
TREENODE
get_split_sibling_from_list (tq_node the_node, tree_queue the_list)
{ /* If a clause with position *l and parent $ is given, return the
   * TREENODE in the_list that has parent $ and position *r, and
   * vice versa if *r is given. 
   * the_list is the tree queue of every split clause in the proof. */
  tq_node node_iterator;     
  String position;           /* {l,r}* argument for the_node. */
  String itr_position;       /* {l,r}* argument for node_iterator. */
  TREENODE sibling;          /* Sibling for the_node. */
  int p_char_count;          /* character count for position. */

  assert (is_split_clause (the_node->the_node->AnnotatedFormula) == TRUE);
  sibling = NULL;
  get_split_info (the_node->the_node->AnnotatedFormula, position);
  p_char_count = strlen (position);
  for (node_iterator = the_list->head; node_iterator != NULL;
       node_iterator = node_iterator->next) {
    if (is_split_clause (node_iterator->the_node->AnnotatedFormula) == TRUE &&
        is_antikid (node_iterator->the_node->AnnotatedFormula) == FALSE) {
      get_split_info (node_iterator->the_node->AnnotatedFormula, itr_position);
      if (strlen (itr_position) == p_char_count &&            
          strncmp (position, itr_position, p_char_count - 1) == 0 &&
          position[p_char_count-1] != itr_position[p_char_count-1]) {
        sibling = node_iterator->the_node;
        break;
      }
    }
  }
  return sibling;
}
//-----------------------------------------------------------------------------
tree_queue 
build_split_clause_list (LISTNODE head, ROOTLIST root_list)
{ /* Builds the list of all split clauses in the proof. */
  tree_queue split_clause_list;
  LISTNODE list_iterator;          
  TREENODE *split_node;
  String split_name;

  split_clause_list = new_tree_queue ();
  for (list_iterator = head; list_iterator != NULL;
       list_iterator = list_iterator->Next) {
    if (is_split_clause (list_iterator->AnnotatedFormula) == TRUE) {
      GetName (list_iterator->AnnotatedFormula, split_name);
      split_node = GetNodeFromRootListByAnnotatedFormulaName (root_list, 
                                                              split_name);
      add_tq_node (&split_clause_list, *split_node);
    }
  }
  return split_clause_list;
}
//-----------------------------------------------------------------------------
int
is_split_clause (ANNOTATEDFORMULA the_formula)
{ /* Returns TRUE if it's a split clause. */
  String inference_info_term;
  if (GetInferenceInfoTerm (the_formula, "status", inference_info_term) == 
      NULL) {
    strcpy (inference_info_term,"unknown");
  }
  if (strcmp (inference_info_term, "status(split)") == 0) 
    return TRUE;
  else
    return FALSE;
}
//-----------------------------------------------------------------------------
int has_child_node (ANNOTATEDFORMULA f, LISTNODE list)
{
  LISTNODE i;
  for (i = list; i != NULL; i = i->Next)
    if (is_child_of(i->AnnotatedFormula, f) == TRUE)
      return TRUE;  
  return FALSE;
}
//-----------------------------------------------------------------------------
int is_child_of (ANNOTATEDFORMULA f, ANNOTATEDFORMULA parent)
{
  String p_names, parent_name;
  char *names_buff;

  GetName(parent, parent_name);
  GetParentNames (f, p_names);
  names_buff = strtok (p_names, "\n");    
  while (names_buff != NULL) {    
    if (strcmp(names_buff, parent_name) == 0)
      return TRUE;
    names_buff = strtok (NULL, "\n");
  }
  return FALSE;
}
//-----------------------------------------------------------------------------
tree_queue
build_distinguished_ancestor_list (LISTNODE head, ROOTLIST root_list)
{ /* Builds the ancestor list for the distinguished false clause.
   * Follows false clauses but not antikids. 
   * Returns NULL if there is no distinguished false. */
  LISTNODE distinguished_false;
  tree_queue ancestor_list;
  tq_node queue_iterator;
  int parent;
  String df_name;           /* Distinguished false name. */
  TREENODE *df_node;         /* Distinguished false tree node. */

  if (root_list == NULL || head == NULL)
    return NULL;
  for (distinguished_false = head; distinguished_false != NULL;
       distinguished_false = distinguished_false->Next) {
    if (is_false_clause(distinguished_false->AnnotatedFormula) == TRUE &&
        has_child_node(distinguished_false->AnnotatedFormula, head) == FALSE)
      break;
  }
  if (distinguished_false == NULL) {
    printf ("%% Structure Fault Detected - no distinguished false found. \n");
    return NULL;
  }

  ancestor_list = new_tree_queue ();
  GetName (distinguished_false->AnnotatedFormula, df_name);
  df_node = GetNodeFromRootListByAnnotatedFormulaName (root_list, df_name);
  add_tq_node (&ancestor_list, *df_node);
  for (queue_iterator = ancestor_list->head; queue_iterator != NULL;
      queue_iterator = queue_iterator->next) {
    for (parent = 0; parent < queue_iterator->the_node->NumberOfParents;
         parent++) { 
      if (is_antikid ((queue_iterator->the_node->Parents[parent])->
                      AnnotatedFormula) == FALSE) {
        add_tq_node (&ancestor_list, queue_iterator->the_node->
                     Parents[parent]);
      }
    }
  }
  return ancestor_list;
}
//-----------------------------------------------------------------------------

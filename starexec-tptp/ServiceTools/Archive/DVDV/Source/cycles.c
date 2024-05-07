/*----------------------------------------------------------------------------
 * FILE: cycles.h
 * AUTHOR: Diego Belfiore
 *
 * Defines functions that are used for checking for cycles in proof trees.
 *--------------------------------------------------------------------------*/
#include "dvdv.h"

int 
cyclic_node (TREENODE the_node)
{ /* Checks if the node is its own parent. */
  int parent;
  int parent_of_itself;
  tq_node c_node;
  tree_queue the_queue;

  parent_of_itself = FALSE;
  the_queue = new_tree_queue ();
  add_tq_node (&the_queue, the_node);
  for (c_node = the_queue->head; c_node != NULL;
       c_node = c_node->next)
    {
      for (parent = 0; parent < c_node->the_node->NumberOfParents; parent++)
        { 
          if (the_node == c_node->the_node->Parents[parent]) 
            { /* the_node is a parent of itself. */
              parent_of_itself = TRUE;
              break;
            }
          add_tq_node (&the_queue, c_node->the_node->Parents[parent]); 
        }
    }
  clear_tree_queue (&the_queue);
  return parent_of_itself;
}
//-----------------------------------------------------------------------------
int
cycle_found (TREENODE false_clause)
{ /* Checks for cycles in the graph by traversing it beginning at
   * false_clause and checking for repeated ancestors.  */  
  int parent;
  int cycle_in_graph;
  tree_queue the_queue;
  tq_node c_node;

  cycle_in_graph = FALSE;
  the_queue = new_tree_queue ();
  add_tq_node (&the_queue, false_clause);
  for (c_node = the_queue->head; c_node != NULL;
       c_node = c_node->next)
    {
      for (parent = 0; parent < c_node->the_node->NumberOfParents; parent++)
        { 
          if (node_in_queue (c_node->the_node->Parents[parent], the_queue) 
              != NULL) 
            { /* Node is already in queue, so there may be a cycle here. */
              if (cyclic_node (c_node->the_node->Parents[parent]) == TRUE) 
                { /* Cycle found. */
                  cycle_in_graph = TRUE;
                  printf ("%% Cycle found in proof tree: the following node"
                          " is a parent of itself: \n");
                  PrintAnnotatedTSTPNode (stdout, c_node->the_node->
                                          AnnotatedFormula, tptp, 1);
                  printf ("\n");
                  break;
                }
            }
          add_tq_node (&the_queue, c_node->the_node->Parents[parent]);
        }
    }
  clear_tree_queue (&the_queue);
  return cycle_in_graph;
}
//-----------------------------------------------------------------------------
int
cyclic_graph_error (tree_queue false_list)
{ /* Checks for cycles in the graph by traversing the graph starting at
   * each false clause. Takes a list of every false clause in the proof.
   * Returns TRUE if a cycle is found, FALSE otherwise. */
  tq_node c_false;         /* Proof forest iterator. */
  int cycle_exists;       /* TRUE if there's a structure fault. */

  cycle_exists = FALSE;
  for (c_false = false_list->head; c_false != NULL; c_false = c_false->next)
    {
      cycle_exists = cycle_found (c_false->the_node);
      if (cycle_exists == TRUE) {
        break;
      }
    }
  return cycle_exists;
}
//-----------------------------------------------------------------------------

/*----------------------------------------------------------------------------
 * FILE: structure_check.h
 * AUTHOR: Diego Belfiore
 *
 * These functions are used to perform structural verification.
 *--------------------------------------------------------------------------*/
#ifndef __STRUCTURE_CHECK_H__
#define __STRUCTURE_CHECK_H__

tree_queue       build_history_queue       (TREENODE the_node);
void             get_split_info            (ANNOTATEDFORMULA the_formula,
                                            String put_info_here);
int
is_antikid (ANNOTATEDFORMULA the_formula);

int
is_false_clause (ANNOTATEDFORMULA the_formula);

int has_child_node (ANNOTATEDFORMULA f, LISTNODE list);

int is_child_of (ANNOTATEDFORMULA f, ANNOTATEDFORMULA parent);

void
build_history_string (tree_queue the_queue,
		      String put_history_here);

int
verify_history_string (char *history);

tree_queue
build_root_list (ROOTLIST root_list, LISTNODE head);

tree_queue
find_roots (ROOTLIST root_list, LISTNODE false_root);

int
starL_starR_failure (TREENODE false_clause);

int
verify_starL_starR (tree_queue false_list);

tq_node 
node_in_queue (TREENODE the_node, tree_queue the_queue);

int
verify_split_completion (LISTNODE head, ROOTLIST root_list);

TREENODE
get_split_sibling_from_list (tq_node the_node, tree_queue the_list);

tree_queue 
build_split_clause_list (LISTNODE head, ROOTLIST root_list);

int
is_split_clause (ANNOTATEDFORMULA the_formula);

tree_queue
build_distinguished_ancestor_list (LISTNODE head, ROOTLIST root_list);

int
cycle_found (TREENODE false_clause);

int
cyclic_graph_error (tree_queue false_list);

#endif

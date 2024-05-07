/*----------------------------------------------------------------------------
 * FILE: data_structures.c
 * AUTHOR: Diego Belfiore
 *
 * Defines all data structure functions.
 *--------------------------------------------------------------------------*/
#include "dvdv.h"

//----------------------------------TREE QUEUE---------------------------------
inline tree_queue
new_tree_queue (void)
{
  tree_queue new_queue;

  new_queue = (tree_queue) malloc (sizeof (tree_queue_type));
  new_queue->head = NULL;
  new_queue->tail = NULL;
  return new_queue;
}
//-----------------------------------------------------------------------------
inline void
print_queue (tree_queue the_queue)
{
  tq_node i;

  for (i = the_queue->head; i != NULL; i = i->next)
    PrintAnnotatedTSTPNode (stdout, i->the_node->AnnotatedFormula, tptp, 1);
}
//-----------------------------------------------------------------------------
int 
add_tq_node (tree_queue *the_queue,
	     TREENODE tree_node)
{ /* returns 1 if the node is added to the queue and 
   * 0 if the node has already been visited and added to the list. */
  tq_node new_node;
  StatusType node_status;

  /* Don't add the node if it's already in the queue. */
  if (node_in_queue (tree_node, *the_queue) != NULL) {
    return 0;
  }
  node_status = GetStatus (tree_node->AnnotatedFormula, NULL);
  if (node_status != derived) 
    return 0;
  new_node = (tq_node) malloc (sizeof (tree_queue_node_type));
  assert (new_node != NULL);
  new_node->the_node = tree_node;
  new_node->next = NULL;
  if ((*the_queue)->head == NULL) 
    {
      (*the_queue)->head = new_node;
      (*the_queue)->tail = new_node;
    }
  else 
    {
      (*the_queue)->tail->next = new_node;
      (*the_queue)->tail = (*the_queue)->tail->next;
    }
  return 1;
}
//-----------------------------------------------------------------------------
inline void
clear_tree_queue (tree_queue *the_queue)
{ /* Sets Visited to 0 on all nodes and clears queue. */
  tq_node node_iterator;
  tq_node deleted_node;

  for (node_iterator = (*the_queue)->head; node_iterator != NULL;
       /* Taken care of in loop. */)
    {
      node_iterator->the_node->Visited = 0;
      deleted_node = node_iterator;
      node_iterator = node_iterator->next;
      free (deleted_node);
    }
  free (*the_queue);
}
//--------------------------------ARGUMENTLIST---------------------------------
ARGUMENTLIST NewArgumentList (void) 
{
  ARGUMENTLIST argList;
  String hostname;
  int process_id;

  printf("%% Creating new argument list... \n");
  argList = (ARGUMENTLIST) malloc(sizeof(ArgumentListType));
  assert (argList != NULL);
  argList->forceContinue = FALSE;
  argList->verbose = FALSE;
  argList->verifyInitials = FALSE;
  argList->keepFiles = FALSE;
  argList->checkParentRelevance = FALSE;
  strcpy (argList->theoremProver, DEFAULT_ATP_SYSTEM);
  strcpy (argList->modelChecker, DEFAULT_MODEL_CHECKER);
  strcpy (argList->timeLimit, DEFAULT_SYSTEM_TIME);
  strcpy (argList->proofFileName, "");
  strcpy (argList->initialsFileName, "");
  strcpy(argList->keptFilesDir, "");
  gethostname(hostname, KBYTE);
  process_id = (int) getpid ();
  sprintf (argList->baseDirectory,"%s/%s_%d", DVDV_FILES_DIRECTORY, 
           hostname, process_id);
  sprintf (argList->host_pid_name, "%s_%d", hostname, process_id);
  (argList->input_problem_sets.P = argList->input_problem_sets.N = 
   argList->input_problem_sets.Mixed = NULL);
  return argList;
}
//---------------------------------SPLIT STACK---------------------------------
StackNode 
NewStackNode(ANNOTATEDFORMULA anfBuffer) 
{
  StackNode node;

  node = (StackNode) malloc(sizeof(StackNodeType));  
  node->theFormula = anfBuffer;
  node->previousNode = NULL;
  return node;
}
//-----------------------------------------------------------------------------
void 
Push(STACK *stackHead, ANNOTATEDFORMULA anfBuffer) 
{
  StackNode newNode;
  
  newNode = NewStackNode(anfBuffer);
  if (*stackHead == NULL) {
    *stackHead = newNode;
  }
  else {
    newNode->previousNode = *stackHead;
    *stackHead = newNode;
  }
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA 
Pop(STACK *stackHead) 
{
  ANNOTATEDFORMULA anfBuffer;
  StackNode head;

  if (*stackHead == NULL) {
    return NULL;
  }
  else {
    anfBuffer = (*stackHead)->theFormula;
    head = *stackHead;
    *stackHead = (*stackHead)->previousNode;
    free(head);
    return anfBuffer;
  }
}
//-----------------------------------------------------------------------------
void 
PrintStack(STACK stackHead, int verbose) 
{
  StackNode stackIterator;
  if (stackHead == NULL) {
    return;
  }
  for (stackIterator = stackHead; 
       stackIterator != NULL;
       stackIterator = stackIterator->previousNode) {
    if (verbose != 0)
      PrintAnnotatedTSTPNode(stdout, stackIterator->theFormula, tptp, 1);
  }
}
//-----------------------------------------------------------------------------
SPLITPARENTLIST 
NewSplitParentList() 
{
  SPLITPARENTLIST list;
  list = (SPLITPARENTLIST) malloc(sizeof(SplitParentListType));
  strcpy(list->FalseClause, "");
  strcpy(list->Parent, "");
  strcpy(list->AntiKidOf, "");
  return list;
}
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * FILE: data_structures.h
 * AUTHOR: Diego Belfiore
 *
 * Includes every important header file from the C Standard Library and 
 * any data structures used in the dvdv verifier.
 *---------------------------------------------------------------------------*/
#ifndef __DVDV_DATA_STRUCTURES_H__
#define __DVDV_DATA_STRUCTURES_H__
/*-----------------------------------------------------------------------------
 * STANDARD LIBRARIES
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>

#include "JJParser/DataTypes.h"
#include "JJParser/Compare.h"
#include "JJParser/Utilities.h"
#include "JJParser/Parsing.h"
#include "JJParser/Tokenizer.h"
#include "JJParser/List.h"
#include "JJParser/Tree.h"
#include "JJParser/ParseTPTP.h"
#include "JJParser/Signature.h"
#include "JJParser/PrintTSTP.h"
#include "JJParser/Examine.h"
#include "JJParser/ListStatistics.h"
#include "JJParser/Modify.h"
#include "JJParser/ParseTSTP.h"
#include "JJParser/Statistics.h"
#include "JJParser/TreeStatistics.h"
/*-----------------------------------------------------------------------------
 * MACRO DEFINITIONS
 *---------------------------------------------------------------------------*/
#define KBYTE 1024
#define TRUE 1
#define UNDEFINED 0
#define FALSE -1
#define ERROR -2

/* System exit statuses. */
#define SUCCESS 1                   
#define FAILURE 0
#define NO_PROOF_FOUND 3
#define INCOMPLETE 4
#define INPUT_FAILURE 5
#define STRUCTURAL_FAILURE 7
#define INITIAL_FILE_FAILURE 8
#define SEMANTIC_FAILURE 10
#define SYSTEMONTPTP_FAILURE 11
#define TPTP2X_FAILURE 12
#define NO_FAILURE 13

#define SEMANTIC_MODEL_CHECK 10
#define SAT_MODEL_CHECK 11     
#define GENERAL_SAT_CHECK 12
#define GENERAL_UNSAT_CHECK 13

#define SYSTEMONTPTP_PATH "/home/graph/tptp/SystemExecution/SystemOnTPTP"
#define TPTP2X_PATH "/home/graph/tptp/TPTP/TPTP2X/tptp2X"
#define TPTP_LIBRARY_PATH "/home/graph/tptp/TPTP/Problems"
#define DVDV_FILES_DIRECTORY "/tmp"

#define OTTER "Otter---3.3"
#define SPASS "SPASS---2.1"
#define VAMPIRE "Vampire---6.0"
#define E_PROVER "E---0.8"
#define PARADOX "Paradox---1.1"

/* Default arguments. */
#define DEFAULT_SYSTEM_TIME "60"
#define DEFAULT_ATP_SYSTEM "Otter---3.3"
#define DEFAULT_MODEL_CHECKER "Paradox---1.0"

#define TPTP2X_RUN_ERROR "tptp2X did not create all the"
#define ATP_NOT_AVAILABLE_ERROR "is not listed or is multiply defined"

#define END_PROOF_LINE "ORIGINAL SYSTEM OUTPUT" 
/*-----------------------------------------------------------------------------
 * DATA STRUCTURES
 *---------------------------------------------------------------------------*/
typedef short BOOLEAN;

typedef struct {
  LISTNODE P;
  LISTNODE N;
  LISTNODE Mixed;
} INPUT_PROBLEM_SETS;

typedef struct ArgumentListTag {
  BOOLEAN forceContinue;
  BOOLEAN verbose;
  BOOLEAN verifyInitials;
  BOOLEAN keepFiles;
  BOOLEAN checkParentRelevance;
  String theoremProver;
  String modelChecker;
  String timeLimit;
  String proofFileName;
  String initialsFileName;
  String baseDirectory;
  String keptFilesDir;
  String host_pid_name;
  INPUT_PROBLEM_SETS input_problem_sets;
} ArgumentListType;

typedef ArgumentListType* ARGUMENTLIST;

typedef struct StackNodeTag {
  ANNOTATEDFORMULA theFormula;
  struct StackNodeTag *previousNode;
} StackNodeType;

typedef StackNodeType * StackNode;
typedef StackNode STACK;

typedef enum {
  LeftChild, 
  RightChild,
  AntiKid,
  Undefined
} SplitType;

typedef struct {
  String FalseClause;
  String Parent;
  String AntiKidOf;
} SplitParentListType;

typedef SplitParentListType * SPLITPARENTLIST;

typedef struct tree_queue_node_tag {
  TREENODE the_node;
  struct tree_queue_node_tag * next;
} tree_queue_node_type;

typedef tree_queue_node_type * tq_node;

typedef struct {
  tq_node head;
  tq_node tail;
} tree_queue_type;

typedef tree_queue_type * tree_queue;

/*-----------------------------------------------------------------------------
 * DATA STRUCTURE FUNCTIONS
 *---------------------------------------------------------------------------*/
ARGUMENTLIST NewArgumentList (void);
/*-----------------------------------------------------------------------------
 * TREE QUEUE FUNCTIONS
 *---------------------------------------------------------------------------*/
inline tree_queue new_tree_queue (void);

int add_tq_node (tree_queue *the_queue, TREENODE new_node);

inline void clear_tree_queue (tree_queue *the_queue);

inline void print_queue (tree_queue the_queue);
/*-----------------------------------------------------------------------------
 * SPLIT STACK FUNCTIONS
 *---------------------------------------------------------------------------*/
void Push (STACK *stackHead, 
	   ANNOTATEDFORMULA anfBuffer);

ANNOTATEDFORMULA Pop (STACK *stackHead);

void PrintStack (STACK stackHead, 
		 int verbose);

SPLITPARENTLIST NewSplitParentList (void);

StackNode NewStackNode (ANNOTATEDFORMULA anfBuffer);
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------

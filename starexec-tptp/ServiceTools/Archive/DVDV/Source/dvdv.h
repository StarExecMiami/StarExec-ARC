/*-----------------------------------------------------------------------------
 * FILE: dvdv.h
 * AUTHOR: Diego Belfiore
 *
 * Includes function signatures for all functions needed to run the 
 * dvdvX verifier. Structural verification function signatures are
 * included in file StructureCheck.h.
 *---------------------------------------------------------------------------*/
#ifndef __DVDV_H__
#define __DVDV_H__
//-----------------------------------------------------------------------------
#include "data_structures.h"
#include "structure_check.h"
//-----------------------------------------------------------------------------
/* Set to TRUE when the program receives an interrupt signal.*/
int Global_Interrupted; 

/* System-wide error flag. */
int Global_Error_Flag;
//-----------------------------------------------------------------------------
BOOLEAN ProcessArguments (int argc, 
			  char *argv[], 
			  ARGUMENTLIST argList);

BOOLEAN ValidateArguments (ARGUMENTLIST argList);

void create_input_set_lists (INPUT_PROBLEM_SETS *sets,
                             char *problem_file, 
                             SIGNATURE *split_sig);

void CreateDirectoryStructure (ARGUMENTLIST argList);

void ClearDirectoryStructure (ARGUMENTLIST argList, 
			      int failedObligations, 
			      BOOLEAN success);

int grep_file (char *filename, 
	       char *subsection, 
	       char *response, 
	       BOOLEAN printResponse);

void GetNodeAxiomSet (ANNOTATEDFORMULA node, 
		      String putNamesHere);

int RunSystemOnTPTP (ARGUMENTLIST argList, 
		     char *formulaName, 
		     char *oblFileName, 
		     int type,
		     int checkModel);

int run_systems (ARGUMENTLIST argList, 
                 char *formula_name, 
                 char *obl_fname);

int verify_node (LISTNODE axiomSet, 
		 LISTNODE *conjectureNode, 
		 STACK *split_stack,
		 ARGUMENTLIST argList,
		 SIGNATURE signature);

int geoff_esplit_check (LISTNODE axiom_set,
                        LISTNODE *first_split,
                        ARGUMENTLIST arg_list,
                        SIGNATURE signature);

char * GetTPTPProblemFilePath (ANNOTATEDFORMULA anfBuffer);

char * GetTPTPProblemName (char *path);

void ConvertTPTPToTSTP (ARGUMENTLIST arg_list,
                        char *tptpFileName, 
			char *parsedFilePath);

/*-----------------------------------------------------------------------------
 * Signal handlers.
 *---------------------------------------------------------------------------*/
void force_exit (int theSignal);

void SIGINT_Handler (int theSignal);

void SIGQUIT_Handler (int theSignal);

void SIGHUP_Handler (int theSignal);

void SIGTERM_Handler (int theSignal);

void SIGABRT_Handler (int theSignal);

/*-----------------------------------------------------------------------------
 * Secure System Calls.
 *---------------------------------------------------------------------------*/
inline FILE * s_popen (const char *command, 
		       const char *type);

inline int s_pclose (FILE *stream);

inline FILE * s_fopen (const char *path,
		       const char *mode);

inline int s_fclose (FILE *stream);

/*-----------------------------------------------------------------------------
 * Split Verification functions
 *---------------------------------------------------------------------------*/

SplitType GetSplitType (ANNOTATEDFORMULA anfBuffer);

SPLITPARENTLIST GetSplitParentList (ANNOTATEDFORMULA anfBuffer, 
				    SplitType type);

int GetSplitLevel (ANNOTATEDFORMULA theFormula);
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------

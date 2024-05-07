/*-----------------------------------------------------------------------------
 *
 * FILE: dvdv.c
 * AUTHOR: Diego Belfiore
 *
 * USAGE: Executable DVDV ATP Verifier. System checks the proof written 
 *        by an ATP system by taking apaprt the proof presented, and running 
 *        each individual component through SystemOnTPTP using the indicated
 *	  ATP system. System uses the JJParser to parse the proof file and 
 *	  build obligation files for each line of the proof.
 *
 *---------------------------------------------------------------------------*/
#include "dvdv.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio_ext.h>
//-----------------------------------------------------------------------------
int main (int argc, char *argv[]) 
{  
  int failedObligations;
  int nodeProven;                     /* Rejected obligation count */         
  extern int Global_Interrupted;
  String tptpProblemFilePath;         /* Used to extract TPTP problem file */
  String parsedTPTPProblemFile;
  ARGUMENTLIST argList;               /* Holds all arguments and options */
  STACK splitStack;  
  LISTNODE listHead;                  /* Pointer to the list head */
  LISTNODE list_index;                /* List iterator */
  SIGNATURE signature;                /* Holds functors, predicates, ... */
  SIGNATURE splitSignature;           /* Signature used for problem split */
  ANNOTATEDFORMULA anfBuffer;         /* Current formula */ 
  ROOTLIST jj_root_list;              /* ROOTLIST from JJParser */
  tree_queue false_list;
  StatusType status, substatus;

  signal(SIGINT, SIGINT_Handler);
  signal(SIGQUIT, SIGQUIT_Handler);
  signal(SIGHUP, SIGHUP_Handler);
  signal(SIGTERM, SIGTERM_Handler);
  signal(SIGABRT, SIGABRT_Handler);

  anfBuffer = NULL;
  system ("clear");
  argList = NewArgumentList ();
  if (ProcessArguments (argc, argv, argList) == FALSE) {
    printf ("\n%% Incorrect system parameters set. \n");
    ClearDirectoryStructure (argList, -1, INPUT_FAILURE);
    printf ("%% Exiting system... \n");
    free (argList);
    return EXIT_FAILURE;
  }

  Global_Interrupted = FALSE;
  Global_Error_Flag = NO_FAILURE;
  printf ("%% Beginning proof check using theorem prover %s, \n"
	  "%% and %s for model verification... \n",
	  argList->theoremProver, argList->modelChecker);
  failedObligations = 0;
  signature = NewSignature ();
  splitSignature = NewSignature ();
  splitStack = NULL;
  SetNeedForNonLogicTokens (0);
  CreateDirectoryStructure (argList);
  printf ("%% Parsing proof file %s into list... \n", argList->proofFileName);
  listHead = ParseFileOfFormulae (argList->proofFileName, signature, 1, NULL);
  printf ("%% Converting to First Order Form...\n");  
  for (list_index = listHead; 
       list_index != NULL; 
       list_index = list_index->Next) {              
    UniversalFOFify(list_index->AnnotatedFormula);
  }
  /* Perform structural verification. */
  jj_root_list = BuildRootList (listHead);
  if (jj_root_list == NULL) {
    printf ("%% No proof found. \n");
    printf("%% Exiting system... \n");
    ClearDirectoryStructure(argList, -1, NO_PROOF_FOUND);
    free(argList);
    return -1;
  }
  printf ("%% Performing structural verification... \n");  
  false_list = build_root_list (jj_root_list, listHead);
  if (cyclic_graph_error (false_list) == TRUE) {
    printf ("%% Structural failure occurred: a cycle was found in the proof"
            "   tree. \n");
    printf("%% Exiting system... \n");
    ClearDirectoryStructure(argList, -1, STRUCTURAL_FAILURE);
    free(argList);
    return -1;
  } else {
    printf ("%% No cycles were found in the proof tree. \n");
  }
  printf ("%% Performing structural verification on split siblings... \n");
  if (verify_starL_starR (false_list) == TRUE) {
    printf ("%% Sibling verification completed successfully. \n");  
  } else {
    printf ("%% Structural failure detected. \n");
    printf("%% Exiting system... \n");
    ClearDirectoryStructure(argList, -1, STRUCTURAL_FAILURE);
    free(argList);
    return EXIT_FAILURE;
  }  
  printf ("%% Verifying split completion... \n");
  if (verify_split_completion (listHead, jj_root_list) == FALSE) {
    printf ("%% Structural failure detected. \n");
    printf("%% Exiting system... \n");
    ClearDirectoryStructure(argList, -1, STRUCTURAL_FAILURE);
    free(argList);
    return EXIT_FAILURE;
  } else {
    printf ("%% Split completion verification returned no errors. \n");
  }
  /* Verify "initial" nodes. */
  if (argList->verifyInitials == TRUE) {
    if (strcmp (argList->initialsFileName, "") == 0) {
      printf("%% Extracting problem from TPTP library... \n");
      for(list_index = listHead; list_index != NULL;
          list_index = list_index->Next) {

        status = GetStatus (list_index->AnnotatedFormula, &substatus);
        if (status != derived && substatus != derived)
          break;
      }

      anfBuffer = list_index->AnnotatedFormula;
      strcpy (tptpProblemFilePath, GetTPTPProblemFilePath(anfBuffer));      
    } else {
      strcpy (tptpProblemFilePath, argList->initialsFileName);
    }

    if (access(tptpProblemFilePath, R_OK) != 0) {
      printf("%% ERROR: The initials file provided:\n\t%s\n", 
             tptpProblemFilePath);
      printf("%% does not exist or is not accessible. Please check file \n"
             "%% permissions and try again. \n");
      ClearDirectoryStructure(argList, -1, INPUT_FAILURE);
      printf("%% Exiting system... \n");
      free(argList);
      return EXIT_FAILURE;
    }
    printf ("%% Parsing initials file %s into list... \n",
            tptpProblemFilePath);

    sprintf (parsedTPTPProblemFile, "%s/Initial/%s", 
             argList->baseDirectory, 
             GetTPTPProblemName(GetTPTPProblemFilePath(anfBuffer)));
    ConvertTPTPToTSTP (argList, tptpProblemFilePath, parsedTPTPProblemFile);
    printf ("%% Splitting problem file %s into satisfiable sets... \n", 
	    tptpProblemFilePath);
    create_input_set_lists (&(argList->input_problem_sets),
                            parsedTPTPProblemFile, &splitSignature);    
  }  
  printf("%% Checking obligation files...\n\n");
  for (list_index = listHead;
       list_index != NULL && Global_Interrupted == FALSE;
       list_index = list_index->Next) {    
    nodeProven = verify_node (listHead, &list_index, &splitStack, 
                              argList, signature);
    if (nodeProven == FALSE || nodeProven == FAILURE) {
      if (argList->forceContinue == FALSE) {
	printf ("\n");
	++failedObligations;
	break;
      }
      failedObligations++;
    }
  }
  if (splitStack != NULL) {
    printf("\n\n%% Some split elements may not have been accounted for. \n");
    printf("%% The following elements remain unaccounted for: \n");
    PrintStack(splitStack, 0);
  }
  
/*-----------------------------------------------------------------------------
 * Close all connections and free memory
 *---------------------------------------------------------------------------*/

  if (Global_Interrupted == FALSE) 
    printf("\n%% Proof Check Complete. \n");  
  printf("%% Clearing annotated list structures... \n");
  FreeListOfAnnotatedFormulae(&listHead);
  ClearDirectoryStructure(argList, failedObligations, SUCCESS);
  free(argList);

  fflush(stdout);
  fclose(stdout);  
  _exit (0);
}

/*-----------------------------------------------------------------------------
 * FILE: dvdvIIutils.c
 * AUTHOR: Diego Belfiore
 *
 * General-purpose utility functions.
 *---------------------------------------------------------------------------*/
#include "dvdv.h"
//-----------------------------------------------------------------------------
void parse_stdin_proof_file (ARGUMENTLIST arg_list);
char * ParseProofFile (char *filename);
void add_node_to_list (LISTNODE *list, LISTNODE item);
//-----------------------------------------------------------------------------
BOOLEAN ProcessArguments (int argc, 
                          char *argv[], 
                          ARGUMENTLIST argList) 
{
  int option;
  String unixCommand;

  assert (argList != NULL);
  printf ("%% Validating command-line arguments... \n");
  while ((option = getopt (argc, argv, "fvik:rhu:s:t:x:p:")) != -1)
    {
      switch (option) 
	{
	case 'f':
	  argList->forceContinue = TRUE;
	  break;
	case 'v':
	  argList->verbose = TRUE;
	  break;
	case 'i':
	  argList->verifyInitials = TRUE;
	  break;
	case 'k':
	  argList->keepFiles = TRUE;
          strcpy(argList->keptFilesDir, optarg);
	  break;
	case 'r':
	  argList->checkParentRelevance = TRUE;
	  break;
	case 'h':
	  system ("cat HELP");    
	  exit (EXIT_SUCCESS);
	  break;
	case 'u':
	  strcpy (argList->theoremProver, optarg);
	  break;
	case 's':
	  strcpy (argList->modelChecker, optarg);
	  break;
	case 't':
	  strcpy (argList->timeLimit, optarg);
	  break;
	case 'x':
	  strcpy (argList->initialsFileName, optarg);
	  break;
	case 'p':
	  strcpy (argList->proofFileName, optarg);
	  break;
	case '?':
	  printf ("Unknown option %c. \n", option);
	  exit (EXIT_FAILURE);
	  break;
	default:
	  printf ("Unknown error occurred with arguments passed. \n");
	  exit (EXIT_FAILURE);
	}
    }
  sprintf (unixCommand, "mkdir %s", argList->baseDirectory);
  system (unixCommand);
  if (strcmp (argList->proofFileName, "") == 0)
    parse_stdin_proof_file (argList);
  return ValidateArguments (argList);
}
//-----------------------------------------------------------------------------
inline FILE *s_popen (const char *command, const char *type)
{
  FILE *process;

  if ((process = popen (command, type)) == NULL) {
    perror ("popen");
    exit (EXIT_FAILURE);
  } else {
    return process;
  }
}
//-----------------------------------------------------------------------------
inline int s_pclose (FILE *stream)
{
  int status;

  if ((status = pclose (stream)) == -1) {
    perror ("pclose");
    exit (EXIT_FAILURE);
  } else {
    return status;
  }
}
//-----------------------------------------------------------------------------
inline FILE *s_fopen (const char *path, const char *mode)
{
  FILE *fp;

  if ((fp = fopen (path, mode)) == NULL) {
    perror ("fopen");
    exit (EXIT_FAILURE);
  } else {
    return fp;
  }
}
//-----------------------------------------------------------------------------
inline int s_fclose (FILE *stream)
{
  int status;

  if (fflush (stream) == EOF) {
    perror ("fflush");
  }
  if ((status = fclose (stream)) == EOF) {
    perror ("fclose");
    exit (EXIT_FAILURE);
  } else {
    return status;
  }
}
//-----------------------------------------------------------------------------
BOOLEAN ValidateArguments (ARGUMENTLIST argList) 
{ /* Does a test run with the ATP system to verify that it exists and can
   * be used.  */
  String unixCommand;
  String filename;
  BOOLEAN valid;

  if (access(argList->proofFileName, R_OK) != 0) {
    printf("%% Filename %s was found to be inaccessible. \n", 
           argList->proofFileName);
    printf("%% Please check the filename and file permissions and " 
           "try again. \n");
    return FALSE;
  }

  sprintf (unixCommand, "%s -q0 %s %s %s > %s/TEST_RUN", 
	   SYSTEMONTPTP_PATH, argList->theoremProver,
	   argList->timeLimit, argList->proofFileName,
	   argList->baseDirectory);
  system (unixCommand);
  sprintf (filename, "%s/TEST_RUN", argList->baseDirectory);  
  if (grep_file (filename, "ERROR:", NULL, TRUE) == TRUE) {
    valid = FALSE;
    if (grep_file (filename, "ERROR:", ATP_NOT_AVAILABLE_ERROR,
			     FALSE) == TRUE) { 
      printf ("%% ERROR: The %s theorem prover is either unavailable or"
              " does not exist. \n", argList->theoremProver);      
    }      
    else if (grep_file (filename, "ERROR:", TPTP2X_RUN_ERROR,
				  FALSE) == TRUE) { 
      Global_Error_Flag = TPTP2X_FAILURE;
    }
    else {   /* Unspecified system error. */
      Global_Error_Flag = SYSTEMONTPTP_FAILURE;      
    }
  }
  else {
    valid = TRUE;
  }
  sprintf (unixCommand, "rm %s", filename);
  system (unixCommand);
  
  return valid;
}
//-----------------------------------------------------------------------------
/* Creates P, N, NP, and NN set lists used for verifying initial nodes.
 * Listnodes are FOFified in the process.
 * */
void create_input_set_lists (INPUT_PROBLEM_SETS *sets,
                             char *problem_file, 
                             SIGNATURE *split_sig)
{
  int p_count;
  int n_count;
  String p_fname;
  LISTNODE i;
  LISTNODE c_node;
  LISTNODE list_head;

  sprintf (p_fname, problem_file);
  SetNeedForNonLogicTokens (0);
  list_head = ParseFileOfFormulae (p_fname, *split_sig, 1, NULL);
  p_count = n_count = 0;
  for (i = list_head; i != NULL; /* Taken care of in loop */) {
    SetStatus (i->AnnotatedFormula, axiom, nonstatus);
    CountLiteralsOfPolarity (i->AnnotatedFormula, &p_count, &n_count);
    UniversalFOFify (i->AnnotatedFormula);
    if (n_count == 0) {
      c_node = i;
      i = i->Next;
      add_node_to_list (&(sets->P), c_node);
    } else if (p_count == 0) {
      c_node = i;
      i = i->Next;
      add_node_to_list (&(sets->N), c_node);
    } else {
      c_node = i;
      i = i->Next;
      add_node_to_list (&(sets->Mixed), c_node);
    }
  }
  list_head = NULL;
}
//-----------------------------------------------------------------------------
void add_node_to_list (LISTNODE *list, LISTNODE item)
{
  LISTNODE i;

  if (*list == NULL) {
    *list = item;
    (*list)->Next = NULL;
  } else {
    for (i = *list; i->Next != NULL; i = i->Next)
      ;
    i->Next = item;
    i->Next->Next = NULL;
  }
}
//-----------------------------------------------------------------------------
void parse_stdin_proof_file (ARGUMENTLIST arg_list)
{ /* STDIN proof file is stripped of all the excess garbage
   * text that the theorem prover may add to the proof.  */
  char *parsed_file;
  String buffer;
  String filename;
  FILE *proof_file;

  printf ("%% Parsing proof file from STDIN... \n");
  sprintf (filename, "%s/ProofFile.tstp", arg_list->baseDirectory);
  strcpy (arg_list->proofFileName, filename);
  proof_file = s_fopen (filename, "w");
  while (fgets (buffer, KBYTE, stdin) != NULL) 
    {
      if ((strstr (buffer, END_PROOF_LINE)) != NULL)
	break;
      fputs (buffer, proof_file);
    }
  s_fclose (proof_file);
  parsed_file = ParseProofFile (filename);  
  parsed_file = strstr (parsed_file, "%");  
  proof_file = s_fopen (filename, "w");
  fputs (parsed_file, proof_file);
  s_fclose (proof_file);
  free (parsed_file);
}                                           
//-----------------------------------------------------------------------------
void CreateDirectoryStructure (ARGUMENTLIST argList) 
{
  String unixCommand;

  printf ("%% Creating Directory Structure... \n");
  sprintf (unixCommand, "mkdir %s/Initial", argList->baseDirectory);
  system (unixCommand);
  sprintf (unixCommand, "mkdir %s/Initial/Obligations", 
	   argList->baseDirectory);
  system (unixCommand);
  sprintf (unixCommand, "mkdir %s/Initial/Results", argList->baseDirectory);
  system (unixCommand);
  sprintf (unixCommand, "mkdir %s/Derived", argList->baseDirectory);
  system (unixCommand);
  sprintf (unixCommand, "mkdir %s/Derived/Obligations", 
	   argList->baseDirectory);
  system (unixCommand);
  sprintf (unixCommand, "mkdir %s/Derived/Results", argList->baseDirectory);
  system (unixCommand);
}
//-----------------------------------------------------------------------------
void ClearDirectoryStructure (ARGUMENTLIST  argList, 
                              int failedObligations, 
                              BOOLEAN success) 
{
  String unixCommand;
  String sendFilesTo;
  extern int Global_Interrupted;

  printf ("%% Proof verification complete. \n");
  if (failedObligations > 0) {
    printf ("%% System encountered %d files for which no proof was found.\n", 
	    failedObligations);
  } else if (failedObligations == 0) {
    printf ("%% Proof given returned no errors. \n");
  } else { 
    // DO NOTHING
  }

  if  (argList->keepFiles == TRUE && failedObligations >= 0) {
    if (argList->keptFilesDir[strlen(argList->keptFilesDir)-1] == '/') {
      sprintf(sendFilesTo, "%s%s.dvdv", argList->keptFilesDir,
              GetTPTPProblemName(argList->proofFileName));
    } else {
      sprintf(sendFilesTo, "%s/%s.dvdv", argList->keptFilesDir,
              GetTPTPProblemName(argList->proofFileName));
    }

    if (access(sendFilesTo, F_OK) == 0) {
      sprintf(unixCommand, "rm -rf %s", sendFilesTo);
      system(unixCommand);
    }
    sprintf(unixCommand, "mkdir %s", sendFilesTo);
    system(unixCommand);

    if (argList->verifyInitials == TRUE) {
      sprintf(unixCommand, "cp -r %s/Initial/Results/* %s", 
              argList->baseDirectory, sendFilesTo);
      system(unixCommand);
    }

    sprintf(unixCommand, "cp -r %s/Derived/Results/* %s", 
            argList->baseDirectory, sendFilesTo);
    system(unixCommand);

    printf("%% You can find the discharged files in %s \n",
           sendFilesTo);
  }
  printf ("%% Clearing directory structure... \n");
  sprintf (unixCommand, "rm -f -r %s", argList->baseDirectory);   
  system (unixCommand);
  
  if (Global_Interrupted == TRUE || success == INCOMPLETE) {
    printf("%% RESULT: Incomplete Verification. \n");
  }
  else {
    if (Global_Error_Flag == SEMANTIC_FAILURE) {
      printf("%% RESULT: Failure       TYPE: Semantic. \n");
    }
    else if (Global_Error_Flag == INITIAL_FILE_FAILURE) {
      printf("%% RESULT: Failure.       TYPE: Initials Input Failure. \n");
    }
    else if (success == NO_PROOF_FOUND) {
      printf("%% RESULT: No Proof Found. \n");
    }
    else if (success == STRUCTURAL_FAILURE) {
      printf("%% RESULT: Failure       TYPE: Structural. \n");
    }
    else if (success == INPUT_FAILURE) {
      printf("%% RESULT: Failure.       TYPE: Input Failure. \n");
    }
    else if (Global_Error_Flag == TPTP2X_FAILURE) {
      printf("%% RESULT: Failure.       TYPE: tptp2X System Failure. \n");
    }
    else if (Global_Error_Flag == SYSTEMONTPTP_FAILURE) {
      printf("%% RESULT: Failure.       TYPE: Unknown SystemOnTPTP Error. \n");
    }
    else if (failedObligations > 0) {
      printf("%% RESULT: Failure       TYPE: Semantic. \n");
    }
    else {
      printf("%% RESULT: Success. \n");
    }
  }
}
//-----------------------------------------------------------------------------
char *ParseProofFile (char *fname) 
{ /* Get rid of extra garbage in the proof produced. */ 
  register int buffSize;
  register int buffIndex;
  register char currentChar;
  char *file;
  FILE *fileStream;

  buffSize = KBYTE;
  buffIndex = 0;
  fileStream = s_fopen(fname, "r");
  file = (char *) malloc(KBYTE);
  assert (file != NULL);
  while ((currentChar = fgetc(fileStream)) != EOF) 
    {
      if (buffIndex == buffSize - 1) {
	buffSize *= 2;
	file = (char *) realloc(file, buffSize);
      }
      file[buffIndex++] = currentChar;
    }
  file[buffIndex] = '\0';
  s_fclose(fileStream);
  return file;
}
//-----------------------------------------------------------------------------
int grep_file (char *filename, 
	       char *subsection, 
	       char *response, 
	       BOOLEAN printResponse) 
{ /* Check for the existence of a subsection in a file, and also check
   * for the existence of a response within that subsection.
   * Main priority is the subsection, then the response.   
   * Returns > 0 if response appears in subsection
   *       0 if the subsection does not exist
   *       < 0 if subsection is present but response is not present.  */
  int verify;
  FILE *file;
  String unix_command;
  String matching_line;
  char *substring;

  if (subsection == NULL)
    return UNDEFINED;
  substring = NULL;
  sprintf (unix_command, "grep %s %s", subsection, filename);
  file = s_popen(unix_command, "r");
  fgets (matching_line, KBYTE, file);    
  if (response != NULL) 
    { /* Check for a response within a subsection */
      substring = strstr (matching_line, subsection);
      if (substring != NULL) {
	if (strstr (substring, response) != NULL) {
	  verify = TRUE;
	  if (printResponse == TRUE)
	    printf("%s \n", substring);
	}
	else
	  verify = FALSE;	
      }
      else {      
	verify = UNDEFINED;
      } 
    }  
  else {     /* Check for only a subsection */
      if (strstr(matching_line, subsection) != NULL) {
	verify = TRUE;
	if (printResponse == TRUE)
	  printf("%s \n", substring);
      }
      else 
	verify = FALSE;
    }  
  s_pclose (file);
  return verify;
}
//-----------------------------------------------------------------------------
void GetNodeAxiomSet (ANNOTATEDFORMULA node, 
		      String putNamesHere) 
{ /* Places node set in set notation into the string. */
  int charCount;
  char *namesBuffer;
  String parentNames;  

  sprintf(putNamesHere, "{ ");
  charCount = 2;

  if (GetParentNames(node, parentNames) != NULL) {
    namesBuffer = strtok(parentNames, "\n");
    while(namesBuffer != NULL) {
      strcat(putNamesHere, namesBuffer);
      strcat(putNamesHere, ", ");
      charCount += strlen(namesBuffer) + 2;
      namesBuffer = strtok(NULL, "\n");
    }
    putNamesHere[charCount - 2] = ' ';
    putNamesHere[charCount - 1] = '}';
    putNamesHere[charCount] = '\0'; 
  } else {
    sprintf (putNamesHere, "{ UNKNOWN PARENT SET }");
  }
}
//-----------------------------------------------------------------------------
char *GetTPTPProblemFilePath (ANNOTATEDFORMULA anfBuffer) 
{
  String inf_info_term;
  char *fname;
  int i;

  GetFileSourceNameAndNode(anfBuffer, inf_info_term);
  fname = (char*) malloc(sizeof(char)*strlen(inf_info_term));
  strcpy(fname, &inf_info_term[1]);
  for (i = 0; i < strlen(fname); i++) {
    if (fname[i] == '\'') {
      fname[i] = '\0';
      break;
    }
  }
  return fname;
}
//-----------------------------------------------------------------------------
char *GetTPTPProblemName (char *path)
{
  char *fname;

  if ((fname = strrchr(path, '/')) != NULL)
    return &fname[1];
  else
    return path;
}
//-----------------------------------------------------------------------------
/**
 * Problem file is run through tptp2X to convert to tstp format and also
 * to remove equality.
 */
void ConvertTPTPToTSTP (ARGUMENTLIST arg_list,
                        char *tptpFilePath,
                        char *parsedFilePath) 
{
  String problem_path;
  String unixCommand;
  String tmp_tstp;

  strcpy (problem_path, tptpFilePath);
  sprintf (tmp_tstp, "%s/TMP_PROBLEM_FILE.p_tstp", arg_list->baseDirectory);
  sprintf (unixCommand, "%s -d- -q2 -f tptp %s > %s", 
	   TPTP2X_PATH, problem_path, tmp_tstp);

  printf("%s\n\n", unixCommand);

  system (unixCommand);
  sprintf (unixCommand, 
           "%s -d- -q2 -t rm_equality:rstfp %s > %s",
	   TPTP2X_PATH, tmp_tstp, parsedFilePath);
  system (unixCommand);
}
//-----------------------------------------------------------------------------
void force_exit (int theSignal)
{
  printf("%% Process exiting... \n");
  //ClearDirectoryStructure
}
//-----------------------------------------------------------------------------
void SIGINT_Handler (int theSignal) 
{
  extern int Global_Interrupted;
  Global_Interrupted = TRUE;
  printf ("\n%% Process received the SIGINT signal... \n");
}
//-----------------------------------------------------------------------------
void SIGQUIT_Handler (int theSignal) 
{
  extern int Global_Interrupted;
  Global_Interrupted = TRUE;
  printf ("\n%% Process received the SIGQUIT signal... \n");
}
//-----------------------------------------------------------------------------
void SIGHUP_Handler (int theSignal) 
{
  extern int Global_Interrupted; 
  Global_Interrupted = TRUE; 
  printf ("\n%% User has closed his terminal... \n");
}
//-----------------------------------------------------------------------------
void SIGTERM_Handler (int theSignal) 
{
  extern int Global_Interrupted;
  Global_Interrupted = TRUE;
  printf ("\n%% Process received the SIGTERM signal... \n");
}
//-----------------------------------------------------------------------------
void SIGABRT_Handler (int theSignal) 
{
  extern int Global_Interrupted;
  Global_Interrupted = TRUE;
  printf ("\n%% Process received the SIGABRT signal... \n");
}
//-----------------------------------------------------------------------------
SplitType GetSplitType(ANNOTATEDFORMULA anfBuffer) 
{
  String 
    parentNames,
    previousName
    ;
  char *currentName;
  short nameCount;

  /*--------------------------------------------------------------
   * Split type depends on the number of parents a split node has.
   * They are recognized in the following form:
   * [ (False Clause), (Parent), (Antikid Sibling) ]
   * The return type is based on the number of parents it has.
   *--------------------------------------------------------------*/  

  currentName = NULL;
  strcpy(previousName, "");
  GetParentNames(anfBuffer, parentNames);
  currentName = strtok(parentNames, "\n");
  nameCount = 0;
  while(currentName != NULL) {
    if (strcmp(previousName, currentName) != 0) 
      nameCount++;
    strcpy(previousName, currentName);
    currentName = strtok(NULL, "\n");
  }
  if (nameCount == 1)
    return LeftChild;
  else if (nameCount == 2)
    return RightChild;
  else if (nameCount == 3)
    return AntiKid;
  else
    return Undefined;
}
//-----------------------------------------------------------------------------
SPLITPARENTLIST GetSplitParentList(ANNOTATEDFORMULA anfBuffer, 
                                   SplitType type) 
{
  SPLITPARENTLIST list;
  String 
    parentNames,
    previousName
    ;
  char *currentName;

  if (anfBuffer == NULL || type == Undefined)
    return NULL;

  list = NewSplitParentList();
  currentName = NULL;
  strcpy(previousName, "");
  GetParentNames(anfBuffer, parentNames);

  /*------------------------------------------------
   * Parent list must be parsed carefully in order
   * to avoid listing duplicate entries as a 
   * component of the parent list.
   *----------------------------------------------*/

  currentName = strtok(parentNames, "\n");
  if (type == LeftChild) {
    strcpy(list->Parent, currentName);
  }
  else {
    strcpy(list->FalseClause, currentName);
  }
  if (type == RightChild || type == AntiKid) {
    strcpy(previousName, currentName);
    while(strcmp(previousName, currentName) == 0 && currentName != NULL) {
      strcpy(previousName, currentName);
      currentName = strtok(NULL, "\n");
    }
    strcpy(list->Parent, currentName);
  }
  if (type == AntiKid) {
    strcpy(previousName, currentName);
    while(strcmp(previousName, currentName) == 0 && currentName != NULL) {
      strcpy(previousName, currentName);
      currentName = strtok(NULL, "\n");
    }
    strcpy(list->AntiKidOf, currentName);
  }

  return list;
}
//-----------------------------------------------------------------------------


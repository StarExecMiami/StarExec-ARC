/*-----------------------------------------------------------------------------
 * FILE: dvdvProcessor.c
 * AUTHOR: Diego Belfiore
 *
 * Defines the node verification functions that work with SystemOnTPTP.
 * --------------------------------------------------------------------------*/
#include "dvdv.h"
//-----------------------------------------------------------------------------
#define OTTER_SYSTEM_COUNT 2

char *OTTER_SYSTEMS[] = { "Otter---3.3", "Otter---3.3-SoS" };
//-----------------------------------------------------------------------------
int perform_model_check (ANNOTATEDFORMULA parent, 
			 ANNOTATEDFORMULA left_child,
			 ANNOTATEDFORMULA right_child,
			 ARGUMENTLIST argList,
			 SIGNATURE signature);

int check_parent_relevance (LISTNODE axiom_set,
			    LISTNODE conjecture_node,
			    ARGUMENTLIST arg_list);

void add_equality (char *file);

void write_node_set_to_file (LISTNODE set, FILE *stream);

int verify_initial_node (LISTNODE conjectureNode, 
                         ARGUMENTLIST argList);

int verify_derived_node (LISTNODE axiomSet, 
			 LISTNODE conjectureNode, 
			 ARGUMENTLIST argList,
                         SIGNATURE signature);

int verify_split_node (LISTNODE axiomSet, 
		       LISTNODE conjectureNode,
		       STACK *splitStack, 
		       ARGUMENTLIST argList, 
		       SIGNATURE signature);

int verify_esplit (LISTNODE axiom_set,
		   LISTNODE *first_split,		   
		   ARGUMENTLIST arg_list,
		   SIGNATURE signature);

void print_derived_stat_info (ANNOTATEDFORMULA c_formula,
			      int v_status);
//-----------------------------------------------------------------------------
int RunSystemOnTPTP (ARGUMENTLIST argList, 
		     char *formulaName, 
		     char *oblFileName, 
		     int type,
		     int checkModel) 
{ /* Type: 1 = Derived(thm) 
   * 2 = Derived(split) 
   * 3 = Initial  */
  int verified;
  extern int Global_Interrupted;
  String outputFileName;
  String systemCommand;
  String systemBuffer;
  String unixCommand;    
  FILE *outputStream;
  FILE *systemStream;    

  switch (type)     /* Open file stream to write SystemOnTPTP output */
    {
    case (1):
      sprintf (outputFileName,"%s/Derived/Results/%s.dv", 
	       argList->baseDirectory, formulaName);
      break;
    case (2):
      if (checkModel == SEMANTIC_MODEL_CHECK) {
        sprintf (outputFileName,"%s/Derived/Results/%s.semantic_model.dv", 
                 argList->baseDirectory, formulaName);
      }
      else if (checkModel == SAT_MODEL_CHECK) {
        sprintf (outputFileName,"%s/Derived/Results/%s.sat_model.dv", 
                 argList->baseDirectory, formulaName);
      }
      else {
        sprintf (outputFileName,"%s/Derived/Results/%s.split.dv", 
                 argList->baseDirectory, formulaName);
      }
      break;
    case (3):
      sprintf (outputFileName,"%s/Initial/Results/%s.dv_initial", 
	       argList->baseDirectory, formulaName);
      break;
    }
  outputStream = s_fopen (outputFileName, "w");  
  sprintf (systemCommand, SYSTEMONTPTP_PATH);
  strcat (systemCommand, " -q0 ");
  if (checkModel == SAT_MODEL_CHECK) 
    strcat (systemCommand, argList->modelChecker);  
  else
    strcat (systemCommand, argList->theoremProver);
  strcat (systemCommand, " ");
  strcat (systemCommand, argList->timeLimit);
  strcat (systemCommand, " ");
  strcat (systemCommand, oblFileName);
  systemStream = s_popen (systemCommand, "r");
  
  while (fgets (systemBuffer, KBYTE, systemStream) != NULL) 
    fprintf (outputStream, "%s", systemBuffer);
  
  s_fclose (outputStream);
  s_pclose (systemStream);
  if (checkModel == SAT_MODEL_CHECK || checkModel == GENERAL_SAT_CHECK) {
    verified = grep_file (outputFileName, "RESULT:", "Satisfiable", FALSE);
  }
  else if (checkModel == GENERAL_UNSAT_CHECK) { 
    verified = grep_file (outputFileName, "RESULT:", "Unsatisfiable", FALSE);
  }
  else { 
    verified = grep_file (outputFileName, "RESULT:", "Theorem", FALSE);
  }
  if (verified == UNDEFINED && Global_Interrupted == FALSE &&
      grep_file (outputFileName, "ERROR:", NULL, TRUE) != 0) {
    printf ("%% Unspecified system error occurred. \n");
  }   
  if (argList->verbose == TRUE && verified == FAILURE && type != 3) {
    printf ("\n");
    sprintf (unixCommand, "cat %s", oblFileName);
    system (unixCommand);
  } 
  return verified;
}
//-----------------------------------------------------------------------------
void add_equality (char *file)
{
  String system_call;
  String tmp_file;

  sprintf (tmp_file, "%s_equality", file);
  sprintf (system_call, "%s -d- -q2 -t add_equality %s > %s", 
           TPTP2X_PATH, file, tmp_file);
  system (system_call);
  sprintf (system_call, "rm %s", file);
  system (system_call);
  sprintf (system_call, "mv %s %s", tmp_file, file);
  system (system_call);
}
//-----------------------------------------------------------------------------
void write_node_set_to_file (LISTNODE set, FILE *stream)
{
  LISTNODE i;

  for (i = set; i != NULL; i = i->Next)
    PrintAnnotatedTSTPNode (stream, i->AnnotatedFormula, tptp, 1);
}
//-----------------------------------------------------------------------------
int perform_model_check (ANNOTATEDFORMULA parent, 
			 ANNOTATEDFORMULA left_child,
			 ANNOTATEDFORMULA right_child,
			 ARGUMENTLIST argList,
			 SIGNATURE signature) 
{
  FILE *obl_file_stream;
  String semantic_obl_filename;
  String sat_obl_filename;
  String formula_name;
  ANNOTATEDFORMULA negated_left;
  ANNOTATEDFORMULA negated_right;
  ANNOTATEDFORMULA negated_parent;
  int semantic_modelcheck;
  int sat_modelcheck;

  GetName (right_child, formula_name);
  /* Use ATP system to prove that {~L, ~R} |= ~P. SEMANTIC_MODEL_CHECK */
  sprintf (semantic_obl_filename, "%s/%s.semantic_model.obl", 
	   argList->baseDirectory, formula_name);
  obl_file_stream = s_fopen (semantic_obl_filename, "w");
  negated_left = DuplicateAnnotatedFormula (left_child, signature);
  negated_right = DuplicateAnnotatedFormula (right_child, signature);
  negated_parent = DuplicateAnnotatedFormula (parent, signature);
  Negate (negated_left, 1);
  Negate (negated_right, 1);
  Negate (negated_parent, 1);
  SetStatus (negated_left, axiom, nonstatus);
  SetStatus (negated_right, axiom, nonstatus);
  SetStatus (negated_parent, conjecture, nonstatus);
  PrintAnnotatedTSTPNode (obl_file_stream, negated_left, tptp, 1);
  PrintAnnotatedTSTPNode (obl_file_stream, negated_right, tptp, 1);
  PrintAnnotatedTSTPNode (obl_file_stream, negated_parent, tptp, 1);
  s_fclose (obl_file_stream);
  semantic_modelcheck = RunSystemOnTPTP (argList, formula_name, 
					 semantic_obl_filename, 2,
					 SEMANTIC_MODEL_CHECK);
  if (semantic_modelcheck == SUCCESS) {
    printf ("Semantic Model verification for formula %s succeeded. \n",
            formula_name);
  }
  else {
    printf ("Semantic Model verification for formula %s failed. \n",
            formula_name);
  }

  /* Use model checker to prove {~L, ~R} is Satisfiable. SAT_MODEL_CHECK */
  sprintf (sat_obl_filename, "%s/%s.sat_model.obl",
           argList->baseDirectory, formula_name);
  obl_file_stream = s_fopen (sat_obl_filename, "w");
  SetStatus (negated_left, axiom, nonstatus);
  SetStatus (negated_right, axiom, nonstatus);
  PrintAnnotatedTSTPNode (obl_file_stream, negated_left, tptp, 1);
  PrintAnnotatedTSTPNode (obl_file_stream, negated_right, tptp, 1);
  s_fclose (obl_file_stream);
  sat_modelcheck = RunSystemOnTPTP (argList, formula_name, sat_obl_filename, 
				    2, SAT_MODEL_CHECK);
  if (sat_modelcheck == SUCCESS) {
    printf ("SAT Model verification for formula %s succeeded. \n",
            formula_name);
  } else {
    printf ("SAT Model verification for formula %s failed. \n", formula_name);
  }
  if (semantic_modelcheck == SUCCESS && sat_modelcheck == SUCCESS)
    return SUCCESS;
  else 
    return FAILURE;
} 
//-----------------------------------------------------------------------------
void print_derived_stat_info (ANNOTATEDFORMULA c_formula,
			      int v_status)
{ /* Displays message based on c_formula's verification status. */
  String inf_rule;
  String p_name_set;
  String formula_name;

  SetStatus (c_formula, derived, nonstatus);  
  GetName (c_formula, formula_name);
  if (GetInferenceRule (c_formula, inf_rule) == NULL) {
    strcpy (inf_rule,"unknown");
  }
  GetNodeAxiomSet (c_formula, p_name_set);
  if (v_status == SUCCESS) {
    printf ("%s |= %s (%s) \n", p_name_set, formula_name, inf_rule);
  } else if (v_status == FALSE) {
    printf ("Set %s doesn't satisfy %s \n", p_name_set, formula_name);
  } else {
    printf ("Unknown verification status for %s \n", formula_name);
  }
}
//-----------------------------------------------------------------------------
int run_systems (ARGUMENTLIST argList, 
                 char *formula_name, 
                 char *obl_fname)
{
  int i;
  int verified;

  if (strcmp (argList->theoremProver, DEFAULT_ATP_SYSTEM) == 0) {
    verified = FALSE;
    for (i = 0; i < OTTER_SYSTEM_COUNT && verified != SUCCESS; i++) {
      strcpy (argList->theoremProver, OTTER_SYSTEMS[i]);
      // printf ("%% Verifying with %s... \n", OTTER_SYSTEMS[i]);
      verified = RunSystemOnTPTP (argList, formula_name, obl_fname, 1, FALSE);
    }
    strcpy (argList->theoremProver, DEFAULT_ATP_SYSTEM);
    return verified;
  } else {
    return RunSystemOnTPTP (argList, formula_name, obl_fname, 1, FALSE);
  }
}
//-----------------------------------------------------------------------------
int verify_derived_node (LISTNODE axiomSet, 
			 LISTNODE conjectureNode, 
			 ARGUMENTLIST argList,
                         SIGNATURE signature)
{
  int verified;
  int add_equality;
  String obl_fname;
  String p_names;
  String formula_name;
  String system_call;
  String inf_info_term;
  char *names_buff;
  FILE *obl_stream;
  ANNOTATEDFORMULA c_formula;
  ANNOTATEDFORMULA negated_f;

  verified = FALSE;
  add_equality = FALSE;
  c_formula = conjectureNode->AnnotatedFormula;
  GetName (c_formula, formula_name);
  sprintf (obl_fname,"%s/Derived/Obligations/%s_%s.obl", 
	   argList->baseDirectory, formula_name, argList->host_pid_name);
  obl_stream = s_fopen (obl_fname, "w");      
  GetParentNames (c_formula, p_names);
  names_buff = strtok (p_names, "\n");    
  while (names_buff != NULL) {    
    if(strcmp(names_buff, "theory(equality)") == 0) {      
      add_equality = TRUE;
    } else {	    
      c_formula = GetAnnotatedFormulaFromListByName (axiomSet, names_buff);
      if (c_formula == NULL) {  
	s_fclose(obl_stream);
	printf("ERROR: Formula %s lists %s as a parent formula, which \n"
	       "       does not appear in the solution file. \n",
	       formula_name, names_buff);
	return FALSE;
      }	
      SetStatus (c_formula, axiom, nonstatus);
      PrintAnnotatedTSTPNode (obl_stream, c_formula, tptp, 1);
    }
    names_buff = strtok (NULL, "\n");
  }

  GetInferenceInfoTerm(conjectureNode->AnnotatedFormula, "status", 
                       inf_info_term);
  if (strcmp(inf_info_term, "status(cth)") == 0) {
    negated_f = DuplicateAnnotatedFormula(conjectureNode->AnnotatedFormula,
                                          signature);
    Negate(negated_f, 1);
    SetStatus(negated_f, conjecture, nonstatus);
    PrintAnnotatedTSTPNode(obl_stream, negated_f, tptp, 1);      
  } else {
    c_formula = conjectureNode->AnnotatedFormula;
    SetStatus (c_formula, conjecture, nonstatus);
    PrintAnnotatedTSTPNode (obl_stream, c_formula, tptp, 1);
  }
  s_fclose(obl_stream);

  if (add_equality == TRUE) {
    sprintf(system_call, 
	    "%s -d- -q2 -t add_equality %s > %s/Derived/DV_TMP_EQUALITY",
	    TPTP2X_PATH, obl_fname, argList->baseDirectory);
    system (system_call);	  
    sprintf (system_call, "rm %s", obl_fname);
    system (system_call);
    sprintf (system_call, "mv %s/Derived/DV_TMP_EQUALITY %s", 
	     argList->baseDirectory, obl_fname);
    system (system_call);      
  }

  verified = run_systems (argList, formula_name, obl_fname);
  return verified;
}
//-----------------------------------------------------------------------------
int verify_initial_node (LISTNODE conjectureNode, 
                         ARGUMENTLIST argList)
{
  int verified;
  String obl_fname;
  String formula_name;
  FILE *obl_stream;
  ANNOTATEDFORMULA c_formula;

  verified = FALSE;
  c_formula = conjectureNode->AnnotatedFormula;
  SetStatus (c_formula, conjecture, nonstatus);
  GetName (c_formula, formula_name);
  sprintf (obl_fname, "%s/Initial/Obligations/%s_%s.obl", 
	   argList->baseDirectory, formula_name, argList->host_pid_name);
  obl_stream = s_fopen (obl_fname, "w");      
  write_node_set_to_file (argList->input_problem_sets.P, obl_stream);
  PrintAnnotatedTSTPNode (obl_stream, c_formula, tptp, 1);
  s_fclose (obl_stream);
  add_equality (obl_fname);
  verified = run_systems (argList, formula_name, obl_fname);
  if (verified != SUCCESS) {
    obl_stream = s_fopen (obl_fname, "w");      
    write_node_set_to_file (argList->input_problem_sets.P, obl_stream);
    write_node_set_to_file (argList->input_problem_sets.Mixed, obl_stream);
    PrintAnnotatedTSTPNode (obl_stream, c_formula, tptp, 1);
    s_fclose (obl_stream);
    add_equality (obl_fname);
    verified = run_systems (argList, formula_name, obl_fname);
  }
  if (verified != SUCCESS) {
    obl_stream = s_fopen (obl_fname, "w");      
    write_node_set_to_file (argList->input_problem_sets.N, obl_stream);
    PrintAnnotatedTSTPNode (obl_stream, c_formula, tptp, 1);
    s_fclose (obl_stream);
    add_equality (obl_fname);
    verified = run_systems (argList, formula_name, obl_fname);
  }
  if (verified != SUCCESS) {
    obl_stream = s_fopen (obl_fname, "w");      
    write_node_set_to_file (argList->input_problem_sets.N, obl_stream);
    write_node_set_to_file (argList->input_problem_sets.Mixed, obl_stream);
    PrintAnnotatedTSTPNode (obl_stream, c_formula, tptp, 1);
    s_fclose (obl_stream);
    add_equality (obl_fname);
    verified = run_systems (argList, formula_name, obl_fname);
  }  
  return verified;
}
//-----------------------------------------------------------------------------
int verify_node (LISTNODE axiomSet, 
		 LISTNODE *conjectureNode, 
		 STACK *split_stack,
		 ARGUMENTLIST argList,
		 SIGNATURE signature)
{ 
  int verified;
  int relevance_check;
  String formula_name;
  String inf_info_term;
  String inf_rule;
  StatusType status, substatus;
  ANNOTATEDFORMULA c_formula;
  ANNOTATEDFORMULA clone_of;

  verified = FAILURE;
  c_formula = (*conjectureNode)->AnnotatedFormula;
  GetName (c_formula, formula_name);
  status = GetStatus (c_formula, &substatus);

  if (status == derived || substatus == derived) {
    if (strcmp(GetSource(c_formula, inf_info_term), "inference") != 0) {
      clone_of = GetAnnotatedFormulaFromListByName(axiomSet, inf_info_term);
      verified = (clone_of != NULL &&
   SameFormulaInAnnotatedFormula(c_formula, clone_of, 1)) ? SUCCESS : FAILURE;
      print_derived_stat_info((*conjectureNode)->AnnotatedFormula, verified);
      return verified;
    }

    strcpy(inf_info_term,"");
    if (GetInferenceInfoTerm(c_formula, "status", inf_info_term) != NULL &&
        (strcmp(inf_info_term, "status(thm)") == 0 ||
         strcmp(inf_info_term, "status(cth)") == 0)) {
      verified = verify_derived_node (axiomSet, (*conjectureNode), argList,
                                      signature);
      print_derived_stat_info ((*conjectureNode)->AnnotatedFormula, 
                               verified);
    } 
    else {
      GetInferenceRule (c_formula, inf_rule);
      if (GetInferenceInfoTerm (c_formula, inf_rule, inf_info_term) != NULL) {
	if (strncmp (inf_info_term, "spt(sr_split", 12) == 0) {
	  verified = verify_split_node (axiomSet, (*conjectureNode),
					split_stack, argList, signature);
	} else if (strncmp (inf_info_term, "spt(ss_split", 12) == 0) {
	  printf ("WARNING: The split type used is not yet supported. \n");
	  verified = SUCCESS;
	} else if (strncmp (inf_info_term, "split(esplit", 12) == 0) {
          verified = geoff_esplit_check(axiomSet, conjectureNode, argList,
                                        signature);
	} else {
	  printf ("ERROR: Unknown special rule name %s. \n", inf_info_term);
	  verified = FAILURE;
	}
      }

      // ADDED TO DEAL WITH FOF CONJECTURES
      else {
        printf("ERROR: Cannot check %s ",formula_name);
        if (strstr(inf_info_term,"status") == inf_info_term) {
          printf("with %s ",inf_info_term);
        }
        printf("\n");
        verified = FAILURE;
      }
    }
    if (verified == FAILURE) {
      Global_Error_Flag = SEMANTIC_FAILURE;
      return FAILURE;
    }
    if (argList->checkParentRelevance == TRUE) {  
      relevance_check = check_parent_relevance (axiomSet, (*conjectureNode), 
						argList);
      if (relevance_check == FAILURE) {
	printf ("DEBUG: RELEVANCE CHECK FAILED!!! \n");
      }
      if (verified == SUCCESS && relevance_check == SUCCESS) {
	return SUCCESS;
      }	else {
	return FAILURE;
      }
    }
  } else {
    if (argList->verifyInitials == TRUE) {
      verified = verify_initial_node ((*conjectureNode), argList);
      if (verified == SUCCESS) {
	printf("(initial) %s passed semantic verification. \n", formula_name);
      } else {
        printf("(initial) %s failed semantic verification. \n", formula_name);
        Global_Error_Flag = INITIAL_FILE_FAILURE;
        if (argList->verbose == TRUE) {
          printf("\n");
          PrintAnnotatedTSTPNode (stdout, c_formula, tptp, 1);
          printf ("\n");
        }
      }
    } else {
      verified = SUCCESS;
    }
  }
  return verified;
}
//-----------------------------------------------------------------------------
int verify_split_node (LISTNODE axiomSet, 
		       LISTNODE conjectureNode,
		       STACK *splitStack, 
		       ARGUMENTLIST argList,
		       SIGNATURE signature) 
{ 
  int verified;
  String formulaName;
  String oblFileName;
  FILE *oblStream;
  SplitType type;
  SPLITPARENTLIST parentList;
  ANNOTATEDFORMULA anfBuffer;
  ANNOTATEDFORMULA conjectureFormula;
  ANNOTATEDFORMULA m_parent;      /* Used only for model checking. */
  ANNOTATEDFORMULA m_left;
  ANNOTATEDFORMULA m_right;

  conjectureFormula = conjectureNode->AnnotatedFormula;
  GetName (conjectureFormula, formulaName);
  type = GetSplitType (conjectureFormula);
  parentList = GetSplitParentList (conjectureFormula, type);
  verified = FAILURE;  
  if (type == Undefined) 
    { /* Unknown split type encuontered. */
      printf("%% Structural error occured: %s is of an undefined "
             "split type. \n", formulaName);
      return UNDEFINED;
    }  
  else if (type == LeftChild) 
    { /* Just push onto stack if it's a left child. */
      printf ("(split) %s is the left child of %s. \n", 
	      formulaName, parentList->Parent);
      Push (splitStack, conjectureFormula);
      return TRUE;
    }  
  else if (type == AntiKid) 
    { /* Antikid: Negated and verified with AntiKidOf node. */   
      sprintf(oblFileName, "%s/Derived/Obligations/%s.split.obl", 
              argList->baseDirectory, formulaName);
      oblStream = s_fopen(oblFileName, "w"); 
      if (splitStack == NULL) {
	printf ("%% Structural error encountered in verifying antikid "
		"formula %s: \n%% No split history present to verify"
		"this formula. \n", formulaName);
        s_fclose (oblStream);
	return FAILURE;
      }
      /* Write obligation {~L} |= A and run through SystemOnTPTP. */
      anfBuffer = GetAnnotatedFormulaFromListByName(axiomSet, 
						    parentList->AntiKidOf);
      SetStatus (anfBuffer, axiom, nonstatus);
      PrintAnnotatedTSTPNode (oblStream, anfBuffer, tptp, 1);
      conjectureFormula = DuplicateAnnotatedFormula (conjectureNode->
						     AnnotatedFormula,
						     signature);
      Negate (conjectureFormula, 1);
      SetStatus (conjectureFormula, conjecture, nonstatus);
      PrintAnnotatedTSTPNode (oblStream, conjectureFormula, tptp, 1);
      s_fclose(oblStream);
      verified = RunSystemOnTPTP (argList, formulaName, oblFileName, 
				  2, FALSE);
      if (verified == SUCCESS) {
	printf ("(split) %s is the AntiKid of %s ({~%s} |= %s). \n", 
		formulaName, parentList->AntiKidOf, formulaName, 
		parentList->AntiKidOf);
      }
      else {
	printf ("(split) AntiKid verification failed, %s != ~%s. \n",
		formulaName, parentList->AntiKidOf);
      }	
    }
  /*-------------------------------------------------------------------
   * Right Child: Model checking is performed in this case. 
   * Verify that {~L, ~R} |= ~P using the specified ATP system,
   * and that {~L, ~R} is satisfiable using the model checking system. 
   *------------------------------------------------------------------*/
  else if (type == RightChild) 
    {
      m_parent = GetAnnotatedFormulaFromListByName (axiomSet, 
                                                    parentList->Parent);
      m_left = Pop (splitStack);
      m_right = conjectureFormula;
      verified = perform_model_check (m_parent, m_left, m_right, argList,
                                      signature);
    }  
  return verified;
}
//-----------------------------------------------------------------------------
int check_parent_relevance (LISTNODE axiom_set,
			    LISTNODE conjecture_node,
			    ARGUMENTLIST arg_list)
{
  int verified;
  int default_verbose;
  char *names_buffer;  
  String formula_name;
  String obl_filename;
  String parent_names;
  String unix_command;
  String default_prover;
  FILE *obl_stream;  
  BOOLEAN equality_flag;  
  ANNOTATEDFORMULA anf_buffer;

  if (is_false_clause(conjecture_node->AnnotatedFormula) == TRUE)
    return SUCCESS;

  verified = FALSE;
  equality_flag = FALSE;
  anf_buffer = conjecture_node->AnnotatedFormula;
  GetName (anf_buffer, formula_name);
  sprintf (obl_filename,"%s/Derived/Obligations/%s.relevance.obl", 
	   arg_list->baseDirectory, formula_name);
  obl_stream = s_fopen (obl_filename, "w");
  GetParentNames (anf_buffer, parent_names);   /* Print parents to file. */
  names_buffer = strtok (parent_names, "\n");    
  while (names_buffer != NULL) 
    { /* Set parents as axioms and print to obligation file. */    	
      if(strcmp(names_buffer, "theory(Equality)") == 0 ||
	 strcmp(names_buffer, "theory(equality)") == 0)
	{ /* Set flag if theory(equality) is a parent. */
	  equality_flag = TRUE;
	}
      else {	    
	anf_buffer = GetAnnotatedFormulaFromListByName (axiom_set, 
						       names_buffer);
	if (anf_buffer == NULL) {  
	  s_fclose(obl_stream);
	  printf ("ERROR: Formula %s lists %s as a parent formula, which \n"
		  "       does not appear in the solution file. \n",
		  formula_name, names_buffer);
	  return FALSE;
	}	
	SetStatus (anf_buffer, axiom, nonstatus);
	PrintAnnotatedTSTPNode (obl_stream, anf_buffer, tptp, 1);
      }
      names_buffer = strtok (NULL, "\n");
    }      
  s_fclose (obl_stream);            
  if (equality_flag == TRUE) 
    { /* Add equality axioms if necessary by using tptp2X. */
      sprintf(unix_command, 
	      "%s -d- -q2 -t add_equality %s > %s/Derived/DV_TMP_EQUALITY",
	      TPTP2X_PATH, obl_filename, arg_list->baseDirectory);
      system (unix_command);	  
      /* Delete old file and rename temp file to obligation name */
      sprintf (unix_command, "rm %s", obl_filename);
      system (unix_command);
      sprintf (unix_command, "mv %s/Derived/DV_TMP_EQUALITY %s", 
	       arg_list->baseDirectory, obl_filename);
      system (unix_command);      
    }

  default_verbose = arg_list->verbose;
  arg_list->verbose = FALSE;  
  strcpy (default_prover, arg_list->theoremProver);
  /* Run check with Paradox, or default model checker. */
  verified = RunSystemOnTPTP (arg_list, formula_name, obl_filename, 2, 
                              SAT_MODEL_CHECK);
  if (verified == FAILURE) {  /* Try for a Satisfiable result with E */
    strcpy (arg_list->theoremProver, E_PROVER);
    verified = RunSystemOnTPTP (arg_list, formula_name, obl_filename, 2, 
                                GENERAL_SAT_CHECK);
  }
  if (verified == SUCCESS) {  /* Relevance succeeded without question. */
    printf ("%% Relevance check for parent set of formula %s succeeded. \n",
            formula_name);
  }
  if (verified == FAILURE) { /* Check for unsatisfiable result with Otter. */
    strcpy (arg_list->theoremProver, OTTER);
    verified = RunSystemOnTPTP (arg_list, formula_name, obl_filename, 2, 
                                GENERAL_UNSAT_CHECK);
    if (verified == SUCCESS) {  /* Obligation can't be discharged. */
      printf ("%% Relevance check for the parent set of formula %s \n"
              "   failed verification. Otter prover returned "
              "\"Unsatisfiable\" for formula set. \n", formula_name);
      verified = FAILURE;
    }
    else {
      printf ("%% Relevance check for the parent set of formula %s \n"
              "   passed verification but without a low degree of"
              "certainty. \n", formula_name);
      verified = SUCCESS;
    }
  }
  arg_list->verbose = default_verbose;
  strcpy (arg_list->theoremProver, default_prover);  
  return verified;
}
//-----------------------------------------------------------------------------

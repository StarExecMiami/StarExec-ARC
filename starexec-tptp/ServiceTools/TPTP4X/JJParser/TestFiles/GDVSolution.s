%------------------------------------------------------------------------------
% File     : E---3.0
% Problem  : PUZ131_1 : TPTP v8.1.2. Released v5.0.0.
% Transfm  : none
% Format   : tptp:raw
% Command  : run_E %s %d THM

% Computer : n005.cluster.edu
% Model    : x86_64 x86_64
% CPU      : Intel(R) Xeon(R) CPU E5-2620 v4 2.10GHz
% Memory   : 8042.1875MB
% OS       : Linux 3.10.0-693.el7.x86_64
% CPULimit : 300s
% WCLimit  : 300s
% DateTime : Wed May 17 15:59:01 EDT 2023

% Result   : Theorem 0.16s 0.42s
% Output   : CNFRefutation 0.16s
% Verified : 

% Comments : 
%------------------------------------------------------------------------------
tff(student_type,type,
    student: $tType ).

tff(professor_type,type,
    professor: $tType ).

tff(course_type,type,
    course: $tType ).

tff(decl_22,type,
    michael: student ).

tff(decl_23,type,
    victor: professor ).

tff(decl_24,type,
    csc410: course ).

tff(decl_25,type,
    enrolled: ( student * course ) > $o ).

tff(decl_26,type,
    teaches: ( professor * course ) > $o ).

tff(decl_27,type,
    taughtby: ( student * professor ) > $o ).

tff(decl_28,type,
    coordinatorof: course > professor ).

tff(coordinator_teaches,axiom,
    ! [X8: course] : teaches(coordinatorof(X8),X8),
    file('/export/starexec/sandbox2/benchmark/theBenchmark.p',coordinator_teaches) ).

tff(student_enrolled_taught,axiom,
    ! [X1: student,X2: course] :
      ( enrolled(X1,X2)
     => ! [X9: professor] :
          ( teaches(X9,X2)
         => taughtby(X1,X9) ) ),
    file('/export/starexec/sandbox2/benchmark/theBenchmark.p',student_enrolled_taught) ).

tff(victor_coordinator_csc410_axiom,axiom,
    coordinatorof(csc410) = victor,
    file('/export/starexec/sandbox2/benchmark/theBenchmark.p',victor_coordinator_csc410_axiom) ).

tff(teaching_conjecture,conjecture,
    taughtby(michael,victor),
    file('/export/starexec/sandbox2/benchmark/theBenchmark.p',teaching_conjecture) ).

tff(michael_enrolled_csc410_axiom,axiom,
    enrolled(michael,csc410),
    file('/export/starexec/sandbox2/benchmark/theBenchmark.p',michael_enrolled_csc410_axiom) ).

tff(c_0_5,plain,
    ! [X21: course] : teaches(coordinatorof(X21),X21),
    inference(variable_rename,[status(thm)],[coordinator_teaches]) ).

tff(c_0_6,plain,
    ! [X10: student,X11: course,X12: professor] :
      ( ~ enrolled(X10,X11)
      | ~ teaches(X12,X11)
      | taughtby(X10,X12) ),
    inference(shift_quantors,[status(thm)],[inference(variable_rename,[status(thm)],[inference(fof_nnf,[status(thm)],[student_enrolled_taught])])]) ).

tcf(c_0_7,plain,
    ! [X2: course] : teaches(coordinatorof(X2),X2),
    inference(split_conjunct,[status(thm)],[c_0_5]) ).

tcf(c_0_8,plain,
    coordinatorof(csc410) = victor,
    inference(split_conjunct,[status(thm)],[victor_coordinator_csc410_axiom]) ).

tcf(c_0_9,plain,
    ! [X1: student,X3: professor,X2: course] :
      ( taughtby(X1,X3)
      | ~ enrolled(X1,X2)
      | ~ teaches(X3,X2) ),
    inference(split_conjunct,[status(thm)],[c_0_6]) ).

tcf(c_0_10,plain,
    teaches(victor,csc410),
    inference(spm,[status(thm)],[c_0_7,c_0_8]) ).

tff(c_0_11,negated_conjecture,
    ~ taughtby(michael,victor),
    inference(fof_simplification,[status(thm)],[inference(assume_negation,[status(cth)],[teaching_conjecture])]) ).

tcf(c_0_12,plain,
    ! [X1: student] :
      ( taughtby(X1,victor)
      | ~ enrolled(X1,csc410) ),
    inference(spm,[status(thm)],[c_0_9,c_0_10]) ).

tcf(c_0_13,plain,
    enrolled(michael,csc410),
    inference(split_conjunct,[status(thm)],[michael_enrolled_csc410_axiom]) ).

tcf(c_0_14,negated_conjecture,
    ~ taughtby(michael,victor),
    inference(split_conjunct,[status(thm)],[c_0_11]) ).

cnf(c_0_15,plain,
    $false,
    inference(sr,[status(thm)],[inference(spm,[status(thm)],[c_0_12,c_0_13]),c_0_14]),
    [proof] ).

%------------------------------------------------------------------------------
%----ORIGINAL SYSTEM OUTPUT
% 0.00/0.10  % Problem    : PUZ131_1 : TPTP v8.1.2. Released v5.0.0.
% 0.10/0.11  % Command    : run_E %s %d THM
% 0.10/0.31  % Computer : n005.cluster.edu
% 0.10/0.31  % Model    : x86_64 x86_64
% 0.10/0.31  % CPU      : Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz
% 0.10/0.31  % Memory   : 8042.1875MB
% 0.10/0.31  % OS       : Linux 3.10.0-693.el7.x86_64
% 0.10/0.31  % CPULimit   : 300
% 0.10/0.31  % WCLimit    : 300
% 0.10/0.31  % DateTime   : Wed May  3 16:29:54 EDT 2023
% 0.10/0.31  % CPUTime    : 
% 0.16/0.42  Running first-order on 8 cores theorem proving
% 0.16/0.42  Running: /export/starexec/sandbox2/solver/bin/eprover --delete-bad-limit=2000000000 --definitional-cnf=24 -s --print-statistics -R --print-version --proof-object --auto-schedule=8 --cpu-limit=300 /export/starexec/sandbox2/benchmark/theBenchmark.p
% 0.16/0.42  # Version: 3.0pre008
% 0.16/0.42  # Preprocessing class: FSSSSMSSSSSNFFN.
% 0.16/0.42  # Scheduled 4 strats onto 8 cores with 300 seconds (2400 total)
% 0.16/0.42  # Starting G-E--_302_C18_F1_URBAN_RG_S04BN with 1500s (5) cores
% 0.16/0.42  # Starting new_bool_3 with 300s (1) cores
% 0.16/0.42  # Starting new_bool_1 with 300s (1) cores
% 0.16/0.42  # Starting sh5l with 300s (1) cores
% 0.16/0.42  # new_bool_1 with pid 18082 completed with status 0
% 0.16/0.42  # Result found by new_bool_1
% 0.16/0.42  # Preprocessing class: FSSSSMSSSSSNFFN.
% 0.16/0.42  # Scheduled 4 strats onto 8 cores with 300 seconds (2400 total)
% 0.16/0.42  # Starting G-E--_302_C18_F1_URBAN_RG_S04BN with 1500s (5) cores
% 0.16/0.42  # Starting new_bool_3 with 300s (1) cores
% 0.16/0.42  # Starting new_bool_1 with 300s (1) cores
% 0.16/0.42  # SinE strategy is GSinE(CountFormulas,hypos,1.5,,3,20000,1.0)
% 0.16/0.42  # Search class: FHUSM-FFSF11-SFFFFFNN
% 0.16/0.42  # partial match(1): FHUSM-FFSF21-SFFFFFNN
% 0.16/0.42  # Scheduled 5 strats onto 1 cores with 300 seconds (300 total)
% 0.16/0.42  # Starting G-E--_208_C18_F1_AE_CS_SP_PI_S0a with 181s (1) cores
% 0.16/0.42  # G-E--_208_C18_F1_AE_CS_SP_PI_S0a with pid 18089 completed with status 0
% 0.16/0.42  # Result found by G-E--_208_C18_F1_AE_CS_SP_PI_S0a
% 0.16/0.42  # Preprocessing class: FSSSSMSSSSSNFFN.
% 0.16/0.42  # Scheduled 4 strats onto 8 cores with 300 seconds (2400 total)
% 0.16/0.42  # Starting G-E--_302_C18_F1_URBAN_RG_S04BN with 1500s (5) cores
% 0.16/0.42  # Starting new_bool_3 with 300s (1) cores
% 0.16/0.42  # Starting new_bool_1 with 300s (1) cores
% 0.16/0.42  # SinE strategy is GSinE(CountFormulas,hypos,1.5,,3,20000,1.0)
% 0.16/0.42  # Search class: FHUSM-FFSF11-SFFFFFNN
% 0.16/0.42  # partial match(1): FHUSM-FFSF21-SFFFFFNN
% 0.16/0.42  # Scheduled 5 strats onto 1 cores with 300 seconds (300 total)
% 0.16/0.42  # Starting G-E--_208_C18_F1_AE_CS_SP_PI_S0a with 181s (1) cores
% 0.16/0.42  # Preprocessing time       : 0.001 s
% 0.16/0.42  
% 0.16/0.42  # Proof found!
% 0.16/0.42  # SZS status Theorem
% 0.16/0.42  # SZS output start CNFRefutation
% See solution above
% 0.16/0.42  # Parsed axioms                        : 19
% 0.16/0.42  # Removed by relevancy pruning/SinE    : 10
% 0.16/0.42  # Initial clauses                      : 9
% 0.16/0.42  # Removed in clause preprocessing      : 0
% 0.16/0.42  # Initial clauses in saturation        : 9
% 0.16/0.42  # Processed clauses                    : 11
% 0.16/0.42  # ...of these trivial                  : 0
% 0.16/0.42  # ...subsumed                          : 0
% 0.16/0.42  # ...remaining for further processing  : 11
% 0.16/0.42  # Other redundant clauses eliminated   : 0
% 0.16/0.42  # Clauses deleted for lack of memory   : 0
% 0.16/0.42  # Backward-subsumed                    : 0
% 0.16/0.42  # Backward-rewritten                   : 0
% 0.16/0.42  # Generated clauses                    : 9
% 0.16/0.42  # ...of the previous two non-redundant : 8
% 0.16/0.42  # ...aggressively subsumed             : 0
% 0.16/0.42  # Contextual simplify-reflections      : 0
% 0.16/0.42  # Paramodulations                      : 9
% 0.16/0.42  # Factorizations                       : 0
% 0.16/0.42  # NegExts                              : 0
% 0.16/0.42  # Equation resolutions                 : 0
% 0.16/0.42  # Propositional unsat checks           : 0
% 0.16/0.42  #    Propositional check models        : 0
% 0.16/0.42  #    Propositional check unsatisfiable : 0
% 0.16/0.42  #    Propositional clauses             : 0
% 0.16/0.42  #    Propositional clauses after purity: 0
% 0.16/0.42  #    Propositional unsat core size     : 0
% 0.16/0.42  #    Propositional preprocessing time  : 0.000
% 0.16/0.42  #    Propositional encoding time       : 0.000
% 0.16/0.42  #    Propositional solver time         : 0.000
% 0.16/0.42  #    Success case prop preproc time    : 0.000
% 0.16/0.42  #    Success case prop encoding time   : 0.000
% 0.16/0.42  #    Success case prop solver time     : 0.000
% 0.16/0.42  # Current number of processed clauses  : 11
% 0.16/0.42  #    Positive orientable unit clauses  : 8
% 0.16/0.42  #    Positive unorientable unit clauses: 0
% 0.16/0.42  #    Negative unit clauses             : 1
% 0.16/0.42  #    Non-unit-clauses                  : 2
% 0.16/0.42  # Current number of unprocessed clauses: 5
% 0.16/0.42  # ...number of literals in the above   : 10
% 0.16/0.42  # Current number of archived formulas  : 0
% 0.16/0.42  # Current number of archived clauses   : 0
% 0.16/0.42  # Clause-clause subsumption calls (NU) : 0
% 0.16/0.42  # Rec. Clause-clause subsumption calls : 0
% 0.16/0.42  # Non-unit clause-clause subsumptions  : 0
% 0.16/0.42  # Unit Clause-clause subsumption calls : 0
% 0.16/0.42  # Rewrite failures with RHS unbound    : 0
% 0.16/0.42  # BW rewrite match attempts            : 0
% 0.16/0.42  # BW rewrite match successes           : 0
% 0.16/0.42  # Condensation attempts                : 0
% 0.16/0.42  # Condensation successes               : 0
% 0.16/0.42  # Termbank termtop insertions          : 397
% 0.16/0.42  
% 0.16/0.42  # -------------------------------------------------
% 0.16/0.42  # User time                : 0.003 s
% 0.16/0.42  # System time              : 0.002 s
% 0.16/0.42  # Total time               : 0.004 s
% 0.16/0.42  # Maximum resident set size: 1776 pages
% 0.16/0.42  
% 0.16/0.42  # -------------------------------------------------
% 0.16/0.42  # User time                : 0.004 s
% 0.16/0.42  # System time              : 0.003 s
% 0.16/0.42  # Total time               : 0.007 s
% 0.16/0.42  # Maximum resident set size: 1716 pages
%------------------------------------------------------------------------------

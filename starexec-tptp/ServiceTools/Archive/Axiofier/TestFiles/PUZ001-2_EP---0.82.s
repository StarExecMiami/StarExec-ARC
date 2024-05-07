%------------------------------------------------------------------------------
% File       : EP---0.82
% Problem    : PUZ001-2 : TPTP v1.0.0
% Transform  : none
% Format     : tptp
% Command    : eproof --print-statistics -xAuto -tAuto --memory-limit=Auto --tstp-in --tstp-out %s

% Computer   : art10.cs.miami.edu
% Model      : i686 unknown
% CPU        : Intel(R) Pentium(R) 4 CPU 2.80GHz @ 2793MHz
% Memory     : 1000MB
% OS         : Linux 2.4.22-21mdk-i686-up-4GB
% CPULimit   : 600s

% Result     : Unsatisfiable 0.1s
% Output     : Refutation 0.1s
% Statistics : Number of clauses     :   28 (  32 expanded)
%              Depth                 :   10
%              Number of atoms       :   48 (  53 expanded)
%              Maximal clause size   :    4 (   2 average)
%              Maximal term depth    :    2 (   1 average)
% Verified   : 

% Comments   : 
%------------------------------------------------------------------------------
%----TSTP SOLUTION
cnf(1,axiom,
    ( lives_at_dreadsbury(someone) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',someone_in_mansion)).

cnf(2,axiom,
    ( killed(someone,aunt_agatha) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',someone_killed_agatha)).

cnf(6,axiom,
    ( X1 = aunt_agatha
    | X1 = butler
    | X1 = charles
    | ~ lives_at_dreadsbury(X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',noone_else_lives_at_mansion)).

cnf(7,axiom,
    ( hates(X1,X2)
    | ~ killed(X1,X2) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',killer_hates_victim)).

cnf(8,axiom,
    ( ~ killed(X1,X2)
    | ~ richer(X1,X2) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',killer_poorer_than_victim)).

cnf(9,axiom,
    ( ~ hates(aunt_agatha,X1)
    | ~ hates(charles,X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',charles_and_agatha_hate_different_people)).

cnf(10,axiom,
    ( X1 = butler
    | hates(aunt_agatha,X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',agatha_likes_only_butler)).

cnf(11,axiom,
    ( richer(X1,aunt_agatha)
    | hates(butler,X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',butler_hates_poor_people)).

cnf(12,axiom,
    ( hates(butler,X1)
    | ~ hates(aunt_agatha,X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',butler_and_agatha_hate_the_same_people)).

cnf(13,axiom,
    ( ~ hates(X1,every_one_but(X1)) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',noone_hates_everyone)).

cnf(14,axiom,
    (  aunt_agatha != butler ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',agatha_is_not_the_butler)).

cnf(15,negated_conjecture,
    ( ~ killed(aunt_agatha,aunt_agatha) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp',prove_agatha_killed_herself)).

cnf(16,derived,
    ( aunt_agatha = someone
    | butler = someone
    | charles = someone ),
    inference(pm,[status(thm)],[6,1,theory(equality)])).

cnf(20,derived,
    ( hates(someone,aunt_agatha) ),
    inference(pm,[status(thm)],[7,2,theory(equality)])).

%----SURPLUS - not in Vampire proof
cnf(21,derived,
    ( ~ hates(aunt_agatha,every_one_but(butler)) ),
    inference(pm,[status(thm)],[13,12,theory(equality)])).

cnf(23,derived,
    ( hates(butler,X1)
    | ~ killed(X1,aunt_agatha) ),
    inference(pm,[status(thm)],[8,11,theory(equality)])).

cnf(24,derived,
    ( butler = every_one_but(butler) ),
    inference(pm,[status(thm)],[21,10,theory(equality)])).

cnf(29,derived,
    ( hates(charles,aunt_agatha)
    | someone = aunt_agatha
    | someone = butler ),
    inference(pm,[status(thm)],[20,16,theory(equality)])).

cnf(33,derived,
    ( ~ hates(butler,butler) ),
    inference(pm,[status(thm)],[13,24,theory(equality)])).

cnf(35,derived,
    ( hates(butler,someone) ),
    inference(pm,[status(thm)],[23,2,theory(equality)])).

cnf(65,derived,
    ( someone = aunt_agatha
    | someone = butler
    | ~ hates(aunt_agatha,aunt_agatha) ),
    inference(pm,[status(thm)],[9,29,theory(equality)])).

cnf(66,derived,
    ( someone = aunt_agatha
    | someone = butler
    | butler = aunt_agatha ),
    inference(pm,[status(thm)],[65,10,theory(equality)])).

%----SURPLUS - not in Vampire proof
cnf(67,derived,
    ( someone = aunt_agatha
    | someone = butler ),
    inference(sr,[status(thm)],[66,14,theory(equality)])).

cnf(72,derived,
    ( hates(butler,butler)
    | someone = aunt_agatha ),
    inference(pm,[status(thm)],[35,67,theory(equality)])).

cnf(75,derived,
    ( someone = aunt_agatha ),
    inference(sr,[status(thm)],[72,33,theory(equality)])).

cnf(79,derived,
    ( killed(aunt_agatha,aunt_agatha) ),
    inference(rw,[status(thm)],[2,75,theory(equality)])).

cnf(80,derived,
    ( $false ),
    inference(sr,[status(thm)],[79,15,theory(equality)])).

cnf(81,derived,
    ( $false ),
    80,
    ['proof']).

%----MISSING here from Vampire 7.0 proof
cnf(48,derived,
    ( hates(butler,X1) | X1=butler ),
    inference(resolution,[status(thm)],[10,12]),
    [iquote('[26,12->48, resolution]')]).

% [16->24, preprocessing]     ~killed(X1,aunt_agatha) \/ hates(butler,X1)
cnf(24,derived,
    ( ~killed(X1,aunt_agatha) | hates(butler,X1) ),
    inference(resolution,[status(thm)],[11,8]),
    [iquote('[16->24, preprocessing]')]).

%------------------------------------------------------------------------------
%----ORIGINAL SYSTEM OUTPUT
% # Problem is unsatisfiable, constructing proof object
% # TSTP exit status: Unsatisfiable
% # Proof object starts here.
% cnf(1,axiom,(lives_at_dreadsbury(someone)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', someone_in_mansion)).
% cnf(2,axiom,(killed(someone,aunt_agatha)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', someone_killed_agatha)).
% cnf(6,axiom,(X1=aunt_agatha|X1=butler|X1=charles|~lives_at_dreadsbury(X1)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', noone_else_lives_at_mansion)).
% cnf(7,axiom,(hates(X1,X2)|~killed(X1,X2)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', killer_hates_victim)).
% cnf(8,axiom,(~killed(X1,X2)|~richer(X1,X2)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', killer_poorer_than_victim)).
% cnf(9,axiom,(~hates(aunt_agatha,X1)|~hates(charles,X1)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', charles_and_agatha_hate_different_people)).
% cnf(10,axiom,(X1=butler|hates(aunt_agatha,X1)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', agatha_likes_only_butler)).
% cnf(11,axiom,(richer(X1,aunt_agatha)|hates(butler,X1)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', butler_hates_poor_people)).
% cnf(12,axiom,(hates(butler,X1)|~hates(aunt_agatha,X1)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', butler_and_agatha_hate_the_same_people)).
% cnf(13,axiom,(~hates(X1,every_one_but(X1))),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', noone_hates_everyone)).
% cnf(14,axiom,(aunt_agatha!=butler),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', agatha_is_not_the_butler)).
% cnf(15,negated_conjecture,(~killed(aunt_agatha,aunt_agatha)),file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ001-2.tptp', prove_agatha_killed_herself)).
% cnf(16,derived,(aunt_agatha=someone|butler=someone|charles=someone),inference(pm,[status(thm)],[6,1,theory(equality)])).
% cnf(20,derived,(hates(someone,aunt_agatha)),inference(pm,[status(thm)],[7,2,theory(equality)])).
% cnf(21,derived,(~hates(aunt_agatha,every_one_but(butler))),inference(pm,[status(thm)],[13,12,theory(equality)])).
% cnf(23,derived,(hates(butler,X1)|~killed(X1,aunt_agatha)),inference(pm,[status(thm)],[8,11,theory(equality)])).
% cnf(24,derived,(butler=every_one_but(butler)),inference(pm,[status(thm)],[21,10,theory(equality)])).
% cnf(29,derived,(hates(charles,aunt_agatha)|someone=aunt_agatha|someone=butler),inference(pm,[status(thm)],[20,16,theory(equality)])).
% cnf(33,derived,(~hates(butler,butler)),inference(pm,[status(thm)],[13,24,theory(equality)])).
% cnf(35,derived,(hates(butler,someone)),inference(pm,[status(thm)],[23,2,theory(equality)])).
% cnf(65,derived,(someone=aunt_agatha|someone=butler|~hates(aunt_agatha,aunt_agatha)),inference(pm,[status(thm)],[9,29,theory(equality)])).
% cnf(66,derived,(someone=aunt_agatha|someone=butler|butler=aunt_agatha),inference(pm,[status(thm)],[65,10,theory(equality)])).
% cnf(67,derived,(someone=aunt_agatha|someone=butler),inference(sr,[status(thm)],[66,14,theory(equality)])).
% cnf(72,derived,(hates(butler,butler)|someone=aunt_agatha),inference(pm,[status(thm)],[35,67,theory(equality)])).
% cnf(75,derived,(someone=aunt_agatha),inference(sr,[status(thm)],[72,33,theory(equality)])).
% cnf(79,derived,(killed(aunt_agatha,aunt_agatha)),inference(rw,[status(thm)],[2,75,theory(equality)])).
% cnf(80,derived,($false),inference(sr,[status(thm)],[79,15,theory(equality)])).
% cnf(81,derived,($false),80,['proof']).
% # Proof object ends here.
% # ...of these trivial                  : 0
% # ...subsumed                          : 6
% # ...remaining for further processing  : 33
% # Other redundant clauses eleminated   : 0
% # Clauses deleted for lack of memory   : 0
% # Backward-subsumed                    : 7
% # Backward-rewritten                   : 6
% # Contextual simplify-reflections      : 1
% # Generated clauses                    : 48
% # ...of the previous two non-trivial   : 41
% # Paramodulations                      : 43
% # Factorizations                       : 5
% # Equation resolutions                 : 0
% # Current number of processed clauses  : 20
% #    Positive orientable unit clauses  : 6
% #    Positive unorientable unit clauses: 0
% #    Negative unit clauses             : 6
% #    Non-unit-clauses                  : 8
% # Current number of unprocessed clauses: 2
% # ...number of literals in the above   : 2
% # Clause-clause subsumption calls (NU) : 17
% # Rec. Clause-clause subsumption calls : 16
% # Unit Clause-clause subsumption calls : 7
% 
% # -------------------------------------------------
% # User time                : 0.010 s
% # System time              : 0.000 s
% # Total time               : 0.010 s
% # Maximum resident set size: 0 pages
% 
%------------------------------------------------------------------------------

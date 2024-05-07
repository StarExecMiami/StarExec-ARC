%------------------------------------------------------------------------------
% File       : Vampire---7.0
% Problem    : PUZ001-2 : TPTP v1.0.0
% Transform  : none
% Format     : oldtptp
% Command    : vampire -t %d %s

% Computer   : art10.cs.miami.edu
% Model      : i686 unknown
% CPU        : Intel(R) Pentium(R) 4 CPU 2.80GHz @ 2793MHz
% Memory     : 1000MB
% OS         : Linux 2.4.22-21mdk-i686-up-4GB
% CPULimit   : 600s

% Result     : Unsatisfiable 0.0s
% Output     : Refutation 0.0s
% Statistics : Number of formulae    :   29 (  36 expanded)
%              Number of clauses     :   28 (  35 expanded)
%              Depth                 :    8
%              Number of atoms       :   55 (  68 expanded)
%              Maximal clause size   :    4 (   2 average)
%              Maximal formula depth :    4 (   2 average)
%              Maximal term depth    :    2 (   1 average)
% Verified   : 

% Comments   : 
%------------------------------------------------------------------------------
%----TSTP SOLUTION
% [1, input]   lives_at_dreadsbury(someone)
cnf(1,initial,
    ( lives_at_dreadsbury(someone) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [2, input]   killed(someone,aunt_agatha)
cnf(2,initial,
    ( killed(someone,aunt_agatha) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [6, input]   ~lives_at_dreadsbury(X0) \/ X0=aunt_agatha \/ X0=butler \/ X0=charles
cnf(6,initial,
    ( ~lives_at_dreadsbury(X0) | X0=aunt_agatha | X0=butler | X0=charles ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [7, input]   ~killed(X1,X2) \/ hates(X1,X2)
cnf(7,initial,
    ( ~killed(X1,X2) | hates(X1,X2) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [8, input]   ~killed(X1,X2) \/ ~richer(X1,X2)
cnf(8,initial,
    ( ~killed(X1,X2) | ~richer(X1,X2) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [9, input]   ~hates(aunt_agatha,X0) \/ ~hates(charles,X0)
cnf(9,initial,
    ( ~hates(aunt_agatha,X0) | ~hates(charles,X0) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [10, input]   X0=butler \/ hates(aunt_agatha,X0)
cnf(10,initial,
    ( X0=butler | hates(aunt_agatha,X0) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [11, input]   richer(X0,aunt_agatha) \/ hates(butler,X0)
cnf(11,initial,
    ( richer(X0,aunt_agatha) | hates(butler,X0) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [12, input]   ~hates(aunt_agatha,X0) \/ hates(butler,X0)
cnf(12,initial,
    ( ~hates(aunt_agatha,X0) | hates(butler,X0) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [13, input]   ~hates(X0,every_one_but(X0))
cnf(13,initial,
    ( ~hates(X0,every_one_but(X0)) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [14, input]   aunt_agatha!=butler
cnf(14,initial,
    (aunt_agatha!=butler ),
    file('PUZ001-2.oldtptp',unknown),
    []).

% [15, input]   ~killed(aunt_agatha,aunt_agatha)
cnf(15,negated_conjecture,
    ( ~killed(aunt_agatha,aunt_agatha) ),
    file('PUZ001-2.oldtptp',unknown),
    []).

%-----------------------------
% [1,22->45, resolution]     someone=charles \/ someone=aunt_agatha \/ someone=butler
cnf(45,derived,
    ( someone=charles | someone=aunt_agatha | someone=butler ),
    inference(resolution,[status(thm)],[1,22]),
    [iquote('[1,22->45, resolution]')]).

% [2,7->46, resolution]     hates(someone,aunt_agatha)
cnf(46,derived,
    ( hates(someone,aunt_agatha) ),
    inference(resolution,[status(thm)],[2,7]),
    [iquote('[2,7->46, resolution]')]).

%----MISSING here, in EP proof
%cnf(21,derived,
%    ( ~ hates(aunt_agatha,every_one_but(butler)) ),
%    inference(pm,[status(thm)],[13,12,theory(equality)])).

% [11,8->16, resolution]     hates(butler,X0) \/ ~killed(X0,aunt_agatha)
cnf(16,derived,
    ( hates(butler,X0) | ~killed(X0,aunt_agatha) ),
    inference(resolution,[status(thm)],[11,8]),
    [iquote('[11,8->16, resolution]')]).

% [13,48->53, resolution]     every_one_but(butler)=butler
cnf(53,derived,
    ( every_one_but(butler)=butler ),
    inference(resolution,[status(thm)],[13,48]),
    [iquote('[13,48->53, resolution]')]).

% [46,45->50, backward superposition]     hates(charles,aunt_agatha) \/ someone=aunt_agatha \/ someone=butler
cnf(50,derived,
    ( hates(charles,aunt_agatha) | someone=aunt_agatha | someone=butler ),
    inference(backward_superposition,[status(thm)],[46,45,theory(equality)]),
    [iquote('[46,45->50, backward superposition]')]).

% [13,53->56, backward superposition]     ~hates(butler,butler)
cnf(56,derived,
    ( ~hates(butler,butler) ),
    inference(backward_superposition,[status(thm)],[13,53,theory(equality)]),
    [iquote('[13,53->56, backward superposition]')]).

% [2,24->47, resolution]     hates(butler,someone)
cnf(47,derived,
    ( hates(butler,someone) ),
    inference(resolution,[status(thm)],[2,24]),
    [iquote('[2,24->47, resolution]')]).

% [25,50->55, resolution]     ~hates(aunt_agatha,aunt_agatha) \/ someone=aunt_agatha \/ someone=butler
cnf(55,derived,
    ( ~hates(aunt_agatha,aunt_agatha) | someone=aunt_agatha | someone=butler ),
    inference(resolution,[status(thm)],[25,50]),
    [iquote('[25,50->55, resolution]')]).

% [26,55->57, resolution]     someone=aunt_agatha \/ someone=butler \/ aunt_agatha=butler
cnf(57,derived,
    ( someone=aunt_agatha | someone=butler | aunt_agatha=butler ),
    inference(resolution,[status(thm)],[26,55]),
    [iquote('[26,55->57, resolution]')]).

%----MISSING here from EP proof
%cnf(67,derived,
%    ( someone = aunt_agatha
%    | someone = butler ),
%    inference(sr,[status(thm)],[66,14,theory(equality)])).
%
%cnf(72,derived,
%    ( hates(butler,butler)
%    | someone = aunt_agatha ),
%    inference(pm,[status(thm)],[35,67,theory(equality)])).
%cnf(75,derived,
%    ( someone = aunt_agatha ),
%    inference(sr,[status(thm)],[72,33,theory(equality)])).
%    
%cnf(79,derived, 
%    ( killed(aunt_agatha,aunt_agatha) ),
%    inference(rw,[status(thm)],[2,75,theory(equality)])).

% [15,2,57->60, backward superposition, forward subsumption resolution]     someone=butler \/ aunt_agatha=butler
cnf(60,derived,
    ( someone=butler | aunt_agatha=butler ),
    inference(backward_superposition__forward_subsumption_resolution,[status(thm)],[15,2,57,theory(equality)]),
    [iquote('[15,2,57->60, backward superposition, forward subsumption resolution]')]).

% [10->26, preprocessing]     hates(aunt_agatha,X1) \/ X1=butler
cnf(26,derived,
    ( hates(aunt_agatha,X1) | X1=butler ),
    inference(preprocessing,[status(thm)],[10]),
    [iquote('[10->26, preprocessing]')]).

cnf(48,derived,
    ( hates(butler,X1) | X1=butler ),
    inference(resolution,[status(thm)],[26,12]),
    [iquote('[26,12->48, resolution]')]).

% [16->24, preprocessing]     ~killed(X1,aunt_agatha) \/ hates(butler,X1)
cnf(24,derived,
    ( ~killed(X1,aunt_agatha) | hates(butler,X1) ),
    inference(preprocessing,[status(thm)],[16]),
    [iquote('[16->24, preprocessing]')]).

% [9->25, preprocessing]     ~hates(charles,X1) \/ ~hates(aunt_agatha,X1)
cnf(25,derived,
    ( ~hates(charles,X1) | ~hates(aunt_agatha,X1) ),
    inference(preprocessing,[status(thm)],[9]),
    [iquote('[9->25, preprocessing]')]).

% [6->22, preprocessing]     ~lives_at_dreadsbury(X1) \/ X1=charles \/ X1=aunt_agatha \/ X1=butler
cnf(22,derived,
    ( ~lives_at_dreadsbury(X1) | X1=charles | X1=aunt_agatha | X1=butler ),
    inference(preprocessing,[status(thm)],[6]),
    [iquote('[6->22, preprocessing]')]).

% [56,47,60->61, backward superposition, forward subsumption resolution]     aunt_agatha=butler
cnf(61,derived,
    ( aunt_agatha=butler ),
    inference(backward_superposition__forward_subsumption_resolution,[status(thm)],[56,47,60,theory(equality)]),
    [iquote('[56,47,60->61, backward superposition, forward subsumption resolution]')]).

% [14,61->71, backward demodulation]     #
cnf(71,derived,
    ( $false ),
    inference(backward_demodulation,[status(thm)],[14,61,theory(equality)]),
    [iquote('[14,61->71, backward demodulation]')]).

%------------------------------------------------------------------------------


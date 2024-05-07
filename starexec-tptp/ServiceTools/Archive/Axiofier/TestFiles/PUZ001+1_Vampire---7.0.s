%------------------------------------------------------------------------------
% File       : Vampire---7.0
% Problem    : PUZ001+1 : TPTP v2.0.0
% Transform  : none
% Format     : oldtptp
% Command    : vampire -t %d %s

% Computer   : art09.cs.miami.edu
% Model      : i686 unknown
% CPU        : Intel(R) Pentium(R) 4 CPU 2.80GHz @ 2793MHz
% Memory     : 1000MB
% OS         : Linux 2.4.22-21mdk-i686-up-4GB
% CPULimit   : 600s

% Result     : Theorem 0.0s
% Output     : Refutation 0.0s
% Statistics : Number of formulae    :   58 (  74 expanded)
%              Number of clauses     :   39 (  45 expanded)
%              Depth                 :   11
%              Number of atoms       :  114 ( 143 expanded)
%              Maximal clause size   :    4 (   3 average)
%              Maximal formula depth :    5 (   3 average)
%              Maximal term depth    :    2 (   1 average)
% Verified   : 

% Comments   : 
%------------------------------------------------------------------------------
%----TSTP SOLUTION
% [13, input]   ~agatha=butler
fof(13,initial,
    ( ~agatha=butler ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [12, input]   (! X0)(? X1)~hates(X0,X1)
fof(12,initial,
    (! [X0] : ? [X1] : ~hates(X0,X1) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [12->31, skolemization]     ~hates(X0,sk1(X0))
cnf(31,derived,
    ( ~hates(X0,sk1(X0)) ),
    inference(skolemization,[status(sat)],[12]),
    [iquote('[12->31, skolemization]')]).

% [31->44, cnf transformation]     ~hates(X0,sk1(X0))
cnf(44,derived,
    ( ~hates(X0,sk1(X0)) ),
    inference(cnf_transformation,[status(thm)],[31]),
    [iquote('[31->44, cnf transformation]')]).

% [11, input]   (! X0)(hates(agatha,X0) => hates(butler,X0))
fof(11,initial,
    (! [X0] : (hates(agatha,X0) => hates(butler,X0)) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [11->30, skolemization]     ~hates(agatha,X0) \/ hates(butler,X0)
cnf(30,derived,
    ( ~hates(agatha,X0) | hates(butler,X0) ),
    inference(skolemization,[status(sat)],[11]),
    [iquote('[11->30, skolemization]')]).

% [30->43, cnf transformation]     hates(butler,X0) \/ ~hates(agatha,X0)
cnf(43,derived,
    ( hates(butler,X0) | ~hates(agatha,X0) ),
    inference(cnf_transformation,[status(thm)],[30]),
    [iquote('[30->43, cnf transformation]')]).

% [43->51, preprocessing]     ~hates(agatha,X1) \/ hates(butler,X1)
cnf(51,derived,
    ( ~hates(agatha,X1) | hates(butler,X1) ),
    inference(preprocessing,[status(thm)],[43]),
    [iquote('[43->51, preprocessing]')]).

% [9, input]   (! X0)(~X0=butler => hates(agatha,X0))
fof(9,initial,
    (! [X0] : (~X0=butler => hates(agatha,X0)) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [9->26, skolemization]     X0=butler \/ hates(agatha,X0)
cnf(26,derived,
    ( X0=butler | hates(agatha,X0) ),
    inference(skolemization,[status(sat)],[9]),
    [iquote('[9->26, skolemization]')]).

% [26->41, cnf transformation]     hates(agatha,X0) \/ X0=butler
cnf(41,derived,
    ( hates(agatha,X0) | X0=butler ),
    inference(cnf_transformation,[status(thm)],[26]),
    [iquote('[26->41, cnf transformation]')]).

% [51,41->77, resolution]     hates(butler,X1) \/ X1=butler
cnf(77,derived,
    ( hates(butler,X1) | X1=butler ),
    inference(resolution,[status(thm)],[51,41]),
    [iquote('[51,41->77, resolution]')]).

% [44,77->83, resolution]     sk1(butler)=butler
cnf(83,derived,
    ( sk1(butler)=butler ),
    inference(resolution,[status(thm)],[44,77]),
    [iquote('[44,77->83, resolution]')]).

% [44,83->84, backward superposition]     ~hates(butler,butler)
cnf(84,derived,
    ( ~hates(butler,butler) ),
    inference(backward_superposition,[status(thm)],[44,83,theory(equality)]),
    [iquote('[44,83->84, backward superposition]')]).

% [10, input]   (! X0)(~richer(X0,agatha) => hates(butler,X0))
fof(10,initial,
    (! [X0] : (~richer(X0,agatha) => hates(butler,X0)) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [10->28, skolemization]     richer(X0,agatha) \/ hates(butler,X0)
cnf(28,derived,
    ( richer(X0,agatha) | hates(butler,X0) ),
    inference(skolemization,[status(sat)],[10]),
    [iquote('[10->28, skolemization]')]).

% [28->42, cnf transformation]     hates(butler,X0) \/ richer(X0,agatha)
cnf(42,derived,
    ( hates(butler,X0) | richer(X0,agatha) ),
    inference(cnf_transformation,[status(thm)],[28]),
    [iquote('[28->42, cnf transformation]')]).

% [7, input]   (! X0 X1)(killed(X0,X1) => ~richer(X0,X1))
fof(7,initial,
    (! [X0,X1] : (killed(X0,X1) => ~richer(X0,X1)) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [7->22, skolemization]     ~killed(X0,X1) \/ ~richer(X0,X1)
cnf(22,derived,
    ( ~killed(X0,X1) | ~richer(X0,X1) ),
    inference(skolemization,[status(sat)],[7]),
    [iquote('[7->22, skolemization]')]).

% [22->39, cnf transformation]     ~richer(X0,X1) \/ ~killed(X0,X1)
cnf(39,derived,
    ( ~richer(X0,X1) | ~killed(X0,X1) ),
    inference(cnf_transformation,[status(thm)],[22]),
    [iquote('[22->39, cnf transformation]')]).

% [42,39->47, resolution]     hates(butler,X0) \/ ~killed(X0,agatha)
cnf(47,derived,
    ( hates(butler,X0) | ~killed(X0,agatha) ),
    inference(resolution,[status(thm)],[42,39]),
    [iquote('[42,39->47, resolution]')]).

% [47->54, preprocessing]     ~killed(X1,agatha) \/ hates(butler,X1)
cnf(54,derived,
    ( ~killed(X1,agatha) | hates(butler,X1) ),
    inference(preprocessing,[status(thm)],[47]),
    [iquote('[47->54, preprocessing]')]).

% [1, input]   (? X0)(lives(X0) & killed(X0,agatha))
fof(1,initial,
    (? [X0] : (lives(X0) & killed(X0,agatha)) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [1->33, cnf transformation]     killed(sk0,agatha)
cnf(33,derived,
    ( killed(sk0,agatha) ),
    inference(cnf_transformation,[status(thm)],[1]),
    [iquote('[1->33, cnf transformation]')]).

% [54,33->79, resolution]     hates(butler,sk0)
cnf(79,derived,
    ( hates(butler,sk0) ),
    inference(resolution,[status(thm)],[54,33]),
    [iquote('[54,33->79, resolution]')]).

% [8, input]   (! X0)(hates(agatha,X0) => ~hates(charles,X0))
fof(8,initial,
    (! [X0] : (hates(agatha,X0) => ~hates(charles,X0)) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [8->24, skolemization]     ~hates(agatha,X0) \/ ~hates(charles,X0)
cnf(24,derived,
    ( ~hates(agatha,X0) | ~hates(charles,X0) ),
    inference(skolemization,[status(sat)],[8]),
    [iquote('[8->24, skolemization]')]).

% [24->40, cnf transformation]     ~hates(charles,X0) \/ ~hates(agatha,X0)
cnf(40,derived,
    ( ~hates(charles,X0) | ~hates(agatha,X0) ),
    inference(cnf_transformation,[status(thm)],[24]),
    [iquote('[24->40, cnf transformation]')]).

% [40->53, preprocessing]     ~hates(agatha,X1) \/ ~hates(charles,X1)
cnf(53,derived,
    ( ~hates(agatha,X1) | ~hates(charles,X1) ),
    inference(preprocessing,[status(thm)],[40]),
    [iquote('[40->53, preprocessing]')]).

% [41,53->78, resolution]     ~hates(charles,X1) \/ X1=butler
cnf(78,derived,
    ( ~hates(charles,X1) | X1=butler ),
    inference(resolution,[status(thm)],[41,53]),
    [iquote('[41,53->78, resolution]')]).

% [6, input]   (! X0 X1)(killed(X0,X1) => hates(X0,X1))
fof(6,initial,
    (! [X0,X1] : (killed(X0,X1) => hates(X0,X1)) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [6->20, skolemization]     ~killed(X0,X1) \/ hates(X0,X1)
cnf(20,derived,
    ( ~killed(X0,X1) | hates(X0,X1) ),
    inference(skolemization,[status(sat)],[6]),
    [iquote('[6->20, skolemization]')]).

% [20->38, cnf transformation]     hates(X0,X1) \/ ~killed(X0,X1)
cnf(38,derived,
    ( hates(X0,X1) | ~killed(X0,X1) ),
    inference(cnf_transformation,[status(thm)],[20]),
    [iquote('[20->38, cnf transformation]')]).

% [38->55, preprocessing]     ~killed(X1,X2) \/ hates(X1,X2)
cnf(55,derived,
    ( ~killed(X1,X2) | hates(X1,X2) ),
    inference(preprocessing,[status(thm)],[38]),
    [iquote('[38->55, preprocessing]')]).

% [55,33->80, resolution]     hates(sk0,agatha)
cnf(80,derived,
    ( hates(sk0,agatha) ),
    inference(resolution,[status(thm)],[55,33]),
    [iquote('[55,33->80, resolution]')]).

% [14, input]   ~killed(agatha,agatha)
cnf(14,negated_conjecture,
    ( ~killed(agatha,agatha) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [14->46, cnf transformation]     ~killed(agatha,agatha)
cnf(46,derived,
    ( ~killed(agatha,agatha) ),
    inference(cnf_transformation,[status(thm)],[14]),
    [iquote('[14->46, cnf transformation]')]).

% [5, input]   (! X0)(lives(X0) => X0=agatha \/ X0=butler \/ X0=charles)
fof(5,initial,
    (! [X0] : (lives(X0) => X0=agatha | X0=butler | X0=charles) ),
    file('PUZ001+1.oldtptp',unknown),
    []).

% [5->18, skolemization]     ~lives(X0) \/ X0=agatha \/ X0=butler \/ X0=charles
cnf(18,derived,
    ( ~lives(X0) | X0=agatha | X0=butler | X0=charles ),
    inference(skolemization,[status(sat)],[5]),
    [iquote('[5->18, skolemization]')]).

% [18->37, cnf transformation]     X0=charles \/ X0=butler \/ X0=agatha \/ ~lives(X0)
cnf(37,derived,
    ( X0=charles | X0=butler | X0=agatha | ~lives(X0) ),
    inference(cnf_transformation,[status(thm)],[18]),
    [iquote('[18->37, cnf transformation]')]).

% [37->56, preprocessing]     ~lives(X1) \/ X1=agatha \/ X1=charles \/ X1=butler
cnf(56,derived,
    ( ~lives(X1) | X1=agatha | X1=charles | X1=butler ),
    inference(preprocessing,[status(thm)],[37]),
    [iquote('[37->56, preprocessing]')]).

% [1->32, cnf transformation]     lives(sk0)
cnf(32,derived,
    ( lives(sk0) ),
    inference(cnf_transformation,[status(thm)],[1]),
    [iquote('[1->32, cnf transformation]')]).

% [56,32->81, resolution]     sk0=agatha \/ sk0=charles \/ sk0=butler
cnf(81,derived,
    ( sk0=agatha | sk0=charles | sk0=butler ),
    inference(resolution,[status(thm)],[56,32]),
    [iquote('[56,32->81, resolution]')]).

% [46,33,81->87, backward superposition, forward subsumption resolution]     sk0=charles \/ sk0=butler
cnf(87,derived,
    ( sk0=charles | sk0=butler ),
    inference(backward_superposition__forward_subsumption_resolution,[status(thm)],[46,33,81,theory(equality)]),
    [iquote('[46,33,81->87, backward superposition, forward subsumption resolution]')]).

% [80,87->88, backward superposition]     hates(charles,agatha) \/ sk0=butler
cnf(88,derived,
    ( hates(charles,agatha) | sk0=butler ),
    inference(backward_superposition,[status(thm)],[80,87,theory(equality)]),
    [iquote('[80,87->88, backward superposition]')]).

% [78,88->91, resolution]     sk0=butler \/ agatha=butler
cnf(91,derived,
    ( sk0=butler | agatha=butler ),
    inference(resolution,[status(thm)],[78,88]),
    [iquote('[78,88->91, resolution]')]).

% [84,79,91->93, backward superposition, forward subsumption resolution]     agatha=butler
cnf(93,derived,
    ( agatha=butler ),
    inference(backward_superposition__forward_subsumption_resolution,[status(thm)],[84,79,91,theory(equality)]),
    [iquote('[84,79,91->93, backward superposition, forward subsumption resolution]')]).

% [13,93->98, backward demodulation]     #
cnf(98,derived,
    ( $false ),
    inference(backward_demodulation,[status(thm)],[13,93,theory(equality)]),
    [iquote('[13,93->98, backward demodulation]')]).

%------------------------------------------------------------------------------
%----ORIGINAL SYSTEM OUTPUT
% Refutation found. Thanks to Tanya!
% =========== Refutation ==========
% *********** [13, input] ***********
% ~agatha=butler
% *********** [13->45, cnf transformation] ***********
%   ~agatha=butler
% -----------------------------
%   agatha!=butler
% *********** [12, input] ***********
% (! X0)(? X1)~hates(X0,X1)
% *********** [12->31, skolemization] ***********
%   (! X0)(? X1)~hates(X0,X1)
% -----------------------------
%   ~hates(X0,sk1(X0))
% *********** [31->44, cnf transformation] ***********
%   ~hates(X0,sk1(X0))
% -----------------------------
%   ~hates(X0,sk1(X0))
% *********** [11, input] ***********
% (! X0)(hates(agatha,X0) => hates(butler,X0))
% *********** [11->29, ENNF transformation] ***********
%   (! X0)(hates(agatha,X0) => hates(butler,X0))
% -----------------------------
%   (! X0)(~hates(agatha,X0) \/ hates(butler,X0))
% *********** [29->30, skolemization] ***********
%   (! X0)(~hates(agatha,X0) \/ hates(butler,X0))
% -----------------------------
%   ~hates(agatha,X0) \/ hates(butler,X0)
% *********** [30->43, cnf transformation] ***********
%   ~hates(agatha,X0) \/ hates(butler,X0)
% -----------------------------
%   hates(butler,X0) \/ ~hates(agatha,X0)
% *********** [43->51, preprocessing] ***********
%   hates(butler,X0) \/ ~hates(agatha,X0)
% -----------------------------
%   ~hates(agatha,X1) \/ hates(butler,X1)
% *********** [9, input] ***********
% (! X0)(~X0=butler => hates(agatha,X0))
% *********** [9->25, ENNF transformation] ***********
%   (! X0)(~X0=butler => hates(agatha,X0))
% -----------------------------
%   (! X0)(X0=butler \/ hates(agatha,X0))
% *********** [25->26, skolemization] ***********
%   (! X0)(X0=butler \/ hates(agatha,X0))
% -----------------------------
%   X0=butler \/ hates(agatha,X0)
% *********** [26->41, cnf transformation] ***********
%   X0=butler \/ hates(agatha,X0)
% -----------------------------
%   hates(agatha,X0) \/ X0=butler
% *********** [51,41->77, resolution] ***********
%   ~hates(agatha,X1) \/ hates(butler,X1)
%   hates(agatha,X0) \/ X0=butler
% -----------------------------
%   hates(butler,X1) \/ X1=butler
% *********** [44,77->83, resolution] ***********
%   ~hates(X0,sk1(X0))
%   hates(butler,X1) \/ X1=butler
% -----------------------------
%   sk1(butler)=butler
% *********** [44,83->84, backward superposition] ***********
%   ~hates(X0,sk1(X0))
%   sk1(butler)=butler
% -----------------------------
%   ~hates(butler,butler)
% *********** [10, input] ***********
% (! X0)(~richer(X0,agatha) => hates(butler,X0))
% *********** [10->27, ENNF transformation] ***********
%   (! X0)(~richer(X0,agatha) => hates(butler,X0))
% -----------------------------
%   (! X0)(richer(X0,agatha) \/ hates(butler,X0))
% *********** [27->28, skolemization] ***********
%   (! X0)(richer(X0,agatha) \/ hates(butler,X0))
% -----------------------------
%   richer(X0,agatha) \/ hates(butler,X0)
% *********** [28->42, cnf transformation] ***********
%   richer(X0,agatha) \/ hates(butler,X0)
% -----------------------------
%   hates(butler,X0) \/ richer(X0,agatha)
% *********** [7, input] ***********
% (! X0 X1)(killed(X0,X1) => ~richer(X0,X1))
% *********** [7->21, ENNF transformation] ***********
%   (! X0 X1)(killed(X0,X1) => ~richer(X0,X1))
% -----------------------------
%   (! X0 X1)(~killed(X0,X1) \/ ~richer(X0,X1))
% *********** [21->22, skolemization] ***********
%   (! X0 X1)(~killed(X0,X1) \/ ~richer(X0,X1))
% -----------------------------
%   ~killed(X0,X1) \/ ~richer(X0,X1)
% *********** [22->39, cnf transformation] ***********
%   ~killed(X0,X1) \/ ~richer(X0,X1)
% -----------------------------
%   ~richer(X0,X1) \/ ~killed(X0,X1)
% *********** [42,39->47, resolution] ***********
%   hates(butler,X0) \/ richer(X0,agatha)
%   ~richer(X0,X1) \/ ~killed(X0,X1)
% -----------------------------
%   hates(butler,X0) \/ ~killed(X0,agatha)
% *********** [47->54, preprocessing] ***********
%   hates(butler,X0) \/ ~killed(X0,agatha)
% -----------------------------
%   ~killed(X1,agatha) \/ hates(butler,X1)
% *********** [1, input] ***********
% (? X0)(lives(X0) & killed(X0,agatha))
% *********** [1->15, skolemization] ***********
%   (? X0)(lives(X0) & killed(X0,agatha))
% -----------------------------
%   lives(sk0) & killed(sk0,agatha)
% *********** [15->33, cnf transformation] ***********
%   lives(sk0) & killed(sk0,agatha)
% -----------------------------
%   killed(sk0,agatha)
% *********** [54,33->79, resolution] ***********
%   ~killed(X1,agatha) \/ hates(butler,X1)
%   killed(sk0,agatha)
% -----------------------------
%   hates(butler,sk0)
% *********** [8, input] ***********
% (! X0)(hates(agatha,X0) => ~hates(charles,X0))
% *********** [8->23, ENNF transformation] ***********
%   (! X0)(hates(agatha,X0) => ~hates(charles,X0))
% -----------------------------
%   (! X0)(~hates(agatha,X0) \/ ~hates(charles,X0))
% *********** [23->24, skolemization] ***********
%   (! X0)(~hates(agatha,X0) \/ ~hates(charles,X0))
% -----------------------------
%   ~hates(agatha,X0) \/ ~hates(charles,X0)
% *********** [24->40, cnf transformation] ***********
%   ~hates(agatha,X0) \/ ~hates(charles,X0)
% -----------------------------
%   ~hates(charles,X0) \/ ~hates(agatha,X0)
% *********** [40->53, preprocessing] ***********
%   ~hates(charles,X0) \/ ~hates(agatha,X0)
% -----------------------------
%   ~hates(agatha,X1) \/ ~hates(charles,X1)
% *********** [41,53->78, resolution] ***********
%   hates(agatha,X0) \/ X0=butler
%   ~hates(agatha,X1) \/ ~hates(charles,X1)
% -----------------------------
%   ~hates(charles,X1) \/ X1=butler
% *********** [6, input] ***********
% (! X0 X1)(killed(X0,X1) => hates(X0,X1))
% *********** [6->19, ENNF transformation] ***********
%   (! X0 X1)(killed(X0,X1) => hates(X0,X1))
% -----------------------------
%   (! X0 X1)(~killed(X0,X1) \/ hates(X0,X1))
% *********** [19->20, skolemization] ***********
%   (! X0 X1)(~killed(X0,X1) \/ hates(X0,X1))
% -----------------------------
%   ~killed(X0,X1) \/ hates(X0,X1)
% *********** [20->38, cnf transformation] ***********
%   ~killed(X0,X1) \/ hates(X0,X1)
% -----------------------------
%   hates(X0,X1) \/ ~killed(X0,X1)
% *********** [38->55, preprocessing] ***********
%   hates(X0,X1) \/ ~killed(X0,X1)
% -----------------------------
%   ~killed(X1,X2) \/ hates(X1,X2)
% *********** [55,33->80, resolution] ***********
%   ~killed(X1,X2) \/ hates(X1,X2)
%   killed(sk0,agatha)
% -----------------------------
%   hates(sk0,agatha)
% *********** [14, input] ***********
% ~killed(agatha,agatha)
% *********** [14->46, cnf transformation] ***********
%   ~killed(agatha,agatha)
% -----------------------------
%   ~killed(agatha,agatha)
% *********** [5, input] ***********
% (! X0)(lives(X0) => X0=agatha \/ X0=butler \/ X0=charles)
% *********** [5->16, ENNF transformation] ***********
%   (! X0)(lives(X0) => X0=agatha \/ X0=butler \/ X0=charles)
% -----------------------------
%   (! X0)(~lives(X0) \/ (X0=agatha \/ X0=butler \/ X0=charles))
% *********** [16->17, flattening] ***********
%   (! X0)(~lives(X0) \/ (X0=agatha \/ X0=butler \/ X0=charles))
% -----------------------------
%   (! X0)(~lives(X0) \/ X0=agatha \/ X0=butler \/ X0=charles)
% *********** [17->18, skolemization] ***********
%   (! X0)(~lives(X0) \/ X0=agatha \/ X0=butler \/ X0=charles)
% -----------------------------
%   ~lives(X0) \/ X0=agatha \/ X0=butler \/ X0=charles
% *********** [18->37, cnf transformation] ***********
%   ~lives(X0) \/ X0=agatha \/ X0=butler \/ X0=charles
% -----------------------------
%   X0=charles \/ X0=butler \/ X0=agatha \/ ~lives(X0)
% *********** [37->56, preprocessing] ***********
%   X0=charles \/ X0=butler \/ X0=agatha \/ ~lives(X0)
% -----------------------------
%   ~lives(X1) \/ X1=agatha \/ X1=charles \/ X1=butler
% *********** [15->32, cnf transformation] ***********
%   lives(sk0) & killed(sk0,agatha)
% -----------------------------
%   lives(sk0)
% *********** [56,32->81, resolution] ***********
%   ~lives(X1) \/ X1=agatha \/ X1=charles \/ X1=butler
%   lives(sk0)
% -----------------------------
%   sk0=agatha \/ sk0=charles \/ sk0=butler
% *********** [46,33,81->87, backward superposition, forward subsumption resolution] ***********
%   ~killed(agatha,agatha)
%   killed(sk0,agatha)
%   sk0=agatha \/ sk0=charles \/ sk0=butler
% -----------------------------
%   sk0=charles \/ sk0=butler
% *********** [80,87->88, backward superposition] ***********
%   hates(sk0,agatha)
%   sk0=charles \/ sk0=butler
% -----------------------------
%   hates(charles,agatha) \/ sk0=butler
% *********** [78,88->91, resolution] ***********
%   ~hates(charles,X1) \/ X1=butler
%   hates(charles,agatha) \/ sk0=butler
% -----------------------------
%   sk0=butler \/ agatha=butler
% *********** [84,79,91->93, backward superposition, forward subsumption resolution] ***********
%   ~hates(butler,butler)
%   hates(butler,sk0)
%   sk0=butler \/ agatha=butler
% -----------------------------
%   agatha=butler
% *********** [45,93->98, backward demodulation] ***********
%   agatha!=butler
%   agatha=butler
% -----------------------------
%   #
% ======= End of refutation =======
% =========== Statistics ==========
% version: 7 Civatateo (CASC J2)
% === General:
% time: 0s
% memory: 3.9Mb
% termination reason: refutation found
% === Generating inferences:
% resolution: 15
% forward_superposition: 6
% backward_superposition: 17
% === Simplifying inferences:
% equational_tautology: 15
% forward_subsumption: 7
% forward_subsumption_resolution: 2
% backward_subsumption: 5
% backward_demodulation: 7
% === Generated clauses:
% total: 73
% discarded_as_redundant: 22
% === Retained clauses:
% total: 51
% selected: 28
% currently_active: 19
% currently_passive: 5
% ======= End of statistics =======
% 
%------------------------------------------------------------------------------

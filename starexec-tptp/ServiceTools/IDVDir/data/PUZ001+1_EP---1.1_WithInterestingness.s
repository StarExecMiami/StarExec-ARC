cnf(77,plain,
    ( ~ hates(butler,butler) ),
    inference(spm,[status(thm)],[51,72,theory(equality)]),
    [interesting(1.00),obviousness(1.00),complexity(1.00),intensity(0.65),surprisingness(1.00),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(ignored)]).

cnf(96,negated_conjecture,
    ( esk1_0 = butler ),
    inference(sr,[status(thm)],[95,52,theory(equality)]),
    [interesting(1.00),obviousness(0.75),complexity(0.75),intensity(1.00),surprisingness(0.84),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(1.00)]).

cnf(58,plain,
    ( hates(butler,X1)
    | butler = X1 ),
    inference(spm,[status(thm)],[48,42,theory(equality)]),
    [interesting(0.95),obviousness(0.00),complexity(0.67),intensity(0.87),surprisingness(0.84),adaptivity(1.00),focus(ignored),weight(0.83),usefulness(1.00)]).

cnf(72,plain,
    ( butler = esk2_1(butler) ),
    inference(spm,[status(thm)],[51,58,theory(equality)]),
    [interesting(0.83),obviousness(0.50),complexity(0.67),intensity(0.87),surprisingness(0.78),adaptivity(0.00),focus(ignored),weight(0.83),usefulness(1.00)]).

cnf(97,plain,
    ( hates(butler,butler) ),
    inference(rw,[status(thm)],[75,96,theory(equality)]),
    [interesting(0.81),obviousness(1.00),complexity(1.00),intensity(0.63),surprisingness(1.00),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(0.00)]).

cnf(75,plain,
    ( hates(butler,esk1_0) ),
    inference(spm,[status(thm)],[57,23,theory(equality)]),
    [interesting(0.78),obviousness(0.50),complexity(0.67),intensity(0.87),surprisingness(0.75),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(ignored)]).

cnf(59,plain,
    ( butler = X1
    | ~ hates(charles,X1) ),
    inference(spm,[status(thm)],[39,42,theory(equality)]),
    [interesting(0.76),obviousness(0.00),complexity(0.33),intensity(1.00),surprisingness(0.54),adaptivity(1.00),focus(ignored),weight(0.83),usefulness(ignored)]).

cnf(57,plain,
    ( hates(butler,X1)
    | ~ killed(X1,agatha) ),
    inference(spm,[status(thm)],[36,45,theory(equality)]),
    [interesting(0.74),obviousness(0.00),complexity(0.33),intensity(0.48),surprisingness(0.55),adaptivity(1.00),focus(ignored),weight(0.83),usefulness(1.00)]).

cnf(95,negated_conjecture,
    ( butler = agatha
    | esk1_0 = butler ),
    inference(spm,[status(thm)],[59,84,theory(equality)]),
    [interesting(0.59),obviousness(0.67),complexity(0.50),intensity(0.47),surprisingness(0.67),adaptivity(0.00),focus(ignored),weight(0.50),usefulness(1.00)]).

cnf(54,plain,
    ( hates(esk1_0,agatha) ),
    inference(spm,[status(thm)],[33,23,theory(equality)]),
    [interesting(0.58),obviousness(0.00),complexity(0.67),intensity(0.55),surprisingness(0.78),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(ignored)]).

cnf(80,negated_conjecture,
    ( esk1_0 = charles
    | esk1_0 = butler ),
    inference(csr,[status(thm)],[66,61]),
    [interesting(0.42),obviousness(0.33),complexity(0.50),intensity(0.22),surprisingness(0.60),adaptivity(0.00),focus(ignored),weight(0.50),usefulness(1.00)]).

cnf(84,negated_conjecture,
    ( hates(charles,agatha)
    | esk1_0 = butler ),
    inference(spm,[status(thm)],[54,80,theory(equality)]),
    [interesting(0.23),obviousness(0.50),complexity(0.00),intensity(0.48),surprisingness(0.00),adaptivity(0.00),focus(ignored),weight(0.50),usefulness(1.00)]).

cnf(56,plain,
    ( agatha = esk1_0
    | butler = esk1_0
    | charles = esk1_0 ),
    inference(spm,[status(thm)],[30,24,theory(equality)]),
    [interesting(0.08),obviousness(0.00),complexity(0.00),intensity(0.00),surprisingness(0.16),adaptivity(0.00),focus(ignored),weight(0.00),usefulness(1.00)]).

cnf(66,negated_conjecture,
    ( esk1_0 = charles
    | esk1_0 = butler
    | ~ killed(esk1_0,esk1_0) ),
    inference(spm,[status(thm)],[53,56,theory(equality)]),
    [interesting(0.01),obviousness(0.08),complexity(0.25),intensity(0.04),surprisingness(0.26),adaptivity(0.00),focus(ignored),weight(0.00),usefulness(1.00)]).

cnf(61,plain,
    ( killed(esk1_0,esk1_0)
    | esk1_0 = charles
    | esk1_0 = butler ),
    inference(spm,[status(thm)],[23,56,theory(equality)]),
    [interesting(0.00),obviousness(0.50),complexity(0.00),intensity(0.16),surprisingness(0.00),adaptivity(0.00),focus(ignored),weight(0.00),usefulness(ignored)]).

cnf(98,plain,
    ( $false ),
    inference(sr,[status(thm)],[97,77,theory(equality)]),
    [interesting(0.00)]).

cnf(99,plain,
    ( $false ),
    98,
    [proof,interesting(0.00)]).

cnf(36,plain,
    ( ~ richer(X1,X2)
    | ~ killed(X1,X2) ),
    inference(split_conjunct,[status(thm)],[35]),
    [interesting(-0.03),obviousness(0.19),complexity(0.75),intensity(0.22),surprisingness(0.91),adaptivity(1.00),focus(1.00),weight(0.88),usefulness(1.00)]).

cnf(51,plain,
    ( ~ hates(X1,esk2_1(X1)) ),
    inference(split_conjunct,[status(thm)],[50]),
    [interesting(-0.03),obviousness(0.19),complexity(0.75),intensity(0.22),surprisingness(0.87),adaptivity(1.00),focus(1.00),weight(0.88),usefulness(1.00)]).

cnf(33,plain,
    ( hates(X1,X2)
    | ~ killed(X1,X2) ),
    inference(split_conjunct,[status(thm)],[32]),
    [interesting(-0.05),obviousness(0.12),complexity(0.75),intensity(0.22),surprisingness(0.89),adaptivity(1.00),focus(1.00),weight(0.88),usefulness(1.00)]).

cnf(39,plain,
    ( ~ hates(charles,X1)
    | ~ hates(agatha,X1) ),
    inference(split_conjunct,[status(thm)],[38]),
    [interesting(-0.19),obviousness(0.19),complexity(0.50),intensity(0.22),surprisingness(0.73),adaptivity(1.00),focus(1.00),weight(0.62),usefulness(1.00)]).

cnf(48,plain,
    ( hates(butler,X1)
    | ~ hates(agatha,X1) ),
    inference(split_conjunct,[status(thm)],[47]),
    [interesting(-0.19),obviousness(0.12),complexity(0.50),intensity(0.22),surprisingness(0.82),adaptivity(1.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(49,plain,(
    ! [X3] :
    ? [X4] : ~ hates(X3,X4) ),
    inference(variable_rename,[status(thm)],[19]),
    [interesting(-0.19),obviousness(0.06),complexity(1.00),intensity(0.22),surprisingness(1.00),adaptivity(0.00),focus(1.00),weight(1.00),usefulness(1.00)]).

fof(19,plain,(
    ! [X1] :
    ? [X2] : ~ hates(X1,X2) ),
    inference(fof_simplification,[status(thm)],[12,theory(equality)]),
    [interesting(-0.20),obviousness(0.00),complexity(1.00),intensity(0.22),surprisingness(1.00),adaptivity(0.00),focus(1.00),weight(1.00),usefulness(1.00)]).

fof(35,plain,(
    ! [X3,X4] :
      ( ~ killed(X3,X4)
      | ~ richer(X3,X4) ) ),
    inference(variable_rename,[status(thm)],[34]),
    [interesting(-0.29),obviousness(0.12),complexity(0.75),intensity(0.22),surprisingness(0.91),adaptivity(0.00),focus(1.00),weight(0.88),usefulness(1.00)]).

cnf(24,plain,
    ( lives(esk1_0) ),
    inference(split_conjunct,[status(thm)],[22]),
    [interesting(-0.30),obviousness(0.12),complexity(0.75),intensity(0.22),surprisingness(0.87),adaptivity(0.00),focus(1.00),weight(0.88),usefulness(1.00)]).

fof(50,plain,(
    ! [X3] : ~ hates(X3,esk2_1(X3)) ),
    inference(skolemize,[status(esa)],[49]),
    [interesting(-0.30),obviousness(0.12),complexity(0.75),intensity(0.22),surprisingness(0.87),adaptivity(0.00),focus(1.00),weight(0.88),usefulness(1.00)]).

fof(32,plain,(
    ! [X3,X4] :
      ( ~ killed(X3,X4)
      | hates(X3,X4) ) ),
    inference(variable_rename,[status(thm)],[31]),
    [interesting(-0.31),obviousness(0.06),complexity(0.75),intensity(0.22),surprisingness(0.89),adaptivity(0.00),focus(1.00),weight(0.88),usefulness(1.00)]).

fof(34,plain,(
    ! [X1,X2] :
      ( ~ killed(X1,X2)
      | ~ richer(X1,X2) ) ),
    inference(fof_nnf,[status(thm)],[16]),
    [interesting(-0.31),obviousness(0.06),complexity(0.75),intensity(0.22),surprisingness(0.91),adaptivity(0.00),focus(1.00),weight(0.88),usefulness(1.00)]).

cnf(42,plain,
    ( hates(agatha,X1)
    | X1 = butler ),
    inference(split_conjunct,[status(thm)],[41]),
    [interesting(-0.31),obviousness(0.12),complexity(0.25),intensity(0.22),surprisingness(0.59),adaptivity(1.00),focus(1.00),weight(0.62),usefulness(1.00)]).

cnf(45,plain,
    ( hates(butler,X1)
    | richer(X1,agatha) ),
    inference(split_conjunct,[status(thm)],[44]),
    [interesting(-0.31),obviousness(0.19),complexity(0.25),intensity(0.22),surprisingness(0.49),adaptivity(1.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(16,plain,(
    ! [X1,X2] :
      ( killed(X1,X2)
     => ~ richer(X1,X2) ) ),
    inference(fof_simplification,[status(thm)],[7,theory(equality)]),
    [interesting(-0.32),obviousness(0.00),complexity(0.75),intensity(0.22),surprisingness(0.91),adaptivity(0.00),focus(1.00),weight(0.88),usefulness(1.00)]).

fof(31,plain,(
    ! [X1,X2] :
      ( ~ killed(X1,X2)
      | hates(X1,X2) ) ),
    inference(fof_nnf,[status(thm)],[6]),
    [interesting(-0.33),obviousness(0.00),complexity(0.75),intensity(0.22),surprisingness(0.89),adaptivity(0.00),focus(1.00),weight(0.88),usefulness(1.00)]).

cnf(53,negated_conjecture,
    ( ~ killed(agatha,agatha) ),
    inference(split_conjunct,[status(thm)],[20]),
    [interesting(-0.37),obviousness(0.04),complexity(0.80),intensity(0.07),surprisingness(0.93),adaptivity(0.00),focus(1.00),weight(0.75),usefulness(1.00)]).

fof(20,negated_conjecture,(
    ~ killed(agatha,agatha) ),
    inference(fof_simplification,[status(thm)],[15,theory(equality)]),
    [interesting(-0.38),obviousness(0.02),complexity(0.80),intensity(0.07),surprisingness(0.93),adaptivity(0.00),focus(1.00),weight(0.75),usefulness(1.00)]).

fof(15,negated_conjecture,(
    ~ killed(agatha,agatha) ),
    inference(assume_negation,[status(cth)],[14]),
    [interesting(-0.39),obviousness(0.00),complexity(0.80),intensity(0.07),surprisingness(0.93),adaptivity(0.00),focus(1.00),weight(0.75),usefulness(1.00)]).

cnf(23,plain,
    ( killed(esk1_0,agatha) ),
    inference(split_conjunct,[status(thm)],[22]),
    [interesting(-0.45),obviousness(0.12),complexity(0.50),intensity(0.22),surprisingness(0.64),adaptivity(0.00),focus(1.00),weight(0.75),usefulness(1.00)]).

fof(47,plain,(
    ! [X2] :
      ( ~ hates(agatha,X2)
      | hates(butler,X2) ) ),
    inference(variable_rename,[status(thm)],[46]),
    [interesting(-0.45),obviousness(0.06),complexity(0.50),intensity(0.22),surprisingness(0.82),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(21,plain,(
    ? [X2] :
      ( lives(X2)
      & killed(X2,agatha) ) ),
    inference(variable_rename,[status(thm)],[1]),
    [interesting(-0.46),obviousness(0.00),complexity(0.50),intensity(0.22),surprisingness(0.71),adaptivity(0.00),focus(1.00),weight(0.75),usefulness(1.00)]).

fof(38,plain,(
    ! [X2] :
      ( ~ hates(agatha,X2)
      | ~ hates(charles,X2) ) ),
    inference(variable_rename,[status(thm)],[37]),
    [interesting(-0.46),obviousness(0.12),complexity(0.50),intensity(0.22),surprisingness(0.73),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(37,plain,(
    ! [X1] :
      ( ~ hates(agatha,X1)
      | ~ hates(charles,X1) ) ),
    inference(fof_nnf,[status(thm)],[17]),
    [interesting(-0.47),obviousness(0.06),complexity(0.50),intensity(0.22),surprisingness(0.73),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(46,plain,(
    ! [X1] :
      ( ~ hates(agatha,X1)
      | hates(butler,X1) ) ),
    inference(fof_nnf,[status(thm)],[11]),
    [interesting(-0.47),obviousness(0.00),complexity(0.50),intensity(0.22),surprisingness(0.82),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(17,plain,(
    ! [X1] :
      ( hates(agatha,X1)
     => ~ hates(charles,X1) ) ),
    inference(fof_simplification,[status(thm)],[8,theory(equality)]),
    [interesting(-0.49),obviousness(0.00),complexity(0.50),intensity(0.22),surprisingness(0.73),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

cnf(52,plain,
    ( agatha != butler ),
    inference(split_conjunct,[status(thm)],[13]),
    [interesting(-0.56),obviousness(0.00),complexity(0.50),intensity(0.22),surprisingness(0.84),adaptivity(0.00),focus(1.00),weight(0.75),usefulness(ignored)]).

fof(41,plain,(
    ! [X2] :
      ( X2 = butler
      | hates(agatha,X2) ) ),
    inference(variable_rename,[status(thm)],[40]),
    [interesting(-0.57),obviousness(0.06),complexity(0.25),intensity(0.22),surprisingness(0.59),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(44,plain,(
    ! [X2] :
      ( richer(X2,agatha)
      | hates(butler,X2) ) ),
    inference(variable_rename,[status(thm)],[43]),
    [interesting(-0.58),obviousness(0.12),complexity(0.25),intensity(0.22),surprisingness(0.49),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(40,plain,(
    ! [X1] :
      ( X1 = butler
      | hates(agatha,X1) ) ),
    inference(fof_nnf,[status(thm)],[9]),
    [interesting(-0.59),obviousness(0.00),complexity(0.25),intensity(0.22),surprisingness(0.59),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(43,plain,(
    ! [X1] :
      ( richer(X1,agatha)
      | hates(butler,X1) ) ),
    inference(fof_nnf,[status(thm)],[18]),
    [interesting(-0.59),obviousness(0.06),complexity(0.25),intensity(0.22),surprisingness(0.49),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(18,plain,(
    ! [X1] :
      ( ~ richer(X1,agatha)
     => hates(butler,X1) ) ),
    inference(fof_simplification,[status(thm)],[10,theory(equality)]),
    [interesting(-0.61),obviousness(0.00),complexity(0.25),intensity(0.22),surprisingness(0.49),adaptivity(0.00),focus(1.00),weight(0.62),usefulness(1.00)]).

fof(22,plain,
    ( lives(esk1_0)
    & killed(esk1_0,agatha) ),
    inference(skolemize,[status(esa)],[21]),
    [interesting(-0.72),obviousness(0.06),complexity(0.25),intensity(0.00),surprisingness(0.33),adaptivity(0.00),focus(1.00),weight(0.50),usefulness(1.00)]).

fof(29,plain,(
    ! [X2] :
      ( ~ lives(X2)
      | X2 = agatha
      | X2 = butler
      | X2 = charles ) ),
    inference(variable_rename,[status(thm)],[28]),
    [interesting(-0.83),obviousness(0.06),complexity(0.00),intensity(0.22),surprisingness(0.18),adaptivity(0.00),focus(1.00),weight(0.25),usefulness(1.00)]).

fof(28,plain,(
    ! [X1] :
      ( ~ lives(X1)
      | X1 = agatha
      | X1 = butler
      | X1 = charles ) ),
    inference(fof_nnf,[status(thm)],[5]),
    [interesting(-0.84),obviousness(0.00),complexity(0.00),intensity(0.22),surprisingness(0.18),adaptivity(0.00),focus(1.00),weight(0.25),usefulness(1.00)]).

cnf(30,plain,
    ( X1 = charles
    | X1 = butler
    | X1 = agatha
    | ~ lives(X1) ),
    inference(split_conjunct,[status(thm)],[29]),
    [interesting(-0.94),obviousness(0.12),complexity(0.00),intensity(0.22),surprisingness(0.18),adaptivity(0.50),focus(0.00),weight(0.25),usefulness(1.00)]).

fof(1,axiom,(
    ? [X1] :
      ( lives(X1)
      & killed(X1,agatha) ) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_1),
    [interesting(-1.00)]).

fof(5,axiom,(
    ! [X1] :
      ( lives(X1)
     => ( X1 = agatha
        | X1 = butler
        | X1 = charles ) ) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_3),
    [interesting(-1.00)]).

fof(6,axiom,(
    ! [X1,X2] :
      ( killed(X1,X2)
     => hates(X1,X2) ) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_4),
    [interesting(-1.00)]).

fof(7,axiom,(
    ! [X1,X2] :
      ( killed(X1,X2)
     => ~ richer(X1,X2) ) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_5),
    [interesting(-1.00)]).

fof(8,axiom,(
    ! [X1] :
      ( hates(agatha,X1)
     => ~ hates(charles,X1) ) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_6),
    [interesting(-1.00)]).

fof(9,axiom,(
    ! [X1] :
      ( X1 != butler
     => hates(agatha,X1) ) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_7),
    [interesting(-1.00)]).

fof(10,axiom,(
    ! [X1] :
      ( ~ richer(X1,agatha)
     => hates(butler,X1) ) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_8),
    [interesting(-1.00)]).

fof(11,axiom,(
    ! [X1] :
      ( hates(agatha,X1)
     => hates(butler,X1) ) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_9),
    [interesting(-1.00)]).

fof(12,axiom,(
    ! [X1] :
    ? [X2] : ~ hates(X1,X2) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_10),
    [interesting(-1.00)]).

fof(13,axiom,(
    agatha != butler ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55_11),
    [interesting(-1.00)]).

fof(14,conjecture,(
    killed(agatha,agatha) ),
    file('/home/graph/tptp/TPTP/Problems/PUZ/PUZ001+1.p',pel55),
    [interesting(-1.00)]).

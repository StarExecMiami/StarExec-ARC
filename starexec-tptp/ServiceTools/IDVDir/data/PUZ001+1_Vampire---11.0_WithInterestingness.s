cnf(94,plain,
    ( ~ hates(butler,butler) ),
    inference('backward superposition, passive clause reanimation',[status(thm)],[92,44]),
    [interesting(1.00),obviousness(1.00),complexity(1.00),intensity(0.65),surprisingness(1.00),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(ignored)]).

cnf(119,plain,
    ( sk_1 = butler ),
    inference('backward superposition, passive clause reanimation',[status(thm)],[112,80]),
    [interesting(1.00),obviousness(0.90),complexity(0.75),intensity(1.00),surprisingness(0.84),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(1.00)]).

cnf(90,plain,
    ( hates(butler,X1)
    | X1 = butler ),
    inference('resolution, passive clause reanimation',[status(thm)],[40,42]),
    [interesting(0.96),obviousness(0.00),complexity(0.67),intensity(0.87),surprisingness(0.82),adaptivity(1.00),focus(ignored),weight(0.83),usefulness(1.00)]).

cnf(92,plain,
    ( sk_0(butler) = butler ),
    inference('resolution, passive clause reanimation',[status(thm)],[90,44]),
    [interesting(0.85),obviousness(0.50),complexity(0.67),intensity(0.87),surprisingness(0.75),adaptivity(0.00),focus(ignored),weight(0.83),usefulness(1.00)]).

cnf(89,plain,
    ( ~ hates(charles,X1)
    | X1 = butler ),
    inference('resolution, passive clause reanimation',[status(thm)],[41,42]),
    [interesting(0.78),obviousness(0.00),complexity(0.33),intensity(1.00),surprisingness(0.47),adaptivity(1.00),focus(ignored),weight(0.83),usefulness(ignored)]).

cnf(123,plain,
    ( killed(butler,agatha) ),
    inference('backward superposition, passive clause reanimation',[status(thm)],[119,48]),
    [interesting(0.77),obviousness(1.00),complexity(0.75),intensity(1.00),surprisingness(0.86),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(0.00)]).

cnf(49,plain,
    ( hates(butler,X0)
    | ~ killed(X0,agatha) ),
    inference(resolution,[status(thm)],[43,46]),
    [interesting(0.67),obviousness(0.00),complexity(0.33),intensity(0.48),surprisingness(0.48),adaptivity(1.00),focus(ignored),weight(0.83),usefulness(ignored)]).

cnf(85,plain,
    ( hates(sk_1,agatha) ),
    inference('resolution, passive clause reanimation',[status(thm)],[45,48]),
    [interesting(0.63),obviousness(0.00),complexity(0.67),intensity(0.55),surprisingness(0.73),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(ignored)]).

cnf(80,plain,
    ( agatha != butler ),
    inference('passive clause reanimation',[status(thm)],[37]),
    [interesting(0.60),obviousness(0.00),complexity(0.67),intensity(0.22),surprisingness(0.89),adaptivity(0.00),focus(ignored),weight(1.00),usefulness(ignored)]).

cnf(112,plain,
    ( agatha = butler
    | sk_1 = butler ),
    inference('resolution, passive clause reanimation',[status(thm)],[108,89]),
    [interesting(0.57),obviousness(0.70),complexity(0.50),intensity(0.47),surprisingness(0.67),adaptivity(0.00),focus(ignored),weight(0.50),usefulness(1.00)]).

cnf(105,plain,
    ( sk_1 = charles
    | sk_1 = butler ),
    inference('backward superposition, forward subsumption resolution, passive clause reanimation',[status(thm)],[103,95,48]),
    [interesting(0.39),obviousness(0.30),complexity(0.50),intensity(0.22),surprisingness(0.60),adaptivity(0.00),focus(ignored),weight(0.50),usefulness(1.00)]).

cnf(108,plain,
    ( hates(charles,agatha)
    | sk_1 = butler ),
    inference('backward superposition, passive clause reanimation',[status(thm)],[105,85]),
    [interesting(0.22),obviousness(0.50),complexity(0.00),intensity(0.48),surprisingness(0.00),adaptivity(0.00),focus(ignored),weight(0.50),usefulness(1.00)]).

cnf(103,plain,
    ( ~ killed(sk_1,sk_1)
    | sk_1 = charles
    | sk_1 = butler ),
    inference('backward superposition, passive clause reanimation',[status(thm)],[95,38]),
    [interesting(0.01),obviousness(0.10),complexity(0.25),intensity(0.04),surprisingness(0.26),adaptivity(0.00),focus(ignored),weight(0.00),usefulness(1.00)]).

cnf(95,plain,
    ( agatha = sk_1
    | sk_1 = charles
    | sk_1 = butler ),
    inference('resolution, passive clause reanimation',[status(thm)],[39,47]),
    [interesting(0.00),obviousness(0.00),complexity(0.00),intensity(0.00),surprisingness(0.00),adaptivity(0.00),focus(ignored),weight(0.00),usefulness(ignored)]).

cnf(124,plain,
    ( $false ),
    inference('resolution, forward subsumption resolution',[status(thm)],[94,49,123]),
    [interesting(0.00)]).

cnf(46,plain,
    ( ~ richer(X0,X1)
    | ~ killed(X0,X1) ),
    inference('cnf transformation',[status(thm)],[32]),
    [interesting(-0.02),obviousness(0.17),complexity(1.00),intensity(0.22),surprisingness(0.98),adaptivity(1.00),focus(1.00),weight(1.00),usefulness(1.00)]).

cnf(45,plain,
    ( hates(X0,X1)
    | ~ killed(X0,X1) ),
    inference('cnf transformation',[status(thm)],[31]),
    [interesting(-0.03),obviousness(0.17),complexity(1.00),intensity(0.22),surprisingness(0.96),adaptivity(1.00),focus(1.00),weight(1.00),usefulness(1.00)]).

cnf(44,plain,
    ( ~ hates(X0,sk_0(X0)) ),
    inference('cnf transformation',[status(thm)],[30]),
    [interesting(-0.05),obviousness(0.08),complexity(1.00),intensity(0.22),surprisingness(0.95),adaptivity(1.00),focus(1.00),weight(1.00),usefulness(1.00)]).

cnf(40,plain,
    ( hates(butler,X0)
    | ~ hates(agatha,X0) ),
    inference('cnf transformation',[status(thm)],[26]),
    [interesting(-0.18),obviousness(0.17),complexity(0.67),intensity(0.22),surprisingness(0.88),adaptivity(1.00),focus(1.00),weight(0.71),usefulness(1.00)]).

cnf(41,plain,
    ( ~ hates(charles,X0)
    | ~ hates(agatha,X0) ),
    inference('cnf transformation',[status(thm)],[27]),
    [interesting(-0.21),obviousness(0.17),complexity(0.67),intensity(0.22),surprisingness(0.78),adaptivity(1.00),focus(1.00),weight(0.71),usefulness(1.00)]).

fof(32,plain,(
    ! [X0,X1] :
      ( ~ killed(X0,X1)
      | ~ richer(X0,X1) ) ),
    inference(skolemization,[status(thm)],[24]),
    [interesting(-0.26),obviousness(0.08),complexity(1.00),intensity(0.22),surprisingness(0.98),adaptivity(0.00),focus(1.00),weight(1.00),usefulness(1.00)]).

cnf(47,plain,
    ( lives(sk_1) ),
    inference('cnf transformation',[status(thm)],[33]),
    [interesting(-0.27),obviousness(0.08),complexity(1.00),intensity(0.22),surprisingness(0.95),adaptivity(0.00),focus(1.00),weight(1.00),usefulness(1.00)]).

fof(31,plain,(
    ! [X0,X1] :
      ( ~ killed(X0,X1)
      | hates(X0,X1) ) ),
    inference(skolemization,[status(thm)],[23]),
    [interesting(-0.27),obviousness(0.08),complexity(1.00),intensity(0.22),surprisingness(0.96),adaptivity(0.00),focus(1.00),weight(1.00),usefulness(1.00)]).

fof(24,plain,(
    ! [X0,X1] :
      ( ~ killed(X0,X1)
      | ~ richer(X0,X1) ) ),
    inference('ENNF transformation',[status(thm)],[7]),
    [interesting(-0.28),obviousness(0.00),complexity(1.00),intensity(0.22),surprisingness(0.98),adaptivity(0.00),focus(1.00),weight(1.00),usefulness(1.00)]).

fof(30,plain,(
    ! [X0] : ~ hates(X0,sk_0(X0)) ),
    inference(skolemization,[status(thm)],[12]),
    [interesting(-0.29),obviousness(0.00),complexity(1.00),intensity(0.22),surprisingness(0.95),adaptivity(0.00),focus(1.00),weight(1.00),usefulness(1.00)]).

fof(23,plain,(
    ! [X0,X1] :
      ( ~ killed(X0,X1)
      | hates(X0,X1) ) ),
    inference('ENNF transformation',[status(thm)],[6]),
    [interesting(-0.29),obviousness(0.00),complexity(1.00),intensity(0.22),surprisingness(0.96),adaptivity(0.00),focus(1.00),weight(1.00),usefulness(1.00)]).

cnf(42,plain,
    ( hates(agatha,X0)
    | X0 = butler ),
    inference('cnf transformation',[status(thm)],[28]),
    [interesting(-0.32),obviousness(0.17),complexity(0.33),intensity(0.22),surprisingness(0.61),adaptivity(1.00),focus(1.00),weight(0.71),usefulness(1.00)]).

cnf(43,plain,
    ( hates(butler,X0)
    | richer(X0,agatha) ),
    inference('cnf transformation',[status(thm)],[29]),
    [interesting(-0.34),obviousness(0.17),complexity(0.33),intensity(0.22),surprisingness(0.51),adaptivity(1.00),focus(1.00),weight(0.71),usefulness(1.00)]).

cnf(38,plain,
    ( ~ killed(agatha,agatha) ),
    inference('cnf transformation',[status(thm)],[14]),
    [interesting(-0.39),obviousness(0.00),complexity(1.00),intensity(0.07),surprisingness(0.98),adaptivity(0.00),focus(1.00),weight(0.86),usefulness(1.00)]).

cnf(37,plain,
    ( butler != agatha ),
    inference('cnf transformation',[status(thm)],[16]),
    [interesting(-0.39),obviousness(0.08),complexity(0.67),intensity(0.22),surprisingness(0.91),adaptivity(0.00),focus(1.00),weight(0.86),usefulness(1.00)]).

fof(16,plain,(
    butler != agatha ),
    inference(normalize,[status(thm)],[13]),
    [interesting(-0.41),obviousness(0.00),complexity(0.67),intensity(0.22),surprisingness(0.91),adaptivity(0.00),focus(1.00),weight(0.86),usefulness(1.00)]).

fof(26,plain,(
    ! [X0] :
      ( ~ hates(agatha,X0)
      | hates(butler,X0) ) ),
    inference(skolemization,[status(thm)],[19]),
    [interesting(-0.43),obviousness(0.08),complexity(0.67),intensity(0.22),surprisingness(0.88),adaptivity(0.00),focus(1.00),weight(0.71),usefulness(1.00)]).

fof(19,plain,(
    ! [X0] :
      ( ~ hates(agatha,X0)
      | hates(butler,X0) ) ),
    inference('ENNF transformation',[status(thm)],[11]),
    [interesting(-0.44),obviousness(0.00),complexity(0.67),intensity(0.22),surprisingness(0.88),adaptivity(0.00),focus(1.00),weight(0.71),usefulness(1.00)]).

cnf(48,plain,
    ( killed(sk_1,agatha) ),
    inference('cnf transformation',[status(thm)],[33]),
    [interesting(-0.44),obviousness(0.08),complexity(0.67),intensity(0.22),surprisingness(0.67),adaptivity(0.00),focus(1.00),weight(0.86),usefulness(1.00)]).

fof(27,plain,(
    ! [X0] :
      ( ~ hates(agatha,X0)
      | ~ hates(charles,X0) ) ),
    inference(skolemization,[status(thm)],[20]),
    [interesting(-0.45),obviousness(0.08),complexity(0.67),intensity(0.22),surprisingness(0.78),adaptivity(0.00),focus(1.00),weight(0.71),usefulness(1.00)]).

fof(20,plain,(
    ! [X0] :
      ( ~ hates(agatha,X0)
      | ~ hates(charles,X0) ) ),
    inference('ENNF transformation',[status(thm)],[8]),
    [interesting(-0.46),obviousness(0.00),complexity(0.67),intensity(0.22),surprisingness(0.78),adaptivity(0.00),focus(1.00),weight(0.71),usefulness(1.00)]).

fof(28,plain,(
    ! [X0] :
      ( X0 = butler
      | hates(agatha,X0) ) ),
    inference(skolemization,[status(thm)],[21]),
    [interesting(-0.56),obviousness(0.08),complexity(0.33),intensity(0.22),surprisingness(0.61),adaptivity(0.00),focus(1.00),weight(0.71),usefulness(1.00)]).

fof(21,plain,(
    ! [X0] :
      ( X0 = butler
      | hates(agatha,X0) ) ),
    inference('ENNF transformation',[status(thm)],[9]),
    [interesting(-0.58),obviousness(0.00),complexity(0.33),intensity(0.22),surprisingness(0.61),adaptivity(0.00),focus(1.00),weight(0.71),usefulness(1.00)]).

fof(29,plain,(
    ! [X0] :
      ( richer(X0,agatha)
      | hates(butler,X0) ) ),
    inference(skolemization,[status(thm)],[22]),
    [interesting(-0.58),obviousness(0.08),complexity(0.33),intensity(0.22),surprisingness(0.51),adaptivity(0.00),focus(1.00),weight(0.71),usefulness(1.00)]).

fof(22,plain,(
    ! [X0] :
      ( richer(X0,agatha)
      | hates(butler,X0) ) ),
    inference('ENNF transformation',[status(thm)],[10]),
    [interesting(-0.60),obviousness(0.00),complexity(0.33),intensity(0.22),surprisingness(0.51),adaptivity(0.00),focus(1.00),weight(0.71),usefulness(1.00)]).

fof(33,plain,
    ( lives(sk_1)
    & killed(sk_1,agatha) ),
    inference(skolemization,[status(thm)],[1]),
    [interesting(-0.72),obviousness(0.00),complexity(0.33),intensity(0.00),surprisingness(0.32),adaptivity(0.00),focus(1.00),weight(0.57),usefulness(1.00)]).

fof(25,plain,(
    ! [X0] :
      ( ~ lives(X0)
      | X0 = charles
      | X0 = butler
      | X0 = agatha ) ),
    inference(skolemization,[status(thm)],[18]),
    [interesting(-0.79),obviousness(0.25),complexity(0.00),intensity(0.22),surprisingness(0.15),adaptivity(0.00),focus(1.00),weight(0.29),usefulness(1.00)]).

fof(18,plain,(
    ! [X0] :
      ( ~ lives(X0)
      | X0 = charles
      | X0 = butler
      | X0 = agatha ) ),
    inference(flattening,[status(thm)],[17]),
    [interesting(-0.81),obviousness(0.17),complexity(0.00),intensity(0.22),surprisingness(0.15),adaptivity(0.00),focus(1.00),weight(0.29),usefulness(1.00)]).

fof(17,plain,(
    ! [X0] :
      ( ~ lives(X0)
      | X0 = charles
      | X0 = butler
      | X0 = agatha ) ),
    inference('ENNF transformation',[status(thm)],[15]),
    [interesting(-0.83),obviousness(0.08),complexity(0.00),intensity(0.22),surprisingness(0.15),adaptivity(0.00),focus(1.00),weight(0.29),usefulness(1.00)]).

fof(15,plain,(
    ! [X0] :
      ( lives(X0)
     => ( X0 = charles
        | X0 = butler
        | X0 = agatha ) ) ),
    inference(normalize,[status(thm)],[5]),
    [interesting(-0.85),obviousness(0.00),complexity(0.00),intensity(0.22),surprisingness(0.15),adaptivity(0.00),focus(1.00),weight(0.29),usefulness(1.00)]).

cnf(39,plain,
    ( X0 = agatha
    | X0 = butler
    | X0 = charles
    | ~ lives(X0) ),
    inference('cnf transformation',[status(thm)],[25]),
    [interesting(-0.89),obviousness(0.33),complexity(0.00),intensity(0.22),surprisingness(0.15),adaptivity(0.50),focus(0.00),weight(0.29),usefulness(1.00)]).

fof(11,axiom,(
    ! [X0] :
      ( hates(agatha,X0)
     => hates(butler,X0) ) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(9,axiom,(
    ! [X0] :
      ( X0 != butler
     => hates(agatha,X0) ) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(12,axiom,(
    ! [X0] :
    ? [X1] : ~ hates(X0,X1) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(10,axiom,(
    ! [X0] :
      ( ~ richer(X0,agatha)
     => hates(butler,X0) ) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(7,axiom,(
    ! [X0,X1] :
      ( killed(X0,X1)
     => ~ richer(X0,X1) ) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(5,axiom,(
    ! [X0] :
      ( lives(X0)
     => ( X0 = agatha
        | X0 = butler
        | X0 = charles ) ) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(1,axiom,(
    ? [X0] :
      ( lives(X0)
      & killed(X0,agatha) ) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(14,negated_conjecture,(
    ~ killed(agatha,agatha) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(6,axiom,(
    ! [X0,X1] :
      ( killed(X0,X1)
     => hates(X0,X1) ) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(8,axiom,(
    ! [X0] :
      ( hates(agatha,X0)
     => ~ hates(charles,X0) ) ),
    file(input,unknown),
    [interesting(-1.00)]).

fof(13,axiom,(
    agatha != butler ),
    file(input,unknown),
    [interesting(-1.00)]).

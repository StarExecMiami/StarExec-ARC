%------------------------------------------------------------------------------
%----TSTP SOLUTION
fof(3,axiom,
    ( op_strict_implies
  <=> ! [X1,X2] : strict_implies(X1,X2) = not(possibly(and(X1,not(X2)))) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',op_strict_implies)).

fof(4,axiom,
    ( op_strict_equiv
  <=> ! [X1,X2] : strict_equiv(X1,X2) = and(strict_implies(X1,X2),strict_implies(X2,X1)) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',op_strict_equiv)).

fof(5,axiom,
    ( axiom_s1_1
  <=> ! [X1,X2] : is_a_theorem(strict_implies(and(X1,X2),and(X2,X1))) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',axiom_s1_1)).

fof(6,axiom,
    ( axiom_s1_2
  <=> ! [X1,X2] : is_a_theorem(strict_implies(and(X1,X2),X1)) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',axiom_s1_2)).

fof(7,axiom,
    ( axiom_s1_3
  <=> ! [X1] : is_a_theorem(strict_implies(X1,and(X1,X1))) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',axiom_s1_3)).

fof(8,axiom,
    ( axiom_s1_4
  <=> ! [X1,X2,X3] : is_a_theorem(strict_implies(and(and(X1,X2),X3),and(X1,and(X2,X3)))) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',axiom_s1_4)).

fof(9,axiom,
    ( axiom_s1_5
  <=> ! [X1,X2,X3] : is_a_theorem(strict_implies(and(strict_implies(X1,X2),strict_implies(X2,X3)),strict_implies(X1,X3))) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',axiom_s1_5)).

fof(10,axiom,
    ( ! [X1,X2] : 
        ( ( is_a_theorem(X1)
          & is_a_theorem(X2) )
       => is_a_theorem(and(X1,X2)) ) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',adjunction)).

fof(11,axiom,
    ( ! [X1,X2] : 
        ( ( is_a_theorem(X1)
          & is_a_theorem(strict_implies(X1,X2)) )
       => is_a_theorem(X2) ) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',modus_ponens_strict_implies)).

fof(12,axiom,
    ( ! [X1,X2] : 
        ( is_a_theorem(strict_equiv(X1,X2))
       => X1 = X2 ) ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',substitution_strict_equiv)).

fof(13,axiom,
    ( op_or
    & op_strict_implies
    & op_strict_equiv
    & op_necessarily
    & axiom_s1_1
    & axiom_s1_2
    & axiom_s1_3
    & axiom_s1_4
    & axiom_s1_5 ),
    file('/tmp/SystemOnTPTP22473//SOT001-1.p',system_S1_0)).

cnf(36,derived,
    ( strict_implies(X3,X4) = not(possibly(and(X3,not(X4))))
    | ~ op_strict_implies ),
    inference(split_conjunct,[status(thm)],[3])).

cnf(41,derived,
    ( strict_equiv(X3,X4) = and(strict_implies(X3,X4),strict_implies(X4,X3))
    | ~ op_strict_equiv ),
    inference(split_conjunct,[status(thm)],[4])).

cnf(46,derived,
    ( is_a_theorem(strict_implies(and(X3,X4),and(X4,X3)))
    | ~ axiom_s1_1 ),
    inference(split_conjunct,[status(thm)],[5])).

cnf(51,derived,
    ( is_a_theorem(strict_implies(and(X3,X4),X3))
    | ~ axiom_s1_2 ),
    inference(split_conjunct,[status(thm)],[6])).

cnf(56,derived,
    ( is_a_theorem(strict_implies(X2,and(X2,X2)))
    | ~ axiom_s1_3 ),
    inference(split_conjunct,[status(thm)],[7])).

cnf(61,derived,
    ( is_a_theorem(strict_implies(and(and(X4,X5),X6),and(X4,and(X5,X6))))
    | ~ axiom_s1_4 ),
    inference(split_conjunct,[status(thm)],[8])).

cnf(66,derived,
    ( is_a_theorem(strict_implies(and(strict_implies(X4,X5),strict_implies(X5,X6)),strict_implies(X4,X6)))
    | ~ axiom_s1_5 ),
    inference(split_conjunct,[status(thm)],[9])).

cnf(69,derived,
    ( is_a_theorem(and(X3,X4))
    | ~ is_a_theorem(X4)
    | ~ is_a_theorem(X3) ),
    inference(split_conjunct,[status(thm)],[10])).

cnf(72,derived,
    ( is_a_theorem(X4)
    | ~ is_a_theorem(strict_implies(X3,X4))
    | ~ is_a_theorem(X3) ),
    inference(split_conjunct,[status(thm)],[11])).

cnf(75,derived,
    ( X3 = X4
    | ~ is_a_theorem(strict_equiv(X3,X4)) ),
    inference(split_conjunct,[status(thm)],[12])).

cnf(76,derived,
    ( axiom_s1_5 ),
    inference(split_conjunct,[status(thm)],[13])).

cnf(77,derived,
    ( axiom_s1_4 ),
    inference(split_conjunct,[status(thm)],[13])).

cnf(78,derived,
    ( axiom_s1_3 ),
    inference(split_conjunct,[status(thm)],[13])).

cnf(79,derived,
    ( axiom_s1_2 ),
    inference(split_conjunct,[status(thm)],[13])).

cnf(80,derived,
    ( axiom_s1_1 ),
    inference(split_conjunct,[status(thm)],[13])).

cnf(82,derived,
    ( op_strict_equiv ),
    inference(split_conjunct,[status(thm)],[13])).

cnf(83,derived,
    ( op_strict_implies ),
    inference(split_conjunct,[status(thm)],[13])).

cnf(111,negated_conjecture,
    ( ~ is_a_theorem(strict_equiv(not(not(esk24_0)),esk24_0)) ),
    inference(split_conjunct,[status(thm)],[110])).

cnf(127,derived,
    ( is_a_theorem(strict_implies(X2,and(X2,X2))) ),
    inference(cn,[status(thm)],[56,78,theory(equality)])).

cnf(142,derived,
    ( is_a_theorem(strict_implies(and(X3,X4),X3)) ),
    inference(cn,[status(thm)],[51,79,theory(equality)])).

cnf(150,derived,
    ( and(strict_implies(X3,X4),strict_implies(X4,X3)) = strict_equiv(X3,X4) ),
    inference(cn,[status(thm)],[41,82,theory(equality)])).

cnf(151,derived,
    ( is_a_theorem(strict_implies(strict_implies(X1,X1),strict_equiv(X1,X1))) ),
    inference(pm,[status(thm)],[127,150,theory(equality)])).

cnf(152,derived,
    ( is_a_theorem(strict_implies(strict_equiv(X1,X2),strict_implies(X1,X2))) ),
    inference(pm,[status(thm)],[142,150,theory(equality)])).

cnf(153,derived,
    ( is_a_theorem(strict_equiv(X1,X2))
    | ~ is_a_theorem(strict_implies(X2,X1))
    | ~ is_a_theorem(strict_implies(X1,X2)) ),
    inference(pm,[status(thm)],[69,150,theory(equality)])).

cnf(157,derived,
    ( not(possibly(and(X3,not(X4)))) = strict_implies(X3,X4) ),
    inference(cn,[status(thm)],[36,83,theory(equality)])).

cnf(166,derived,
    ( is_a_theorem(strict_implies(and(X3,X4),and(X4,X3))) ),
    inference(cn,[status(thm)],[46,80,theory(equality)])).

cnf(173,derived,
    ( is_a_theorem(strict_implies(and(and(X4,X5),X6),and(X4,and(X5,X6)))) ),
    inference(cn,[status(thm)],[61,77,theory(equality)])).

cnf(178,derived,
    ( is_a_theorem(strict_implies(and(strict_implies(X4,X5),strict_implies(X5,X6)),strict_implies(X4,X6))) ),
    inference(cn,[status(thm)],[66,76,theory(equality)])).

cnf(180,derived,
    ( is_a_theorem(strict_implies(X1,X3))
    | ~ is_a_theorem(and(strict_implies(X1,X2),strict_implies(X2,X3))) ),
    inference(pm,[status(thm)],[72,178,theory(equality)])).

cnf(303,negated_conjecture-derived,
    ( ~ is_a_theorem(strict_implies(esk24_0,not(not(esk24_0))))
    | ~ is_a_theorem(strict_implies(not(not(esk24_0)),esk24_0)) ),
    inference(pm,[status(thm)],[111,153,theory(equality)])).

cnf(304,derived,
    ( X1 = X2
    | ~ is_a_theorem(strict_implies(X2,X1))
    | ~ is_a_theorem(strict_implies(X1,X2)) ),
    inference(pm,[status(thm)],[75,153,theory(equality)])).

cnf(310,derived,
    ( and(X1,X1) = X1
    | ~ is_a_theorem(strict_implies(and(X1,X1),X1)) ),
    inference(pm,[status(thm)],[304,127,theory(equality)])).

cnf(313,derived,
    ( and(X2,X1) = and(X1,X2)
    | ~ is_a_theorem(strict_implies(and(X2,X1),and(X1,X2))) ),
    inference(pm,[status(thm)],[304,166,theory(equality)])).

cnf(316,derived,
    ( strict_equiv(X1,X1) = strict_implies(X1,X1)
    | ~ is_a_theorem(strict_implies(strict_equiv(X1,X1),strict_implies(X1,X1))) ),
    inference(pm,[status(thm)],[304,151,theory(equality)])).

cnf(320,derived,
    ( and(X1,X1) = X1 ),
    inference(cn,[status(thm)],[310,142,theory(equality)])).

cnf(322,derived,
    ( and(X2,X1) = and(X1,X2) ),
    inference(cn,[status(thm)],[313,166,theory(equality)])).

cnf(324,derived,
    ( strict_equiv(X1,X1) = strict_implies(X1,X1) ),
    inference(cn,[status(thm)],[316,152,theory(equality)])).

cnf(340,derived,
    ( is_a_theorem(strict_implies(X2,X2)) ),
    inference(rw,[status(thm)],[127,320,theory(equality)])).

cnf(388,derived,
    ( is_a_theorem(strict_implies(and(X2,X1),X1)) ),
    inference(pm,[status(thm)],[142,322,theory(equality)])).

cnf(392,derived,
    ( not(possibly(and(not(X2),X1))) = strict_implies(X1,X2) ),
    inference(pm,[status(thm)],[157,322,theory(equality)])).

cnf(755,derived,
    ( is_a_theorem(strict_implies(X1,X3))
    | ~ is_a_theorem(strict_implies(X2,X3))
    | ~ is_a_theorem(strict_implies(X1,X2)) ),
    inference(pm,[status(thm)],[180,69,theory(equality)])).

cnf(769,derived,
    ( is_a_theorem(strict_implies(X3,X2))
    | ~ is_a_theorem(strict_implies(X3,and(X1,X2))) ),
    inference(pm,[status(thm)],[755,388,theory(equality)])).

cnf(789,derived,
    ( is_a_theorem(strict_implies(and(and(X1,X2),X3),and(X2,X3))) ),
    inference(pm,[status(thm)],[769,173,theory(equality)])).

cnf(1630,derived,
    ( strict_implies(not(X2),X1) = strict_implies(not(X1),X2) ),
    inference(pm,[status(thm)],[157,392,theory(equality)])).

cnf(1861,derived,
    ( X2 = not(X1)
    | ~ is_a_theorem(strict_implies(not(X2),X1))
    | ~ is_a_theorem(strict_implies(X2,not(X1))) ),
    inference(pm,[status(thm)],[304,1630,theory(equality)])).

cnf(1864,derived,
    ( is_a_theorem(strict_implies(X1,X3))
    | ~ is_a_theorem(and(strict_implies(X1,not(X2)),strict_implies(not(X3),X2))) ),
    inference(pm,[status(thm)],[180,1630,theory(equality)])).

cnf(1910,negated_conjecture-derived,
    ( ~ is_a_theorem(strict_implies(esk24_0,not(not(esk24_0)))) ),
    inference(cn,[status(thm)],[303,1630,340,theory(equality)])).

cnf(2451,derived,
    ( is_a_theorem(and(X2,X3))
    | ~ is_a_theorem(and(and(X1,X2),X3)) ),
    inference(pm,[status(thm)],[72,789,theory(equality)])).

cnf(2629,derived,
    ( is_a_theorem(and(X2,X3))
    | ~ is_a_theorem(X3)
    | ~ is_a_theorem(and(X1,X2)) ),
    inference(pm,[status(thm)],[2451,69,theory(equality)])).

cnf(2631,derived,
    ( is_a_theorem(and(strict_implies(X2,X1),X3))
    | ~ is_a_theorem(strict_equiv(X1,X2))
    | ~ is_a_theorem(X3) ),
    inference(pm,[status(thm)],[2629,150,theory(equality)])).

cnf(4486,derived,
    ( X1 = not(not(X1))
    | ~ is_a_theorem(strict_implies(X1,not(not(X1)))) ),
    inference(pm,[status(thm)],[1861,340,theory(equality)])).

cnf(4582,derived,
    ( is_a_theorem(and(strict_implies(X1,X1),X2))
    | ~ is_a_theorem(strict_implies(X1,X1))
    | ~ is_a_theorem(X2) ),
    inference(pm,[status(thm)],[2631,324,theory(equality)])).

cnf(4587,derived,
    ( is_a_theorem(and(strict_implies(X1,X1),X2))
    | ~ is_a_theorem(X2) ),
    inference(cn,[status(thm)],[4582,340,theory(equality)])).

cnf(4593,derived,
    ( is_a_theorem(and(X2,strict_implies(X1,X1)))
    | ~ is_a_theorem(X2) ),
    inference(pm,[status(thm)],[4587,322,theory(equality)])).

cnf(79846,derived,
    ( is_a_theorem(strict_implies(X1,X2))
    | ~ is_a_theorem(strict_implies(X1,not(not(X2)))) ),
    inference(pm,[status(thm)],[1864,4593,theory(equality)])).

cnf(79876,derived,
    ( is_a_theorem(strict_implies(and(not(not(X1)),X2),X1)) ),
    inference(pm,[status(thm)],[79846,142,theory(equality)])).

cnf(80181,derived,
    ( is_a_theorem(strict_implies(and(not(not(not(not(X1)))),X2),X1)) ),
    inference(pm,[status(thm)],[79846,79876,theory(equality)])).

cnf(86887,derived,
    ( is_a_theorem(strict_implies(not(not(not(not(X1)))),X1)) ),
    inference(pm,[status(thm)],[80181,320,theory(equality)])).

cnf(87011,derived,
    ( is_a_theorem(strict_implies(not(X1),not(not(not(X1))))) ),
    inference(rw,[status(thm)],[86887,1630,theory(equality)])).

cnf(87097,derived,
    ( not(not(not(X1))) = not(X1) ),
    inference(pm,[status(thm)],[4486,87011,theory(equality)])).

cnf(87210,derived,
    ( not(possibly(and(X1,not(X2)))) = strict_implies(X1,not(not(X2))) ),
    inference(pm,[status(thm)],[157,87097,theory(equality)])).

cnf(87773,derived,
    ( strict_implies(X1,X2) = strict_implies(X1,not(not(X2))) ),
    inference(rw,[status(thm)],[87210,157,theory(equality)])).

cnf(99426,negated_conjecture-derived,
    ( $false ),
    inference(rw,[status(thm)],[inference(rw,[status(thm)],[1910,87773,theory(equality)]),340,theory(equality)])).

cnf(99427,negated_conjecture-derived,
    ( $false ),
    inference(cn,[status(thm)],[99426,theory(equality)])).

cnf(99428,negated_conjecture-derived,
    ( $false ),
    99427,
    ['proof']).
%------------------------------------------------------------------------------

%------------------------------------------------------------------------------
% File       : EP---0.999
% Problem    : PUZ031-1 : TPTP v1.0.0
% Transform  : none
% Format     : tptp
% Command    : eproof --print-statistics -xAuto -tAuto --cpu-limit=%d --memory-limit=Auto --tstp-in --tstp-out %s

% Computer   : art08.cs.miami.edu
% Model      : i686 i686
% CPU        : Intel(R) Pentium(R) 4 CPU 2.80GHz @ 2793MHz
% Memory     : 1003MB
% OS         : Linux 2.6.17-1.2142_FC4
% CPULimit   : 600s
% DateTime   : Sun Sep 23 03:12:43 EDT 2007

% Result     : Unsatisfiable 0.1s
% Output     : CNFRefutation 0.1s
% Verified   : 
% Statistics : Number of clauses     :   62 ( 108 expanded)
%              Number of leaves      :   20 (  52 expanded)
%              Depth                 :   27
%              Number of atoms       :  224 ( 344 expanded)
%              Maximal clause size   :    9 (   4 average)
%              Maximal term depth    :    2 (   1 average)

% Comments   : 
%------------------------------------------------------------------------------
cnf(1,axiom,
    ( animal(X1)
    | ~ wolf(X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',wolf_is_an_animal)).

cnf(2,axiom,
    ( animal(X1)
    | ~ fox(X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',fox_is_an_animal)).

cnf(3,axiom,
    ( animal(X1)
    | ~ bird(X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',bird_is_an_animal)).

cnf(5,axiom,
    ( animal(X1)
    | ~ snail(X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',snail_is_an_animal)).

cnf(6,axiom,
    ( wolf(a_wolf) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',there_is_a_wolf)).

cnf(7,axiom,
    ( fox(a_fox) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',there_is_a_fox)).

cnf(8,axiom,
    ( bird(a_bird) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',there_is_a_bird)).

cnf(10,axiom,
    ( snail(a_snail) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',there_is_a_snail)).

cnf(11,axiom,
    ( grain(a_grain) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',there_is_a_grain)).

cnf(12,axiom,
    ( plant(X1)
    | ~ grain(X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',grain_is_a_plant)).

cnf(13,axiom,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ animal(X1)
    | ~ plant(X2)
    | ~ animal(X3)
    | ~ plant(X4)
    | ~ much_smaller(X3,X1)
    | ~ eats(X3,X4) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',eating_habits)).

cnf(15,axiom,
    ( much_smaller(X1,X2)
    | ~ snail(X1)
    | ~ bird(X2) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',snail_smaller_than_bird)).

cnf(16,axiom,
    ( much_smaller(X1,X2)
    | ~ bird(X1)
    | ~ fox(X2) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',bird_smaller_than_fox)).

cnf(17,axiom,
    ( much_smaller(X1,X2)
    | ~ fox(X1)
    | ~ wolf(X2) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',fox_smaller_than_wolf)).

cnf(18,axiom,
    ( ~ wolf(X1)
    | ~ fox(X2)
    | ~ eats(X1,X2) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',wolf_dont_eat_fox)).

cnf(19,axiom,
    ( ~ wolf(X1)
    | ~ grain(X2)
    | ~ eats(X1,X2) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',wolf_dont_eat_grain)).

cnf(21,axiom,
    ( ~ bird(X1)
    | ~ snail(X2)
    | ~ eats(X1,X2) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',bird_dont_eat_snail)).

cnf(24,axiom,
    ( plant(snail_food_of(X1))
    | ~ snail(X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',snail_food_is_a_plant)).

cnf(25,axiom,
    ( eats(X1,snail_food_of(X1))
    | ~ snail(X1) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',snail_eats_snail_food)).

cnf(26,negated_conjecture,
    ( ~ animal(X1)
    | ~ animal(X2)
    | ~ grain(X3)
    | ~ eats(X1,X2)
    | ~ eats(X2,X3) ),
    file('/home/graph/tptp/TSTP/PreparedTPTP/tptp---none/PUZ/PUZ031-1.tptp',prove_the_animal_exists)).

cnf(28,plain,
    ( animal(a_fox) ),
    inference(spm,[status(thm)],[2,7,theory(equality)])).

cnf(29,plain,
    ( animal(a_bird) ),
    inference(spm,[status(thm)],[3,8,theory(equality)])).

cnf(32,plain,
    ( plant(a_grain) ),
    inference(spm,[status(thm)],[12,11,theory(equality)])).

cnf(42,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ animal(X3)
    | ~ animal(X1)
    | ~ fox(X3)
    | ~ wolf(X1) ),
    inference(spm,[status(thm)],[13,17,theory(equality)])).

cnf(43,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ animal(X3)
    | ~ animal(X1)
    | ~ bird(X3)
    | ~ fox(X1) ),
    inference(spm,[status(thm)],[13,16,theory(equality)])).

cnf(45,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ animal(X3)
    | ~ animal(X1)
    | ~ snail(X3)
    | ~ bird(X1) ),
    inference(spm,[status(thm)],[13,15,theory(equality)])).

cnf(57,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ fox(X3)
    | ~ wolf(X1)
    | ~ animal(X3) ),
    inference(csr,[status(thm)],[42,1])).

cnf(58,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ fox(X3)
    | ~ wolf(X1) ),
    inference(csr,[status(thm)],[57,2])).

cnf(59,plain,
    ( eats(X1,X2)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ fox(X3)
    | ~ wolf(X1) ),
    inference(csr,[status(thm)],[58,18])).

cnf(63,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ bird(X3)
    | ~ fox(X1)
    | ~ animal(X3) ),
    inference(csr,[status(thm)],[43,2])).

cnf(64,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ bird(X3)
    | ~ fox(X1) ),
    inference(csr,[status(thm)],[63,3])).

cnf(98,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ snail(X3)
    | ~ bird(X1)
    | ~ animal(X3) ),
    inference(csr,[status(thm)],[45,3])).

cnf(99,plain,
    ( eats(X1,X2)
    | eats(X1,X3)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ snail(X3)
    | ~ bird(X1) ),
    inference(csr,[status(thm)],[98,5])).

cnf(100,plain,
    ( eats(X1,X2)
    | ~ eats(X3,X4)
    | ~ plant(X4)
    | ~ plant(X2)
    | ~ snail(X3)
    | ~ bird(X1) ),
    inference(csr,[status(thm)],[99,21])).

cnf(103,plain,
    ( eats(X1,X2)
    | ~ plant(snail_food_of(X3))
    | ~ plant(X2)
    | ~ snail(X3)
    | ~ bird(X1) ),
    inference(spm,[status(thm)],[100,25,theory(equality)])).

cnf(259,plain,
    ( eats(X1,X2)
    | ~ plant(X2)
    | ~ snail(X3)
    | ~ bird(X1) ),
    inference(csr,[status(thm)],[103,24])).

cnf(260,plain,
    ( eats(X1,a_grain)
    | ~ snail(X2)
    | ~ bird(X1) ),
    inference(spm,[status(thm)],[259,32,theory(equality)])).

cnf(264,plain,
    ( eats(X1,a_grain)
    | ~ bird(X1) ),
    inference(spm,[status(thm)],[260,10,theory(equality)])).

cnf(265,plain,
    ( eats(a_bird,a_grain) ),
    inference(spm,[status(thm)],[264,8,theory(equality)])).

cnf(269,negated_conjecture,
    ( ~ eats(X1,a_bird)
    | ~ grain(a_grain)
    | ~ animal(a_bird)
    | ~ animal(X1) ),
    inference(spm,[status(thm)],[26,265,theory(equality)])).

cnf(271,plain,
    ( eats(X1,a_bird)
    | eats(X1,X2)
    | ~ plant(a_grain)
    | ~ plant(X2)
    | ~ bird(a_bird)
    | ~ fox(X1) ),
    inference(spm,[status(thm)],[64,265,theory(equality)])).

cnf(277,negated_conjecture,
    ( ~ eats(X1,a_bird)
    | $false
    | ~ animal(a_bird)
    | ~ animal(X1) ),
    inference(rw,[status(thm)],[269,11,theory(equality)])).

cnf(278,negated_conjecture,
    ( ~ eats(X1,a_bird)
    | $false
    | $false
    | ~ animal(X1) ),
    inference(rw,[status(thm)],[277,29,theory(equality)])).

cnf(279,negated_conjecture,
    ( ~ eats(X1,a_bird)
    | ~ animal(X1) ),
    inference(cn,[status(thm)],[278,theory(equality)])).

cnf(282,plain,
    ( eats(X1,a_bird)
    | eats(X1,X2)
    | $false
    | ~ plant(X2)
    | ~ bird(a_bird)
    | ~ fox(X1) ),
    inference(rw,[status(thm)],[271,32,theory(equality)])).

cnf(283,plain,
    ( eats(X1,a_bird)
    | eats(X1,X2)
    | $false
    | ~ plant(X2)
    | $false
    | ~ fox(X1) ),
    inference(rw,[status(thm)],[282,8,theory(equality)])).

cnf(284,plain,
    ( eats(X1,a_bird)
    | eats(X1,X2)
    | ~ plant(X2)
    | ~ fox(X1) ),
    inference(cn,[status(thm)],[283,theory(equality)])).

cnf(294,negated_conjecture,
    ( ~ eats(a_fox,a_bird) ),
    inference(spm,[status(thm)],[279,28,theory(equality)])).

cnf(298,plain,
    ( eats(X1,a_bird)
    | eats(X1,a_grain)
    | ~ fox(X1) ),
    inference(spm,[status(thm)],[284,32,theory(equality)])).

cnf(301,plain,
    ( eats(a_fox,a_grain)
    | eats(a_fox,a_bird) ),
    inference(spm,[status(thm)],[298,7,theory(equality)])).

cnf(306,plain,
    ( eats(a_fox,a_grain) ),
    inference(sr,[status(thm)],[301,294,theory(equality)])).

cnf(311,plain,
    ( eats(X1,X2)
    | ~ plant(a_grain)
    | ~ plant(X2)
    | ~ fox(a_fox)
    | ~ wolf(X1) ),
    inference(spm,[status(thm)],[59,306,theory(equality)])).

cnf(321,plain,
    ( eats(X1,X2)
    | $false
    | ~ plant(X2)
    | ~ fox(a_fox)
    | ~ wolf(X1) ),
    inference(rw,[status(thm)],[311,32,theory(equality)])).

cnf(322,plain,
    ( eats(X1,X2)
    | $false
    | ~ plant(X2)
    | $false
    | ~ wolf(X1) ),
    inference(rw,[status(thm)],[321,7,theory(equality)])).

cnf(323,plain,
    ( eats(X1,X2)
    | ~ plant(X2)
    | ~ wolf(X1) ),
    inference(cn,[status(thm)],[322,theory(equality)])).

cnf(328,plain,
    ( eats(X1,a_grain)
    | ~ wolf(X1) ),
    inference(spm,[status(thm)],[323,32,theory(equality)])).

cnf(331,plain,
    ( eats(a_wolf,a_grain) ),
    inference(spm,[status(thm)],[328,6,theory(equality)])).

cnf(336,plain,
    ( ~ grain(a_grain)
    | ~ wolf(a_wolf) ),
    inference(spm,[status(thm)],[19,331,theory(equality)])).

cnf(344,plain,
    ( $false
    | ~ wolf(a_wolf) ),
    inference(rw,[status(thm)],[336,11,theory(equality)])).

cnf(345,plain,
    ( $false
    | $false ),
    inference(rw,[status(thm)],[344,6,theory(equality)])).

cnf(346,plain,
    ( $false ),
    inference(cn,[status(thm)],[345,theory(equality)])).

cnf(347,plain,
    ( $false ),
    346,
    [proof]).

%------------------------------------------------------------------------------
% File       : Otter---3.3
% Problem    : PUZ001+1 : TPTP v2.0.0
% Transform  : add_equality:r
% Format     : otter:none:set(auto),clear(print_given)
% Command    : otter-script %s

% Computer   : art05.cs.miami.edu
% Model      : i686 unknown
% CPU        : Intel(R) Pentium(R) 4 CPU 2.80GHz @ 2793MHz
% Memory     : 1000MB
% OS         : Linux 2.4.22-21mdk-i686-up-4GB
% CPULimit   : 600s

% Result     : Theorem 0.0s
% Output     : Refutation 0.0s
% Statistics : Number of clauses     :   23 (  27 expanded)
%              Depth                 :    7
%              Number of atoms       :   35 (  40 expanded)
%              Maximal clause size   :    4 (   2 average)
%              Maximal term depth    :    2 (   1 average)
% Verified   : 

% Comments   : 
%------------------------------------------------------------------------------
%----TSTP SOLUTION
% 1 [] -lives(A)|equal(A,agatha)|equal(A,butler)|equal(A,charles).
cnf(1,initial,
    ( ~lives(A)
    | equal(A,agatha)
    | equal(A,butler)
    | equal(A,charles) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 2 [] -killed(A,B)|hates(A,B).
cnf(2,initial,
    ( ~killed(A,B)
    | hates(A,B) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 3 [] -killed(A,B)| -richer(A,B).
cnf(3,initial,
    ( ~killed(A,B)
    | ~richer(A,B) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 4 [] -hates(agatha,A)| -hates(charles,A).
cnf(4,initial,
    ( ~hates(agatha,A)
    | ~hates(charles,A) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 5 [] -hates(agatha,A)|hates(butler,A).
cnf(5,initial,
    ( ~hates(agatha,A)
    | hates(butler,A) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 6 [] -hates(A,$f1(A)).
cnf(6,initial,
    ( ~hates(A,sk_f1(A)) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 7 [] -equal(agatha,butler).
cnf(7,initial,
    ( ~equal(agatha,butler) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 8 [copy,7,flip.1] -equal(butler,agatha).
cnf(8,derived,
    ( ~equal(butler,agatha) ),
    inference(flip,[status(thm)],[
        inference(copy,[status(thm)],[7]),theory(equality)]),
    [iquote('copy,7,flip.1')]).

% 9 [] -killed(agatha,agatha).
cnf(9,initial,
    ( ~killed(agatha,agatha) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 11 [] lives($c1).
cnf(11,initial,
    ( lives(sk_c1) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 12 [] killed($c1,agatha).
cnf(12,initial,
    ( killed(sk_c1,agatha) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 16 [] equal(A,butler)|hates(agatha,A).
cnf(16,initial,
    ( equal(A,butler)
    | hates(agatha,A) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 17 [] richer(A,agatha)|hates(butler,A).
cnf(17,initial,
    ( richer(A,agatha)
    | hates(butler,A) ),
    file('PUZ001+1+eq_r.in',unknown),
    []).

% 19 [hyper,12,2] hates($c1,agatha).
cnf(19,derived,
    ( hates(sk_c1,agatha) ),
    inference(hyper,[status(thm)],[12,2]),
    [iquote('hyper,12,2')]).

% 22 [para_into,12.1.1,1.2.1,unit_del,9,11,flip.1,flip.2] equal(butler,$c1)|equal(charles,$c1).
cnf(22,derived,
    ( equal(butler,sk_c1)
    | equal(charles,sk_c1) ),
    inference(flip,[status(thm)],[
        inference(flip,[status(thm)],[
            inference(unit_del,[status(thm)],[
                inference(para_into,[status(thm)],[12,1,theory(equality)]),9,11]),theory(equality)]),theory(equality)]),
    [iquote('para_into,12.1.1,1.2.1,unit_del,9,11,flip.1,flip.2')]).

% 27 [hyper,16,5] equal(A,butler)|hates(butler,A).
cnf(27,derived,
    ( equal(A,butler)
    | hates(butler,A) ),
    inference(hyper,[status(thm)],[16,5]),
    [iquote('hyper,16,5')]).

% 40 [hyper,17,3,12] hates(butler,$c1).
cnf(40,derived,
    ( hates(butler,sk_c1) ),
    inference(hyper,[status(thm)],[17,3,12]),
    [iquote('hyper,17,3,12')]).

% 52 [hyper,27,6] equal($f1(butler),butler).
cnf(52,derived,
    ( equal(sk_f1(butler),butler) ),
    inference(hyper,[status(thm)],[27,6]),
    [iquote('hyper,27,6')]).

% 66 [para_from,52.1.1,6.1.2] -hates(butler,butler).
cnf(66,derived,
    ( ~hates(butler,butler) ),
    inference(para_from,[status(thm)],[52,6,theory(equality)]),
    [iquote('para_from,52.1.1,6.1.2')]).

% 87,86 [para_into,66.1.2,22.1.1,unit_del,40] equal(charles,$c1).
cnf(87,derived,
    ( equal(charles,sk_c1) ),
    inference(unit_del,[status(thm)],[
        inference(para_into,[status(thm)],[66,22,theory(equality)]),40]),
    [iquote('para_into,66.1.2,22.1.1,unit_del,40')]).

% 92 [back_demod,4,demod,87] -hates(agatha,A)| -hates($c1,A).
cnf(92,derived,
    ( ~hates(agatha,A)
    | ~hates(sk_c1,A) ),
    inference(demod,[status(thm)],[
        inference(back_demod,[status(thm)],[4]),87,theory(equality)]),
    [iquote('back_demod,4,demod,87')]).

% 104 [hyper,92,16,19,flip.1] equal(butler,agatha).
cnf(104,derived,
    ( equal(butler,agatha) ),
    inference(flip,[status(thm)],[
        inference(hyper,[status(thm)],[92,16,19]),theory(equality)]),
    [iquote('hyper,92,16,19,flip.1')]).

% 106 [binary,104.1,8.1] $F.
cnf(106,derived,
    ( $false ),
    inference(binary,[status(thm)],[104,8]),
    [iquote('binary,104.1,8.1')]).

%------------------------------------------------------------------------------
%----ORIGINAL SYSTEM OUTPUT
% ----- Otter 3.3, August 2003 -----
% The process was started by tptp on art05.cs.miami.edu,
% Mon Jun  6 00:58:37 2005
% The command was "/home/graph/tptp/Systems/Otter---3.3/otter".  The process ID is 28388.
% 
% set(prolog_style_variables).
% set(tptp_eq).
% set(auto).
%    dependent: set(auto1).
%    dependent: set(process_input).
%    dependent: clear(print_kept).
%    dependent: clear(print_new_demod).
%    dependent: clear(print_back_demod).
%    dependent: clear(print_back_sub).
%    dependent: set(control_memory).
%    dependent: assign(max_mem, 12000).
%    dependent: assign(pick_given_ratio, 4).
%    dependent: assign(stats_level, 1).
%    dependent: assign(max_seconds, 10800).
% clear(print_given).
% 
% formula_list(usable).
% all A equal(A,A).
% exists X (lives(X)&killed(X,agatha)).
% lives(agatha).
% lives(butler).
% lives(charles).
% all X (lives(X)->equal(X,agatha)|equal(X,butler)|equal(X,charles)).
% all X Y (killed(X,Y)->hates(X,Y)).
% all X Y (killed(X,Y)-> -richer(X,Y)).
% all X (hates(agatha,X)-> -hates(charles,X)).
% all X (-equal(X,butler)->hates(agatha,X)).
% all X (-richer(X,agatha)->hates(butler,X)).
% all X (hates(agatha,X)->hates(butler,X)).
% all X exists Y (-hates(X,Y)).
% -equal(agatha,butler).
% -killed(agatha,agatha).
% end_of_list.
% 
% -------> usable clausifies to:
% 
% list(usable).
% 0 [] equal(A,A).
% 0 [] lives($c1).
% 0 [] killed($c1,agatha).
% 0 [] lives(agatha).
% 0 [] lives(butler).
% 0 [] lives(charles).
% 0 [] -lives(X)|equal(X,agatha)|equal(X,butler)|equal(X,charles).
% 0 [] -killed(X,Y)|hates(X,Y).
% 0 [] -killed(X,Y)| -richer(X,Y).
% 0 [] -hates(agatha,X)| -hates(charles,X).
% 0 [] equal(X,butler)|hates(agatha,X).
% 0 [] richer(X,agatha)|hates(butler,X).
% 0 [] -hates(agatha,X)|hates(butler,X).
% 0 [] -hates(X,$f1(X)).
% 0 [] -equal(agatha,butler).
% 0 [] -killed(agatha,agatha).
% end_of_list.
% 
% SCAN INPUT: prop=0, horn=0, equality=1, symmetry=0, max_lits=4.
% 
% This ia a non-Horn set with equality.  The strategy will be
% Knuth-Bendix, ordered hyper_res, factoring, and unit
% deletion, with positive clauses in sos and nonpositive
% clauses in usable.
% 
%    dependent: set(knuth_bendix).
%    dependent: set(anl_eq).
%    dependent: set(para_from).
%    dependent: set(para_into).
%    dependent: clear(para_from_right).
%    dependent: clear(para_into_right).
%    dependent: set(para_from_vars).
%    dependent: set(eq_units_both_ways).
%    dependent: set(dynamic_demod_all).
%    dependent: set(dynamic_demod).
%    dependent: set(order_eq).
%    dependent: set(back_demod).
%    dependent: set(lrpo).
%    dependent: set(hyper_res).
%    dependent: set(unit_deletion).
%    dependent: set(factor).
% 
% ------------> process usable:
% ** KEPT (pick-wt=11): 1 [] -lives(A)|equal(A,agatha)|equal(A,butler)|equal(A,charles).
% ** KEPT (pick-wt=6): 2 [] -killed(A,B)|hates(A,B).
% ** KEPT (pick-wt=6): 3 [] -killed(A,B)| -richer(A,B).
% ** KEPT (pick-wt=6): 4 [] -hates(agatha,A)| -hates(charles,A).
% ** KEPT (pick-wt=6): 5 [] -hates(agatha,A)|hates(butler,A).
% ** KEPT (pick-wt=4): 6 [] -hates(A,$f1(A)).
% ** KEPT (pick-wt=3): 8 [copy,7,flip.1] -equal(butler,agatha).
% ** KEPT (pick-wt=3): 9 [] -killed(agatha,agatha).
% 
% ------------> process sos:
% ** KEPT (pick-wt=3): 10 [] equal(A,A).
% ** KEPT (pick-wt=2): 11 [] lives($c1).
% ** KEPT (pick-wt=3): 12 [] killed($c1,agatha).
% ** KEPT (pick-wt=2): 13 [] lives(agatha).
% ** KEPT (pick-wt=2): 14 [] lives(butler).
% ** KEPT (pick-wt=2): 15 [] lives(charles).
% ** KEPT (pick-wt=6): 16 [] equal(A,butler)|hates(agatha,A).
% ** KEPT (pick-wt=6): 17 [] richer(A,agatha)|hates(butler,A).
%   Following clause subsumed by 10 during input processing: 0 [copy,10,flip.1] equal(A,A).
% 
% ======= end of input processing =======
% 
% =========== start of search ===========
% 
% -------- PROOF -------- 
% 
% ----> UNIT CONFLICT at   0.01 sec ----> 106 [binary,104.1,8.1] $F.
% 
% Length of proof is 10.  Level of proof is 6.
% 
% ---------------- PROOF ----------------
% 
% 1 [] -lives(A)|equal(A,agatha)|equal(A,butler)|equal(A,charles).
% 2 [] -killed(A,B)|hates(A,B).
% 3 [] -killed(A,B)| -richer(A,B).
% 4 [] -hates(agatha,A)| -hates(charles,A).
% 5 [] -hates(agatha,A)|hates(butler,A).
% 6 [] -hates(A,$f1(A)).
% 7 [] -equal(agatha,butler).
% 8 [copy,7,flip.1] -equal(butler,agatha).
% 9 [] -killed(agatha,agatha).
% 11 [] lives($c1).
% 12 [] killed($c1,agatha).
% 16 [] equal(A,butler)|hates(agatha,A).
% 17 [] richer(A,agatha)|hates(butler,A).
% 19 [hyper,12,2] hates($c1,agatha).
% 22 [para_into,12.1.1,1.2.1,unit_del,9,11,flip.1,flip.2] equal(butler,$c1)|equal(charles,$c1).
% 27 [hyper,16,5] equal(A,butler)|hates(butler,A).
% 40 [hyper,17,3,12] hates(butler,$c1).
% 52 [hyper,27,6] equal($f1(butler),butler).
% 66 [para_from,52.1.1,6.1.2] -hates(butler,butler).
% 87,86 [para_into,66.1.2,22.1.1,unit_del,40] equal(charles,$c1).
% 92 [back_demod,4,demod,87] -hates(agatha,A)| -hates($c1,A).
% 104 [hyper,92,16,19,flip.1] equal(butler,agatha).
% 106 [binary,104.1,8.1] $F.
% 
% ------------ end of proof -------------
% 
% 
% Search stopped by max_proofs option.
% 
% 
% Search stopped by max_proofs option.
% 
% ============ end of search ============
% 
% -------------- statistics -------------
% clauses given                 32
% clauses generated            335
% clauses kept                 100
% clauses forward subsumed     281
% clauses back subsumed         22
% Kbytes malloced              223
% 
% ----------- times (seconds) -----------
% user CPU time          0.01          (0 hr, 0 min, 0 sec)
% system CPU time        0.01          (0 hr, 0 min, 0 sec)
% wall-clock time        0             (0 hr, 0 min, 0 sec)
% hyper_res time         0.00
% para_into time         0.00
% para_from time         0.00
% for_sub time           0.00
% back_sub time          0.00
% conflict time          0.00
% demod time             0.00
% 
% That finishes the proof of the theorem.
% 
% Process 28388 finished Mon Jun  6 00:58:37 2005
% Otter interrupted
% PROOF FOUND
% 
%------------------------------------------------------------------------------

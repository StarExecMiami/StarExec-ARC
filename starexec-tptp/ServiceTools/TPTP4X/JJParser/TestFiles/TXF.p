tff(a0,axiom,[a,b] = [c,d]).

tff(boolean_tuple,axiom,[![X:$i]:p(X),b] = [c,d]).

tff(var_1, type, n: $int).
tff(localvar_1, type, i: $int).
tff(require_axiom1, axiom, $greatereq(n, 1)).
tff(fib_loop_consec, conjecture,
    ( $less(i, n)
   => ( ( $less(0, i)
        & $lesseq(i, n) )
     => $let([a:$int,b:$int],[a := b, b := $sum(a, b)],
             $let(i:$int,i := $sum(i, 1),
                  ( ( $less(0, i)
                    & $lesseq(i, n) )
                  & $true ) ) ) ) )).

tff(an,axiom,p([a,s,d])).

tff(p_type,type,p: ($i * $o * $int) > $o ).
tff(q_type,type,q: ($int * $i) > $o ).
tff(me_type,type,me: $i ).
tff(fool_1,axiom,! [X: $int] : p(me,! [Y: $i] : q(X,Y),27) ).

tff(p_type,type,p: $i > $o ).
tff(q_type,type,p: $o > $o ).
tff(me_type,type,me: $i ).
tff(fool_2,axiom,q((~p(me)) != q(me))).

tff(implies_type,type,implies: ($o * $o) > $o).
tff(implies_defn,axiom, ! [X: $o,Y: $o]: (implies(X,Y) <=> ((~X) | Y))).

tff(p_type,type,p: ([$int,$i,$o] * $o * $int) > $o ).
tff(f_type,type,q: ($int * $i) > $o ).
tff(me_type,type,me: $i ).
tff(tuples_1,axiom,! [X: $int] : p([33,me,$true],! [Y: $i] : q(X,Y),27) ).

tff(t1_type,type,t1: $tType ).
tff(d_type,type,d: [$i,t1,$int] ).
tff(p_type,type,p: [t1,$i] > $o ).
tff(f_type,type,f: ($o * [$i,t1,$int]) > [t1,$i] ).
tff(tuples_2,axiom,p(f($true,d)) ).

tff(p_type,type,p: $int > $o).
tff(q_type,type,q: $int > $o).
tff(max_type,type,max: ($int * $int) > $int).
tff(ite_1,axiom,! [X:$int,Y:$int] : $ite($greater(X,Y),p(X),p(Y)) ).
tff(ite_2,axiom,! [X:$int,Y:$int] : q($ite($greater(X,Y),X,Y)) ).
tff(max_defn,axiom,! [X: $int,Y: $int]: (max(X,Y) = $ite($greatereq(X,Y),X,Y))).
tff(max_property,axiom,! [X: $int,Y: $int]: $ite(max(X,Y) = X,$greatereq(X,Y),$greatereq(Y,X))).

tff(p_type,type,p: [$int,$int] > $o).
tff(d_type,type,d: [$int,$int]).
tff(ite_3,axiom,! [X:$int,Y:$int] : p($ite($greater(X,Y),[X,Y],[Y,X])) ).
tff(ite_4,axiom,! [X:$int,Y:$int] : (d = $ite($greater(X,Y),[X,Y],[Y,X])) ).

tff(p_type,type,p: $int > $o ).
tff(let_1,axiom,$let(c: $int,c:= 27,p(c))).

tff(i_type,type,i: $int).
tff(j_type,type,j: $int).
tff(f_type,type,f: ($int * $int * $int * $int) > $rat).
tff(p_type,type,p: $rat > $o ).
tff(let_2,axiom,$let(ff: ($int * $int) > $rat, ff(X,Y):= f(X,X,Y,Y), p(ff(i,j))) ).

tff(array_type,type,array: $int > $real).
tff(p_type,type,p: $real > $o).
tff(let_3,axiom,$let(array: $int > $real,array(I):= $ite(I = 3,5.2,array(I)),p($sum(array(2),array(3)))) ).

tff(a_type,type,a: $int).
tff(b_type,type,b: $int).
tff(p_type,type,p: ($int * $int) > $o).
tff(let_tuple_1,axiom,$let([a: $int,b: $int],[a:= b,b:= a],p(a,b))).

tff(i_type,type,i: $int).
tff(f_type,type,f: ($int * $int * $int * $int) > $int).
tff(p_type,type,p: $int > $o ).
tff(let_tuple_2,axiom,
    $let([ff: ($int * $int) > $int, gg: $int > $int],
         [ff(X,Y):= f(X,X,Y,Y), gg(Z):= f(Z,Z,Z,Z)],
         p(ff(i,gg(i)))) ).

%----Not allowed
% tff(p_type,type,p: ($int * $int) > $o).
% tff(not_let_tuple,axiom,
%     $let([a,b]: [$int,$int],[a:= b,b:= a],p(a,b)) ).

tff(i_type,type,i: $int).
tff(f_type,type,f: ($int * $int * $int * $int) > $int).
tff(p_type,type,p: $int > $o ).
tff(let_tuple_3,axiom,
    $let(ff: ($int * $int) > $int,
         ff(X,Y):= f(X,X,Y,Y),
         $let(gg: $int > $int,gg(Z):= ff(Z,Z),p(gg(i)) ) ) ).

tff(p_type,type,p: ($int * $int) > $o ).
tff(q_type,type,q: [$int,$int] > $o ).
tff(let_tuple_4,axiom,$let([a:$int,b:$int], [a,b]:= [27,28], p(a,b)) ).
tff(let_tuple_5,axiom,$let(d: [$int,$int], d:= [27,28],q(d)) ).

%----Not allowed
% tff(test,axiom,$let([a,b]: [$int,$int], [a,b]:= [27,28], p(a,b)) ).

tff(cc_type,type,cc: $int).
tff(dd_type,type,dd: $int).
tff(let_ite_1,axiom,
    $let([aa: $int,bb: $int],
         [aa,bb]:= $ite($greater(cc,dd),[cc,dd],[dd,cc]),
         p(aa,bb))).

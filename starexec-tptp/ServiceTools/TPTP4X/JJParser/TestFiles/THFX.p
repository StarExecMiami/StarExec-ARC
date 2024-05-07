% thf(t1_type,type,t1: $tType ).
% thf(d_type,type,d: [$i,t1,$int] ).
% thf(p_type,type,p: [t1,$i] > $o ).
% thf(f_type,type,f: $o > [$i,t1,$int] > [t1,$i] ).
% thf(tuples_1,axiom,p @ (f @ $true @ d ) ).

thf(p_type,type,p: [$int,$i,$o] > $o > $int > $o ).
thf(q_type,type,q: $int > $i > $o ).
thf(r_type,type,r: $int > $o).
thf(me_type,type,me: $i ).
thf(tuples_2,axiom,r = (^ [X: $int] : (p @ [33,me,$true] @ (q @ 27 @ me))) ).

thf(q_type,type,q: $int > $o).
thf(max_type,type,max: $int > $int > $int).
thf(ite_1,axiom,! [X:$int,Y:$int] : $ite($greater @ X @ Y,p @ X,p @ Y) ).
thf(ite_2,axiom,! [X:$int,Y:$int] : ( q @ $ite($greater @ X @ Y,X,Y)) ).
thf(max_defn,axiom,! [X: $int,Y: $int]: ((max @ X @ Y) = $ite($greatereq @ X @ Y,X,Y)) ).
thf(max_property,axiom,! [X: $int,Y: $int]: $ite((max @ X @ Y) = X,$greatereq @ X @ Y,$greatereq @ Y @ X)).

thf(p_type,type,p: [$int,$int] > $o).
thf(d_type,type,d: [$int,$int]).
thf(ite_3,axiom,! [X:$int,Y:$int] : (p @ $ite($greater @ X @ Y,[X,Y],[Y,X])) ).
thf(ite_4,axiom,! [X:$int,Y:$int] : (d = $ite($greater @ X @ Y,[X,Y],[Y,X])) ).

thf(p_type,type,p: $int > $o ).
thf(let_1,axiom,$let(c: $int,c:= 27,p @ c)).

thf(i_type,type,i: $int).
thf(j_type,type,j: $int).
thf(f_type,type,f: $int > $int > $int > $int > $rat).
thf(p_type,type,p: $rat > $o ).
thf(let_2,axiom,$let(ff: $int > $int > $rat, ff @ X @ Y:= f @ X @ X @ Y @ Y, p @ (ff @ i @ j)) ).

thf(i_type,type,i: $int).
thf(j_type,type,j: $int).
thf(f_type,type,f: $int > $int > $int > $int > $rat).
thf(p_type,type,p: $rat > $o ).
thf(let_2,axiom,$let(ff: $int > $int > $rat, ff := ^ [X: $int,Y: $int] : (f @ X @ X @ Y @ Y), p @ (ff @ i @ j)) ).

thf(array_type,type,array: $int > $real).
thf(p_type,type,p: $real > $o).
thf(let_3,axiom,$let(array: $int > $real,array @ I:= $ite(I = 3,5.2,array @ I),p @ ($sum @ (array @ 2) @ (array @ 3))) ).

thf(a_type,type,a: $int).
thf(b_type,type,b: $int).
thf(p_type,type,p: $int > $int > $o).
thf(let_tuple_1,axiom,$let([a: $int,b: $int],[a:= b,b:= a],p @ a @ b)).

thf(i_type,type,i: $int).
thf(f_type,type,f: $int > $int > $int > $int > $int).
thf(p_type,type,p: $int > $o ).
thf(let_tuple_2,axiom,
    $let([ff: $int > $int > $int, gg: $int > $int],
         [ff @ X @ Y:= f @ X @ X @ Y @ Y, gg @ Z:= f @ Z @ Z @ Z @ Z],
         p @ (ff @ i @ ( gg @ i))) ).

thf(i_type,type,i: $int).
thf(f_type,type,f: $int > $int > $int > $int > $int).
thf(p_type,type,p: $int > $o ).
thf(let_tuple_3,axiom,
    $let(ff: $int > $int > $int,
         ff @ X @ Y:= f @ X @ X @ Y @ Y,
         $let(gg: $int > $int,gg @ Z:= ff @ Z @ Z,p @ (gg @ i)) ) ).

thf(p_type,type,p: $int > $int > $o ).
thf(q_type,type,q: [$int,$int] > $o ).
thf(let_tuple_4,axiom,$let([a:$int,b:$int], [a,b]:= [27,28], p @ a @ b) ).
thf(let_tuple_5,axiom,$let(d: [$int,$int], d:= [27,28],q @ d) ).

thf(cc_type,type,cc: $int).
thf(dd_type,type,dd: $int).
thf(let_ite_1,axiom,
    $let([aa: $int,bb: $$int],
         [aa,bb]:= $ite($greater @ cc @ dd,[cc,dd],[dd,cc]),
         p @ aa @ bb) ).


tff(tf_par,axiom,
    $let_tf(
      [ ! [X1: $int,X2: $int] : g(X1,X2) = h(X1,X1,X1)
      , ! [X3: $int] : i(X3) = k ]
    , p(g(a,b),c,i(d)) )).

tff(tf,axiom,
    $let_tf(
      ! [X1: $int,X2: $int] : g(X1,X2) = h(X1,X1,X1)
    , p(g(a,b),c) )).

tff(ff_par,axiom,
    $let_ff(
      [ ! [Y1: $int,Y2: $int] : p(Y1,Y2) <=> q(Y1)
      , ! [Y3: $int] : r(Y3) <=> $true ]
    , ( p(h(a,a,a),b)
     => r(a) ) )).

tff(ff,axiom,
    $let_ff(
      ! [Y1: $int,Y2: $int] : p(Y1,Y2) <=> q(Y1)
    , p(h(a,a,a),b) )).

tff(tt,axiom,
    ! [X: $int] : 
      p($let_tt(
          ! [Z1: $int] : f(Z1) = g(Z1,b)
        , f(a)),X) ).

tff(combined,axiom,
    ! [X: $int] :
      $let_ff(
        ! [Y1: $int,Y2: $int] : p(Y1,Y2) <=> q(Y1)
      , $let_tf(
          ! [X1: $int,X2: $int] : g(X1,X2) = h(X1,X1,X1)
        , p($let_tt(
              ! [Z1: $int] : f(Z1) = g(Z1,b)
            , f(a)),X) )) ).

tff(with_ite,axiom,
    p($let_ft(
        ! [Y1: $int,Y2: $int] : p(Y1,Y2) <=> q(Y1)
      , $ite_t(p(a,b),a,b))) ).

%----Let binders
tff(let_binders,axiom,(
    ! [X: $i] :
      $let_ff(
        ! [Y1: $i,Y2: $i] :
          ( q(Y1,Y2)
        <=> p(Y1) )
      , ( q($let_tt(! [Z1: $i] : f(Z1) = g(Z1,b), f(a)),X)
        & p($let_ft(! [Y3: $i] : ! [Y4: $i] : ( q(Y3,Y4) <=> $ite_f(Y3 = Y4, q(a,a), q(Y3,Y4) ) ), $ite_t(q(b,b), f(a), f(X)))) ) ) )).

tff(v1_type,type,v1: $int).
tff(v2_type,type,v2: $int).
tff(ordered_p,axiom,
    $let([large: $int,small: $int],
         [large,small]:= $ite($greater(v1,v2),[v1,v2],[v2,v1]),
         p(large,small)) ).

tff(x,type,x:$int).
tff(y,type,y:$int).
tff(t,type,t:$int).
tff(x_leq_y,conjecture,
    $let([x:$int,y:$int,t:$int],
         [x,y,t] := $ite($greater(x,y),
                         $let(t:$int, t := x,
                         $let(x:$int, x := y,
                         $let(y:$int, y := t,
                              [x,y,t]))),
                         [x,y,t]),
         $lesseq(x,y))).


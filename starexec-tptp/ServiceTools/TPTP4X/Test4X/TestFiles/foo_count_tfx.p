tff(ww,type,ww: $o > $o ).

tff(large1,axiom,
    ! [X: $o] : 
      (X) = 
      ( ? [Y: $o] :
          Y = ww(Y) )).

tff(large2,axiom,
    ( ! [X: $o] : (X) ) =
    ( ? [Y: $o] : Y = ww(Y) )).

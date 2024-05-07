tff(p,type,
    p: $o > $o ).

tff(1,axiom,
    $true ).

tff('2a',axiom,
    p($true) ).

tff('2b',axiom,
    $true = $true ).

tff(3,axiom,
    ! [X: $o] : (X) ).

tff(4,axiom,
    ! [X: $o] :
      ( (X)
      | $false ) ).

tff(5,axiom,
    ! [X: $o] :
      ( $false
      | (X) ) ).

tff(6,axiom,
    ! [X: $o] :
      ( $false
      | ( (X) = $true ) ) ).

tff(7,axiom,
    ! [X: $o] : ( (X) = $true ) ).

tff(8,axiom,
    ! [X: $o] : ( $true = (X) ) ).

tff(z,type,
    z: $o > $o ).

tff(x,type,
    x: ( $i * $o * $i ) > $o ).

tff(q,type,
    q: $o > $o ).

tff(c1,type,
    c1: $i ).

tff(c2,type,
    c2: $i ).

tff(9,axiom,
    z($true) ).

tff(10,axiom,
    x(c1,$true,c2) ).

tff(11,axiom,
    p(
      ! [X: $int] : $true) ).

tff(12,axiom,
    q(
      $true
    | $false) ).

tff(13,axiom,
    ! [X: $o] :
      ( ( (X)
        | $true )
      = $true ) ).

tff(14,axiom,
    ! [X: $o] :
      ( ( (X) = $true )
      = $true ) ).

tff(15,axiom,
    ! [X: $o] : ( (X) = (X) ) ).

tff(r,type,
    r: $o > $o ).

tff(p0,type,
    p0: ( $i * $i * $i * $i ) > $o ).

tff(p1,type,
    p1: $o > $o ).

tff(p3,type,
    p3: $o > $o ).

tff(p21,type,
    p21: $o > $o ).

tff(a,type,
    a: $i ).

tff(a1,type,
    a1: $i ).

tff(a2,type,
    a2: $i ).

tff(a3,type,
    a3: ( $i * $i ) > $i ).

tff(a4,type,
    a4: $i ).

tff(b,type,
    b: $i ).

tff(b1,type,
    b1: $i ).

tff(b2,type,
    b2: $i ).

tff(b20,type,
    b20: $i ).

tff(d1,type,
    d1: $i ).

tff(d2,type,
    d2: $i ).

tff(d3,type,
    d3: $i ).

tff(d4,type,
    d4: $i ).

tff(f1,type,
    f1: ( $i * $i * $i * $i ) > $i ).

tff(18,axiom,
    p0(a1,a2,a3(b1,b2),a4) ).

tff(19,axiom,
    ! [X: $int] : r(( X = 0 )) ).

tff(20,axiom,
    p1(( a = b )) ).

tff(21,axiom,
    p3(( f1(d1,d2,d3,d4) = b20 )) ).

tff(22,axiom,
    ! [X: $o] : p21(X) ).

tff(ww,type,
    ww: $o > $o ).

tff(c,type,
    c: $o ).

tff(ee,type,
    ee: ( $o * $o ) > $o ).

tff(qq,type,
    qq: $o > $o ).

tff(constant,type,
    constant: $i ).

tff(large,axiom,
    ! [X: $o] :
      ( qq(
          ! [Z: $o] :
            ee(
              (Z)
            & ( ( (X) = ww(Z) )
              | c ),
              $false))
      | (X)
      | ( (X)
        = ( ? [Y: $o] : ( (Y) = ww(Y) ) ) ) ) ).

tff(large2,axiom,
    ! [X: $o,Y: $i] :
      z(
        (X)
      | ( Y = constant )) ).

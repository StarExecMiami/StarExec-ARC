fof(a,axiom, ~ a).

thf(a,axiom,~ (a)).

thf(a,axiom,p @ ~).

thf(antisymmetry_r2_hidden, axiom,  
    ! [A: $i] :  
    ! [B: $i] :  
      ( ( ( r2_hidden @ A )  @ B)  
     => ( ~ ( (r2_hidden @ B)  @ A ) ) )).


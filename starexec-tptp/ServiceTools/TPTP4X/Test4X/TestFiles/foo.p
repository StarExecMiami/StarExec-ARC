thf(a_type,type,(
    a: $i )).

thf(p_type,type,
    p: $i > $o ).

thf(role_assumption,assumption,
    ( p @ a )).

thf(role_lemma,lemma,
    ( p @ a )).

thf(role_theorem,theorem,
    ( p @ a )).

thf(role_unknown,unknown,
    ( p @ a )).

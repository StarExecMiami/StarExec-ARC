%--------------------------------------------------------------------------
cnf(a_group,hypothesis,
    ( group(f71,f72) )).

cnf(f73_is_the_identity,hypothesis,
    ( identity(f71,f72,f73) )).

cnf(x_squared_is_identity,hypothesis,
    ( ~ member(X,f71)
    | apply_to_two_arguments(f72,X,X) = f73 )).

cnf(prove_the_group_is_commutative,negated_conjecture,
    ( ~ commutes(f71,f72) )).

%--------------------------------------------------------------------------


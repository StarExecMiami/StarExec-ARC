fof(conj,conjecture,
    ( ( a & a & b ) | ( ~b & c & c ) )  ).

fof(a,axiom,a).

fof(c,axiom,c).

fof(not_conj,negated_conjecture,
    ~ ( ( a & a & b ) | ( ~b & c & c ) ),
    inference(negate_conj,[status(cth)],[conj])).

cnf(conj1,plain,
    ( ~a | ~a | ~b ),
    inference(fofcnf,[status(thm)],[not_conj])).

cnf(conj2,plain,
    ( b | ~c | ~c ),
    inference(fofcnf,[status(thm)],[not_conj])).

cnf(a_cnf,plain,a,
    inference(fofcnf,[status(thm)],[a])).

cnf(c_cnf,plain,c,
    inference(fofcnf,[status(thm)],[c])).

cnf(not_a_not_b,plain,
    ( ~a | ~b ),
    inference(resolve,[status(thm)],[a_cnf,conj1])).

cnf(not_b,plain,
    ( ~b ),
    inference(resolve,[status(thm)],[a_cnf,not_a_not_b])).

cnf(b_not_c,plain,
    ( b | ~c ),
    inference(resolve,[status(thm)],[c_cnf,conj2])).

cnf(b,plain,
    ( b ),
    inference(resolve,[status(thm)],[c_cnf,b_not_c])).

cnf(done,plain,
    $false,
    inference(resolve,[status(thm)],[b,not_b])).

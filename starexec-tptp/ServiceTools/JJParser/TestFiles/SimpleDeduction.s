fof(a_implies_b,axiom,
    ( a
   => b ),
    introduced(black_magic,[status(foo)])).

fof(b,plain,(
    b ),
    inference(magic,[status(thm),X,$fot(Y)],[a_implies_b,a])).

fof(a,axiom,(
    a )).

fof(c_implies_d,axiom,
    ( c
   => d ),
    file(foo,blah)).

fof(d,plain,(
    d ),
    inference(magic,[status(thm)],[c_implies_d,c])).

fof(c,axiom,(
    c )).

%fof(b,conjecture,(
%    b )).
%
%cnf(inferred,plain,$false,inference(magic,[status(thm)],[a_implies_b,a,b])).


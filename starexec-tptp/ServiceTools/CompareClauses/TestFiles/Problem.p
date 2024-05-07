fof(t3_xboole_1,axiom,(
    ! [A] :
      ( subset(A,empty_set)
     => A = empty_set ) )).

fof(f39,plain,(
    ! [X0] :
      ( ~ subset(X0,empty_set)
      | empty_set = X0 ) ),
    inference(cnf_transformation,[],[f24])).

fof(f24,plain,(
    ! [X0] :
      ( ~ subset(X0,empty_set)
      | empty_set = X0 ) ),
    inference(ennf_transformation,[],[f14])).


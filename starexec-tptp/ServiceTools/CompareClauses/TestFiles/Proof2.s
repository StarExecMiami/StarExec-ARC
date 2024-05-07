fof(f2,axiom,(
    ! [X1,X2] : set_intersection2(X1,X2) = set_intersection2(X2,X1) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',commutativity_k3_xboole_0)).

fof(f25,plain,(
    ! [X3,X4] : set_intersection2(X3,X4) = set_intersection2(X4,X3) ),
    inference(variable_rename,[status(thm)],[f2])).

cnf(f26,plain,
    ( set_intersection2(X1,X2) = set_intersection2(X2,X1) ),
    inference(split_conjunct,[status(thm)],[f25])).


fof(14,axiom,(
    ! [X1] :
      ( subset(X1,empty_set)
     => X1 = empty_set ) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',t3_xboole_1)).

fof(52,plain,(
    ! [X1] :
      ( ~ subset(X1,empty_set)
      | X1 = empty_set ) ),
    inference(fof_nnf,[status(thm)],[14])).

fof(53,plain,(
    ! [X2] :
      ( ~ subset(X2,empty_set)
      | X2 = empty_set ) ),
    inference(variable_rename,[status(thm)],[52])).

cnf(54,plain,
    ( X1 = empty_set
    | ~ subset(X1,empty_set) ),
    inference(split_conjunct,[status(thm)],[53])).

fof(12,axiom,(
    ! [X1,X2,X3] :
      ( subset(X1,X2)
     => subset(set_intersection2(X1,X3),set_intersection2(X2,X3)) ) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',t26_xboole_1)).

fof(47,plain,(
    ! [X1,X2,X3] :
      ( ~ subset(X1,X2)
      | subset(set_intersection2(X1,X3),set_intersection2(X2,X3)) ) ),
    inference(fof_nnf,[status(thm)],[12])).

fof(48,plain,(
    ! [X4,X5,X6] :
      ( ~ subset(X4,X5)
      | subset(set_intersection2(X4,X6),set_intersection2(X5,X6)) ) ),
    inference(variable_rename,[status(thm)],[47])).

cnf(49,plain,
    ( subset(set_intersection2(X1,X2),set_intersection2(X3,X2))
    | ~ subset(X1,X3) ),
    inference(split_conjunct,[status(thm)],[48])).

fof(3,axiom,(
    ! [X1,X2] :
      ( disjoint(X1,X2)
    <=> set_intersection2(X1,X2) = empty_set ) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',d7_xboole_0)).

fof(27,plain,(
    ! [X1,X2] :
      ( ( ~ disjoint(X1,X2)
        | set_intersection2(X1,X2) = empty_set )
      & ( set_intersection2(X1,X2) != empty_set
        | disjoint(X1,X2) ) ) ),
    inference(fof_nnf,[status(thm)],[3])).

fof(28,plain,(
    ! [X3,X4] :
      ( ( ~ disjoint(X3,X4)
        | set_intersection2(X3,X4) = empty_set )
      & ( set_intersection2(X3,X4) != empty_set
        | disjoint(X3,X4) ) ) ),
    inference(variable_rename,[status(thm)],[27])).

cnf(30,plain,
    ( set_intersection2(X1,X2) = empty_set
    | ~ disjoint(X1,X2) ),
    inference(split_conjunct,[status(thm)],[28])).

fof(15,conjecture,(
    ! [X1,X2,X3] :
      ( ( subset(X1,X2)
        & disjoint(X2,X3) )
     => disjoint(X1,X3) ) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',t63_xboole_1)).

fof(19,negated_conjecture,(
    ~ ! [X1,X2,X3] :
        ( ( subset(X1,X2)
          & disjoint(X2,X3) )
       => disjoint(X1,X3) ) ),
    inference(assume_negation,[status(cth)],[15])).

fof(55,negated_conjecture,(
    ? [X1,X2,X3] :
      ( subset(X1,X2)
      & disjoint(X2,X3)
      & ~ disjoint(X1,X3) ) ),
    inference(fof_nnf,[status(thm)],[19])).

fof(56,negated_conjecture,(
    ? [X4,X5,X6] :
      ( subset(X4,X5)
      & disjoint(X5,X6)
      & ~ disjoint(X4,X6) ) ),
    inference(variable_rename,[status(thm)],[55])).

fof(57,negated_conjecture,
    ( subset(esk3_0,esk4_0)
    & disjoint(esk4_0,esk5_0)
    & ~ disjoint(esk3_0,esk5_0) ),
    inference(skolemize,[status(esa)],[56])).

cnf(59,negated_conjecture,
    ( disjoint(esk4_0,esk5_0) ),
    inference(split_conjunct,[status(thm)],[57])).

cnf(71,negated_conjecture,
    ( set_intersection2(esk4_0,esk5_0) = empty_set ),
    inference(spm,[status(thm)],[30,59,theory(equality)])).

cnf(100,negated_conjecture,
    ( subset(set_intersection2(X1,esk5_0),empty_set)
    | ~ subset(X1,esk4_0) ),
    inference(spm,[status(thm)],[49,71,theory(equality)])).

cnf(121,negated_conjecture,
    ( empty_set = set_intersection2(X1,esk5_0)
    | ~ subset(X1,esk4_0) ),
    inference(spm,[status(thm)],[54,100,theory(equality)])).

cnf(60,negated_conjecture,
    ( subset(esk3_0,esk4_0) ),
    inference(split_conjunct,[status(thm)],[57])).

cnf(143,negated_conjecture,
    ( set_intersection2(esk3_0,esk5_0) = empty_set ),
    inference(spm,[status(thm)],[121,60,theory(equality)])).

fof(2,axiom,(
    ! [X1,X2] : set_intersection2(X1,X2) = set_intersection2(X2,X1) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',commutativity_k3_xboole_0)).

fof(25,plain,(
    ! [X3,X4] : set_intersection2(X3,X4) = set_intersection2(X4,X3) ),
    inference(variable_rename,[status(thm)],[2])).

cnf(26,plain,
    ( set_intersection2(X1,X2) = set_intersection2(X2,X1) ),
    inference(split_conjunct,[status(thm)],[25])).

cnf(146,negated_conjecture,
    ( set_intersection2(esk5_0,esk3_0) = empty_set ),
    inference(rw,[status(thm)],[143,26,theory(equality)])).

cnf(58,negated_conjecture,
    ( ~ disjoint(esk3_0,esk5_0) ),
    inference(split_conjunct,[status(thm)],[57])).

cnf(29,plain,
    ( disjoint(X1,X2)
    | set_intersection2(X1,X2) != empty_set ),
    inference(split_conjunct,[status(thm)],[28])).

cnf(73,negated_conjecture,
    ( set_intersection2(esk3_0,esk5_0) != empty_set ),
    inference(spm,[status(thm)],[58,29,theory(equality)])).

cnf(94,negated_conjecture,
    ( set_intersection2(esk5_0,esk3_0) != empty_set ),
    inference(rw,[status(thm)],[73,26,theory(equality)])).

cnf(147,negated_conjecture,
    ( $false ),
    inference(sr,[status(thm)],[146,94,theory(equality)])).

cnf(148,negated_conjecture,
    ( $false ),
    147,
    [proof]).

fof(f12,axiom,(
    ! [X0,X1,X2] :
      ( subset(X0,X1)
     => subset(set_intersection2(X0,X2),set_intersection2(X1,X2)) ) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',t26_xboole_1)).

fof(f27,plain,(
    ! [X0,X1,X2] :
      ( ~ subset(X0,X1)
      | subset(set_intersection2(X0,X2),set_intersection2(X1,X2)) ) ),
    inference(ennf_transformation,[],[f12])).

fof(f47,plain,(
    ! [X2,X0,X1] :
      ( ~ subset(X0,X1)
      | subset(set_intersection2(X0,X2),set_intersection2(X1,X2)) ) ),
    inference(cnf_transformation,[],[f27])).

fof(f15,negated_conjecture,(
    ~ ! [X0,X1,X2] :
        ( ( subset(X0,X1)
          & disjoint(X1,X2) )
       => disjoint(X0,X2) ) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',t63_xboole_1)).

fof(f21,plain,(
    ? [X0,X1,X2] :
      ( subset(X0,X1)
      & disjoint(X1,X2)
      & ~ disjoint(X0,X2) ) ),
    inference(ennf_transformation,[],[f15])).

fof(f22,plain,(
    ? [X0,X1,X2] :
      ( subset(X0,X1)
      & disjoint(X1,X2)
      & ~ disjoint(X0,X2) ) ),
    inference(flattening,[],[f21])).

fof(f29,plain,
    ( subset(sK0,sK1)
    & disjoint(sK1,sK2)
    & ~ disjoint(sK0,sK2) ),
    inference(skolemisation,[status(esa)],[f22])).

fof(f33,plain,(
    subset(sK0,sK1) ),
    inference(cnf_transformation,[],[f29])).

fof(f74,plain,(
    ! [X0] : subset(set_intersection2(sK0,X0),set_intersection2(sK1,X0)) ),
    inference(resolution,[],[f47,f33])).

fof(f3,axiom,(
    ! [X0,X1] :
      ( disjoint(X0,X1)
    <=> set_intersection2(X0,X1) = empty_set ) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',d7_xboole_0)).

fof(f30,plain,(
    ! [X0,X1] :
      ( ( ~ disjoint(X0,X1)
        | set_intersection2(X0,X1) = empty_set )
      & ( set_intersection2(X0,X1) != empty_set
        | disjoint(X0,X1) ) ) ),
    inference(nnf_transformation,[],[f3])).

fof(f44,plain,(
    ! [X0,X1] :
      ( ~ disjoint(X0,X1)
      | set_intersection2(X0,X1) = empty_set ) ),
    inference(cnf_transformation,[],[f30])).

fof(f34,plain,(
    disjoint(sK1,sK2) ),
    inference(cnf_transformation,[],[f29])).

fof(f69,plain,(
    set_intersection2(sK1,sK2) = empty_set ),
    inference(resolution,[],[f44,f34])).

fof(f81,plain,(
    subset(set_intersection2(sK0,sK2),empty_set) ),
    inference(superposition,[],[f74,f69])).

fof(f14,axiom,(
    ! [X0] :
      ( subset(X0,empty_set)
     => empty_set = X0 ) ),
    file('/home/graph/tptp/TPTP/Problems/SEU/SEU140+1.p',t3_xboole_1)).

fof(f24,plain,(
    ! [X0] :
      ( ~ subset(X0,empty_set)
      | empty_set = X0 ) ),
    inference(ennf_transformation,[],[f14])).

fof(f39,plain,(
    ! [X0] :
      ( ~ subset(X0,empty_set)
      | empty_set = X0 ) ),
    inference(cnf_transformation,[],[f24])).

fof(f91,plain,(
    set_intersection2(sK0,sK2) = empty_set ),
    inference(resolution,[],[f81,f39])).

fof(f45,plain,(
    ! [X0,X1] :
      ( disjoint(X0,X1)
      | set_intersection2(X0,X1) != empty_set ) ),
    inference(cnf_transformation,[],[f30])).

fof(f35,plain,(
    ~ disjoint(sK0,sK2) ),
    inference(cnf_transformation,[],[f29])).

fof(f71,plain,(
    set_intersection2(sK0,sK2) != empty_set ),
    inference(resolution,[],[f45,f35])).

fof(f93,plain,(
    $false ),
    inference(subsumption_resolution,[],[f91,f71])).

thf(11,axiom,
    ( ~ ( c )
    | b
    | ~ ( a ) )).

thf(10,plain,
    ( ~ ( c )
    | b
    | ~ ( a ) ),
    inference(magic,[],[11])).

thf(9,axiom,(
    c )).

thf(8,plain,
    ( ~ ( c )
    | b
    | ~ ( a ) ),
    inference(magic,[],[9,10])).

fof(7,plain,
    ( b
    | ~ a ),
    inference(magic,[],[8])).

cnf(6,plain,
    ( b
    | ~ a ),
    inference(magic,[],[7])).

thf(5,conjecture,(
    b )).

thf(i5_3,plain,(
    bb ),
    inference(conjsplit,[conjsplit(leo_conj_split,[])],[5])).

fof(i5_2,plain,(
    bb ),
    inference(magic,[],[i5_3])).

cnf(i5_1,plain,
    ( bb ),
    inference(magic,[],[i5_2])).

thf(i4_5,plain,(
    b ),
    inference(conjsplit,[conjsplit(leo_conj_split,[])],[5])).

fof(i3_5,plain,(
    b ),
    inference(magic,[],[i4_5,10])).

fof(i2_5,plain,(
    b ),
    inference(magic,[],[i3_5])).

cnf(i1_5,plain,
    ( b ),
    inference(magic,[],[i2_5,7])).

cnf(4,plain,
    ( ~ a ),
    inference(magic,[],[i1_5,6])).

cnf(3,plain,
    ( $false ),
    inference(magic,[],[4])).

thf(2,axiom,(
    a )).

fof(i3_2,plain,(
    a ),
    inference(magic,[],[2])).

cnf(i2_2,plain,
    ( a ),
    inference(magic,[],[i3_2])).

cnf(i1_2,plain,
    ( $false ),
    inference(magic,[],[i2_2,i5_1])).

cnf(1,plain,
    ( $false ),
    inference(magic,[],[i1_2,3])).

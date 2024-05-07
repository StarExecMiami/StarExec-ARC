%------------------------------------------------------------------------------
%Removed by character conversion :-op(99,fx,'$').
:-op(100,fx,++).
:-op(100,fx,--).
:-op(150,fy,~).
:-op(405,xfx,'=').
:-op(405,xfx,'~=').
%------------------------------------------------------------------------------
symmetric_member(E,L):-
    member(E,L).

symmetric_member(EqualityLiteral,L):-
    EqualityLiteral =.. [Sign,equal(X,Y)],
    SymmetricEqualityLiteral =.. [Sign,equal(Y,X)],
    member(SymmetricEqualityLiteral,L).
%------------------------------------------------------------------------------
%----Check every member of the first list is a member of the second
all_members([],_).

all_members([H|T],L):-
    symmetric_member(H,L),
    all_members(T,L).
%------------------------------------------------------------------------------
%----Check if a list of literals subsumed another
literals_subsume(SubsumingLiterals,SubsumedLiterals):-
%----Verify to avoid instiating variables
    \+ ( \+ (
        numbervars(SubsumedLiterals,0,_),
        all_members(SubsumingLiterals,SubsumedLiterals))).
%------------------------------------------------------------------------------
%----Set if two clauses have the same literals, modulo variable renaming
%----Need to avoid instantiation here
same_literals([],[],_).
    
same_literals([Literal1|RestOfLiterals1],Literals2,NumberFrom):-
    select(Literal2,Literals2,RestOfLiterals2),
    numbervars(Literal1,NumberFrom,NumberOfVariables),
    numbervars(Literal2,NumberFrom,NumberOfVariables),
    Literal1 == Literal2,
    NextNumberFrom is NumberFrom + NumberOfVariables,
    same_literals(RestOfLiterals1,RestOfLiterals2,NextNumberFrom).

same_literals([EqualityLiteral1|RestOfLiterals1],Literals2,NumberFrom):-
    EqualityLiteral1 =.. [Sign,equal(_,_)],
    select(EqualityLiteral2,Literals2,RestOfLiterals2),
    EqualityLiteral2 =.. [Sign,equal(Y1,Y2)],
    SymmetricEqualityLiteral2 =.. [Sign,equal(Y2,Y1)],
    numbervars(EqualityLiteral1,0,NumberOfVariables),
    numbervars(SymmetricEqualityLiteral2,0,NumberOfVariables),
    EqualityLiteral1 == SymmetricEqualityLiteral2,
    NextNumberFrom is NumberFrom + NumberOfVariables,
    same_literals(RestOfLiterals1,RestOfLiterals2,NextNumberFrom).
%------------------------------------------------------------------------------
%----TSTP conversion procedures
convert_tptp_to_literals((LHS + RHS),Literals):-
    !,
    convert_tptp_to_literals(LHS,LHSLiterals),
    convert_tptp_to_literals(RHS,RHSLiterals),
    append(LHSLiterals,RHSLiterals,Literals).

convert_tptp_to_literals(LHS ~= RHS,[--equal(LHS,RHS)]):-
    !.

convert_tptp_to_literals(LHS = RHS,[++equal(LHS,RHS)]):-
    !.

convert_tptp_to_literals(zfalse,[]):-
    !.

convert_tptp_to_literals(~ ztrue,[]):-
    !.

convert_tptp_to_literals(~ Atom,[--Atom]):-
    !.

convert_tptp_to_literals(Atom,[++Atom]).
%------------------------------------------------------------------------------
extract_name_and_tptp_literals(Clause,Name,Literals):-
    Clause =.. [cnf,Name,_Status,TSTPClause|_],
    !,
    convert_tptp_to_literals(TSTPClause,Literals).

extract_name_and_tptp_literals(input_clause(Name,_Status,Literals),
Name,Literals).
%------------------------------------------------------------------------------
do_comparison(Name1,Literals1,Name2,Literals2,same(Name1,Name2)):-
    same_literals(Literals1,Literals2,0),
    !.

do_comparison(Name1,Literals1,Name2,Literals2,subsumes(Name1,Name2)):-
    literals_subsume(Literals1,Literals2),
    !.

do_comparison(Name1,Literals1,Name2,Literals2,subsumed(Name1,Name2)):-
    literals_subsume(Literals2,Literals1),
    !.

do_comparison(Name1,_,Name2,_,unrelated(Name1,Name2)).
%------------------------------------------------------------------------------
extract_and_do_comparison(Clause1,Clause2,Result):-
    extract_name_and_tptp_literals(Clause1,Name1,Literals1),
    extract_name_and_tptp_literals(Clause2,Name2,Literals2),
    !,
    do_comparison(Name1,Literals1,Name2,Literals2,Result).

extract_and_do_comparison(_,_,failed).
%------------------------------------------------------------------------------
compare_clauses:-
    set_prolog_flag(char_conversion,on),
    char_conversion('|','+'),
    char_conversion('!','~'),
    char_conversion('$','z'),
    read(Clause1),
    read(Clause2),
    extract_and_do_comparison(Clause1,Clause2,Result),
    write(Result),
    nl,
    halt.
%------------------------------------------------------------------------------
:-initialization(compare_clauses).
%------------------------------------------------------------------------------

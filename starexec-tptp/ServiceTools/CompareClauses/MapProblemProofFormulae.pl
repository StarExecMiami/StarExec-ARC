%==============================================================================
:-consult('TPTP2X/tptp2X.main').
:-op(700,xfx,'=~').
:-op(700,xfx,'~=').
%==============================================================================
%------------------------------------------------------------------------------
%DEBUG same_logic_formulae(LogicFormula1,LogicFormula2,_,_,_,_,_,_):-
%DEBUG write('--- Compare '),nl,write(LogicFormula1),nl,
%DEBUG write('... with ...'),nl,write(LogicFormula2),nl,fail.

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar):-
    (   looks_like_a_variable(LogicFormula1)
    ;   looks_like_a_variable(LogicFormula2)
    ),
    !,
    LogicFormula1 == LogicFormula2.

same_logic_formulae([],[],
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,SymbolsToMap1,
SymbolsToMap2,SymbolMappingSoFar):-
    !.

same_logic_formulae([FirstLogicFormula1|RestOfLogicFormulae1],
[FirstLogicFormula2|RestOfLogicFormulae2],
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    !,
    same_logic_formulae(FirstLogicFormula1,FirstLogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping),
    same_logic_formulae(RestOfLogicFormulae1,RestOfLogicFormulae2,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping).

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
%----All variables unified now
    tptp_quantified_formula(LogicFormula1,Connective,[],Formula1),
    tptp_quantified_formula(LogicFormula2,Connective,[],Formula2),
    !,
    same_logic_formulae(Formula1,Formula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping).

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    tptp_quantified_formula(LogicFormula1,Connective,Variables1,Formula1),
    tptp_quantified_formula(LogicFormula2,Connective,Variables2,Formula2),
%----Unify the variables, allowing reordering
    select(Variable,Variables1,OtherVariables1),
    !,
    select(Variable,Variables2,OtherVariables2),
    tptp_quantified_formula(NewLogicFormula1,Connective,OtherVariables1,
Formula1),
    tptp_quantified_formula(NewLogicFormula2,Connective,OtherVariables2,
Formula2),
    same_logic_formulae(NewLogicFormula1,NewLogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping).

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    tptp_binary_formula(LogicFormula1,Connective,LHS1,RHS1),
    tptp_binary_formula(LogicFormula2,Connective,LHS2,RHS2),
    same_logic_formulae(LHS1,LHS2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping),
    same_logic_formulae(RHS1,RHS2,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping),
    !.

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    tptp_binary_formula(LogicFormula1,'=>',LHS1,RHS1),
    tptp_binary_formula(LogicFormula2,'<=',LHS2,RHS2),
    same_logic_formulae(LHS1,RHS2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping),
    same_logic_formulae(LHS2,RHS1,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping),
    !.

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    tptp_binary_formula(LogicFormula1,'<=',LHS1,RHS1),
    tptp_binary_formula(LogicFormula2,'=>',LHS2,RHS2),
    same_logic_formulae(LHS1,RHS2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping),
    same_logic_formulae(LHS2,RHS1,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping),
    !.

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    tptp_binary_formula(LogicFormula1,Connective,LHS1,RHS1),
    tptp_binary_formula(LogicFormula2,Connective,LHS2,RHS2),
    !,
    tptp_associative_binary_connective(Connective),
    same_logic_formulae(LHS1,RHS2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping),
    same_logic_formulae(LHS2,RHS1,
MoreSymbolsToMap1,MoreSymbolsToMap2,MoreSymbolMapping,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping).

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    tptp_unary_formula(LogicFormula1,Connective,Formula1),
    tptp_unary_formula(LogicFormula2,Connective,Formula2),
    !,
    same_logic_formulae(Formula1,Formula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping).

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar):-
    atomic(LogicFormula1),
    atomic(LogicFormula2),
    LogicFormula1 == LogicFormula2,
    !.

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar):-
    atomic(LogicFormula1),
    atomic(LogicFormula2),
    member(LogicFormula1 == LogicFormula2,SymbolMappingSoFar),
    !.

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar):-
    atomic(LogicFormula1),
    atomic(LogicFormula2),
    member(LogicFormula2 == LogicFormula1,SymbolMappingSoFar),
    !.

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,
[LogicFormula1 == LogicFormula2|SymbolMappingSoFar]):-
    atomic(LogicFormula1),
    atomic(LogicFormula2),
    !,
    select(LogicFormula1,SymbolsToMap1,RemainingSymbolsToMap1),
    select(LogicFormula2,SymbolsToMap2,RemainingSymbolsToMap2).
%DEBUG write('Add symbol mapping '),write(LogicFormula1 == LogicFormula2),nl.

same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    tptp_atomic_formula(LogicFormula1),
    tptp_atomic_formula(LogicFormula2),
    LogicFormula1 =.. LogicFormulaList1,
    LogicFormula2 =.. LogicFormulaList2,
    length(LogicFormulaList1,ArityPlusOne),
    length(LogicFormulaList2,ArityPlusOne),
    same_logic_formulae(LogicFormulaList1,LogicFormulaList2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping),
    !.

same_logic_formulae('$tptp_equal'(LHS1,RHS1),'$tptp_equal'(LHS2,RHS2),
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    % tptp_atomic_formula(LogicFormula1),
    % tptp_atomic_formula(LogicFormula2),
    !,
    same_logic_formulae([LHS1,RHS1],[RHS2,LHS2],
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping).

%------------------------------------------------------------------------------
%DEBUG same_annotated_formulae(AnnotatedFormula1,AnnotatedFormula2,_,_,_,_,_,_,_):-
%DEBUG write('--- Compare '),nl,write(AnnotatedFormula1),nl,
%DEBUG write('... with ...'),nl,write(AnnotatedFormula2),nl,fail.

%----Simplest test case
same_annotated_formulae(AnnotatedFormula1,AnnotatedFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
'==',SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar):-
    AnnotatedFormula1 =.. [_,_,_,LogicFormula1|_],
    AnnotatedFormula2 =.. [_,_,_,LogicFormula2|_],
    \+ \+ (
        numbervars(LogicFormula1,0,N),
        numbervars(LogicFormula2,0,N),
        LogicFormula1 = LogicFormula2
    ),
    !.

same_annotated_formulae(AnnotatedFormula1,AnnotatedFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
'==',RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    AnnotatedFormula1 =.. [_,_,_,LogicFormula1|_],
    AnnotatedFormula2 =.. [_,_,_,LogicFormula2|_],
    same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping),
    !.

same_annotated_formulae(AnnotatedFormula1,AnnotatedFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
'~=',RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    AnnotatedFormula1 =.. [_,_,negated_conjecture,~ LogicFormula1|_],
    AnnotatedFormula2 =.. [_,_,conjecture,LogicFormula2|_],
    same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping),
    !.

same_annotated_formulae(AnnotatedFormula1,AnnotatedFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
'=~',RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping):-
    AnnotatedFormula1 =.. [_,_,conjecture,LogicFormula1|_],
    AnnotatedFormula2 =.. [_,_,negated_conjecture,~ LogicFormula2|_],
    same_logic_formulae(LogicFormula1,LogicFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,ExtendedSymbolMapping),
    !.

%------------------------------------------------------------------------------
do_parent_child(ParentAnnotatedFormula,ChildAnnotatedFormula):-
    ParentAnnotatedFormula =.. [_,ParentNames|_],
    ChildAnnotatedFormula =.. [_,_,_,_,inference(_,_,Parents)|_],
    member(Name,ParentNames),
    member(Name,Parents),
    !.
do_parent_child(ParentAnnotatedFormula,ChildAnnotatedFormula):-
    ParentAnnotatedFormula =.. [_,ParentNames|_],
    ChildAnnotatedFormula =.. [_,_,_,_,Parent|_],
    member(Parent,ParentNames),
    !.
do_parent_child(ParentAnnotatedFormula,ChildAnnotatedFormula):-
    ParentAnnotatedFormula =.. [_,ParentNames|_],
    ChildAnnotatedFormula =.. [_,_,_,_,inference(_,_,Parents)|_],
    member(Name,ParentNames),
    member(Name,Parents),
    !.
%------------------------------------------------------------------------------
parent_child(ParentAnnotatedFormula,ChildAnnotatedFormula,
ParentAnnotatedFormula,ChildAnnotatedFormula):-
    do_parent_child(ParentAnnotatedFormula,ChildAnnotatedFormula),
    !.

parent_child(ParentAnnotatedFormula,ChildAnnotatedFormula,
ChildAnnotatedFormula,ParentAnnotatedFormula):-
    do_parent_child(ChildAnnotatedFormula,ParentAnnotatedFormula),
    !.
%------------------------------------------------------------------------------
nest_parent_source(NameList,inference(Rule,Info,Parents),Source,
NestedInference):-
    member(Name,NameList),
    append(FirstParents,[Name|OtherParents],Parents),
    !,
    append(FirstParents,[Source|OtherParents],NestedParents),
    nest_parent_source(NameList,inference(Rule,Info,NestedParents),Source,
NestedInference).

nest_parent_source(NameList,inference(Rule,Info,Parents),Source,
inference(Rule,Info,NestedParentsWithInference)):-
    append(FirstParents,[inference(NestedRule,NestedInfo,NestedParents)|
OtherParents],Parents),
    !,
    nest_parent_source(NameList,inference(NestedRule,NestedInfo,NestedParents),
Source,NestedInference),
    append(FirstParents,[NestedInference|OtherParents],
NestedParentsWithInference).

nest_parent_source(_,Inference,_,Inference).
%------------------------------------------------------------------------------
do_merge_same_annotated_formulae([],[]).

do_merge_same_annotated_formulae([FirstAnnotatedFormula|
RestOfAnnotatedFormulae],MergedAnnotatedFormulae):-
    select(SelectedAnnotatedFormula,RestOfAnnotatedFormulae,
OtherAnnotatedFormulae),
%DEBUG write('Compare '),write(FirstAnnotatedFormula),nl,
%DEBUG write('...with '),write(SelectedAnnotatedFormula),nl,
    same_annotated_formulae(FirstAnnotatedFormula,SelectedAnnotatedFormula,
[],[],[],'==',[],[],[]),
    parent_child(FirstAnnotatedFormula,SelectedAnnotatedFormula,
ParentAnnotatedFormula,ChildAnnotatedFormula),
    !,
    ParentAnnotatedFormula =.. [_Type1,Name1,_Role1,_Logic1,Source1,
UsefulInfo1],
    ChildAnnotatedFormula =.. [Type2,Name2,Role2,Logic2,Source2,UsefulInfo2],
    append(Name1,Name2,Name),
    nest_parent_source(Name1,Source2,Source1,Source),
    append(UsefulInfo1,UsefulInfo2,UsefulInfo),
    MergedAnnotatedFormula =.. [Type2,Name,Role2,Logic2,Source,UsefulInfo],
%DEBUG write('MERGED '),write(MergedAnnotatedFormula),nl,
    do_merge_same_annotated_formulae([MergedAnnotatedFormula|
OtherAnnotatedFormulae],MergedAnnotatedFormulae).

do_merge_same_annotated_formulae([FirstAnnotatedFormula|
RestOfAnnotatedFormulae],[FirstAnnotatedFormula|
RestOfMergedAnnotatedFormulae]):-
    do_merge_same_annotated_formulae(RestOfAnnotatedFormulae,
RestOfMergedAnnotatedFormulae).
%------------------------------------------------------------------------------
listify_names([],[]).

listify_names([FirstAnnotatedFormula|RestOfAnnotatedFormulae],
[FirstRenamedAnnotatedFormula|RestOfRenamedAnnotatedFormulae]):-
    FirstAnnotatedFormula =.. [Type,Name|Rest],
    FirstRenamedAnnotatedFormula =.. [Type,[Name]|Rest],
    listify_names(RestOfAnnotatedFormulae,RestOfRenamedAnnotatedFormulae).
%------------------------------------------------------------------------------
merge_same_annotated_formulae(AnnotatedFormulae,MergedAnnotatedFormulae):-
    listify_names(AnnotatedFormulae,RenamedAnnotatedFormulae),
    do_merge_same_annotated_formulae(RenamedAnnotatedFormulae,
MergedAnnotatedFormulae).
%------------------------------------------------------------------------------
map_annotated_formulae([],[],_,_,SymbolMapping,SymbolMapping,[]):-
    !.

map_annotated_formulae([FirstAnnotatedFormula1|RestOfAnnotatedFormulae1],
[],SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,SymbolMapping,
[Name1==[]|RestOfAnnotatedFormulaNameMapping]):-
    !,
    FirstAnnotatedFormula1 =.. [_,Name1|_],
    map_annotated_formulae(RestOfAnnotatedFormulae1,[],
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,SymbolMapping,
RestOfAnnotatedFormulaNameMapping).

map_annotated_formulae([],[FirstAnnotatedFormula2|RestOfAnnotatedFormulae2],
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,SymbolMapping,
[[]==Name2|RestOfAnnotatedFormulaNameMapping]):-
    !,
    FirstAnnotatedFormula2 =.. [_,Name2|_],
    map_annotated_formulae([],RestOfAnnotatedFormulae2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,SymbolMapping,
RestOfAnnotatedFormulaNameMapping).

map_annotated_formulae([FirstAnnotatedFormula1|RestOfAnnotatedFormulae1],
AnnotatedFormulae2,SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
SymbolMapping,[Mapping|RestOfAnnotatedFormulaNameMapping]):-
    select(SelectedAnnotatedFormula2,AnnotatedFormulae2,
RestOfAnnotatedFormulae2),
    same_annotated_formulae(FirstAnnotatedFormula1,SelectedAnnotatedFormula2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
MappingType,RemainingSymbolsToMap1,RemainingSymbolsToMap2,UpdatedSymbolMapping),
%----Could allow other mappings by not cutting here
    !,
    FirstAnnotatedFormula1 =.. [_,Name1|_],
    SelectedAnnotatedFormula2 =.. [_,Name2|_],
    Mapping =.. [MappingType,Name1,Name2],
    map_annotated_formulae(RestOfAnnotatedFormulae1,RestOfAnnotatedFormulae2,
RemainingSymbolsToMap1,RemainingSymbolsToMap2,UpdatedSymbolMapping,
SymbolMapping,RestOfAnnotatedFormulaNameMapping).

map_annotated_formulae([FirstAnnotatedFormula1|RestOfAnnotatedFormulae1],
AnnotatedFormulae2,SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,
SymbolMapping,[Name1==[]|RestOfAnnotatedFormulaNameMapping]):-
    !,
    FirstAnnotatedFormula1 =.. [_,Name1|_],
    map_annotated_formulae(RestOfAnnotatedFormulae1,AnnotatedFormulae2,
SymbolsToMap1,SymbolsToMap2,SymbolMappingSoFar,SymbolMapping,
RestOfAnnotatedFormulaNameMapping).
%------------------------------------------------------------------------------
%----If no source, assume leaf
leaf_formula(AnnotatedFormula):-
    AnnotatedFormula =.. [_,_,_,_],
    !.

%----If not inferred source, assume leaf
leaf_formula(AnnotatedFormula):-
    AnnotatedFormula =.. [_,_,_,_,Source|_],
    atomic(Source),
    !,
    fail.

leaf_formula(AnnotatedFormula):-
    AnnotatedFormula =.. [_,_,_,_,Source|_],
    Source =.. [Type|_],
    Type \== inference.
%------------------------------------------------------------------------------
extract_proof_leaves([],[]).

extract_proof_leaves([FirstAnnotatedFormula|RestOfAnnotatedFormulae],
[FirstAnnotatedFormula|RestOfLeaves]):-
    leaf_formula(FirstAnnotatedFormula),
    !,
    extract_proof_leaves(RestOfAnnotatedFormulae,RestOfLeaves).

extract_proof_leaves([_|RestOfAnnotatedFormulae],Leaves):-
    extract_proof_leaves(RestOfAnnotatedFormulae,Leaves).
%------------------------------------------------------------------------------
print_mapping_elements([]).

print_mapping_elements([FirstMappingElement|RestOfMappingElements]):-
    write(FirstMappingElement),nl,
    print_mapping_elements(RestOfMappingElements).
%------------------------------------------------------------------------------
print_mapping(_Heading,MappingElements):-
%%    write(Heading),nl,
    print_mapping_elements(MappingElements).
%------------------------------------------------------------------------------
map_formula_files(ProblemFile,ProofFile):-
    read_formulae_from_file(ProblemFile,ProblemAnnotatedFormulae,_),
    merge_same_annotated_formulae(ProblemAnnotatedFormulae,
MergedProblemAnnotatedFormulae),
    read_formulae_from_file(ProofFile,ProofAnnotatedFormulae,_),
    direct_translate_to_fof(ProofAnnotatedFormulae,ProofAnnotatedFOF),
    merge_same_annotated_formulae(ProofAnnotatedFOF,
MergedProofAnnotatedFormulae),
%    extract_proof_leaves(MergedProofAnnotatedFormulae,
%MergedProofLeafAnnotatedFormulae),
    map_annotated_formulae(MergedProblemAnnotatedFormulae,
MergedProofAnnotatedFormulae,
[],[],[],_SymbolMapping,AnnotatedFormulaNameMapping),
    print_mapping('#FOFLeaves',AnnotatedFormulaNameMapping).

map_formula_files(ProblemFile,ProofFile1,ProofFile2):-
    read_formulae_from_file(ProblemFile,ProblemAnnotatedFormulae,_),
    merge_same_annotated_formulae(ProblemAnnotatedFormulae,
MergedProblemAnnotatedFormulae),
    examine_formulae_for_functors(MergedProblemAnnotatedFormulae,_,
ProblemFunctors),
    read_formulae_from_file(ProofFile1,ProofAnnotatedFormulae1,_),
    direct_translate_to_fof(ProofAnnotatedFormulae1,ProofAnnotatedFOF1),
    merge_same_annotated_formulae(ProofAnnotatedFOF1,
MergedProofAnnotatedFormulae1),
    read_formulae_from_file(ProofFile2,ProofAnnotatedFormulae2,_),
    direct_translate_to_fof(ProofAnnotatedFormulae2,ProofAnnotatedFOF2),
    merge_same_annotated_formulae(ProofAnnotatedFOF2,
MergedProofAnnotatedFormulae2),
    examine_formulae_for_functors(MergedProofAnnotatedFormulae1,_,
ProofFunctors1),
    tptp2X_list_difference(ProofFunctors1,ProblemFunctors,NewFunctors1),
    examine_formulae_for_functors(MergedProofAnnotatedFormulae2,_,
ProofFunctors2),
    tptp2X_list_difference(ProofFunctors2,ProblemFunctors,NewFunctors2),
    map_annotated_formulae(MergedProofAnnotatedFormulae1,
MergedProofAnnotatedFormulae2,NewFunctors1,NewFunctors2,[],_SymbolMapping,
AnnotatedFormulaNameMapping),
%DEBUG print_mapping('#Symbols',SymbolMapping),
    print_mapping('#Formulae',AnnotatedFormulaNameMapping).
%------------------------------------------------------------------------------
run:-
    current_prolog_flag(argv,[_|Arguments]),
%DEBUG write(Arguments),nl,
    length(Arguments,NumberOfArguments),
    member(NumberOfArguments,[2,3]),
    Query =.. [map_formula_files|Arguments],
    Query.

run:-
    write('Usage:'),nl.
%------------------------------------------------------------------------------
save:-
    set_prolog_flag(verbose,silent),
    qsave_program('MapProblemProofFormulae',
[stand_alone(true),op(save),toplevel(run)]).
%------------------------------------------------------------------------------
go1:-
    map_formula_files(
'/home/tptp/ServiceTools/CompareClauses/TestFiles/Problem.p',
% '/home/tptp/ServiceTools/CompareClauses/TestFiles/Proof1.s',
'/home/tptp/ServiceTools/CompareClauses/TestFiles/Proof2.s').

go2:-
    map_formula_files(
'/home/tptp/TPTP/Problems/SEU/SEU140+1.p',
'/home/tptp/ServiceTools/CompareClauses/TestFiles/Vampire.s').

go3:-
    map_formula_files(
'/home/tptp/TPTP/Problems/SEU/SEU140+1.p',
'/home/tptp/ServiceTools/CompareClauses/TestFiles/EP.s').

go4:-
    map_formula_files(
'/home/tptp/TPTP/Problems/SEU/SEU140+1.p',
'/home/tptp/ServiceTools/CompareClauses/TestFiles/EP.s',
'/home/tptp/ServiceTools/CompareClauses/TestFiles/Vampire.s').

%==============================================================================

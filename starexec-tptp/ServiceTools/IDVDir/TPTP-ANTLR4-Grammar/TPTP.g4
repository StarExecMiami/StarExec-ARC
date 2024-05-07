// created by Alexander Steen (a.steen@fu-berlin.de)
// and Tobias Gleißner (tobias.gleissner@fu-berlin.de)
// Revised by Geoff Sutcliffe for v8.1.0

// #INFO is about sections or where the parse tree has been flattened according to ANTLR idiomatics
// #ALT alternative grammar formulation for some parts
// #RES where no further restrictions are applied e.g. in the case of defined_functor any dollar 
// word is allowed instead of only the predefined functors

grammar TPTP;

// #INFO HERE COME THE LEXER RULES

fragment Do_char : [\u0020-\u0021\u0023-\u005B\u005D-\u007E] | '\\'["\\];
fragment Sq_char : [\u0020-\u0026\u0028-\u005B\u005D-\u007E] | '\\'['\\];
fragment Sign : [+-];
fragment Exponent : [Ee];
fragment Non_zero_numeric : [1-9];
fragment Numeric : [0-9];
fragment Lower_alpha : [a-z];
fragment Upper_alpha : [A-Z];
fragment Alpha_numeric : Lower_alpha | Upper_alpha | Numeric | '_';

Or: '|';
And: '&';
Iff : '<=>';
Impl : '=>';
If: '<=';
Niff: '<~>';
Nor: '~|';
Nand: '~&';
Not: '~';
ForallComb: '!!';
TyForall: '!>';
Infix_inequality : '!=';
Infix_equality : '=';
Forall: '!';
ExistsComb: '??';
TyExists: '?*';
Exists: '?';
Lambda: '^';
ChoiceComb: '@@+';
Choice: '@+';
DescriptionComb: '@@-';
Description: '@-';
EqComb: '@=';
App: '@';
Assignment: ':=';
Identical: '==';
Arrow: '>';
Star: '*';
Plus: '+';
Hash: '#';
Subtype_sign: '<<';
Gentzen_arrow: '-->';

Real : Signed_real | Unsigned_real;
Signed_real : Sign Unsigned_real;
Unsigned_real : Decimal_fraction|Decimal_exponent;
Rational: Signed_rational | Unsigned_rational;
Signed_rational: Sign Unsigned_rational;
Unsigned_rational: Decimal '/' Positive_decimal;
Integer : Signed_integer | Unsigned_integer;
Signed_integer: Sign Unsigned_integer;
Unsigned_integer: Decimal;
Decimal : '0' | Positive_decimal;
Positive_decimal : Non_zero_numeric Numeric*;
Decimal_exponent : (Decimal|Decimal_fraction) Exponent Exp_integer;
Decimal_fraction : Decimal Dot_decimal;
Dot_decimal : '.' Numeric Numeric*;
Exp_integer : Signed_exp_integer|Unsigned_exp_integer;
Signed_exp_integer : Sign Unsigned_exp_integer;
Unsigned_exp_integer : Numeric Numeric*;

Dollar_word : '$' Lower_word;
Dollar_dollar_word : '$$' Lower_word;
Upper_word : Upper_alpha Alpha_numeric*;
Lower_word : Lower_alpha Alpha_numeric*;

Single_quoted : '\'' Sq_char+ '\'';
Distinct_object : '"' Do_char+ '"';

WS : [ \r\t\n]+ -> skip ;
Line_comment : '%' ~[\r\n]* -> skip;
Block_comment : '/*' .*? '*/' -> skip;

tptp_file               : tptp_input* EOF;
tptp_input              : annotated_formula | include;

annotated_formula       : thf_annotated | tff_annotated | tcf_annotated | fof_annotated | 
                          cnf_annotated | tpi_annotated;
tpi_annotated           : 'tpi('name ',' formula_role ',' tpi_formula annotations?').';
tpi_formula             : fof_formula;
thf_annotated           : 'thf('name ',' formula_role ',' thf_formula annotations?').';
tff_annotated           : 'tff('name ',' formula_role ',' tff_formula annotations?').';
tcf_annotated           : 'tcf('name ',' formula_role ',' tcf_formula annotations?').';
fof_annotated           : 'fof('name ',' formula_role ',' fof_formula annotations?').';
cnf_annotated           : 'cnf('name ',' formula_role ',' cnf_formula annotations?').';
annotations             : ',' source optional_info?;

formula_role            : Lower_word;

thf_formula             : thf_logic_formula | thf_atom_typing | thf_subtype;
thf_logic_formula       : thf_unitary_formula | thf_unary_formula | thf_binary_formula |
                          thf_defined_infix | thf_definition | thf_sequent;
thf_binary_formula      : thf_binary_nonassoc | thf_binary_assoc | thf_binary_type;
thf_binary_nonassoc     : thf_unit_formula nonassoc_connective thf_unit_formula;
thf_binary_assoc        : thf_or_formula | thf_and_formula | thf_apply_formula;
thf_or_formula          : thf_unit_formula Or thf_unit_formula | thf_or_formula Or thf_unit_formula;
thf_and_formula         : thf_unit_formula And thf_unit_formula | 
                          thf_and_formula And thf_unit_formula;
thf_apply_formula       : thf_unit_formula App thf_unit_formula | 
                          thf_apply_formula App thf_unit_formula;
thf_unit_formula        : thf_unitary_formula | thf_unary_formula | thf_defined_infix;
thf_preunit_formula     : thf_unitary_formula | thf_prefix_unary;
thf_unitary_formula     : thf_quantified_formula | thf_atomic_formula | variable | 
                          '('thf_logic_formula')';

thf_quantified_formula  : thf_quantification thf_unit_formula;
thf_quantification      : thf_quantifier '[' thf_variable_list ']' ':';
thf_variable_list       : thf_variable (',' thf_variable)*; // #INFO thf_variable_list flattened
thf_variable            : thf_typed_variable | variable;
thf_typed_variable      : variable ':' thf_top_level_type;
thf_unary_formula       : thf_prefix_unary | thf_infix_unary;
thf_prefix_unary        : unary_connective thf_preunit_formula;
thf_infix_unary         : thf_unitary_term Infix_inequality thf_unitary_term;
thf_atomic_formula      : thf_plain_atomic | thf_defined_atomic | thf_system_atomic | 
                          thf_fof_function;
thf_plain_atomic        : constant | thf_tuple;
thf_defined_atomic      : defined_constant | thf_defined_term | '('thf_conn_term')' | 
                          ntf_connective | thf_let;
thf_defined_term        : defined_term | th1_defined_term;
thf_defined_infix       : thf_unitary_term defined_infix_pred thf_unitary_term;
thf_system_atomic       : system_constant;

thf_let                 : '$let('thf_let_types ',' thf_let_defns ',' thf_logic_formula')';
thf_let_types           : thf_atom_typing | '[' thf_atom_typing_list ']';
thf_atom_typing_list    : thf_atom_typing | thf_atom_typing ',' thf_atom_typing_list;
thf_let_defns           : thf_let_defn | '[' thf_let_defn_list ']';
thf_let_defn            : thf_logic_formula Assignment thf_logic_formula;
thf_let_defn_list       : thf_let_defn | thf_let_defn ',' thf_let_defn_list;
thf_unitary_term        : thf_atomic_formula | variable | '('thf_logic_formula')';
thf_conn_term           : nonassoc_connective | assoc_connective | 
                          Infix_equality | Infix_inequality | unary_connective;

thf_tuple               : '[]' | '[' thf_formula_list ']';
thf_fof_function        : functor '('thf_arguments')' | defined_functor '('thf_arguments')' |
                          system_functor '('thf_arguments')';
thf_arguments           : thf_formula_list;
thf_formula_list        : thf_logic_formula | thf_logic_formula ',' thf_formula_list;

thf_atom_typing         : untyped_atom ':' thf_top_level_type | '('thf_atom_typing')';
thf_top_level_type      : thf_unitary_type | thf_mapping_type | thf_apply_type;
thf_unitary_type        : thf_unitary_formula;
thf_apply_type          : thf_apply_formula;
thf_binary_type         : thf_mapping_type | thf_xprod_type | thf_union_type;
thf_mapping_type        : thf_unitary_type Arrow thf_unitary_type |
                          thf_unitary_type Arrow thf_mapping_type;
thf_xprod_type          : thf_unitary_type Star thf_unitary_type |
                          thf_xprod_type Star thf_unitary_type;
thf_union_type          : thf_unitary_type Plus thf_unitary_type |
                          thf_union_type Plus thf_unitary_type;
thf_subtype             : untyped_atom Subtype_sign atom;

thf_definition          : thf_atomic_formula Identical thf_logic_formula;
thf_sequent             : thf_tuple Gentzen_arrow thf_tuple;
//-------------------------------------------------------------------------------------------------
tff_formula             : tff_logic_formula | tff_atom_typing | tff_subtype;
tff_logic_formula       : tff_unitary_formula | tff_unary_formula | tff_binary_formula | 
                          tff_defined_infix | txf_definition | txf_sequent;

tff_binary_formula      : tff_binary_nonassoc | tff_binary_assoc;
tff_binary_nonassoc     : tff_unit_formula nonassoc_connective tff_unit_formula;
tff_binary_assoc        : tff_or_formula | tff_and_formula;
tff_or_formula          : tff_unit_formula Or tff_unit_formula | 
                          tff_or_formula Or tff_unit_formula;
tff_and_formula         : tff_unit_formula And tff_unit_formula | 
                          tff_and_formula And tff_unit_formula;
tff_unit_formula        : tff_unitary_formula | tff_unary_formula | tff_defined_infix;
tff_preunit_formula     : tff_unitary_formula | tff_prefix_unary;
tff_unitary_formula     : tff_quantified_formula | tff_atomic_formula | 
                          txf_unitary_formula | '('tff_logic_formula')';
txf_unitary_formula     : variable;
tff_quantified_formula  : fof_quantifier '['tff_variable_list']' ':' tff_unit_formula;

tff_variable_list       : tff_variable | tff_variable ',' tff_variable_list;
tff_variable            : tff_typed_variable | variable;
tff_typed_variable      : variable ':' tff_atomic_type;
tff_unary_formula       : tff_prefix_unary | tff_infix_unary;
tff_prefix_unary        : unary_connective tff_preunit_formula;
tff_infix_unary         : tff_unitary_term Infix_inequality tff_unitary_term;

tff_atomic_formula      : tff_plain_atomic | tff_defined_atomic | tff_system_atomic;
tff_plain_atomic        : constant | functor'('tff_arguments')';
tff_defined_atomic      : tff_defined_plain | ntf_connective;
tff_defined_plain       : defined_constant | defined_functor'('tff_arguments')' | txf_ntf_atom | 
                          txf_let;
tff_defined_infix       : tff_unitary_term defined_infix_pred tff_unitary_term;
tff_system_atomic       : system_constant | system_functor'('tff_arguments')';
txf_let                 : '$let('txf_let_types ',' txf_let_defns ',' tff_term')';
txf_let_types           : tff_atom_typing | '['tff_atom_typing_list']';
tff_atom_typing_list    : tff_atom_typing | tff_atom_typing ',' tff_atom_typing_list;
txf_let_defns           : txf_let_defn | '['txf_let_defn_list']';
txf_let_defn            : txf_let_LHS Assignment tff_term;
txf_let_LHS             : tff_plain_atomic | txf_tuple;
txf_let_defn_list       : txf_let_defn | txf_let_defn ',' txf_let_defn_list;
txf_ntf_atom            : ntf_connective App '('tff_arguments')';

tff_term                : tff_logic_formula | defined_term | txf_tuple | ntf_key_pair;
tff_unitary_term        : tff_atomic_formula | defined_term | txf_tuple | variable | 
                          '('tff_logic_formula')';
txf_tuple               : '[]' | '['tff_arguments']';

tff_arguments           : tff_term | tff_term ',' tff_arguments;

tff_atom_typing         : untyped_atom ':' tff_top_level_type | '('tff_atom_typing')';
tff_top_level_type      : tff_atomic_type | tff_non_atomic_type;
tff_non_atomic_type     : tff_mapping_type | <tf1_quantified_type> | '('tff_non_atomic_type')';
tf1_quantified_type     : TyForall '['tff_variable_list']' ':' tff_monotype;
tff_monotype            : tff_atomic_type | '('tff_mapping_type')' | tf1_quantified_type;
tff_unitary_type        : tff_atomic_type | '('tff_xprod_type')';
tff_atomic_type         : type_constant | defined_type | variable | 
                          type_functor'('tff_type_arguments')' | '('tff_atomic_type')' | 
                          txf_tuple_type;
tff_type_arguments      : tff_atomic_type | tff_atomic_type ',' tff_type_arguments;
tff_mapping_type        : tff_unitary_type Arrow tff_atomic_type;
tff_xprod_type          : tff_unitary_type Star tff_atomic_type | 
                          tff_xprod_type Star tff_atomic_type;
txf_tuple_type          : '['tff_type_list']';
tff_type_list           : tff_top_level_type | tff_top_level_type ',' tff_type_list;

tff_subtype             : untyped_atom Subtype_sign atom;

txf_definition          : tff_atomic_formula Identical tff_term;
txf_sequent             : txf_tuple Gentzen_arrow txf_tuple;
//-------------------------------------------------------------------------------------------------
ntf_connective          : ntf_short_connective | ntf_long_connective;
ntf_short_connective    : '[.]' | '<.>' | '{.}' | '[' ntf_index ']' | '<' ntf_index '>' | 
                          '{' ntf_index '}';
ntf_long_connective     : '{' ntf_connective_name '}' | 
                          '{' ntf_connective_name '('ntf_parameter_list')}';
ntf_connective_name     : def_or_sys_constant;
ntf_parameter_list      : ntf_parameter | ntf_parameter ',' ntf_parameter_list;
ntf_parameter           : ntf_index | ntf_key_pair;
ntf_index               : Hash tff_unitary_term;
ntf_key_pair            : def_or_sys_constant Assignment tff_unitary_term;

logic_defn_rule         : logic_defn_LHS Identical logic_defn_RHS;
logic_defn_LHS          : defined_constant;
logic_defn_RHS          : defined_constant | txf_tuple;
//-------------------------------------------------------------------------------------------------
tcf_formula             : tcf_logic_formula | tff_atom_typing;
tcf_logic_formula       : tcf_quantified_formula | cnf_formula;
tcf_quantified_formula  : Forall '['tff_variable_list']' ':' tcf_logic_formula;
//-------------------------------------------------------------------------------------------------
fof_formula             : fof_logic_formula | fof_sequent;
fof_logic_formula       : fof_binary_formula | fof_unary_formula | fof_unitary_formula;
fof_binary_formula      : fof_binary_nonassoc | fof_binary_assoc;
fof_binary_nonassoc     : fof_unit_formula nonassoc_connective fof_unit_formula;
fof_binary_assoc        : fof_or_formula | fof_and_formula;
fof_or_formula          : fof_unit_formula Or fof_unit_formula | fof_or_formula Or fof_unit_formula;
fof_and_formula         : fof_unit_formula And fof_unit_formula | 
                          fof_and_formula And fof_unit_formula;
fof_unary_formula       : unary_connective fof_unit_formula | fof_infix_unary;
fof_infix_unary         : fof_term Infix_inequality fof_term;
fof_unit_formula        : fof_unitary_formula | fof_unary_formula;
fof_unitary_formula     : fof_quantified_formula | fof_atomic_formula | '('fof_logic_formula')';
fof_quantified_formula  : fof_quantifier '['fof_variable_list']' ':' fof_unit_formula;
fof_variable_list       : variable | variable ',' fof_variable_list;
fof_atomic_formula      : fof_plain_atomic_formula | fof_defined_atomic_formula | 
                          fof_system_atomic_formula;
fof_plain_atomic_formula   : fof_plain_term;
fof_defined_atomic_formula : fof_defined_plain_formula | fof_defined_infix_formula;
fof_defined_plain_formula  : fof_defined_plain_term;
fof_defined_infix_formula  : fof_term defined_infix_pred fof_term;
fof_system_atomic_formula  : fof_system_term;

fof_plain_term          : constant | functor'('fof_arguments')';
fof_defined_term        : defined_term | fof_defined_atomic_term;
fof_defined_atomic_term : fof_defined_plain_term;
fof_defined_plain_term  : defined_constant | defined_functor'('fof_arguments')';
fof_system_term         : system_constant | system_functor'('fof_arguments')';
fof_arguments           : fof_term | fof_term ',' fof_arguments;
fof_term                : fof_function_term | variable;
fof_function_term       : fof_plain_term | fof_defined_term | fof_system_term;
//-------------------------------------------------------------------------------------------------
fof_sequent             : fof_formula_tuple Gentzen_arrow fof_formula_tuple | '('fof_sequent')';
fof_formula_tuple       : '{}' | '{'fof_formula_tuple_list'}';
fof_formula_tuple_list  : fof_logic_formula | fof_logic_formula ',' fof_formula_tuple_list;
//-------------------------------------------------------------------------------------------------
cnf_formula             : cnf_disjunction | '('cnf_disjunction')';
cnf_disjunction         : cnf_literal | cnf_disjunction Or cnf_literal;
cnf_literal             : fof_atomic_formula | Not fof_atomic_formula | 
                          Not '('fof_atomic_formula')' | fof_infix_unary;
//-------------------------------------------------------------------------------------------------
thf_quantifier          : fof_quantifier | th0_quantifier | th1_quantifier;
th1_quantifier          : TyForall | TyExists;
th0_quantifier          : Lambda | Choice | Description;
fof_quantifier          : Forall | Exists;
nonassoc_connective     : Iff | Impl | If | Niff | Nor | Nand;
assoc_connective        : Or | And;
unary_connective        : Not;

type_constant           : type_functor;
type_functor            : atomic_word;
defined_type            : Dollar_word;
system_type             : atomic_system_word;

atom                    : untyped_atom | defined_constant;
untyped_atom            : constant | system_constant;

defined_proposition     : Dollar_word; 
defined_predicate       : Dollar_word;
defined_infix_pred      : Infix_equality | Assignment;

constant                : functor;
functor                 : atomic_word;
defined_constant        : defined_functor;
defined_functor         : atomic_defined_word;
system_constant         : system_functor;
system_functor          : atomic_system_word;
def_or_sys_constant   : defined_constant | system_constant;
th1_defined_term      : ForallComb | ExistsComb | ChoiceComb | DescriptionComb |
                        EqComb;
defined_term            : number | Distinct_object;
variable                : Upper_word;

source                  : dag_source | internal_source
                        | external_source
                        | Lower_word // #RES | 'unknown'
                        | '[' sources ']';
sources                 : source ( ',' source )*; // #INFO flattened
dag_source              : name | inference_record;

inference_record        : 'inference('inference_rule ',' useful_info ',' inference_parents')';
inference_rule          : atomic_word;

inference_parents       : '[]' | '[' parent_list ']';
parent_list             : parent_info ( ',' parent_info )*; // #INFO flattened
parent_info             : source parent_details?; // #INFO ? because parent_details may be empty
parent_details          : ':' general_list;
internal_source         : 'introduced('intro_type optional_info?')';
intro_type              : Lower_word; // #RES Intro_type;

external_source          : file_source | theory | creator_source;
file_source             : 'file('file_name file_info?')'; // #INFO ? because file_info may be empty
file_info               : ',' name;
theory                  : 'theory('theory_name optional_info?')'; // #INFO ? because optional_info may be empty
theory_name             : Lower_word; // #RES Theory_name;
//Theory_name             : 'equality' | 'ac';
creator_source          : 'creator('creator_name optional_info?')'; // #INFO ? because optional_info may be empty
creator_name            : atomic_word;

//%----Useful info fields
//<optional_info>        ::= ,<useful_info> | <null>
//<useful_info>          ::= <general_list>
//<useful_info>          :== [] | [<info_items>]
//<info_items>           :== <info_item> | <info_item>,<info_items>
//<info_item>            :== <formula_item> | <inference_item> |
//                           <general_function>
optional_info           : ',' useful_info;
useful_info             : '[]' | '[' info_items ']' | general_list;
info_items              : info_item ( ',' info_item )*; // #INFO flattened
info_item               : formula_item | inference_item
                        | general_function;

//%----Useful info for formula records
//<formula_item>         :== <description_item> | <iquote_item>
//<description_item>     :== description(<atomic_word>)
//<iquote_item>          :== iquote(<atomic_word>)
//%----<iquote_item>s are used for recording exactly what the system output about
//%----the inference step. In the future it is planned to encode this information
//%----in standardized forms as <parent_details> in each <inference_record>.
//%----Useful info for inference records
formula_item            : description_item | iquote_item;
description_item        : 'description('atomic_word')';
iquote_item             : 'iquote('atomic_word')';

//<inference_item>       :== <inference_status> | <assumptions_record> |
//                           <new_symbol_record> | <refutation>
//<inference_status>     :== status(<status_value>) | <inference_info>
//%----These are the success status values from the SZS ontology. The most
//%----commonly used values are:
//%----  thm - Every model of the parent formulae is a model of the inferred
//%----        formula. Regular logical consequences.
//%----  cth - Every model of the parent formulae is a model of the negation of
//%----        the inferred formula. Used for negation of conjectures in FOF to
//%----        CNF conversion.
//%----  esa - There exists a model of the parent formulae iff there exists a
//%----        model of the inferred formula. Used for Skolemization steps.
//%----For the full hierarchy see the SZSOntology file distributed with the TPTP.
//<status_value>         :== suc | unp | sap | esa | sat | fsa | thm | eqv | tac |
//                           wec | eth | tau | wtc | wth | cax | sca | tca | wca |
//                           cup | csp | ecs | csa | cth | ceq | unc | wcc | ect |
//                           fun | uns | wuc | wct | scc | uca | noc
//%----<inference_info> is used to record standard information associated with an
//%----arbitrary inference rule. The <inference_rule> is the same as the
//%----<inference_rule> of the <inference_record>. The <atomic_word> indicates
//%----the information being recorded in the <general_list>. The <atomic_word>
//%----are (loosely) set by TPTP conventions, and include esplit, sr_split, and
//%----discharge.
//<inference_info>       :== <inference_rule>(<atomic_word>,<general_list>)
inference_item          : inference_status | assumptions_record
                        | new_symbol_record | refutation;
inference_status        : 'status('status_value')' | inference_info;
status_value            : Lower_word; // #RES Status_value;
//Status_value            : 'suc' | 'unp' | 'sap' | 'esa' | 'sat' | 'fsa' | 'thm' | 'eqv' | 'tac'
//                        | 'wec' | 'eth' | 'tau' | 'wtc' | 'wth' | 'cax' | 'sca' | 'tca' | 'wca'
//                        | 'cup' | 'csp' | 'ecs' | 'csa' | 'cth' | 'ceq' | 'unc' | 'wcc' | 'ect'
//                        | 'fun' | 'uns' | 'wuc' | 'wct' | 'scc' | 'uca' | 'noc';
inference_info          : inference_rule '('atomic_word ',' general_list')';

//%----An <assumptions_record> lists the names of assumptions upon which this
//%----inferred formula depends. These must be discharged in a completed proof.
//<assumptions_record>   :== assumptions([<name_list>])
//%----A <refutation> record names a file in which the inference recorded here
//%----is recorded as a proof by refutation.
//<refutation>           :== refutation(<file_source>)
//%----A <new_symbol_record> provides information about a newly introduced symbol.
//<new_symbol_record>    :== new_symbols(<atomic_word>,[<new_symbol_list>])
//<new_symbol_list>      :== <principal_symbol> |
//                           <principal_symbol>,<new_symbol_list>
//%----Principal symbols are predicates, functions, variables
//<principal_symbol>   :== <functor> | <variable>
assumptions_record      : 'assumptions(''[' name_list ']'')';
refutation              : 'refutation('file_source')';
new_symbol_record       : 'new_symbols('atomic_word ',' '[' new_symbol_list ']'')';
new_symbol_list         : principal_symbol ( ',' principal_symbol )*; // #INFO flattened
//new_symbol_list         : principal_symbol | principal_symbol ',' new_symbol_list; //#ALT to flattened new_symbol_list
principal_symbol        : functor | variable;

include                 : 'include('file_name formula_selection?').'; 
formula_selection       : ',' '[' name_list ']';
name_list               : name (',' name)*;

general_term            : general_data | general_data ':' general_term | general_list;
general_data            : atomic_word | general_function | variable | number | Distinct_object | 
                          formula_data;
general_function        : atomic_word '('general_terms')';
formula_data            : '$thf('thf_formula')' | '$tff('tff_formula')' | 
                          '$fof('fof_formula')' | '$cnf('cnf_formula')' | '$fot('fof_term')';
general_list            : '[]' | '[' general_terms ']';
general_terms           : general_term (',' general_term)*; // #INFO flattened

name                    : atomic_word | Integer;
atomic_word             : Lower_word | Single_quoted;
atomic_defined_word     : Dollar_word;
atomic_system_word      : Dollar_dollar_word;
number                  : Integer | Rational | Real;
file_name               : Single_quoted;












































































#ifndef DATATYPES_H
#define DATATYPES_H
#include <stdio.h>
//-------------------------------------------------------------------------------------------------
//----Types for file and token handling
typedef enum {
    punctuation,
    quantifier,
    unary_connective,
    binary_connective,
    number,
    distinct_object,
    lower_word,
    upper_word,
//----Token groups
    predicate_symbol,
    functor,
    name,
//----Non-logic tokens
    comment_token,
    blank_line_token,
    error,
    endeof
} TokenType;

typedef struct {
    TokenType KindToken;
    char * NameToken;
} ReadToken;

typedef ReadToken * TOKEN;

typedef struct {
    char * FileName;
    FILE * FileHandle;
    int Line;
    int Character;
//----Content for a string file
    char * StringFileContent;
//----Overshot by one character or not
    int Overshot;
//----Index of next character to use
    int StringOffset;
//----Current character and token
    int CurrentCharacter;
    TOKEN CurrentToken;
    TOKEN Auxilliary;
//----Whether or not non-logicals are needed
    int NeedNonLogicTokens;
//----Whether or not symbols can be overloaded, etc.
    int Warnings;
} ReadFile;

typedef ReadFile * READFILE;

typedef struct {
    char * FileName; 
    FILE * FileHandle;
    char * StringFileContent;
} PrintFile;

typedef PrintFile * PRINTFILE;
//-------------------------------------------------------------------------------------------------
//----Types for the signature
typedef struct SymbolTag {
    char * NameSymbol;
    char * ShortSymbol;
    int NumberOfUses;
    int Arity;         //----The true arity, i.e., in ()s, and for {} connectives the @ ()ed length
    int AppliedArity;  //----Used for {} connectives that have their own parameters (arity)
    int InternalSymbol;  //-----Used for things not to be counted in statistics
//----These are left and right for the tree implementation (to be renamed)
    struct SymbolTag * LastSymbol;
    struct SymbolTag * NextSymbol;
} SymbolNodeType;

typedef SymbolNodeType * SYMBOLNODE;

typedef struct {
    SYMBOLNODE Variables;
    SYMBOLNODE Functions;
    SYMBOLNODE Predicates;
    SYMBOLNODE Types;
    SYMBOLNODE NonLogicals;
} SignatureType;

typedef SignatureType * SIGNATURE;
//-------------------------------------------------------------------------------------------------
typedef enum {
//----First order and upwards
    disjunction,
    conjunction,
    equivalence,
    implication,
    reverseimplication,
    nonequivalence,
    negateddisjunction,
    negatedconjunction,
    negation,
    universal,
    existential,
//----Higher order
    lambda,
    pibinder,
    sigmabinder,
    choicebinder,
    descriptionbinder,
    typecolon,
    application,
    equation,
    negequation,  //----Never ends up in data structure - just a hacky thing
    typedequation,
    pi,
    sigma,
    choice,
    description,
    subtype,
    maparrow,
    xprodtype,
    uniontype,
    gentzenarrow,
    assignmentsym,
    identicalsym,
//----Non-classical
    box,
    diamond,
    quatrefoil,
    circle,
//----Special for unknown quantification
    free_variable,
//----Specials for output formatting
    outermost,
    brackets,
//----For parsing when coming from outermost (why did I not reuse outermost?)
    none
} ConnectiveType;
//-------------------------------------------------------------------------------------------------
//----Terms
typedef enum {
//----A variable or a function, for requests not used after parsing has resolved it.
    term,   
//----Arguments in THF and TXF are formulae, which are terms of type atom
    atom_as_term,
//----Set TheSymbol = "[]" for a tuple "function"
    function,
    variable,
    nested_thf,
    nested_tff,
    nested_tcf,
    nested_fof,
    nested_cnf,
    nested_fot,   // Used to record variable bindings in proofs
//----Types are stored as terms too
    a_type,
//----For formulae arguments in THF and TXF
    formula,
//----For connectives used as terms in THF, e.g., (&)
    connective,
//----For useful info, source, etc. Not in signature.
    non_logical_data,  
//----Forcing a new variable to be inserted, replaced by variable
    new_variable,
    nonterm
} TermType;

typedef struct VariableTag {
    int NumberOfUses;
    ConnectiveType Quantification;
    TermType Type;
    struct TermNodeTag * Instantiation;
    SYMBOLNODE VariableName;
    struct VariableTag * NextVariable;
} VariableNodeType;

typedef VariableNodeType * VARIABLENODE;

typedef union {
    SYMBOLNODE NonVariable;
    VARIABLENODE Variable;
    struct FormulaWithVariablesTag * NestedFormula;
    struct TermWithVariablesTag * NestedTerm;
//----For nested THF and TXF formulae
    struct FormulaTypetag * Formula;
} TermUnionType;

typedef struct TermNodeTag {
    TermType Type;
    TermUnionType TheSymbol;
//----Used for lists (they can be extended). Symbol arity is set to -1
    int FlexibleArity;
    struct TermNodeTag ** Arguments;
} TermNodeType;

typedef TermNodeType * TERM;

typedef TERM * TERMArray;

//-------------------------------------------------------------------------------------------------
//----Formula types
typedef enum {
    sequent,
    assignment,  //----For := and ==
    type_declaration,
    quantified,
    binary,
    unary,
    atom,
    applied_connective,
    tuple,
    ite_formula,
    let_formula,
    nonformulatype
} FormulaTypeType;

typedef struct {
    ConnectiveType Quantifier;
    int ExistentialCount;
    TERM Variable;
    struct FormulaTypetag * VariableType;
    struct FormulaTypetag * Formula;
} QuantifiedFormulaType;

typedef struct {
    struct FormulaTypetag * LHS;
    ConnectiveType Connective;
    struct FormulaTypetag * RHS;
} BinaryFormulaType;

typedef struct {
    ConnectiveType Connective;
    struct FormulaTypetag * Formula;
} UnaryFormulaType;

typedef struct {
    int NumberOfElements;
    struct FormulaTypetag ** Elements;
} TupleFormulaType;

typedef struct {
    int NumberOfLHSElements;
    struct FormulaTypetag ** LHS;
    int NumberOfRHSElements;
    struct FormulaTypetag ** RHS;
} SequentFormulaType;

typedef struct {
    struct FormulaTypetag * Condition;
    struct FormulaTypetag * FormulaIfTrue;
    struct FormulaTypetag * FormulaIfFalse;
} ConditionalFormulaType;

typedef struct {
    struct FormulaTypetag * LetTypes;
    struct FormulaTypetag * LetDefn;
    struct FormulaTypetag * LetBody;
} LetFormulaType;

typedef union {
    TupleFormulaType TupleFormula;
    SequentFormulaType SequentFormula;
    QuantifiedFormulaType QuantifiedFormula;
    BinaryFormulaType BinaryFormula;  //----Includes type declarations and assignments
    UnaryFormulaType UnaryFormula;
    ConditionalFormulaType ConditionalFormula;
    LetFormulaType LetFormula;
    TERM Atom;
} FormulaUnionType;

typedef struct FormulaTypetag {
    FormulaTypeType Type;
    FormulaUnionType FormulaUnion;
} FormulaType;

typedef FormulaType * FORMULA;

typedef FORMULA * FORMULAArray;

//----If I were to do this again, I'd link the variables from the
//----AnnotatedTSTPFormulaType
typedef struct FormulaWithVariablesTag {
    FORMULA Formula;
    VARIABLENODE Variables;
} FormulaWithVariablesType;

typedef FormulaWithVariablesType * FORMULAWITHVARIABLES;

typedef struct TermWithVariablesTag {
    TERM Term;
    VARIABLENODE Variables;
} TermWithVariablesType;

typedef TermWithVariablesType * TERMWITHVARIABLES;

typedef struct {
    VARIABLENODE * Variables;
    SIGNATURE Signature;
} ContextType;
//-------------------------------------------------------------------------------------------------
//----Annotated records
typedef enum {
    tptp_tpi,
    tptp_thf,
    tptp_tff,
    tptp_fof,
    tptp_tcf,
    tptp_cnf,
    tptp_mixed,
    include,
    blank_line,
    comment,
    nontype
} SyntaxType;

typedef enum {
//----Old for backwards compatibility
    initial,
    derived,
//----Current
    assumption,
    axiom,
    hypothesis,
    definition,
    lemma,
    theorem,
    corollary,
    conjecture,
    question,
    negated_conjecture,
    plain,
    answer,
//----For typed logics
    type,
//----For interpretations
    fi_domain,
    fi_functors,
    fi_predicates,
    interpretation,
    unknown,
//----Collections
    logical,
    axiom_like,
    not_conjecture,
//----For logic specifications
    logic,
//----External
    external,
//----Future
    knowledge,
//---TPI
    tpi_input,
    tpi_output,
    tpi_activate,
    tpi_deactivate,
    tpi_delete,
    tpi_set_role,
    tpi_start_group,
    tpi_end_group,
    tpi_activate_group,
    tpi_deactivate_group,
    tpi_delete_group,
    tpi_setenv,
    tpi_waitenv,
    tpi_unsetenv,
    tpi_set_logic,
    tpi_execute,
    tpi_execute_async,
    tpi_filter,
    tpi_generate,
    tpi_mktemp,
    tpi_assert,
    tpi_write,
    tpi_clean,
    tpi_exit,
//----None of the above
    nonstatus
} StatusType;

typedef struct {
    char * Name;
    StatusType Status;
    TERM SubStatus;
    FORMULAWITHVARIABLES FormulaWithVariables;
    TERM Source;
    TERM UsefulInfo;
} AnnotatedTSTPFormulaType;

typedef char * CommentType;

typedef TERM IncludeType;

typedef union {
    AnnotatedTSTPFormulaType AnnotatedTSTPFormula;
    CommentType Comment;
    IncludeType Include;
} AnnotatedFormulaUnionType;

typedef struct {
    int NumberOfUses;
    SyntaxType Syntax;
    AnnotatedFormulaUnionType AnnotatedFormulaUnion;
} AnnotatedFormulaType;

typedef AnnotatedFormulaType * ANNOTATEDFORMULA;
//-------------------------------------------------------------------------------------------------
//----Types for lists and trees of annotated formulae
typedef struct TreeNodeTag {
    int NumberOfUses;
    ANNOTATEDFORMULA AnnotatedFormula;
    int NumberOfParents;
    struct TreeNodeTag ** Parents;
    int Visited;
    void * UserData;
} TreeNodeType;

typedef TreeNodeType * TREENODE;

typedef struct RootListTag {
    TREENODE TheTree;
//----For lists the Last is always NULL - lists are not doubly linked.
//----For binary trees the Last comes before and the Next comes after.
    struct RootListTag * Last;
    struct RootListTag * Next;
} RootListType;

typedef RootListType * ROOTLIST;
//----Make alias for binary tree case, to avoid confusion in code
#define ROOTBTREE ROOTLIST

typedef struct ListNodeTag {
    ANNOTATEDFORMULA AnnotatedFormula;
//----For lists the Last is always NULL - lists are not doubly linked.
//----For binary trees the Last comes before and the Next comes after.
    struct ListNodeTag * Last;
    struct ListNodeTag * Next;
    int Visited;  //----Never used???
//TODO check if it is ever used
} ListNodeType;

typedef ListNodeType * LISTNODE;
//----Make alias for binary tree case, to avoid confusion in code
#define BTREENODE LISTNODE

typedef struct ListListTag {
    LISTNODE TheList;
    struct ListListTag * Next;
} HeadListType;

typedef HeadListType * HEADLIST;

//-------------------------------------------------------------------------------------------------
#endif

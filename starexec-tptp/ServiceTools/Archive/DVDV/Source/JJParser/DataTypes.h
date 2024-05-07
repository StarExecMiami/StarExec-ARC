#ifndef DATATYPES_H
#define DATATYPES_H
//-----------------------------------------------------------------------------
//----Types for the signature
typedef struct SymbolTag {
    char * NameSymbol;
    int NumberOfUses;
    int Arity;
    struct SymbolTag * NextSymbol;
} SymbolNodeType;

typedef SymbolNodeType * SYMBOLNODE;

typedef struct {
    SYMBOLNODE Variables;
    SYMBOLNODE Functions;
    SYMBOLNODE Predicates;
    SYMBOLNODE NonLogicals;
} SignatureType;

typedef SignatureType * SIGNATURE;
//-----------------------------------------------------------------------------
typedef enum {
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
//----Special for unknown quantification
    free_variable,
//----Specials for output formatting
    outermost,
    none
} ConnectiveType;

//----Types for variable instance lists
typedef struct VariableTag {
    int NumberOfUses;
    ConnectiveType Quantification;
    struct TermNodeTag * Instantiation;
    SYMBOLNODE VariableName;
    struct VariableTag * NextVariable;
} VariableNodeType;

typedef VariableNodeType * VARIABLENODE;

typedef struct {
    VARIABLENODE * Variables;
    SIGNATURE Signature;
} ContextType;
//-----------------------------------------------------------------------------
//----Terms
typedef enum {
    predicate,
    term,
    function,
    variable,
//----Forcing a new variable to be inserted, replaced by variable
    new_variable,
//----For useful info, source, etc. Not in signature.
//----Set TheSymbol = "[]" for a list
    non_logical_data,  
    nonterm
} TermType;

typedef union {
    SYMBOLNODE NonVariable;
    VARIABLENODE Variable;
} TERMNODE;

typedef struct TermNodeTag {
    TermType Type;
    TERMNODE TheSymbol;
//----Used for lists (they can be extended). Symbol arity is set to -1
    int FlexibleArity;
    struct TermNodeTag ** Arguments;
} TermNodeType;

typedef TermNodeType * TERM;

typedef TERM * TERMArray;
//-----------------------------------------------------------------------------
//----Formula types
typedef enum {
    quantified,
    binary,
    unary,
    atom,
    nonformulatype
} FormulaTypeType;

typedef struct {
    ConnectiveType Quantifier;
    int ExistentialCount;
    TERM Variable;
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

typedef union {
    QuantifiedFormulaType QuantifiedFormula;
    BinaryFormulaType BinaryFormula;
    UnaryFormulaType UnaryFormula;
    TERM Atom;
} FormulaUnionType;

typedef struct FormulaTypetag {
    FormulaTypeType Type;
    FormulaUnionType FormulaUnion;
} FormulaType;

typedef FormulaType * FORMULA;

//----If I were to do this again, I'd link the variables from the
//----AnnotatedTSTPFormulaType
typedef struct {
    FORMULA Formula;
    VARIABLENODE Variables;
} FormulaWithVariablesType;

typedef FormulaWithVariablesType * FORMULAWITHVARIABLES;
//-----------------------------------------------------------------------------
//----Annotated records
typedef enum {
    tptp_fof,
    tptp_cnf,
    tptp_mixed,
    include,
    blank_line,
    comment,
    nontype
} SyntaxType;

typedef enum {
    initial,
    derived,
    axiom,
    definition,
    knowledge,
    assumption,
    hypothesis,
    conjecture,
    negated_conjecture,
    lemma,
    theorem,
    plain,
    unknown,
    nonstatus
} StatusType;

typedef struct {
    char* Name;
    StatusType Status;
    StatusType SubStatus;
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
//-----------------------------------------------------------------------------
//----Types for lists and trees of annotated formulae
typedef struct TreeNodeTag {
    int NumberOfUses;
    ANNOTATEDFORMULA AnnotatedFormula;
    int NumberOfParents;
    struct TreeNodeTag ** Parents;
    int Visited;
    double StatisticsCache;
} TreeNodeType;

typedef TreeNodeType * TREENODE;

typedef struct RootListTag {
    TREENODE TheTree;
    struct RootListTag * Next;
} RootListType;

typedef RootListType * ROOTLIST;

typedef struct ListNodeTag {
    ANNOTATEDFORMULA AnnotatedFormula;
    struct ListNodeTag * Next;
} ListNodeType;

typedef ListNodeType * LISTNODE;

typedef struct ListListTag {
    LISTNODE TheList;
    struct ListListTag * Next;
} HeadListType;

typedef HeadListType * HEADLIST;

//-----------------------------------------------------------------------------
#endif

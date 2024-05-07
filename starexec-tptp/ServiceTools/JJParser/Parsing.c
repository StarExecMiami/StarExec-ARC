#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Parsing.h"
#include "Tokenizer.h"
#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Signature.h"
#include "Examine.h"
#include "List.h"
#include "ParseTSTP.h"
#include "ParseTPTP.h"
#include "PrintTSTP.h"
//-------------------------------------------------------------------------------------------------
static int AllowFreeVariables = 0;
static int AllowFOFNumbers = 0;
//-------------------------------------------------------------------------------------------------
void SetAllowFreeVariables(int OnOff) {

    AllowFreeVariables = OnOff;
}
//-------------------------------------------------------------------------------------------------
void SetAllowFOFNumbers(int OnOff) {

    AllowFOFNumbers = OnOff;
}
//-------------------------------------------------------------------------------------------------
void IncreaseVariableUseCount(VARIABLENODE Variable,int HowMuch) {

    Variable->NumberOfUses += HowMuch;
    IncreaseSymbolUseCount(Variable->VariableName,HowMuch);
}
//-------------------------------------------------------------------------------------------------
void PrintVariableList(VARIABLENODE Variables,VARIABLENODE EndOfScope) {

    printf("Formula variables: ");
    if (EndOfScope == NULL) {
        printf("(EndOfScope is NULL): ");
    } 
    while (Variables != NULL) {
        printf("%s/%d(%d)@%p ",GetSignatureSymbol(Variables->VariableName),
GetSignatureArity(Variables->VariableName),Variables->NumberOfUses,Variables);
        if (Variables == EndOfScope) {
            printf("--- end of scope ---\n");
        }
        Variables = Variables->NextVariable;
    }
    printf("\n");
}
//-------------------------------------------------------------------------------------------------
VARIABLENODE IsVariableInList(VARIABLENODE List,VARIABLENODE EndOfScope,
char * Name) {

    VARIABLENODE NodeFound;

//DEBUG printf("about to start search for %s in list ...\n",Name);
//DEBUG PrintVariableList(List,EndOfScope);
    NodeFound = NULL;
//----Need the last with this name in list up to end of scope. Last to get
//----smallest scope
    while (EndOfScope != NULL && List != NULL) {
//----If found then woohoo
//DEBUG printf("looking for %s, looking at %s\n",Name,GetSignatureSymbol(List->VariableName));
        if (!strcmp(GetSignatureSymbol(List->VariableName),Name)) {
            NodeFound = List;
        }
//----If at end of scope then not found
        if (List == EndOfScope) {
            return(NodeFound);
        }
//----Otherwise move on down the list
        List = List->NextVariable;
    }

    return(NodeFound);
}
//-------------------------------------------------------------------------------------------------
VARIABLENODE NewVariable(void) {

    VARIABLENODE NewVariable;

    NewVariable = (VARIABLENODE)Malloc(sizeof(VariableNodeType));
    NewVariable->NumberOfUses = 0;
    NewVariable->Quantification = none;
    NewVariable->Instantiation = NULL;
    NewVariable->VariableName = NULL;
    NewVariable->NextVariable = NULL;

    return(NewVariable);
}
//-------------------------------------------------------------------------------------------------
void RemoveVariable(VARIABLENODE * Variables,VARIABLENODE * Variable) {

//----Variables points to the pointer to the first element of the list of
//----variable node. Variable points to the pointer to the one to remove.
//----Search down the list.
    while (*Variables != NULL && *Variables != *Variable) {
        Variables = &((*Variables)->NextVariable);
    }

    if (*Variables == NULL) {
        CodingError("Tried to remove a non-existent variable");
    }

//----Bypass in the list
    *Variables = (*Variables)->NextVariable;
//----Remove the list element
    Free((void **)Variable);
}
//-------------------------------------------------------------------------------------------------
VARIABLENODE InsertVariable(READFILE Stream,SIGNATURE Signature,VARIABLENODE * Variables,
VARIABLENODE * EndOfScope,int ForceNew,char * VariableName,ConnectiveType Quantification,
int MustBeQuantifiedAlready) {

    VARIABLENODE Variable;
    VARIABLENODE FoundVariable;
    String ErrorMessage;

//DEBUG printf("Variable %s forced = %d allowfree = %d mbqa = %d\n",VariableName,ForceNew,AllowFreeVariables,MustBeQuantifiedAlready);
//DEBUG PrintVariableList(*Variables,*EndOfScope);

    FoundVariable = IsVariableInList(*Variables,*EndOfScope,VariableName);

//----Bail if not quantified
    if (!AllowFreeVariables && MustBeQuantifiedAlready && 
Quantification == free_variable && FoundVariable == NULL) {
        sprintf(ErrorMessage,"Unquantified variable %s",VariableName);
        TokenError(Stream,ErrorMessage);
    }

//----Check if variable exists in the current scope
    if (!ForceNew && FoundVariable != NULL) {
//DEBUG printf("Found variable %s  in the list\n",VariableName);
        IncreaseVariableUseCount(FoundVariable,1);
        return(FoundVariable);
    } else {

//----Add new variable
        Variable = NewVariable();
        Variable->NumberOfUses = 1;
        Variable->Quantification = Quantification;
        Variable->Instantiation = NULL;
        Variable->VariableName = InsertIntoSignature(Signature,variable,VariableName,0,-1,0,NULL);

//----If a tolerated free variable, add at top and don't change context
        if (FoundVariable == NULL && Quantification == free_variable && AllowFreeVariables) {
//DEBUG printf("Adding free variable %s\n",VariableName);
            Variable->NextVariable = (*Variables);
            *Variables = Variable;
            if (*EndOfScope == NULL) {
                *EndOfScope = Variable;
            }
//DEBUG PrintVariableList(*Variables,*EndOfScope);
        } else {
//----If the top of the formula's variable list, then update the context
            if (*EndOfScope == NULL) {
                Variable->NextVariable = (*Variables);
                *Variables = Variable;
            } else {
//----Otherwise add after the end of scope
                assert(*Variables != NULL);
                Variable->NextVariable = (*EndOfScope)->NextVariable;
                (*EndOfScope)->NextVariable = Variable;
            }
//----This new variable is the new end of scope
            *EndOfScope = Variable;
        }
//DEBUG PrintVariableList(*Variables,*EndOfScope);
        return(Variable);
    }
}
//-------------------------------------------------------------------------------------------------
VARIABLENODE ParallelCopyVariableList(VARIABLENODE Original) {

    VARIABLENODE Copy;

    if (Original == NULL) {
        return(NULL);
    } else {
        Copy = NewVariable();
        *Copy = *Original;
        Copy->NumberOfUses = 0;
        Copy->Instantiation = (TERM)Original;
        Copy->NextVariable = ParallelCopyVariableList(Original->NextVariable);
        return(Copy);
    }
}
//-------------------------------------------------------------------------------------------------
void ParallelCopyVariableInstantiations(VARIABLENODE Original,VARIABLENODE Copy) {

    if (Original == NULL) {
        if (Copy == NULL) {
            return;
        } else {
            CodingError("Different length variable lists from duplication");
        }
    } else {
        Copy->Instantiation = Original->Instantiation;
        ParallelCopyVariableInstantiations(Original->NextVariable,Copy->NextVariable);
    }
}
//-------------------------------------------------------------------------------------------------
TERM NewTerm(void) {

    TERM Term;

    Term = (TERM)Malloc(sizeof(TermNodeType));
    Term->Type = nonterm;
    Term->FlexibleArity = -1;
    Term->TheSymbol.Variable = NULL;
    Term->Arguments = NULL;

    return(Term);
}
//-------------------------------------------------------------------------------------------------
TERMWITHVARIABLES NewTermWithVariables(void) {

    TERMWITHVARIABLES TermWithVariables;

    TermWithVariables = (TERMWITHVARIABLES)Malloc(sizeof(TermWithVariablesType));
    TermWithVariables->Term = NULL;
    TermWithVariables->Variables = NULL;

    return(TermWithVariables);
}
//-------------------------------------------------------------------------------------------------
void FreeTerm(TERM * Term,SIGNATURE Signature,VARIABLENODE * Variables) {

    int ArgumentIndex;

    if ((*Term) != NULL) {
//DEBUG printf("Free term with type %s\n",TermTypeToString((*Term)->Type));
        if ((*Term)->Type == variable) {
            (*Term)->TheSymbol.Variable->VariableName->NumberOfUses--;
            (*Term)->TheSymbol.Variable->NumberOfUses--;
            if ((*Term)->TheSymbol.Variable->NumberOfUses == 0) {
                RemoveVariable(Variables,&((*Term)->TheSymbol.Variable));
                assert((*Term)->TheSymbol.Variable == NULL);
            }
        } else if ((*Term)->Type == formula) {
//DEBUG printf("Free formula term \n");
            FreeFormula(&((*Term)->TheSymbol.Formula),Signature,Variables);
        } else if ((*Term)->Type == nested_thf || (*Term)->Type == nested_tff || 
(*Term)->Type == nested_tcf || (*Term)->Type == nested_fof || (*Term)->Type == nested_cnf) {
            FreeFormulaWithVariables(&((*Term)->TheSymbol.NestedFormula),Signature);
        } else if ((*Term)->Type == nested_fot) {
            FreeTermWithVariables(&((*Term)->TheSymbol.NestedTerm),Signature);
        } else {
//DEBUG printf("Free normal term with symbol %s\n",(*Term)->TheSymbol.NonVariable->NameSymbol);
            if ((*Term)->Arguments != NULL) {
                for (ArgumentIndex=0;ArgumentIndex<GetArity(*Term);ArgumentIndex++) {
//DEBUG printf("Free arg %d of %d\n",ArgumentIndex,ArgumentIndex<GetArity(*Term));
                    FreeTerm(&((*Term)->Arguments[ArgumentIndex]),Signature,Variables);
                    assert((*Term)->Arguments[ArgumentIndex] == NULL);
                }
                Free((void **)&((*Term)->Arguments));
            }
//DEBUG printf("Freed args of normal term with symbol %s\n",(*Term)->TheSymbol.NonVariable->NameSymbol);
            (*Term)->TheSymbol.NonVariable->NumberOfUses--;
//DEBUG printf("TheSymbol %s/%d now has %d uses\n",(*Term)->TheSymbol.NonVariable->NameSymbol,GetArity(*Term),(*Term)->TheSymbol.NonVariable->NumberOfUses);
        }
        Free((void **)Term);
    }
}
//-------------------------------------------------------------------------------------------------
void FreeTermWithVariables(TERMWITHVARIABLES * TermWithVariables,SIGNATURE Signature) {

    if (*TermWithVariables != NULL) {
        FreeTerm(&((*TermWithVariables)->Term),Signature,&((*TermWithVariables)->Variables));
        assert((*TermWithVariables)->Term == NULL);
        assert((*TermWithVariables)->Variables == NULL);
        Free((void **)TermWithVariables);
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA NewFormula(void) {

    FORMULA Formula;

    Formula = (FORMULA)Malloc(sizeof(FormulaType));
    Formula->Type = nonformulatype;

    return(Formula);
}
//-------------------------------------------------------------------------------------------------
FORMULAWITHVARIABLES NewFormulaWithVariables(void) {

    FORMULAWITHVARIABLES FormulaWithVariables;

    FormulaWithVariables = (FORMULAWITHVARIABLES)Malloc(sizeof(FormulaWithVariablesType));
    FormulaWithVariables->Formula = NULL;
    FormulaWithVariables->Variables = NULL;

    return(FormulaWithVariables);
}
//-------------------------------------------------------------------------------------------------
void FreeTupleFormulae(int NumberOfElements,FORMULAArray * TupleFormulae,SIGNATURE Signature,
VARIABLENODE * Variables) {

    if (NumberOfElements > 0) {
        while (NumberOfElements > 0) {
            FreeFormula((*TupleFormulae)+NumberOfElements-1,Signature,Variables);
            NumberOfElements--;
        }
        Free((void **)TupleFormulae);
        *TupleFormulae = NULL;
    } else {
//----Check that the array is empty
        assert(*TupleFormulae == NULL);
    }
}
//-------------------------------------------------------------------------------------------------
void FreeFormula(FORMULA * Formula,SIGNATURE Signature,VARIABLENODE * Variables) {

    SYMBOLNODE Symbol;

    if (*Formula != NULL) {
        switch ((*Formula)->Type) {
            case tuple:
                FreeTupleFormulae((*Formula)->FormulaUnion.TupleFormula.NumberOfElements,
&((*Formula)->FormulaUnion.TupleFormula.Elements),Signature,Variables);
                assert((*Formula)->FormulaUnion.TupleFormula.Elements == NULL);
                break;
                FreeTupleFormulae((*Formula)->FormulaUnion.SequentFormula.NumberOfLHSElements,
&((*Formula)->FormulaUnion.SequentFormula.LHS),Signature,Variables);
                assert((*Formula)->FormulaUnion.SequentFormula.LHS == NULL);
                FreeTupleFormulae((*Formula)->FormulaUnion.SequentFormula.NumberOfRHSElements,
&((*Formula)->FormulaUnion.SequentFormula.RHS),Signature,Variables);
                assert((*Formula)->FormulaUnion.SequentFormula.RHS == NULL);
                break;
            case quantified:
                FreeTerm(&((*Formula)->FormulaUnion.QuantifiedFormula.Variable),Signature,
Variables);
                assert((*Formula)->FormulaUnion.QuantifiedFormula.Variable == NULL);
                FreeFormula(&((*Formula)->FormulaUnion.QuantifiedFormula.VariableType),Signature,
Variables);
                assert((*Formula)->FormulaUnion.QuantifiedFormula.VariableType == NULL);
                FreeFormula(&((*Formula)->FormulaUnion.QuantifiedFormula.Formula),Signature,
Variables);
                assert((*Formula)->FormulaUnion.QuantifiedFormula.Formula == NULL);
                break;
            case binary:
            case assignment:
            case type_declaration:
                FreeFormula(&((*Formula)->FormulaUnion.BinaryFormula.LHS),Signature,Variables);
                assert((*Formula)->FormulaUnion.BinaryFormula.LHS == NULL);
                if ((*Formula)->FormulaUnion.BinaryFormula.Connective == equation) {
                    if ((Symbol = IsSymbolInSignatureList(Signature->Predicates,"=",2,NULL)) != 
NULL) {
                        IncreaseSymbolUseCount(Symbol,-1);
                    } else {
                        CodingError("Freeing an equation, but = not in signature");
                    }
                }
                FreeFormula(&((*Formula)->FormulaUnion.BinaryFormula.RHS),Signature,Variables);
                assert((*Formula)->FormulaUnion.BinaryFormula.RHS == NULL);
                break;
            case unary:
                FreeFormula(&((*Formula)->FormulaUnion.UnaryFormula.Formula),Signature,Variables);
                assert((*Formula)->FormulaUnion.UnaryFormula.Formula == NULL);
                break; 
            case atom:
            case applied_connective:
                FreeTerm(&((*Formula)->FormulaUnion.Atom),Signature,Variables);
                assert((*Formula)->FormulaUnion.Atom == NULL);
                break;
            case ite_formula:
                FreeFormula(&((*Formula)->FormulaUnion.ConditionalFormula.Condition),Signature,
Variables);
                FreeFormula(&((*Formula)->FormulaUnion.ConditionalFormula.FormulaIfTrue),Signature,
Variables);
                FreeFormula(&((*Formula)->FormulaUnion.ConditionalFormula.FormulaIfFalse),
Signature,Variables);
                break;
            case let_formula:
                FreeFormula(&((*Formula)->FormulaUnion.LetFormula.LetTypes),Signature,Variables);
                FreeFormula(&((*Formula)->FormulaUnion.LetFormula.LetDefn),Signature,Variables);
                FreeFormula(&((*Formula)->FormulaUnion.LetFormula.LetBody),Signature,Variables);
                break;
            default:
                CodingError("Formula type unknown for freeing");
                break;
        }
        Free((void **)Formula);
    }
}
//-------------------------------------------------------------------------------------------------
void FreeFormulaWithVariables(FORMULAWITHVARIABLES * FormulaWithVariables,SIGNATURE Signature) {

    if (*FormulaWithVariables != NULL) {
        FreeFormula(&((*FormulaWithVariables)->Formula),Signature,
&((*FormulaWithVariables)->Variables));
        assert((*FormulaWithVariables)->Formula == NULL);
        assert((*FormulaWithVariables)->Variables == NULL);
        Free((void **)FormulaWithVariables);
    }
}
//-------------------------------------------------------------------------------------------------
TERMArray NewArguments(int NumberOfArguments) {

    TERMArray Arguments;
    int Index;

    Arguments = (TERMArray)Malloc(NumberOfArguments * sizeof(TERM));
    for (Index = 0; Index < NumberOfArguments; Index++) {
        Arguments[Index] = NULL;
    }

    return(Arguments);
}
//-------------------------------------------------------------------------------------------------
TERMArray DuplicateArguments(int Arity,TERMArray Original,ContextType Context,
int ForceNewVariables) {

    TERMArray Arguments;
    int ArgumentNumber;

//----Arguments could be null when duplicating the type declaration of a symbol
//DEBUG printf("Duplicating arguments length %d, forced new variables %d\n",Arity,ForceNewVariables);
    if (Arity > 0 && Original != NULL) {
        Arguments = NewArguments(Arity);
        for (ArgumentNumber=0;ArgumentNumber<Arity;ArgumentNumber++) {
//DEBUG printf("Duplicating arg %d ",ArgumentNumber); PrintTSTPTerm(stdout,tptp_tff,Original[ArgumentNumber],0,1,1);
            Arguments[ArgumentNumber] = DuplicateTerm(Original[ArgumentNumber],Context,
ForceNewVariables);
        }
        return(Arguments);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
TERM ParseArgument(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,TermType DesiredType,int VariablesMustBeQuantified) {

    TERM FormulaArgument;

//----THF and TFF have formulae as arguments. Type is formula if looking for arguments of a
//----predicate or function in THF and TFF.
    if ((Language == tptp_thf || Language == tptp_tff || Language == tptp_tcf) &&
(DesiredType == function || DesiredType == atom_as_term) ) {
        FormulaArgument = NewTerm();
        FormulaArgument->Type = formula;
        FormulaArgument->TheSymbol.Formula = ParseFormula(Stream,Language,Context,EndOfScope,1,1,
VariablesMustBeQuantified,none);
        return(FormulaArgument);
    } else {
//----If parsing non-logical, keep it like that, else it must be a term (variable or function)
        if (DesiredType != non_logical_data) {
            DesiredType = term;
        }
        return(ParseTerm(Stream,Language,Context,EndOfScope,DesiredType,free_variable,NULL,
VariablesMustBeQuantified));
    }
}
//-------------------------------------------------------------------------------------------------
TERMArray ParseArguments(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int * Arity,TermType DesiredType,char * MatchingBracket,
int VariablesMustBeQuantified) {

    TERMArray Arguments;

//----Disallows the () case, which is illegal in the BNF
    if (!strcmp(MatchingBracket,"]") && CheckToken(Stream,punctuation,MatchingBracket)) {
        Arguments = (TERMArray)NULL;
        *Arity = 0;
    } else {
        Arguments = (TERMArray)Malloc(sizeof(TERM));
        *Arity = 1;
        Arguments[0] = ParseArgument(Stream,Language,Context,EndOfScope,DesiredType,
VariablesMustBeQuantified);
        while (CheckToken(Stream,punctuation,",")) {
            AcceptToken(Stream,punctuation,",");
            (*Arity)++;
            Arguments = (TERMArray)Realloc((void *)Arguments,*Arity * sizeof(TERM));
            Arguments[*Arity - 1] = ParseArgument(Stream,Language,Context,EndOfScope,DesiredType,
VariablesMustBeQuantified);
        }
    }
    return(Arguments);
}
//-------------------------------------------------------------------------------------------------
//----This assumes it's in the context of duplicating a formula with variables
TERM DuplicateTerm(TERM Original,ContextType Context,int ForceNewVariables) {

    TERM Term;
    VARIABLENODE Variable;
    String ErrorMessage;
    TermType ActualType;

    if (Original == NULL) {
        return(NULL);
    }

    Term = NewTerm();
    *Term = *Original;

    switch (Term->Type) {
        case connective:
            break;
        case atom_as_term:
        case function:
        case a_type:
        case non_logical_data:
//----For TFF functions are stored as atom_as_term. Need to hack arond that
            if (Term->Type == atom_as_term && IsSymbolInSignatureList(Context.Signature->Functions,
GetSymbol(Term),GetArity(Term),NULL) != NULL) {
                ActualType = function;
            } else {
                ActualType = Term->Type;
            }
//DEBUG printf("Duplicating term with symbol %s, original type %s, fixed type %s, arity %d, arguments are %s \n",GetSymbol(Term),TermTypeToString(Term->Type),TermTypeToString(ActualType),GetArity(Term),Original->Arguments == NULL ? "NULL" : "not NULL");
            Term->TheSymbol.NonVariable = InsertIntoSignature(Context.Signature,ActualType,
Original->TheSymbol.NonVariable->NameSymbol,Original->TheSymbol.NonVariable->Arity,
Original->TheSymbol.NonVariable->AppliedArity,Original->TheSymbol.NonVariable->InternalSymbol,
NULL);
//DEBUG printf("Duplicated term with symbol %s, type %s, arity %d, arguments are %s \n",GetSymbol(Term),TermTypeToString(Term->Type),GetArity(Term),Original->Arguments == NULL ? "NULL" : "not NULL");
            Term->Arguments = DuplicateArguments(GetArity(Term),Original->Arguments,Context,
ForceNewVariables);
            break;
        case variable:
//----Look for the corresponding variable in the new variables list
            Variable = *(Context.Variables);
            while (Variable != NULL && Variable->Instantiation !=
(TERM)Original->TheSymbol.Variable) {
                Variable = Variable->NextVariable;
            }
            if (Variable == NULL) {
                CodingError("Cannot find variable for copy of original");
            }
//----Check if it has been quantified, if not use original unless new is forced
            if (Variable->NumberOfUses > 0 || ForceNewVariables) {
                Term->TheSymbol.Variable = Variable;
            } else {
//----Use of the original is for the case of duplication of subformulae within a formula.
                Term->TheSymbol.Variable = Original->TheSymbol.Variable;
            }
            IncreaseVariableUseCount(Term->TheSymbol.Variable,1);
            break;
        case nested_thf:
        case nested_tff:
        case nested_tcf:
        case nested_fof:
        case nested_cnf:
//----For CNF the variables are implicitly universally quantified, and must
//----be new variables. For FOF we use the originals (can't recall why)
//----But later I decided that nested formulae are special, and should always
//----use new variables, e.g., for bind/2 terms.
            Term->TheSymbol.NestedFormula = DuplicateFormulaWithVariables(
Original->TheSymbol.NestedFormula,Context.Signature,1);
            break;
        case nested_fot:
            Term->TheSymbol.NestedTerm = DuplicateTermWithVariables(Original->TheSymbol.NestedTerm,
Context.Signature,0);
            break;
        case formula:
            Term->TheSymbol.Formula = DuplicateFormula(Original->TheSymbol.Formula,Context,
ForceNewVariables);
            break;
        default:
            sprintf(ErrorMessage,"Unknown term type %s to duplicate",TermTypeToString(Term->Type));
            CodingError(ErrorMessage);
            break;
    }
    return(Term);
}
//-------------------------------------------------------------------------------------------------
TERMWITHVARIABLES DuplicateTermWithVariables(TERMWITHVARIABLES Original,SIGNATURE Signature,
int ForceNewVariables) {

    ContextType Context;
    TERMWITHVARIABLES TermWithVariables;
    
    TermWithVariables = NewTermWithVariables();

//----Copy the variables list, setting each use to 0, and setting the
//----instantiation to point to the original (cheating in duplication :-)
    TermWithVariables->Variables = ParallelCopyVariableList(Original->Variables);
    
//----Create a context for the parsing
    Context.Variables = &(TermWithVariables->Variables);
    Context.Signature = Signature;
    
//DEBUG printf("original variables\n");
//DEBUG PrintVariableList(Original->Variables,NULL);
//DEBUG printf("parallel copy variables\n");
//DEBUG PrintVariableList(FormulaWithVariables->Variables,NULL);
    TermWithVariables->Term = DuplicateTerm(Original->Term,Context,ForceNewVariables);
//DEBUG printf("after copy variables\n");
//DEBUG PrintVariableList(FormulaWithVariables->Variables,NULL);

//----Set the variable instantiations to their rightful values
    ParallelCopyVariableInstantiations(Original->Variables,TermWithVariables->Variables);

    return(TermWithVariables); 
}
//-------------------------------------------------------------------------------------------------
TermType KnownTermTypeOrError(READFILE Stream,SyntaxType Language) {

    if (CheckTokenType(Stream,upper_word)) {
//DEBUG printf("Found a variable %s\n",CurrentToken(Stream)->NameToken);
        return(variable);
    } else {
//DEBUG printf("Found a function with functor %s\n",CurrentToken(Stream)->NameToken);
        if (CheckTokenType(Stream,functor) || CheckToken(Stream,punctuation,"[") ||
CheckToken(Stream,punctuation,"(")) {
//DEBUG printf("%s parsed as a function\n",CurrentToken(Stream)->NameToken);
//----Numbers not allowed in CNF or FOF
            if (!AllowFOFNumbers && (Language == tptp_cnf || Language == tptp_fof)) {
                EnsureTokenNotType(Stream,number);
            }
            return(function);
        } else {
//----Connectives are terms in THF
            if (Language == tptp_thf && 
(CheckTokenType(Stream,binary_connective) || CheckTokenType(Stream,unary_connective) ||
CheckToken(Stream,lower_word,"$ite"))) {
                return(function);
            } else if (Language == tptp_tff && CheckToken(Stream,punctuation,"{")) {
                return(function);
            } else {
//----Force an error
                EnsureTokenType(Stream,functor);
                return(nonterm);
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------
int InfixOperatorParsing(READFILE Stream,SyntaxType Language,TermType OriginallyExpectedType,
TermType * ExpectedRHSTermType) {

//DEBUG printf("Checking for infix, syntax %s, expected %s\n",SyntaxToString(Language),TermTypeToString(OriginallyExpectedType));
//----For THF and TFF equality is dealt with as a binary operator. That means here it's a regular
//----first-order situation, and equality is between terms (variables of functions).
    if (Language != tptp_thf && Language != tptp_tff && Language != tptp_tcf && 
OriginallyExpectedType == atom_as_term && 
(CheckToken(Stream,lower_word,"=") || CheckToken(Stream,lower_word,"!="))) {
        *ExpectedRHSTermType = term;
        return(1);
    }

//----Non-logical constructs
    if (OriginallyExpectedType == non_logical_data &&
(CheckToken(Stream,punctuation,"-") || CheckToken(Stream,punctuation,":"))) {
        *ExpectedRHSTermType = non_logical_data;
        return(1);
    }

    return(0);
}
//-------------------------------------------------------------------------------------------------
TERM ParseTerm(READFILE Stream,SyntaxType Language,ContextType Context,VARIABLENODE * EndOfScope,
TermType DesiredType,ConnectiveType VariableQuantifier,int * InfixNegatedAtom,
int VariablesMustBeQuantified) {

    TokenType FunctorType;
    TERM InfixTerm,Term;
    int NumberOfArguments;
    char * PrefixSymbol;
    String MatchingBracket;
    TermType TypeIfInfix;
    TermType InfixRHSType;
    int DoInfixProcessing;
    char * InfixToken;
    int SearchNumberOfArguments;
    SYMBOLNODE FoundSymbol;
    String ErrorMessage;

    Term = NewTerm();
    TypeIfInfix = nonterm;

//DEBUG printf("ParseTerm with token %s\n",CurrentToken(Stream)->NameToken);
//DEBUG printf("Hoping for a %s\n",TermTypeToString(DesiredType));
//----Record token type to check if brackets are legal later
    FunctorType = CurrentToken(Stream)->KindToken;

//----If a generic term, look at first letter to decide which
    switch (DesiredType) {
        case term:
//----Will come back as variable or function
            DesiredType = KnownTermTypeOrError(Stream,Language);
            break;
        case variable:
        case new_variable:
            EnsureTokenType(Stream,upper_word);
            break;
        case function:
            EnsureTokenType(Stream,functor);
            break;
        case atom_as_term:
//----Can't check it's a predicate because it might be infix with var first
//----      EnsureTokenType(Stream,predicate_symbol);
//DEBUG printf("Found a predicate with symbol %s %s (want %s)\n",CurrentToken(Stream)->NameToken,TokenTypeToString(CurrentToken(Stream)->KindToken),TokenTypeToString(lower_word));
            if (IsSymbolInSignatureList(Context.Signature->Types,CurrentToken(Stream)->NameToken,
0,Stream) != NULL) {
                DesiredType = a_type;
                TypeIfInfix = nonterm;
            } else {
//----Guess that it's a variable or function for infix predicate
                TypeIfInfix = KnownTermTypeOrError(Stream,Language);
//DEBUG printf("%s could be a %s\n",CurrentToken(Stream)->NameToken,TermTypeToString(TypeIfInfix));
            }
            break;
        case non_logical_data:
//DEBUG printf("Found a non-logical with symbol %s\n",CurrentToken(Stream)->NameToken);
//----Nested formulae and terms
            if (CheckToken(Stream,lower_word,"$thf")) {
                DesiredType = nested_thf;
            } else if (CheckToken(Stream,lower_word,"$tff")) {
                DesiredType = nested_tff;
            } else if (CheckToken(Stream,lower_word,"$tcf")) {
                DesiredType = nested_tcf;
            } else if (CheckToken(Stream,lower_word,"$fof")) {
                DesiredType = nested_fof;
            } else if (CheckToken(Stream,lower_word,"$cnf")) {
                DesiredType = nested_cnf;
            } else if (CheckToken(Stream,lower_word,"$fot")) {
                DesiredType = nested_fot;
            } else {
                TypeIfInfix = non_logical_data;
//----Make sure it's something that looks like a term
                if (!CheckTokenType(Stream,functor) && !CheckToken(Stream,punctuation,"[") && 
!CheckTokenType(Stream,upper_word)) {
                    TokenError(Stream,"Invalid non-logical data");
                }
            }
            break;
        default:
            CodingError("Term type unknown in parsing");
            break;
    }
    Term->Type = DesiredType;
//DEBUG printf("Set type of %s to %s\n",CurrentToken(Stream)->NameToken,TermTypeToString(DesiredType));

//----Save the symbol for inserting in signature later
    PrefixSymbol = CopyHeapString(CurrentToken(Stream)->NameToken);
//DEBUG printf("PrefixSymbol is %s\n",PrefixSymbol);
//----Eat the symbol if not a list in []s (tuple) or ()s (NXF arguments)
    if (strcmp(PrefixSymbol,"[") && strcmp(PrefixSymbol,"(")) {
        NextToken(Stream);
    }

    if (
( DesiredType == atom_as_term || DesiredType == function || DesiredType == non_logical_data ) &&
( CheckToken(Stream,punctuation,"(") || CheckToken(Stream,punctuation,"[") ) ) {
//DEBUG printf("it ==%s==has arguments\n\n",PrefixSymbol);
//----Now we can check that expected predicates look like predicates
//----Variables, distinct objects and numbers cannot have arguments
//THF TO FIX - Currently only allows ground predicates with arguments
        if (!CheckToken(Stream,punctuation,"[") && !CheckToken(Stream,punctuation,"(") &&
(FunctorType == upper_word || FunctorType == distinct_object || FunctorType == number ||
((DesiredType == atom_as_term || DesiredType == function) && FunctorType != lower_word))) {
            sprintf(ErrorMessage,
"Invalid form \"%s\" for a principal symbol, DesiredType is %s, FunctorType is %s\n",
CurrentToken(Stream)->NameToken,TermTypeToString(DesiredType),TokenTypeToString(FunctorType));
            TokenError(Stream,ErrorMessage);
        }
        if (CheckToken(Stream,punctuation,"(")) {
            strcpy(MatchingBracket,")");
        } else {
            strcpy(MatchingBracket,"]");
        }
        AcceptTokenType(Stream,punctuation);
        Term->Arguments = ParseArguments(Stream,Language,Context,EndOfScope,&NumberOfArguments,
DesiredType == non_logical_data ? non_logical_data : function,MatchingBracket,
VariablesMustBeQuantified);
        AcceptToken(Stream,punctuation,MatchingBracket);
//----Is it a nested formula?
    } else if (NestedFormulaType(DesiredType,0)) {
        NumberOfArguments = 0;
        Term->Arguments = NULL;
        AcceptToken(Stream,punctuation,"(");
        Term->TheSymbol.NestedFormula = ParseFormulaWithVariables(Stream,
DesiredType == nested_thf ? tptp_thf :
DesiredType == nested_tff ? tptp_tff : DesiredType == nested_tcf ? tptp_tcf :
DesiredType == nested_fof ? tptp_fof : tptp_cnf,Context.Signature,0);
//----Have to allow unbound variables in nested terms, e.g., for bind/2
//----terms in inference() terms where the list of bindings together makes
//----"free" variables ground.
        AcceptToken(Stream,punctuation,")");
    } else if (DesiredType == nested_fot) {
        NumberOfArguments = 0;
        Term->Arguments = NULL;
        AcceptToken(Stream,punctuation,"(");
        Term->TheSymbol.NestedTerm = ParseTermWithVariables(Stream,Language,Context.Signature,0);
        AcceptToken(Stream,punctuation,")");
//----Otherwise no list (roughly, no arguments to a predicate or function)
    } else {
        NumberOfArguments = 0;
        Term->Arguments = NULL;
//DEBUG printf("it ==%s== does not have arguments\n",PrefixSymbol);
    }

//----If a list make a special name and record flexible arity
    if (!strcmp(PrefixSymbol,"[")) {
//----Need an extra byte :-)
        Free((void **)&PrefixSymbol);
        PrefixSymbol = CopyHeapString("[]");
        Term->FlexibleArity = NumberOfArguments;
        NumberOfArguments = -1;
    }
    if (!strcmp(PrefixSymbol,"(")) {
//DEBUG printf("It is a (\n");
//----Need an extra byte :-)
        Free((void **)&PrefixSymbol);
        PrefixSymbol = CopyHeapString("()");
        Term->FlexibleArity = NumberOfArguments;
        NumberOfArguments = -1;
    }

//----Check for infix predicate
    if ((DoInfixProcessing = InfixOperatorParsing(Stream,Language,DesiredType,&InfixRHSType))) {
        if (DesiredType == atom_as_term && Language != tptp_thf && Language != tptp_tff &&
Language != tptp_tcf) {
            Term->Type = TypeIfInfix;
        }
//----If a term is expected, then if a variable it must be free here (infix =)
        if (InfixRHSType == term) {
            VariableQuantifier = free_variable;
        }
    } else {
//DEBUG printf("Not doing infix now, at %s\n",CurrentToken(Stream)->NameToken);
        InfixRHSType = nonterm;
//----Cannot have a variable if a predicate was expected, unless in a typed
//----language, where variables can be types in polymorphic cases.
        if (Language != tptp_thf && Language != tptp_tff && Language != tptp_tcf &&
DesiredType == atom_as_term && TypeIfInfix == variable) {
            TokenError(Stream,"Variables cannot be used as predicates except in THF and TFX");
        }
    }

//----Insert symbol into signature. Could be LHS of infix.
    if (Term->Type == non_logical_data) {
        Term->TheSymbol.NonVariable = InsertIntoSignature(Context.Signature,Term->Type,
PrefixSymbol,NumberOfArguments,-1,0,Stream);        
    } else if (Term->Type == new_variable) {
        Term->Type = variable;
        Term->TheSymbol.Variable = InsertVariable(Stream,Context.Signature,Context.Variables,
EndOfScope,1,PrefixSymbol,VariableQuantifier,VariablesMustBeQuantified);
//THF - this was Term->Type == variable, but I want to allow variable predicates. Will this work?
    } else if (((Language == tptp_thf || Language == tptp_tff || Language == tptp_tcf) && 
TypeIfInfix == variable) || Term->Type == variable) {
//----Force the term type to variable
        Term->Type = variable;
        Term->TheSymbol.Variable = InsertVariable(Stream,Context.Signature,Context.Variables,
EndOfScope,0,PrefixSymbol,free_variable,VariablesMustBeQuantified);
    } else if (NestedFormulaType(Term->Type,1)) {
//----Do nothing
    } else {
//----Need to note connectives used as terms in THF
        SearchNumberOfArguments = ((Language == tptp_thf && NumberOfArguments == 0) ? -1 : 
NumberOfArguments);
//DEBUG printf("See if type is known for %s/%d (search %d) currently %s\n",PrefixSymbol,NumberOfArguments,SearchNumberOfArguments,TermTypeToString(Term->Type));
//----Fix functions created from connectives in THF to be connective
        if (FunctorType == unary_connective || FunctorType == binary_connective ||
(FunctorType == lower_word && !strcmp(PrefixSymbol,"="))) {
            Term->Type = connective;
//----Numbers and distinct objects and NTF indices are known to be functions
        } else if (FunctorType == number || FunctorType == distinct_object || 
(FunctorType == lower_word && PrefixSymbol[0] == '#')) {
            Term->Type = function;
//----If is known to be a type from type declaration, fix this term type
        } else if (IsSymbolInSignatureList(Context.Signature->Types,PrefixSymbol,0,Stream) != 
NULL) {
            Term->Type = a_type;
//----Do predicates first so that THF things (SearchNumberOfArguments == -1) default to
//----atom_as_term rather than function
        } else if ((FoundSymbol = IsSymbolInSignatureList(Context.Signature->Predicates,
PrefixSymbol,SearchNumberOfArguments,Stream)) != NULL) {
//DEBUG printf("Yes, known predicate, convert %s to predicate arity %d\n",PrefixSymbol,NumberOfArguments);
            Term->Type = atom_as_term;
            if (GetSignatureArity(FoundSymbol) != -1) {
                NumberOfArguments = GetSignatureArity(FoundSymbol);
            }
//----By default things are type $i, i.e., function. But this makes undeclared predicates into
//----functions too. EVil world!
//        } else {
//            Term->Type = function;
        } else if ((FoundSymbol = IsSymbolInSignatureList(Context.Signature->Functions,PrefixSymbol,
SearchNumberOfArguments,Stream)) != NULL) {
//DEBUG printf("Yes, known function, convert %s to function arity %d\n",PrefixSymbol,NumberOfArguments);
            Term->Type = function;
//----If it has -1 arity in signature, then need to set it from arguments
            if (GetSignatureArity(FoundSymbol) != -1) {
                NumberOfArguments = GetSignatureArity(FoundSymbol);
            }
        }
//----Some functions and types might get inserted as predicates here when they appear on the LHS
//----of a type declaration, but that gets fixed later when the parsing of the declaration is
//----completed in ParseFormula.
        Term->TheSymbol.NonVariable = InsertIntoSignature(Context.Signature,Term->Type,
PrefixSymbol,NumberOfArguments,-1,0,Stream);
//----Note that if the term is a THF connective that is not a term, then the formula is deleted in 
//----ParseUnaryFormula and the NumberOfUses in the signature will be decremented, possibly down 
//----to 0.
    }

//----Free the saved symbol
    Free((void **)&PrefixSymbol);

//----Build the infix structure
    if (DoInfixProcessing) {
        InfixTerm = NewTerm();
        InfixTerm->Type = DesiredType;
//----Insert the infix symbol
        if (InfixNegatedAtom != NULL && CheckToken(Stream,lower_word,"!=")) {
            InfixToken = "=";
            *InfixNegatedAtom = 1;
        } else {
            InfixToken = CurrentToken(Stream)->NameToken;
        }
        InfixTerm->TheSymbol.NonVariable = InsertIntoSignature(Context.Signature,InfixTerm->Type,
InfixToken,2,-1,0,Stream);
        InfixTerm->Arguments = NewArguments(2);
        InfixTerm->Arguments[0] = Term;
//----Move on only after saving the infix operator
        NextToken(Stream);
        InfixTerm->Arguments[1] = ParseTerm(Stream,Language,Context,EndOfScope,InfixRHSType,
VariableQuantifier,NULL,VariablesMustBeQuantified);
        return(InfixTerm);
    } else {
//----Non-infix
        return(Term);
    }
}
//-------------------------------------------------------------------------------------------------
TERMWITHVARIABLES ParseTermWithVariables(READFILE Stream,SyntaxType Language,SIGNATURE Signature,
int VariablesMustBeQuantified) {

    ContextType Context;
    TERMWITHVARIABLES TermWithVariables;
    VARIABLENODE EndOfScope;
    int NeedNonLogicTokens;

    EndOfScope = NULL;
    TermWithVariables = NewTermWithVariables();

//----Create a context for the parsing
    Context.Variables = &(TermWithVariables->Variables);
    Context.Signature = Signature;

    NeedNonLogicTokens = Stream->NeedNonLogicTokens;
    Stream->NeedNonLogicTokens = 0;
    TermWithVariables->Term = ParseTerm(Stream,Language,Context,&EndOfScope,
non_logical_data,none,NULL,VariablesMustBeQuantified);
    Stream->NeedNonLogicTokens = NeedNonLogicTokens;
    return(TermWithVariables);
}
//-------------------------------------------------------------------------------------------------
int RightAssociative(ConnectiveType Connective) {

    return(Connective == disjunction || Connective == conjunction || Connective == maparrow);
}
//-------------------------------------------------------------------------------------------------
int LeftAssociative(ConnectiveType Connective) {

    return(Connective == disjunction || Connective == conjunction || Connective == application || 
Connective == xprodtype || Connective == uniontype);
}
//-------------------------------------------------------------------------------------------------
int Associative(ConnectiveType Connective) {

    return(RightAssociative(Connective) || LeftAssociative(Connective));
}
//-------------------------------------------------------------------------------------------------
int FullyAssociative(ConnectiveType Connective) {

    return(RightAssociative(Connective) && LeftAssociative(Connective));
}
//-------------------------------------------------------------------------------------------------
int Symmetric(ConnectiveType Connective) {

    return(FullyAssociative(Connective) || Connective == equivalence ||
Connective == nonequivalence);
}
//-------------------------------------------------------------------------------------------------
//----Unused now, for changing a right branch to a left branch
FORMULA ChangeAssociationRightToLeft(FORMULA Formula) {

    FORMULA RHS;

    if (Formula->FormulaUnion.BinaryFormula.RHS->Type == binary) {
        RHS = Formula->FormulaUnion.BinaryFormula.RHS;
        Formula->FormulaUnion.BinaryFormula.RHS = RHS->FormulaUnion.BinaryFormula.LHS;
        RHS->FormulaUnion.BinaryFormula.LHS = Formula;
        return(ChangeAssociationRightToLeft(RHS));
    } else {
        return(Formula);
    }
}
//-------------------------------------------------------------------------------------------------
//----This parses an atom, or a variable that is a formula (type $o)
FORMULA ParseAtom(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int VariablesMustBeQuantified) {

    FORMULA Formula;
    int InfixNegatedAtom;
    FORMULA InfixFormula;

    InfixNegatedAtom = 0;
    Formula = NewFormula();
    Formula->Type = atom;
    Formula->FormulaUnion.Atom = ParseTerm(Stream,Language,Context,EndOfScope,atom_as_term,none,
&InfixNegatedAtom,VariablesMustBeQuantified);
//DEBUG printf("Atom symbol is %s and the arity is %d and the args are %s and the sig has %d uses\n",GetSymbol(Formula->FormulaUnion.Atom),GetArity(Formula->FormulaUnion.Atom),GetArguments(Formula->FormulaUnion.Atom) == NULL ? "NULL" : "not NULL",Formula->FormulaUnion.Atom->TheSymbol.NonVariable->NumberOfUses);
//DEBUG printf("Parsed an atom: ");PrintTSTPTerm(stdout,Language,Formula->FormulaUnion.Atom,0,1,1);printf("\n");

//----Hack to fix negated infix equality
    if (InfixNegatedAtom) {
        InfixFormula = NewFormula();
        InfixFormula->Type = unary;
        InfixFormula->FormulaUnion.UnaryFormula.Connective = negation;
        InfixFormula->FormulaUnion.UnaryFormula.Formula = Formula;
        Formula = InfixFormula;
    }

    return(Formula);
}
//-------------------------------------------------------------------------------------------------
FORMULA ParseUnaryFormula(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int VariablesMustBeQuantified) {

    FORMULA Formula;
    ConnectiveType Connective;
    READFILE StringStream;
    
    Connective = StringToConnective(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,unary_connective);
//----See if a ), which means it was a connective term
    if (CheckToken(Stream,punctuation,")")) {
        if ((StringStream = OpenStringReadFile(ConnectiveToString(Connective))) == NULL) {
            CodingError("Could not open string stream");
            return(NULL);
        }
//TODO applied_connective
//----Unary connective as a term in THF
        Formula = ParseAtom(StringStream,Language,Context,EndOfScope,VariablesMustBeQuantified);
        CloseReadFile(StringStream);
    } else {
        Formula = NewFormula();
        Formula->Type = unary;
        Formula->FormulaUnion.UnaryFormula.Connective = Connective;
//----No binary inside unary
        Formula->FormulaUnion.UnaryFormula.Formula = ParseFormula(Stream,Language,Context,
EndOfScope,0,0,VariablesMustBeQuantified,none);
    }
    return(Formula);
}
//-------------------------------------------------------------------------------------------------
void ParseQuantifiedVariable(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,ConnectiveType Quantifier,int VariablesMustBeQuantified,
QuantifiedFormulaType * QuantifiedFormula) {

    if (QuantifiedFormula->Quantifier == existential && CheckTokenType(Stream,number)) {
        QuantifiedFormula->ExistentialCount = atoi(CurrentToken(Stream)->NameToken);
        AcceptTokenType(Stream,number);
        AcceptToken(Stream,punctuation,":");
    } else {
        QuantifiedFormula->ExistentialCount = -1;
    }

//----Get the variable. The EndOfScope is extended to include this variable.
    QuantifiedFormula->Variable = ParseTerm(Stream,Language,Context,EndOfScope,new_variable,
Quantifier,NULL,0);
//----THF requires type
    if (Language == tptp_thf ||
//----TFF optional type
((Language == tptp_tff || Language == tptp_tcf) && CheckToken(Stream,punctuation,":"))) {
        AcceptToken(Stream,punctuation,":");
        QuantifiedFormula->VariableType = ParseFormula(Stream,Language,Context,EndOfScope,-1,1,
VariablesMustBeQuantified,none);
//----If not $o it's a term variable, else a boolean variable
        QuantifiedFormula->Variable->TheSymbol.Variable->Type = 
(GetResultFromTyping(Stream,QuantifiedFormula->VariableType)->Type != atom || strcmp("$o",
GetSymbol(GetResultFromTyping(Stream,QuantifiedFormula->VariableType)->FormulaUnion.Atom))) ? 
term : formula;
    } else {
        QuantifiedFormula->VariableType = NULL;
        QuantifiedFormula->Variable->TheSymbol.Variable->Type = nonterm;
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA ParseQuantifiedRemainder(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,ConnectiveType Quantifier,int VariablesMustBeQuantified) {

    FORMULA Formula;

    if (CheckToken(Stream,punctuation,"]")) {
        AcceptToken(Stream,punctuation,"]");
        AcceptToken(Stream,punctuation,":");
//----No Binary formulae allowed (i.e., quantification binds tight). But = 
//----and != do get allowed.
        Formula = ParseFormula(Stream,Language,Context,EndOfScope,0,1,VariablesMustBeQuantified,
none);
        return(Formula);
    } else {
        AcceptToken(Stream,punctuation,",");
        Formula = NewFormula();
        Formula->Type = quantified;
        Formula->FormulaUnion.QuantifiedFormula.Quantifier = Quantifier;
        Formula->FormulaUnion.QuantifiedFormula.ExistentialCount = 0;
        ParseQuantifiedVariable(Stream,Language,Context,EndOfScope,Quantifier,
VariablesMustBeQuantified,&(Formula->FormulaUnion.QuantifiedFormula));
//----Now get the rest of the variables
        Formula->FormulaUnion.QuantifiedFormula.Formula = 
ParseQuantifiedRemainder(Stream,Language,Context,EndOfScope,Quantifier,VariablesMustBeQuantified);
        return(Formula);
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA ParseQuantifiedFormula(READFILE Stream,SyntaxType Language,
ContextType Context,VARIABLENODE * EndOfScope,int VariablesMustBeQuantified) {

    FORMULA Formula;
    VARIABLENODE OldEndOfScope;
    
    Formula = NewFormula();
    Formula->Type = quantified;
    Formula->FormulaUnion.QuantifiedFormula.Quantifier = 
StringToConnective(CurrentToken(Stream)->NameToken);
    Formula->FormulaUnion.QuantifiedFormula.ExistentialCount = 0;
    AcceptTokenType(Stream,quantifier);
    AcceptToken(Stream,punctuation,"[");
    OldEndOfScope = *EndOfScope;
    ParseQuantifiedVariable(Stream,Language,Context,EndOfScope,
Formula->FormulaUnion.QuantifiedFormula.Quantifier,VariablesMustBeQuantified,
&(Formula->FormulaUnion.QuantifiedFormula));
    Formula->FormulaUnion.QuantifiedFormula.Formula = ParseQuantifiedRemainder(
Stream,Language,Context,EndOfScope,Formula->
FormulaUnion.QuantifiedFormula.Quantifier,VariablesMustBeQuantified);
    *EndOfScope = OldEndOfScope;

    return(Formula);
}
//-------------------------------------------------------------------------------------------------
FORMULAArray DuplicateTupleFormulae(int NumberOfElements,FORMULAArray Original,
ContextType Context,int ForceNewVariables) {

    FORMULAArray Duplicate;
    
    Duplicate = (FORMULAArray)Malloc(NumberOfElements * sizeof(FORMULA));
    while (NumberOfElements > 0) {
        Duplicate[NumberOfElements-1] = DuplicateFormula(Original[NumberOfElements-1],Context,
ForceNewVariables);
    }
    return(Duplicate);
}
//-------------------------------------------------------------------------------------------------
FORMULAArray ParseTupleFormulae(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int AllowBinary,int VariablesMustBeQuantified,
ConnectiveType LastConnective,int * NumberOfElements) {

    FORMULAArray TupleFormulae;

    TupleFormulae = NULL;
    *NumberOfElements = 0;
    AcceptToken(Stream,punctuation,"[");
    if (!CheckToken(Stream,punctuation,"]")) {
        (*NumberOfElements)++;
        TupleFormulae = (FORMULAArray)Malloc(sizeof(FORMULA));
        TupleFormulae[*NumberOfElements-1] = ParseFormula(Stream,Language,Context,EndOfScope,1,1,
VariablesMustBeQuantified,none);
        while (CheckToken(Stream,punctuation,",")) {
            AcceptToken(Stream,punctuation,",");
            (*NumberOfElements)++;
            TupleFormulae = (FORMULAArray)Realloc((void *)TupleFormulae,
*NumberOfElements * sizeof(FORMULA));
            TupleFormulae[*NumberOfElements-1] = ParseFormula(Stream,Language,Context,EndOfScope,
1,1,VariablesMustBeQuantified,none);
        }
    } else {
        TupleFormulae = NULL;
    }
    AcceptToken(Stream,punctuation,"]");
    return(TupleFormulae);
}
//-------------------------------------------------------------------------------------------------
FORMULA ParseTupleOrSequentFormula(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int AllowBinary,int VariablesMustBeQuantified,
ConnectiveType LastConnective) {

    FORMULA TupleOrSequent;
    FORMULAArray FirstTuple;
    int NumberOfElements;

    EnsureToken(Stream,punctuation,"[");
    TupleOrSequent = NewFormula();
    FirstTuple = ParseTupleFormulae(Stream,Language,Context,EndOfScope,AllowBinary,
VariablesMustBeQuantified,LastConnective,&NumberOfElements);
    if (CheckToken(Stream,binary_connective,"-->")) {
        TupleOrSequent->Type = sequent;
        TupleOrSequent->FormulaUnion.SequentFormula.LHS = FirstTuple;
        TupleOrSequent->FormulaUnion.SequentFormula.NumberOfLHSElements = NumberOfElements;
        AcceptToken(Stream,binary_connective,"-->");
        TupleOrSequent->FormulaUnion.SequentFormula.RHS = ParseTupleFormulae(Stream,Language,
Context,EndOfScope,AllowBinary,VariablesMustBeQuantified,LastConnective,
&(TupleOrSequent->FormulaUnion.SequentFormula.NumberOfRHSElements));
    } else {
        TupleOrSequent->Type = tuple;
        TupleOrSequent->FormulaUnion.TupleFormula.Elements = FirstTuple;
        TupleOrSequent->FormulaUnion.TupleFormula.NumberOfElements = NumberOfElements;
    }

    return(TupleOrSequent);
}
//-------------------------------------------------------------------------------------------------
FORMULA ParseITEFormula(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int VariablesMustBeQuantified) {

    FORMULA ITEFormula;

    ITEFormula = NewFormula();
    ITEFormula->Type = ite_formula;
    
    AcceptToken(Stream,predicate_symbol,"$ite");
    AcceptToken(Stream,punctuation,"(");
    ITEFormula->FormulaUnion.ConditionalFormula.Condition = ParseFormula(Stream,Language,Context,
EndOfScope,1,1,VariablesMustBeQuantified,none);
    AcceptToken(Stream,punctuation,",");
    ITEFormula->FormulaUnion.ConditionalFormula.FormulaIfTrue = ParseFormula(Stream,Language,
Context,EndOfScope,1,1,VariablesMustBeQuantified,none);
    AcceptToken(Stream,punctuation,",");
    ITEFormula->FormulaUnion.ConditionalFormula.FormulaIfFalse = ParseFormula(Stream,Language,
Context,EndOfScope,1,1,VariablesMustBeQuantified,none);
    AcceptToken(Stream,punctuation,")");

    return(ITEFormula);
}
//-------------------------------------------------------------------------------------------------
FORMULA ParseLETFormula(READFILE Stream,SyntaxType Language,
ContextType Context,VARIABLENODE * EndOfScope,int VariablesMustBeQuantified) {

    FORMULA LETFormula;

    LETFormula = NewFormula();
    LETFormula->Type = let_formula;
    
    AcceptToken(Stream,predicate_symbol,"$let");
    AcceptToken(Stream,punctuation,"(");
//----ParseFormula accepts tuples too :-)
    LETFormula->FormulaUnion.LetFormula.LetTypes = ParseFormula(Stream,Language,Context,EndOfScope,
1,0,0,none);
    AcceptToken(Stream,punctuation,",");
    LETFormula->FormulaUnion.LetFormula.LetDefn = ParseFormula(Stream,Language,Context,EndOfScope,
1,1,0,none);
    AcceptToken(Stream,punctuation,",");
    LETFormula->FormulaUnion.LetFormula.LetBody = ParseFormula(Stream,Language,Context,EndOfScope,
1,1,VariablesMustBeQuantified,none);
    AcceptToken(Stream,punctuation,")");

    return(LETFormula);
}
//-------------------------------------------------------------------------------------------------
//----This assumes it's in the context of duplicating a formula with variables
FORMULA DuplicateFormula(FORMULA Original,ContextType Context,int ForceNewVariables) {

    FORMULA Formula;
    String ErrorMessage;
    SYMBOLNODE Symbol;

    if (Original == NULL) {
        return(NULL);
    } else {
        Formula = NewFormula();
        *Formula = *Original;

        switch (Formula->Type) {
            case sequent:
                Formula->FormulaUnion.SequentFormula.LHS = DuplicateTupleFormulae(
Original->FormulaUnion.SequentFormula.NumberOfLHSElements,
Original->FormulaUnion.SequentFormula.LHS,Context,ForceNewVariables);
                Formula->FormulaUnion.SequentFormula.RHS = DuplicateTupleFormulae(
Original->FormulaUnion.SequentFormula.NumberOfRHSElements,
Original->FormulaUnion.SequentFormula.RHS,Context,ForceNewVariables);
                break;
            case quantified:
                Formula->FormulaUnion.QuantifiedFormula.Variable = DuplicateTerm(
Original->FormulaUnion.QuantifiedFormula.Variable,Context,1);
                Formula->FormulaUnion.QuantifiedFormula.VariableType = DuplicateFormula(
Original->FormulaUnion.QuantifiedFormula.VariableType,Context,ForceNewVariables);
                Formula->FormulaUnion.QuantifiedFormula.Formula = DuplicateFormula(
Original->FormulaUnion.QuantifiedFormula.Formula,Context,ForceNewVariables);
                break;
            case assignment:
            case type_declaration:
            case binary:
                Formula->FormulaUnion.BinaryFormula.LHS = DuplicateFormula(
Original->FormulaUnion.BinaryFormula.LHS,Context,ForceNewVariables);
                if (Formula->FormulaUnion.BinaryFormula.Connective == equation) {
                    if ((Symbol = IsSymbolInSignatureList(Context.Signature->Predicates,"=",2,
NULL)) != NULL) {
                        IncreaseSymbolUseCount(Symbol,1);
                    } else {
                        CodingError("Duplicating an equation, but = not in signature");
                    }
                }
                Formula->FormulaUnion.BinaryFormula.RHS = DuplicateFormula(
Original->FormulaUnion.BinaryFormula.RHS,Context,ForceNewVariables);
                break;
            case unary:
                Formula->FormulaUnion.UnaryFormula.Formula = DuplicateFormula(
Original->FormulaUnion.UnaryFormula.Formula,Context,ForceNewVariables);
                break; 
            case atom:
            case applied_connective:
                Formula->FormulaUnion.Atom = DuplicateTerm(Original->FormulaUnion.Atom,Context,
ForceNewVariables);
                break;
            case tuple:
                Formula->FormulaUnion.TupleFormula.Elements = DuplicateTupleFormulae(
Original->FormulaUnion.TupleFormula.NumberOfElements,
Original->FormulaUnion.TupleFormula.Elements,Context,ForceNewVariables);
                break;
            case ite_formula:
                Formula->FormulaUnion.ConditionalFormula.Condition = DuplicateFormula(
Original->FormulaUnion.ConditionalFormula.Condition,Context,ForceNewVariables);
                Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue = DuplicateFormula(
Original->FormulaUnion.ConditionalFormula.FormulaIfTrue, Context,ForceNewVariables);
                Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse = DuplicateFormula(
Original->FormulaUnion.ConditionalFormula.FormulaIfFalse,Context,ForceNewVariables);
                break;
            case let_formula:
                Formula->FormulaUnion.LetFormula.LetDefn = DuplicateFormula(
Original->FormulaUnion.LetFormula.LetDefn,Context,ForceNewVariables);
                Formula->FormulaUnion.LetFormula.LetBody = DuplicateFormula(
Original->FormulaUnion.LetFormula.LetBody,Context,ForceNewVariables);
                break;
            default:
                sprintf(ErrorMessage,"Formula type %s unknown for duplication",
FormulaTypeToString(Formula->Type));
                CodingError(ErrorMessage);
                break;
        }
    }
    return(Formula);
}
//-------------------------------------------------------------------------------------------------
FORMULA ParseLowPrecedenceBinary(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int AllowBinary,int AllowInfixEquality,int VariablesMustBeQuantified,
FORMULA PossibleLHSFormula) {

    FORMULA BinaryFormula = NULL;

    if (AllowBinary && 
(CheckToken(Stream,binary_connective,":=") || CheckToken(Stream,binary_connective,"=="))) {
        BinaryFormula = NewFormula();
        BinaryFormula->Type = assignment;
        BinaryFormula->FormulaUnion.BinaryFormula.LHS = PossibleLHSFormula;
        if (CheckToken(Stream,binary_connective,":=")) {
            BinaryFormula->FormulaUnion.BinaryFormula.Connective = assignmentsym;
        } else {
            BinaryFormula->FormulaUnion.BinaryFormula.Connective = identicalsym;
        }
        AcceptTokenType(Stream,binary_connective);
//----Set the last connective to be none so that the RHS is parsed as a top level formula
        BinaryFormula->FormulaUnion.BinaryFormula.RHS =
ParseFormula(Stream,Language,Context,EndOfScope,1,1,VariablesMustBeQuantified,none);
        return(BinaryFormula);
    } else {
        return(PossibleLHSFormula);
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA ParseFormula(READFILE Stream,SyntaxType Language,ContextType Context,
VARIABLENODE * EndOfScope,int AllowBinary,int AllowInfixEquality,int VariablesMustBeQuantified,
ConnectiveType LastConnective) {

    FORMULA Formula = NULL;
    FORMULA BinaryFormula = NULL;
    FORMULA InfixFormula = NULL;
    ConnectiveType ThisConnective;
    String ErrorMessage;
    TermType NewTermType;
    SYMBOLNODE * ToDeletePtr;
    SYMBOLNODE ExistingType;
    char * LHSSymbol;
    int LHSSymbolArity;

//DEBUG printf("ParseFormula for %s, with token %s, allow binary %d, last connective %s\n",SyntaxToString(Language),CurrentToken(Stream)->NameToken,AllowBinary,ConnectiveToString(LastConnective));
    switch (CurrentToken(Stream)->KindToken) {
//----Three types of punctuation - ( for ()ed, [ for tuple, { for non-classical
        case punctuation:
            if (CheckToken(Stream,punctuation,"[")) {
                Formula = ParseTupleOrSequentFormula(Stream,Language,Context,
EndOfScope,AllowBinary,VariablesMustBeQuantified,LastConnective);
            } else if (CheckToken(Stream,punctuation,"(")) {
                if (Language == tptp_tff && LastConnective == application) {
//DEBUG printf("Parsing a ()ed atom %s\n",CurrentToken(Stream)->NameToken);
                Formula = ParseAtom(Stream,Language,Context,EndOfScope,VariablesMustBeQuantified);
//DEBUG printf("Parsed as a ()ed atom with functor %s and arity %d\n",GetSymbol(Formula->FormulaUnion.Atom),GetArity(Formula->FormulaUnion.Atom));
                } else {
                    AcceptToken(Stream,punctuation,"(");
                    Formula = ParseFormula(Stream,Language,Context,EndOfScope,1,1,
VariablesMustBeQuantified,none);
                    AcceptToken(Stream,punctuation,")");
                }
            } else if (CheckToken(Stream,punctuation,"{")) {
                AcceptToken(Stream,punctuation,"{");
                Formula = NewFormula();
                Formula->Type = applied_connective;
                Formula->FormulaUnion.Atom = ParseTerm(Stream,Language,Context,EndOfScope,
atom_as_term,none,NULL,VariablesMustBeQuantified);
                AcceptToken(Stream,punctuation,"}");
//----Ignore any last connective so that this is treated as binary when the @ comes next.
                LastConnective = none;
            }
            break;
        case quantifier:
            Formula = ParseQuantifiedFormula(Stream,Language,Context,EndOfScope,
VariablesMustBeQuantified);
            break;
//----Binary connective as a term in THF
        case binary_connective:
            Formula = NewFormula();
            Formula->Type = atom;
            Formula->FormulaUnion.Atom = ParseTerm(Stream,Language,Context,EndOfScope,atom_as_term,
none,NULL,VariablesMustBeQuantified);
            break;
        case unary_connective:
            Formula = ParseUnaryFormula(Stream,Language,Context,EndOfScope,
VariablesMustBeQuantified);
            break;
        default:
//----For THF $ite are parsed as binary formulae, because the application might be partial.
//----Luckily ListStatistics counts $ite by looking at the symbol, not the FormulaTypeType.
            if (!strcmp(CurrentToken(Stream)->NameToken,"$ite") && 
(Language == tptp_tff || Language == tptp_tcf)) {
                Formula = ParseITEFormula(Stream,Language,Context,EndOfScope,
VariablesMustBeQuantified);
            } else if (!strcmp(CurrentToken(Stream)->NameToken,"$let")) {
                Formula = ParseLETFormula(Stream,Language,Context,EndOfScope,
VariablesMustBeQuantified);
            } else {
//DEBUG printf("Parsed as an atom %s\n",CurrentToken(Stream)->NameToken);
                Formula = ParseAtom(Stream,Language,Context,EndOfScope,VariablesMustBeQuantified);
            }
            break;
    }
//DEBUG printf("Parsed formula of type %s is\n",FormulaTypeToString(Formula->Type));PrintTSTPFormula(stdout,Language,Formula,0,1,outermost,1);printf("\n");

//----Check for an equality
//DEBUG printf("check equality with token %s and allow is %d\n",CurrentToken(Stream)->NameToken,AllowInfixEquality);
    if (AllowInfixEquality && 
(Language == tptp_thf || Language == tptp_tff || Language == tptp_tcf) && 
(CheckToken(Stream,lower_word,"=") || CheckToken(Stream,lower_word,"!="))) {
        BinaryFormula = NewFormula();
        BinaryFormula->Type = binary;
        BinaryFormula->FormulaUnion.BinaryFormula.LHS = Formula;
        ThisConnective = StringToConnective(CurrentToken(Stream)->NameToken);
        BinaryFormula->FormulaUnion.BinaryFormula.Connective = ThisConnective;
        InsertIntoSignatureList(&(Context.Signature->Predicates),"=",2,-1,0,Stream);
        NextToken(Stream);
        BinaryFormula->FormulaUnion.BinaryFormula.RHS = ParseFormula(Stream,Language,
Context,EndOfScope,0,0,VariablesMustBeQuantified,ThisConnective);
//----Hack to fix negated infix equality
        if (ThisConnective == negequation) {
            InfixFormula = NewFormula();
            InfixFormula->Type = unary;
            InfixFormula->FormulaUnion.UnaryFormula.Connective = negation;
            BinaryFormula->FormulaUnion.BinaryFormula.Connective = equation;
            InfixFormula->FormulaUnion.UnaryFormula.Formula = BinaryFormula;
            BinaryFormula = InfixFormula;
        }
        Formula = BinaryFormula;
    }

//----Check for a binary formula
//DEBUG printf("check infix with token %s and allow is %d and type is %s\n",CurrentToken(Stream)->NameToken,AllowBinary,TokenTypeToString(CurrentToken(Stream)->KindToken));
    if (
//----THF and TXF allow formulae as arguments of equality and application. 
AllowBinary &&
( CheckTokenType(Stream,binary_connective) ||
//----THF and TFF have types. Should this be allowed independent of AllowBinary?
  ( ( Language == tptp_thf || Language == tptp_tff  || Language == tptp_tcf ) &&
    CheckToken(Stream,punctuation,":")
  ) ) ) {
//----Make sure it's a legitimate type declaration
        if (CheckToken(Stream,punctuation,":") && Formula->Type != atom) {
            TokenError(Stream,"Type declaration for non-atomic symbol");
            return(NULL);
        }
        ThisConnective = StringToConnective(CurrentToken(Stream)->NameToken);
//DEBUG printf("do infix because connective is %s (last was %s)\n",ConnectiveToString(ThisConnective),ConnectiveToString(LastConnective));
        if (LastConnective == none || (Associative(ThisConnective) &&
LastConnective == ThisConnective)) {
            if ((LastConnective == none && !LeftAssociative(ThisConnective)) || 
RightAssociative(ThisConnective)) {
                BinaryFormula = NewFormula();
                BinaryFormula->Type = 
(ThisConnective == assignmentsym || ThisConnective == identicalsym) ?  assignment : 
ThisConnective == typecolon ? type_declaration : binary;
                BinaryFormula->FormulaUnion.BinaryFormula.LHS = Formula;
                BinaryFormula->FormulaUnion.BinaryFormula.Connective = ThisConnective;
//----For some things set the connective to "none" because ()s are not needed.
                if (ThisConnective == subtype || ThisConnective == typecolon || 
ThisConnective == maparrow) {
                    ThisConnective = none;
                }
//----There are many different connectives here, so cannot "AcceptToken"
                NextToken(Stream);
                BinaryFormula->FormulaUnion.BinaryFormula.RHS = ParseFormula(Stream,Language,
Context,EndOfScope,AllowBinary,1,VariablesMustBeQuantified,ThisConnective);

//----If it's a type declaration, then fix the symbol to be in the right part of the signature
                if (BinaryFormula->Type == type_declaration) {
                    LHSSymbol = GetSymbol(BinaryFormula->FormulaUnion.BinaryFormula.LHS->
FormulaUnion.Atom);
                    LHSSymbolArity = GetArity(BinaryFormula->FormulaUnion.BinaryFormula.LHS->
FormulaUnion.Atom);
//----If a declaration of a type in THF or TFF, move the LHS to Types in signature
//TODO What about TH1 with constructors?
                    if (LHSSymbolArity == 0 && 
BinaryFormula->FormulaUnion.BinaryFormula.RHS->Type == atom &&
BinaryFormula->FormulaUnion.BinaryFormula.RHS->FormulaUnion.Atom->Type == a_type &&
!strcmp("$tType",GetSymbol(BinaryFormula->FormulaUnion.BinaryFormula.RHS->FormulaUnion.Atom))) {
//----No no no. Duplicate type declarations are allowed! Only one instance of the type is kept
//----in the signature. Symbols that are known to be types are detected as such up above.
//DEBUG printf("DEBUG Checking for existing type %s\n",GetSymbol(BinaryFormula->FormulaUnion.BinaryFormula.LHS->FormulaUnion.Atom));
                        if ((ExistingType = IsSymbolInSignatureList(
Context.Signature->Types,LHSSymbol,0,Stream)) == NULL) {
//DEBUG printf("DEBUG Do not have existing type %s\n",GetSymbol(BinaryFormula->FormulaUnion.BinaryFormula.LHS->FormulaUnion.Atom));
                            if (MoveSignatureNode(&(Context.Signature->Predicates),
&(Context.Signature->Types),LHSSymbol,0,Stream) == NULL) {
                                sprintf(ErrorMessage,"Could not move %s to types",LHSSymbol);
                                TokenError(Stream,ErrorMessage);
                                return(NULL);
                            }
                        } else {
//DEBUG printf("DEBUG We have existing type %s\n",GetSymbol(BinaryFormula->FormulaUnion.BinaryFormula.LHS->FormulaUnion.Atom));
                        }
//----In TFF a declared function might have been put in predicates, in both arity might be wrong
                    } else {
//----Decrement count of old version that might be in the wrong place with the wrong arity
                        IncreaseSymbolUseCount(BinaryFormula->FormulaUnion.BinaryFormula.LHS->
FormulaUnion.Atom->TheSymbol.NonVariable,-1);
                        if (BinaryFormula->FormulaUnion.BinaryFormula.LHS->
FormulaUnion.Atom->TheSymbol.NonVariable->NumberOfUses == 0) {
                            if ((ToDeletePtr = IsSymbolInSignatureListPointer(
&(Context.Signature->Functions),LHSSymbol,LHSSymbolArity,Stream)) != NULL ||
(ToDeletePtr = IsSymbolInSignatureListPointer(&(Context.Signature->Predicates),
LHSSymbol,LHSSymbolArity,Stream)) != NULL) {
                                RemoveSignatureNodeFromTree(ToDeletePtr);
                            } else {
                                sprintf(ErrorMessage,
"Could not find %s/%d in function or predicates",LHSSymbol,LHSSymbolArity);
                                CodingError(ErrorMessage);
                                return(NULL);
                            }
                        }
//----If not just $o type, then it's a function (I hope!)
//----If is known to be a function from type declaration, fix this term type
//----If type is known to be a predicate from type declaration, fix this term type and arity 
                        NewTermType = (GetResultFromTyping(Stream,BinaryFormula->
FormulaUnion.BinaryFormula.RHS)->Type != atom || strcmp("$o",GetSymbol(GetResultFromTyping(
Stream,BinaryFormula->FormulaUnion.BinaryFormula.RHS)->FormulaUnion.Atom))) ? 
function : atom_as_term;
//----Insert and assign correct version
//DEBUG printf("Fix %s to be a %s of arity %d\n",LHSSymbol,TermTypeToString(NewTermType),GetArityFromTyping(Stream,BinaryFormula->FormulaUnion.BinaryFormula.RHS));
                        BinaryFormula->FormulaUnion.BinaryFormula.LHS->FormulaUnion.Atom->
TheSymbol.NonVariable = InsertIntoSignature(Context.Signature,NewTermType,LHSSymbol,
GetArityFromTyping(Stream,BinaryFormula->FormulaUnion.BinaryFormula.RHS),-1,0,Stream);
//DEBUG printf("Fixed atom symbol is %s and the arity is %d and the args are %s\n",GetSymbol(BinaryFormula->FormulaUnion.BinaryFormula.LHS->FormulaUnion.Atom),GetArity(BinaryFormula->FormulaUnion.BinaryFormula.LHS->FormulaUnion.Atom),GetArguments(BinaryFormula->FormulaUnion.BinaryFormula.LHS->FormulaUnion.Atom) == NULL ? "NULL" : "not NULL");
                    }
                }

//----If finished a binary, still need to allow another binary of low precedence, right now 
//----that's :=
                return(ParseLowPrecedenceBinary(Stream,Language,Context,EndOfScope,1,
AllowInfixEquality,VariablesMustBeQuantified,BinaryFormula));
            } else if (LeftAssociative(ThisConnective)) {
                while (LastConnective == none || LastConnective == ThisConnective) {
                    BinaryFormula = NewFormula();
                    BinaryFormula->Type = 
(ThisConnective == assignmentsym || ThisConnective == identicalsym) ? assignment : binary;
                    BinaryFormula->FormulaUnion.BinaryFormula.LHS = Formula;
                    BinaryFormula->FormulaUnion.BinaryFormula.Connective = ThisConnective;
//----Only binary connectives are left associative, so I can "AcceptToken"
                    AcceptTokenType(Stream,binary_connective);
                    BinaryFormula->FormulaUnion.BinaryFormula.RHS = ParseFormula(Stream,Language,
Context,EndOfScope,0,1,VariablesMustBeQuantified,ThisConnective);
                    Formula = BinaryFormula;
                    LastConnective = ThisConnective;
//----If a connective atom applied to a ()ed list, save AppliedArity
                    if (Formula->FormulaUnion.BinaryFormula.LHS->Type == applied_connective &&
ThisConnective == application &&
Formula->FormulaUnion.BinaryFormula.RHS->Type == atom &&
!strcmp(GetSymbol(Formula->FormulaUnion.BinaryFormula.RHS->FormulaUnion.Atom),"()")) {
                        SetSignatureAppliedArity(
Formula->FormulaUnion.BinaryFormula.LHS->FormulaUnion.Atom->TheSymbol.NonVariable,
GetArity(Formula->FormulaUnion.BinaryFormula.RHS->FormulaUnion.Atom));
                    }
//----Check if we should continue a stream of binary. If a binary connective then keep it and the 
//----while loop will check, else nope.
                    if (CheckTokenType(Stream,binary_connective)) {
                        ThisConnective = StringToConnective(CurrentToken(Stream)->NameToken);
                    } else {
                        ThisConnective = none;
                    }
                }
//----If finished a binary, still need to allow another binary of low precedence, right now 
//----that's :=
                return(ParseLowPrecedenceBinary(Stream,Language,Context,EndOfScope,1,
AllowInfixEquality,VariablesMustBeQuantified,BinaryFormula));
            } else if (LastConnective != none) {
                CodingError("Association neither left nor right");
                return(NULL);
            } else {
                CodingError("Should never get here in ParseFormula");
                return(NULL);
            }
        } else {
            TokenError(Stream,"Binary with ambiguous associativity");
            return(NULL);
        }
    } else {
//DEBUG printf("Not binary, the next token is %s\n",CurrentToken(Stream)->NameToken);
        return(Formula);
    }
}
//-------------------------------------------------------------------------------------------------
FORMULAWITHVARIABLES DuplicateFormulaWithVariables(FORMULAWITHVARIABLES Original,
SIGNATURE Signature,int ForceNewVariables) {

    ContextType Context;
    FORMULAWITHVARIABLES FormulaWithVariables;
    
    FormulaWithVariables = NewFormulaWithVariables();

//----Copy the variables list, setting each use to 0, and setting the
//----instantiation to point to the original (cheating in duplication :-)
    FormulaWithVariables->Variables = ParallelCopyVariableList(Original->Variables);
    
//----Create a context for the parsing
    Context.Variables = &(FormulaWithVariables->Variables);
    Context.Signature = Signature;
    
//DEBUG printf("original variables\n");
//DEBUG PrintVariableList(Original->Variables,NULL);
//DEBUG printf("parallel copy variables\n");
//DEBUG PrintVariableList(FormulaWithVariables->Variables,NULL);
    FormulaWithVariables->Formula = DuplicateFormula(Original->Formula,Context,ForceNewVariables);
//DEBUG printf("after copy variables\n");
//DEBUG PrintVariableList(FormulaWithVariables->Variables,NULL);

//----Set the variable instantiations to their rightful values
    ParallelCopyVariableInstantiations(Original->Variables,
FormulaWithVariables->Variables);

    return(FormulaWithVariables); 
}
//-------------------------------------------------------------------------------------------------
FORMULA DuplicateInternalFormulaWithVariables(FORMULA Original,ContextType OriginalContext) {

    FORMULAWITHVARIABLES LocalFormulaWithVariables;
    FORMULAWITHVARIABLES CopiedFormulaWithVariables;
    VARIABLENODE * VariableNodePP;
    VARIABLENODE VariableNode;
    FORMULA Copy;

//----Make a local formula with variables to copy
    LocalFormulaWithVariables = NewFormulaWithVariables();
    LocalFormulaWithVariables->Variables = *(OriginalContext.Variables);
    LocalFormulaWithVariables->Formula = Original;

//----Copy it
    CopiedFormulaWithVariables = DuplicateFormulaWithVariables(
LocalFormulaWithVariables,OriginalContext.Signature,0);

//----Remove unused variables in copy
    VariableNodePP = &(CopiedFormulaWithVariables->Variables);
    while (*VariableNodePP != NULL) {
        if ((*VariableNodePP)->NumberOfUses == 0) {
            VariableNode = *VariableNodePP;
            *VariableNodePP = VariableNode->NextVariable;
            Free((void **)&VariableNode);
        } else {
            VariableNodePP = &((*VariableNodePP)->NextVariable);
        }
    }

//----Add into original variables
    *VariableNodePP = *(OriginalContext.Variables);
    *(OriginalContext.Variables) = CopiedFormulaWithVariables->Variables;

//----Discard the local formula with variables
    Copy = CopiedFormulaWithVariables->Formula;
    Free((void **)&CopiedFormulaWithVariables);

    return(Copy);
}
//-------------------------------------------------------------------------------------------------
FORMULAWITHVARIABLES ParseFormulaWithVariables(READFILE Stream,SyntaxType Language,
SIGNATURE Signature,int VariablesMustBeQuantified) {

    ContextType Context;
    FORMULAWITHVARIABLES FormulaWithVariables;
    VARIABLENODE EndOfScope;
    int NeedNonLogicTokens;

    EndOfScope = NULL;
    FormulaWithVariables = NewFormulaWithVariables();

//----Create a context for the parsing
    Context.Variables = &(FormulaWithVariables->Variables);
    Context.Signature = Signature;

    NeedNonLogicTokens = Stream->NeedNonLogicTokens;
    Stream->NeedNonLogicTokens = 0;
    FormulaWithVariables->Formula = ParseFormula(Stream,Language,Context,&EndOfScope,1,1,
VariablesMustBeQuantified,none);
    Stream->NeedNonLogicTokens = NeedNonLogicTokens;
    return(FormulaWithVariables);
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA ParseInclude(READFILE Stream,SIGNATURE Signature) {

    ContextType Context;
    ANNOTATEDFORMULA AnnotatedFormula;
    int Arity;

    AnnotatedFormula = NewAnnotatedFormula(include);
    Context.Variables = NULL;
    Context.Signature = Signature;
    AnnotatedFormula->AnnotatedFormulaUnion.Include = ParseTerm(Stream,nontype,Context,NULL,
non_logical_data,none,NULL,0);
    TakeToken(Stream,punctuation,".");

//----Check it looks like an include
    if (strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.Include),"include") || 
(((Arity = GetArity(AnnotatedFormula-> AnnotatedFormulaUnion.Include)) != 1) && Arity != 2) || 
(Arity == 1 && GetArity(AnnotatedFormula->AnnotatedFormulaUnion.Include->Arguments[0]) != 0) ||
(Arity == 2 && strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.Include->Arguments[1]),
"[]"))) {
        TokenError(Stream,"Ill-formed include directive");
    }

    return(AnnotatedFormula);
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA ParseComment(READFILE Stream) {

    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = NewAnnotatedFormula(comment);
    AnnotatedFormula->AnnotatedFormulaUnion.Comment = CopyHeapString(
CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,comment_token);

    return(AnnotatedFormula);
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA ParseBlankLine(READFILE Stream) {

    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = NewAnnotatedFormula(blank_line);
    AcceptTokenType(Stream,blank_line_token);

    return(AnnotatedFormula);
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA DuplicateAnnotatedFormula(ANNOTATEDFORMULA Original,SIGNATURE Signature) {

    switch (Original->Syntax) {
        case include:
        case blank_line:
        case comment:
            CodingError("Includes, blank lines, and comments cannot be duplicated\n");
            break;
//----For CNF the variables are implicitly universally quantified, and must
//----be new variables. For FOF we use the originals (can't recall why)
        case tptp_thf:
        case tptp_tff:
        case tptp_fof:
            return(DuplicateAnnotatedTSTPFormula(Original,Signature,0));
            break;
        case tptp_tcf:
        case tptp_cnf:
            return(DuplicateAnnotatedTSTPFormula(Original,Signature,1));
            break;
        default:
            CodingError("Annotated formula syntax unknown for duplicating");
            break;
    }
    return(NULL);
}
//-------------------------------------------------------------------------------------------------
void FreeAnnotatedFormula(ANNOTATEDFORMULA * AnnotatedFormula,SIGNATURE Signature) {

    if (*AnnotatedFormula != NULL) {
        if (--((*AnnotatedFormula)->NumberOfUses) == 0) {
            switch ((*AnnotatedFormula)->Syntax) {
                case include:
                    FreeTerm(&((*AnnotatedFormula)->AnnotatedFormulaUnion.Include),Signature,NULL);
                    Free((void **)AnnotatedFormula);
                    break;
                case comment:
                    Free((void **)&((*AnnotatedFormula)->AnnotatedFormulaUnion.Comment));
                    Free((void **)AnnotatedFormula);
                    break;
                case blank_line:
                    Free((void **)AnnotatedFormula);
                    break;
                case tptp_tpi:
                case tptp_thf:
                case tptp_tff:
                case tptp_tcf:
                case tptp_fof:
                case tptp_cnf:
                    FreeAnnotatedTSTPFormula(AnnotatedFormula,Signature);
                    break;
                default:
                    CodingError("Annotated formula syntax unknown for freeing\n");
                    break;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA ParseAnnotatedFormula(READFILE Stream,SIGNATURE Signature) {

    int NeedNonLogicTokens;
    ANNOTATEDFORMULA AnnotatedFormula;

    NeedNonLogicTokens = Stream->NeedNonLogicTokens;

    if (CheckToken(Stream,lower_word,"input_formula")) {
        Stream->NeedNonLogicTokens = 0;
        AnnotatedFormula = ParseAnnotatedTPTPFormula(Stream,Signature);
    } else if (CheckToken(Stream,lower_word,"input_clause")) {
        Stream->NeedNonLogicTokens = 0;
        AnnotatedFormula = ParseAnnotatedTPTPClause(Stream,Signature);
    } else if (CheckToken(Stream,lower_word,"include")) {
        Stream->NeedNonLogicTokens = 0;
        AnnotatedFormula = ParseInclude(Stream,Signature);
    } else if (CheckTokenType(Stream,comment_token)) {
        AnnotatedFormula = ParseComment(Stream);
    } else if (CheckTokenType(Stream,blank_line_token)) {
        AnnotatedFormula = ParseBlankLine(Stream);
    } else {
        Stream->NeedNonLogicTokens = 0;
        AnnotatedFormula = ParseAnnotatedTSTPFormula(Stream,Signature);
    }

    Stream->NeedNonLogicTokens = NeedNonLogicTokens;
    return(AnnotatedFormula);
}
//-------------------------------------------------------------------------------------------------
//----Use this entry point if you want the count updated
ANNOTATEDFORMULA ParseAndUseAnnotatedFormula(READFILE Stream,SIGNATURE Signature) {

    ANNOTATEDFORMULA AnnotatedFormula;

    if ((AnnotatedFormula = ParseAnnotatedFormula(Stream,Signature)) != NULL) {
        AnnotatedFormula->NumberOfUses++;
    }

    return(AnnotatedFormula);
}
//-------------------------------------------------------------------------------------------------
void GetIncludeParts(ANNOTATEDFORMULA AnnotatedFormula,String IncludeFile,
SuperString IncludeFilter) {

    int Index;

    strcpy(IncludeFile,GetSymbol(
AnnotatedFormula->AnnotatedFormulaUnion.Include->Arguments[0]));
    if (GetArity(AnnotatedFormula->AnnotatedFormulaUnion.Include) > 1) {
        if (!strcmp(GetSymbol(
AnnotatedFormula->AnnotatedFormulaUnion.Include->Arguments[1]),"all")) {
            strcpy(IncludeFilter,"all");
        } else {
            if (GetSymbol(
AnnotatedFormula->AnnotatedFormulaUnion.Include->Arguments[1])[0] == '[') {
                strcpy(IncludeFilter,"");
                for (Index = 0; Index < GetArity(
AnnotatedFormula->AnnotatedFormulaUnion.Include->Arguments[1]);Index++) {
                    strcat(IncludeFilter,GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.Include->Arguments[1]->Arguments[Index]));
                    strcat(IncludeFilter,"\n");
                }
            } else {
                ReportError("SyntaxError","Include directive is malformed",1);
            }
        }
    } else {
        strcpy(IncludeFilter,"all");
    }
//DEBUG printf("==%s==%s==\n",IncludeFile,IncludeFilter);
}
//-------------------------------------------------------------------------------------------------
LISTNODE GetIncludedAnnotatedFormulae(READFILE Stream,SIGNATURE Signature,int ExpandIncludes,
ANNOTATEDFORMULA AnnotatedFormula) {

    String IncludeFile;
    SuperString IncludeFilter;
    LISTNODE IncludedHead;
    LISTNODE HeaderNode;
    String ErrorMessage;

    GetIncludeParts(AnnotatedFormula,IncludeFile,IncludeFilter);
//DEBUG printf("Have to include %s filtered by %s\n",IncludeFile,IncludeFilter);
    if ((IncludedHead = ParseFileOfFormulae(IncludeFile,Stream->FileName,
Signature,ExpandIncludes,IncludeFilter)) == NULL) {
        sprintf(ErrorMessage,"Could not include %s",IncludeFile);
        ReportError("InputError",ErrorMessage,0);
    } else {
//DEBUG printf("===%s===\n",IncludeFile);
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,IncludedHead,1,1);
//DEBUG printf("-------------\n");

//----Remove included header
        if (IncludedHead->Next != NULL &&
IncludedHead->Next->AnnotatedFormula->Syntax == comment &&
strstr(IncludedHead->Next->AnnotatedFormula->AnnotatedFormulaUnion.Comment,
"% File     :") == IncludedHead->Next->AnnotatedFormula->
AnnotatedFormulaUnion.Comment) {
            do {
                HeaderNode = IncludedHead;
                IncludedHead = IncludedHead->Next;
                FreeAnnotatedFormula(&(HeaderNode->AnnotatedFormula),Signature);
                Free((void **)&HeaderNode);
            } while (IncludedHead != NULL &&
!(IncludedHead->AnnotatedFormula->Syntax == comment &&
strstr(IncludedHead->AnnotatedFormula->AnnotatedFormulaUnion.Comment,
"%------------------------------------------------------") ==
IncludedHead->AnnotatedFormula->AnnotatedFormulaUnion.Comment));
        }
    }
    return(IncludedHead);
}
//-------------------------------------------------------------------------------------------------
LISTNODE ParseREADFILEOfHeader(READFILE Stream) {

    SIGNATURE Signature;
    int HeaderFound;
    int HeaderMissing;
    ANNOTATEDFORMULA AnnotatedFormula;
    LISTNODE Head;
    LISTNODE * Current;

    Signature = NewSignature();
    Head = NULL;
    Current = &Head;
    HeaderFound = 0;
    HeaderMissing = 0;

//----Look for start of header
    while (!HeaderFound && !HeaderMissing && !CheckTokenType(Stream,endeof)) {
        AnnotatedFormula = ParseAndUseAnnotatedFormula(Stream,Signature);
        if (GetSyntax(AnnotatedFormula) == comment &&
strstr(AnnotatedFormula->AnnotatedFormulaUnion.Comment,"% File ") != NULL) {
            HeaderFound = 1;
        } else {
            if (GetSyntax(AnnotatedFormula) != comment) {
                HeaderMissing = 1;
            }
            FreeAnnotatedFormula(&AnnotatedFormula,Signature);
        } 
    }
    while (HeaderFound && !HeaderMissing && !CheckTokenType(Stream,endeof)) {
        AddListNode(Current,NULL,AnnotatedFormula);
        Current = &((*Current)->Next);
        AnnotatedFormula = ParseAndUseAnnotatedFormula(Stream,Signature);
        if (GetSyntax(AnnotatedFormula) == blank_line) {
//----Blank lines are OK
        } else if (GetSyntax(AnnotatedFormula) == comment) {
            if (strstr(AnnotatedFormula->AnnotatedFormulaUnion.Comment,"%--------") != NULL) {
                HeaderFound = 0;
                FreeAnnotatedFormula(&AnnotatedFormula,Signature);
            }
        } else {
            HeaderMissing = 1;
            FreeAnnotatedFormula(&AnnotatedFormula,Signature);
        }
    }


//----Delete if still in header
    if (HeaderMissing) {
        FreeListOfAnnotatedFormulae(&Head,Signature);
    } 
    FreeSignature(&Signature);
    return(Head);
}
//-------------------------------------------------------------------------------------------------
LISTNODE ParseREADFILEOfFormulae(READFILE Stream,SIGNATURE Signature,int ExpandIncludes,
char * NameFilter) {

    ANNOTATEDFORMULA AnnotatedFormula;
    LISTNODE Head;
    String FormulaName;
    String IncludedNames;
    LISTNODE IncludedHead,Mover;
    LISTNODE * Current;
    String ErrorMessage;

    Head = NULL;
    Current = &Head;
    while (!CheckTokenType(Stream,endeof)) {
        AnnotatedFormula = ParseAnnotatedFormula(Stream,Signature);
//----Expand includes if required
        if (ExpandIncludes && GetSyntax(AnnotatedFormula) == include) {
            IncludedHead = GetIncludedAnnotatedFormulae(Stream,Signature,ExpandIncludes,
AnnotatedFormula);
//DEBUG printf("---- READ INCLUDE ---------\n");
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,Signature,IncludedHead,1,1);
//DEBUG printf("-------------\n");
//----Link in and move down to the end
            if (IncludedHead != NULL) {
                (*Current) = IncludedHead;
                do {
                    Current = &((*Current)->Next);
                } while (*Current != NULL);
            }
//----Fake that it was used so it gets freed
            AnnotatedFormula->NumberOfUses++;
            FreeAnnotatedFormula(&AnnotatedFormula,Signature);
        } else {
//----The usage count for the AnnotatedFormula is incremented in the addition
//----of a list node
            AddListNode(Current,NULL,AnnotatedFormula);
            Current = &((*Current)->Next);
        }
    }

//----Filter formulae by name - only makes sense if includes have been expanded
//----and you are not requesting all
    if (ExpandIncludes && NameFilter != NULL && strcmp(NameFilter,"all")) {
        strcpy(IncludedNames,"");
        Current = &Head;
        while ((*Current) != NULL) {
            if (ReallyAnAnnotatedFormula((*Current)->AnnotatedFormula)) {
                GetName((*Current)->AnnotatedFormula,FormulaName);
//----If the name is in the list, delete it from the list and move on
                if (NameInList(FormulaName,IncludedNames)) {
                    sprintf(ErrorMessage,"Ambiguous include selection - %s",
FormulaName);
                    ReportError("InputError",ErrorMessage,0);
                } 
                if (RemoveNameFromList(FormulaName,NameFilter)) {
                    Current = &((*Current)->Next);
                    strcat(IncludedNames,FormulaName);
                    strcat(IncludedNames,"\n");
                } else {
                    Mover = (*Current)->Next;
                    FreeAnnotatedFormula(&((*Current)->AnnotatedFormula),Signature);
                    Free((void **)Current);
                    *Current = Mover;
                }
            } else {
                Current = &((*Current)->Next);
            }
        }
//----Make sure all have been found
        if (strcmp(NameFilter,"")) {
            sprintf(ErrorMessage,"Could not find %s",NameFilter);
            ReportError("InputError",ErrorMessage,0);
        }
    }

    return(Head);
}
//-------------------------------------------------------------------------------------------------
LISTNODE ParseFILEOfHeader(char * FileName,FILE * FileStream) {

    READFILE Stream; 
    LISTNODE Head;

    if ((Stream = OpenFILEReadFile(FileName,FileStream)) == NULL) {
        return(NULL);
    }

    Head = ParseREADFILEOfHeader(Stream);
    CloseReadFile(Stream);

    return(Head);
}
//-------------------------------------------------------------------------------------------------
LISTNODE ParseFILEOfFormulae(char * FileName,FILE * FileStream,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter) {

    READFILE Stream; 
    LISTNODE Head;

    if ((Stream = OpenFILEReadFile(FileName,FileStream)) == NULL) {
        return(NULL);
    }

    Head = ParseREADFILEOfFormulae(Stream,Signature,ExpandIncludes,NameFilter);
    CloseReadFile(Stream);

    return(Head);
}
//-------------------------------------------------------------------------------------------------
LISTNODE ParseFileOfHeader(char * FileName) {

    READFILE Stream; 
    LISTNODE Head;

    if ((Stream = OpenReadFile(FileName,NULL)) == NULL) {
        return(NULL);
    }

    Head = ParseREADFILEOfHeader(Stream);
    CloseReadFile(Stream);

    return(Head);
}
//-------------------------------------------------------------------------------------------------
//----Send NULL as the CurrentFileName when starting. It's used for resolving
//----includes. Send NULL as the NameFilter if no filtering required.
LISTNODE ParseFileOfFormulae(char * FileName,char * CurrentFileName,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter) {

    READFILE Stream; 
    LISTNODE Head;

    if ((Stream = OpenReadFile(FileName,CurrentFileName)) == NULL) {
        return(NULL);
    }

    Head = ParseREADFILEOfFormulae(Stream,Signature,ExpandIncludes,NameFilter);
    CloseReadFile(Stream);

    return(Head);
}
//-------------------------------------------------------------------------------------------------
LISTNODE ParseStringOfFormulae(char * Content,SIGNATURE Signature,int ExpandIncludes,
char * NameFilter) {

    READFILE Stream;
    LISTNODE Head;
    
    if ((Stream = OpenStringReadFile(Content)) == NULL) {
        return(NULL);
    }
    
    Head = ParseREADFILEOfFormulae(Stream,Signature,ExpandIncludes,NameFilter);
    CloseReadFile(Stream);
    
    return(Head);

}
//-------------------------------------------------------------------------------------------------
TERM ParseStringTerm(char * Content,SyntaxType Language,SIGNATURE Signature,
int VariablesMustBeQuantified) {

    READFILE Stream;
    ContextType Context;
    TERM Term;

    if ((Stream = OpenStringReadFile(Content)) == NULL) {
        return(NULL);
    }

//----Create a context for the parsing. No variable in non-logical data
    Context.Variables = NULL;
    Context.Signature = Signature;
    Term = ParseTerm(Stream,Language,Context,NULL,non_logical_data,none,NULL,
VariablesMustBeQuantified);
    CloseReadFile(Stream);

    return(Term);
}
//-------------------------------------------------------------------------------------------------
int ParseFileForSZSResults(char * FileName,SZSResultType * SZSResult,SZSOutputType * SZSOutput) {

    SIGNATURE Signature;
    LISTNODE Head,MovingHead;
    char * Comment;
    char * SZSComment;
    int Index;
    String FileNameCopy;

    Signature = NewSignatureWithTypes();
    SetNeedForNonLogicTokens(1);
    SetAllowFreeVariables(1);
    *SZSResult = nonszsresult;
    *SZSOutput = nonszsoutput;
    if ((Head = ParseFileOfFormulae(FileName,NULL,Signature,1,NULL)) != NULL) {
        RemovedUnusedSymbols(Signature);
        MovingHead = Head;
        while (MovingHead != NULL && (*SZSResult == nonszsresult || *SZSOutput == nonszsoutput)) {
            if (MovingHead->AnnotatedFormula->Syntax == comment) {
                Comment = MovingHead->AnnotatedFormula->AnnotatedFormulaUnion.Comment;
                if (*SZSResult == nonszsresult && 
(SZSComment = strstr(Comment,"SZS status ")) != NULL &&
strlen(SZSComment) > strlen("SZS status ")) {
                    SZSComment += + strlen("SZS status ");
                    Index = 0;
                    while (Index < strlen(SZSComment) && isalpha(SZSComment[Index])) {
                        Index++;
                    }
                    SZSComment[Index] = '\0';
                    if (StringIsASZSResult(SZSComment)) {
                        *SZSResult = StringToSZSResult(SZSComment);
                    }
                } else if (*SZSOutput == nonszsoutput &&
(SZSComment = strstr(Comment,"SZS output end ")) != NULL &&
strlen(SZSComment) > strlen("SZS output end ")) {
                    SZSComment += + strlen("SZS output end ");
                    Index = 0;
                    while (Index < strlen(SZSComment) && isalpha(SZSComment[Index])) {
                        Index++;
                    }
                    SZSComment[Index] = '\0';
                    if (StringIsASZSOutput(SZSComment)) {
                        *SZSOutput = StringToSZSOutput(SZSComment);
                    }
                }
            }
            MovingHead = MovingHead->Next;
        }
    }
    FreeListOfAnnotatedFormulae(&Head,Signature);
    FreeSignature(&Signature);
//----Look at solution file name if could not find in output
    if (*SZSResult == nonszsresult || *SZSOutput == nonszsoutput) {
        strcpy(FileNameCopy,FileName);
//----Looking for .CSA-Sat.s style name
        if (strlen(FileNameCopy) > 10 && 
FileNameCopy[strlen(FileNameCopy) - 10] == '.' &&
FileNameCopy[strlen(FileNameCopy) - 6] == '-' &&
!strcmp(FileNameCopy + strlen(FileNameCopy) - 2,".s")) {  
            FileNameCopy[strlen(FileNameCopy) - 2] = '\0';
            if (StringIsASZSOutputTLA(FileNameCopy + strlen(FileNameCopy) - 3)) {
                if (*SZSOutput == nonszsoutput) {
                    *SZSOutput = StringToSZSOutput(FileNameCopy + strlen(FileNameCopy) - 3);
                }
                FileNameCopy[strlen(FileNameCopy) - 4] = '\0';
                if (StringIsASZSResultTLA(FileNameCopy + strlen(FileNameCopy) - 3)) {
                    if (*SZSResult == nonszsresult) {
                        *SZSResult = StringToSZSResult(FileNameCopy + strlen(FileNameCopy) - 3);
                    }
                }
            }
        }
    }
    return(*SZSResult != nonszsresult && *SZSOutput != nonszsoutput);
}
//-------------------------------------------------------------------------------------------------

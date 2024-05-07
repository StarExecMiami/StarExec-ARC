#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Parsing.h"
#include "Tokenizer.h"
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Examine.h"
#include "ParseTSTP.h"
#include "ParseTPTP.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
TERM DuplicateTerm(TERM Original,ContextType Context,int ForceNewVariables);
TERM ParseTerm(READFILE Stream,ContextType Context,VARIABLENODE * EndOfScope,
TermType Type,ConnectiveType Quantification,int * InfixNegatedAtom);
FORMULA ParseFormula(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope,int AllowBinary);
//-----------------------------------------------------------------------------
void IncreaseVariableUseCount(VARIABLENODE Variable,int HowMuch) {

    Variable->NumberOfUses += HowMuch;
    IncreaseSymbolUseCount(Variable->VariableName,HowMuch);
}
//-----------------------------------------------------------------------------
//----Need the last with this name in list up to end of scope. Last to get
//----smallest scope
VARIABLENODE IsVariableInList(VARIABLENODE List,VARIABLENODE EndOfScope,
char * Name) {

    VARIABLENODE NodeFound;

    NodeFound = NULL;
    while (List != NULL) {
//----If found then woohoo
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
//-----------------------------------------------------------------------------
void PrintVariableList(VARIABLENODE Variables) {

    printf("Formula variables: ");
    while (Variables != NULL) {
        printf("%s/%d(%d)@%p ",GetSignatureSymbol(Variables->VariableName),
GetSignatureArity(Variables->VariableName),Variables->NumberOfUses,Variables);
        Variables = Variables->NextVariable;
    }
    printf("\n");
}
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
void RemoveVariable(VARIABLENODE * Variables,VARIABLENODE * Variable) {

//----Variables points to the pointer to the first element of the list of
//----variable node. Variable points to the pointer to the one to remove.
//----Search down the list.
    while (*Variables != NULL && *Variables != *Variable) {
        Variables = &((*Variables)->NextVariable);
    }

    if (*Variables == NULL) {
        printf("ERROR: Tried to remove a non-existant variable\n");
        exit(-1);
    }

//----Bypass in the list
    *Variables = (*Variables)->NextVariable;
//----Remove the list element
    Free((void **)Variable);
}
//-----------------------------------------------------------------------------
VARIABLENODE InsertVariable(SIGNATURE Signature,VARIABLENODE * Variables,
VARIABLENODE * EndOfScope,int ForceNew,char * VariableName,
ConnectiveType Quantification) {

    VARIABLENODE Variable;

//DEBUG printf("Variable %s with forced = %d\n",VariableName,ForceNew);

//----Check if variable exists in the current scope
    if (!ForceNew && (Variable = IsVariableInList(*Variables,*EndOfScope,
VariableName)) != NULL) {
//DEBUG printf("Found variable %s  in the signature\n",VariableName);
        IncreaseVariableUseCount(Variable,1);
    } else {

//----Add after end of scope
        Variable = NewVariable();
        Variable->NumberOfUses = 1;
        Variable->Quantification = Quantification;
        Variable->Instantiation = NULL;
        Variable->VariableName = InsertIntoSignature(Signature,variable,
VariableName,0);

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
//DEBUG PrintVariableList(*Variables);
    return(Variable);
}
//-----------------------------------------------------------------------------
TERM NewTerm(void) {

    TERM Term;

    Term = (TERM)Malloc(sizeof(TermNodeType));
    Term->Type = nonterm;
    Term->FlexibleArity = -1;
    Term->TheSymbol.Variable = NULL;
    Term->Arguments = NULL;

    return(Term);
}
//-----------------------------------------------------------------------------
void FreeTerm(TERM * Term,VARIABLENODE * Variables) {

    int ArgumentIndex;

    if ((*Term) != NULL) {
        if ((*Term)->Type == variable) {
            (*Term)->TheSymbol.Variable->VariableName->NumberOfUses--;
            (*Term)->TheSymbol.Variable->NumberOfUses--;
            if ((*Term)->TheSymbol.Variable->NumberOfUses == 0) {
                RemoveVariable(Variables,&((*Term)->TheSymbol.Variable));
                assert((*Term)->TheSymbol.Variable == NULL);
            }
        } else {
            for (ArgumentIndex=0;
ArgumentIndex<(*Term)->TheSymbol.NonVariable->Arity;ArgumentIndex++) {
                FreeTerm(&((*Term)->Arguments[ArgumentIndex]),Variables);
                assert((*Term)->Arguments[ArgumentIndex] == NULL);
            }
            if ((*Term)->TheSymbol.NonVariable->Arity > 0) {
                Free((void **)&((*Term)->Arguments));
            }
            (*Term)->TheSymbol.NonVariable->NumberOfUses--;
        }
        Free((void **)Term);
    }
}
//-----------------------------------------------------------------------------
FORMULA NewFormula(void) {

    FORMULA Formula;

    Formula = (FORMULA)Malloc(sizeof(FormulaType));
    Formula->Type = nonformulatype;

    return(Formula);
}
//-----------------------------------------------------------------------------
void FreeFormula(FORMULA * Formula,VARIABLENODE * Variables) {

    if (*Formula != NULL) {
        switch ((*Formula)->Type) {
            case quantified:
                FreeTerm(&((*Formula)->FormulaUnion.QuantifiedFormula.Variable),
Variables);
                assert((*Formula)->FormulaUnion.QuantifiedFormula.Variable == 
NULL);
                FreeFormula(&((*Formula)->
FormulaUnion.QuantifiedFormula.Formula),Variables);
                assert((*Formula)->FormulaUnion.QuantifiedFormula.Formula == 
NULL);
                break;
            case binary:
                FreeFormula(&((*Formula)->FormulaUnion.BinaryFormula.LHS),
Variables);
                assert((*Formula)->FormulaUnion.BinaryFormula.LHS == NULL);
                FreeFormula(&((*Formula)->FormulaUnion.BinaryFormula.RHS),
Variables);
                assert((*Formula)->FormulaUnion.BinaryFormula.RHS == NULL);
                break;
            case unary:
                FreeFormula(&((*Formula)->FormulaUnion.UnaryFormula.Formula),
Variables);
                assert((*Formula)->FormulaUnion.UnaryFormula.Formula == NULL);
                break; 
            case atom:
                FreeTerm(&((*Formula)->FormulaUnion.Atom),Variables);
                assert((*Formula)->FormulaUnion.Atom == NULL);
                break;
            default:
                printf("ERROR: Formula type unknown for freeing\n");
                exit(EXIT_FAILURE);
                break;
        }
        Free((void **)Formula);
    }
}
//-----------------------------------------------------------------------------
FORMULAWITHVARIABLES NewFormulaWithVariables(void) {

    FORMULAWITHVARIABLES FormulaWithVariables;

    FormulaWithVariables = 
(FORMULAWITHVARIABLES)Malloc(sizeof(FormulaWithVariablesType));
    FormulaWithVariables->Formula = NULL;
    FormulaWithVariables->Variables = NULL;

    return(FormulaWithVariables);
}
//-----------------------------------------------------------------------------
void FreeFormulaWithVariables(FORMULAWITHVARIABLES * FormulaWithVariables) {

    if (*FormulaWithVariables != NULL) {
        FreeFormula(&((*FormulaWithVariables)->Formula),
&((*FormulaWithVariables)->Variables));
        assert((*FormulaWithVariables)->Formula == NULL);
        assert((*FormulaWithVariables)->Variables == NULL);
        Free((void **)FormulaWithVariables);
    }
}
//-----------------------------------------------------------------------------
TERMArray NewArguments(int NumberOfArguments) {

    TERMArray Arguments;
    int Index;

    Arguments = (TERMArray)Malloc(NumberOfArguments * sizeof(TERM));
    for (Index = 0; Index < NumberOfArguments; Index++) {
        Arguments[Index] = NULL;
    }

    return(Arguments);
}
//-----------------------------------------------------------------------------
TERMArray DuplicateArguments(TERMArray Original,ContextType Context,int Arity,
int ForceNewVariables) {

    TERMArray Arguments;
    int ArgumentNumber;

    if (Arity > 0) {
        Arguments = NewArguments(Arity);
        for (ArgumentNumber=0;ArgumentNumber<Arity;ArgumentNumber++) {
            Arguments[ArgumentNumber] = DuplicateTerm(Original[ArgumentNumber],
Context,ForceNewVariables);
        }
        return(Arguments);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
TERMArray ParseArguments(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope,int * Arity,TermType Type,char * MatchingBracket) {

    TERMArray Arguments;

    if (CheckToken(Stream,punctuation,MatchingBracket)) {
        Arguments = (TERMArray)NULL;
        *Arity = 0;
    } else {
        Arguments = (TERMArray)Malloc(sizeof(TERM));
        *Arity = 1;
//----If parsing non-logical, keep it like that, else it must be a term
        if (Type != non_logical_data) {
            Type = term;
        }
        Arguments[0] = ParseTerm(Stream,Context,EndOfScope,Type,free_variable,
NULL);
        while (CheckToken(Stream,punctuation,",")) {
//DEBUG printf("and another argument\n");
            AcceptToken(Stream,punctuation,",");
            (*Arity)++;
            Arguments = (TERMArray)Realloc((void *)Arguments,
*Arity * sizeof(TERM));
            Arguments[*Arity - 1] = ParseTerm(Stream,Context,EndOfScope,Type,
free_variable,NULL);
        }
    }

    return(Arguments);
}
//-----------------------------------------------------------------------------
//----This assumes it's in the context of duplicating a formula with variables
TERM DuplicateTerm(TERM Original,ContextType Context,int ForceNewVariables) {

    TERM Term;
    int NumberOfArguments;
    VARIABLENODE Variable;

    if (Original == NULL) {
        return(NULL);
    } else {
        Term = NewTerm();
        *Term = *Original;

        if (Term->Type == variable) {
//----Look for the corresponding variable in the new variables list
            Variable = *(Context.Variables);
            while (Variable != NULL && Variable->Instantiation !=
(TERM)Original->TheSymbol.Variable) {
                Variable = Variable->NextVariable;
            }
            if (Variable == NULL) {
                CodingError("Cannot find variable for copy of original");
            }
//----Check if it has been quantified, if not use original unless new is
//----forced
            if (Variable->NumberOfUses > 0 || ForceNewVariables) {
                Term->TheSymbol.Variable = Variable;
            } else {
//----Use of the original is for the case of duplication of subformulae
//----within a formula.
                Term->TheSymbol.Variable = Original->TheSymbol.Variable;
            }
            IncreaseVariableUseCount(Term->TheSymbol.Variable,1);
        } else {
            Term->TheSymbol.NonVariable = InsertIntoSignature(Context.Signature,
Term->Type,Original->TheSymbol.NonVariable->NameSymbol,
Original->TheSymbol.NonVariable->Arity);
//----Check if a flexible arity case
            if (Term->TheSymbol.NonVariable->Arity == -1) {
                NumberOfArguments = Term->FlexibleArity;
            } else {
                NumberOfArguments = Term->TheSymbol.NonVariable->Arity;
            }
            Term->Arguments = DuplicateArguments(Original->Arguments,Context,
NumberOfArguments,ForceNewVariables);
        }
        return(Term);
    }
}
//-----------------------------------------------------------------------------
TermType VariableOrFunctionOrError(READFILE Stream) {

    if (CheckTokenType(Stream,upper_word)) {
//DEBUG printf("Found a variable %s\n",CurrentToken(Stream)->NameToken);
        return(variable);
    } else {
//DEBUG printf("Found a function with functor %s\n",CurrentToken(Stream)->NameToken);
        if (CheckTokenType(Stream,atomic)) {
//DEBUG printf("%s parsed as a function\n",CurrentToken(Stream)->NameToken);
            return(function);
        } else {
            EnsureTokenType(Stream,atomic);
            return(nonterm);
        }
    }
}
//-----------------------------------------------------------------------------
int InfixOperatorParsing(READFILE Stream,TermType OriginallyExpectedType,
TermType * ExpectedRHSTermType) {

    if (OriginallyExpectedType == predicate && 
(CheckToken(Stream,lower_word,"$equal") || 
CheckToken(Stream,lower_word,"$notequal"))) {
        *ExpectedRHSTermType = term;
        return(1);
    }

    if (OriginallyExpectedType == non_logical_data &&
(CheckToken(Stream,punctuation,"-") || CheckToken(Stream,punctuation,":"))) {
        *ExpectedRHSTermType = non_logical_data;
        return(1);
    }

    return(0);
}
//-----------------------------------------------------------------------------
TERM ParseTerm(READFILE Stream,ContextType Context,VARIABLENODE * EndOfScope,
TermType Type,ConnectiveType VariableQuantifier,int * InfixNegatedAtom) {

    TERM InfixTerm,Term;
    int NumberOfArguments;
    String PrefixSymbol;
    String MatchingBracket;
    TermType TypeIfInfix;
    TermType InfixRHSType;
    int DoInfixProcessing;
    char * InfixToken;

    Term = NewTerm();
    TypeIfInfix = nonterm;

//----If a generic term, look at first letter to decide which
    switch (Type) {
        case term:
            Type = VariableOrFunctionOrError(Stream);
            break;
        case variable:
        case new_variable:
            EnsureTokenType(Stream,upper_word);
            break;
        case function:
            EnsureTokenType(Stream,atomic);
            break;
        case predicate:
//DEBUG printf("Found a predicate with symbol %s %d (want %d)\n",CurrentToken(Stream)->NameToken,CurrentToken(Stream)->KindToken,lower_word);
//----Guess that it's a variable or function for infix predicate
            TypeIfInfix = VariableOrFunctionOrError(Stream);
            break;
        case non_logical_data:
            TypeIfInfix = non_logical_data;
            break;
        default:
            printf("ERROR: Term type unknown\n");
            exit(-1);
    }
    Term->Type = Type;

//----Save the symbol for inserting in signature later
    strcpy(PrefixSymbol,CurrentToken(Stream)->NameToken);

//----Move on if not a list
    if (strcmp(PrefixSymbol,"[")) {
        NextToken(Stream);
    }
    if ((Type == predicate || Type == function || Type == non_logical_data) && 
(CheckToken(Stream,punctuation,"(") || CheckToken(Stream,punctuation,"["))) {
//DEBUG printf("it has arguments\n\n");
        if (CheckToken(Stream,punctuation,"(")) {
            strcpy(MatchingBracket,")");
        } else {
            strcpy(MatchingBracket,"]");
        }
        AcceptTokenType(Stream,punctuation);
        Term->Arguments = ParseArguments(Stream,Context,EndOfScope,
&NumberOfArguments,Type,MatchingBracket);
        AcceptToken(Stream,punctuation,MatchingBracket);
    } else {
        NumberOfArguments = 0;
        Term->Arguments = NULL;
//DEBUG printf("it does not have arguments\n");
    }

//----If a list make a special name and record flexible arity
    if (!strcmp(PrefixSymbol,"[")) {
        strcpy(PrefixSymbol,"[]");
        Term->FlexibleArity = NumberOfArguments;
        NumberOfArguments = -1;
    }

//----Check for infix predicate
    if ((DoInfixProcessing = InfixOperatorParsing(Stream,Type,&InfixRHSType))) {
        Term->Type = TypeIfInfix;
    }

//----Insert symbol into signature. Could be LHS of infix.
    if (Term->Type == new_variable) {
        Term->Type = variable;
        Term->TheSymbol.Variable = InsertVariable(Context.Signature,
Context.Variables,EndOfScope,1,PrefixSymbol,VariableQuantifier);
    } else if (Term->Type == variable) {
        Term->TheSymbol.Variable = InsertVariable(Context.Signature,
Context.Variables,EndOfScope,0,PrefixSymbol,VariableQuantifier);
    } else {
        Term->TheSymbol.NonVariable = InsertIntoSignature(Context.Signature,
Term->Type,PrefixSymbol,NumberOfArguments);
    }

//----Build the infix structure
    if (DoInfixProcessing) {
        InfixTerm = NewTerm();
        InfixTerm->Type = Type;
//----Insert the infix symbol
        if (InfixNegatedAtom != NULL &&
CheckToken(Stream,lower_word,"$notequal")) {
            InfixToken = "$equal";
            *InfixNegatedAtom = 1;
        } else {
            InfixToken = CurrentToken(Stream)->NameToken;
        }
        InfixTerm->TheSymbol.NonVariable = InsertIntoSignature(
Context.Signature,InfixTerm->Type,InfixToken,2);
        InfixTerm->Arguments = NewArguments(2);
        InfixTerm->Arguments[0] = Term;
//----Move on only after saving the infix operator
        NextToken(Stream);
        InfixTerm->Arguments[1] = ParseTerm(Stream,Context,EndOfScope,
InfixRHSType,none,NULL);
        return(InfixTerm);

    } else {
//----Non-infix
        return(Term);
    }
}
//-----------------------------------------------------------------------------
FORMULA ParseAtom(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope) {

    FORMULA Formula;
    int InfixNegatedAtom;
    FORMULA InfixFormula;

    InfixNegatedAtom = 0;
    Formula = NewFormula();
    Formula->Type = atom;
    Formula->FormulaUnion.Atom = ParseTerm(Stream,Context,EndOfScope,
predicate,none,&InfixNegatedAtom);

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
//-----------------------------------------------------------------------------
FORMULA ParseUnaryFormula(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope) {

    FORMULA Formula;
    
    Formula = NewFormula();
    Formula->Type = unary;
    Formula->FormulaUnion.UnaryFormula.Connective =
StringToConnective(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,unary_connective);
    Formula->FormulaUnion.UnaryFormula.Formula = ParseFormula(Stream,Context,
EndOfScope,0);

    return(Formula);
}
//-----------------------------------------------------------------------------
FORMULA ParseQuantifiedRemainder(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope,ConnectiveType Quantifier) {

    FORMULA Formula;
    VARIABLENODE ExtendedEndOfScope;

    if (CheckToken(Stream,punctuation,"]")) {
        AcceptToken(Stream,punctuation,"]");
        AcceptToken(Stream,punctuation,":");
        return(ParseFormula(Stream,Context,EndOfScope,0));
    } else {
        AcceptToken(Stream,punctuation,",");
        Formula = NewFormula();
        Formula->Type = quantified;
        Formula->FormulaUnion.QuantifiedFormula.Quantifier = Quantifier;
        if (Formula->FormulaUnion.QuantifiedFormula.Quantifier == existential &&
CheckTokenType(Stream,number)) {
            Formula->FormulaUnion.QuantifiedFormula.ExistentialCount =
atoi(CurrentToken(Stream)->NameToken);
            AcceptTokenType(Stream,number);
            AcceptToken(Stream,punctuation,":");
        } else {
            Formula->FormulaUnion.QuantifiedFormula.ExistentialCount = -1;
        }

//----Get the variable
        ExtendedEndOfScope = *EndOfScope;
        Formula->FormulaUnion.QuantifiedFormula.Variable =
ParseTerm(Stream,Context,&ExtendedEndOfScope,new_variable,Quantifier,NULL);
//----Here's the first place a type would be parsed
        Formula->FormulaUnion.QuantifiedFormula.Formula = 
ParseQuantifiedRemainder(Stream,Context,&ExtendedEndOfScope,Quantifier);
        return(Formula);
    }
}
//-----------------------------------------------------------------------------
FORMULA ParseQuantifiedFormula(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope) {

    FORMULA Formula;
    VARIABLENODE ExtendedEndOfScope;
    
    Formula = NewFormula();
    Formula->Type = quantified;
    Formula->FormulaUnion.QuantifiedFormula.Quantifier = 
StringToConnective(CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,quantifier);
    AcceptToken(Stream,punctuation,"[");
//----Check if existential count is there
    if (Formula->FormulaUnion.QuantifiedFormula.Quantifier == existential &&
CheckTokenType(Stream,number)) {
        Formula->FormulaUnion.QuantifiedFormula.ExistentialCount =
atoi(CurrentToken(Stream)->NameToken);
        AcceptTokenType(Stream,number);
        AcceptToken(Stream,punctuation,":");
    } else {
        Formula->FormulaUnion.QuantifiedFormula.ExistentialCount = -1;
    }

//----Get the variable
    ExtendedEndOfScope = *EndOfScope;
    Formula->FormulaUnion.QuantifiedFormula.Variable = 
ParseTerm(Stream,Context,&ExtendedEndOfScope,new_variable,
Formula->FormulaUnion.QuantifiedFormula.Quantifier,NULL);
//----Here's the second place a type would be parsed
    Formula->FormulaUnion.QuantifiedFormula.Formula = ParseQuantifiedRemainder(
Stream,Context,&ExtendedEndOfScope,Formula->
FormulaUnion.QuantifiedFormula.Quantifier);

    return(Formula);
}
//-----------------------------------------------------------------------------
//----This assumes it's in the context of duplicating a formula with variables
FORMULA DuplicateFormula(FORMULA Original,ContextType Context,
int ForceNewVariables) {

    FORMULA Formula;

    Formula = NewFormula();
    *Formula = *Original;

    switch (Formula->Type) {
        case quantified:
            Formula->FormulaUnion.QuantifiedFormula.Variable =
DuplicateTerm(Original->FormulaUnion.QuantifiedFormula.Variable,Context,1);
            Formula->FormulaUnion.QuantifiedFormula.Formula =
DuplicateFormula(Original->FormulaUnion.QuantifiedFormula.Formula,Context,
ForceNewVariables);
            break;
        case binary:
            Formula->FormulaUnion.BinaryFormula.LHS =
DuplicateFormula(Original->FormulaUnion.BinaryFormula.LHS,Context,
ForceNewVariables);
            Formula->FormulaUnion.BinaryFormula.RHS =
DuplicateFormula(Original->FormulaUnion.BinaryFormula.RHS,Context,
ForceNewVariables);
            break;
        case unary:
            Formula->FormulaUnion.UnaryFormula.Formula =
DuplicateFormula(Original->FormulaUnion.UnaryFormula.Formula,Context,
ForceNewVariables);
            break; 
        case atom:
            Formula->FormulaUnion.Atom =
DuplicateTerm(Original->FormulaUnion.Atom,Context,
ForceNewVariables);
            break;
        default:
            printf("ERROR: Formula type unknown for duplication\n");
            exit(-1);
            break;
    }
    return(Formula);
}
//-----------------------------------------------------------------------------
FORMULA ParseFormula(READFILE Stream,ContextType Context,
VARIABLENODE * EndOfScope,int AllowBinary) {

    FORMULA Formula;
    FORMULA BinaryFormula;

    switch (CurrentToken(Stream)->KindToken) {
        case punctuation:
            AcceptToken(Stream,punctuation,"(");
            Formula = ParseFormula(Stream,Context,EndOfScope,1);
            AcceptToken(Stream,punctuation,")");
            break;
        case quantifier:
            Formula = ParseQuantifiedFormula(Stream,Context,EndOfScope);
            break;
        case unary_connective:
            Formula = ParseUnaryFormula(Stream,Context,EndOfScope);
            break;
        default:
            Formula = ParseAtom(Stream,Context,EndOfScope);
            break;
    }

//----Check for a binary formula
    if (AllowBinary && CheckTokenType(Stream,binary_connective)) {
        BinaryFormula = NewFormula();
        BinaryFormula->Type = binary;
        BinaryFormula->FormulaUnion.BinaryFormula.LHS = Formula;
        BinaryFormula->FormulaUnion.BinaryFormula.Connective = 
StringToConnective(CurrentToken(Stream)->NameToken);
        AcceptTokenType(Stream,binary_connective);
        BinaryFormula->FormulaUnion.BinaryFormula.RHS = ParseFormula(Stream,
Context,EndOfScope,1);
        return(BinaryFormula);
    } else {
        return(Formula);
    }
}
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
void ParallelCopyVariableInstantiations(VARIABLENODE Original,
VARIABLENODE Copy) {

    if (Original == NULL) {
        if (Copy == NULL) {
            return;
        } else {
            CodingError("Different length variable lists from duplication");
        }
    } else {
        Copy->Instantiation = Original->Instantiation;
        ParallelCopyVariableInstantiations(Original->NextVariable,
Copy->NextVariable);
    }
}
//-----------------------------------------------------------------------------
FORMULAWITHVARIABLES DuplicateFormulaWithVariables(
FORMULAWITHVARIABLES Original,SIGNATURE Signature,int ForceNewVariables) {

    ContextType Context;
    FORMULAWITHVARIABLES FormulaWithVariables;
    
    FormulaWithVariables = NewFormulaWithVariables();

//----Copy the variables list, setting each use to 0, and setting the
//----instantiation to point to the original (cheating in duplication :-)
    FormulaWithVariables->Variables = ParallelCopyVariableList(
Original->Variables);
    
//----Create a context for the parsing
    Context.Variables = &(FormulaWithVariables->Variables);
    Context.Signature = Signature;
    
//DEBUG printf("original variables\n");
//DEBUG PrintVariableList(Original->Variables);
//DEBUG printf("parallel copy variables\n");
//DEBUG PrintVariableList(FormulaWithVariables->Variables);
    FormulaWithVariables->Formula = DuplicateFormula(Original->Formula,
Context,ForceNewVariables);
//DEBUG printf("after copy variables\n");
//DEBUG PrintVariableList(FormulaWithVariables->Variables);

//----Set the variable instantiations to their rightful values
    ParallelCopyVariableInstantiations(Original->Variables,
FormulaWithVariables->Variables);

    return(FormulaWithVariables); 
}
//-----------------------------------------------------------------------------
FORMULA DuplicateInternalFormulaWithVariables(FORMULA Original,ContextType 
OriginalContext) {

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
//-----------------------------------------------------------------------------
FORMULAWITHVARIABLES ParseFormulaWithVariables(READFILE Stream,
SIGNATURE Signature) {

    ContextType Context;
    FORMULAWITHVARIABLES FormulaWithVariables;
    VARIABLENODE EndOfScope;

    EndOfScope = NULL;
    FormulaWithVariables = NewFormulaWithVariables();

//----Create a context for the parsing
    Context.Variables = &(FormulaWithVariables->Variables);
    Context.Signature = Signature;

    Stream->IgnoreBlankLines = 1;
    FormulaWithVariables->Formula = ParseFormula(Stream,Context,&EndOfScope,1);
    Stream->IgnoreBlankLines = 0;
    return(FormulaWithVariables);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA ParseInclude(READFILE Stream,SIGNATURE Signature) {

    ContextType Context;
    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = (ANNOTATEDFORMULA)Malloc(sizeof(AnnotatedFormulaType));
    AnnotatedFormula->NumberOfUses = 1;
    AnnotatedFormula->Syntax = include;
    Context.Variables = NULL;
    Context.Signature = Signature;
    AnnotatedFormula->AnnotatedFormulaUnion.Include = ParseTerm(Stream,
Context,NULL,non_logical_data,none,NULL);
    TakeToken(Stream,punctuation,".");

    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA ParseComment(READFILE Stream) {

    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = (ANNOTATEDFORMULA)Malloc(sizeof(AnnotatedFormulaType));
    AnnotatedFormula->NumberOfUses = 1;
    AnnotatedFormula->Syntax = comment;
    AnnotatedFormula->AnnotatedFormulaUnion.Comment = CopyHeapString(
CurrentToken(Stream)->NameToken);
    AcceptTokenType(Stream,comment_token);

    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA ParseBlankLine(READFILE Stream) {

    ANNOTATEDFORMULA AnnotatedFormula;

    AnnotatedFormula = NewAnnotatedFormula(blank_line);
    AnnotatedFormula->NumberOfUses = 1;
    AcceptTokenType(Stream,blank_line_token);

    return(AnnotatedFormula);
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA DuplicateAnnotatedFormula(ANNOTATEDFORMULA Original,
SIGNATURE Signature) {

    switch (Original->Syntax) {
        case include:
        case blank_line:
        case comment:
            printf(
"ERROR: Includes, blank lines, and comments cannot be duplicated\n");
            exit(-1);
            break;
        case tptp_fof:
            return(DuplicateAnnotatedTSTPFormula(Original,Signature,0));
            break;
        case tptp_cnf:
            return(DuplicateAnnotatedTSTPFormula(Original,Signature,1));
            break;
        default:
            printf("ERROR: Annotated formula syntax unknown for duplicating\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
void FreeAnnotatedFormula(ANNOTATEDFORMULA * AnnotatedFormula) {

    if (*AnnotatedFormula != NULL) {
        if (--((*AnnotatedFormula)->NumberOfUses) == 0) {
            switch ((*AnnotatedFormula)->Syntax) {
                case include:
                    FreeTerm(&((*AnnotatedFormula)->
AnnotatedFormulaUnion.Include),NULL);
                    Free((void **)AnnotatedFormula);
                    break;
                case comment:
                    Free((void **)&((*AnnotatedFormula)->
AnnotatedFormulaUnion.Comment));
                    Free((void **)AnnotatedFormula);
                    break;
                case blank_line:
                    Free((void **)AnnotatedFormula);
                    break;
                case tptp_fof:
                case tptp_cnf:
                    FreeAnnotatedTSTPFormula(AnnotatedFormula);
                    break;
                default:
                    printf(
"ERROR: Annotated formula syntax unknown for freeing\n");
                    exit(-1);
                    break;
            }
        }
    }
}
//-----------------------------------------------------------------------------
ANNOTATEDFORMULA ParseAnnotatedFormula(READFILE Stream,SIGNATURE Signature) {

    if (CheckToken(Stream,lower_word,"input_formula")) {
        return(ParseAnnotatedTPTPFormula(Stream,Signature));
    }

    if (CheckToken(Stream,lower_word,"input_clause")) {
        return(ParseAnnotatedTPTPClause(Stream,Signature));
    }

    if (CheckToken(Stream,lower_word,"include")) {
        return(ParseInclude(Stream,Signature));
    }

    if (CheckTokenType(Stream,comment_token)) {
        return(ParseComment(Stream));
    }

    if (CheckTokenType(Stream,blank_line_token)) {
        return(ParseBlankLine(Stream));
    }

    return(ParseAnnotatedTSTPFormula(Stream,Signature));
}
//-----------------------------------------------------------------------------
LISTNODE NewListNode(ANNOTATEDFORMULA AnnotatedFormula) {

    LISTNODE NewNode;

    NewNode = (LISTNODE)Malloc(sizeof(ListNodeType));
    NewNode->Next = NULL;
    NewNode->AnnotatedFormula = AnnotatedFormula;

    return(NewNode);
}
//-----------------------------------------------------------------------------
void FreeListOfAnnotatedFormulae(LISTNODE * Head) {

    if (*Head != NULL) {
        if ((*Head)->Next != NULL) {
            FreeListOfAnnotatedFormulae(&((*Head)->Next));
        }
        FreeAnnotatedFormula(&((*Head)->AnnotatedFormula));
        Free((void **)Head);
    }
}
//-----------------------------------------------------------------------------
void GetIncludeParts(ANNOTATEDFORMULA AnnotatedFormula,String IncludeFile,
String IncludeFilter) {

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
                printf("ERROR: Include directive is malformed\n");
                exit(-1);
            }
        }
    } else {
        strcpy(IncludeFilter,"all");
    }
//DEBUG printf("==%s==%s==\n",IncludeFile,IncludeFilter);
}
//-----------------------------------------------------------------------------
LISTNODE ParseREADFILEOfFormulae(READFILE Stream,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter) {

    ANNOTATEDFORMULA AnnotatedFormula;
    LISTNODE Head;
    String IncludeFile,IncludeFilter;
    String FormulaName;
    LISTNODE IncludedHead,IncludeNode,HeaderNode;
    LISTNODE * Current;
    LISTNODE Mover;

    Head = NULL;
    Current = &Head;
    while (!CheckTokenType(Stream,endeof)) {
        AnnotatedFormula = ParseAnnotatedFormula(Stream,Signature);
//----Filter formulae by name
        if ((AnnotatedFormula->Syntax == tptp_fof ||
AnnotatedFormula->Syntax == tptp_cnf) &&
!NameInList(GetName(AnnotatedFormula,FormulaName),NameFilter)) {
            FreeAnnotatedFormula(&AnnotatedFormula);
        }

//----If it's still there, then add it on
        if (AnnotatedFormula != NULL) {
            (*Current) = NewListNode(AnnotatedFormula);
            Current = &((*Current)->Next);
        }
    }

//----Expand includes if required
    if (ExpandIncludes) {
        Current = &Head;
        while ((*Current) != NULL) {
            if ((*Current)->AnnotatedFormula->Syntax == include) {
                GetIncludeParts((*Current)->AnnotatedFormula,IncludeFile,
IncludeFilter);
//DEBUG printf("Have to include %s filtered by %s\n",IncludeFile,IncludeFilter);
                if ((IncludedHead = ParseFileOfFormulae(IncludeFile,Signature,
ExpandIncludes,IncludeFilter)) == NULL) {
                    printf("ERROR: Could not include %s\n",IncludeFile);
                } else {
//DEBUG printf("===%s===\n",IncludeFile);
//DEBUG PrintListOfAnnotatedTSTPNodes(stdout,IncludedHead,1);
//DEBUG printf("-------------\n");

//----Remove included header
                    if (IncludedHead->Next != NULL &&
IncludedHead->Next->AnnotatedFormula->Syntax == comment &&
strstr(IncludedHead->Next->AnnotatedFormula->AnnotatedFormulaUnion.Comment,
"% File     :") == IncludedHead->Next->
AnnotatedFormula->AnnotatedFormulaUnion.Comment) {
                        do {
                            HeaderNode = IncludedHead;
                            IncludedHead = IncludedHead->Next;
                            FreeAnnotatedFormula(&(HeaderNode->
AnnotatedFormula));
                            Free((void **)&HeaderNode);
                        } while (IncludedHead != NULL &&
!(IncludedHead->AnnotatedFormula->Syntax == comment &&
strstr(IncludedHead->AnnotatedFormula->AnnotatedFormulaUnion.Comment,
"%------------------------------------------------------") ==
IncludedHead->AnnotatedFormula->AnnotatedFormulaUnion.Comment));
                    }
                }

//----Link in and move down to the end
                IncludeNode = (*Current);
                if (IncludedHead == NULL) {
                    (*Current) = IncludeNode->Next;
                } else {
                    (*Current) = IncludedHead;
                    Mover = *Current;
                    while (Mover->Next != NULL) {
                        Mover = Mover->Next;
                    }
                    Mover->Next = IncludeNode->Next;
                }
                FreeAnnotatedFormula(&(IncludeNode->AnnotatedFormula));
                Free((void **)&IncludeNode);
            } else {
                Current = &((*Current)->Next);
            }
        }
    }

    return(Head);
}
//-----------------------------------------------------------------------------
LISTNODE ParseFILEOfFormulae(FILE * FileStream,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter) {

    READFILE Stream; 
    LISTNODE Head;

    if ((Stream = OpenFILEFile(FileStream)) == NULL) {
        return(NULL);
    }

    Head = ParseREADFILEOfFormulae(Stream,Signature,ExpandIncludes,NameFilter);
    CloseFile(Stream);

    return(Head);
}
//-----------------------------------------------------------------------------
LISTNODE ParseFileOfFormulae(char * FileName,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter) {

    READFILE Stream; 
    LISTNODE Head;

    if ((Stream = OpenFile(FileName)) == NULL) {
        return(NULL);
    }

    Head = ParseREADFILEOfFormulae(Stream,Signature,ExpandIncludes,NameFilter);
    CloseFile(Stream);

    return(Head);
}
//-----------------------------------------------------------------------------
LISTNODE ParseStringOfFormulae(char * Content,SIGNATURE Signature,
int ExpandIncludes,char * NameFilter) {

    READFILE Stream;
    LISTNODE Head;
    
    if ((Stream = OpenStringFile(Content)) == NULL) {
        return(NULL);
    }
    
    Head = ParseREADFILEOfFormulae(Stream,Signature,ExpandIncludes,NameFilter);
    CloseFile(Stream);
    
    return(Head);

}
//-----------------------------------------------------------------------------
TERM ParseStringTerm(char * Content,SIGNATURE Signature) {

    READFILE Stream;
    ContextType Context;
    TERM Term;

    if ((Stream = OpenStringFile(Content)) == NULL) {
        return(NULL);
    }

//----Create a context for the parsing. No variable in non-logical data
    Context.Variables = NULL;
    Context.Signature = Signature;
    Term = ParseTerm(Stream,Context,NULL,non_logical_data,none,NULL);
    CloseFile(Stream);

    return(Term);
}
//-----------------------------------------------------------------------------

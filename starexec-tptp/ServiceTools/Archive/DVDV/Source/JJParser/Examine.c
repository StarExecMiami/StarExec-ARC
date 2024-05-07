#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "PrintTSTP.h"
#include "Examine.h"
//-----------------------------------------------------------------------------
char * GetInferenceParentNames(TERM InferenceTerm,String PutNamesHere);
int CountVariableUsageInTerm(TERM Term,VARIABLENODE Variable);
//-----------------------------------------------------------------------------
int CheckAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SyntaxType ExpectedSyntax) {

    return(AnnotatedFormula != NULL && 
AnnotatedFormula->Syntax == ExpectedSyntax &&
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
FormulaWithVariables != NULL);
}
//-----------------------------------------------------------------------------
char * GetSymbol(TERM Term) {

    if (Term->Type == variable) {
        return(GetSignatureSymbol(Term->TheSymbol.Variable->VariableName));
    } else {
        return(GetSignatureSymbol(Term->TheSymbol.NonVariable));
    }
}
//-----------------------------------------------------------------------------
int GetArity(TERM Term) {

    if (Term->Type == variable) {
        return(GetSignatureArity(Term->TheSymbol.Variable->VariableName));
//----Lists have flexible arity (signature arity should be -1)
    } else if (!strcmp(GetSymbol(Term),"[]")) {
        return(Term->FlexibleArity);
//----Otherwise get from the signature
    } else {
        return(GetSignatureArity(Term->TheSymbol.NonVariable));
    }
}
//-----------------------------------------------------------------------------
char * TSTPTermToString(TERM Term,String PutTermHere) {

    String Part;
    int Index;
    int Arity;
    String OpeningBracket,ClosingBracket;

    strcpy(PutTermHere,"");

//----Check if infix - or : (see also PrintTSTPTerm in PrintTSTP.c)
//----No need to worry about infix equality here - only for non_logical_data
    if (!strcmp(GetSymbol(Term),"-") || !strcmp(GetSymbol(Term),":")) {
        strcat(PutTermHere,TSTPTermToString(Term->Arguments[0],Part));
        strcat(PutTermHere,GetSymbol(Term));
        strcat(PutTermHere,TSTPTermToString(Term->Arguments[1],Part));
    } else {
//----Check if a list
        if (!strcmp(GetSymbol(Term),"[]")) {
            strcpy(OpeningBracket,"[");
            strcpy(ClosingBracket,"]");
        } else {
            strcat(PutTermHere,GetSymbol(Term));
            strcpy(OpeningBracket,"(");
            strcpy(ClosingBracket,")");
        }
        
        if ((Arity = GetArity(Term)) > 0 || !strcmp(OpeningBracket,"[")) {
            strcat(PutTermHere,OpeningBracket);
            if (Arity > 0) {
                strcat(PutTermHere,TSTPTermToString(Term->Arguments[0],Part));
                for (Index=1;Index < Arity;Index++) {
                    strcat(PutTermHere,",");
                    strcat(PutTermHere,TSTPTermToString(Term->Arguments[Index],
Part));
                }
            }
            strcat(PutTermHere,ClosingBracket);
        }
    }
    return(PutTermHere);
}
//-----------------------------------------------------------------------------
int CountVariableUsageInArguments(TERMArray Arguments,int Arity,
VARIABLENODE Variable) {

    int Count;
    int Index;

    Count = 0;
    for (Index = 0;Index<Arity;Index++) {
        Count += CountVariableUsageInTerm(Arguments[Index],Variable);
    }
    return(Count);
}
//-----------------------------------------------------------------------------
int CountVariableUsageInTerm(TERM Term,VARIABLENODE Variable) {

    switch (Term->Type) {
        case variable:
            return(Term->TheSymbol.Variable == Variable ? 1 : 0);
            break;
        case function:
        case predicate:
            return(CountVariableUsageInArguments(Term->Arguments,Term->
TheSymbol.NonVariable->Arity,Variable));
            break;
        default:
            printf("ERROR: Bad term type for counting variable occurences\n");
            exit(-1);
    }

}
//-----------------------------------------------------------------------------
int CountVariableUsageInFormula(FORMULA Formula,VARIABLENODE Variable,
int * QuantifiedOccurences) {

    int LocalQuantifiedOccurences;
    int LocalQuantifiedOccurences2;
    int LocalCount;

    LocalQuantifiedOccurences = 0;

    switch (Formula->Type) {
        case quantified:
            LocalCount = CountVariableUsageInFormula(Formula->
FormulaUnion.QuantifiedFormula.Formula,Variable,&LocalQuantifiedOccurences);
            if (Formula->FormulaUnion.QuantifiedFormula.Variable->
TheSymbol.Variable == Variable) {
                LocalQuantifiedOccurences++;
            }
            break;
        case binary:
            LocalCount = CountVariableUsageInFormula(Formula->FormulaUnion.
BinaryFormula.LHS,Variable,&LocalQuantifiedOccurences);
            LocalCount += CountVariableUsageInFormula(Formula->FormulaUnion.
BinaryFormula.RHS,Variable,&LocalQuantifiedOccurences2);
            LocalQuantifiedOccurences += LocalQuantifiedOccurences2;
            break;
        case unary:
            LocalCount = CountVariableUsageInFormula(Formula->FormulaUnion.
UnaryFormula.Formula,Variable,&LocalQuantifiedOccurences);
            break;
        case atom:
            LocalCount = CountVariableUsageInTerm(Formula->FormulaUnion.Atom,
Variable);
            break;
        default:
            printf("ERROR: Unknown formula type in count variables usage\n");
            exit(EXIT_FAILURE);
            break;
    }
    if (LocalQuantifiedOccurences > 1) {
        CodingError("Multiply quantified variable");
    }
    if (QuantifiedOccurences != NULL) {
        *QuantifiedOccurences = LocalQuantifiedOccurences;
    }

    return(LocalCount);
}
//-----------------------------------------------------------------------------
void NormalizeSymbolUsage(char * SymbolUsage) {

    SYMBOLNODE Head;
    SYMBOLNODE Searcher;
    char * Triple;
    char * TripleLast;
    char * Functor;
    int Arity,Uses;
    String NextTriple;

    Head = NULL;
    Triple = strtok_r(SymbolUsage,"\n",&TripleLast);
    while (Triple != NULL) {
        Functor = strtok(Triple,"/");
        Arity = atoi(strtok(NULL,"/"));
        Uses = atoi(strtok(NULL,"\n"));
        Searcher = Head;
        while (Searcher != NULL && (strcmp(Searcher->NameSymbol,Functor) || 
Searcher->Arity != Arity)) {
            Searcher = Searcher->NextSymbol;
        }
        if (Searcher != NULL) {
            Searcher->NumberOfUses += Uses;
        } else {
            Searcher = (SYMBOLNODE)Malloc(sizeof(SymbolNodeType));
            Searcher->NameSymbol = CopyHeapString(Functor);
            Searcher->Arity = Arity;
            Searcher->NumberOfUses = Uses;
            Searcher->NextSymbol = Head;
            Head = Searcher;
        }
        Triple = strtok_r(NULL,"\n",&TripleLast);
    }

    strcpy(SymbolUsage,"");
    while (Head != NULL) {
        sprintf(NextTriple,"%s/%d/%d\n",Head->NameSymbol,Head->Arity,
Head->NumberOfUses);
        strcat(SymbolUsage,NextTriple);
        Searcher = Head;
        Head = Head->NextSymbol;
        Free((void **)&(Searcher->NameSymbol));
        Free((void **)&Searcher);
    }
}
//-----------------------------------------------------------------------------
void CollectVariablesInAtom(TERM Term,char ** Collector,int * CollectorLength) {

    String Variable;
    int index;

    if (Term->Type == variable) {
        sprintf(Variable,"%s/0/1\n",
Term->TheSymbol.Variable->VariableName->NameSymbol);
        ExtendString(Collector,Variable,CollectorLength);
    } else if (Term->Type == predicate || Term->Type == function) {
        for (index = 0; index < Term->TheSymbol.NonVariable->Arity; index++) {
            CollectVariablesInAtom(Term->Arguments[index],Collector,
CollectorLength);
        }
    }
}
//-----------------------------------------------------------------------------
void CollectFunctorsInAtom(TERM Term,char ** Collector,int * CollectorLength) {

    String FunctorAndArity;
    int index;

    if (Term->Type == predicate || Term->Type == function) {
        if (Term->Type == function) {
            sprintf(FunctorAndArity,"%s/%d/1\n",
Term->TheSymbol.NonVariable->NameSymbol,Term->TheSymbol.NonVariable->Arity);
            ExtendString(Collector,FunctorAndArity,CollectorLength);
        }
        for (index = 0; index < Term->TheSymbol.NonVariable->Arity; index++) {
            CollectFunctorsInAtom(Term->Arguments[index],Collector,
CollectorLength);
        }
    }
}
//-----------------------------------------------------------------------------
//----PutUsageHere must be address of a malloced String
char * GetLiteralSymbolUsage(FORMULA Literal,char ** PutUsageHere,
char ** VariablesStartHere) {

    char Sign;
    char * Collector;
    int UsageLength = STRINGLENGTH;
    int CollectorLength = STRINGLENGTH;

    strcpy(*PutUsageHere,"");
    if (Literal == NULL) {
        return(NULL);
    } else if (Literal->Type == unary && 
Literal->FormulaUnion.UnaryFormula.Connective == negation) {
        Sign = '~';
        Literal = Literal->FormulaUnion.UnaryFormula.Formula;
    } else if (Literal->Type == atom) {
        Sign = ' ';
    } else {
        return(NULL);
    }

    sprintf(*PutUsageHere,"%c%s/%d/1\n",Sign,
Literal->FormulaUnion.Atom->TheSymbol.NonVariable->NameSymbol,
Literal->FormulaUnion.Atom->TheSymbol.NonVariable->Arity);

    Collector = (char *)Malloc(sizeof(String));
    strcpy(Collector,"");
    CollectFunctorsInAtom(Literal->FormulaUnion.Atom,&Collector,
&CollectorLength);
    NormalizeSymbolUsage(Collector);
    ExtendString(PutUsageHere,Collector,&UsageLength);
    Free((void **)&Collector);

//----Collect variables if not a NULL start pointer
    if (VariablesStartHere != NULL) {
        Collector = (char *)Malloc(sizeof(String));
        strcpy(Collector,"");
        CollectVariablesInAtom(Literal->FormulaUnion.Atom,&Collector,
&CollectorLength);
        *VariablesStartHere = &((*PutUsageHere)[strlen(*PutUsageHere)]);
        NormalizeSymbolUsage(Collector);
        ExtendString(PutUsageHere,Collector,&UsageLength);
        Free((void **)&Collector);
    }

    return(*PutUsageHere);
}
//-----------------------------------------------------------------------------
void CollectSymbolsInFormula(FORMULA Formula,char ** PredicateCollector,
int * PredicateCollectorLength,char ** FunctorCollector,
int * FunctorCollectorLength,char ** VariableCollector,
int * VariableCollectorLength) {

    String PredicateAndArity;

    switch (Formula->Type) {
        case quantified:
            CollectSymbolsInFormula(Formula->FormulaUnion.QuantifiedFormula.
Formula,PredicateCollector,PredicateCollectorLength,FunctorCollector,
FunctorCollectorLength,VariableCollector,VariableCollectorLength);
            break;
        case binary:
            CollectSymbolsInFormula(Formula->FormulaUnion.BinaryFormula.LHS,
PredicateCollector,PredicateCollectorLength,FunctorCollector,
FunctorCollectorLength,VariableCollector,VariableCollectorLength);
            CollectSymbolsInFormula(Formula->FormulaUnion.BinaryFormula.RHS,
PredicateCollector,PredicateCollectorLength,FunctorCollector,
FunctorCollectorLength,VariableCollector,VariableCollectorLength);
            break;
        case unary:
            CollectSymbolsInFormula(Formula->
FormulaUnion.UnaryFormula.Formula,PredicateCollector,PredicateCollectorLength,
FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength);
            break;
        case atom:
            sprintf(PredicateAndArity,"%s/%d/1\n",GetSymbol(Formula->
FormulaUnion.Atom),GetArity(Formula->FormulaUnion.Atom));
            ExtendString(PredicateCollector,PredicateAndArity,
PredicateCollectorLength);
            CollectFunctorsInAtom(Formula->FormulaUnion.Atom,FunctorCollector,
FunctorCollectorLength);
            CollectVariablesInAtom(Formula->FormulaUnion.Atom,VariableCollector,
VariableCollectorLength);
            break;
        default:
            printf("ERROR: Not a known formula type in collect predicates\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
//----PutUsageHere must be address of a malloced String
char * GetFormulaSymbolUsage(FORMULA Formula,char ** PutUsageHere,
char ** FunctorUsageStartsHere,char ** VariableUsageStartsHere) {

    char * PredicateCollector;
    char * FunctorCollector;
    char * VariableCollector;
    int UsageLength = STRINGLENGTH;
    int PredicateCollectorLength = STRINGLENGTH;
    int FunctorCollectorLength = STRINGLENGTH;
    int VariableCollectorLength = STRINGLENGTH;
    int PredicateLength;
    int FunctorLength;

    PredicateCollector = (char *)Malloc(sizeof(String));
    strcpy(PredicateCollector,"");
    FunctorCollector = (char *)Malloc(sizeof(String));
    strcpy(FunctorCollector,"");
    VariableCollector = (char *)Malloc(sizeof(String));
    strcpy(VariableCollector,"");
    CollectSymbolsInFormula(Formula,
&PredicateCollector,&PredicateCollectorLength,&FunctorCollector,
&FunctorCollectorLength,&VariableCollector,&VariableCollectorLength);
//DEBUG printf("Predicates:%s\n",PredicateCollector);
//DEBUG printf("Functors  :%s\n",FunctorCollector);
//DEBUG printf("Variables :%s\n",VariableCollector);

    strcpy(*PutUsageHere,"");
    NormalizeSymbolUsage(PredicateCollector);
    PredicateLength = strlen(PredicateCollector);
    ExtendString(PutUsageHere,PredicateCollector,&UsageLength);
    Free((void **)&PredicateCollector);

    NormalizeSymbolUsage(FunctorCollector);
    FunctorLength = strlen(FunctorCollector);
    ExtendString(PutUsageHere,FunctorCollector,&UsageLength);
    Free((void **)&FunctorCollector);

    NormalizeSymbolUsage(VariableCollector);
    ExtendString(PutUsageHere,VariableCollector,&UsageLength);
    Free((void **)&VariableCollector);

    *FunctorUsageStartsHere = *PutUsageHere + PredicateLength;
    *VariableUsageStartsHere = *FunctorUsageStartsHere + FunctorLength;

    return(*PutUsageHere);
}
//-----------------------------------------------------------------------------
//----PutUsageHere must be address of a malloced String
char * GetAnnotatedFormulaSymbolUsage(ANNOTATEDFORMULA AnnotatedTSTPFormula,
char ** PutUsageHere,char ** FunctorUsageStartsHere) {

    char * VariableUsage;
    char * Result;

//----Ignore comments
    if (CheckAnnotatedFormula(AnnotatedTSTPFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedTSTPFormula,tptp_cnf)) {
        if ((Result = GetFormulaSymbolUsage(AnnotatedTSTPFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
PutUsageHere,FunctorUsageStartsHere,&VariableUsage)) != NULL) {
//----Variables not returned at the moment, maybe later
            *VariableUsage = '\0';
            return(Result);
        } else {
            return(NULL);
        }
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
//----PutUsageHere must be address of a malloced String
char * GetListOfAnnotatedFormulaSymbolUsage(LISTNODE ListNode,
char ** PutUsageHere,char ** FunctorUsageStartsHere) {

    char * PredicateCollector;
    char * FunctorCollector;
    char * OneUsage;
    char * FunctorsStart;
    int UsageLength = STRINGLENGTH;
    int PredicateCollectorLength = STRINGLENGTH;
    int FunctorCollectorLength = STRINGLENGTH;

//----Collect predicates and functors
    PredicateCollector = (char *)Malloc(sizeof(String));
    strcpy(PredicateCollector,"");
    FunctorCollector = (char *)Malloc(sizeof(String));
    strcpy(FunctorCollector,"");

    while (ListNode != NULL) {
        OneUsage = (char *)Malloc(sizeof(String));
        strcpy(OneUsage,"");
        if (GetAnnotatedFormulaSymbolUsage(ListNode->AnnotatedFormula,
&OneUsage,&FunctorsStart) != NULL) {
            ExtendString(&FunctorCollector,FunctorsStart,
&FunctorCollectorLength);
            *FunctorsStart = '\0';
            ExtendString(&PredicateCollector,OneUsage,
&PredicateCollectorLength);
        }
        Free((void **)&OneUsage);
        ListNode = ListNode->Next;
    }

    strcpy(*PutUsageHere,"");
    NormalizeSymbolUsage(PredicateCollector);
    ExtendString(PutUsageHere,PredicateCollector,&UsageLength);
    Free((void **)&PredicateCollector);
    *FunctorUsageStartsHere = &((*PutUsageHere)[strlen(*PutUsageHere)]);
    NormalizeSymbolUsage(FunctorCollector);
    ExtendString(PutUsageHere,FunctorCollector,&UsageLength);
    Free((void **)&FunctorCollector);

    return(*PutUsageHere);
}
//-----------------------------------------------------------------------------
//----PutPositivesHere and PutNegativesHere must be addresses of
//----malloced empty strings
void CollectVariablesOfPolarity(FORMULA DisjunctionOrLiteral,
char ** PutPositivesHere,int * PositivesLength,char ** PutNegativesHere,
int * NegativesLength) {

    char * LiteralSymbols;
    char * LiteralVariables;

    if (DisjunctionOrLiteral == NULL) {
        return;
    }

    switch (DisjunctionOrLiteral->Type) {
        case binary:
            CollectVariablesOfPolarity(DisjunctionOrLiteral->
FormulaUnion.BinaryFormula.LHS,PutPositivesHere,PositivesLength,
PutNegativesHere,NegativesLength);
            CollectVariablesOfPolarity(DisjunctionOrLiteral->
FormulaUnion.BinaryFormula.RHS,PutPositivesHere,PositivesLength,
PutNegativesHere,NegativesLength);
            break;
        case unary:
        case atom:
            LiteralSymbols = (char *)Malloc(sizeof(String));
            if (GetLiteralSymbolUsage(DisjunctionOrLiteral,&LiteralSymbols,
&LiteralVariables) != NULL) {
//DEBUG printf("Literal symbols are \n%s\n",LiteralSymbols);
//DEBUG printf("Literal variables are \n%s\n",LiteralVariables);
                if (DisjunctionOrLiteral->Type == unary) {
                    ExtendString(PutNegativesHere,LiteralVariables,
NegativesLength);
                } else {
                    ExtendString(PutPositivesHere,LiteralVariables,
PositivesLength);
                }
            } else {
                printf("ERROR: Cannot get literal symbol usage\n");
            }
            Free((void **)&LiteralSymbols);
            break;
        default:
            printf("ERROR: Not a clause in tptp_cnf\n");
            exit(-1);
            break;
    }
    NormalizeSymbolUsage(*PutPositivesHere);
    NormalizeSymbolUsage(*PutNegativesHere);
}
//-----------------------------------------------------------------------------
int RangeRestrictedClause(ANNOTATEDFORMULA AnnotatedFormula) {

    char * PutPositivesHere;
    int PositivesLength;
    char * PutNegativesHere;
    int NegativesLength;
    int RangeRestricted;
    char * PositiveVariable;
    char * Slash;
    String CRNameSlash;

    if (!CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        return(0);
    }

    PutPositivesHere = (char *)Malloc(sizeof(String));
    strcpy(PutPositivesHere,"");
    PositivesLength = STRINGLENGTH;
    PutNegativesHere = (char *)Malloc(sizeof(String));
    strcpy(PutNegativesHere,"");
    NegativesLength = STRINGLENGTH;

    CollectVariablesOfPolarity(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula,&PutPositivesHere,
&PositivesLength,&PutNegativesHere,&NegativesLength);

//----Assume RR
    RangeRestricted = 1;
    PositiveVariable = strtok(PutPositivesHere,"\n");
//----Check each positive is also a negative
    while (RangeRestricted && PositiveVariable != NULL) {
        if ((Slash = strchr(PositiveVariable,'/')) == NULL) {
            CodingError("No slash in variable information\n");
        }
        *(Slash+1) = '\0';
        strcpy(CRNameSlash,"\n");
        strcat(CRNameSlash,PositiveVariable);
//----Check at start of list and beyond (see NameInList)
        if ((strstr(PutNegativesHere,&CRNameSlash[1]) != PutNegativesHere) &&
(strstr(PutNegativesHere,CRNameSlash) == NULL)) {
            RangeRestricted = 0;
        }
        PositiveVariable = strtok(NULL,"\n");
    }

    Free((void **)&PutPositivesHere);
    Free((void **)&PutNegativesHere);

    return(RangeRestricted);
}
//-----------------------------------------------------------------------------
int CountFormulaLiteralsOfPolarity(FORMULA DisjunctionOrLiteral,int Sign) {

    if (DisjunctionOrLiteral == NULL) {
        return(0);
    }

    switch (DisjunctionOrLiteral->Type) {
        case binary:
            return(
CountFormulaLiteralsOfPolarity(DisjunctionOrLiteral->
FormulaUnion.BinaryFormula.LHS,Sign) +
CountFormulaLiteralsOfPolarity(DisjunctionOrLiteral->
FormulaUnion.BinaryFormula.RHS,Sign));
            break;
        case unary:
            if (Sign == -1) {
                return(1);
            } else {
                return(0);
            }
            break;
        case atom:
            if (Sign ==  1) {
                 return(1);
            } else {
                return(0);
            }
            break;
        default:
            printf("ERROR: Not a clause in tptp_cnf\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
int CountLiteralsOfPolarity(ANNOTATEDFORMULA AnnotatedFormula,int * Positive,
int * Negative) {

    FORMULA DisjunctionOrLiteral;

    if (!CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        return(0);
    }

    DisjunctionOrLiteral = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula;
    *Positive = CountFormulaLiteralsOfPolarity(DisjunctionOrLiteral,1);
    *Negative = CountFormulaLiteralsOfPolarity(DisjunctionOrLiteral,-1);
    return(1);
}
//-----------------------------------------------------------------------------
int HornClause(ANNOTATEDFORMULA AnnotatedFormula) {

    int Positive,Negative;

    return(CountLiteralsOfPolarity(AnnotatedFormula,&Positive,&Negative) &&
Positive <= 1);
}
//-----------------------------------------------------------------------------
int NonHornClause(ANNOTATEDFORMULA AnnotatedFormula) {

    int Positive,Negative;

    return(CountLiteralsOfPolarity(AnnotatedFormula,&Positive,&Negative) &&
Positive > 1);
}
//-----------------------------------------------------------------------------
int CountAnnotatedFormulaUniqueVariablesByUse(ANNOTATEDFORMULA 
AnnotatedFormula,int MinUse,int MaxUse,ConnectiveType Quantification) {

    int Counter;
    VARIABLENODE VariableNode;

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        Counter = 0;
        VariableNode = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables;
        while (VariableNode != NULL) {
            if (
//----Usage constraint
(MinUse < 0 || MaxUse < MinUse || (VariableNode->NumberOfUses >= MinUse && 
VariableNode->NumberOfUses <= MaxUse)) && 
//----Quantification constraint
(Quantification == none || VariableNode->Quantification == Quantification)) {
                Counter++;
            }
            VariableNode = VariableNode->NextVariable;
        }
        return(Counter);
    } else {
        return(-1);
    }

}
//-----------------------------------------------------------------------------
int CountAnnotatedFormulaSingletons(ANNOTATEDFORMULA AnnotatedFormula) {

    return(CountAnnotatedFormulaUniqueVariablesByUse(AnnotatedFormula,1,1,
none));
}
//-----------------------------------------------------------------------------
int CountAnnotatedFormulaUniqueVariables(ANNOTATEDFORMULA AnnotatedFormula) {

    return(CountAnnotatedFormulaUniqueVariablesByUse(AnnotatedFormula,-1,-1,
none));
}
//-----------------------------------------------------------------------------
int CountFormulaTerms(FORMULA Formula) {

    switch(Formula->Type) {
        case quantified:
            return(CountFormulaTerms(
Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
            return(CountFormulaTerms(
Formula->FormulaUnion.BinaryFormula.LHS) + CountFormulaTerms(
Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case unary:
            return(CountFormulaTerms(
Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
            return(GetArity(Formula->FormulaUnion.Atom));
            break;
        default:
            printf("ERROR: Invalid formula type for counting atoms\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
int CountAnnotatedFormulaTerms(ANNOTATEDFORMULA AnnotatedFormula) {

    return(CountFormulaTerms(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula));
}
//-----------------------------------------------------------------------------
int CountFormulaAtomsByPredicate(FORMULA Formula,char * Predicate) {

    switch(Formula->Type) {
        case quantified:
            return(CountFormulaAtomsByPredicate(
Formula->FormulaUnion.QuantifiedFormula.Formula,Predicate));
            break;
        case binary:
            return(CountFormulaAtomsByPredicate(Formula->
FormulaUnion.BinaryFormula.LHS,Predicate) + CountFormulaAtomsByPredicate(
Formula->FormulaUnion.BinaryFormula.RHS,Predicate));
            break;
        case unary:
            return(CountFormulaAtomsByPredicate(
Formula->FormulaUnion.UnaryFormula.Formula,Predicate));
            break;
        case atom:
            if (strlen(Predicate) == 0 || !strcmp(Predicate,
Formula->FormulaUnion.Atom->TheSymbol.NonVariable->NameSymbol)) {
                return(1);
            } else {
                return(0);
            }
            break;
        default:
            printf("ERROR: Invalid formula type for counting atoms\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
int CountAnnotatedFormulaAtomsByPredicate(ANNOTATEDFORMULA AnnotatedFormula,
char * Predicate) {

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        return(CountFormulaAtomsByPredicate(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
Predicate));
    } else {
        return(-1);
    }
}
//-----------------------------------------------------------------------------
//----All the counters have to be previously initialized to 0
void GetFormulaConnectiveUsage(FORMULA Formula,
double * NumberOfFormulaNegations,double * NumberOfFormulaDisjunctions,
double * NumberOfFormulaConjunctions,double * NumberOfFormulaEquivalences,
double * NumberOfFormulaImplications,
double * NumberOfFormulaReverseImplications,
double * NumberOfFormulaXORs,double * NumberOfFormulaNORs,
double * NumberOfFormulaNANDs,double * NumberOfFormulaUniversals,
double * NumberOfFormulaExistentials) {

    switch(Formula->Type) {
        case quantified:
            if (Formula->FormulaUnion.QuantifiedFormula.Quantifier == 
universal) {
                (*NumberOfFormulaUniversals)++;
            } else if (Formula->FormulaUnion.QuantifiedFormula.Quantifier ==
existential) {
                (*NumberOfFormulaExistentials)++;
            } else {
                printf("ERROR: Unknown quantifer type in counting\n");
                exit(-1);
            }
            GetFormulaConnectiveUsage(Formula->FormulaUnion.QuantifiedFormula.
Formula,NumberOfFormulaNegations,NumberOfFormulaDisjunctions,
NumberOfFormulaConjunctions,NumberOfFormulaEquivalences,
NumberOfFormulaImplications,NumberOfFormulaReverseImplications,
NumberOfFormulaXORs,NumberOfFormulaNORs,NumberOfFormulaNANDs,
NumberOfFormulaUniversals,NumberOfFormulaExistentials);
            break;
        case binary:
            if (Formula->FormulaUnion.BinaryFormula.Connective == disjunction) {
                (*NumberOfFormulaDisjunctions)++;
            } else if (Formula->FormulaUnion.BinaryFormula.Connective ==
conjunction) {
                (*NumberOfFormulaConjunctions)++;
            } else if (Formula->FormulaUnion.BinaryFormula.Connective ==
equivalence) {
                (*NumberOfFormulaEquivalences)++;
            } else if (Formula->FormulaUnion.BinaryFormula.Connective ==
implication) {
                (*NumberOfFormulaImplications)++;
            } else if (Formula->FormulaUnion.BinaryFormula.Connective ==
reverseimplication) {
                (*NumberOfFormulaReverseImplications)++;
            } else if (Formula->FormulaUnion.BinaryFormula.Connective ==
nonequivalence) {
                (*NumberOfFormulaXORs)++;
            } else if (Formula->FormulaUnion.BinaryFormula.Connective ==
negateddisjunction) {
                (*NumberOfFormulaNORs)++;
            } else if (Formula->FormulaUnion.BinaryFormula.Connective ==
negatedconjunction) {
                (*NumberOfFormulaNANDs)++;
            } else {
                printf("ERROR: Unknown binary connective in counting\n");
                exit(-1);
            }
            GetFormulaConnectiveUsage(Formula->FormulaUnion.BinaryFormula.LHS,
NumberOfFormulaNegations,NumberOfFormulaDisjunctions,
NumberOfFormulaConjunctions,NumberOfFormulaEquivalences,
NumberOfFormulaImplications,NumberOfFormulaReverseImplications,
NumberOfFormulaXORs,NumberOfFormulaNORs,NumberOfFormulaNANDs,
NumberOfFormulaUniversals,NumberOfFormulaExistentials);
            GetFormulaConnectiveUsage(Formula->FormulaUnion.BinaryFormula.RHS,
NumberOfFormulaNegations,NumberOfFormulaDisjunctions,
NumberOfFormulaConjunctions,NumberOfFormulaEquivalences,
NumberOfFormulaImplications,NumberOfFormulaReverseImplications,
NumberOfFormulaXORs,NumberOfFormulaNORs,NumberOfFormulaNANDs,
NumberOfFormulaUniversals,NumberOfFormulaExistentials);
            break;
        case unary:
            if (Formula->FormulaUnion.UnaryFormula.Connective == negation) {
                (*NumberOfFormulaNegations)++;
            } else {
                printf("ERROR: Unknown unary connective in counting\n");
                exit(-1);
            }
            GetFormulaConnectiveUsage(Formula->FormulaUnion.UnaryFormula.
Formula,NumberOfFormulaNegations,NumberOfFormulaDisjunctions,
NumberOfFormulaConjunctions,NumberOfFormulaEquivalences,
NumberOfFormulaImplications,NumberOfFormulaReverseImplications,
NumberOfFormulaXORs,NumberOfFormulaNORs,NumberOfFormulaNANDs,
NumberOfFormulaUniversals,NumberOfFormulaExistentials);
            break;
        case atom:
            break;
        default:
            printf("ERROR: Invalid formula type for counting connectives\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
int FormulaDepth(FORMULA Formula) {

    switch(Formula->Type) {
        case quantified:
            return(1 + FormulaDepth(
Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
            return(1 + MaximumOfInt(FormulaDepth(
Formula->FormulaUnion.BinaryFormula.LHS),FormulaDepth(
Formula->FormulaUnion.BinaryFormula.RHS)));
            break;
        case unary:
            return(1 + FormulaDepth(
Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
            return(1);
            break;
        default:
            printf("ERROR: Invalid formula type for measuring depth\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
int AnnotatedFormulaDepth(ANNOTATEDFORMULA AnnotatedFormula) {

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        return(FormulaDepth(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula));
    } else {
        return(-1);
    }
}
//-----------------------------------------------------------------------------
int MaxTermDepth(TERM Term) {

    int MaxDepth;
    int Index;

    MaxDepth = 0;
    for (Index = 0; Index < GetArity(Term); Index++) {
        MaxDepth = MaximumOfInt(MaxDepth,MaxTermDepth(Term->Arguments[Index]));
    }

    return(1 + MaxDepth);
}
//-----------------------------------------------------------------------------
int MaxFormulaTermDepth(FORMULA Formula) {

    switch(Formula->Type) {
        case quantified:
            return(MaxFormulaTermDepth(
Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
            return(MaximumOfInt(MaxFormulaTermDepth(
Formula->FormulaUnion.BinaryFormula.LHS),MaxFormulaTermDepth(
Formula->FormulaUnion.BinaryFormula.RHS)));
            break;
        case unary:
            return(MaxFormulaTermDepth(
Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
            return(MaxTermDepth(Formula->FormulaUnion.Atom)-1);
//----Minus 1 because the predicate doesn't count
            break;
        default:
            printf("ERROR: Invalid formula type for max term depth\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
int MaxAnnotatedFormulaTermDepth(ANNOTATEDFORMULA AnnotatedFormula) {

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        return(MaxFormulaTermDepth(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula));
    } else {
        return(-1);
    }
}
//-----------------------------------------------------------------------------
int SumTermDepth(TERM Atom) {

    int SumDepth;
    int Index;
    
    SumDepth = 0;
    for (Index = 0; Index < GetArity(Atom); Index++) {
        SumDepth += MaxTermDepth(Atom->Arguments[Index]);
    }

    return(SumDepth);
}
//-----------------------------------------------------------------------------
int SumFormulaTermDepth(FORMULA Formula) {

    switch(Formula->Type) {
        case quantified:
            return(SumFormulaTermDepth(
Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
            return(SumFormulaTermDepth(
Formula->FormulaUnion.BinaryFormula.LHS) + SumFormulaTermDepth(
Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case unary:
            return(SumFormulaTermDepth(
Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
            return(SumTermDepth(Formula->FormulaUnion.Atom));
            break;
        default:
            printf("ERROR: Invalid formula type for max term depth\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
int SumAnnotatedFormulaTermDepth(ANNOTATEDFORMULA AnnotatedFormula) {

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        return(SumFormulaTermDepth(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula));
    } else {
        return(-1);
    }
}
//-----------------------------------------------------------------------------
SyntaxType GetSyntax(ANNOTATEDFORMULA AnnotatedFormula) {

    assert(AnnotatedFormula != NULL);
    return(AnnotatedFormula->Syntax);
}
//-----------------------------------------------------------------------------
SyntaxType GetListSyntax(LISTNODE Head) {

    SyntaxType SyntaxOfFirstAnnotatedFormula;
    SyntaxType SyntaxOfAnnotatedFormula;

    SyntaxOfFirstAnnotatedFormula = nontype;
    while (Head != NULL && SyntaxOfFirstAnnotatedFormula != tptp_cnf &&
SyntaxOfFirstAnnotatedFormula != tptp_fof) {
        SyntaxOfFirstAnnotatedFormula = GetSyntax(Head->AnnotatedFormula);
        Head = Head->Next;
    }
    if (SyntaxOfFirstAnnotatedFormula != nontype) {
        while (Head != NULL) {
            SyntaxOfAnnotatedFormula = GetSyntax(Head->AnnotatedFormula);
            if ((SyntaxOfAnnotatedFormula == tptp_cnf ||
SyntaxOfAnnotatedFormula == tptp_fof) && 
SyntaxOfFirstAnnotatedFormula != SyntaxOfAnnotatedFormula) {
                return(tptp_mixed);
            }
            Head = Head->Next;
        }
    }
    return(SyntaxOfFirstAnnotatedFormula);
}
//-----------------------------------------------------------------------------
char * GetName(ANNOTATEDFORMULA AnnotatedFormula,String PutNameHere) {

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        strcpy(PutNameHere,
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
        return(PutNameHere);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
StatusType GetStatus(ANNOTATEDFORMULA AnnotatedFormula,StatusType * SubStatus) {

    if (AnnotatedFormula == NULL) {
        CodingError("No formula in GetStatus\n");
    }

    if (AnnotatedFormula->Syntax == tptp_fof || 
AnnotatedFormula->Syntax == tptp_cnf) {
//----Return the substatus only if the pointer is non-NULL
        if (SubStatus != NULL) {
            *SubStatus = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.SubStatus;
        }
        return(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status);
    } else {
        return(nonstatus);
    }
}
//-----------------------------------------------------------------------------
FORMULA GetLiteralFromClauseByNumber(FORMULA Clause,int Number) {

    if (Clause->Type == binary) {
        if (Number == 1) {
            return(Clause->FormulaUnion.BinaryFormula.LHS);
        } else {
            return(GetLiteralFromClauseByNumber(
Clause->FormulaUnion.BinaryFormula.RHS,Number-1));
        }
    } else if ((Clause->Type == unary || Clause->Type == atom) && Number == 1) {
        return(Clause);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
FORMULA GetLiteralFromAnnotatedClauseByNumber(ANNOTATEDFORMULA AnnotatedClause,
int Number) {

    FORMULAWITHVARIABLES FormulaWithVariables;

    if (CheckAnnotatedFormula(AnnotatedClause,tptp_cnf)) {
        FormulaWithVariables = AnnotatedClause->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables;
        return(GetLiteralFromClauseByNumber(AnnotatedClause->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
Number));
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
//----Calling routine must provide enough space for info
char * GetSource(ANNOTATEDFORMULA AnnotatedFormula,char * PutInfoHere) {

    if ((CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) &&
//----It has a source
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source != NULL) {
        strcpy(PutInfoHere,GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source));
        return(PutInfoHere);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
//----Calling routine must provide enough space for info
char * GetInferenceRule(ANNOTATEDFORMULA AnnotatedFormula,char * PutNameHere) {

    StatusType SubStatus;

    if ((CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) &&
//----It's derived
(GetStatus(AnnotatedFormula,&SubStatus) == derived || SubStatus == derived) &&
//----It has a source
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source != NULL) {
//----Source is an inference term
        if (!strcmp(GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),"inference")) {
            return(TSTPTermToString(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source->Arguments[0],PutNameHere));
        } else {
//----Must be a plain copy of another, no inference rule
            strcpy(PutNameHere,"");
        }
        return(PutNameHere);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
//----Gets a useful info term from an inference source
//----Calling routine must provide enough space for info
char * GetInferenceInfoTerm(ANNOTATEDFORMULA AnnotatedFormula,char * Symbol,
char * PutInfoHere) {

    TERM InferenceInfo;
    int Index;
    StatusType SubStatus;

    if ((CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) &&
//----It's derived
(GetStatus(AnnotatedFormula,&SubStatus) == derived || SubStatus == derived) &&
//----It has a source
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source !=
NULL &&
//----Source is an inference term
!strcmp(GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),"inference")) {
        InferenceInfo = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source->Arguments[1];
        for (Index = 0; Index < InferenceInfo->FlexibleArity; Index++) {
            if (!strcmp(Symbol,InferenceInfo->Arguments[Index]->
TheSymbol.NonVariable->NameSymbol)) {
//----Need to sprintf term into PutInfoHere aaargh
                return(TSTPTermToString(InferenceInfo->Arguments[Index],
PutInfoHere));
            }
        }
    }
    return(NULL);
}
//-----------------------------------------------------------------------------
//----Calling routine must provide enough space for parent names
//----Really this should be fixed to use ExtendString with malloced memory
char * GetOneParentNames(TERM ParentSource,char * PutNamesHere) {

//----If an atom, return that name
    if (GetArity(ParentSource) == 0) {
        strcpy(PutNamesHere,GetSymbol(ParentSource));
        strcat(PutNamesHere,"\n");
        return(PutNamesHere);
    }

//----If a theory
    if (!strcmp(GetSymbol(ParentSource),"theory")) {
        TSTPTermToString(ParentSource,PutNamesHere);
        strcat(PutNamesHere,"\n");
        return(PutNamesHere);
    }

//----If an atom with extra information about the inference
    if (!strcmp(GetSymbol(ParentSource),"-") && GetArity(ParentSource) == 2) {
        strcpy(PutNamesHere,GetSymbol(ParentSource->Arguments[0]));
        strcat(PutNamesHere,"\n");
        return(PutNamesHere);
    }

//----If a nested inference record
    if (!strcmp(GetSymbol(ParentSource),"inference")) {
        GetInferenceParentNames(ParentSource,PutNamesHere);
        return(PutNamesHere);
    }

    strcpy(PutNamesHere,"");
    return(PutNamesHere);
}
//-----------------------------------------------------------------------------
//----Calling routine must provide enough space for parent names
//----Really this should be fixed to use ExtendString with malloced memory
char * GetInferenceParentNames(TERM InferenceTerm,char * PutNamesHere) {

    int Index;
    String OneParentNames;

//----Check that it's an inference record with a list of parents
    if (GetArity(InferenceTerm) != 3 ||
GetSymbol(InferenceTerm->Arguments[2])[0] != '[') {
        CodingError("Getting parent names from malformed inference record");
    }

    strcpy(PutNamesHere,"");
    for (Index = 0; Index < GetArity(InferenceTerm->Arguments[2]); Index++) {
        strcat(PutNamesHere,GetOneParentNames(InferenceTerm->Arguments[2]->
Arguments[Index],OneParentNames));
    }

    return(PutNamesHere);
}
//-----------------------------------------------------------------------------
//----Calling routine must provide enough space for parent names
//----Really this should be fixed to use ExtendString with malloced memory
char * GetParentNames(ANNOTATEDFORMULA AnnotatedFormula,char * PutNamesHere) {

    StatusType SubStatus;

//----Check it's an annotated formula
    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
 CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
//----Check if it's derived and it has a source
        if ((GetStatus(AnnotatedFormula,&SubStatus) == derived ||
SubStatus == derived) && 
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source != NULL) {
//----Check if it's an inference
            if (!strcmp(GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),"inference")) {
                GetInferenceParentNames(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source,PutNamesHere);
            } else {
//----Must be the name of a node directly
                strcpy(PutNamesHere,GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source));
                strcat(PutNamesHere,"\n");
            }
        } else {
//----No source implies no parents
            strcpy(PutNamesHere,"");
        }
    } else {
//----Something wrong
        CodingError("Getting parent names from non-formula");
    }

    return(PutNamesHere);
}
//-----------------------------------------------------------------------------
//----Calling routine must provide enough space for info
char * GetFileSourceNameAndNode(ANNOTATEDFORMULA AnnotatedFormula,
char * PutUsageHere) {

    String NameOrNode;
    TERM FileTerm;

//----Formula is OK
    if ((CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) &&
//----File source
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source != NULL &&
!strcmp(GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),"file")) {
        FileTerm = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source;
        strcpy(PutUsageHere,TSTPTermToString(FileTerm->Arguments[0],
NameOrNode));
        strcat(PutUsageHere,"\n");
        strcat(PutUsageHere,TSTPTermToString(FileTerm->Arguments[1],
NameOrNode));
        return(PutUsageHere);
    } else {
        return(NULL);
    }
}
//-----------------------------------------------------------------------------
//----Gets a term from the useful info global to a CNF/FOF node
char * GetUsefulInfoTerm(ANNOTATEDFORMULA AnnotatedFormula,char * Symbol,
String PutInfoHere) {

    TERM UsefulInfo;
    int Index;

//----Formula is OK
    if ((CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) &&
//----It has useful info
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo != 
NULL &&
//----Useful info is a list of length > 0
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo->
FlexibleArity > 0) {
        UsefulInfo = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo;
        for (Index = 0; Index < UsefulInfo->FlexibleArity; Index++) {
            if (!strcmp(Symbol,UsefulInfo->Arguments[Index]->
TheSymbol.NonVariable->NameSymbol)) {
//----Need to sprintf term into PutInfoHere aaargh
                return(TSTPTermToString(UsefulInfo->Arguments[Index],
PutInfoHere));
            }
        }
    }
    return(NULL);
}
//-----------------------------------------------------------------------------

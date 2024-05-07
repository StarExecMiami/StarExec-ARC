#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include "DataTypes.h"
#include "Utilities.h"
#include "FileUtilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "List.h"
#include "PrintTSTP.h"
#include "Examine.h"
#include "SystemOnTPTP.h"
//-------------------------------------------------------------------------------------------------
char * GetInferenceParentNames(TERM InferenceTerm,String PutNamesHere);
int CountVariableUsageInTerm(TERM Term,VARIABLENODE Variable);
int CountTermNestedFormulae(SIGNATURE Signature,TERM Term);
int CountVariablesInFormulaByType(FORMULA Formula,char * Type);
int CountArgumentVariablesByType(TERM Term,char * Type);
//-------------------------------------------------------------------------------------------------
char * GetSymbol(TERM Term) {

    String ErrorMessage;

    if (Term == NULL) {
        CodingError("Getting symbol for NULL term");
    }

    switch (Term->Type) {
        case atom_as_term:
        case connective:
        case function:
        case a_type:
        case non_logical_data:
            return(GetSignatureSymbol(Term->TheSymbol.NonVariable));
            break;
        case variable:
            return(GetSignatureSymbol(Term->TheSymbol.Variable->VariableName));
            break;
        case formula:
            if (Term->TheSymbol.Formula->Type == atom) {
                return(GetSymbol(Term->TheSymbol.Formula->FormulaUnion.Atom));
            }
        default:
            sprintf(ErrorMessage,"Invalid term type %s to get symbol\n",
TermTypeToString(Term->Type));
            CodingError(ErrorMessage);
            break;
    }
    return(NULL);
}
//-------------------------------------------------------------------------------------------------
int GetArity(TERM Term) {

    String ErrorMessage;

    if (Term == NULL) {
        CodingError("Getting arity for NULL term");
    }

    switch (Term->Type) {
        case atom_as_term:
        case connective:
        case function:
        case a_type:
        case non_logical_data:
            if (!strcmp(GetSymbol(Term),"[]") || !strcmp(GetSymbol(Term),"()")) {
                return(Term->FlexibleArity);
            } else {
                return(GetSignatureArity(Term->TheSymbol.NonVariable));
            }
            break;
        case variable:
            return(0);
            break;
        case formula:
        default:
            sprintf(ErrorMessage,"Invalid term type %s to get arity\n",
TermTypeToString(Term->Type));
            CodingError(ErrorMessage);
            break;
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
TERMArray GetArguments(TERM Term) {

    if (Term == NULL) {
        CodingError("Getting arguments for NULL term");
    }

    return(Term->Arguments);
}
//-------------------------------------------------------------------------------------------------
//----If PutNameHere is NULL, return pointer to original, else copy into PutNameHere and return 
//----pointer to that.
char * GetName(ANNOTATEDFORMULA AnnotatedFormula,char * PutNameHere) {

    if (ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        if (PutNameHere == NULL) {
            return(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
        } else {
            strcpy(PutNameHere,AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name);
            return(PutNameHere);
        }
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
StatusType GetRole(ANNOTATEDFORMULA AnnotatedFormula,TERM * SubStatus) {

    if (AnnotatedFormula == NULL) {
        CodingError("No formula in GetRole");
    }

    if (ReallyAnAnnotatedFormula(AnnotatedFormula)) {
//----Return the substatus only if the pointer is non-NULL
        if (SubStatus != NULL) {
            *SubStatus = AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.SubStatus;
        }
        return(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status);
    } else {
        return(nonstatus);
    }
}
//-------------------------------------------------------------------------------------------------
AnnotatedTSTPFormulaType * GetAnnotatedTSTPFormula(ANNOTATEDFORMULA AnnotatedFormula) {

    if (AnnotatedFormula != NULL && ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        return(&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
AnnotatedTSTPFormulaType * GetListNodeAnnotatedTSTPFormula(LISTNODE List) {

    if (List != NULL && ReallyAnAnnotatedFormula(List->AnnotatedFormula)) {
        return(&(List->AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
StatusType GetListNodeStatus(LISTNODE List) {

    AnnotatedTSTPFormulaType * AnnotatedTSTPFormula;

    if ((AnnotatedTSTPFormula = GetListNodeAnnotatedTSTPFormula(List)) != NULL) {
        return(AnnotatedTSTPFormula->Status);
    } else {
        return(nonstatus);
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA GetListNodeFormula(LISTNODE List) {

    AnnotatedTSTPFormulaType * AnnotatedTSTPFormula;

    if ((AnnotatedTSTPFormula = GetListNodeAnnotatedTSTPFormula(List)) != NULL) {
        return(AnnotatedTSTPFormula->FormulaWithVariables->Formula);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
VARIABLENODE GetListNodeVariables(LISTNODE List) {

    AnnotatedTSTPFormulaType * AnnotatedTSTPFormula;

    if ((AnnotatedTSTPFormula = GetListNodeAnnotatedTSTPFormula(List)) != NULL) {
        return(AnnotatedTSTPFormula->FormulaWithVariables->Variables);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
AnnotatedTSTPFormulaType * GetTreeNodeAnnotatedTSTPFormula(TREENODE Tree) {

    if (Tree != NULL && ReallyAnAnnotatedFormula(Tree->AnnotatedFormula)) {
        return(&(Tree->AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
StatusType GetTreeNodeStatus(TREENODE Tree) {

    AnnotatedTSTPFormulaType * AnnotatedTSTPFormula;

    if ((AnnotatedTSTPFormula = GetTreeNodeAnnotatedTSTPFormula(Tree)) != NULL) {
        return(AnnotatedTSTPFormula->Status);
    } else {
        return(nonstatus);
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA GetTreeNodeFormula(TREENODE Tree) {

    AnnotatedTSTPFormulaType * AnnotatedTSTPFormula;

    if ((AnnotatedTSTPFormula = GetTreeNodeAnnotatedTSTPFormula(Tree)) != NULL) {
        return(AnnotatedTSTPFormula->FormulaWithVariables->Formula);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
VARIABLENODE GetTreeNodeVariables(TREENODE Tree) {

    AnnotatedTSTPFormulaType * AnnotatedTSTPFormula;

    if ((AnnotatedTSTPFormula = GetTreeNodeAnnotatedTSTPFormula(Tree)) != NULL) {
        return(AnnotatedTSTPFormula->FormulaWithVariables->Variables);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA GetResultFromTyping(READFILE Stream,FORMULA TypeFormula) {

    if (TypeFormula->Type == atom) {
        return(TypeFormula);
    } else if (TypeFormula->Type == tuple) {
        return(TypeFormula);
    } else if (TypeFormula->Type == binary) {
        return(GetResultFromTyping(Stream,TypeFormula->FormulaUnion.BinaryFormula.RHS));
//----Polymorphic types
    } else if (TypeFormula->Type == quantified) {
        return(GetResultFromTyping(Stream,TypeFormula->FormulaUnion.QuantifiedFormula.Formula));
    } else {
        TokenError(Stream,"Could not get result type from typing");
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
int GetArityFromTyping(READFILE Stream,FORMULA TypeFormula) {

    int Arity;
    FORMULA Side;
    String ErrorMessage;

//DEBUG printf("Get arity from type %s\n",FormulaTypeToString(TypeFormula->Type));
    switch (TypeFormula->Type) {
        case atom:
            return(0);
            break;
        case applied_connective:
        case tuple:
            return(0);
            break;
        case binary:
            if (TypeFormula->FormulaUnion.BinaryFormula.Connective == maparrow) {
                Arity = 1;
//----Do xprods on LHS for TFF
                Side = TypeFormula->FormulaUnion.BinaryFormula.LHS;
                while (Side->Type == binary && 
Side->FormulaUnion.BinaryFormula.Connective == xprodtype) {
                    Arity++;
                    Side = Side->FormulaUnion.BinaryFormula.LHS;
                }
//----Do maps on RHS for THF
                Side = TypeFormula->FormulaUnion.BinaryFormula.RHS;
                while (Side->Type == binary && 
Side->FormulaUnion.BinaryFormula.Connective == maparrow) {
                    Arity++;
                    Side = Side->FormulaUnion.BinaryFormula.RHS;
                }
                return(Arity);
            } else {
                return(0);
            }
            break;
        case  quantified:
            return(1 + GetArityFromTyping(Stream,
TypeFormula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        default:
            sprintf(ErrorMessage,"Unknown type %s for getting arity from type",
FormulaTypeToString(TypeFormula->Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
int LooksLikeAReal(char * RealString) {

    int NumberScanned;
    double TheDouble;

//----Old way of dealing with nan/Nan/NAN
//    for (Index = 0;Index < strlen(RealString);Index++) {
//        if (isalpha(RealString[Index])) {
//            RealString[Index] = tolower(RealString[Index]);
//        }
//    }

    if (strncasecmp("inf",RealString,3) && strncasecmp("nan",RealString,3)) {
        NumberScanned = sscanf(RealString,"%lf",&TheDouble);
//DEBUG printf("%s float scanned %d characters as %lf\n",RealString,NumberScanned,TheDouble);
        return(NumberScanned);
    } else {
        return(0);
    }

//----Doing it by hand
//     char * Dot;
//     char * E;
//     SuperString CopyOfRealString;
// 
// //----Currently does not recognize scientific format
//     strcpy(CopyOfRealString,RealString);
//     if ((Dot = strchr(CopyOfRealString,'.')) != NULL) {
//         *Dot = '\0';
//         if (LooksLikeAnInteger(CopyOfRealString)) {
//             if ((E = strchr(Dot+1,'E')) != NULL || 
// (E = strchr(Dot+1,'e')) != NULL) {
//                 *E = '\0';
//                 return(LooksLikeAnUnsignedInteger(Dot+1) && 
// LooksLikeAnInteger(E+1));
//             } else {
//                 return(LooksLikeAnInteger(CopyOfRealString) &&
// LooksLikeAnUnsignedInteger(Dot+1));
//             }
//         } else {
//             return(0);
//         }
//     } else {
//         return(0);
//     }
}
//-------------------------------------------------------------------------------------------------
int LooksLikeAnInteger(char * IntegerString) {

    int NumberScanned;
    long TheLong;

//----Old way of dealing with nan/Nan/NAN
//    for (Index = 0;Index < strlen(IntegerString);Index++) {
//        if (isalpha(IntegerString[Index])) {
//            IntegerString[Index] = tolower(IntegerString[Index]);
//        }
//     }

    if (strncasecmp("inf",IntegerString,3) && strncasecmp("nan",IntegerString,3)) {
        NumberScanned = sscanf(IntegerString,"%ld",&TheLong);
//DEBUG printf("%s long scanned %d characters as %ld\n",IntegerString,NumberScanned,TheLong);
        return(NumberScanned && !LooksLikeAReal(IntegerString));
    } else {
        return(0);
    }

//----Doing it by hand
//     unsigned int Index;
// 
//     Index = 0;
//     if (IntegerString[Index] == '-' || IntegerString[Index] == '+') {
//         Index++;
//     }
//     return(LooksLikeAnUnsignedInteger(&IntegerString[Index]));
}
//-------------------------------------------------------------------------------------------------
int LooksLikeAnUnsignedInteger(char * UnsignedIntegerString) {

    if (*UnsignedIntegerString == '-' || *UnsignedIntegerString == '+') {
        return(0);
    } else {
        return(LooksLikeAnInteger(UnsignedIntegerString));
    }
//----Doing it by hand
//     unsigned int Index;
// 
//     Index = 0;
//     while (Index < strlen(UnsignedIntegerString)) {
//         if (! isdigit(UnsignedIntegerString[Index])) {
//             return(0);
//         }
//         Index++;
//     }
//     return(1);
}
//-------------------------------------------------------------------------------------------------
int LooksLikeARational(char * RationalString) {

    char * Slash;
    SuperString CopyOfRationalString;

    strcpy(CopyOfRationalString,RationalString);
    if ((Slash = strchr(CopyOfRationalString,'/')) != NULL) {
        *Slash = '\0';
        return(LooksLikeAnInteger(CopyOfRationalString) && LooksLikeAnUnsignedInteger(Slash+1));
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int LooksLikeANumber(char * NumberString) {

    return(LooksLikeAnInteger(NumberString) || LooksLikeARational(NumberString) || 
LooksLikeAReal(NumberString));
}
//-------------------------------------------------------------------------------------------------
int IsMathPredicate(char * Symbol,int Arity) {

    char* MathPredicates[] = {
        "$less/2",
        "$lesseq/2",
        "$greater/2",
        "$greatereq/2",
        "$is_int/1",
        "$is_rat/1" };
    SuperString LookFor;
    int Index;

    sprintf(LookFor,"%s/%d",Symbol,Arity);
    for (Index=0; Index < sizeof(MathPredicates)/sizeof(char*);Index++) {
        if (!strcmp(LookFor,MathPredicates[Index])) {
            return(1);
        }
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int IsMathFunctor(char * Symbol,int Arity) {

    char* MathFunctors[] = {
        "$uminus/1",
        "$sum/2",
        "$difference/2",
        "$product/2",
        "$quotient/2",
        "$quotient_e/2",
        "$quotient_t/2",
        "$quotient_f/2",
        "$remainder_e/2",
        "$remainder_t/2",
        "$remainder_f/2",
        "$floor/1",
        "$ceiling/1",
        "$truncate/1",
        "$round/1",
        "$to_int/1",
        "$to_rat/1",
        "$to_real/1" };
    SuperString LookFor;
    int Index;

    sprintf(LookFor,"%s/%d",Symbol,Arity);
    for (Index=0; Index < sizeof(MathFunctors)/sizeof(char*);Index++) {
        if (!strcmp(LookFor,MathFunctors[Index])) {
            return(1);
        }
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int IsMathType(char * Symbol) {

    char* MathTypes[] = {
        "$int",
        "$rat",
        "$real" };
    int Index;

    for (Index=0; Index < sizeof(MathTypes)/sizeof(char*);Index++) {
        if (!strcmp(Symbol,MathTypes[Index])) {
            return(1);
        }
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int LooksLikeAList(TERM Term,int MinElements,int MaxElements) {

    if (Term == NULL) {
        CodingError("Check if NULL term is a list");
    }

    return(Term->Type != variable && !strcmp(GetSymbol(Term),"[]") &&
(MinElements == -1 || GetArity(Term) >= MinElements) && 
(MaxElements == -1 || GetArity(Term) <= MaxElements));
}
//-------------------------------------------------------------------------------------------------
int CheckRole(StatusType Role,StatusType DesiredRole) {

     return(Role == DesiredRole || 
(DesiredRole == axiom_like && 
 (Role == axiom || Role == hypothesis || Role == definition || Role == lemma || 
  Role == theorem || Role == corollary || Role == external)) || 
(DesiredRole == logical && 
 (Role == assumption || Role == axiom || Role == hypothesis || Role == definition ||
  Role == lemma || Role == theorem || Role == corollary || Role == conjecture ||
  Role == question || Role == negated_conjecture || Role == plain || Role == answer ||
  Role == type || Role == fi_domain || Role == fi_functors || Role == fi_predicates ||
  Role == interpretation)) ||
//----Note: assumptions are not axiom_like
(DesiredRole == not_conjecture && Role != conjecture && 
Role != negated_conjecture && Role != question));
}
//-------------------------------------------------------------------------------------------------
int CheckAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,SyntaxType ExpectedSyntax) {

    return(AnnotatedFormula != NULL && AnnotatedFormula->Syntax == ExpectedSyntax &&
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables != NULL);
}
//-------------------------------------------------------------------------------------------------
int LogicalAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

    return(
CheckAnnotatedFormula(AnnotatedFormula,tptp_thf) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_tff) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_tcf) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf));
}
//-------------------------------------------------------------------------------------------------
int LogicalAnnotatedFormulaWithRole(ANNOTATEDFORMULA AnnotatedFormula,StatusType DesiredRole) {

    return(LogicalAnnotatedFormula(AnnotatedFormula) && 
CheckRole(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status,DesiredRole));
}
//-------------------------------------------------------------------------------------------------
int TPIAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

    return(CheckAnnotatedFormula(AnnotatedFormula,tptp_tpi));
}
//-------------------------------------------------------------------------------------------------
int ReallyAnAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

    return(LogicalAnnotatedFormula(AnnotatedFormula) || TPIAnnotatedFormula(AnnotatedFormula));
}
//-------------------------------------------------------------------------------------------------
int CopiedAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

//----Logical
    return(LogicalAnnotatedFormula(AnnotatedFormula) &&
//----Has a source
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source != NULL && 
//----Source is a single word, not "unknown", i.e., a node name
GetArity(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source) == 0 &&
strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),"unknown"));
}
//-------------------------------------------------------------------------------------------------
int InferredAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

//DEBUG printf("logical %d\n",LogicalAnnotatedFormula(AnnotatedFormula));
//DEBUG printf("has source %d\n",AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source != NULL);
//DEBUG printf("is inference %d\n",!strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
//DEBUG Source),"inference"));
//DEBUG printf("arity 3 is %d\n",GetArity(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source) == 3);
//----Logical
    return(LogicalAnnotatedFormula(AnnotatedFormula) &&
//----Has a source
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source != NULL && 
//----Source is inference
!strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Source),"inference") &&
GetArity(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source) 
== 3);
}
//-------------------------------------------------------------------------------------------------
int DerivedAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

//----Logical
    return(CopiedAnnotatedFormula(AnnotatedFormula) || InferredAnnotatedFormula(AnnotatedFormula));
}
//-------------------------------------------------------------------------------------------------
int NestedFormulaType(TermType TheType,int IncludeNestedTerms) {

    return(TheType == nested_thf || TheType == nested_tff || TheType == nested_tcf ||
TheType == nested_fof || TheType == nested_cnf || 
(IncludeNestedTerms && TheType == nested_fot));
}
//-------------------------------------------------------------------------------------------------
//----Extract the contents of a term (wot's in the ()s)
int ExtractTermArguments(String Term) {

    char * Open;
    char * Close;
    String Arguments;

    if ((Open = strchr(Term,'(')) != NULL && (Close = strrchr(Term,')')) != NULL) {
        *Close = '\0';
        strcpy(Arguments,Open+1);
        strcpy(Term,Arguments);
        return(1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * TSTPTermToString(TERM Term,char * PutTermHere) {

    char * Part;
    int Index;
    int Arity;
    String OpeningBracket,ClosingBracket;
    char * Buffer;
    int BufferSize;

//----Build in malloced memory
    Buffer = (char *)Malloc(sizeof(String));
    Buffer[0] = '\0';
    BufferSize = sizeof(String);

//----Check if infix - or : (see also PrintTSTPTerm in PrintTSTP.c)
//----No need to worry about infix equality here - only for non_logical_data
    if (!strcmp(GetSymbol(Term),"-") || !strcmp(GetSymbol(Term),":")) {
        Part = TSTPTermToString(Term->Arguments[0],NULL);
        ExtendString(&Buffer,Part,&BufferSize);
        Free((void **)&Part);
        ExtendString(&Buffer,GetSymbol(Term),&BufferSize);
        Part = TSTPTermToString(Term->Arguments[1],NULL);
        ExtendString(&Buffer,Part,&BufferSize);
        Free((void **)&Part);
    } else {
//----Check if a list
        if (!strcmp(GetSymbol(Term),"[]")) {
            strcpy(OpeningBracket,"[");
            strcpy(ClosingBracket,"]");
        } else {
            ExtendString(&Buffer,GetSymbol(Term),&BufferSize);
            strcpy(OpeningBracket,"(");
            strcpy(ClosingBracket,")");
        }
        
        if ((Arity = GetArity(Term)) > 0 || !strcmp(OpeningBracket,"[")) {
            ExtendString(&Buffer,OpeningBracket,&BufferSize);
            if (Arity > 0) {
                Part = TSTPTermToString(Term->Arguments[0],NULL);
                ExtendString(&Buffer,Part,&BufferSize);
                Free((void **)&Part);
                for (Index=1;Index < Arity;Index++) {
                    ExtendString(&Buffer,",",&BufferSize);
                    Part = TSTPTermToString(Term->Arguments[Index],NULL);
                    ExtendString(&Buffer,Part,&BufferSize);
                    Free((void **)&Part);
                }
            }
            ExtendString(&Buffer,ClosingBracket,&BufferSize);
        }
    }
//----Check if user provided memory or not
    if (PutTermHere != NULL) {
        strcpy(PutTermHere,Buffer);
        Free((void **)&Buffer);
        return(PutTermHere);
    } else {
        return(Buffer);
    }
}
//-------------------------------------------------------------------------------------------------
int CountSimpleUsageInTERMArray(int NumberOfElements,TERMArray Terms,int (*CountFunction)(TERM)) {

    int ElementNumber;
    int Total;

    Total = 0;
    if (NumberOfElements > 0 && Terms != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            Total += (*CountFunction)(Terms[ElementNumber]);
        }
    }
    return(Total);
}
//-------------------------------------------------------------------------------------------------
int CountSimpleUsageInFORMULATERMArray(int NumberOfElements,TERMArray Terms,
int (*CountFunction)(FORMULA)) {

    int ElementNumber;
    int Total;

    Total = 0;
    if (NumberOfElements > 0 && Terms != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            Total += (*CountFunction)(Terms[ElementNumber]->TheSymbol.Formula);
        }
    }
    return(Total);
}
//-------------------------------------------------------------------------------------------------
int CountSimpleUsageInFORMULAArray(int NumberOfElements,FORMULAArray Formulae,
int (*CountFunction)(FORMULA)) {

    int ElementNumber;
    int Total;

    Total = 0;
    if (NumberOfElements > 0 && Formulae != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            Total += (*CountFunction)(Formulae[ElementNumber]);
        }
    }
    return(Total);
}
//-------------------------------------------------------------------------------------------------
int CountVariableUsageInTERMArray(int NumberOfElements,TERMArray Terms,VARIABLENODE Variable) {

    int Count;
    int Index;

    Count = 0;
    if (NumberOfElements > 0 && Terms != NULL) {
        for (Index = 0;Index<NumberOfElements;Index++) {
            Count += CountVariableUsageInTerm(Terms[Index],Variable);
        }
    }
    return(Count);
}
//-------------------------------------------------------------------------------------------------
int CountVariableUsageInTerm(TERM Term,VARIABLENODE Variable) {

    int LocalQuantifiedUsage;
    String ErrorMessage;

    switch (Term->Type) {
        case variable:
            return(Term->TheSymbol.Variable == Variable ? 1 : 0);
            break;
        case function:
        case atom_as_term:
            return(CountVariableUsageInTERMArray(GetArity(Term),GetArguments(Term),Variable));
            break;
        case formula:
            return(CountVariableUsageInFormula(Term->TheSymbol.Formula,Variable,
&LocalQuantifiedUsage));
            break;
        default:
            sprintf(ErrorMessage,"Bad term type %s for counting variable occurrences",
TermTypeToString(Term->Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int CountVariableUsageInTuple(int NumberOfElements,FORMULAArray TupleFormulae,
VARIABLENODE Variable,int * QuantifiedOccurrences) {

    int ElementNumber;
    int TotalUsage;
    int LocalQuantifiedUsage;

    *QuantifiedOccurrences = 0;
    TotalUsage = 0;
    LocalQuantifiedUsage = 0;
    if (NumberOfElements > 0 && TupleFormulae != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            TotalUsage += CountVariableUsageInFormula(TupleFormulae[ElementNumber],Variable,
&LocalQuantifiedUsage);
            *QuantifiedOccurrences += LocalQuantifiedUsage;
        }
    }
    return(TotalUsage);
}
//-------------------------------------------------------------------------------------------------
int CountVariableUsageInFormula(FORMULA Formula,VARIABLENODE Variable,
int * QuantifiedOccurrences) {

    int LocalQuantifiedOccurrences;
    int LocalQuantifiedOccurrences2;
    int LocalCount;

    LocalQuantifiedOccurrences = 0;
    LocalQuantifiedOccurrences2 = 0;

    switch (Formula->Type) {
        case sequent:
            LocalCount = CountVariableUsageInTuple(
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,Formula->FormulaUnion.SequentFormula.LHS,
Variable,&LocalQuantifiedOccurrences);
            LocalCount += CountVariableUsageInTuple(
Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,Formula->FormulaUnion.SequentFormula.RHS,
Variable,&LocalQuantifiedOccurrences2);
            LocalQuantifiedOccurrences += LocalQuantifiedOccurrences2;
            break;
        case quantified:
            LocalCount = CountVariableUsageInFormula(
Formula->FormulaUnion.QuantifiedFormula.Formula,Variable,&LocalQuantifiedOccurrences);
            if (Formula->FormulaUnion.QuantifiedFormula.Variable->TheSymbol.Variable == Variable) {
                LocalQuantifiedOccurrences++;
            }
            break;
        case binary:
            LocalCount = CountVariableUsageInFormula(
Formula->FormulaUnion.BinaryFormula.LHS,Variable,&LocalQuantifiedOccurrences);
            LocalCount += CountVariableUsageInFormula(
Formula->FormulaUnion.BinaryFormula.RHS,Variable,&LocalQuantifiedOccurrences2);
            LocalQuantifiedOccurrences += LocalQuantifiedOccurrences2;
            break;
        case unary:
            LocalCount = CountVariableUsageInFormula(
Formula->FormulaUnion.UnaryFormula.Formula,Variable,&LocalQuantifiedOccurrences);
            break;
        case atom:
        case applied_connective:
            LocalCount = CountVariableUsageInTerm(Formula->FormulaUnion.Atom,Variable);
            break;
        case ite_formula:
            LocalCount = CountVariableUsageInFormula(Formula->FormulaUnion.
ConditionalFormula.Condition,Variable,&LocalQuantifiedOccurrences);
            LocalCount += CountVariableUsageInFormula(Formula->FormulaUnion.
ConditionalFormula.FormulaIfTrue,Variable,&LocalQuantifiedOccurrences);
            LocalCount += CountVariableUsageInFormula(Formula->FormulaUnion.
ConditionalFormula.FormulaIfFalse,Variable,&LocalQuantifiedOccurrences);
            break;
        case let_formula:
            LocalCount = CountVariableUsageInFormula(Formula->FormulaUnion.LetFormula.LetBody,
Variable,&LocalQuantifiedOccurrences);
            break;
        default:
            LocalCount = 0;
            CodingError("Unknown formula type in count variables usage");
            break;
    }
    if (LocalQuantifiedOccurrences > 1) {
        CodingError("Multiply quantified variable");
    }
    if (QuantifiedOccurrences != NULL) {
        *QuantifiedOccurrences = LocalQuantifiedOccurrences;
    }

    return(LocalCount);
}
//-------------------------------------------------------------------------------------------------
void NormalizeSymbolUsage(char * SymbolUsage) {

    SYMBOLNODE Head;
    SYMBOLNODE Searcher;
    char * Triple;
    char * TripleLast;
    char * Functor;
    int Arity,Uses;
    SuperString NextTriple;
    char * Slash;

    Head = NULL;
    TripleLast = NULL;
    Triple = strtok_r(SymbolUsage,"\n",&TripleLast);
    while (Triple != NULL) {
//----Have to search backwards to avoid / in rationals
        Slash = strrchr(Triple,'/');
        *Slash = '\0';
        Slash++;
        Uses = atoi(Slash);
        Slash = strrchr(Triple,'/');
        *Slash = '\0';
        Slash++;
        Arity = atoi(Slash);
        Functor = Triple;
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
//-------------------------------------------------------------------------------------------------
void CollectSymbolsInArguments(int Arity,TERMArray Arguments,char ** PredicateCollector,
int * PredicateCollectorLength,char ** FunctorCollector,int * FunctorCollectorLength,
char ** VariableCollector,int * VariableCollectorLength,char ** TypeCollector,
int * TypeCollectorLength) {

    int ArgumentNumber;

//----Arguments could be null when duplicating the type declaration of a symbol
    if (Arity > 0 && Arguments != NULL) {
        for (ArgumentNumber=0;ArgumentNumber<Arity;ArgumentNumber++) {
            CollectSymbolsInTerm(Arguments[ArgumentNumber],PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
        }
//DEBUG printf("args:\nP:%sF:%sV:%sT:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector,*TypeCollector);
    }
}
//-------------------------------------------------------------------------------------------------
void CollectSymbolsInTerm(TERM Term,char ** PredicateCollector,int * PredicateCollectorLength,
char ** FunctorCollector,int * FunctorCollectorLength,char ** VariableCollector,
int * VariableCollectorLength,char ** TypeCollector,int * TypeCollectorLength) {

    SuperString TermData;
    String ErrorMessage;

    switch (Term->Type) {
        case connective:
            sprintf(TermData,"%s/0/1\n",GetSymbol(Term));
            ExtendString(PredicateCollector,TermData,PredicateCollectorLength);
            break;
        case atom_as_term:
        case function:
//TODO
            if (strcmp(GetSymbol(Term),"()")) {
                sprintf(TermData,"%s/%d/1\n",GetSymbol(Term),GetArity(Term));
                if (Term->Type == atom_as_term) {
                    ExtendString(PredicateCollector,TermData,PredicateCollectorLength);
                } else {
                    ExtendString(FunctorCollector,TermData,FunctorCollectorLength);
                }
            }
//DEBUG printf("principle:\nP:%sF:%sV:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector);
            CollectSymbolsInArguments(GetArity(Term),Term->Arguments,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
//DEBUG printf("predfun:\nP:%sF:%sV:%sT:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector,*TypeCollector);
            break;
        case a_type:
            sprintf(TermData,"%s/0/1\n",GetSymbol(Term));
            ExtendString(TypeCollector,TermData,TypeCollectorLength);
            break;
        case variable:
            sprintf(TermData,"%s/0/1\n",GetSymbol(Term));
            ExtendString(VariableCollector,TermData,VariableCollectorLength);
//DEBUG printf("var:\nP:%sF:%sV:%sT:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector,*TypeCollector);
            break;
        case formula:
            CollectSymbolsInFormula(Term->TheSymbol.Formula,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
            break;
//DEBUG printf("termform:\nP:%sF:%sV:%sT:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector,TypeCollector);
        default:
            sprintf(ErrorMessage,"Unknown term type %s for collecting symbols",
TermTypeToString(Term->Type));
            CodingError(ErrorMessage);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
//----PutUsageHere must be address of a malloced String
char * GetLiteralSymbolUsage(FORMULA Literal,char ** PutUsageHere,char ** VariablesStartHere) {

    char Sign;
    char * FunctorCollector;
    char * VariableCollector;
    char * TypeCollector;
    int UsageLength = STRINGLENGTH;
    int FunctorCollectorLength;
    int VariableCollectorLength;
    int TypeCollectorLength;

    strcpy(*PutUsageHere,"");
    if (Literal == NULL) {
        return(NULL);
    } else if (Literal->Type == unary && 
Literal->FormulaUnion.UnaryFormula.Connective == negation) {
        Sign = '~';
        Literal = Literal->FormulaUnion.UnaryFormula.Formula;
    } else if (Literal->Type == atom || 
(Literal->Type == binary && Literal->FormulaUnion.BinaryFormula.Connective == equation)) {
        Sign = ' ';
    } else {
        return(NULL);
    }

    sprintf(*PutUsageHere,"%c",Sign);

    FunctorCollector = (char *)Malloc(sizeof(String));
    FunctorCollectorLength = STRINGLENGTH;
    strcpy(FunctorCollector,"");
    VariableCollector = (char *)Malloc(sizeof(String));
    VariableCollectorLength = STRINGLENGTH;
    strcpy(VariableCollector,"");
    TypeCollector = (char *)Malloc(sizeof(String));
    TypeCollectorLength = STRINGLENGTH;
    strcpy(TypeCollector,"");
    CollectSymbolsInFormula(Literal,PutUsageHere,&UsageLength,&FunctorCollector,
&FunctorCollectorLength,&VariableCollector,&VariableCollectorLength,&TypeCollector,
&TypeCollectorLength);
    NormalizeSymbolUsage(*PutUsageHere);
    NormalizeSymbolUsage(FunctorCollector);
    NormalizeSymbolUsage(VariableCollector);
    NormalizeSymbolUsage(TypeCollector);
    ExtendString(PutUsageHere,FunctorCollector,&UsageLength);
//----Collect variables if not a NULL start pointer
    if (VariablesStartHere != NULL) {
        *VariablesStartHere = &((*PutUsageHere)[strlen(*PutUsageHere)]);
        ExtendString(PutUsageHere,VariableCollector,&UsageLength);
    }
//----Don't do types for literals
    Free((void **)&FunctorCollector);
    Free((void **)&VariableCollector);
    Free((void **)&TypeCollector);

    return(*PutUsageHere);
}
//-------------------------------------------------------------------------------------------------
void CollectSymbolsInTupleFormulae(int NumberOfElements,FORMULAArray TupleFormulae,
char ** PredicateCollector, int * PredicateCollectorLength,char ** FunctorCollector,
int * FunctorCollectorLength,char ** VariableCollector,int * VariableCollectorLength,
char ** TypeCollector,int * TypeCollectorLength) {

    int ElementNumber;

    if (NumberOfElements > 0 && TupleFormulae != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            CollectSymbolsInFormula(TupleFormulae[ElementNumber],PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
        }
    }
}
//-------------------------------------------------------------------------------------------------
void CollectSymbolsInFormula(FORMULA Formula,char ** PredicateCollector,
int * PredicateCollectorLength,char ** FunctorCollector,int * FunctorCollectorLength,
char ** VariableCollector,int * VariableCollectorLength,char ** TypeCollector,
int * TypeCollectorLength) {

    String ErrorMessage;

    switch (Formula->Type) {
        case sequent:
//DEBUG printf("CollectSymbolsInFormula: sequent");
            CollectSymbolsInTupleFormulae(
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,Formula->FormulaUnion.SequentFormula.LHS,
PredicateCollector,PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,
VariableCollector,VariableCollectorLength,TypeCollector,TypeCollectorLength);
            CollectSymbolsInTupleFormulae(
Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,Formula->FormulaUnion.SequentFormula.RHS,
PredicateCollector,PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,
VariableCollector,VariableCollectorLength,TypeCollector,TypeCollectorLength);
            break;
        case assignment:
            CollectSymbolsInFormula(Formula->FormulaUnion.BinaryFormula.RHS,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
            break;
        case quantified:
//----Add in RHS of : and := variables
//            if (Formula->FormulaUnion.QuantifiedFormula.VariableType != NULL) {
//                CollectSymbolsInFormula(Formula->FormulaUnion.QuantifiedFormula.VariableType,
//PredicateCollector,PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,
//VariableCollector,VariableCollectorLength);
//            }
//printf("types:\nP:%sF:%sV:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector);
            CollectSymbolsInFormula(Formula->FormulaUnion.QuantifiedFormula.Formula,
PredicateCollector,PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,
VariableCollector,VariableCollectorLength,TypeCollector,TypeCollectorLength);
//DEBUG printf("quantified:\nP:%sF:%sV:%sT%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector,*TypeCollector);
            break;
//----This is so broken now, because I don't know if predicate or functor. Should use signature
        case type_declaration:
            break;
        case binary:
            CollectSymbolsInFormula(Formula->FormulaUnion.BinaryFormula.LHS,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
//DEBUG printf("binary LHS:\nP:%sF:%sV:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector);
            CollectSymbolsInFormula(Formula->FormulaUnion.BinaryFormula.RHS,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
//DEBUG printf("binary ALL:\nP:%sF:%sV:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector);
            break;
        case unary:
            CollectSymbolsInFormula(Formula->FormulaUnion.UnaryFormula.Formula,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
//DEBUG printf("unary:\nP:%sF:%sV:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector);
            break;
        case atom:
        case applied_connective:
//            if (strcmp(GetSymbol(Formula->FormulaUnion.Atom),"$true") &&
//strcmp(GetSymbol(Formula->FormulaUnion.Atom),"$false")) {
            CollectSymbolsInTerm(Formula->FormulaUnion.Atom,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
//DEBUG printf("atom:\nP:%sF:%sV:%s\n",*PredicateCollector,*FunctorCollector,*VariableCollector);
            break;
        case tuple:
            CollectSymbolsInTupleFormulae(Formula->FormulaUnion.TupleFormula.NumberOfElements,
Formula->FormulaUnion.TupleFormula.Elements,PredicateCollector,PredicateCollectorLength,
FunctorCollector,FunctorCollectorLength,VariableCollector,VariableCollectorLength,TypeCollector,
TypeCollectorLength);
            break;
        case ite_formula:
//DEBUG printf("CollectSymbolsInFormula: ite_formula");
            CollectSymbolsInFormula(Formula->FormulaUnion.ConditionalFormula.Condition,
PredicateCollector,PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,
VariableCollector,VariableCollectorLength,TypeCollector,TypeCollectorLength);
            CollectSymbolsInFormula(Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue,
PredicateCollector,PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,
VariableCollector,VariableCollectorLength,TypeCollector,TypeCollectorLength);
            CollectSymbolsInFormula(Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse,
PredicateCollector,PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,
VariableCollector,VariableCollectorLength,TypeCollector,TypeCollectorLength);
            break;
        case let_formula:
            CollectSymbolsInFormula(Formula->FormulaUnion.LetFormula.LetDefn,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
            CollectSymbolsInFormula(Formula->FormulaUnion.LetFormula.LetBody,PredicateCollector,
PredicateCollectorLength,FunctorCollector,FunctorCollectorLength,VariableCollector,
VariableCollectorLength,TypeCollector,TypeCollectorLength);
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for counting atoms",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
//----PutUsageHere must be address of a malloced String
char * GetFormulaSymbolUsage(FORMULA Formula,char ** PutUsageHere,char ** FunctorUsageStartsHere,
char ** VariableUsageStartsHere,char **TypeUsageStartsHere) {

    char * PredicateCollector;
    char * FunctorCollector;
    char * VariableCollector;
    char * TypeCollector;
    int UsageLength = STRINGLENGTH;
    int PredicateCollectorLength = STRINGLENGTH;
    int FunctorCollectorLength = STRINGLENGTH;
    int VariableCollectorLength = STRINGLENGTH;
    int TypeCollectorLength = STRINGLENGTH;
    int PredicateLength;
    int FunctorLength;
    int VariableLength;

//DEBUG printf("PROGRESS: Allocate memory for GetFormulaSymbolUsage\n");
    PredicateCollector = (char *)Malloc(sizeof(String));
    strcpy(PredicateCollector,"");
    FunctorCollector = (char *)Malloc(sizeof(String));
    strcpy(FunctorCollector,"");
    VariableCollector = (char *)Malloc(sizeof(String));
    strcpy(VariableCollector,"");
    TypeCollector = (char *)Malloc(sizeof(String));
    strcpy(TypeCollector,"");
    CollectSymbolsInFormula(Formula,&PredicateCollector,&PredicateCollectorLength,
&FunctorCollector,&FunctorCollectorLength,&VariableCollector,&VariableCollectorLength,
&TypeCollector,&TypeCollectorLength);
//DEBUG printf("Predicates:\n%s\n",PredicateCollector);
//DEBUG printf("Functors  :\n%s\n",FunctorCollector);
//DEBUG printf("Variables :\n%s\n",VariableCollector);
//DEBUG printf("Types  :\n%s\n",TypeCollector);

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
    VariableLength = strlen(VariableCollector);
    ExtendString(PutUsageHere,VariableCollector,&UsageLength);
    Free((void **)&VariableCollector);

    NormalizeSymbolUsage(TypeCollector);
    ExtendString(PutUsageHere,TypeCollector,&UsageLength);
    Free((void **)&TypeCollector);

    *FunctorUsageStartsHere = *PutUsageHere + PredicateLength;
    *VariableUsageStartsHere = *FunctorUsageStartsHere + FunctorLength;
    *TypeUsageStartsHere = *VariableUsageStartsHere + VariableLength;

    return(*PutUsageHere);
}
//-------------------------------------------------------------------------------------------------
//----PutUsageHere must be address of a malloced String
char * GetAnnotatedFormulaSymbolUsage(ANNOTATEDFORMULA AnnotatedTSTPFormula,char ** PutUsageHere,
char ** FunctorUsageStartsHere,char ** VariableUsageStartsHere,char ** TypeUsageStartsHere) {

    char * Result;

//----Ignore comments
    if (LogicalAnnotatedFormula(AnnotatedTSTPFormula)) {
        if ((Result = GetFormulaSymbolUsage(
AnnotatedTSTPFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
PutUsageHere,FunctorUsageStartsHere,VariableUsageStartsHere,TypeUsageStartsHere)) != NULL) {
            return(Result);
        } else {
            return(NULL);
        }
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
//----PutUsageHere must be address of a malloced String or pointer to NULL
char * GetListOfAnnotatedFormulaSymbolUsage(LISTNODE ListNode,char ** PutUsageHere,
char ** FunctorUsageStartsHere,char ** VariableUsageStartsHere,char ** TypeUsageStartsHere) {

    char * PredicateCollector;
    char * FunctorCollector;
    char * VariableCollector;
    char * TypeCollector;
    char * OneUsage;
    char * FunctorsStart;
    char * VariablesStart;
    char * TypesStart;
    int UsageLength = STRINGLENGTH;
    int PredicateCollectorLength = STRINGLENGTH;
    int FunctorCollectorLength = STRINGLENGTH;
    int VariableCollectorLength = STRINGLENGTH;
    int TypeCollectorLength = STRINGLENGTH;

//DEBUG printf("PROGRESS: Allocate memory\n");
//----Initialize PutUsageHere if not done already
    if (*PutUsageHere == NULL) {
        *PutUsageHere = (char *)Malloc(sizeof(String));
        strcpy(*PutUsageHere,"");
    }

//----Collect predicates and functors
    PredicateCollector = (char *)Malloc(sizeof(String));
    strcpy(PredicateCollector,"");
    FunctorCollector = (char *)Malloc(sizeof(String));
    strcpy(FunctorCollector,"");
    VariableCollector = (char *)Malloc(sizeof(String));
    strcpy(VariableCollector,"");
    TypeCollector = (char *)Malloc(sizeof(String));
    strcpy(TypeCollector,"");

//DEBUG printf("PROGRESS: Allocated memory\n");
    while (ListNode != NULL) {
        OneUsage = (char *)Malloc(sizeof(String));
        strcpy(OneUsage,"");
        if (GetAnnotatedFormulaSymbolUsage(ListNode->AnnotatedFormula,&OneUsage,&FunctorsStart,
&VariablesStart,&TypesStart) != NULL) {
            ExtendString(&TypeCollector,TypesStart,&TypeCollectorLength);
            *TypesStart = '\0';
            ExtendString(&VariableCollector,VariablesStart,&VariableCollectorLength);
            *VariablesStart = '\0';
            ExtendString(&FunctorCollector,FunctorsStart,&FunctorCollectorLength);
            *FunctorsStart = '\0';
            ExtendString(&PredicateCollector,OneUsage,&PredicateCollectorLength);
        }
        Free((void **)&OneUsage);
        ListNode = ListNode->Next;
    }
//DEBUG printf("PROGRESS: Done nodes\n");

    strcpy(*PutUsageHere,"");
//DEBUG printf("Collected predicates\n%s\n",PredicateCollector);
    NormalizeSymbolUsage(PredicateCollector);
//DEBUG printf("Normalized predicates\n%s\n",PredicateCollector);
    ExtendString(PutUsageHere,PredicateCollector,&UsageLength);
    PredicateCollectorLength = strlen(*PutUsageHere);
    Free((void **)&PredicateCollector);
//DEBUG printf("PROGRESS: Normalized predicates\n");

//DEBUG printf("Collected functors\n%s\n",FunctorCollector);
    NormalizeSymbolUsage(FunctorCollector);
//DEBUG printf("Normalized functors\n%s\n",FunctorCollector);
    ExtendString(PutUsageHere,FunctorCollector,&UsageLength);
    *FunctorUsageStartsHere = (*PutUsageHere) + PredicateCollectorLength;
    Free((void **)&FunctorCollector);
//DEBUG printf("PROGRESS: Normalized functors\n");

//DEBUG printf("Collected variables\n%s\n",VariableCollector);
    NormalizeSymbolUsage(VariableCollector);
//DEBUG printf("Normalized variables\n%s\n",VariableCollector);
    ExtendString(PutUsageHere,VariableCollector,&UsageLength);
    *VariableUsageStartsHere = (*PutUsageHere) + PredicateCollectorLength + FunctorCollectorLength;
    Free((void **)&VariableCollector);
//DEBUG printf("PROGRESS: Normalized variables\n");

//DEBUG printf("Collected types\n%s\n",TypeCollector);
    NormalizeSymbolUsage(TypeCollector);
//DEBUG printf("Normalized functors\n%s\n",FunctorCollector);
    ExtendString(PutUsageHere,TypeCollector,&UsageLength);
    *TypeUsageStartsHere = (*PutUsageHere) + PredicateCollectorLength + FunctorCollectorLength +
+ VariableCollectorLength;
    Free((void **)&TypeCollector);
//DEBUG printf("PROGRESS: Normalized types\n");

    return(*PutUsageHere);
}
//-------------------------------------------------------------------------------------------------
//----PutPositivesHere and PutNegativesHere must be addresses of malloced empty strings
void CollectVariablesOfPolarity(FORMULA DisjunctionOrLiteral,char ** PutPositivesHere,
int * PositivesLength,char ** PutNegativesHere,int * NegativesLength) {

    char * LiteralSymbols;
    char * LiteralVariables;
    String ErrorMessage;

    if (DisjunctionOrLiteral == NULL) {
        return;
    }

    switch (DisjunctionOrLiteral->Type) {
        case quantified:
            CollectVariablesOfPolarity(DisjunctionOrLiteral->FormulaUnion.QuantifiedFormula.Formula,
PutPositivesHere,PositivesLength,PutNegativesHere,NegativesLength);
            break;
        case binary:
            if (DisjunctionOrLiteral->FormulaUnion.BinaryFormula.Connective != equation) {
                CollectVariablesOfPolarity(DisjunctionOrLiteral->FormulaUnion.BinaryFormula.LHS,
PutPositivesHere,PositivesLength,PutNegativesHere,NegativesLength);
                CollectVariablesOfPolarity(DisjunctionOrLiteral->FormulaUnion.BinaryFormula.RHS,
PutPositivesHere,PositivesLength,PutNegativesHere,NegativesLength);
//----Oh my goodness, what a bit of trickery for TXF. If an equation then head on down to atom
                break;
            }
        case unary:
        case atom:
        case applied_connective:
            LiteralSymbols = (char *)Malloc(sizeof(String));
            if (GetLiteralSymbolUsage(DisjunctionOrLiteral,&LiteralSymbols,&LiteralVariables) !=
NULL) {
                if (DisjunctionOrLiteral->Type == unary) {
                    ExtendString(PutNegativesHere,LiteralVariables,NegativesLength);
                } else {
                    ExtendString(PutPositivesHere,LiteralVariables,PositivesLength);
                }
            } else {
                CodingError("Cannot get literal symbol usage");
            }
            Free((void **)&LiteralSymbols);
            break;
        default:
            sprintf(ErrorMessage,"Cannot collect clause statistics for a %s",
FormulaTypeToString(DisjunctionOrLiteral->Type));
            CodingError(ErrorMessage);
            break;
    }
    NormalizeSymbolUsage(*PutPositivesHere);
    NormalizeSymbolUsage(*PutNegativesHere);
}
//-------------------------------------------------------------------------------------------------
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
//----GetListSymbolUsageStatistics the old non-signature way is broken for typed things
// !CheckAnnotatedFormula(AnnotatedFormula,tptp_tcf)) {
        return(0);
    }

    PutPositivesHere = (char *)Malloc(sizeof(SuperString));
    strcpy(PutPositivesHere,"");
    PositivesLength = STRINGLENGTH;
    PutNegativesHere = (char *)Malloc(sizeof(SuperString));
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
            CodingError("No slash in variable information");
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
//-------------------------------------------------------------------------------------------------
int CountFormulaLiteralsOfPolarity(FORMULA DisjunctionOrLiteral,int Sign) {

    String ErrorMessage;

    if (DisjunctionOrLiteral == NULL) {
        return(0);
    }

    switch (DisjunctionOrLiteral->Type) {
        case quantified:
            return(CountFormulaLiteralsOfPolarity(
DisjunctionOrLiteral->FormulaUnion.QuantifiedFormula.Formula,Sign));
            break;
        case binary:
            return(
CountFormulaLiteralsOfPolarity(DisjunctionOrLiteral->FormulaUnion.BinaryFormula.LHS,Sign) +
CountFormulaLiteralsOfPolarity(DisjunctionOrLiteral->FormulaUnion.BinaryFormula.RHS,Sign));
            break;
        case unary:
            if (Sign == -1) {
                return(1);
            } else {
                return(0);
            }
            break;
        case atom:
        case applied_connective:
            if (Sign ==  1) {
                 return(1);
            } else {
                return(0);
            }
            break;
        default:
            sprintf(ErrorMessage,"Cannot collect clause polarity for a %s",
FormulaTypeToString(DisjunctionOrLiteral->Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
int GetSymbolUses(SIGNATURE Signature,TermType Type,char * Name,int Arity) {

    SYMBOLNODE List;
    SYMBOLNODE SymbolNode;
    String ErrorMessage;

    switch (Type) {
        case atom_as_term:
            List = Signature->Predicates;
            break;
        case function:
            List = Signature->Functions;
            break;
        case a_type:
            List = Signature->Types;
            break;
        case variable:
            List = Signature->Variables;
            break;
        default:
            sprintf(ErrorMessage,"Unknown type %s for GetSymbolUses",TermTypeToString(Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }

    if ((SymbolNode = IsSymbolInSignatureList(List,Name,Arity,NULL)) != NULL) {
        return(GetSignatureUses(SymbolNode));
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int CountLiteralsOfPolarity(ANNOTATEDFORMULA AnnotatedFormula,int * Positive,
int * Negative) {

    FORMULA DisjunctionOrLiteral;

    if (!CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf) &&
!CheckAnnotatedFormula(AnnotatedFormula,tptp_tcf)) {
        return(0);
    }

    DisjunctionOrLiteral = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula;
    *Positive = CountFormulaLiteralsOfPolarity(DisjunctionOrLiteral,1);
    *Negative = CountFormulaLiteralsOfPolarity(DisjunctionOrLiteral,-1);
    return(1);
}
//-------------------------------------------------------------------------------------------------
int HornClause(ANNOTATEDFORMULA AnnotatedFormula) {

    int Positive,Negative;

    return(CountLiteralsOfPolarity(AnnotatedFormula,&Positive,&Negative) && Positive <= 1);
}
//-------------------------------------------------------------------------------------------------
int NonHornClause(ANNOTATEDFORMULA AnnotatedFormula) {

    int Positive,Negative;

    return(CountLiteralsOfPolarity(AnnotatedFormula,&Positive,&Negative) && Positive > 1);
}
//-------------------------------------------------------------------------------------------------
int CountAnnotatedFormulaUniqueVariablesByUse(ANNOTATEDFORMULA AnnotatedFormula,int MinUse,
int MaxUse,ConnectiveType RequiredQuantification) {

    int Counter;
    VARIABLENODE VariableNode;

    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
        Counter = 0;
        VariableNode = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables;
//DEBUG printf("Want MIN %d MAX %d TYPE %s\n",MinUse,MaxUse,RequiredQuantification == universal ? "!" : RequiredQuantification == existential ? "?" : "DUNNO");
        while (VariableNode != NULL) {
//DEBUG printf("Variable %s %s\n",GetSignatureSymbol(VariableNode->VariableName),VariableNode->Quantification == universal ? "!" : VariableNode->Quantification == existential ? "?" : "DUNNO");
            if (
//----Care only about quantified variables, not free, e.g., in $let
//----Now only counting for CNF, so this doesn't apply
// VariableNode->Quantification != none && VariableNode->Quantification != free_variable &&
//----Usage constraint
(MinUse < 0 || MaxUse < MinUse || 
 (VariableNode->NumberOfUses >= MinUse && VariableNode->NumberOfUses <= MaxUse)) && 
//----Quantification constraint
(RequiredQuantification == none || VariableNode->Quantification == RequiredQuantification)) {
                Counter++;
//DEBUG printf("That one counts %s\n",GetSignatureSymbol(VariableNode->VariableName));
            }
            VariableNode = VariableNode->NextVariable;
        }
        return(Counter);
    } else {
        return(-1);
    }
}
//-------------------------------------------------------------------------------------------------
int CountAnnotatedFormulaSingletons(ANNOTATEDFORMULA AnnotatedFormula) {

    return(CountAnnotatedFormulaUniqueVariablesByUse(AnnotatedFormula,1,1,none));
}
//-------------------------------------------------------------------------------------------------
int CountAnnotatedFormulaUniqueVariables(ANNOTATEDFORMULA AnnotatedFormula) {

    return(CountAnnotatedFormulaUniqueVariablesByUse(AnnotatedFormula,-1,-1,none));
}
//-------------------------------------------------------------------------------------------------
int CountNestedFormulaeInFormulae(SIGNATURE Signature,int NumberOfElements,FORMULAArray Formulae,
int NestedYet) {

    int ElementNumber;
    int Count;

    Count = 0;
    if (NumberOfElements > 0 && Formulae != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            Count += CountNestedFormulae(Signature,Formulae[ElementNumber],NestedYet);
        }
    }
    return(Count);
}
//-------------------------------------------------------------------------------------------------
int CountNestedFormulaeInTerms(SIGNATURE Signature,int NumberOfElements,TERMArray Terms) {

    int ElementNumber;
    int Count;

    Count = 0;
    if (NumberOfElements > 0 && Terms != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            switch (Terms[ElementNumber]->Type) {
                case formula:
                    Count += CountNestedFormulae(Signature,Terms[ElementNumber]->TheSymbol.Formula,
1);
                    break;
                case atom_as_term:
                case function:
                    Count += CountNestedFormulaeInTerms(Signature,GetArity(Terms[ElementNumber]),
GetArguments(Terms[ElementNumber]));
                    break;
                default:
                    break;
            }
        }
    }
    return(Count);
}
//-------------------------------------------------------------------------------------------------
int CountNestedFormulae(SIGNATURE Signature,FORMULA Formula,int NestedYet) {

    String ErrorMessage;
    int Count;
    
//DEBUG printf("Look at formula with type %s, NestedYet is %d\n",FormulaTypeToString(Formula->Type),NestedYet);
    Count = 0;
    switch (Formula->Type) {
        case sequent:
            Count = NestedYet;
            NestedYet = 0;
            return(Count + CountNestedFormulaeInFormulae(Signature,
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,Formula->FormulaUnion.SequentFormula.LHS,
NestedYet) + CountNestedFormulaeInFormulae(Signature,
Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,Formula->FormulaUnion.SequentFormula.RHS,
NestedYet));
            break;
        case assignment:
            Count = NestedYet;
            NestedYet = 0;
            return(Count + CountNestedFormulae(Signature,Formula->FormulaUnion.BinaryFormula.RHS,
NestedYet));
            break;
        case type_declaration:
            return(0);
            break;
        case quantified:
            Count = NestedYet;
            NestedYet = 0;
            Count += CountNestedFormulae(Signature,Formula->FormulaUnion.QuantifiedFormula.Formula,
NestedYet);
//DEBUG printf("After looking at quantified the count is %d\n",Count);
            return(Count);
            break;
        case binary:
//DEBUG printf("Binary with connective %s\n",ConnectiveToString(Formula->FormulaUnion.BinaryFormula.Connective));
            Count = NestedYet;
            if (Formula->FormulaUnion.BinaryFormula.Connective == equation) {
                NestedYet = 1;
            } else {
                NestedYet = 0;
            }
            return(Count + CountNestedFormulae(Signature,
Formula->FormulaUnion.BinaryFormula.LHS,NestedYet) + CountNestedFormulae(Signature,
Formula->FormulaUnion.BinaryFormula.RHS,NestedYet));
            break;
        case unary:
            Count = NestedYet;
            NestedYet = 0;
            return(Count + CountNestedFormulae(Signature,
Formula->FormulaUnion.UnaryFormula.Formula,NestedYet));
            break;
        case atom:
        case applied_connective:
//DEBUG printf("It's an atom with symbol %s\n",GetSymbol(Formula->FormulaUnion.Atom));
            if (IsSymbolInSignatureList(Signature->Predicates,
GetSymbol(Formula->FormulaUnion.Atom),GetArity(Formula->FormulaUnion.Atom),NULL) != NULL) {
                Count = NestedYet;
                NestedYet = 1;
            }
//DEBUG printf("After looking at the symbol %s the count is %d\n",GetSymbol(Formula->FormulaUnion.Atom),Count);
            Count += CountNestedFormulaeInTerms(Signature,GetArity(Formula->FormulaUnion.Atom),
GetArguments(Formula->FormulaUnion.Atom));
//DEBUG printf("After looking at the arguments of %s the count is %d\n",GetSymbol(Formula->FormulaUnion.Atom),Count);
            return(Count);
            break;
        case tuple:
            NestedYet = 1;
            return(CountNestedFormulaeInFormulae(Signature,
Formula->FormulaUnion.TupleFormula.NumberOfElements,
Formula->FormulaUnion.TupleFormula.Elements,NestedYet));
            break;
        case ite_formula:
            Count = NestedYet;
            NestedYet = 0;
            return(Count + 
CountNestedFormulae(Signature,Formula->FormulaUnion.ConditionalFormula.Condition,NestedYet) +
CountNestedFormulae(Signature,Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue,NestedYet) +
CountNestedFormulae(Signature,Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse,NestedYet));
            break;
        case let_formula:
            Count = NestedYet;
            NestedYet = 0;
            return(Count + CountNestedFormulae(Signature,
Formula->FormulaUnion.LetFormula.LetBody,NestedYet));
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for counting nested formulae",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
int CountVariablesInFormulaeByType(int NumberOfElements,FORMULAArray Formulae,char * Type) {

    int ElementNumber;
    int Count;

    Count = 0;
    if (NumberOfElements > 0 && Formulae != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            Count += CountVariablesInFormulaByType(Formulae[ElementNumber],Type);
        }
    }
    return(Count);
}
//-------------------------------------------------------------------------------------------------
int CountVariablesInTermsByType(int NumberOfElements,TERMArray Terms,char * Type) {

    int ElementNumber;
    int Count;

    Count = 0;
    if (NumberOfElements > 0 && Terms != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            Count += CountArgumentVariablesByType(Terms[ElementNumber],Type);
        }
    }
    return(Count);
}
//-------------------------------------------------------------------------------------------------
int CountArgumentVariablesByType(TERM Term,char * Type)  {

    if (Term->Type == formula) {
        return(CountVariablesInFormulaByType(Term->TheSymbol.Formula,Type));
    } else {
        return(CountVariablesInTermsByType(GetArity(Term),GetArguments(Term),Type));
    }
}
//-------------------------------------------------------------------------------------------------
int CountVariablesInFormulaByType(FORMULA Formula,char * Type) {

    int Count;
    String ErrorMessage;

    Count = 0;
    switch (Formula->Type) {
        case sequent:
            return(CountVariablesInFormulaeByType(
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,Formula->FormulaUnion.SequentFormula.LHS,
Type) + CountVariablesInFormulaeByType(
Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,Formula->FormulaUnion.SequentFormula.RHS,
Type));
            break;
        case assignment:
//TODO - should I count the LHS?
            return(CountVariablesInFormulaByType(Formula->FormulaUnion.BinaryFormula.RHS,Type));
            break;
        case type_declaration:
            return(0);
            break;
        case quantified:
//DEBUG printf("Before content of %s it is %d\n",GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable),Count);
            Count = CountVariablesInFormulaByType(Formula->FormulaUnion.QuantifiedFormula.Formula,
Type);
//DEBUG printf("After content of %s it is %d\n",GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable),Count);
            if (Formula->FormulaUnion.QuantifiedFormula.VariableType != NULL &&
Formula->FormulaUnion.QuantifiedFormula.VariableType->Type == atom &&
!strcmp(GetSymbol(Formula->FormulaUnion.QuantifiedFormula.VariableType->FormulaUnion.Atom),Type)) {
//DEBUG printf("Add %d uses of %s\n",Formula->FormulaUnion.QuantifiedFormula.Variable->TheSymbol.Variable->NumberOfUses - 1,GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
                Count += 
//----One less because quantification use doesn't count
Formula->FormulaUnion.QuantifiedFormula.Variable->TheSymbol.Variable->NumberOfUses - 1;
//DEBUG printf("After %s it is %d\n",GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable),Count);
                return(Count);
            } else {
                return(Count + 0);
            }
            break;
        case binary:
//DEBUG printf("Before LHS of %s it is %d\n",ConnectiveToString(Formula->FormulaUnion.BinaryFormula.Connective),Count);
            Count = CountVariablesInFormulaByType(Formula->FormulaUnion.BinaryFormula.LHS,Type);
//DEBUG printf("After LHS of %s it is %d\n",ConnectiveToString(Formula->FormulaUnion.BinaryFormula.Connective),Count);
            Count += CountVariablesInFormulaByType(Formula->FormulaUnion.BinaryFormula.RHS,Type);
//DEBUG printf("After RHS of %s it is %d\n",ConnectiveToString(Formula->FormulaUnion.BinaryFormula.Connective),Count);
            return(Count);
            break;
        case unary:
            return(CountVariablesInFormulaByType(Formula->FormulaUnion.UnaryFormula.Formula,Type));
            break;
        case atom:
        case applied_connective:
//DEBUG printf("Going to do an atom %s with %d args\n",GetSymbol(Formula->FormulaUnion.Atom),GetArity(Formula->FormulaUnion.Atom));
            Count = CountVariablesInTermsByType(GetArity(Formula->FormulaUnion.Atom),
GetArguments(Formula->FormulaUnion.Atom),Type);
//DEBUG printf("After doing atom %s it is %d\n",GetSymbol(Formula->FormulaUnion.Atom),Count);
            return(Count);
            break;
        case tuple:
            return(CountVariablesInFormulaeByType(
Formula->FormulaUnion.TupleFormula.NumberOfElements,Formula->FormulaUnion.TupleFormula.Elements,
Type));
            break;
        case ite_formula:
            return(
CountVariablesInFormulaByType(Formula->FormulaUnion.ConditionalFormula.Condition,Type) +
CountVariablesInFormulaByType(Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue,Type) +
CountVariablesInFormulaByType(Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse,Type));
            break;
        case let_formula:
            return(CountVariablesInFormulaByType(Formula->FormulaUnion.LetFormula.LetBody,Type));
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for counting atoms",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
int CountFormulaTuples(FORMULA Formula) {

    String ErrorMessage;

    switch (Formula->Type) {
        case sequent:
            return(
CountSimpleUsageInFORMULAArray(Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,
Formula->FormulaUnion.SequentFormula.LHS,&CountFormulaTuples) +
CountSimpleUsageInFORMULAArray(Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,
Formula->FormulaUnion.SequentFormula.RHS,&CountFormulaTuples));
            break;
        case quantified:
            return(CountFormulaTuples(Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case type_declaration:
            return(0);
            break;
        case assignment:
        case binary:
            return(CountFormulaTuples(Formula->FormulaUnion.BinaryFormula.LHS) +
CountFormulaTuples(Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case unary:
            return(CountFormulaTuples(Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
        case applied_connective:
            return(CountSimpleUsageInFORMULATERMArray(GetArity(Formula->FormulaUnion.Atom),
GetArguments(Formula->FormulaUnion.Atom),&CountFormulaTuples));
            break;
        case tuple:
            return(1 + 
CountSimpleUsageInFORMULAArray(Formula->FormulaUnion.TupleFormula.NumberOfElements,
Formula->FormulaUnion.TupleFormula.Elements,&CountFormulaTuples));
            break;
        case ite_formula:
            return(CountFormulaTuples(Formula->FormulaUnion.ConditionalFormula.Condition) + 
CountFormulaTuples(Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue) +
CountFormulaTuples(Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse));
            break;
        case let_formula:
            return(CountFormulaTuples(Formula->FormulaUnion.LetFormula.LetBody));
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for counting atoms",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            break;
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int CountTermTerms(TERM Term) {

    int TermCount;
    
    if (Term->Type == formula) {
        return(CountFormulaTerms(Term->TheSymbol.Formula));
    } else {
        if (Term->Type == atom_as_term) {
            TermCount = 0;
        } else {
            TermCount = 1;
        }
        TermCount += CountSimpleUsageInTERMArray(GetArity(Term),GetArguments(Term),
&CountTermTerms);
//DEBUG printf("CountTermTerms for %s is %d\n",GetSymbol(Term),TermCount);
        return (TermCount);
    }
}
//-------------------------------------------------------------------------------------------------
int CountFormulaTerms(FORMULA Formula) {

    String ErrorMessage;

    switch(Formula->Type) {
        case sequent:
            return(
CountSimpleUsageInFORMULAArray(Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,
Formula->FormulaUnion.SequentFormula.LHS,&CountFormulaTerms) +
CountSimpleUsageInFORMULAArray(Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,
Formula->FormulaUnion.SequentFormula.RHS,&CountFormulaTerms));
            break;
        case assignment:
//TODO - should I count the LHS?
            return(CountFormulaTerms(Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case type_declaration:
            return(0);
            break;
        case quantified:
            return(CountFormulaTerms(Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
            return(CountFormulaTerms(Formula->FormulaUnion.BinaryFormula.LHS) + 
CountFormulaTerms(Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case unary:
            return(CountFormulaTerms(Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
        case applied_connective:
//DEBUG printf("The number of terms in %s is %d\n",GetSymbol(Formula->FormulaUnion.Atom),CountTermTerms(Formula->FormulaUnion.Atom));
            return(CountTermTerms(Formula->FormulaUnion.Atom));
            break;
        case tuple:
            return(CountSimpleUsageInFORMULAArray(
Formula->FormulaUnion.TupleFormula.NumberOfElements,
Formula->FormulaUnion.TupleFormula.Elements,&CountFormulaTerms));
            break;
        case ite_formula:
            return(
CountFormulaTerms(Formula->FormulaUnion.ConditionalFormula.Condition) +
CountFormulaTerms(Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue) +
CountFormulaTerms(Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse));
            break;
        case let_formula:
            return(CountFormulaTerms(Formula->FormulaUnion.LetFormula.LetBody));
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for counting terms",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            break;
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int CountAnnotatedFormulaTerms(ANNOTATEDFORMULA AnnotatedFormula) {

    return(CountFormulaTerms(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula));
}
//-------------------------------------------------------------------------------------------------
int CountTupleFormulaeAtomsByPredicate(SIGNATURE Signature,int NumberOfElements,
FORMULAArray TupleFormulae,char * Predicate,int DoNested) {

    int ElementNumber;
    int TotalAtoms;

    TotalAtoms = 0;
    for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
        TotalAtoms += CountFormulaAtomsByPredicate(Signature,TupleFormulae[ElementNumber],
Predicate,DoNested);
    }
    return(TotalAtoms);
}
//-------------------------------------------------------------------------------------------------
int CountNestedFormulaAtomsByPredicate(SIGNATURE Signature,TERM Atom,char * Predicate) {

    int Index;
    int Count;

    Count = 0;
    if (GetArity(Atom) > 0 && GetArguments(Atom) != NULL) {
        for (Index = 0; Index < GetArity(Atom); Index++) {
//----If nested is possible everything is a formula, so just check first. Otherwise it's a GOF
//----term that cannot have nested formulae.
            if (Atom->Arguments[Index]->Type == formula) {
                Count += CountFormulaAtomsByPredicate(Signature,
Atom->Arguments[Index]->TheSymbol.Formula,Predicate,1);
            }
        }
    }
    return(Count);
}
//-------------------------------------------------------------------------------------------------
int CountFormulaAtomsByPredicate(SIGNATURE Signature,FORMULA Formula,char * Predicate,
int DoNested) {

    int Count;
    String ErrorMessage;

//DEBUG printf("Counting %s (DoNested=%d) in\n",Predicate,DoNested); PrintFileTSTPFormula(OpenFILEPrintFile(stdout,NULL),tptp_thf,Formula,0,1,outermost,1);printf("\n");
    Count = 0;
    switch(Formula->Type) {
        case sequent:
            return(CountTupleFormulaeAtomsByPredicate(Signature,
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,
Formula->FormulaUnion.SequentFormula.LHS,Predicate,DoNested) + 
CountTupleFormulaeAtomsByPredicate(Signature,
Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,
Formula->FormulaUnion.SequentFormula.RHS,Predicate,DoNested));
            break;
        case assignment:
//TODO - should I count the LHS?
            return(CountFormulaAtomsByPredicate(Signature,Formula->FormulaUnion.BinaryFormula.RHS,
Predicate,DoNested));
            break;
        case type_declaration:
            return(0);
            break;
        case quantified:
//----Add in RHS of : variables
//            if (Formula->FormulaUnion.QuantifiedFormula.VariableType != NULL) {
//                Count += CountFormulaAtomsByPredicate(
//Formula->FormulaUnion.QuantifiedFormula.VariableType,Predicate,DoNested);
//            }
            Count += CountFormulaAtomsByPredicate(Signature,
Formula->FormulaUnion.QuantifiedFormula.Formula,Predicate,DoNested);
            return(Count);
            break;
        case binary:
            if (Formula->FormulaUnion.BinaryFormula.Connective != equation || DoNested) {
//----LHS and RHS of equations are nested
                Count += CountFormulaAtomsByPredicate(Signature,
Formula->FormulaUnion.BinaryFormula.LHS,Predicate,DoNested);
//----Don't count RHS of typings. Why aren't these type_declaration?
                if (Formula->FormulaUnion.BinaryFormula.Connective != typecolon) {
                    Count += CountFormulaAtomsByPredicate(Signature,
Formula->FormulaUnion.BinaryFormula.RHS,Predicate,DoNested);
                }
            }
//----Equality counts as an atom
            if (Formula->FormulaUnion.BinaryFormula.Connective == equation && 
(!strcmp(Predicate,"=") || !strcmp(Predicate,"PREDICATE"))) {
//DEBUG printf("--=-- matches --%s--\n",Predicate);
                Count++;
            }
            return(Count);
            break;
        case unary:
            return(CountFormulaAtomsByPredicate(Signature,
Formula->FormulaUnion.UnaryFormula.Formula,Predicate,DoNested));
            break;
        case atom:
        case applied_connective:
            if (DoNested) {
//----Do nested for TXF (and first-order style THF, if it's ever used)
//DEBUG printf("Count nested of %s\n",GetSymbol(Formula->FormulaUnion.Atom));
                Count = CountNestedFormulaAtomsByPredicate(Signature,
Formula->FormulaUnion.Atom,Predicate);
//DEBUG printf("Counted nested of %s gets %d\n",GetSymbol(Formula->FormulaUnion.Atom),Count);
            }
//DEBUG printf("Look if required %s is the symbol here %s\n",Predicate,GetSymbol(Formula->FormulaUnion.Atom));
//----If nothing requested, take everything
            if (
(!strcmp(Predicate,"PREDICATE") && IsSymbolInSignatureList(Signature->Predicates,
GetSymbol(Formula->FormulaUnion.Atom),GetArity(Formula->FormulaUnion.Atom),NULL)) || 
(!strcmp(Predicate,"CONNECTIVE") && Formula->FormulaUnion.Atom->Type == connective) ||
(!strcmp(Predicate,"APPLIED_CONNECTIVE") && Formula->Type == applied_connective) ||
(!strcmp(Predicate,"INDEXED_CONNECTIVE") && GetSymbol(Formula->FormulaUnion.Atom)[0] == '#') ||
//----It's the predicate I want (in CNF and FOF; in TFF and THF it's dealt with as binary). See
//----comment "Check for an equality" in ParseFormula in Parsing.c
!strcmp(Predicate,GetSymbol(Formula->FormulaUnion.Atom)) ||
//----A variable in THF
(!strcmp(Predicate,"VARIABLE") && Formula->FormulaUnion.Atom->Type == variable) ||
//----A math predicate (non-variable)
(!strcmp(Predicate,"MATH_PREDICATE") && IsMathPredicate(GetSymbol(Formula->FormulaUnion.Atom),
GetArity(Formula->FormulaUnion.Atom))) ||
(!strcmp(Predicate,"MATH_FUNCTOR") && IsMathFunctor(GetSymbol(Formula->FormulaUnion.Atom),
GetArity(Formula->FormulaUnion.Atom))) ||
(!strcmp(Predicate,"MATH_NUMBER") && LooksLikeANumber(GetSymbol(Formula->FormulaUnion.Atom))) ) {
//DEBUG printf("--%s-- matches --%s--, total is %d\n",GetSymbol(Formula->FormulaUnion.Atom),Predicate,Count+1);
//DEBUG printf("Required %s is the symbol here %s\n",Predicate,GetSymbol(Formula->FormulaUnion.Atom));
                return(Count + 1);
            } else {
//DEBUG printf("--%s-- not matches --%s--, total is %d\n",GetSymbol(Formula->FormulaUnion.Atom),Predicate,Count);
                return(Count + 0);
            }
            break;
        case tuple:
            return(CountTupleFormulaeAtomsByPredicate(Signature,
Formula->FormulaUnion.TupleFormula.NumberOfElements,Formula->FormulaUnion.TupleFormula.Elements,
Predicate,DoNested));
            break;
        case ite_formula:
            Count = !strcmp(Predicate,"$ite") ? 1 : 0;
            Count += 
CountFormulaAtomsByPredicate(Signature,Formula->FormulaUnion.ConditionalFormula.Condition,
Predicate,DoNested) +
CountFormulaAtomsByPredicate(Signature,Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue,
Predicate,DoNested) +
CountFormulaAtomsByPredicate(Signature,Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse,
Predicate,DoNested);
            return(Count);
            break;
        case let_formula:
            Count = !strcmp(Predicate,"$let") ? 1 : 0;
            Count += 
CountFormulaAtomsByPredicate(Signature,Formula->FormulaUnion.LetFormula.LetBody,Predicate,DoNested);
            return(Count);
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for counting atoms",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void CountTheConnective(ConnectiveType Connective,
ConnectiveStatisticsType * ConnectiveStatistics) {

    String ErrorMessage;

    switch(Connective) {
//----Quantifiers and binders
        case universal:
            ConnectiveStatistics->NumberOfUniversals++;
            break;
        case existential:
            ConnectiveStatistics->NumberOfExistentials++;
            break;
        case lambda:
            ConnectiveStatistics->NumberOfLambdas++;
            break;
        case pibinder:
            ConnectiveStatistics->NumberOfPiBinders++;
            break;
        case sigmabinder:
            ConnectiveStatistics->NumberOfSigmaBinders++;
            break;
        case descriptionbinder:
            ConnectiveStatistics->NumberOfDescriptionBinders++;
            break;
        case choicebinder:
            ConnectiveStatistics->NumberOfChoiceBinders++;
            break;
//----True connectives
        case disjunction:
            ConnectiveStatistics->NumberOfDisjunctions++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case conjunction:
            ConnectiveStatistics->NumberOfConjunctions++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case equivalence:
            ConnectiveStatistics->NumberOfEquivalences++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case implication:
            ConnectiveStatistics->NumberOfImplications++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case reverseimplication:
            ConnectiveStatistics->NumberOfReverseImplications++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case nonequivalence:
            ConnectiveStatistics->NumberOfXors++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case negateddisjunction:
            ConnectiveStatistics->NumberOfNors++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case negatedconjunction:
            ConnectiveStatistics->NumberOfNands++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case negation:
            ConnectiveStatistics->NumberOfNegations++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case application:
            ConnectiveStatistics->NumberOfApplications++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case equation:
            ConnectiveStatistics->NumberOfEqualitySymbols++;
            break;
        case typedequation:
            ConnectiveStatistics->NumberOfTypedEqualitySymbols++;
            break;
        case pi:
            ConnectiveStatistics->NumberOfPis++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case sigma:
            ConnectiveStatistics->NumberOfSigmas++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case choice:
            ConnectiveStatistics->NumberOfChoices++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case description:
            ConnectiveStatistics->NumberOfDescriptions++;
            ConnectiveStatistics->NumberOfConnectives++;
            break;
        case subtype:
            ConnectiveStatistics->NumberOfSubtypes++;
            ConnectiveStatistics->NumberOfTypeConnectives++;
            break;
        case maparrow:
            ConnectiveStatistics->NumberOfMaparrows++;
            ConnectiveStatistics->NumberOfTypeConnectives++;
            break;
        case xprodtype:
            ConnectiveStatistics->NumberOfXprods++;
            ConnectiveStatistics->NumberOfTypeConnectives++;
            break;
        case uniontype:
            ConnectiveStatistics->NumberOfUnions++;
            ConnectiveStatistics->NumberOfTypeConnectives++;
            break;
        case box:
        case diamond:
        case quatrefoil:
        case circle:
            ConnectiveStatistics->NumberOfNTFConnectives++;
            ConnectiveStatistics->NumberOfConnectives++;
//DEBUG printf("Found a short applied %s counts are %d %d\n",ConnectiveToString(Connective),ConnectiveStatistics->NumberOfNTFConnectives,ConnectiveStatistics->NumberOfConnectives);
            break;
        default:
            sprintf(ErrorMessage,"Unknown connective %s in counting",
ConnectiveToString(Connective));
            CodingError(ErrorMessage);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
ConnectiveStatisticsType GetSimpleConnectiveStatisticsInTERMArray(int NumberOfElements,
TERMArray Terms,ConnectiveStatisticsType (*GetFunction)(TERM)) {

    int ElementNumber;
    ConnectiveStatisticsType TotalStatistics;

    InitializeConnectiveStatistics(&TotalStatistics);
    if (NumberOfElements > 0 && Terms != NULL) {
        TotalStatistics = (*GetFunction)(Terms[0]);
        for (ElementNumber = 1;ElementNumber < NumberOfElements;ElementNumber++) {
            AddOnConnectiveStatistics(&TotalStatistics,(*GetFunction)(Terms[ElementNumber]));
        }
    }
    return(TotalStatistics);
}
//-------------------------------------------------------------------------------------------------
ConnectiveStatisticsType GetSimpleConnectiveStatisticsInFORMULATERMArray(int NumberOfElements,
TERMArray Terms,ConnectiveStatisticsType (*GetFunction)(FORMULA)) {

    int ElementNumber;
    ConnectiveStatisticsType TotalStatistics;

    InitializeConnectiveStatistics(&TotalStatistics);
    if (NumberOfElements > 0 && Terms != NULL) {
        TotalStatistics = (*GetFunction)(Terms[0]->TheSymbol.Formula);
        for (ElementNumber = 1;ElementNumber < NumberOfElements;ElementNumber++) {
            AddOnConnectiveStatistics(&TotalStatistics,(*GetFunction)(
Terms[ElementNumber]->TheSymbol.Formula));
        }
    }
    return(TotalStatistics);
}
//-------------------------------------------------------------------------------------------------
ConnectiveStatisticsType GetSimpleConnectiveStatisticsInFORMULAArray(int NumberOfElements,
FORMULAArray Formulae,ConnectiveStatisticsType (*GetFunction)(FORMULA)) {

    int ElementNumber;
    ConnectiveStatisticsType TotalStatistics;

    InitializeConnectiveStatistics(&TotalStatistics);
    if (NumberOfElements > 0 && Formulae != NULL) {
        TotalStatistics = (*GetFunction)(Formulae[0]);
        for (ElementNumber = 1;ElementNumber < NumberOfElements;ElementNumber++) {
            AddOnConnectiveStatistics(&TotalStatistics,(*GetFunction)(Formulae[ElementNumber]));
        }
    }
    return(TotalStatistics);
}
//-------------------------------------------------------------------------------------------------
ConnectiveStatisticsType GetArgumentConnectiveUsage(TERM Term) {

    if (Term->Type == formula) {
        return(GetFormulaConnectiveUsage(Term->TheSymbol.Formula));
    } else {
        return(GetSimpleConnectiveStatisticsInTERMArray(GetArity(Term),GetArguments(Term),
&GetArgumentConnectiveUsage));
    }
}
//-------------------------------------------------------------------------------------------------
ConnectiveStatisticsType GetFormulaConnectiveUsage(FORMULA Formula) {

    ConnectiveStatisticsType ConnectiveStatistics;
    ConnectiveStatisticsType MoreConnectiveStatistics;
    FormulaType * VariableType;
    String ErrorMessage;
    char * AtomSymbol;

    InitializeConnectiveStatistics(&ConnectiveStatistics);
    InitializeConnectiveStatistics(&MoreConnectiveStatistics);

    switch(Formula->Type) {
        case sequent:
            ConnectiveStatistics = GetSimpleConnectiveStatisticsInFORMULAArray(
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,
Formula->FormulaUnion.SequentFormula.LHS,&GetFormulaConnectiveUsage);
            MoreConnectiveStatistics = GetSimpleConnectiveStatisticsInFORMULAArray(
Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,
Formula->FormulaUnion.SequentFormula.RHS,&GetFormulaConnectiveUsage);
            AddOnConnectiveStatistics(&ConnectiveStatistics,
MoreConnectiveStatistics);
            break;
        case assignment:
            ConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.BinaryFormula.RHS);
            ConnectiveStatistics.NumberOfGlobalDefns++;
            break;
        case type_declaration:
            ConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.BinaryFormula.RHS);
            ConnectiveStatistics.NumberOfGlobalTypeDecs++;
            break;
        case quantified:
//DEBUG printf("Looking at quantified variable %s with quantifier %s\n",GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable),ConnectiveToString(Formula->FormulaUnion.QuantifiedFormula.Quantifier));
//----For typed variables
            VariableType = Formula->FormulaUnion.QuantifiedFormula.VariableType;
            if (VariableType != NULL) {
                ConnectiveStatistics = GetFormulaConnectiveUsage(VariableType);
                ConnectiveStatistics.NumberOfTypedVariables++;
//----Count math variables
                if (VariableType->Type == atom && 
GetArity(VariableType->FormulaUnion.Atom) == 0 &&
(!strcmp(GetSymbol(VariableType->FormulaUnion.Atom),"$int") ||
 !strcmp(GetSymbol(VariableType->FormulaUnion.Atom),"$rat") ||
 !strcmp(GetSymbol(VariableType->FormulaUnion.Atom),"$real"))) {
                    ConnectiveStatistics.NumberOfMathVariables++;
                }
            }
            MoreConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.QuantifiedFormula.Formula);
            AddOnConnectiveStatistics(&ConnectiveStatistics,MoreConnectiveStatistics);
            CountTheConnective(Formula->FormulaUnion.QuantifiedFormula.Quantifier,
&ConnectiveStatistics);
            break;
        case binary:
            ConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.BinaryFormula.LHS);
            MoreConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.BinaryFormula.RHS);
            AddOnConnectiveStatistics(&ConnectiveStatistics,MoreConnectiveStatistics);
            CountTheConnective(Formula->FormulaUnion.BinaryFormula.Connective,
&ConnectiveStatistics);
            break;
        case unary:
            ConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.UnaryFormula.Formula);
            switch (Formula->FormulaUnion.UnaryFormula.Connective) {
                case negation:
                    ConnectiveStatistics.NumberOfNegations++;
                    break;
                case box:
                case diamond:
                case quatrefoil:
                case circle:
                    ConnectiveStatistics.NumberOfNTFConnectives++;
                    break;
//----Ignore these - they are counted as atoms in formulae
                case pi:
                case sigma:
                case choice:
                case description:
                    break;
                default:
                    sprintf(ErrorMessage,"Unknown unary connective %s in counting",
ConnectiveToString(Formula->FormulaUnion.UnaryFormula.Connective));
                    CodingError(ErrorMessage);
                    break;
            }
            ConnectiveStatistics.NumberOfConnectives++;
            break;
        case atom:
        case applied_connective:
            ConnectiveStatistics = GetSimpleConnectiveStatisticsInTERMArray(
GetArity(Formula->FormulaUnion.Atom),GetArguments(Formula->FormulaUnion.Atom),
&GetArgumentConnectiveUsage);
//----Count use of connectives as atoms. 
            AtomSymbol = GetSymbol(Formula->FormulaUnion.Atom);
//DEBUG printf("AtomSymbol is %s type is %s\n",AtomSymbol,TermTypeToString(Formula->FormulaUnion.Atom->Type));
//----Counting {$box} type things for NTF
            if (Formula->Type == applied_connective && Formula->FormulaUnion.Atom->Type == atom_as_term) {
//----The number of actual statistics is counted by APPLIED_CONNECTIVES in HeadListCount
                ConnectiveStatistics.NumberOfConnectives++;
            }
            if (Formula->FormulaUnion.Atom->Type == connective ||
(Formula->FormulaUnion.Atom->Type == atom_as_term &&
(!strcmp(AtomSymbol,"@=") ||
 !strcmp(AtomSymbol,"!!") || !strcmp(AtomSymbol,"??") ||
 !strcmp(AtomSymbol,"@@+") || !strcmp(AtomSymbol,"@@-")))) {
                CountTheConnective(StringToConnective(GetSymbol(Formula->FormulaUnion.Atom)),
&ConnectiveStatistics);
            }
            break;
        case tuple:
            ConnectiveStatistics = GetSimpleConnectiveStatisticsInFORMULAArray(
Formula->FormulaUnion.TupleFormula.NumberOfElements,Formula->FormulaUnion.TupleFormula.Elements,
&GetFormulaConnectiveUsage);
            break;
        case ite_formula:
            ConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.ConditionalFormula.Condition);
            MoreConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue);
            AddOnConnectiveStatistics(&ConnectiveStatistics,MoreConnectiveStatistics);
            MoreConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse);
            AddOnConnectiveStatistics(&ConnectiveStatistics,MoreConnectiveStatistics);
            break;
        case let_formula:
            ConnectiveStatistics = GetFormulaConnectiveUsage(
Formula->FormulaUnion.LetFormula.LetBody);
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for counting connectives",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            break;
    }
    return(ConnectiveStatistics);
}
//-------------------------------------------------------------------------------------------------
int TupleFormulaeDepth(int NumberOfElements,FORMULAArray TupleFormulae) {

    int ElementNumber;
    int MaximalDepth;

    MaximalDepth = 0;
    for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
        MaximalDepth = MaximumOfInt(MaximalDepth,FormulaDepth(TupleFormulae[ElementNumber]));
    }
    return(MaximalDepth);
}
//-------------------------------------------------------------------------------------------------
int FormulaDepth(FORMULA Formula) {

    switch(Formula->Type) {
        case sequent:
            return(MaximumOfInt(TupleFormulaeDepth(
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,Formula->FormulaUnion.SequentFormula.LHS),
TupleFormulaeDepth(Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,
Formula->FormulaUnion.SequentFormula.RHS)));
            break;
        case assignment:
            return(FormulaDepth(Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case type_declaration:
            return(0);
            break;
        case quantified:
            return(1 + FormulaDepth(Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
            if (Formula->FormulaUnion.BinaryFormula.Connective == equation) {
                return(1);
            } else {
                return(1 + 
MaximumOfInt(FormulaDepth(Formula->FormulaUnion.BinaryFormula.LHS),
FormulaDepth(Formula->FormulaUnion.BinaryFormula.RHS)));
            }
            break;
        case unary:
            return(1 + FormulaDepth(Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
        case applied_connective:
            return(1);
            break;
        case tuple:
            return(TupleFormulaeDepth(Formula->FormulaUnion.TupleFormula.NumberOfElements,
Formula->FormulaUnion.TupleFormula.Elements));
            break;
        case ite_formula:
            return(1 + MaximumOfInt(FormulaDepth(
Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue),
FormulaDepth(Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse)));
            break;
        case let_formula:
            return(FormulaDepth(Formula->FormulaUnion.LetFormula.LetBody));
            break;
        default:
            CodingError("Invalid formula type for measuring depth");
            return(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
//int AnnotatedFormulaDepth(ANNOTATEDFORMULA AnnotatedFormula) {
//
//    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
//        return(FormulaDepth(AnnotatedFormula->AnnotatedFormulaUnion.
//AnnotatedTSTPFormula.FormulaWithVariables->Formula));
//    } else {
//        return(-1);
//    }
//}
//-------------------------------------------------------------------------------------------------
int MaxTermDepth(TERM Term) {

    int MaxDepth;
    int Index;

    if (Term->Type == formula) {
        return(MaxFormulaTermDepth(Term->TheSymbol.Formula));
    } else {
        MaxDepth = 0;
        if (GetArity(Term) > 0 && GetArguments(Term) != NULL) {
            for (Index = 0; Index < GetArity(Term); Index++) {
                MaxDepth = MaximumOfInt(MaxDepth,MaxTermDepth(Term->Arguments[Index]));
            }
        }
        if (Term->Type != atom_as_term) {
            MaxDepth += 1;
        }
//DEBUG printf("MaxTermDepth for %s is %d\n",GetSymbol(Term),MaxDepth);
        return (MaxDepth);
    }
}
//-------------------------------------------------------------------------------------------------
int MaxTupleFormulaeTermDepth(int NumberOfElements,FORMULAArray TupleFormulae) {

    int ElementNumber;
    int MaximalDepth;

    MaximalDepth = 0;
    if (NumberOfElements > 0 && TupleFormulae != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            MaximalDepth = MaximumOfInt(MaximalDepth,MaxFormulaTermDepth(
TupleFormulae[ElementNumber]));
        }
    }
    return(MaximalDepth);
}
//-------------------------------------------------------------------------------------------------
//----Dig down to atoms and get max term depth. Nested formula have no term depth.
int MaxFormulaTermDepth(FORMULA Formula) {

    String ErrorMessage;

    switch(Formula->Type) {
        case sequent:
            return(MaximumOfInt(MaxTupleFormulaeTermDepth(
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,Formula->FormulaUnion.SequentFormula.LHS),
MaxTupleFormulaeTermDepth(Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,
Formula->FormulaUnion.SequentFormula.RHS)));
            break;
        case assignment:
            return(MaxFormulaTermDepth(Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case type_declaration:
            return(0);
            break;
        case quantified:
            return(MaxFormulaTermDepth(Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
            return(MaximumOfInt(
MaxFormulaTermDepth(Formula->FormulaUnion.BinaryFormula.LHS),
MaxFormulaTermDepth(Formula->FormulaUnion.BinaryFormula.RHS)));
            break;
        case unary:
            return(MaxFormulaTermDepth(Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
        case applied_connective:
            return(MaxTermDepth(Formula->FormulaUnion.Atom));
            break;
        case tuple:
            return(MaxTupleFormulaeTermDepth(Formula->FormulaUnion.TupleFormula.NumberOfElements,
Formula->FormulaUnion.TupleFormula.Elements));
            break;
        case ite_formula:
            return(MaximumOfInt(
MaxFormulaTermDepth(Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue),
MaxFormulaTermDepth(Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse)));
            break;
        case let_formula:
            return(MaxFormulaTermDepth(Formula->FormulaUnion.LetFormula.LetBody));
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for max term depth",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
//int MaxAnnotatedFormulaTermDepth(ANNOTATEDFORMULA AnnotatedFormula) {
//
//    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
//        return(MaxFormulaTermDepth(AnnotatedFormula->AnnotatedFormulaUnion.
//AnnotatedTSTPFormula.FormulaWithVariables->Formula));
//    } else {
//        return(-1);
//    }
//}
//-------------------------------------------------------------------------------------------------
int SumTermDepth(TERM Atom) {

    int SumDepth;
    int Index;
    
    if (Atom->Type == formula) {
        return(SumFormulaTermDepth(Atom->TheSymbol.Formula));
    } else {
//----Don't count predicate
        if (Atom->Type == atom_as_term) {
            SumDepth = 0;
        } else {
            SumDepth = MaxTermDepth(Atom);
        }
        if (GetArity(Atom) > 0 && GetArguments(Atom) != NULL) {
            for (Index = 0; Index < GetArity(Atom); Index++) {
                SumDepth += SumTermDepth(Atom->Arguments[Index]);
            }
        }
    }
//DEBUG printf("SumTermDepth for %s is %d\n",GetSymbol(Atom),SumDepth);
    return(SumDepth);
}
//-------------------------------------------------------------------------------------------------
int SumTupleFormulaeTermDepth(int NumberOfElements,FORMULAArray TupleFormulae) {

    int ElementNumber;
    int TotalDepth;

    TotalDepth = 0;
    if (NumberOfElements > 0 && TupleFormulae != NULL) {
        for (ElementNumber = 0;ElementNumber < NumberOfElements;ElementNumber++) {
            TotalDepth += SumFormulaTermDepth(TupleFormulae[ElementNumber]);
        }
    }
    return(TotalDepth);
}
//-------------------------------------------------------------------------------------------------
int SumFormulaTermDepth(FORMULA Formula) {

    String ErrorMessage;

    switch(Formula->Type) {
        case sequent:
            return(SumTupleFormulaeTermDepth(
Formula->FormulaUnion.SequentFormula.NumberOfLHSElements,
Formula->FormulaUnion.SequentFormula.LHS) +
SumTupleFormulaeTermDepth(Formula->FormulaUnion.SequentFormula.NumberOfRHSElements,
Formula->FormulaUnion.SequentFormula.RHS));
        case assignment:
            return(SumFormulaTermDepth(Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case type_declaration:
            return(0);
            break;
        case quantified:
            return(SumFormulaTermDepth(Formula->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
            return(
SumFormulaTermDepth(Formula->FormulaUnion.BinaryFormula.LHS) + 
SumFormulaTermDepth(Formula->FormulaUnion.BinaryFormula.RHS));
            break;
        case unary:
            return(SumFormulaTermDepth(Formula->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
        case applied_connective:
            return(SumTermDepth(Formula->FormulaUnion.Atom));
            break;
        case tuple:
            return(SumTupleFormulaeTermDepth(Formula->FormulaUnion.TupleFormula.NumberOfElements,
Formula->FormulaUnion.TupleFormula.Elements));
            break;
        case ite_formula:
            return(
SumFormulaTermDepth(Formula->FormulaUnion.ConditionalFormula.FormulaIfTrue) + 
SumFormulaTermDepth(Formula->FormulaUnion.ConditionalFormula.FormulaIfFalse));
            break;
        case let_formula:
            return(SumFormulaTermDepth(Formula->FormulaUnion.LetFormula.LetBody));
            break;
        default:
            sprintf(ErrorMessage,"Invalid formula type %s for sum formula term depth",
FormulaTypeToString(Formula->Type));
            CodingError(ErrorMessage);
            return(0);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
//int SumAnnotatedFormulaTermDepth(ANNOTATEDFORMULA AnnotatedFormula) {
//
//    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
//        return(SumFormulaTermDepth(AnnotatedFormula->AnnotatedFormulaUnion.
//AnnotatedTSTPFormula.FormulaWithVariables->Formula));
//    } else {
//        return(-1);
//    }
//}
//-------------------------------------------------------------------------------------------------
SyntaxType GetSyntax(ANNOTATEDFORMULA AnnotatedFormula) {

    assert(AnnotatedFormula != NULL);
    return(AnnotatedFormula->Syntax);
}
//-------------------------------------------------------------------------------------------------
SyntaxType GetListSyntax(LISTNODE Head) {

    SyntaxType SyntaxOfFirstAnnotatedFormula;

    SyntaxOfFirstAnnotatedFormula = nontype;
    while (Head != NULL && !LogicalAnnotatedFormula(Head->AnnotatedFormula)) {
        Head = Head->Next;
    }
    if (Head != NULL) {
        SyntaxOfFirstAnnotatedFormula = GetSyntax(Head->AnnotatedFormula);
        Head = Head->Next;
        while (Head != NULL) {
            if (LogicalAnnotatedFormula(Head->AnnotatedFormula) &&
SyntaxOfFirstAnnotatedFormula != GetSyntax(Head->AnnotatedFormula)) {
                return(tptp_mixed);
            }
            Head = Head->Next;
        }
    }
    return(SyntaxOfFirstAnnotatedFormula);
}
//-------------------------------------------------------------------------------------------------
void GetListSyntaxTypes(LISTNODE Head,String SyntaxTypes) {

    int Syntax;
    LISTNODE Node;

    strcpy(SyntaxTypes,"");

    for (Syntax=tptp_tpi;Syntax<=tptp_cnf;Syntax++) {
        Node = Head;
        while (Node != NULL) {
            if (GetSyntax(Node->AnnotatedFormula) == Syntax) {
                strcat(SyntaxTypes,SyntaxToString((SyntaxType)Syntax));
                strcat(SyntaxTypes,"\n");
                Node = NULL;
            } else {
                Node = Node->Next;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA GetUniversalCoreFormula(FORMULA QuantifiedFormula) {

    while (QuantifiedFormula->Type == quantified &&
QuantifiedFormula->FormulaUnion.QuantifiedFormula.Quantifier == universal) {
        QuantifiedFormula = QuantifiedFormula->FormulaUnion.QuantifiedFormula.Formula;
    }

    return(QuantifiedFormula);
}
//-------------------------------------------------------------------------------------------------
int ThereIsAConjecture(LISTNODE Head) {

    StatusType Role;

    while (Head != NULL) {
        if ((Role = GetRole(Head->AnnotatedFormula,NULL)) == conjecture ||
Role == negated_conjecture || Role == question) {
            return(1);
        }
        Head = Head->Next;
    }

    return(0);
}
//-------------------------------------------------------------------------------------------------
FORMULA GetLiteralFromClauseByNumber(FORMULA Clause,int Number) {

    if (Clause->Type == binary) {
        if (Number == 1) {
            return(Clause->FormulaUnion.BinaryFormula.LHS);
        } else {
            return(GetLiteralFromClauseByNumber(Clause->FormulaUnion.BinaryFormula.RHS,Number-1));
        }
    } else if ((Clause->Type == unary || Clause->Type == atom) && Number == 1) {
        return(Clause);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
FORMULA GetLiteralFromAnnotatedClauseByNumber(ANNOTATEDFORMULA AnnotatedClause,
int Number) {

//    FORMULAWITHVARIABLES FormulaWithVariables;

    if (CheckAnnotatedFormula(AnnotatedClause,tptp_cnf)) {
//        FormulaWithVariables = AnnotatedClause->
//AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables;
        return(GetLiteralFromClauseByNumber(AnnotatedClause->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
Number));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
TERM GetSourceTERM(ANNOTATEDFORMULA AnnotatedFormula,char * SourceSymbol) {

    if (!ReallyAnAnnotatedFormula(AnnotatedFormula) || 
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source == NULL) {
        return(NULL);
    }

    if (SourceSymbol == NULL ||
!strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Source),SourceSymbol)) {
        return(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Source);
    }
    return(NULL);
}
//-------------------------------------------------------------------------------------------------
char * GetSource(ANNOTATEDFORMULA AnnotatedFormula) {

    TERM SourceTerm;

    if ((SourceTerm = GetSourceTERM(AnnotatedFormula,NULL)) != NULL) {
        return(GetSymbol(SourceTerm));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetSourceTerm(ANNOTATEDFORMULA AnnotatedFormula,char * PutInfoHere) {

    TERM SourceTerm;

    if ((SourceTerm = GetSourceTERM(AnnotatedFormula,NULL)) != NULL) {
        return(TSTPTermToString(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.Source,PutInfoHere));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
TERM GetInferenceRuleTERM(ANNOTATEDFORMULA AnnotatedFormula) {

    if (DerivedAnnotatedFormula(AnnotatedFormula) &&
//----Source is an inference term
!strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Source),"inference")) {
        return(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Source->Arguments[0]);
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetInferenceRule(ANNOTATEDFORMULA AnnotatedFormula,char * PutNameHere) {

    char * Buffer;
    int BufferSize;

    if (DerivedAnnotatedFormula(AnnotatedFormula)) {
//----Source is an inference term
        if (!strcmp(GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),"inference")) {
            return(TSTPTermToString(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.Source->Arguments[0],PutNameHere));
        } else {
//----Must be a plain copy of another, no inference rule
            MakeBuffer(&Buffer,&BufferSize);
            return(BufferReturn(&Buffer,PutNameHere));
        }
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
TERM GetSourceInfoTERMFromSourceInfo(TERM InferenceInfo,char * Symbol,
char * InferenceRuleName,int * Index) {

    String FinalSymbol;

    if (!strcmp(Symbol,"__inference_rule__")) {
        strcpy(FinalSymbol,InferenceRuleName);
    } else {
        strcpy(FinalSymbol,Symbol);
    }
    for ( ; *Index < InferenceInfo->FlexibleArity; (*Index)++) {
        if (!strcmp(FinalSymbol,InferenceInfo->Arguments[*Index]->TheSymbol.
NonVariable->NameSymbol)) {
            return(InferenceInfo->Arguments[*Index]);
        }
    }
    return(NULL);
}
//-------------------------------------------------------------------------------------------------
void DoGetInferenceInfoTERMsFromInferenceRecord(TERM InferenceRecord,
char * Symbol,TERMArray * ArrayOfInfoTERMs,int * NumberOfTerms) {

    TERM ThisInfoTERM;
    TERM ParentsList;
    int Index;

//----Check that it's an inference record with a list of parents
    if (GetArity(InferenceRecord) != 3 ||
!LooksLikeAList(InferenceRecord->Arguments[2],-1,-1)) {
        CodingError("Getting inference info from malformed inference record");
    }

    Index = 0;
    while ((ThisInfoTERM = GetSourceInfoTERMFromSourceInfo(InferenceRecord->
Arguments[1],Symbol,GetSymbol(InferenceRecord->Arguments[0]),&Index)) != NULL) {
        (*NumberOfTerms)++;
        *ArrayOfInfoTERMs = (TERMArray)Realloc((void *)*ArrayOfInfoTERMs,
(*NumberOfTerms) * sizeof(TERM));
        (*ArrayOfInfoTERMs)[(*NumberOfTerms) - 1] = ThisInfoTERM;
        Index++;
    }

//----Now look in the parents list for nested inferences
    ParentsList = InferenceRecord->Arguments[2];
    for (Index=0;Index < ParentsList->FlexibleArity;Index++) {
        if (!strcmp(GetSymbol(ParentsList->Arguments[Index]),"inference")) {
            DoGetInferenceInfoTERMsFromInferenceRecord(ParentsList->
Arguments[Index],Symbol,ArrayOfInfoTERMs,NumberOfTerms);
        }
    }
}
//-------------------------------------------------------------------------------------------------
//----Gets one from this layer, then looks through the parents to get more
//----from nested inference records
void GetInferenceInfoTERMsFromInferenceRecord(TERM InferenceRecord,
char * Symbol,TERMArray * ArrayOfInfoTERMs,int * NumberOfTerms) {

    *NumberOfTerms = 0;
    DoGetInferenceInfoTERMsFromInferenceRecord(InferenceRecord,Symbol,
ArrayOfInfoTERMs,NumberOfTerms);
}
//-------------------------------------------------------------------------------------------------
TERMArray GetInferenceInfoTERMs(ANNOTATEDFORMULA AnnotatedFormula,
char * Symbol,int * NumberOfTerms) {

    TERMArray ArrayOfInfoTERMs;

    ArrayOfInfoTERMs = NULL;
    *NumberOfTerms = 0;
    if (LogicalAnnotatedFormula(AnnotatedFormula) &&
//----It's derived
DerivedAnnotatedFormula(AnnotatedFormula) &&
//----Source is an inference term
!strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Source),"inference")) {
        GetInferenceInfoTERMsFromInferenceRecord(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source,Symbol,
&ArrayOfInfoTERMs,NumberOfTerms);
    }
    return(ArrayOfInfoTERMs);
}
//-------------------------------------------------------------------------------------------------
TERM GetSourceInfoTERM(ANNOTATEDFORMULA AnnotatedFormula,char * SourceSymbol,
char * InfoTermSymbol) {

    int Index;

//DEBUG printf("SourceSymbol %s InfoTermSymbol %s\n",SourceSymbol,InfoTermSymbol);
//----Source is any or as specified
    if ((SourceSymbol == NULL ||
!strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Source),SourceSymbol)) &&
//----Must have at least two arguments
GetArity(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source)
>= 2 &&
//----The second argument must look like a list
LooksLikeAList(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Source->Arguments[1],-1,-1)) {
        Index = 0;
        return(GetSourceInfoTERMFromSourceInfo(AnnotatedFormula-> 
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source->Arguments[1],InfoTermSymbol,
GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source->
Arguments[0]),&Index));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetSourceInfoTerm(ANNOTATEDFORMULA AnnotatedFormula,char * SourceSymbol,
char * InfoTermSymbol,char * PutInfoHere) {

    TERM SourceTerm;

    if ((SourceTerm = GetSourceInfoTERM(AnnotatedFormula,SourceSymbol,
InfoTermSymbol)) != NULL) {
        return(TSTPTermToString(SourceTerm,PutInfoHere));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
TERM GetInferenceInfoTERM(ANNOTATEDFORMULA AnnotatedFormula,char * Symbol) {

    if (DerivedAnnotatedFormula(AnnotatedFormula)) {
        return(GetSourceInfoTERM(AnnotatedFormula,"inference",Symbol));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
//----Gets a useful info term from an inference source
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetInferenceInfoTerm(ANNOTATEDFORMULA AnnotatedFormula,char * Symbol,
char * PutInfoHere) {

    TERM InferenceTerm;

    if ((InferenceTerm = GetInferenceInfoTERM(AnnotatedFormula,Symbol)) != 
NULL) {
        return(TSTPTermToString(InferenceTerm,PutInfoHere));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and 
//----take responsibility for the malloced memory.
SZSResultArray GetInferenceSZSStatuses(ANNOTATEDFORMULA AnnotatedFormula,
SZSResultArray ArrayOfSZSStatuses,int * NumberOfSZSResults) {

    TERMArray ArrayOfStatusTERMs;
    int NumberOfTerms;
    int Index;

    ArrayOfStatusTERMs = GetInferenceInfoTERMs(AnnotatedFormula,"status",
&NumberOfTerms);
    if (NumberOfTerms == 0) {
        if (ArrayOfStatusTERMs != NULL) {
            Free((void **)&ArrayOfStatusTERMs);
        }
        *NumberOfSZSResults = 0;
        return(NULL);
    } else {
        if (ArrayOfSZSStatuses == NULL) {
            ArrayOfSZSStatuses = (SZSResultArray)Malloc(NumberOfTerms * 
sizeof(SZSResultType));
        }
        for (Index=0;Index<NumberOfTerms;Index++) {
            ArrayOfSZSStatuses[Index] = StringToSZSResult(
ArrayOfStatusTERMs[Index]->Arguments[0]->TheSymbol.NonVariable->NameSymbol);
        }
        if (ArrayOfStatusTERMs != NULL) {
            Free((void **)&ArrayOfStatusTERMs);
        }
        *NumberOfSZSResults = NumberOfTerms;
        return(ArrayOfSZSStatuses);
    }
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and 
//----take responsibility for the malloced memory.
char * GetInferenceStatus(ANNOTATEDFORMULA AnnotatedFormula,char * SZSStatus) {

    char * Buffer;

    Buffer = GetInferenceInfoTerm(AnnotatedFormula,"status",NULL);
    if (Buffer == NULL) {
        return(NULL);
    }
    if (!ExtractTermArguments(Buffer)) {
        Free((void **)&Buffer);
        return(NULL);
    }
    return(BufferReturn(&Buffer,SZSStatus));
}
//-------------------------------------------------------------------------------------------------
char * GetDischargedNames(ANNOTATEDFORMULA AnnotatedFormula,TERM * DischargeList) {

    TERMArray ArrayOfInfoTERMs;
    int NumberOfTerms;
    int Index;
    char * Buffer;
    int BufferSize;
    int NameIndex;

    MakeBuffer(&Buffer,&BufferSize);
    ArrayOfInfoTERMs = GetInferenceInfoTERMs(AnnotatedFormula,
"__inference_rule__",&NumberOfTerms);
    for (Index=0;Index < NumberOfTerms;Index++) {
        if (GetArity(ArrayOfInfoTERMs[Index]) == 2 &&
!strcmp(GetSymbol(ArrayOfInfoTERMs[Index]->Arguments[0]),"discharge")) {
            if (!LooksLikeAList(ArrayOfInfoTERMs[Index]->Arguments[1],-1,-1)) {
                CodingError("No list of discharged assumptions");
            }
//----This assumes only one discharge list, which is prolly true
            *DischargeList = ArrayOfInfoTERMs[Index]->Arguments[1];
            for (NameIndex=0;NameIndex < GetArity(ArrayOfInfoTERMs[Index]->
Arguments[1]);NameIndex++) {
                ExtendString(&Buffer,GetSymbol(ArrayOfInfoTERMs[Index]->
Arguments[1]->Arguments[NameIndex]),&BufferSize);
                ExtendString(&Buffer,",",&BufferSize);
            }
        }
    }
    if (ArrayOfInfoTERMs != NULL) {
        Free((void **)&ArrayOfInfoTERMs);
    }
//----Check if any discharges found
    if (strlen(Buffer) == 0) {
        Free((void **)&Buffer);
    }
    return(Buffer);
}
//-------------------------------------------------------------------------------------------------
//----Get a list of assumptions in Malloced memory. User must Free the memory.
char * ExtractAssumptionsList(TERM AssumptionsTerm) {

    char * Buffer;
    int BufferSize;
    int Index;
    TERM TheList;

    if (AssumptionsTerm == NULL || GetArity(AssumptionsTerm) != 1 || 
!LooksLikeAList(AssumptionsTerm->Arguments[0],-1,-1)) {
        CodingError("Illformed assumptions record");
    }
    TheList = AssumptionsTerm->Arguments[0];
//----Check for empty list
    if (GetArity(TheList) == 0) {
        return(NULL);
    } else {
        MakeBuffer(&Buffer,&BufferSize);
        for (Index=0;Index < GetArity(TheList);Index++) {
            ExtendString(&Buffer,GetSymbol(TheList->Arguments[Index]),
&BufferSize);
            ExtendString(&Buffer,",",&BufferSize);
        }
        return(Buffer);
    }
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetOneParentNames(TERM ParentSource,char * PutNamesHere) {

    char * Buffer;
    int BufferSize;

//----Build in malloced memory
    MakeBuffer(&Buffer,&BufferSize);

//----If an atom, return that name
    if (GetArity(ParentSource) == 0) {
        ExtendString(&Buffer,GetSymbol(ParentSource),&BufferSize);
        ExtendString(&Buffer,"\n",&BufferSize);
//----If a theory
    } else if (!strcmp(GetSymbol(ParentSource),"theory")) {
        ExtendAndFree(&Buffer,TSTPTermToString(ParentSource,NULL),&BufferSize);
        ExtendString(&Buffer,"\n",&BufferSize);
//----If an atom with extra information about the inference
    } else if (!strcmp(GetSymbol(ParentSource),":") && GetArity(ParentSource) 
== 2) {
        ExtendString(&Buffer,GetSymbol(ParentSource->Arguments[0]),&BufferSize);
        ExtendString(&Buffer,"\n",&BufferSize);
//----If a nested inference record
    } else if (!strcmp(GetSymbol(ParentSource),"inference")) {
        ExtendAndFree(&Buffer,GetInferenceParentNames(ParentSource,NULL),
&BufferSize);
    } 

    return(BufferReturn(&Buffer,PutNamesHere));
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetInferenceParentNames(TERM InferenceTerm,char * PutNamesHere) {

    int Index;
    char * Buffer;
    int BufferSize;

//----Check that it's an inference record with a list of parents
    if (GetArity(InferenceTerm) != 3 ||
GetSymbol(InferenceTerm->Arguments[2])[0] != '[') {
        CodingError("Getting parent names from malformed inference record");
    }

//----Build in malloced memory
    MakeBuffer(&Buffer,&BufferSize);

    for (Index = 0; Index < GetArity(InferenceTerm->Arguments[2]); Index++) {
        ExtendAndFree(&Buffer,GetOneParentNames(InferenceTerm->Arguments[2]->
Arguments[Index],NULL),&BufferSize);
    }

    return(BufferReturn(&Buffer,PutNamesHere));
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetParentNames(ANNOTATEDFORMULA AnnotatedFormula,char * PutNamesHere) {

    char * Buffer;
    int BufferSize;

//----Check it's an annotated formula
    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
//----Check if it's derived and it has a source
        if (DerivedAnnotatedFormula(AnnotatedFormula)) {
//----Check if it's an inference
            if (InferredAnnotatedFormula(AnnotatedFormula)) {
                Buffer = GetInferenceParentNames(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source,NULL);
            } else {
//----Must be the name of a node directly
                MakeBuffer(&Buffer,&BufferSize);
                ExtendString(&Buffer,GetSymbol(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),&BufferSize);
                ExtendString(&Buffer,"\n",&BufferSize);
            }
        } else {
            MakeBuffer(&Buffer,&BufferSize);
        }
    } else {
//----Something wrong
        CodingError("Getting parent names from non-formula");
    }

    return(BufferReturn(&Buffer,PutNamesHere));
}
//-------------------------------------------------------------------------------------------------
//----Same as GetParentNames but no theory names
char * GetNodeParentNames(ANNOTATEDFORMULA AnnotatedFormula,char * PutNamesHere) {

    char * Buffer;
    char * StartOfTheory;
    char * EndOfTheory;

    Buffer = GetParentNames(AnnotatedFormula,NULL);
    while ((StartOfTheory = strstr(Buffer,"theory(")) != NULL) {
        EndOfTheory = strchr(StartOfTheory,'\n');
        strcpy(StartOfTheory,EndOfTheory+1);
    }

    return(BufferReturn(&Buffer,PutNamesHere));
}
//-------------------------------------------------------------------------------------------------
int GetNodeParentList(ANNOTATEDFORMULA AnnotatedFormula,LISTNODE Head,LISTNODE * Parents,
SIGNATURE Signature) {

    char * AllParentNames;
    int NumberOfParents;
    StringParts ParentNames;

    *Parents = NULL;
    AllParentNames = GetNodeParentNames(AnnotatedFormula,NULL);
    NumberOfParents = Tokenize(AllParentNames,ParentNames,"\n");
    if (!GetNodesForNames(Head,ParentNames,NumberOfParents,Parents,Signature)) {
        Free((void **)&AllParentNames);
        return(0);
    }
    Free((void **)&AllParentNames);
    return(1);
}
//-------------------------------------------------------------------------------------------------
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetFileSourceNameAndNode(ANNOTATEDFORMULA AnnotatedFormula,
char * PutResultHere) {

    TERM FileTerm;
    char * Buffer;
    int BufferSize;

//----Formula is OK
    if (ReallyAnAnnotatedFormula(AnnotatedFormula) &&
//----File source
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source != NULL &&
!strcmp(GetSymbol(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),"file")) {
//----Build in malloced memory
        MakeBuffer(&Buffer,&BufferSize);
//----Build the parts
        FileTerm = AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source;
        ExtendAndFree(&Buffer,TSTPTermToString(FileTerm->Arguments[0],NULL),&BufferSize);
        ExtendString(&Buffer,"\n",&BufferSize);
//----Check if the node name is given
        if (GetArity(FileTerm) > 1) {
            ExtendAndFree(&Buffer,TSTPTermToString(FileTerm->Arguments[1],NULL),&BufferSize);
        } else {
            ExtendString(&Buffer,"unknown",&BufferSize);
        }
        return(BufferReturn(&Buffer,PutResultHere));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------
TERM GetUsefulInfoTERM(ANNOTATEDFORMULA AnnotatedFormula,char * Symbol,int OccurrenceNumber) {

    TERM UsefulInfo;
    int Index;

    if (!ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        CodingError("Trying to get useful info from a non-formula");
    }

//----It has useful info
    if (AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo != NULL) {
        UsefulInfo = AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo;
        for (Index = 0; Index < UsefulInfo->FlexibleArity; Index++) {
            if (!strcmp(Symbol,UsefulInfo->Arguments[Index]->TheSymbol.NonVariable->NameSymbol) &&
(OccurrenceNumber < 0 || --OccurrenceNumber == 0)) {
                return(UsefulInfo->Arguments[Index]);
            }
        }
    }
    return(NULL);
}
//-------------------------------------------------------------------------------------------------
//----Gets a term from the useful info global to a CNF/FOF node
//----Calling routine must provide enough space for info, or send NULL and
//----take responsibility for the malloced memory.
char * GetUsefulInfoTerm(ANNOTATEDFORMULA AnnotatedFormula,char * Symbol,int OccurrenceNumber,
char * PutInfoHere) {

    TERM UsefulTerm;

    if ((UsefulTerm = GetUsefulInfoTERM(AnnotatedFormula,Symbol,OccurrenceNumber)) != NULL) {
        return(TSTPTermToString(UsefulTerm,PutInfoHere));
    } else {
        return(NULL);
    }
}
//-------------------------------------------------------------------------------------------------

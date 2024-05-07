#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "Examine.h"
#include "Modify.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
//----Use with care - you're breaking the logic
int SetSyntax(ANNOTATEDFORMULA AnnotatedFormula,SyntaxType Syntax) {

    assert(AnnotatedFormula != NULL);
    if ((AnnotatedFormula->Syntax == tptp_fof ||
AnnotatedFormula->Syntax == tptp_cnf) && (Syntax == tptp_fof ||
Syntax == tptp_cnf)) {
        AnnotatedFormula->Syntax = Syntax;
        return(1);
    } else {
        return(0);
    }   
}
//-----------------------------------------------------------------------------
int SetStatus(ANNOTATEDFORMULA AnnotatedFormula,StatusType Status,
StatusType SubStatus) {

    assert(AnnotatedFormula != NULL);
    if (AnnotatedFormula->Syntax == tptp_fof || 
AnnotatedFormula->Syntax == tptp_cnf) {
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status =
Status;
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.SubStatus =
SubStatus;
        return(1);
    } else {
        return(0);
    }
}
//-----------------------------------------------------------------------------
void DeDoubleNegateFormula(FORMULA * Formula) {

    FORMULA NegatedFormula,DoubleNegatedFormula;

    if ((*Formula)->Type == unary && 
(*Formula)->FormulaUnion.UnaryFormula.Connective == negation) {
        NegatedFormula = (*Formula)->FormulaUnion.UnaryFormula.Formula;
        if (NegatedFormula->Type == unary &&
NegatedFormula->FormulaUnion.UnaryFormula.Connective == negation) {
            DoubleNegatedFormula = NegatedFormula->
FormulaUnion.UnaryFormula.Formula;
            Free((void **)Formula);
            Free((void **)&NegatedFormula);
            *Formula = DoubleNegatedFormula;
        }
    }
}
//-----------------------------------------------------------------------------
int DeDoubleNegate(ANNOTATEDFORMULA AnnotatedFormula) {

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof)) {
        DeDoubleNegateFormula(&(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula));
        return(1);
    } else {
        return(0);
    }
}
//-----------------------------------------------------------------------------
void NegateFormula(FORMULA * Formula,int Simplify) {

    FORMULA NegatedFormula;

    NegatedFormula = NewFormula();
    NegatedFormula->Type = unary;
    NegatedFormula->FormulaUnion.UnaryFormula.Connective = negation;
    NegatedFormula->FormulaUnion.UnaryFormula.Formula = *Formula;
    *Formula = NegatedFormula;
}
//-----------------------------------------------------------------------------
int Negate(ANNOTATEDFORMULA AnnotatedFormula,int Simplify) {

    FORMULA NegatedFormula;

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof)) {
//----Check if already negated when simplifying
        if (Simplify && AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->
Formula->Type == unary &&
AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->
Formula->FormulaUnion.UnaryFormula.Connective == negation) {
//DEBUG printf("\n can simplify in negation\n");
            NegatedFormula = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula;
            AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
FormulaWithVariables->Formula = NegatedFormula->
FormulaUnion.UnaryFormula.Formula;
            Free((void **)&NegatedFormula);
        } else {
            NegateFormula(&(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula),
Simplify);
        }
        return(1);
    } else {
        return(0);
    }
}
//-----------------------------------------------------------------------------
void UniqueifyVariableNames(ANNOTATEDFORMULA AnnotatedFormula) {
    
    VARIABLENODE VariableNode;
    VARIABLENODE SameNameNode;
    int UniqueIndex;
    String NewName;

    if (!CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) &&
!CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        CodingError("Trying to rename variables in a non-formula");
    }

    UniqueIndex = 1;
    VariableNode = AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables;
    while (VariableNode != NULL) {
        SameNameNode = VariableNode->NextVariable;
        while (SameNameNode != NULL) {
            if (VariableNode->VariableName == SameNameNode->VariableName) {
                sprintf(NewName,"%s_NN_%d",
GetSignatureSymbol(VariableNode->VariableName),UniqueIndex++);
                SameNameNode->VariableName = InsertIntoSignatureList(
&(VariableNode->VariableName->NextSymbol),NewName,0);
                IncreaseSymbolUseCount(VariableNode->VariableName,-1);
            }
           SameNameNode = SameNameNode->NextVariable;
        }
        VariableNode = VariableNode->NextVariable;
    }
}
//-----------------------------------------------------------------------------
int RemoveVacuousQuantifiersFromFormula(FORMULA * TheFormula,
VARIABLENODE * TheVariables) {

    VARIABLENODE * VariableNodePtr;
    VARIABLENODE VariableNode;
    FORMULA FormulaNode;

//DEBUG printf("Entering RemoveVacuousQuantifiersFromFormula for\n");
//DEBUG PrintTSTPFormula(stdout,*TheFormula,0,0,1,outermost,outermost,0);
//DEBUG printf("\n");
    switch ((*TheFormula)->Type) {
        case quantified:
            if ((*TheFormula)->FormulaUnion.QuantifiedFormula.Variable->
TheSymbol.Variable->NumberOfUses == 1) {
//----Find and remove the variable node
//DEBUG printf("Remove singleton %s\n",(*TheFormula)->FormulaUnion.QuantifiedFormula.Variable->TheSymbol.Variable->VariableName->NameSymbol);
                VariableNodePtr = TheVariables;
                while (*VariableNodePtr != (*TheFormula)->
FormulaUnion.QuantifiedFormula.Variable->TheSymbol.Variable) {
                    VariableNodePtr = &((*VariableNodePtr)->NextVariable);
                }
                IncreaseSymbolUseCount((*VariableNodePtr)->VariableName,-1);
//DEBUG printf("Count in sig is now %d\n",(*VariableNodePtr)->VariableName->NumberOfUses);
                VariableNode = *VariableNodePtr;
                *VariableNodePtr = VariableNode->NextVariable;
                Free((void **)&VariableNode);
//----Bypass the formula node
                FormulaNode = *TheFormula;
                *TheFormula = FormulaNode->
FormulaUnion.QuantifiedFormula.Formula;
                Free((void **)&FormulaNode);
//----Start again at the same place for next formula
                return(1 + RemoveVacuousQuantifiersFromFormula(TheFormula,
TheVariables));
            } else {
                return(RemoveVacuousQuantifiersFromFormula(&((*TheFormula)->FormulaUnion.QuantifiedFormula.Formula),TheVariables));
            }
            break;
        case binary:
            return(RemoveVacuousQuantifiersFromFormula(&((*TheFormula)->
FormulaUnion.BinaryFormula.LHS),TheVariables)
+ RemoveVacuousQuantifiersFromFormula(&((*TheFormula)->
FormulaUnion.BinaryFormula.RHS),TheVariables));
            break;
        case unary:
            return(RemoveVacuousQuantifiersFromFormula(&((*TheFormula)->
FormulaUnion.UnaryFormula.Formula),TheVariables));
            break;
        case atom:
            return(0);
            break;
        default:
            printf("ERROR: Formula type unknown for removing vacuous qs\n");
            exit(EXIT_FAILURE);
            break;
    }

}
//-----------------------------------------------------------------------------
int RemoveVacuousQuantifiersFromAnnotatedFormula(
ANNOTATEDFORMULA AnnotatedFormula) {

    if (!CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) &&
!CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        CodingError("Trying to remove vacuous quantifiers in a non-formula");
    }
    
    return(RemoveVacuousQuantifiersFromFormula(&(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula),
&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
FormulaWithVariables->Variables)));
    
}
//-----------------------------------------------------------------------------
int UniversalFOFify(ANNOTATEDFORMULA AnnotatedFormula) {

    FORMULA UnquantifiedFormula;
    VARIABLENODE VariableNode;
    FORMULA QuantifiedFormula;

    if (!CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) &&
!CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        CodingError("Trying to rename variables in a non-formula");
    }

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        UnquantifiedFormula = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula;

//----Go through all variables on formula's list
        VariableNode = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables;
        while (VariableNode != NULL) {
            QuantifiedFormula = NewFormula();
            QuantifiedFormula->Type = quantified;
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Quantifier =
universal;
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Variable =
NewTerm();
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Variable->Type = 
variable;
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Variable->TheSymbol.Variable = VariableNode;
            IncreaseVariableUseCount(VariableNode,1);
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Formula = 
AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula;
            AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula =
QuantifiedFormula;
            VariableNode = VariableNode->NextVariable;
        }
//----And viola, it's FOF
        SetSyntax(AnnotatedFormula,tptp_fof);
        return(1);
    } else {
        return(0);
    }
}
//-----------------------------------------------------------------------------
void EnsureLongForm(ANNOTATEDFORMULA AnnotatedFormula,SIGNATURE Signature) {

    if (AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source ==
NULL) {
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source = 
ParseStringTerm("unknown",Signature);
    }

    if (AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo == NULL) {
        AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo = 
ParseStringTerm("[]",Signature);
    }
}
//-----------------------------------------------------------------------------
int RemoveUsefulInformationFromAnnotatedFormula(
ANNOTATEDFORMULA AnnotatedFormula,char * PrincipleSymbol) {

    TERM UsefulInfoList;
    int Index;
    int MoveIndex;
    int NumberRemoved;

//----None if not a formula
    if (!CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) &&
!CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        return(0);
    }

//----None if not long form or not a list of useful info
    if (AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source ==
NULL || AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
UsefulInfo == NULL || AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo->TheSymbol.NonVariable->Arity != -1) {
        return(0);
    }

//----Look through useful info list and remove all with this symbol
    UsefulInfoList = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo;
    NumberRemoved = 0;
    Index = 0;
    while (Index < UsefulInfoList->FlexibleArity) {
        if (!strcmp(PrincipleSymbol,UsefulInfoList->Arguments[Index]->
TheSymbol.NonVariable->NameSymbol)) {
            FreeTerm(&(UsefulInfoList->Arguments[Index]),NULL);
            for (MoveIndex = Index+1; MoveIndex < UsefulInfoList->FlexibleArity;
MoveIndex++) {
                UsefulInfoList->Arguments[MoveIndex-1] = 
UsefulInfoList->Arguments[MoveIndex];
            }
            UsefulInfoList->FlexibleArity--;
            NumberRemoved++;
        } else {
            Index++;
        }
    }

    return(NumberRemoved);
}
//-----------------------------------------------------------------------------
int AddUsefulInformationToAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature,char * UsefulInformation) {

    TERM UsefulInfoTerm;
    TERM UsefulInfoList;

    if (!CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) &&
!CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        return(0);
    }

    if ((UsefulInfoTerm = ParseStringTerm(UsefulInformation,Signature)) == 
NULL) {
        return(0);
    }

//----Add source and useful info if there wasn't one before
    EnsureLongForm(AnnotatedFormula,Signature);

//----Add in new useful info
    UsefulInfoList = AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo;
    UsefulInfoList->FlexibleArity++;
    UsefulInfoList->Arguments = 
(TERMArray)Realloc((void *)UsefulInfoList->Arguments,
UsefulInfoList->FlexibleArity * sizeof(TERM));
    UsefulInfoList->Arguments[UsefulInfoList->FlexibleArity - 1] =
UsefulInfoTerm;
    
    return(1);
}
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "Examine.h"
#include "List.h"
#include "Modify.h"
#include "PrintTSTP.h"
//-------------------------------------------------------------------------------------------------
int SetName(ANNOTATEDFORMULA AnnotatedFormula,char * Name) {

    assert(AnnotatedFormula != NULL);
    if (ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        Free((void **)&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name));
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Name = CopyHeapString(Name);
        return(1);
    } else {
        return(0);
    }   

}
//-------------------------------------------------------------------------------------------------
//----Use with care - you're breaking the logic
int SetSyntax(ANNOTATEDFORMULA AnnotatedFormula,SyntaxType Syntax) {

    assert(AnnotatedFormula != NULL);
    if (ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        AnnotatedFormula->Syntax = Syntax;
        return(1);
    } else {
        return(0);
    }   
}
//-------------------------------------------------------------------------------------------------
int SetStatus(ANNOTATEDFORMULA AnnotatedFormula,StatusType Status,TERM SubStatus) {

    assert(AnnotatedFormula != NULL);
    if (ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Status = Status;
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.SubStatus = SubStatus;
        return(1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
void UninterpretNumbers(SYMBOLNODE Symbols,int Quote) {

    char * NotNumber;

    if (Symbols != NULL) {
        if (Symbols->Arity == 0 && LooksLikeANumber(Symbols->NameSymbol)) {
            if (Quote) {
                NotNumber = (char *)Malloc(strlen(Symbols->NameSymbol) + 3);
                strcpy(NotNumber,"\"");
                strcat(NotNumber,Symbols->NameSymbol);
                strcat(NotNumber,"\"");
            } else {
                NotNumber = (char *)Malloc(strlen(Symbols->NameSymbol) + 5);
                if (Symbols->NameSymbol[0] == '-') {
                    strcpy(NotNumber,"nn__");
                    strcat(NotNumber,&(Symbols->NameSymbol[1]));
                } else {
                    strcpy(NotNumber,"np__");
                    strcat(NotNumber,Symbols->NameSymbol);
                }
            }
            Free((void **)&(Symbols->NameSymbol));
            Symbols->NameSymbol = NotNumber;
        }
        UninterpretNumbers(Symbols->LastSymbol,Quote);
        UninterpretNumbers(Symbols->NextSymbol,Quote);
    }
}
//-------------------------------------------------------------------------------------------------
void UninterpretNumbersInSignature(SIGNATURE Signature,int Quote) {

    UninterpretNumbers(Signature->Functions,Quote);
//----Need to do predicates too for THF
    UninterpretNumbers(Signature->Predicates,Quote);
}
//-------------------------------------------------------------------------------------------------
void ShortenSymbols(SYMBOLNODE Symbols,char * FormatString,int MallocLength,
long * SymbolIndex) {

    char * ShortSymbol;

    if (Symbols != NULL) {
        if(strcmp(Symbols->NameSymbol,"=") && 
*(Symbols->NameSymbol) != '$' && !isdigit(*(Symbols->NameSymbol)) &&
*(Symbols->NameSymbol) != '-' && *(Symbols->NameSymbol) != '+' &&
*(Symbols->NameSymbol) != '"') {
            ShortSymbol = (char *)Malloc(MallocLength);
            sprintf(ShortSymbol,FormatString,*SymbolIndex);
            Free((void **)&(Symbols->NameSymbol));
            Symbols->NameSymbol = ShortSymbol;
            (*SymbolIndex)++;
        }
        ShortenSymbols(Symbols->LastSymbol,FormatString,MallocLength,SymbolIndex);
        ShortenSymbols(Symbols->NextSymbol,FormatString,MallocLength,SymbolIndex);
    }
}
//-------------------------------------------------------------------------------------------------
void ShortenSymbolType(SYMBOLNODE Symbols,char ShortChar) {

    int NumberOfSymbols,NumberOfSymbolsArity0,MinSymbolArity,MaxSymbolArity,DummyCounter;
    int NumberOfDigits;
    String FormatString;
    long SymbolIndex = 1;

    GetSignatureSymbolUsageStatistics(Symbols,&NumberOfSymbols,&NumberOfSymbolsArity0,
&DummyCounter,&MinSymbolArity,&MaxSymbolArity);
    NumberOfDigits = (int)ceil(log10(NumberOfSymbols+1));
    sprintf(FormatString,"%c%%0%dld",ShortChar,NumberOfDigits);
    ShortenSymbols(Symbols,FormatString,NumberOfDigits+2,&SymbolIndex);

}
//-------------------------------------------------------------------------------------------------
void ShortenSymbolsInSignature(SIGNATURE Signature) {

    ShortenSymbolType(Signature->Variables,'X');
    ShortenSymbolType(Signature->Functions,'f');
    ShortenSymbolType(Signature->Predicates,'p');
}
//-------------------------------------------------------------------------------------------------
void AritizeSymbols(SYMBOLNODE Symbols) {

    char * SymbolAndArity;;
    int SingleQuoted;

    if (Symbols != NULL) {
        if (Symbols->NameSymbol[0] != '$' && Symbols->NameSymbol[0] != '"' &&
!isdigit(Symbols->NameSymbol[0]) && strcmp(Symbols->NameSymbol,"=")) {
            SymbolAndArity = (char *)Malloc(strlen(Symbols->NameSymbol) + 5);
            if (Symbols->NameSymbol[0] == '\'') {
                SingleQuoted = 1;
                Symbols->NameSymbol[strlen(Symbols->NameSymbol)-1] = '\0';
            } else {
                SingleQuoted = 0;
            }
            sprintf(SymbolAndArity,"%s__%02d%s",Symbols->NameSymbol,
Symbols->Arity,SingleQuoted?"'":"");
            Free((void **)&(Symbols->NameSymbol));
            Symbols->NameSymbol = SymbolAndArity;
        }
        AritizeSymbols(Symbols->LastSymbol);
        AritizeSymbols(Symbols->NextSymbol);
    }
}
//-------------------------------------------------------------------------------------------------
void AritizeSymbolsInSignature(SIGNATURE Signature) {
    
    AritizeSymbols(Signature->Functions);
    AritizeSymbols(Signature->Predicates);
}
//-------------------------------------------------------------------------------------------------
void DequoteSymbols(SYMBOLNODE Symbols) {

    int TakeIndex;
    int PutIndex;

    if (Symbols != NULL) {
        if (Symbols->NameSymbol[0] == '\'') {
            TakeIndex = 1;
            if (!islower(Symbols->NameSymbol[1])) {
                Symbols->NameSymbol[0] = 'z';
                PutIndex = 1;
            } else {
                PutIndex = 0;
            }
//----Stop at final '
            while (Symbols->NameSymbol[TakeIndex+1] != '\0') {
                if (!isalnum(Symbols->NameSymbol[TakeIndex])) {
                    Symbols->NameSymbol[PutIndex] = '_';
                } else {
                    Symbols->NameSymbol[PutIndex] = 
Symbols->NameSymbol[TakeIndex];
                }
                TakeIndex++;
                PutIndex++;
            }
            Symbols->NameSymbol[PutIndex] = '\0';
        }
        DequoteSymbols(Symbols->LastSymbol);
        DequoteSymbols(Symbols->NextSymbol);
    }
}
//-------------------------------------------------------------------------------------------------
void DequoteSymbolsInSignature(SIGNATURE Signature) {
    
    DequoteSymbols(Signature->Functions);
    DequoteSymbols(Signature->Predicates);
}
//-------------------------------------------------------------------------------------------------
void AppendVariableList(VARIABLENODE * OntoThis,VARIABLENODE AppendThis) {

//----Move down to the end of the onto list
    while (*OntoThis != NULL) {
        OntoThis = &((*OntoThis)->NextVariable);
    }
//----Stick the append list on the end
    *OntoThis = AppendThis;
}
//-------------------------------------------------------------------------------------------------
void ExpandAnnotatedFormulaAssumptions(ANNOTATEDFORMULA AnnotatedFormula,LISTNODE AllFormula,
SIGNATURE Signature) {

    TERM FormulaAssumptionsTerm;
    char * FormulaAssumptions;
    StringParts AssumptionNames;
    int NumberOfAssumptions;
    char * ParentNames;
    int AssumptionNumber;
    ANNOTATEDFORMULA Assumption;
    FORMULAWITHVARIABLES Antecedent;
    FORMULA AssumptionFormula;
    char * AllDischargedNames;
    StringParts DischargeNames;
    int NumberOfDischarges;
    int DischargeNumber;
    TERM DischargedNamesList;
    String ErrorMessage;

//DEBUG printf("------- Expanding assumptions in\n");
//DEBUG PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);

//----Get parents' names
    ParentNames = GetNodeParentNames(AnnotatedFormula,NULL);
    if ((FormulaAssumptionsTerm = GetInferenceInfoTERM(AnnotatedFormula,
"assumptions")) != NULL) {
//----Get assumptions' names
        FormulaAssumptions = ExtractAssumptionsList(FormulaAssumptionsTerm);
//DEBUG printf("FormulaAssumptions are %s\n",FormulaAssumptions);
        NumberOfAssumptions = Tokenize(FormulaAssumptions,AssumptionNames,",");
//DEBUG printf("NumberOfAssumptions is %d\n",NumberOfAssumptions);
        for (AssumptionNumber=0;AssumptionNumber < NumberOfAssumptions;
AssumptionNumber++) {
//----Get assumption annotated formula from list
            if ((Assumption = GetAnnotatedFormulaFromListByName(AllFormula,
AssumptionNames[AssumptionNumber])) == NULL) {
                sprintf(ErrorMessage,"Missing assumption %s",
AssumptionNames[0]);
                ReportError("SemanticError",ErrorMessage,0);
                return;
            }
//DEBUG printf("The assumption %s is\n",AssumptionNames[AssumptionNumber]);
//DEBUG PrintAnnotatedTSTPNode(stdout,Assumption,tptp,1);
//----Duplicate the logical part
            Antecedent = DuplicateFormulaWithVariables(Assumption->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables,Signature,1);
//----Make a new node for the implication
            AssumptionFormula = NewFormula();
            AssumptionFormula->Type = binary;
            AssumptionFormula->FormulaUnion.BinaryFormula.Connective = 
implication;
            AssumptionFormula->FormulaUnion.BinaryFormula.LHS = Antecedent->
Formula;
            AssumptionFormula->FormulaUnion.BinaryFormula.RHS = 
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
FormulaWithVariables->Formula;
//----Combine the variable lists
            AppendVariableList(&(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Variables),Antecedent->Variables);
//----Free the node - we stole the components
            Free((void **)&Antecedent);
//----Update the original to use this new formula
            AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
FormulaWithVariables->Formula = AssumptionFormula;
//----Remove the assumption parent if exists
            if (NameInList(AssumptionNames[AssumptionNumber],ParentNames)) {
                RemoveParentFromInferenceTerm(AssumptionNames[AssumptionNumber],
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source,Signature);
                RemoveNameFromList(AssumptionNames[AssumptionNumber],
ParentNames);
            }
//DEBUG printf("New formula with assumption removed is\n");
//DEBUG PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
        }

//----Free memory
        if (FormulaAssumptions != NULL) {
            Free((void **)&FormulaAssumptions);
        }
//----Remove the assumption record 
        DoUpdateRecordInList(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.Source->Arguments[1],Signature,"assumptions",1,0);
//DEBUG printf("New formula with all assumptions removed is\n");
//DEBUG PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    }

//----Remove any discharges, as they are now unused
    AllDischargedNames = GetDischargedNames(AnnotatedFormula,
&DischargedNamesList);
    if (AllDischargedNames != NULL) {
//----Get the list of discharge name
        NumberOfDischarges = Tokenize(AllDischargedNames,DischargeNames,",");
        for (DischargeNumber=0;DischargeNumber < NumberOfDischarges;
DischargeNumber++) {
            if (NameInList(DischargeNames[DischargeNumber],ParentNames)) {
                RemoveParentFromInferenceTerm(DischargeNames[DischargeNumber],
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source,Signature);
                RemoveNameFromList(DischargeNames[DischargeNumber],
ParentNames);
            }
            RemoveNamedTermFromList(DischargeNames[DischargeNumber],DischargedNamesList,-1,
Signature);
        }
        if (AllDischargedNames != NULL) {
            Free((void **)&AllDischargedNames);
        }
    }
    Free((void **)&ParentNames);
//DEBUG printf("New formula with all assumptions and discharges removed is\n");
//DEBUG PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
}
//-------------------------------------------------------------------------------------------------
void ExpandListAssumptions(LISTNODE Head,SIGNATURE Signature) {

    LISTNODE Target;

    Target = Head;
    while (Target != NULL) {
        ExpandAnnotatedFormulaAssumptions(Target->AnnotatedFormula,Head,
Signature);
        Target = Target->Next;
    }
}
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
int DeDoubleNegate(ANNOTATEDFORMULA AnnotatedFormula) {

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof)) {
        DeDoubleNegateFormula(&(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula));
        return(1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
void NegateFormula(FORMULA * Formula) {

    FORMULA NegatedFormula;

    NegatedFormula = NewFormula();
    NegatedFormula->Type = unary;
    NegatedFormula->FormulaUnion.UnaryFormula.Connective = negation;
    NegatedFormula->FormulaUnion.UnaryFormula.Formula = *Formula;
    *Formula = NegatedFormula;
}
//-------------------------------------------------------------------------------------------------
int Negate(ANNOTATEDFORMULA AnnotatedFormula,int Simplify) {

    FORMULA NegatedFormula;

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_tcf) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_tff) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_thf)) {
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
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula));
        }
        return(1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int NegateListOfAnnotatedTSTPNodes(LISTNODE Head,int Simplify) {

    LISTNODE Reverse;

    Reverse = Head;
    while (Head != NULL && Negate(Head->AnnotatedFormula,Simplify)) {
        Head = Head->Next;
    }

//----If could not do all then reverse earlier ones
    if (Head == NULL) {
        return(1);
    } else {
        while (Reverse != Head) {
            Negate(Reverse->AnnotatedFormula,1);
            Reverse = Reverse->Next;
        }
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
int NegateConjectures(LISTNODE Head,int Simplify) {

    int NumberNegated;

    NumberNegated = 0;
    while (Head != NULL) {
        if (LogicalAnnotatedFormulaWithRole(Head->AnnotatedFormula,conjecture) &&
Negate(Head->AnnotatedFormula,Simplify)) {
            Head->AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
Status = negated_conjecture;
            NumberNegated++;
        }
        Head = Head->Next;
    }
    return(NumberNegated);
}
//-------------------------------------------------------------------------------------------------
void UniqueifyVariableNames(ANNOTATEDFORMULA AnnotatedFormula) {
    
    VARIABLENODE VariableNode;
    VARIABLENODE SameNameNode;
    int UniqueIndex;
    String NewName;

    if (!LogicalAnnotatedFormula(AnnotatedFormula)) {
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
&(VariableNode->VariableName->NextSymbol),NewName,0,-1,0,NULL);
                IncreaseSymbolUseCount(VariableNode->VariableName,-1);
            }
           SameNameNode = SameNameNode->NextVariable;
        }
        VariableNode = VariableNode->NextVariable;
    }
}
//-------------------------------------------------------------------------------------------------
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
        case applied_connective:
            return(0);
            break;
        default:
            CodingError("Formula type unknown for removing vacuous qs");
            return(0);
            break;
    }

}
//-------------------------------------------------------------------------------------------------
int RemoveVacuousQuantifiersFromAnnotatedFormula(
ANNOTATEDFORMULA AnnotatedFormula) {

    if (!LogicalAnnotatedFormula(AnnotatedFormula)) {
        CodingError("Trying to remove vacuous quantifiers in a non-formula");
    }
    
    return(RemoveVacuousQuantifiersFromFormula(&(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula),
&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
FormulaWithVariables->Variables)));
    
}
//-------------------------------------------------------------------------------------------------
void QuantifyFormula(FORMULA * UnquantifiedFormula,ConnectiveType Quantifier,
VARIABLENODE VariableNode) {

    FORMULA QuantifiedFormula;

    while (VariableNode != NULL) {
//----Check that it's a free variable
        if (VariableNode->Quantification == free_variable) {
//DEBUG printf("quantifying %s with quantification %d\n",VariableNode->VariableName->NameSymbol,VariableNode->Quantification);
            QuantifiedFormula = NewFormula();
            QuantifiedFormula->Type = quantified;
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Quantifier = Quantifier;
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.ExistentialCount = 0;
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.VariableType = NULL;
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Variable = NewTerm();
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Variable->Type = variable;
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Variable-> TheSymbol.Variable = 
VariableNode;
            IncreaseVariableUseCount(VariableNode,1);
            QuantifiedFormula->FormulaUnion.QuantifiedFormula.Formula = *UnquantifiedFormula;
            *UnquantifiedFormula = QuantifiedFormula;
        }
        VariableNode = VariableNode->NextVariable;
    }
}
//-------------------------------------------------------------------------------------------------
void Quantify(ANNOTATEDFORMULA AnnotatedFormula,ConnectiveType Quantifier) {

    if (Quantifier != universal && Quantifier != existential && Quantifier != lambda) {
        CodingError("Quantifying with a non-quantifier");
    }

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_thf) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_tcf) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_tff) ||
CheckAnnotatedFormula(AnnotatedFormula,tptp_fof)) {
        QuantifyFormula(&(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula),Quantifier,
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables);
    }
}
//-------------------------------------------------------------------------------------------------
void QuantifyList(LISTNODE Head,ConnectiveType Quantifier) {

    while (Head != NULL) {
        Quantify(Head->AnnotatedFormula,Quantifier);
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------
void FOFify(ANNOTATEDFORMULA AnnotatedFormula,ConnectiveType Quantifier) {

    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
        if (CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
            SetSyntax(AnnotatedFormula,tptp_fof);
            Quantify(AnnotatedFormula,Quantifier);
        }
    }
}
//-------------------------------------------------------------------------------------------------
void FOFifyList(LISTNODE Head,ConnectiveType Quantifier) {

    while (Head != NULL) {
        FOFify(Head->AnnotatedFormula,Quantifier);
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------
void RandomizeFormula(FORMULA Formula,unsigned int Seed) {

    TERM TempTerm;
    FORMULA TempFormula;

    SeedRand(Seed);

    switch (Formula->Type) {
        case quantified:
            RandomizeFormula(Formula->FormulaUnion.QuantifiedFormula.Formula,0);
            break;
        case binary:
            RandomizeFormula(Formula->FormulaUnion.BinaryFormula.LHS,0);
            RandomizeFormula(Formula->FormulaUnion.BinaryFormula.RHS,0);
            if ((Symmetric(Formula->FormulaUnion.BinaryFormula.Connective) ||
Formula->FormulaUnion.BinaryFormula.Connective == implication || 
Formula->FormulaUnion.BinaryFormula.Connective == reverseimplication) &&
rand() % 2) {
                TempFormula = Formula->FormulaUnion.BinaryFormula.LHS;
                Formula->FormulaUnion.BinaryFormula.LHS =
Formula->FormulaUnion.BinaryFormula.RHS;
                Formula->FormulaUnion.BinaryFormula.RHS = TempFormula;
                Formula->FormulaUnion.BinaryFormula.Connective =
(Formula->FormulaUnion.BinaryFormula.Connective == implication ? 
reverseimplication : (Formula->FormulaUnion.BinaryFormula.Connective == 
reverseimplication ? implication : Formula->FormulaUnion.BinaryFormula.Connective));
            } 
            break;
        case unary:
            RandomizeFormula(Formula->FormulaUnion.UnaryFormula.Formula,0);
            break;
        case atom:
        case applied_connective:
//----Switch equalities
            if (!strcmp(GetSymbol(Formula->FormulaUnion.Atom),"=") && 
GetArity(Formula->FormulaUnion.Atom) == 2 && rand() % 2) {
                TempTerm = Formula->FormulaUnion.Atom->Arguments[0];
                Formula->FormulaUnion.Atom->Arguments[0] =
Formula->FormulaUnion.Atom->Arguments[1];
                Formula->FormulaUnion.Atom->Arguments[1] = TempTerm;
            }
            break;
        default:
            CodingError("Formula type unknown for randomize");
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void RandomizeAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
unsigned int Seed) {

    SeedRand(Seed);
    if (LogicalAnnotatedFormula(AnnotatedFormula)) {
        RandomizeFormula(AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula,0);
    }
}
//-------------------------------------------------------------------------------------------------
void EnsureShortForm(ANNOTATEDFORMULA AnnotatedFormula,SIGNATURE Signature) {

    if (ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        FreeTerm(&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),Signature,
&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables));
        FreeTerm(&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo),
Signature,
&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables));
    }
}
//-------------------------------------------------------------------------------------------------
void EnsureLongForm(ANNOTATEDFORMULA AnnotatedFormula,SIGNATURE Signature) {

    if (ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        if (AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source == NULL) {
            AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source = 
ParseStringTerm("unknown",nontype,Signature,0);
        }

        if (AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo == NULL) {
            AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo = 
ParseStringTerm("[]",nontype,Signature,0);
        }
    }
}
//-------------------------------------------------------------------------------------------------
void DoUpdateRecordInList(TERM TheList,SIGNATURE Signature,char * UsefulInformation,int DoRemove,
int DoAdd) {

    char * Open;
    String Symbol;
    TERM ListTerm;
    int NumberRemoved;
    int NumberAdded;
    int Index;
    int MoveIndex;

//----Check that the new term is well formed
    if (DoAdd && (ListTerm = ParseStringTerm(UsefulInformation,nontype,Signature,0)) == NULL) {
        ListTerm = NULL;
        CodingError("Trying to add a bad term as useful info");
    }

//----Extract the principle symbol
    Open = UsefulInformation;
    Index = 0;
    Symbol[Index] = '\0';
    while (Index < STRINGLENGTH && *Open != '(' && *Open != '\0') {
        Symbol[Index++] = *Open;
        Open += 1;
    }
    if (Index == STRINGLENGTH) {
        CodingError("UsefulInformation symbol too long for processing");
    }
    Symbol[Index] = '\0';

//----Done so that new info is placed is position if first old one
//----Look through useful info list and remove all with this symbol
    NumberRemoved = 0;
    NumberAdded = 0;
    Index = 0;
    while (Index < TheList->FlexibleArity) {
//----Check for the functor of the record to be removed
        if (!strcmp(Symbol,TheList->Arguments[Index]->TheSymbol.NonVariable->NameSymbol)) {
            if (DoRemove) {
                FreeTerm(&(TheList->Arguments[Index]),Signature,NULL);
                if (DoAdd && NumberRemoved == 0) {
                    TheList->Arguments[Index] = ListTerm;
                    NumberAdded = 1;
                    Index++;
                } else {
                    for (MoveIndex = Index+1; MoveIndex < TheList->FlexibleArity;MoveIndex++) {
                        TheList->Arguments[MoveIndex-1] = TheList->Arguments[MoveIndex];
                    }
                    TheList->FlexibleArity--;
                }
                NumberRemoved++;
            } else {
                Index++;
            }
        } else {
            Index++;
        }
    }

//----Add in new useful info if not done by replacement
    if (DoAdd && NumberAdded == 0) {
        TheList->FlexibleArity++;
        TheList->Arguments = (TERMArray)Realloc((void *)TheList->Arguments,
TheList->FlexibleArity * sizeof(TERM));
        TheList->Arguments[TheList->FlexibleArity - 1] = ListTerm;
    }
}
//-------------------------------------------------------------------------------------------------
int RemoveNamedTermFromList(char * Name,TERM TheList,int MaxToRemove,SIGNATURE Signature) {

    int ListIndex;
    int NumberRemoved;

//----Check that it looks like a list
    if (!LooksLikeAList(TheList,-1,-1)) {
        CodingError("Trying to removes from not a list");
    }

//----Loop through the parents looking for one to remove
    NumberRemoved = 0;
    ListIndex = 0;
    while (ListIndex < TheList->FlexibleArity &&
(NumberRemoved < MaxToRemove || MaxToRemove == -1)) {
//----If found then free and shift up the rest and realloc for less memory
        if (!strcmp(Name,GetSymbol(TheList->Arguments[ListIndex]))) {
            FreeTerm(&(TheList->Arguments[ListIndex]),Signature,NULL);
            while (ListIndex < TheList->FlexibleArity - 1) {
                TheList->Arguments[ListIndex] = TheList->Arguments[ListIndex+1];
                ListIndex++;
            }
            TheList->FlexibleArity--;
            TheList->Arguments = (TERMArray)Realloc((void *)TheList->Arguments,
TheList->FlexibleArity * sizeof(TERM));
            NumberRemoved++;
        } else {
            ListIndex++;
        }
    }
    return(NumberRemoved);
}
//-------------------------------------------------------------------------------------------------
int RemoveParentFromInferenceTerm(char * ParentName,TERM Source,SIGNATURE Signature) {

//----Nothing if not an inference term
    if (strcmp(GetSymbol(Source),"inference") || GetArity(Source) != 3 ||
GetArity(Source->Arguments[2]) == -1) {
        return(0);
    }

    return(RemoveNamedTermFromList(ParentName,Source->Arguments[2],-1,Signature) > 0);
}
//-------------------------------------------------------------------------------------------------
int SetSourceFromString(ANNOTATEDFORMULA AnnotatedFormula,SIGNATURE Signature,
char * SourceString) {

    TERM Source;

    if (ReallyAnAnnotatedFormula(AnnotatedFormula) &&
(Source = ParseStringTerm(SourceString,nontype,Signature,0)) != NULL) {
        FreeTerm(&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source),Signature,
&(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables));
        AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.Source = Source;
        return(1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
void DoUpdateUsefulInformationInAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature, char * UsefulInformation,int DoRemove,int DoAdd) {

    if (!ReallyAnAnnotatedFormula(AnnotatedFormula)) {
        CodingError("Trying to add useful info to a non-formula");
    }

//----Add source and useful info if there wasn't one before
    EnsureLongForm(AnnotatedFormula,Signature);
//----Get pointer to the list
    DoUpdateRecordInList(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.UsefulInfo,
Signature,UsefulInformation,DoRemove,DoAdd);
}
//-------------------------------------------------------------------------------------------------
void RemoveUsefulInformationFromAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature,char * PrincipleSymbol) {

    DoUpdateUsefulInformationInAnnotatedFormula(AnnotatedFormula,Signature,PrincipleSymbol,1,0);
}
//-------------------------------------------------------------------------------------------------
void AddUsefulInformationToAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature,char * UsefulInformation) {

    DoUpdateUsefulInformationInAnnotatedFormula(AnnotatedFormula,Signature,UsefulInformation,0,1);
}
//-------------------------------------------------------------------------------------------------
void UpdateUsefulInformationInAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
SIGNATURE Signature,char * UsefulInformation) { 

    DoUpdateUsefulInformationInAnnotatedFormula(AnnotatedFormula,Signature,UsefulInformation,1,1);
}
//-------------------------------------------------------------------------------------------------
void StandardizeFormula(FORMULA * Formula) {

    switch ((*Formula)->Type) {
        case quantified:
            StandardizeFormula(&((*Formula)->FormulaUnion.QuantifiedFormula.Formula));
            break;
        case binary:
        {
            BinaryFormulaType * BinaryFormula = &((*Formula)->FormulaUnion.BinaryFormula);
            switch (BinaryFormula->Connective) {
                case reverseimplication:
                {
                    FORMULA Tmp = BinaryFormula->LHS;
                    BinaryFormula->LHS = BinaryFormula->RHS;
                    BinaryFormula->RHS = Tmp;
                    BinaryFormula->Connective = implication;
                    break;
                }
                case nonequivalence:
                {
                    FORMULA NegatedFormula = NewFormula();
                    NegatedFormula->Type = unary;
                    NegatedFormula->FormulaUnion.UnaryFormula.Connective = negation;
                    NegatedFormula->FormulaUnion.UnaryFormula.Formula = *Formula;
                    BinaryFormula->Connective = equivalence;
                    *Formula = NegatedFormula;
                    break;
                }
                case negateddisjunction:
                {
                    FORMULA NegatedFormula = NewFormula();
                    NegatedFormula->Type = unary;
                    NegatedFormula->FormulaUnion.UnaryFormula.Connective = negation;
                    NegatedFormula->FormulaUnion.UnaryFormula.Formula = *Formula;
                    BinaryFormula->Connective = conjunction;
                    *Formula = NegatedFormula;
                    break;
                }
                case negatedconjunction:
                {
                    FORMULA NegatedFormula = NewFormula();
                    NegatedFormula->Type = unary;
                    NegatedFormula->FormulaUnion.UnaryFormula.Connective = negation;
                    NegatedFormula->FormulaUnion.UnaryFormula.Formula = *Formula;
                    BinaryFormula->Connective = conjunction;
                    *Formula = NegatedFormula;
                    break;
                }
                default:
                    break;
            }
            StandardizeFormula(&(BinaryFormula->LHS));
            StandardizeFormula(&(BinaryFormula->RHS));
            break;
        }
        case unary:
            StandardizeFormula(&((*Formula)->FormulaUnion.UnaryFormula.Formula));
            break;
        case atom:
        case applied_connective:
            break;
        default:
            CodingError("ERROR: Not a formula type for standardization");
            break;
    }
}
//-------------------------------------------------------------------------------------------------
void StandardizeAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula) {

    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_fof)) {
        StandardizeFormula(&(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula));
    }
}
//-------------------------------------------------------------------------------------------------
void StandardizeListOfAnnotatedTSTPNodes(LISTNODE Head) {

    while (Head != NULL) {
        StandardizeAnnotatedFormula(Head->AnnotatedFormula);
        Head = Head->Next;
    }
}
//-------------------------------------------------------------------------------------------------

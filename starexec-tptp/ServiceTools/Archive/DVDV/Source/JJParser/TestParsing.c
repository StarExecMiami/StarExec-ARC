#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "Compare.h"
#include "Modify.h"
#include "List.h"
#include "ListStatistics.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    LISTNODE Head;
    LISTNODE AnotherHead;
    String InferenceRule;
    String PutNamesHere;
    SIGNATURE Signature;
    ANNOTATEDFORMULA AnnotatedFormula;
    ANNOTATEDFORMULA AnotherAnnotatedFormula;
    ANNOTATEDFORMULA DuplicatedAnnotatedFormula;
    FORMULA Literal;
    FORMULA AnotherLiteral;
    String SomeString;
    char * SymbolUsage;
    char * AnotherSymbolUsage;
    char * VariablesStartHere;
    int SymbolUsageLength = STRINGLENGTH;
    int VarCount,QuantCount;
    StatusType SubStatus;
    TERM ANewTerm;
    int Positive,Negative;
    READFILE Stream; 
    ListStatisticsRecordType ListStatistics;
    int Universals,Existentials;
    int NumberRemoved;
    ContextType Context;

//----One signature for all testing
    Signature = NewSignature();

//----Read from file or stdin
    SetNeedForNonLogicTokens(1);
    if (argc > 1) {
        Head = ParseFileOfFormulae(argv[1],Signature,1,NULL);
    } else {
        Head = ParseFILEOfFormulae(stdin,Signature,1,NULL);
    }
    PrintListOfAnnotatedTSTPNodes(stdout,Head,tptp);
    return(EXIT_SUCCESS);

//-----------------------------------------------------------------------------
//----Test getting inference rule
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    if (GetInferenceRule(AnnotatedFormula,InferenceRule) != NULL) {
        printf("The inference rule is ==%s==\n",InferenceRule);
    }
    if (GetParentNames(AnnotatedFormula,PutNamesHere) != NULL) {
        printf("The parents are ==%s==\n",PutNamesHere);
    }
    if (GetInferenceInfoTerm(AnnotatedFormula,"status",SomeString) != 
NULL) {
        printf("The %s term is %s\n",InferenceRule,SomeString);
    }
    return(EXIT_SUCCESS);

//----Test comparison of first two formula for being the same
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    AnotherAnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,2);
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    PrintAnnotatedTSTPNode(stdout,AnotherAnnotatedFormula,tptp,1);
    if (SameFormulaInAnnotatedFormula(AnnotatedFormula,
AnotherAnnotatedFormula,0)) {
        printf("They are identical\n");
    } else {
        if (SameFormulaInAnnotatedFormula(AnnotatedFormula,
AnotherAnnotatedFormula,1)) {
            printf("They are renamings\n");
        } else {
            printf("They are quite different\n");
        }
    }
    return(EXIT_SUCCESS);

//----Test getting symbol usage in general
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    SymbolUsage = (char *)Malloc(sizeof(String));
    if (GetAnnotatedFormulaSymbolUsage(AnnotatedFormula,&SymbolUsage,
&AnotherSymbolUsage) != NULL) {
        printf("The total symbol usage is \n%s and the functors are \n%s\n",
SymbolUsage,AnotherSymbolUsage);
    } else {
        printf("No total symbol usage collected\n");
    }
    Free((void **)&SymbolUsage);
    return(EXIT_SUCCESS);

//----Test duplication
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    if (AnnotatedFormula != NULL) {
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
        PrintVariableList(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables);
        PrintSignature(Signature);
        DuplicatedAnnotatedFormula = DuplicateAnnotatedFormula(AnnotatedFormula,
Signature);
        PrintAnnotatedTSTPNode(stdout,DuplicatedAnnotatedFormula,tptp,1);
        PrintVariableList(DuplicatedAnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables);
        PrintSignature(Signature);
    } else {
        printf("Could not get formula dv\n");
    }
    return(EXIT_SUCCESS);

//----Test internal formula copying
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    if (AnnotatedFormula != NULL) {
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
        PrintVariableList(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables);
        PrintSignature(Signature);
        Literal = AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula->FormulaUnion.QuantifiedFormula.Formula->FormulaUnion.BinaryFormula.LHS;
        Context.Signature = Signature;
        Context.Variables = &(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables);
        AnotherLiteral = DuplicateInternalFormulaWithVariables(
Literal,Context);
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
        printf("duplicate is ...\n");
        PrintTSTPFormula(stdout,AnotherLiteral,0,0,1,outermost,outermost,0);
        printf("\n");
        PrintVariableList(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables);
        PrintSignature(Signature);
    } else {
        printf("Could not get first formula\n");
    }
    return(EXIT_SUCCESS);

//----Test variable counting
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    if (AnnotatedFormula != NULL) {
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,0);
        VarCount = CountVariableUsageInFormula(AnnotatedFormula->
AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Formula,
AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.
FormulaWithVariables->Variables,&QuantCount);
        printf("First variable occurs %d times, plus quantified %d times\n",
VarCount,QuantCount);
    } else {
        printf("Could not get first formula\n");
    }
    return(EXIT_SUCCESS);

//----Test getting parents' names
    if (AnnotatedFormula != NULL) {
        printf("Parents are\n%s\n",GetParentNames(AnnotatedFormula,
PutNamesHere));
    } else {
        printf("Formula of that name not found\n");
    }
    return(EXIT_SUCCESS);

//----Test removal of vacuous quantifiers
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    if (AnnotatedFormula != NULL) {
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,0);
        PrintVariableList(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables);
        PrintSignature(Signature);
        NumberRemoved = RemoveVacuousQuantifiersFromAnnotatedFormula(
AnnotatedFormula);
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
        PrintVariableList(AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula.FormulaWithVariables->Variables);
        PrintSignature(Signature);
        printf("%d removed\n",NumberRemoved);
    } else {
        printf("Could not get first formula\n");
    }
    return(EXIT_SUCCESS);

//----Test removing useful information
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    if (AnnotatedFormula != NULL) {
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,0);
        PrintSignature(Signature);
        NumberRemoved = RemoveUsefulInformationFromAnnotatedFormula(
AnnotatedFormula,"useless");
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
        PrintSignature(Signature);
        printf("%d removed\n",NumberRemoved);
    } else {
        printf("Could not get formula dv\n");
    }
    return(EXIT_SUCCESS);

//----Test uniqueify variable names
    AnnotatedFormula = GetAnnotatedFormulaFromListByName(Head,"dv");
    if (AnnotatedFormula != NULL) {
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
        PrintSignature(Signature);
        UniqueifyVariableNames(AnnotatedFormula);
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
        PrintSignature(Signature);
    } else {
        printf("Could not get formula dv\n");
    }
    return(EXIT_SUCCESS);

//----Test freeing
    FreeListOfAnnotatedFormulae(&Head);
    assert(Head == NULL);
    return(EXIT_SUCCESS);

//----Test reading another file
    AnotherHead = ParseFileOfFormulae(argv[1],Signature,1,NULL);
    PrintListOfAnnotatedTSTPNodes(stdout,AnotherHead,tptp);
    return(EXIT_SUCCESS);

//----Test printing of all
    PrintListOfAnnotatedTSTPNodes(stdout,Head,tptp);
    return(EXIT_SUCCESS);

//----Reading formulae one-by-one from stdin. Ignore comments, etc
    if (argc > 1 && !strcmp(argv[1],"--")) {
        if ((Stream = OpenFILEFile(stdin)) != NULL) {
            SetNeedForNonLogicTokens(0);
            while (!CheckTokenType(Stream,endeof)) {
                AnnotatedFormula = ParseAnnotatedFormula(Stream,Signature);
                printf("-----------------------------\n");
                PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
                printf("That formula has %d unique variables\n",
CountAnnotatedFormulaUniqueVariables(AnnotatedFormula));
                fflush(stdout);
            }
            CloseFile(Stream);
        }
    }
    return(EXIT_SUCCESS);

//----Test negation or universal fofify
    AnnotatedFormula = GetAnnotatedFormulaFromListByName(Head,"22");
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    if (DeDoubleNegate(AnnotatedFormula)) {
        printf("Dedouble negated\n");
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    }
    UniversalFOFify(AnnotatedFormula);
    if (CheckAnnotatedFormula(AnnotatedFormula,tptp_cnf)) {
        UniversalFOFify(AnnotatedFormula);
    } else {
        Negate(AnnotatedFormula,1);
    }
    printf("negated (FOF) or fofified (CNF)\n");
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    return(EXIT_SUCCESS);

//----Test stats
    if (GetListStatistics(Head,&ListStatistics) != NULL) {
        PrintListStatistics(stdout,ListStatistics);
    } else {
        printf("Could not get statistics\n");
    }
    FreeListOfAnnotatedFormulae(&Head);
    assert(Head == NULL);
    return(EXIT_SUCCESS);

    AnnotatedFormula = GetAnnotatedFormulaFromListByName(Head,"pel47_14");
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    Universals = CountAnnotatedFormulaUniqueVariablesByUse(AnnotatedFormula,
-1,-1,universal);
    Existentials = CountAnnotatedFormulaUniqueVariablesByUse(AnnotatedFormula,
-1,-1,existential);
    printf("Universals = %d Existentials = %d\n",Universals,Existentials);
    return(EXIT_SUCCESS);

//----Test parsing of strings
    ANewTerm = ParseStringTerm("hello(there,my(BIG),friend)",Signature);
    printf("The term is ==");
    PrintTSTPTerm(stdout,ANewTerm,0);
    printf("==\n");

//----Test getting by name
    AnnotatedFormula = GetAnnotatedFormulaFromListByName(Head,"15");         
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    if (AnnotatedFormula != NULL) {
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
//----Test adding useful info
        assert(AddUsefulInformationToAnnotatedFormula(AnnotatedFormula,
Signature,"relevance(15)"));
        PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    }
    if (GetUsefulInfoTerm(AnnotatedFormula,"relevance",SomeString) != NULL) {
        printf("The relevance term is %s\n",SomeString);
    }

//----Test getting file source
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,1);
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    if (GetSource(AnnotatedFormula,SomeString) != NULL) {
        printf("The source is %s\n",SomeString);
        if (GetFileSourceNameAndNode(AnnotatedFormula,SomeString) != NULL) {
            printf("The file and node are %s\n",SomeString);
        } else {
            printf("No file and node\n");
        }
    } else {
        printf("No source for file and node\n");
    }


//----Test getting inference status
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,10);
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    if (GetSource(AnnotatedFormula,SomeString) != NULL) {
        printf("The source is %s\n",SomeString);
        if (GetInferenceInfoTerm(AnnotatedFormula,"status",SomeString) != NULL) {
            printf("The status term is %s\n",SomeString);
        } else {
            printf("No status term\n");
        }
    } else {
        printf("No source for status\n");
    }

//----Test getting by count
    printf("There are %d clauses\n",ListCount(Head,cnf_nodes));
    AnnotatedFormula = GetAnnotatedFormulaFromListByNumber(Head,20);
    GetName(AnnotatedFormula,PutNamesHere);
    printf("Got the node for clause named %s\n",PutNamesHere);
    printf("The status is %s\n",StatusToString(GetStatus(AnnotatedFormula,
&SubStatus)));
    if (SubStatus != nonstatus) {
        printf("The substatus is %s\n",StatusToString(SubStatus));
    } else {
        printf("It has no substatus\n");
    }
    if (GetInferenceRule(AnnotatedFormula,SomeString) != NULL) {
        printf("The inference rule is %s\n",SomeString);
    } else {
        printf("No inference rule found\n");
    }

//----Print symbol extraction
    PrintAnnotatedTSTPNode(stdout,AnnotatedFormula,tptp,1);
    if (CountLiteralsOfPolarity(AnnotatedFormula,&Positive,&Negative)) {
        printf("The clause has %d literals, %d positive, %d negative\n",
CountAnnotatedFormulaAtomsByPredicate(AnnotatedFormula,""),Positive,Negative);
    }
    if ((Literal = GetLiteralFromAnnotatedClauseByNumber(AnnotatedFormula,1))
!= NULL) {
        printf("The literal is ");
        PrintTSTPFormula(stdout,Literal,0,0,1,none,none,0);
        printf("\n");
        SymbolUsage = (char *)Malloc(sizeof(String));
        GetLiteralSymbolUsage(Literal,&SymbolUsage,&VariablesStartHere);
        printf("The literal data is \n%s\n",SymbolUsage);
        printf("The variables are \n%s\n",VariablesStartHere);

        if ((AnotherLiteral = GetLiteralFromAnnotatedClauseByNumber(
AnnotatedFormula,2)) != NULL) {
            printf("The literal is ");
            PrintTSTPFormula(stdout,AnotherLiteral,0,0,1,none,none,0);
            printf("\n");
            AnotherSymbolUsage = (char *)Malloc(sizeof(String));
            if (GetLiteralSymbolUsage(AnotherLiteral,&AnotherSymbolUsage,
NULL) != NULL) {
                printf("The literal data is \n%s\n",AnotherSymbolUsage);
            }
            ExtendString(&SymbolUsage,AnotherSymbolUsage,&SymbolUsageLength);
            NormalizeSymbolUsage(SymbolUsage);
            printf("The combined data is \n%s\n",SymbolUsage);
            Free((void **)&AnotherSymbolUsage);
        } else {
            printf("Could not get literal number 2\n");
        }
        Free((void **)&SymbolUsage);
    } else {
        printf("Could not get literal number 1\n");
    }

    FreeListOfAnnotatedFormulae(&Head);
    assert(Head == NULL);

    return(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------

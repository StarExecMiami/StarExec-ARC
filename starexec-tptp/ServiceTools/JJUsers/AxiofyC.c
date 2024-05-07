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
#include "Modify.h"
#include "List.h"
#include "ListStatistics.h"
#include "PrintTSTP.h"
//-------------------------------------------------------------------------------------------------
int HasNegatedConjectureAncestor(ANNOTATEDFORMULA AnnotatedFormula,LISTNODE Head) {

    String AllParentNames;
    int NumberOfParents;
    StringParts ParentNames;
    int ParentNumber;
    ANNOTATEDFORMULA Parent;

    GetParentNames(AnnotatedFormula,AllParentNames);
    NumberOfParents = Tokenize(AllParentNames,ParentNames,"\n");
    if (NumberOfParents == 0) {
        return(GetRole(AnnotatedFormula,NULL) == negated_conjecture);
    } else {
        for (ParentNumber=0;ParentNumber < NumberOfParents;ParentNumber++) {
            if (strstr(ParentNames[ParentNumber],"theory(") != ParentNames[ParentNumber]) {
                Parent = GetAnnotatedFormulaFromListByName(Head,ParentNames[ParentNumber]);
                if (HasNegatedConjectureAncestor(Parent,Head)) {
                    return(1);
                }
            }
        }
    }
    return(0);
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    SIGNATURE Signature;
    LISTNODE Head;
    LISTNODE Target;
    LISTNODE * DiscardTarget;
    PrintFormatType Format;
    int Pretty;
    int ArgOffset;
    int KeepNonLogicals;
    StatusType Status;
    TERM SubStatus;

    Format = tptp;
    Pretty = 1;
    KeepNonLogicals = 0;

    ArgOffset = 0;
    while (argc > ArgOffset+2 && argv[ArgOffset+1][0] == '-') {
//----Change output length if specified
        if (argc > ArgOffset+3 && !strcmp(argv[ArgOffset+1],"-f")) {
            Format = StringToPrintFormat(argv[ArgOffset+2]);
            ArgOffset += 2;
        }
        if (argc > ArgOffset+3 && !strcmp(argv[ArgOffset+1],"-u")) {
            if (!strcmp("machine",argv[ArgOffset+2])) {
                Pretty = 0;
            }
            ArgOffset += 2;
        }
    }

//----One signature for all testing
    Signature = NewSignature();

//----Read in derivation
    SetNeedForNonLogicTokens(KeepNonLogicals);
    if ((Head = ParseFileOfFormulae(argv[ArgOffset+1],NULL,Signature,1,NULL)) != NULL) {
        Target = Head;
        while (Target != NULL) {
            if (LogicalAnnotatedFormula(Target->AnnotatedFormula)) {
                Status = GetRole(Target->AnnotatedFormula,&SubStatus);
                if (Status == derived || !strcmp(GetSymbol(SubStatus),"derived")) {
                    if (!HasNegatedConjectureAncestor(Target->AnnotatedFormula,Head)) {
                        SetStatus(Target->AnnotatedFormula,lemma,NULL);
                    } else {
                        SetStatus(Target->AnnotatedFormula,derived,NULL);
                    }
                } else if (Status != negated_conjecture) {
                    SetStatus(Target->AnnotatedFormula,axiom,NULL);
                }
            }
            Target = Target->Next;
        }
//----Discard those that are derived - have some negated conjecture in them
        DiscardTarget = &Head;
        while (*DiscardTarget != NULL) {
            if ((Status = GetRole((*DiscardTarget)->AnnotatedFormula,&SubStatus)) == derived) {
                FreeAListNode(DiscardTarget,Signature);
            } else {
                DiscardTarget = &((*DiscardTarget)->Next);
            }
        }

        PrintListOfAnnotatedTSTPNodes(stdout,Signature,Head,Format,Pretty);
        FreeListOfAnnotatedFormulae(&Head,Signature);
    } 
    FreeSignature(&Signature);

    return(EXIT_SUCCESS);
}
//-------------------------------------------------------------------------------------------------

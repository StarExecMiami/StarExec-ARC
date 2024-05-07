#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "List.h"
#include "Tokenizer.h"
#include "PrintKIF.h"
#include "Examine.h"
//-------------------------------------------------------------------------------------------------
void StartSUMOProof(FILE * Stream) {

    fprintf(Stream,"<queryResponse>\n");
    fprintf(Stream,"  <answer result='yes' number='1'>\n");
    fprintf(Stream,"    <proof>\n");
}
//-------------------------------------------------------------------------------------------------
void SUMOPrintAnnotatedTSTPFormula(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula,LISTNODE Head,
SIGNATURE Signature) {

    LISTNODE Parents;
    LISTNODE Parent;
    const char * SUMOFormulaType;

    fprintf(Stream,"      <proofStep>\n");
    fprintf(Stream,"        <premises>\n");

    if (!GetNodeParentList(AnnotatedFormula,Head,&Parents,Signature)) {
        CodingError("Missing parents in derivation");
    }
    Parent = Parents;
    while (Parent != NULL) {
        SUMOFormulaType = GetSyntax(Parent->AnnotatedFormula) == tptp_fof?
"formula":"clause";
        fprintf(Stream,"          <premise>\n");
        fprintf(Stream,"            <%s number='%s'>\n",SUMOFormulaType,
GetName(Parent->AnnotatedFormula,NULL));
        KIFPrintFormula(Stream,Parent->AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula,14,0,1);
        fprintf(Stream,"\n");
        fprintf(Stream,"            </%s>\n",SUMOFormulaType);
        fprintf(Stream,"          </premise>\n");
        Parent = Parent->Next;
    }
    FreeListOfAnnotatedFormulae(&Parents,Signature);
    fprintf(Stream,"        </premises>\n");

    SUMOFormulaType = GetSyntax(AnnotatedFormula) == tptp_fof?
"formula":"clause";
    fprintf(Stream,"        <conclusion>\n");
    fprintf(Stream,"          <%s number='%s'>\n",SUMOFormulaType,
GetName(AnnotatedFormula,NULL));
    KIFPrintFormula(Stream,AnnotatedFormula->AnnotatedFormulaUnion.
AnnotatedTSTPFormula.FormulaWithVariables->Formula,12,0,1);
    fprintf(Stream,"\n");
    fprintf(Stream,"          </%s>\n",SUMOFormulaType);
    fprintf(Stream,"        </conclusion>\n");
    fprintf(Stream,"      </proofStep>\n");
}
//-------------------------------------------------------------------------------------------------
void EndSUMOProof(FILE * Stream) {

    fprintf(Stream,"    </proof>\n");
    fprintf(Stream,"  </answer>\n");
    fprintf(Stream,"  <summary proofs='1'/>\n");
    fprintf(Stream,"</queryResponse>\n");
}
//-------------------------------------------------------------------------------------------------
void SUMOPrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head,SIGNATURE Signature) {
    
    StartSUMOProof(Stream);
    LISTNODE Target;
    
    Target = Head;
    while (Target != NULL) {
        switch (GetSyntax(Target->AnnotatedFormula)) {
            case include:
                CodingError("include directive in derivation");
                break;
            case comment:
                break;
            case blank_line:
                fprintf(Stream,"\n");
                break;
            case tptp_fof:
            case tptp_cnf:
                SUMOPrintAnnotatedTSTPFormula(Stream,Target->AnnotatedFormula,Head,Signature);
                break;
            default:
                CodingError("Annotated formula syntax unknown for printing");
        }
        Target = Target->Next;
    }
    EndSUMOProof(Stream);
}
//-------------------------------------------------------------------------------------------------

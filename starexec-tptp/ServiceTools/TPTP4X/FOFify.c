#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Examine.h"
#include "Modify.h"
#include "PrintTSTP.h"
#include "tptp4X.h"
//-------------------------------------------------------------------------------------------------
char * ChooseAlgorithm(OptionsType Options,String Algorithm) {

    String FOFifyPart;

    if (strstr(Options.Transformations,"fofify") == NULL) {
        return(NULL);
    }
//----Extract starting at the fofify part
    strcpy(FOFifyPart,strstr(Options.Transformations,"fofify"));
//----Remove other transformations
    if (strchr(FOFifyPart,'+') != NULL) {
        *(strchr(FOFifyPart,'+')) = '\0';
    }
//----See if a specific algorithm has been requested
    if (strchr(FOFifyPart,':') !=  NULL) {
        strcpy(Algorithm,strchr(FOFifyPart,':')+1);
    } else {
        strcpy(Algorithm,"plain");
    }       

    return(Algorithm);
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA DoFOFifyAnnotatedFormula(ANNOTATEDFORMULA AnnotatedFormula,
char * Algorithm) {

    if (Algorithm != NULL && LogicalAnnotatedFormula(AnnotatedFormula)) {
//----Convert CNF to FOF and universal quantify
        if (!strcmp(Algorithm,"plain")) {
            FOFify(AnnotatedFormula,universal);
//----Universal quantify FOF
        } else if (!strcmp(Algorithm,"quantify_universal") ||
!strcmp(Algorithm,"!")) {
            Quantify(AnnotatedFormula,universal);
        } else if (!strcmp(Algorithm,"quantify_existential") ||
!strcmp(Algorithm,"?")) {
            Quantify(AnnotatedFormula,existential);
        } else if (!strcmp(Algorithm,"quantify_lambda") ||
!strcmp(Algorithm,"^")) {
            if (CheckAnnotatedFormula(AnnotatedFormula,tptp_thf)) {
                Quantify(AnnotatedFormula,lambda);
            } else {
                printf("ERROR: Cannot lambda quantify FOF formula\n");
            }
        }
    }

    return(AnnotatedFormula);
}
//-------------------------------------------------------------------------------------------------
ANNOTATEDFORMULA FOFifyAnnotatedFormula(OptionsType Options,ANNOTATEDFORMULA 
AnnotatedFormula) {

    String Algorithm;

    return(DoFOFifyAnnotatedFormula(AnnotatedFormula,ChooseAlgorithm(Options,
Algorithm)));

}
//-------------------------------------------------------------------------------------------------
LISTNODE FOFifyListOfAnnotatedFormulae(OptionsType Options,
LISTNODE AllAnnotatedFormulae) {

    String Algorithm;
    LISTNODE Target;

    if (ChooseAlgorithm(Options,Algorithm) != NULL) {
        Target = AllAnnotatedFormulae;
        while (Target != NULL) {
            DoFOFifyAnnotatedFormula(Target->AnnotatedFormula,Algorithm);
            Target = Target->Next;
        }
    }
 
    return(AllAnnotatedFormulae);
}
//-------------------------------------------------------------------------------------------------

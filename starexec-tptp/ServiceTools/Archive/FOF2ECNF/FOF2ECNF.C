#include <iostream.h>
#include "ConvertToECNF.h"

//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

  /*
    Executing:
    FOF2ECNF <filename> <arg>
    Put -s for <arg> for splitting
  */

    LISTNODE Head;
    ANNOTATEDFORMULA A;
    SIGNATURE Signature;
    bool split_formula;

//----One signature for all testing
    Signature = NewSignature();

//----Split formula
    split_formula = false;
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-s") == 0) {
	split_formula = true;
      }
    }

//----Read from file or stdin
    SetNeedForNonLogicTokens(0);
    if (argc > 1) {
        Head = ParseFileOfFormulae(argv[1],Signature,1,NULL);
	//Print initial formulas
	//PrintListOfAnnotatedTSTPNodes(stdout,Head,tstp);
    } else {
        Head = ParseFILEOfFormulae(stdin,Signature,1,NULL);
    }
    
    A = GetAnnotatedFormulaFromListByNumber(Head,1);
    ConvertToECNF(&Head, Signature, split_formula);
    //Print final results
    PrintListOfAnnotatedTSTPNodes(stdout,Head,tstp);
}

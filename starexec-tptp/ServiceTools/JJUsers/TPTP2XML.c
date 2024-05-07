#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Tokenizer.h"
#include "Parsing.h"
#include "Signature.h"
#include "Examine.h"
#include "Modify.h"
#include "List.h"
#include "ListStatistics.h"
#include "PrintXML.h"
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    LISTNODE Head;
    SIGNATURE Signature;
    Boolean ExpandIncludes=FALSE;
    Content TSTPFormulae=CONTENT_XML;
    Boolean CommentedOriginal=FALSE;
    int opt;
    
    if (argc<=1) {
        fprintf(stderr,"\
Syntax: %s [-e] [-t|-T] <filename>\n\
    <filename> is path to tstp file; if set to -, standard input is used\n\
    -e  expands includes present in the input\n\
    -t  doesn't XMLize the content of formulae\n\
        instead, prints them intact inside <tstp-logic-formula> tag.\n\
    -T  prints both XMLized and intact formulae inside <tstp-logic-formula> tag.\n\
    -o  prepends each formula tag with a comment with its TSTP version\n\
",argv[0]);
        exit(0);
    }
    
    while ((opt=getopt(argc,argv,"etTo"))!=-1) {
        switch (opt) {
            case 'e': ExpandIncludes=TRUE; break;
            case 't': TSTPFormulae=CONTENT_TSTP; break;
            case 'T': TSTPFormulae=CONTENT_BOTH; break;
            case 'o': CommentedOriginal=TRUE; break;
            case ':': Error("Missing option argument"); break;
            case '?': // unknown option
            default:  Error("Unknown option specified"); break;
        }
    }

    Signature = NewSignature();
    SetNeedForNonLogicTokens(1);
    if (argc==optind)
        Error("No input file specified");
    if (!strcmp(argv[optind],"-"))
        Head=ParseFILEOfFormulae(stdin,Signature,ExpandIncludes,NULL);
    else
        Head=ParseFileOfFormulae(argv[optind],NULL,Signature,ExpandIncludes,NULL);
    
    XMLPrintListOfAnnotatedTSTPNodes(stdout,Head,TSTPFormulae,CommentedOriginal);

    FreeListOfAnnotatedFormulae(&Head);
    assert(Head == NULL);

    return(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------

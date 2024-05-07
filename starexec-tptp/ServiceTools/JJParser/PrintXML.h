#ifndef PRINTXML_H
#define PRINTXML_H
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "DataTypes.h"
#include "PrintTSTP.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
typedef int Boolean;

typedef const char * AttrNameType;
typedef const char * AttrValueType;

typedef enum {
    CONTENT_XML,
    CONTENT_TSTP,
    CONTENT_BOTH
} Content;


typedef struct {
    FILE *Stream;
    int IndentLevel;
    Content FormulaeContent;
    Boolean CommentedOriginal;
} XMLOutputType;

typedef XMLOutputType * XMLOutput;
//-------------------------------------------------------------------------------------------------
void Error(char *message);
void XMLPrintListOfAnnotatedTSTPNodes(FILE *Stream, LISTNODE Head,
Content FormulaeContent, Boolean CommentedOriginal);
//-------------------------------------------------------------------------------------------------
#endif

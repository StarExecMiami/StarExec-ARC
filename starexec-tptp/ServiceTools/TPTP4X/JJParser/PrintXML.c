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
#include "Tokenizer.h"
#include "Examine.h"
#include "PrintXML.h"

//-------------------------------------------------------------------------------------------------
void Warning(char * ErrorMessage) {
    fprintf(stderr,"Warning:  %s (continuing anyway)\n",ErrorMessage);
}

//-------------------------------------------------------------------------------------------------
void StringCat(String Dest, const char *Src) {
    strncat(Dest,Src,sizeof(String)-1);
}
//-------------------------------------------------------------------------------------------------
void SuperStringCat(SuperString Dest, const char *Src) {
    strncat(Dest,Src,sizeof(SuperString)-1);
}
//-------------------------------------------------------------------------------------------------
void StringCpy(String Dest, const char *Src) {
    strncpy(Dest,Src,sizeof(String)-1);
    Dest[sizeof(String)-1]='\0';
}
//-------------------------------------------------------------------------------------------------
void SuperStringCpy(SuperString Dest, const char *Src) {
    strncpy(Dest,Src,sizeof(SuperString)-1);
    Dest[sizeof(SuperString)-1]='\0';
}
//-------------------------------------------------------------------------------------------------
void Error(char *message) {
    fprintf(stderr,"ERROR: %s\n",message);
    exit(1);
}
//-------------------------------------------------------------------------------------------------
void InitXMLOutput(XMLOutput Out, FILE *Stream,
Content FormulaeContent, Boolean CommentedOriginal) {
    Out->Stream=Stream;
    Out->IndentLevel=0;
    Out->FormulaeContent=FormulaeContent;
    Out->CommentedOriginal=CommentedOriginal;
}
//-------------------------------------------------------------------------------------------------
void CleanXMLOutput(XMLOutput Out) {
    assert(Out->IndentLevel==0);
}
//-------------------------------------------------------------------------------------------------
void Indent(XMLOutput Out) {
    fprintf(Out->Stream,"%*s",Out->IndentLevel*2,"");
}
//-------------------------------------------------------------------------------------------------
void XMLEscapedString(XMLOutput Out, const char *s) {
    FILE * Stream=Out->Stream;
    const char *ref,*p;
    for(p=s;*p!='\0';p++) {
        switch (*p) {
            case '&': 
                ref="amp"; 
            break;
            case '\'': 
                ref="apos"; 
            break;
            case '"': 
                ref="quot"; 
            break;
            case '<': 
                ref="lt"; 
            break;
            case '>': 
                ref="gt"; 
            break;
            default: 
                continue;
            break;
        }
        fprintf(Stream,"%.*s&%s;",(int)(p-s),s,ref);
        s=p+1;
    }
    fputs(s,Stream);
}
//-------------------------------------------------------------------------------------------------
void EndTag(XMLOutput Out, const char *name) {
    Out->IndentLevel--;
    Indent(Out);
    fprintf(Out->Stream,"</%s>\n",name);
}
//-------------------------------------------------------------------------------------------------
void StartTag(XMLOutput Out, const char *name, AttrNameType *attrNames,
AttrValueType *attrValues, Boolean empty) {

    Indent(Out);
    if (!empty) {
        Out->IndentLevel++;
    }
    fprintf(Out->Stream,"<%s",name);
    if ((attrNames!=NULL)&&(attrValues!=NULL)) {
        for (;*attrNames!=NULL;attrNames++,attrValues++) {
            if (*attrValues==NULL) {
                continue;
            }
            fprintf(Out->Stream," %s=\'",*attrNames);
            XMLEscapedString(Out,*attrValues);
            fprintf(Out->Stream,"'");
        }
    }
    if (empty) {
        fputc('/',Out->Stream);
    }
    fprintf(Out->Stream,">\n");
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

char * XMLConnectiveToString(ConnectiveType Connective) {

    switch (Connective) {
        case disjunction:
            return("disjunction");
            break;
        case conjunction:
            return("conjunction");
            break;
        case equivalence:
            return("equivalence");
            break;
        case implication:
            return("implication");
            break;
        case reverseimplication:
            return("reverse-implication");
            break;
        case nonequivalence:
            return("nonequivalence");
            break;
        case negateddisjunction:
            return("negated-disjunction");
            break;
        case negatedconjunction:
            return("negated-conjunction");
            break;
        case negation:
            return("negation");
            break;
        case universal:
            return("universal");
            break;
        case existential:
            return("existential");
            break;
         case typecolon:
              return("type-declaration");
              break;
         case maparrow:
              return("arrow-type");
              break;
         case xprodtype:
              return("product-type");
              break;
        default:
            Error("ERROR: Not a connective");
            return(NULL); // Satisfy compiler
    }
}

//-------------------------------------------------------------------------------------------------
void XMLPrintTSTPTerm(XMLOutput Out, TERM Term) {

    int Arity=GetArity(Term);
    SuperString tagName;
    SuperString symbolCopy;
    char *symbol;
    static AttrNameType names[]={"name",NULL};
    AttrValueType values[]={NULL,NULL};

    SuperStringCpy(tagName,"");
    SuperStringCpy(symbolCopy,GetSymbol(Term));
    symbol=symbolCopy;

    // for regular terms, do some preprocessing
    if (*symbol=='\'') {        // remove quotes, if present
        int l=strlen(symbol)-1;
        if (symbol[l]!='\'') {
//DEBUG printf("====%s====\n",symbol);
            CodingError("Unmatched single qoute ");
        }
	    symbol[l]='\0';
	    symbol++;
    } else if (*symbol=='$') {  // $ marks defined and $$ system symbols
        symbol++;
        if (*symbol=='$') {
            symbol++;
            StringCat(tagName,"system-");
        } else
            StringCat(tagName,"defined-");
    }
    // look up the term type
    switch (Term->Type) {
        case atom_as_term:
            SuperStringCat(tagName,"predicate"); break;
        case function:
            SuperStringCat(tagName,"function"); break;
        case variable:
            SuperStringCat(tagName,"variable"); break;
        case non_logical_data:
            SuperStringCat(tagName,"non-logical-data"); break;
        default:
            CodingError("Unsupported term type");
    }
//----Check if infix -
    // TODO
    // for some special cases alter the tag name
    if (*symbol=='\"') {  // double-quoted string
        int l=strlen(symbol)-1;
	    if (symbol[l]!='\"') {
	        CodingError("Unmatched double qoute ");
        }
	    symbol[l]='\0';
	    symbol++;
	    SuperStringCpy(tagName,"string");
    } else if (isdigit(*symbol)||(*symbol=='+')||(*symbol=='-')) {
	    SuperStringCpy(tagName,"number");
    }
//----Check if a list
    if (symbol[0] != '[') {
        values[0]=symbol;
    }
    StartTag(Out,tagName,names,values,Arity==0);
    if (Arity>0) {
        int i;
        for(i=0;i<Arity;i++) {
            XMLPrintTSTPTerm(Out,Term->Arguments[i]);
        }
        EndTag(Out,tagName);
    }
}
//-------------------------------------------------------------------------------------------------
void XMLPrintTSTPFormula(XMLOutput Out,FORMULA Formula) {
    
    if (Formula == NULL)
        Error("No TSTP formula to print");
    else {
        switch (Formula->Type) {
            case quantified: {
                static AttrNameType names[]={"type",NULL};
                AttrValueType values[]={NULL,NULL};
                char count[16]="";
                ConnectiveType Quantifier=
                    Formula->FormulaUnion.QuantifiedFormula.Quantifier;
                values[0]=XMLConnectiveToString(Quantifier);
                StartTag(Out,"quantifier",names,values,FALSE);
//----Print existential count if there is one
                if (
(Quantifier == existential) &&
(Formula->FormulaUnion.QuantifiedFormula.ExistentialCount > 0))
                    sprintf(count,"%.*d",(int)sizeof(count)-1,
Formula->FormulaUnion.QuantifiedFormula.ExistentialCount);
//----List variables for same quantifiers
                while (
Formula->Type == quantified &&
Formula->FormulaUnion.QuantifiedFormula.Quantifier == Quantifier) {
//----Here's where types will be printed, in a future TSTP
                    static AttrNameType vNames[]={"name","count","type",NULL};
                    AttrValueType vValues[]={
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable),
(count[0]!='\0')?count:NULL,NULL,NULL};
//----Here's where types will be printed, in a future TSTP
                    StartTag(Out,"variable",vNames,vValues,TRUE);
                    Formula=Formula->FormulaUnion.QuantifiedFormula.Formula;
                }
                
                XMLPrintTSTPFormula(Out,Formula);
                EndTag(Out,"quantifier");
                break;
            }

            case binary: {
                char *tagName=
XMLConnectiveToString(Formula->FormulaUnion.BinaryFormula.Connective);
                StartTag(Out,tagName,NULL,NULL,FALSE);
                XMLPrintTSTPFormula(Out,Formula->FormulaUnion.BinaryFormula.LHS);
                XMLPrintTSTPFormula(Out,Formula->FormulaUnion.BinaryFormula.RHS);
                EndTag(Out,tagName);
                break;
            }

            case unary: {
                char *tagName=
XMLConnectiveToString(Formula->FormulaUnion.UnaryFormula.Connective);
                StartTag(Out,tagName,NULL,NULL,FALSE);
                XMLPrintTSTPFormula(Out,Formula->FormulaUnion.UnaryFormula.Formula);
                EndTag(Out,tagName);
                break;
            }

            case atom:
                XMLPrintTSTPTerm(Out,Formula->FormulaUnion.Atom);
                break;

            default:
                CodingError("Formula type unknown for printing XML");
        }
    }
}
//-------------------------------------------------------------------------------------------------
void XMLPrintAnnotatedTSTPFormula(XMLOutput Out, SyntaxType Syntax,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula) {
    static AttrNameType names[]={"name","syntax","status",NULL};
    AttrValueType values[]={NULL,NULL,NULL,NULL};
    char status[32];
    
    values[0] = AnnotatedTSTPFormula.Name;

    if (Out->CommentedOriginal) {
        Indent(Out);
        fprintf(Out->Stream,"<!-- ");
        PrintAnnotatedTSTPFormula(Out->Stream,Syntax,AnnotatedTSTPFormula,
tptp,1);
        fprintf(Out->Stream," -->\n");
    }
    
    switch (Syntax) {
        case tptp_fof:
            values[1]="formula";
            break;
        case tptp_cnf:
        values[1]="clause";
            break;
        default:
            CodingError("TSTP formula type unknown for printing");
    }
    
    status[0]='\0';
    strncat(status,StatusToString(AnnotatedTSTPFormula.Status),sizeof(status)-1);
    if (AnnotatedTSTPFormula.SubStatus != NULL) {
        strncat(status,"-",sizeof(status)-1);
        XMLPrintTSTPTerm(Out,AnnotatedTSTPFormula.SubStatus);
//TODO        strncat(status,StatusToString(AnnotatedTSTPFormula.SubStatus),sizeof(status)-1);
    }
    values[2]=status;
    StartTag(Out,"formula",names,values,FALSE);
    
    if ((Out->FormulaeContent == CONTENT_XML) || (Out->FormulaeContent == CONTENT_BOTH)) {
        XMLPrintTSTPFormula(Out,AnnotatedTSTPFormula.FormulaWithVariables->Formula);
    }
    if ((Out->FormulaeContent == CONTENT_TSTP) || (Out->FormulaeContent == CONTENT_BOTH)) {
        Indent(Out);
        fprintf(Out->Stream,"<tstp-logic-formula><![CDATA[");
//TODO: Silently we hope that ]]> never occurs in the formula
        PrintTSTPFormula(Out->Stream,Syntax,AnnotatedTSTPFormula.FormulaWithVariables->Formula,6,1,
outermost,1);
        fprintf(Out->Stream,"]]></tstp-logic-formula>\n");
    }

//----Source and useful info are optional
    if (AnnotatedTSTPFormula.Source != NULL) {
        StartTag(Out,"source",NULL,NULL,FALSE);
        XMLPrintTSTPTerm(Out,AnnotatedTSTPFormula.Source);
        EndTag(Out,"source");
    }
    if (AnnotatedTSTPFormula.UsefulInfo != NULL) {
        StartTag(Out,"useful-info",NULL,NULL,FALSE);
        XMLPrintTSTPTerm(Out,AnnotatedTSTPFormula.UsefulInfo);
        EndTag(Out,"useful-info");
    }
    EndTag(Out,"formula");
}
//-------------------------------------------------------------------------------------------------
LISTNODE XMLPrintComments(XMLOutput Out, LISTNODE Head) {

    if (Head->AnnotatedFormula->Syntax!=comment) {
        CodingError("Node is not a comment");
        return(NULL);
    }
    Indent(Out);
    fprintf(Out->Stream,"<comment><![CDATA[\n");
//TODO: Silently we hope that ]]> never occurs in the comment
    for(;Head!=NULL;Head=Head->Next) {
        ANNOTATEDFORMULA AnnotatedFormula=Head->AnnotatedFormula;
        SyntaxType Syntax=AnnotatedFormula->Syntax;
        if (Syntax==comment) {
            char *c=AnnotatedFormula->AnnotatedFormulaUnion.Comment;
            // strip the initial '%'
            if (*c=='%')
                c++;
            fprintf(Out->Stream,"%s",c);
            fprintf(Out->Stream,"\n");
        } else if (Syntax==blank_line) {
            fprintf(Out->Stream,"\n");
        } else
            break;
    }
    fprintf(Out->Stream,"]]></comment>\n");
    return(Head);
}
//-------------------------------------------------------------------------------------------------
void XMLPrintListOfAnnotatedTSTPNodes(FILE * Stream, LISTNODE Head, Content 
FormulaeContent, Boolean CommentedOriginal) {
    XMLOutputType Out;
    
    InitXMLOutput(&Out,Stream,FormulaeContent,CommentedOriginal);
    StartTag(&Out,"tstp",NULL,NULL,FALSE);
    while (Head!=NULL) {
        ANNOTATEDFORMULA AnnotatedFormula=Head->AnnotatedFormula;
        switch (AnnotatedFormula->Syntax) {
            case include: {
                TERM Term=AnnotatedFormula->AnnotatedFormulaUnion.Include;
                XMLPrintTSTPTerm(&Out,Term);
                /*
                char *c;
                assert(GetArity(Term)==1);
                Term=Term->Arguments[0];
                c=GetSymbol(Term);
                // TODO
                StartTag(&Out,"include",NULL,NULL,FALSE);
                XMLEscapedString(&Out,c);
                EndTag(&Out,"include");
                */
                break;
            }
            case comment:
                Head=XMLPrintComments(&Out,Head);
                continue; // skip the Head=Head->Next line
            case blank_line:
                fprintf(Out.Stream,"\n");
                break;
            case tptp_fof:
            case tptp_cnf:
                    XMLPrintAnnotatedTSTPFormula(&Out,AnnotatedFormula->Syntax,
    AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula);
                break;
            default:
                CodingError("Annotated formula syntax unknown for printing");
        }
        Head=Head->Next;
    }
    EndTag(&Out,"tstp");
    CleanXMLOutput(&Out);
}
//-------------------------------------------------------------------------------------------------

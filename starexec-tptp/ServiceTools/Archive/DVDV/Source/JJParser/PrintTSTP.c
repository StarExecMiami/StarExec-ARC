#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Utilities.h"
#include "Signature.h"
#include "Parsing.h"
#include "Tokenizer.h"
#include "Examine.h"
#include "PrintTSTP.h"
//-----------------------------------------------------------------------------
PrintFormatType StringToPrintFormat(char * String) {

    if (!strcmp(String,"tptp")) {
        return(tptp);
    }
    if (!strcmp(String,"tptp:long")) {
        return(tptp);
    }
    if (!strcmp(String,"tptp:short")) {
        return(tptp_short);
    }
    if (!strcmp(String,"oldtptp")) {
        return(oldtptp);
    }
    printf("ERROR: String %s not a print format\n",String);
    exit(-1);
}
//-----------------------------------------------------------------------------
char * PrintFormatToString(PrintFormatType Format) {

     switch (Format) {
        case tptp:
            return("tptp");
            break;
        case tptp_short:
            return("tptp:short");
            break;
        case oldtptp:
            return("oldtptp");
            break;
        default:
            printf("ERROR: Not a print format\n");
            exit(-1);
    }
}
//-----------------------------------------------------------------------------
void PrintTSTPTerm(FILE * Stream,TERM Term,int TSTPSyntaxFlag) {

    int Index;
    int Arity;
    char OpeningBracket,ClosingBracket;

//----Check if infix - or : (see also TSTPTermToString in Examine.c)
    if (!strcmp(GetSymbol(Term),"-") || !strcmp(GetSymbol(Term),":")) {
        PrintTSTPTerm(Stream,Term->Arguments[0],0);
        fprintf(Stream,"%s",GetSymbol(Term));
        PrintTSTPTerm(Stream,Term->Arguments[1],0);
    } else if (TSTPSyntaxFlag && !strcmp(GetSymbol(Term),"$equal")) {
        PrintTSTPTerm(Stream,Term->Arguments[0],0);
        fprintf(Stream," ");
        if (TSTPSyntaxFlag == 2) {
            fprintf(Stream,"!");
        }
        fprintf(Stream,"= ");
        PrintTSTPTerm(Stream,Term->Arguments[1],0);
    } else {
//----Check if a list
        if (GetSymbol(Term)[0] == '[') {
            OpeningBracket = '[';
            ClosingBracket = ']';
        } else {
            fprintf(Stream,"%s",GetSymbol(Term));
            OpeningBracket = '(';
            ClosingBracket = ')';
        }
        
        if ((Arity = GetArity(Term)) > 0 || OpeningBracket == '[') {
            fprintf(Stream,"%c",OpeningBracket);
            if (Arity > 0) {
                PrintTSTPTerm(Stream,Term->Arguments[0],TSTPSyntaxFlag);
                for (Index=1;Index < Arity;Index++) {
                    fprintf(Stream,",");
                    PrintTSTPTerm(Stream,Term->Arguments[Index],0);
                }
            }
            fprintf(Stream,"%c",ClosingBracket);
        }
    }
}
//-----------------------------------------------------------------------------
void PrintIndent(FILE * Stream,int Indent,int AlreadyIndented,int Pretty) {

    int Index;

    if (Pretty) {
        for (Index = AlreadyIndented+1;Index <= Indent;Index++) {
            fprintf(Stream," ");
        }
    }
}
//-----------------------------------------------------------------------------
int Associative(ConnectiveType Connective) {

    return(Connective == disjunction || Connective == conjunction);
}
//-----------------------------------------------------------------------------
void PrintTSTPFormula(FILE * Stream,FORMULA Formula,int Indent,
int AlreadyIndented,int Pretty,ConnectiveType LastConnective,
ConnectiveType NextConnective,int TSTPSyntaxFlag) {

    int NoIndent;
    int NoUndent;
    int ConnectiveIndent;

    if (Formula == NULL) {
        fprintf(Stream,"ERROR: No TSTP formula to print\n");
    } else {
        switch (Formula->Type) {
            case quantified:
                PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
                fprintf(Stream,"%s ",ConnectiveToString(
Formula->FormulaUnion.QuantifiedFormula.Quantifier));
                fprintf(Stream,"[");
//----Print existential count if there is one
                if (Formula->FormulaUnion.QuantifiedFormula.Quantifier ==
existential && Formula->FormulaUnion.QuantifiedFormula.ExistentialCount >= 0) {
                    fprintf(Stream,"%d:",Formula->
FormulaUnion.QuantifiedFormula.ExistentialCount);
                }
                fprintf(Stream,"%s",
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
//----Here's where types will be printed, in a future TSTP
//----List variables for same quantifiers
                while (Pretty && 
Formula->FormulaUnion.QuantifiedFormula.Formula->Type == quantified &&
Formula->FormulaUnion.QuantifiedFormula.Quantifier ==
Formula->FormulaUnion.QuantifiedFormula.Formula->FormulaUnion.QuantifiedFormula.Quantifier) {
                    Formula = Formula->FormulaUnion.QuantifiedFormula.Formula;
                    fprintf(Stream,",%s",
GetSymbol(Formula->FormulaUnion.QuantifiedFormula.Variable));
                }
                fprintf(Stream,"] : ");
//----If unary or atom, do on same line
                if ((Formula->FormulaUnion.QuantifiedFormula.Formula->Type == 
unary) || (Formula->FormulaUnion.QuantifiedFormula.Formula->Type == atom)) {
                    PrintTSTPFormula(Stream,Formula->
FormulaUnion.QuantifiedFormula.Formula,Indent,Indent,Pretty,
Formula->FormulaUnion.QuantifiedFormula.Quantifier,none,TSTPSyntaxFlag);
                } else {
//----Otherwise on the next line
                    fprintf(Stream,"%s",(Pretty?"\n":""));
//----If another quantified, no extra indent
                    if (Formula->FormulaUnion.QuantifiedFormula.Formula->Type !=
quantified) {
                        Indent += 2;
                    }
                    PrintTSTPFormula(Stream,Formula->
FormulaUnion.QuantifiedFormula.Formula,Indent,0,Pretty,
Formula->FormulaUnion.QuantifiedFormula.Quantifier,none,TSTPSyntaxFlag);
                }
                break;

            case binary:
                PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
//----No brackets for sequences of associative formulae and top level
                NoIndent = (Pretty &&
Formula->FormulaUnion.BinaryFormula.Connective == LastConnective && 
Associative(Formula->FormulaUnion.BinaryFormula.Connective))
|| LastConnective == outermost;
                NoUndent = (Pretty &&
Formula->FormulaUnion.BinaryFormula.Connective == NextConnective && 
Associative(Formula->FormulaUnion.BinaryFormula.Connective))
|| NextConnective == outermost;
                if (NoIndent || NoUndent) {
                    ConnectiveIndent = Indent - 2 - strlen(ConnectiveToString(
Formula->FormulaUnion.BinaryFormula.Connective)) + 1;
                    AlreadyIndented = Indent;
                } else {
                    fprintf(Stream,"(%s",(Pretty?" ":""));
                    ConnectiveIndent = Indent - strlen(ConnectiveToString(
Formula->FormulaUnion.BinaryFormula.Connective)) + 1;
                    Indent = AlreadyIndented = Indent + 2;
                }
                PrintTSTPFormula(Stream,Formula->FormulaUnion.BinaryFormula.LHS,
Indent,AlreadyIndented,Pretty,none,Formula->
FormulaUnion.BinaryFormula.Connective,TSTPSyntaxFlag);
                fprintf(Stream,"%s",(Pretty?"\n":" "));
                PrintIndent(Stream,ConnectiveIndent,0,Pretty);
                fprintf(Stream,"%s ",ConnectiveToString(
Formula->FormulaUnion.BinaryFormula.Connective));
                PrintTSTPFormula(Stream,Formula->FormulaUnion.BinaryFormula.RHS,
Indent,AlreadyIndented,Pretty,Formula->FormulaUnion.BinaryFormula.Connective,
none,TSTPSyntaxFlag);
                if (!NoIndent && !NoUndent) {
                    fprintf(Stream,"%s)",(Pretty?" ":""));
                }
                break;

            case unary:
                PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
//----Special for infix negated equality
                if (TSTPSyntaxFlag &&
Formula->FormulaUnion.UnaryFormula.Connective == negation &&
Formula->FormulaUnion.UnaryFormula.Formula->Type == atom &&
!strcmp(GetSymbol(Formula->FormulaUnion.UnaryFormula.Formula->
FormulaUnion.Atom),"$equal")) {
                    TSTPSyntaxFlag = 2;
                    NoIndent = 1;
                } else {
                    fprintf(Stream,"%s ",ConnectiveToString(
Formula->FormulaUnion.UnaryFormula.Connective));
//----() on negated quantified formulae
                    if (Formula->FormulaUnion.UnaryFormula.Formula->Type == 
quantified) {
                        fprintf(Stream,"( ");
                        Indent = AlreadyIndented = Indent + 4;
                        NoIndent = 0;
                    } else {
//----Assumes connective length one - could make it flexible
                        Indent = AlreadyIndented = Indent + 2;
                        NoIndent = 1;
                    }
                }
                PrintTSTPFormula(Stream,
Formula->FormulaUnion.UnaryFormula.Formula,Indent,AlreadyIndented,Pretty,
Formula->FormulaUnion.UnaryFormula.Connective,none,TSTPSyntaxFlag);
                if (!NoIndent) {
                    fprintf(Stream," )");
                }
                break;

            case atom:
                PrintIndent(Stream,Indent,AlreadyIndented,Pretty);
                PrintTSTPTerm(Stream,Formula->FormulaUnion.Atom,
TSTPSyntaxFlag);
                break;

            default:
                printf("ERROR: Formula type unknown for printing\n");
                exit(-1);
                break;
        }
    }
}
//-----------------------------------------------------------------------------
void PrintAnnotatedTSTPFormula(FILE * Stream,SyntaxType Syntax,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula,PrintFormatType Format,
int Pretty) {

    switch (Syntax) {
        case tptp_fof:
            fprintf(Stream,"fof");
            break;
        case tptp_cnf:
            fprintf(Stream,"cnf");
            break;
        default:
            printf("ERROR: TSTP formula type unknown for printing\n");
            exit(-1);
            break;
    }
    fprintf(Stream,"(%s,%s",AnnotatedTSTPFormula.Name,
StatusToString(AnnotatedTSTPFormula.Status));
    if (Format == tptp && AnnotatedTSTPFormula.SubStatus != nonstatus) {
        fprintf(Stream,"-%s",StatusToString(AnnotatedTSTPFormula.SubStatus));
    }
    fprintf(Stream,",%s(",(Pretty?"\n    ":""));
    PrintTSTPFormula(Stream,AnnotatedTSTPFormula.FormulaWithVariables->Formula,
6,5,Pretty,outermost,outermost,1);
    fprintf(Stream," )");

//----Source and useful info are optional
    if (Format == tptp && AnnotatedTSTPFormula.Source != NULL) {
        fprintf(Stream,",%s",(Pretty?"\n    ":""));
        PrintTSTPTerm(Stream,AnnotatedTSTPFormula.Source,0);
        if (AnnotatedTSTPFormula.UsefulInfo != NULL) {
            fprintf(Stream,",%s",(Pretty?"\n    ":""));
            PrintTSTPTerm(Stream,AnnotatedTSTPFormula.UsefulInfo,0);
        }
    }
    fprintf(Stream,").\n");
}
//-----------------------------------------------------------------------------
void PrintTPTPClause(FILE * Stream,FORMULA Formula,int Indent,
int AlreadyIndented,int NeedCommaNewline) {

//----Bypass the universal quantifiers (all outermost)
    while (Formula->Type == quantified &&  
Formula->FormulaUnion.QuantifiedFormula.Quantifier == universal) {
//DEBUG printf("drop quantifier\n");
        Formula = Formula->FormulaUnion.QuantifiedFormula.Formula;
    }

//-----Start formatting
    if (NeedCommaNewline) {
        fprintf(Stream,",\n");
        AlreadyIndented = 0;
    }
    PrintIndent(Stream,Indent,AlreadyIndented,1);

//-----Print the literals
    switch (Formula->Type) {
        case atom:
//----Print nothing for an empty clause
            if (GetSymbol(Formula->FormulaUnion.Atom)[0] == '$') {
                if (strcmp(GetSymbol(Formula->FormulaUnion.Atom),"$false")) {
                    printf("ERROR: Printing an empty clause that is true\n");
                    exit(-1);
                }
            } else {
                fprintf(Stream,"++");
                PrintTSTPTerm(Stream,Formula->FormulaUnion.Atom,0);
            }
            break;
        case unary:
            if (Formula->FormulaUnion.UnaryFormula.Connective == negation) {
                fprintf(Stream,"--");
                PrintTSTPTerm(Stream,
Formula->FormulaUnion.UnaryFormula.Formula->FormulaUnion.Atom,0);
            } else {
                printf("ERROR: Printing a non-clause as a clause\n");
                exit(-1);
            }
            break;
        case binary:
            if (Formula->FormulaUnion.BinaryFormula.Connective == disjunction) {
                PrintTPTPClause(Stream,Formula->FormulaUnion.BinaryFormula.LHS,
Indent,Indent,0);
                PrintTPTPClause(Stream,Formula->FormulaUnion.BinaryFormula.RHS,
Indent,0,1);
            } else {
                printf("ERROR: Printing a non-clause as a clause\n");
                exit(-1);
            }
            break;
        default:
            printf("ERROR: Printing a non-clause as a clause\n");
            exit(-1);
            break;
    }
}
//-----------------------------------------------------------------------------
void PrintAnnotatedTPTPFormula(FILE * Stream,SyntaxType Syntax,
AnnotatedTSTPFormulaType AnnotatedTSTPFormula,int Pretty) {

    switch (Syntax) {
        case tptp_fof:
            fprintf(Stream,"input_formula");
            break;
        case tptp_cnf:
            fprintf(Stream,"input_clause");
            break;
        default:
            printf("ERROR: TSTP formula type unknown for printing\n");
            exit(-1);
            break;
    }
    fprintf(Stream,"(%s,%s,%s",AnnotatedTSTPFormula.Name,
StatusToString(AnnotatedTSTPFormula.Status),(Pretty?"\n":""));
    switch (Syntax) {
        case tptp_fof:
            fprintf(Stream,"    (");
            PrintTSTPFormula(Stream,AnnotatedTSTPFormula.FormulaWithVariables->
Formula,6,5,Pretty,outermost,outermost,0);
            fprintf(Stream," )");
            break;
        case tptp_cnf:
            fprintf(Stream,"    [");
            PrintTPTPClause(Stream,AnnotatedTSTPFormula.FormulaWithVariables->
Formula,5,5,0);
            fprintf(Stream,"]");
            break;
        default:
            printf("ERROR: TSTP formula type unknown for printing\n");
            exit(-1);
            break;
    }
    fprintf(Stream,").\n");
}
//-----------------------------------------------------------------------------
void PrintAnnotatedTSTPNode(FILE * Stream,ANNOTATEDFORMULA AnnotatedFormula,
PrintFormatType Format,int Pretty) {

    if (AnnotatedFormula != NULL) {
        switch (AnnotatedFormula->Syntax) {
            case include:
                PrintTSTPTerm(Stream,
AnnotatedFormula->AnnotatedFormulaUnion.Include,0);
                fprintf(Stream,".\n");
                break;
            case comment:
                fprintf(Stream,"%s",
AnnotatedFormula->AnnotatedFormulaUnion.Comment);
                break;
            case blank_line:
                fprintf(Stream,"\n");
                break;
            case tptp_fof:
            case tptp_cnf:
                switch (Format) {
                    case tptp:
                    case tptp_short:
                        PrintAnnotatedTSTPFormula(Stream,AnnotatedFormula->
Syntax,AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula,Format,
Pretty);
                        break;
                    case oldtptp:
                        PrintAnnotatedTPTPFormula(Stream,AnnotatedFormula->
Syntax,AnnotatedFormula->AnnotatedFormulaUnion.AnnotatedTSTPFormula,Pretty);
                        break;
                    default:
                        fprintf(Stream,"ERROR: Print format not known");
                        break;
                }
                break;
            default:
                printf(
"ERROR: Annotated formula syntax unknown for printing\n");
                exit(-1);
                break;
        }
    }
}
//-----------------------------------------------------------------------------
void PrintListOfAnnotatedTSTPNodes(FILE * Stream,LISTNODE Head,
PrintFormatType Format) {

    while (Head != NULL) {
        PrintAnnotatedTSTPNode(Stream,Head->AnnotatedFormula,Format,1);
        Head = Head->Next;
        if (Head != NULL) {
            fprintf(Stream,"\n");
        }
    }
}
//-----------------------------------------------------------------------------

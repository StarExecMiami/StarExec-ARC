#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <pwd.h>
#include "DataTypes.h"
#include "Tokenizer.h"
#include "Utilities.h"
#include "FileUtilities.h"
//-------------------------------------------------------------------------------------------------
//----Static for all, which really needs to be passed in when a stream is
//----opened, rather than being set here and copied from here (Yaaaack)
static int NeedNonLogicTokens = 0;
static int Warnings = 0;
//-------------------------------------------------------------------------------------------------
int GetNeedForNonLogicTokens(void) {

    return(NeedNonLogicTokens);
}
//-------------------------------------------------------------------------------------------------
void SetNeedForNonLogicTokens(int OnOff) {

    NeedNonLogicTokens = OnOff;
}
//-------------------------------------------------------------------------------------------------
int GetStreamNeedForNonLogicTokens(READFILE Stream) {

    return(Stream->NeedNonLogicTokens);
}
//-------------------------------------------------------------------------------------------------
int GetWarnings(void) {

    return(Warnings);
}
//-------------------------------------------------------------------------------------------------
int SetWarnings(int GiveWarnings) {

    int OldWarnings;

    OldWarnings = Warnings;
    Warnings = GiveWarnings;
    return(OldWarnings);
}
//-------------------------------------------------------------------------------------------------
int GetStreamWarnings(READFILE Stream) {

    return(Stream->Warnings);
}
//-------------------------------------------------------------------------------------------------
int SetStreamWarnings(READFILE Stream,int GiveWarnings) {

    int OldWarnings;

    OldWarnings = Stream->Warnings;
    Stream->Warnings = GiveWarnings;
    return(OldWarnings);
}
//-------------------------------------------------------------------------------------------------
int EndFile(TOKEN CurrentToken) {

    return(CurrentToken->KindToken == endeof);
}
//-------------------------------------------------------------------------------------------------
void CharacterError(READFILE Stream) {

    String RestOfLine;
    String ErrorMessage;

    strcpy(RestOfLine,"");
    if (Stream->FileHandle != NULL) {
        fgets(RestOfLine,20,Stream->FileHandle);
    } else if (Stream->StringFileContent != NULL) {
        strncat(RestOfLine,Stream->StringFileContent + Stream->StringOffset,20);
    }
    sprintf(ErrorMessage,"Line %d Char %d Character \"%c\" continuing with \"%s\"\n",
Stream->Line,Stream->Character,CurrentCharacter(Stream),RestOfLine);
    ReportError("SyntaxError",ErrorMessage,1);
}
//-------------------------------------------------------------------------------------------------
//---- Function Character returns the following values depending on the 
//---- Operation value:
//---- -1 : Read into static, return that one
//---- 0 : Return the static
//---- 1 : Return the static, & read next from File into static
int Character(READFILE Stream,int Operation) {

    int Auxilliary;

    assert((Stream->FileHandle != NULL || Stream->StringFileContent != NULL) &&
(Stream->FileHandle == NULL || Stream->StringFileContent == NULL));

    switch (Operation) {
        case 1:
//----Read into static, return it
            if (Stream->CurrentCharacter == '\n') {
                Stream->Line++;
                Stream->Character = 0;
            }
            if (Stream->FileHandle != NULL) {
                Stream->CurrentCharacter = fgetc(Stream->FileHandle);
            } else if (Stream->StringFileContent != NULL) {
                Stream->CurrentCharacter = 
Stream->StringFileContent[Stream->StringOffset];
                Stream->StringOffset++;
//----Convert end of string to end of file
                if (Stream->CurrentCharacter == '\0') {
                    Stream->CurrentCharacter = EOF;
                }
            } else {
                CharacterError(Stream);
            }
            Stream->Character++;
            return(Stream->CurrentCharacter);
            break;
        case 0:
//----Return static
            return(Stream->CurrentCharacter);
            break;
       case -1:
//----Return static, read next into static
            Auxilliary = Stream->CurrentCharacter;
            if (Stream->CurrentCharacter == '\n') {
                Stream->Line++;
                Stream->Character = 0;
            }
            if (Stream->FileHandle != NULL) {
                Stream->CurrentCharacter = fgetc(Stream->FileHandle);
            } else if (Stream->StringFileContent != NULL) {
                Stream->CurrentCharacter = 
Stream->StringFileContent[Stream->StringOffset];
                Stream->StringOffset++;
//----Convert end of string to end of file
                if (Stream->CurrentCharacter == '\0') {
                    Stream->CurrentCharacter = EOF;
                }
            } else {
                CharacterError(Stream);
            }
            Stream->Character++;
            return(Auxilliary);
            break;
       default:
            return(EOF);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
StatusType StringToStatus(char * StatusString) {

    String ErrorMessage;

    if (!strcmp(StatusString,"initial")) {
        return(initial);
    }
    if (!strcmp(StatusString,"derived")) {
        return(derived);
    }
    if (!strcmp(StatusString,"assumption")) {
        return(assumption);
    }
    if (!strcmp(StatusString,"axiom")) {
        return(axiom);
    }
    if (!strcmp(StatusString,"hypothesis")) {
        return(hypothesis);
    }
    if (!strcmp(StatusString,"definition")) {
        return(definition);
    }
    if (!strcmp(StatusString,"lemma")) {
        return(lemma);
    }
    if (!strcmp(StatusString,"theorem")) {
        return(theorem);
    }
    if (!strcmp(StatusString,"corollary")) {
        return(corollary);
    }
    if (!strcmp(StatusString,"conjecture")) {
        return(conjecture);
    }
    if (!strcmp(StatusString,"question")) {
        return(question);
    }
    if (!strcmp(StatusString,"answer")) {
        return(answer);
    }
    if (!strcmp(StatusString,"negated_conjecture")) {
        return(negated_conjecture);
    }
    if (!strcmp(StatusString,"plain")) {
        return(plain);
    }
    if (!strcmp(StatusString,"type")) {
        return(type);
    }
    if (!strcmp(StatusString,"fi_domain")) {
        return(fi_domain);
    }
    if (!strcmp(StatusString,"fi_functors")) {
        return(fi_functors);
    }
    if (!strcmp(StatusString,"fi_predicates")) {
        return(fi_predicates);
    }
    if (!strcmp(StatusString,"interpretation")) {
        return(interpretation);
    }
    if (!strcmp(StatusString,"unknown")) {
        return(unknown);
    }
    if (!strcmp(StatusString,"knowledge")) {
        return(knowledge);
    }
    if (!strcmp(StatusString,"external")) {
        return(external);
    }
    if (!strcmp(StatusString,"logic")) {
        return(logic);
    }
    if (!strcmp(StatusString,"input")) {
        return(tpi_input);
    }
    if (!strcmp(StatusString,"output")) {
        return(tpi_output);
    }
    if (!strcmp(StatusString,"activate")) {
        return(tpi_activate);
    }
    if (!strcmp(StatusString,"deactivate")) {
        return(tpi_deactivate);
    }
    if (!strcmp(StatusString,"delete")) {
        return(tpi_delete);
    }
    if (!strcmp(StatusString,"set_role")) {
        return(tpi_set_role);
    }
    if (!strcmp(StatusString,"start_group")) {
        return(tpi_start_group);
    }
    if (!strcmp(StatusString,"end_group")) {
        return(tpi_end_group);
    }
    if (!strcmp(StatusString,"activate_group")) {
        return(tpi_activate_group);
    }
    if (!strcmp(StatusString,"deactivate_group")) {
        return(tpi_deactivate_group);
    }
    if (!strcmp(StatusString,"delete_group")) {
        return(tpi_delete_group);
    }
    if (!strcmp(StatusString,"setenv")) {
        return(tpi_setenv);
    }
    if (!strcmp(StatusString,"waitenv")) {
        return(tpi_waitenv);
    }
    if (!strcmp(StatusString,"unsetenv")) {
        return(tpi_unsetenv);
    }
    if (!strcmp(StatusString,"set_logic")) {
        return(tpi_set_logic);
    }
    if (!strcmp(StatusString,"execute")) {
        return(tpi_execute);
    }
    if (!strcmp(StatusString,"execute_async")) {
        return(tpi_execute_async);
    }
    if (!strcmp(StatusString,"filter")) {
        return(tpi_filter);
    }
    if (!strcmp(StatusString,"generate")) {
        return(tpi_generate);
    }
    if (!strcmp(StatusString,"mktemp")) {
        return(tpi_mktemp);
    }
    if (!strcmp(StatusString,"assert")) {
        return(tpi_assert);
    }
    if (!strcmp(StatusString,"write")) {
        return(tpi_write);
    }
    if (!strcmp(StatusString,"clean")) {
        return(tpi_clean);
    }
    if (!strcmp(StatusString,"exit")) {
        return(tpi_exit);
    }
    sprintf(ErrorMessage,"Not a string to make into a role: %s",StatusString);
    CodingError(ErrorMessage);
    return(nonstatus);
}
//-------------------------------------------------------------------------------------------------
char * StatusToString(StatusType Status) {

    String ErrorMessage;

     switch (Status) {
        case initial:
            return("initial");
            break;
        case derived:
            return("derived");
            break;
        case assumption:
            return("assumption");
            break;
        case axiom:
            return("axiom");
            break;
        case hypothesis:
            return("hypothesis");
            break;
        case definition:
            return("definition");
            break;
        case lemma:
            return("lemma");
            break;
        case theorem:
            return("theorem");
            break;
        case corollary:
            return("corollary");
            break;
        case conjecture:
            return("conjecture");
            break;
        case question:
            return("question");
            break;
        case answer:
            return("answer");
            break;
        case negated_conjecture:
            return("negated_conjecture");
            break;
        case plain:
            return("plain");
            break;
        case type:
            return("type");
            break;
        case fi_domain:
            return("fi_domain");
            break;
        case fi_functors:
            return("fi_functors");
            break;
        case fi_predicates:
            return("fi_predicates");
            break;
        case interpretation:
            return("interpretation");
            break;
        case unknown:
            return("unknown");
            break;
        case knowledge:
            return("knowledge");
            break;
        case logic:
            return("logic");
            break;
        case external:
            return("external");
            break;
        case tpi_input:
            return("input");
            break;
        case tpi_output:
            return("output");
            break;
        case tpi_activate:
            return("activate");
            break;
        case tpi_deactivate:
            return("deactivate");
            break;
        case tpi_delete:
            return("delete");
            break;
        case tpi_set_role:
            return("set_role");
            break;
        case tpi_start_group:
            return("start_group");
            break;
        case tpi_end_group:
            return("end_group");
            break;
        case tpi_activate_group:
            return("activate_group");
            break;
        case tpi_deactivate_group:
            return("deactivate_group");
            break;
        case tpi_delete_group:
            return("delete_group");
            break;
        case tpi_setenv:
            return("setenv");
            break;
        case tpi_waitenv:
            return("waitenv");
            break;
        case tpi_unsetenv:
            return("unsetenv");
            break;
        case tpi_set_logic:
            return("set_logic");
            break;
        case tpi_execute:
            return("execute");
            break;
        case tpi_execute_async:
            return("execute_async");
            break;
        case tpi_filter:
            return("filter");
            break;
        case tpi_generate:
            return("generate");
            break;
        case tpi_mktemp:
            return("mktemp");
            break;
        case tpi_assert:
            return("assert");
            break;
        case tpi_write:
            return("write");
            break;
        case tpi_clean:
            return("clean");
            break;
        case tpi_exit:
            return("exit");
            break;
        default:
            sprintf(ErrorMessage,"Not a role to make into a string, index is %d",Status);
            CodingError(ErrorMessage);
            return(NULL);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
ConnectiveType StringToConnective(char * ConnectiveString) {

    String ErrorMessage;

    if (!strcmp(ConnectiveString,"|")) {
        return(disjunction);
    }
    if (!strcmp(ConnectiveString,"&")) {
        return(conjunction);
    }
    if (!strcmp(ConnectiveString,"<=>")) {
        return(equivalence);
    }
    if (!strcmp(ConnectiveString,"=>")) {
        return(implication);
    }
    if (!strcmp(ConnectiveString,"<=")) {
        return(reverseimplication);
    }
    if (!strcmp(ConnectiveString,"<~>")) {
        return(nonequivalence);
    }
    if (!strcmp(ConnectiveString,"~|")) {
        return(negateddisjunction);
    }
    if (!strcmp(ConnectiveString,"~&")) {
        return(negatedconjunction);
    }
    if (!strcmp(ConnectiveString,"~")) {
        return(negation);
    }
    if (!strcmp(ConnectiveString,"--")) {
        return(negation);
    }
    if (!strcmp(ConnectiveString,"!")) {
        return(universal);
    }
    if (!strcmp(ConnectiveString,"?")) {
        return(existential);
    }
    if (!strcmp(ConnectiveString,"^")) {
        return(lambda);
    }
    if (!strcmp(ConnectiveString,"!>")) {
        return(pibinder);
    }
    if (!strcmp(ConnectiveString,"?*")) {
        return(sigmabinder);
    }
    if (!strcmp(ConnectiveString,"@+")) {
        return(choicebinder);
    }
    if (!strcmp(ConnectiveString,"@-")) {
        return(descriptionbinder);
    }
    if (!strcmp(ConnectiveString,"@")) {
        return(application);
    }
    if (!strcmp(ConnectiveString,"=")) {
        return(equation);
    }
    if (!strcmp(ConnectiveString,"@=")) {
        return(typedequation);
    }
    if (!strcmp(ConnectiveString,"!=")) {
        return(negequation);
    }
    if (!strcmp(ConnectiveString,"!!")) {
        return(pi);
    }
    if (!strcmp(ConnectiveString,"??")) {
        return(sigma);
    }
    if (!strcmp(ConnectiveString,"@@+")) {
        return(choice);
    }
    if (!strcmp(ConnectiveString,"@@-")) {
        return(description);
    }
    if (!strcmp(ConnectiveString,":")) {
        return(typecolon);
    }
    if (!strcmp(ConnectiveString,"<<")) {
        return(subtype);
    }
    if (!strcmp(ConnectiveString,">")) {
        return(maparrow);
    }
    if (!strcmp(ConnectiveString,"*")) {
        return(xprodtype);
    }
    if (!strcmp(ConnectiveString,"+")) {
        return(uniontype);
    }
    if (!strcmp(ConnectiveString,"-->")) {
        return(gentzenarrow);
    }
    if (!strcmp(ConnectiveString,":=")) {
        return(assignmentsym);
    }
    if (!strcmp(ConnectiveString,"==")) {
        return(identicalsym);
    }
    if (!strcmp(ConnectiveString,"[.]")) {
        return(box);
    }
    if (!strcmp(ConnectiveString,"<.>")) {
        return(diamond);
    }
    if (!strcmp(ConnectiveString,"{.}")) {
        return(quatrefoil);
    }
    if (!strcmp(ConnectiveString,"(.)")) {
        return(circle);
    }
    sprintf(ErrorMessage,"Not a string to make into a connective: %s",ConnectiveString);
    CodingError(ErrorMessage);
    return(none);
}
//-------------------------------------------------------------------------------------------------
char * ConnectiveToString(ConnectiveType Connective) {

    String ErrorMessage;

    switch (Connective) {
        case disjunction:
            return("|");
            break;
        case conjunction:
            return("&");
            break;
        case equivalence:
            return("<=>");
            break;
        case implication:
            return("=>");
            break;
        case reverseimplication:
            return("<=");
            break;
        case nonequivalence:
            return("<~>");
            break;
        case negateddisjunction:
            return("~|");
            break;
        case negatedconjunction:
            return("~&");
            break;
        case negation:
            return("~");
            break;
        case universal:
            return("!");
            break;
        case existential:
            return("?");
            break;
        case lambda:
            return("^");
            break;
        case pibinder:
            return("!>");
            break;
        case sigmabinder:
            return("?*");
            break;
        case choicebinder:
            return("@+");
            break;
        case descriptionbinder:
            return("@-");
            break;
        case application:
            return("@");
            break;
        case equation:
            return("=");
            break;
        case typedequation:
            return("@=");
            break;
        case negequation:
            return("!=");
            break;
        case pi:
            return("!!");
            break;
        case sigma:
            return("??");
            break;
        case choice:
            return("@@+");
            break;
        case description:
            return("@@-");
            break;
        case typecolon:
            return(":");
            break;
        case subtype:
            return(" <<");
            break;
        case maparrow:
            return(">");
            break;
        case xprodtype:
            return("*");
            break;
        case uniontype:
            return("+");
            break;
        case gentzenarrow:
            return("-->");
            break;
        case assignmentsym:
            return(":=");
            break;
        case identicalsym:
            return("==");
            break;
        case box:
            return("[.]");
            break;
        case diamond:
            return("<.>");
            break;
        case quatrefoil:
            return("{.}");
            break;
        case circle:
            return("(.)");
            break;
        case brackets:
            return("()");
            break;
        case outermost:
            return("outermost");
            break;
        case none:
            return("none");
            break;
        default:
            sprintf(ErrorMessage,"Not a connective to make into a string, index is %d",Connective);
            CodingError(ErrorMessage);
            return(NULL);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
SyntaxType StringToSyntax(char * SyntaxString) {

    String ErrorMessage;

    if (!strcmp(SyntaxString,"tpi")) {
        return(tptp_tpi);
    }
    if (!strcmp(SyntaxString,"thf")) {
        return(tptp_thf);
    }
    if (!strcmp(SyntaxString,"tff")) {
        return(tptp_tff);
    }
    if (!strcmp(SyntaxString,"tcf")) {
        return(tptp_tcf);
    }
    if (!strcmp(SyntaxString,"fof")) {
        return(tptp_fof);
    }
    if (!strcmp(SyntaxString,"cnf")) {
        return(tptp_cnf);
    }
    if (!strcmp(SyntaxString,"include")) {
        return(include);
    }
    sprintf(ErrorMessage,"Not a string to make into a syntax type: %s",SyntaxString);
    CodingError(ErrorMessage);
    return(nontype);
}
//-------------------------------------------------------------------------------------------------
char * TokenTypeToString(TokenType Type) {

    String ErrorMessage;

    switch (Type) {
        case punctuation:
            return("punctuation");
            break;
        case quantifier:
            return("quantifier");
            break;
        case unary_connective:
            return("unary_connective");
            break;
        case binary_connective:
            return("binary_connective");
            break;
        case number:
            return("number");
            break;
        case distinct_object:
            return("distinct_object");
            break;
        case lower_word:
            return("lower_word");
            break;
        case upper_word:
            return("upper_word");
            break;
        case predicate_symbol:
            return("predicate_symbol");
            break;
        case functor:
            return("functor");
            break;
        case name:
            return("name");
            break;
        case comment_token:
            return("comment_token");
            break;
        case blank_line_token:
            return("blank_line_token");
            break;
        case error:
            return("error");
            break;
        case endeof:
            return("endeof");
            break;
        default:
            sprintf(ErrorMessage,"Not a token type to make into a string, index is %d",Type);
            CodingError(ErrorMessage);
            return(NULL);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
char * SyntaxToString(SyntaxType Syntax) {

    String ErrorMessage;

    switch (Syntax) {
        case tptp_tpi:
            return("tpi");
            break;
        case tptp_thf:
            return("thf");
            break;
        case tptp_tff:
            return("tff");
            break;
        case tptp_tcf:
            return("tcf");
            break;
        case tptp_fof:
            return("fof");
            break;
        case tptp_cnf:
            return("cnf");
            break;
        case tptp_mixed:
            return("mixed");
            break;
        case include:
            return("include");
            break;
        case blank_line:
            return("blank line");
            break;
        case comment:
            return("comment");
            break;
        case nontype:
            return("nontype");
            break;
        default:
            sprintf(ErrorMessage,"Not a syntax type to make into a string, index is %d",Syntax);
            CodingError(ErrorMessage);
            return(NULL);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
char * TermTypeToString(TermType Type) {

    String ErrorMessage;

    switch (Type) {
        case connective:
            return("connective");
            break;
        case term:
            return("term");
            break;
        case atom_as_term:
            return("atom_as_term");
            break;
        case function:
            return("function");
            break;
        case a_type:
            return("a_type");
            break;
        case variable:
            return("variable");
            break;
        case nested_thf:
            return("nested_thf");
            break;
        case nested_tff:
            return("nested_tff");
            break;
        case nested_tcf:
            return("nested_tcf");
            break;
        case nested_fof:
            return("nested_fof");
            break;
        case nested_cnf:
            return("nested_cnf");
            break;
        case nested_fot:
            return("nested_fot");
            break;
        case new_variable:
            return("new_variable");
            break;
        case formula:
            return("formula");
            break;
        case non_logical_data:
            return("non_logical_data");
            break;
        case nonterm:
            return("nonterm");
            break;
        default:
            sprintf(ErrorMessage,"Not a term type to make into a string, index is %d",Type);
            CodingError(ErrorMessage);
            return(NULL);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
SyntaxType NestedTermTypeToSyntax(TermType Type) {

    String ErrorMessage;

    switch (Type) {
        case nested_thf:
            return(tptp_thf);
            break;
        case nested_tff:
            return(tptp_tff);
            break;
        case nested_tcf:
            return(tptp_tcf);
            break;
        case nested_fof:
            return(tptp_fof);
            break;
        case nested_cnf:
            return(tptp_cnf);
            break;
        default:
            sprintf(ErrorMessage,"Not a nested term type to make into a syntax, index is %d",Type);
            CodingError(ErrorMessage);
            return(nontype);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
char * FormulaTypeToString(FormulaTypeType Type) {

    switch (Type) {
        case sequent:
            return("sequent");
            break;
        case assignment:
            return("assignment");
            break;
        case type_declaration:
            return("type_declaration");
            break;
        case quantified:
            return("quantified");
            break;
        case binary:
            return("binary");
            break;
        case unary:
            return("unary");
            break;
        case atom:
            return("atom");
            break;
        case applied_connective:
            return("applied_connective");
            break;
        case tuple:
            return("tuple");
            break;
        case ite_formula:
            return("ite_formula");
            break;
        case let_formula:
            return("let_formula");
            break;
        case nonformulatype:
            return("nonformulatype");
            break;
        default:
            CodingError("Not a formula type to make into a string");
            return(NULL);
            break;
    }
}
//-------------------------------------------------------------------------------------------------
TOKEN BuildToken(TokenType TypeToken,char * LocalValue) {

    TOKEN NewToken;

    NewToken = (TOKEN)(Malloc(sizeof(ReadToken)));
    NewToken->KindToken = TypeToken;
//DEBUG printf("Saving token ===%s===\n",LocalValue);
    NewToken->NameToken = CopyHeapString(LocalValue);

//DEBUG printf("token built is ==%s==\n",NewToken->NameToken);
    return(NewToken);
}
//-------------------------------------------------------------------------------------------------
TOKEN CloneToken(TOKEN TokenCopy) {

    return(BuildToken(TokenCopy->KindToken,TokenCopy->NameToken));
}
//-------------------------------------------------------------------------------------------------
void FreeToken(TOKEN * Pointer) {

    if (*Pointer != NULL) {
        Free((void **)&((*Pointer)->NameToken));
        Free((void **)Pointer);
    }
}
//-------------------------------------------------------------------------------------------------
void IncrementTokenIndex(READFILE Stream,int* Index) {

    (*Index)++;
    if (*Index >= SUPERSUPERSTRINGLENGTH) {
        ReportError("InputError","Token too long",0);
        CharacterError(Stream);
    }
}
//-------------------------------------------------------------------------------------------------
int NumberToken(READFILE Stream,char PreviousChar,char CurrentChar,SuperSuperString LocalValue) {

    int Index;

    if (isdigit(CurrentChar)) {
        Index = 0;
//----If signed, keep sign
        if (PreviousChar != '\0') {
            LocalValue[Index++] = PreviousChar;
        }
        do {
            LocalValue[Index] = CurrentChar;
            CurrentChar = NextCharacter(Stream);
            IncrementTokenIndex(Stream,&Index);
        } while (isdigit(CurrentChar));
//----Rationals, and reals from SPASS-XDB (what is personal hack)
        if (CurrentChar == '/' || CurrentChar == '\\') {
            LocalValue[Index] = CurrentChar;
            CurrentChar = NextCharacter(Stream);
            IncrementTokenIndex(Stream,&Index);
            if (CurrentChar == '+' || CurrentChar == '-') {
                LocalValue[Index] = CurrentChar;
                CurrentChar = NextCharacter(Stream);
                IncrementTokenIndex(Stream,&Index);
            }
//----Check there's something in the denominator
            if (isdigit(CurrentChar)) {
                do {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                } while (isdigit(CurrentChar));
            } else {
                CharacterError(Stream);
            }
        } else {
//----Reals
            if (CurrentChar == '.') {
                do {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                } while (isdigit(CurrentChar));
            }
            if (CurrentChar == 'E' || CurrentChar == 'e') {
                LocalValue[Index] = CurrentChar;
                CurrentChar = NextCharacter(Stream);
                IncrementTokenIndex(Stream,&Index);
                if (CurrentChar == '+' || CurrentChar == '-') {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                }
                if (isdigit(CurrentChar)) {
                    do {
                        LocalValue[Index] = CurrentChar;
                        CurrentChar = NextCharacter(Stream);
                        IncrementTokenIndex(Stream,&Index);
                    } while (isdigit(CurrentChar));
                } else {
//----Exponent without numbers
                    CharacterError(Stream);
                }
            }
        }
        LocalValue[Index] = '\0';
        Stream->Overshot = 1;
        return(1);
    } else {
        return(0);
    }
}
//-------------------------------------------------------------------------------------------------
TOKEN QuotedToken(READFILE Stream,char OpeningQuote,TokenType Type) {

//----static so it doesn't have to get allocated everytime (very often!)
    static SuperSuperString LocalValue;
    int Index;

    Index = 0;
    LocalValue[Index] = OpeningQuote;
    do {
        IncrementTokenIndex(Stream,&Index);
        LocalValue[Index] = NextCharacter(Stream);
//----Check legality - only visibles and only quote and escape escaped
        if (LocalValue[Index] < ' ' || LocalValue[Index] > '~') {
            CharacterError(Stream);
        }
        if (LocalValue[Index] == '\\') {
            IncrementTokenIndex(Stream,&Index);
            LocalValue[Index] = NextCharacter(Stream);
            if (LocalValue[Index] != OpeningQuote && 
LocalValue[Index] != '\\') {
                CharacterError(Stream);
            }
        }
    } while (LocalValue[Index] != OpeningQuote || LocalValue[Index-1] == '\\');
    IncrementTokenIndex(Stream,&Index);
    LocalValue[Index] = '\0';

//----Strip '' quotes from regular lower words
    if (LocalValue[0] == '\'' && islower(LocalValue[1])) {
        Index = 1;
//----Make sure it's legal without the ''s
        while (isalnum(LocalValue[Index]) || LocalValue[Index] == '_') {
            Index++;
        }
        if (Index == strlen(LocalValue) -1) {
            LocalValue[Index] = '\0';
            return(BuildToken(lower_word,&(LocalValue[1])));
        } 
    }

    return(BuildToken(Type,LocalValue));
}
//-------------------------------------------------------------------------------------------------
TOKEN GetNextToken(READFILE Stream) {

    int CurrentChar,PreviousChar;
    int Index;
//----static so it doesn't have to get allocated everytime (very often!)
    static SuperSuperString LocalValue;

//DEBUG printf("char was ==%c==\n",CurrentCharacter(Stream));
    if (Stream->Overshot) {
//DEBUG printf("overshot\n");
        CurrentChar = CurrentCharacter(Stream);
    } else {
//DEBUG printf("get next\n");
        CurrentChar = NextCharacter(Stream);
    }
    Stream->Overshot = 0;

//----Skip whitespace
    while (isspace(CurrentChar)) {
        PreviousChar = CurrentChar;
        CurrentChar = NextCharacter(Stream);
//----Check for a blank line, if required
        if (Stream->NeedNonLogicTokens && PreviousChar == '\n' && CurrentChar == '\n') {
            return(BuildToken(blank_line_token,""));
        }
    }

//DEBUG printf("char is ==%c==\n",CurrentChar);
    switch (CurrentChar) {
        case '/':
            Index = 0;
            LocalValue[Index++] = CurrentChar;
            PreviousChar = CurrentChar;
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '*') {
                LocalValue[Index] = CurrentChar;
                while (CurrentChar != EOF && (CurrentChar != '/' || PreviousChar != '*')) {
                    PreviousChar = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                    LocalValue[Index] = CurrentChar;
                }
                if (CurrentChar == '/') {
//----Add eoln if it's there
                    CurrentChar = NextCharacter(Stream);
                    if (CurrentChar == '\n') {
                        IncrementTokenIndex(Stream,&Index);
                        LocalValue[Index] = CurrentChar;
                    } else {
                        Stream->Overshot = 1;
                    }
                    IncrementTokenIndex(Stream,&Index);
                    LocalValue[Index] = '\0';
                    if (Stream->NeedNonLogicTokens) {
                        return(BuildToken(comment_token,LocalValue));
                    } else {
                        return(GetNextToken(Stream));
                    }
                } else {
                    CharacterError(Stream);
                }
            } else {
                CharacterError(Stream);
            }
            break;
//----# as the first character is still a comment, to make E happy. This is nasty code.
        case '#':
            if (Stream->Character > 1) {
//----Copied from default case below
                Index = 0;
                do {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                } while (isalnum(CurrentChar) || CurrentChar=='_');
                LocalValue[Index] = '\0';
                Stream->Overshot = 1;
                return(BuildToken(lower_word,LocalValue));
            }
//----Otherwise continue to comment processing
        case '%':
            if (Stream->NeedNonLogicTokens) {
                Index = 0;
                do {
                    LocalValue[Index] = CurrentChar;
                    IncrementTokenIndex(Stream,&Index);
                    CurrentChar = NextCharacter(Stream);
                } while (CurrentChar != '\n' && CurrentChar != EOF);
                LocalValue[Index] = '\0';
                Stream->Overshot = 1;
//DEBUG printf("FOUND COMMENT ===%s===\n",LocalValue);
                return(BuildToken(comment_token,LocalValue));
            } else {
//----Discard sequences of comments (recursive approach gave stack overflow)
                do {
                    while (CurrentChar != '\n' && CurrentChar != EOF) {
                        CurrentChar = NextCharacter(Stream);
                    }
                    CurrentChar = NextCharacter(Stream);
//----# comments from E start at column 1
                } while (CurrentChar == '%' || (Stream->Character == 1 && CurrentChar == '#'));
                Stream->Overshot = 1;
                return(GetNextToken(Stream));
            }
            break;
        case '\'':
            return(QuotedToken(Stream,'\'',lower_word));
            break;
        case '(':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '.') {
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == ')') {
                    return(BuildToken(unary_connective,"(.)"));
                } else {
                    CharacterError(Stream);
                }
            } else {
                Stream->Overshot = 1;
                return(BuildToken(punctuation,"("));
            }
            break;
        case ')':
            return(BuildToken(punctuation,")"));
            break;
        case '[':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '.') {
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == ']') {
                    return(BuildToken(unary_connective,"[.]"));
                } else {
                    CharacterError(Stream);
                }
            } else {
                Stream->Overshot = 1;
                return(BuildToken(punctuation,"["));
            }
            break;
        case ']':
            return(BuildToken(punctuation,"]"));
            break;
        case '{':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '.') {
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == '}') {
                    return(BuildToken(unary_connective,"{.}"));
                } else {
                    CharacterError(Stream);
                }
            } else {
                Stream->Overshot = 1;
                return(BuildToken(punctuation,"{"));
            }
            break;
        case '}':
            return(BuildToken(punctuation,"}"));
            break;
        case '!':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '=') {
                return(BuildToken(lower_word,"!="));
            } else if (CurrentChar == '>') {
                return(BuildToken(quantifier,"!>"));
            } else if (CurrentChar == '!') {
                return(BuildToken(lower_word,"!!"));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(quantifier,"!"));
            }
            break;
        case '?':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '*') {
                return(BuildToken(quantifier,"?*"));
            } else if (CurrentChar == '?') {
                return(BuildToken(lower_word,"??"));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(quantifier,"?"));
            }
            break;
        case '^':
            return(BuildToken(quantifier,"^"));
            break;
        case '.':
            return(BuildToken(punctuation,"."));
            break;
        case ':':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '=') {
                return(BuildToken(binary_connective,":="));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(punctuation,":"));
            }
            break;
        case ',':
            return(BuildToken(punctuation,","));
            break;
        case '<':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '='){
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == '>') {
                    return(BuildToken(binary_connective,"<=>"));
                } else {
                    Stream->Overshot = 1;
                    return(BuildToken(binary_connective,"<="));
                }
            } else if (CurrentChar == '~') {
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == '>') {
                    return(BuildToken(binary_connective,"<~>"));
                } else {
                    CharacterError(Stream);
                }
            } else if (CurrentChar == '<') {
                return(BuildToken(binary_connective,"<<"));
            } else if (CurrentChar == '.') {
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == '>') {
                    return(BuildToken(unary_connective,"<.>"));
                } else {
                    CharacterError(Stream);
                }
            } else {
                Stream->Overshot = 1;
                CharacterError(Stream);
            }
            break;
        case '=':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '>') {
                return(BuildToken(binary_connective,"=>"));
            } else if (CurrentChar == '=') {
                return(BuildToken(binary_connective,"=="));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(lower_word,"="));
            }
            break;
        case '~':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '|') {
                return(BuildToken(binary_connective,"~|"));
            } else if (CurrentChar == '&') {
                return(BuildToken(binary_connective,"~&"));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(unary_connective,"~"));
            }
            break;
        case '+':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '+') {
                return(BuildToken(unary_connective,"++"));
            } else if (NumberToken(Stream,'+',CurrentChar,LocalValue)) {
                return(BuildToken(number,LocalValue));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(binary_connective,"+"));
            }
            break;
        case '-':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '-') {
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == '>') {
                    return(BuildToken(binary_connective,"-->"));
                } else {
                    Stream->Overshot = 1;
                    return(BuildToken(unary_connective,"--"));
                }
//----Code copied from below for numbers
            } else if (NumberToken(Stream,'-',CurrentChar,LocalValue)) {
                return(BuildToken(number,LocalValue));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(punctuation,"-"));
            }
            break;
        case '"':
            return(QuotedToken(Stream,'"',distinct_object));
            break;
        case '|':
            return(BuildToken(binary_connective,"|"));
            break;
        case '&':
            return(BuildToken(binary_connective,"&"));
            break;
        case '@':
            CurrentChar = NextCharacter(Stream);
            if (CurrentChar == '@') {
                CurrentChar = NextCharacter(Stream);
                if (CurrentChar == '+') {
                    return(BuildToken(lower_word,"@@+"));
                } else if (CurrentChar == '-') {
                    return(BuildToken(lower_word,"@@-"));
                } else {
                    CharacterError(Stream);
                }
            } else if (CurrentChar == '=') {
                return(BuildToken(lower_word,"@="));
            } else if (CurrentChar == '+') {
                return(BuildToken(quantifier,"@+"));
            } else if (CurrentChar == '-') {
                return(BuildToken(quantifier,"@-"));
            } else {
                Stream->Overshot = 1;
                return(BuildToken(binary_connective,"@"));
            }
            break;
        case '>':
            return(BuildToken(binary_connective,">"));
            break;
        case '*':
            return(BuildToken(binary_connective,"*"));
            break;
        case EOF:
            return(BuildToken(endeof,""));
            break;
        default:
            Index = 0;
            if (CurrentChar == '$' || islower(CurrentChar)) {
                do {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                } while (isalnum(CurrentChar) || CurrentChar=='_' ||
//----Allow second $ for system predicates and functions
(Index == 1 && CurrentChar == '$' && LocalValue[0] == '$'));
                LocalValue[Index] = '\0';
                Stream->Overshot = 1;
//----Ensure $ words have some length
                Index = 0;
                while (LocalValue[Index] == '$') {
                    Index++;
                }
                if (Index > 0 && !islower(LocalValue[Index])) {
                    CharacterError(Stream);
                }
                return(BuildToken(lower_word,LocalValue));
            } else if (isupper(CurrentChar)) {
                do {
                    LocalValue[Index] = CurrentChar;
                    CurrentChar = NextCharacter(Stream);
                    IncrementTokenIndex(Stream,&Index);
                } while (isalnum(CurrentChar) || (CurrentChar=='_'));
                LocalValue[Index] = '\0';
                Stream->Overshot = 1;
//----Nasty hack to allow end of file to be specified by user on input stream
                if (!strcmp(LocalValue,"EOF__")) {
                    return(BuildToken(endeof,""));
                } else {
                    return(BuildToken(upper_word,LocalValue));
                }
//----Numbers
            } else if (NumberToken(Stream,'\0',CurrentChar,LocalValue)) {
                return(BuildToken(number,LocalValue));
            } else {
                CharacterError(Stream);
            }
            break;
    }
//----Need a default return for the error cases which compiler doesn't get
    return(NULL);
}
//-------------------------------------------------------------------------------------------------
TOKEN Token(READFILE Stream, int Operation) {

//----Can't return the current token with a NULL file
    assert(!(Stream == NULL && Operation != 0));

    switch (Operation) {
        case 2:
            FreeToken(&(Stream->Auxilliary));
            FreeToken(&(Stream->CurrentToken));
            return((TOKEN)NULL);
            break;
        case 1:
//----Read into static, return it
//DEBUG if (Stream->CurrentToken != NULL ) printf("Had %s\n",CurrentToken->NameToken);
            FreeToken(&(Stream->Auxilliary));
            FreeToken(&(Stream->CurrentToken));
            Stream->CurrentToken = GetNextToken(Stream);
//DEBUG printf("Have %s\n",Stream->CurrentToken->NameToken);
            return(Stream->CurrentToken);
            break;
        case 0:
//----Return static
            FreeToken(&(Stream->Auxilliary));
            if (Stream->CurrentToken == NULL) {
                Stream->CurrentToken = GetNextToken(Stream);
                return(Stream->CurrentToken);
            } else {
//DEBUG printf("CT ==%s==\n",Stream->CurrentToken->NameToken);
                return(Stream->CurrentToken);
            }
            break;
        case -1:
//----Return static, read next into static
            FreeToken(&(Stream->Auxilliary));
            if (Stream->CurrentToken == NULL) {
                Stream->CurrentToken = GetNextToken(Stream);
            }
            Stream->Auxilliary = Stream->CurrentToken;
            Stream->CurrentToken = GetNextToken(Stream);
//DEBUG printf("%s\n",Stream->Auxilliary->NameToken);
            return(Stream->Auxilliary);
            break;
       default:
            return((TOKEN)NULL);
            break;
    }
}
//---------------------------------------------------------------------------
void TokenWarning(READFILE Stream,char * Message) {

    printf("WARNING: Line %d Char %d Token \"%s\" : %s\n",
Stream->Line,Stream->Character,CurrentToken(Stream)->NameToken,Message);
}
//-------------------------------------------------------------------------------------------------
void TokenError(READFILE Stream,char * Message) {

    String RestOfLine;
    String ErrorMessage;

    strcpy(RestOfLine,"");
    if (Stream->FileHandle != NULL) {
        fgets(RestOfLine,20,Stream->FileHandle);
    } else if (Stream->StringFileContent != NULL) {
        strncat(RestOfLine,Stream->StringFileContent + Stream->StringOffset,20);
    }
    if (strlen(RestOfLine) > 0 && RestOfLine[strlen(RestOfLine)-1] == '\n') {
        RestOfLine[strlen(RestOfLine)-1] = '\0';
    }

    sprintf(ErrorMessage,
"Line %d Char %d Token \"%s\" continuing with \"%s\" : %s",
Stream->Line,Stream->Character,CurrentToken(Stream)->NameToken,RestOfLine,
Message == NULL ? "" : Message);
    ReportError("SyntaxError",ErrorMessage,1);
}
//-------------------------------------------------------------------------------------------------
void SetTokenType(READFILE Stream,TokenType Type) {

    TOKEN ThisToken;

    ThisToken = CurrentToken(Stream);
    if (ThisToken == NULL) {
        CodingError("No token");
    }

    ThisToken->KindToken = Type;
}
//-------------------------------------------------------------------------------------------------
int CheckTokenType(READFILE Stream,TokenType Type) {

    TOKEN ThisToken;

    ThisToken = CurrentToken(Stream);
    if (ThisToken == NULL) {
        CodingError("No token");
    }

    return((ThisToken->KindToken == Type) ||
(Type == predicate_symbol && ThisToken->KindToken == lower_word) ||
(Type == functor && (ThisToken->KindToken == lower_word || 
ThisToken->KindToken == number || ThisToken->KindToken == distinct_object)) ||
(Type == name && (ThisToken->KindToken == lower_word ||
ThisToken->KindToken == number)));
}
//--------------------------------------------------------------------------------------------------
int CheckToken(READFILE Stream,TokenType Type,char * Value) {

//DEBUG printf("Current type = %d Require %d\n",CurrentToken(Stream)->KindToken,Type);
//DEBUG printf("Current value = %s Require %s\n",CurrentToken(Stream)->NameToken,Value);
    return(CheckTokenType(Stream,Type) && 
!strcmp(CurrentToken(Stream)->NameToken,Value));
}
//--------------------------------------------------------------------------------------------------
int TakeTokenType(READFILE Stream,TokenType Type) {

    String ErrorMessage;

    if (CheckTokenType(Stream,Type)) {
        TakeCurrentToken(Stream);
        return(1);
    } else {
        sprintf(ErrorMessage,"Wrong token type, expected %s",TokenTypeToString(Type));
        TokenError(Stream,ErrorMessage);
        return(0);
    }
}
//--------------------------------------------------------------------------------------------------
int TakeToken(READFILE Stream,TokenType Type,char * Value) {

    String ErrorMessage;

    if (CheckTokenType(Stream,Type) && !strcmp(CurrentToken(Stream)->NameToken,Value)) {
        TakeCurrentToken(Stream); 
        return(1);
    } else {
        sprintf(ErrorMessage,"Wrong token type or value, expected %s with value \"%s\"",
TokenTypeToString(Type),Value);
        TokenError(Stream,ErrorMessage);
        return(0);
    }
}
//--------------------------------------------------------------------------------------------------
void EnsureTokenType(READFILE Stream,TokenType Type) {

    String ErrorMessage;

    if (!CheckTokenType(Stream,Type)) {
        sprintf(ErrorMessage,"Wrong token type, expected %s",TokenTypeToString(Type));
        TokenError(Stream,ErrorMessage);
    }
}
//--------------------------------------------------------------------------------------------------
void EnsureTokenNotType(READFILE Stream,TokenType NotType) {

    String ErrorMessage;

    if (CheckTokenType(Stream,NotType)) {
        sprintf(ErrorMessage,"Wrong token type, not expecting %s",TokenTypeToString(NotType));
        TokenError(Stream,ErrorMessage);
    }
}
//--------------------------------------------------------------------------------------------------
void EnsureToken(READFILE Stream,TokenType Type,char * Value) {

    String ErrorMessage;

    if (!CheckToken(Stream,Type,Value)) {
        sprintf(ErrorMessage,"Wrong token type or value, expected %s with value \"%s\"",
TokenTypeToString(Type),Value);
        TokenError(Stream,ErrorMessage);
    }
}
//--------------------------------------------------------------------------------------------------
int AcceptTokenType(READFILE Stream,TokenType Type) {

    String ErrorMessage;

    if (CheckTokenType(Stream,Type)) {
        NextToken(Stream); 
        return(1);
    } else {
        sprintf(ErrorMessage,"Wrong token type, expected %s",TokenTypeToString(Type));
        TokenError(Stream,ErrorMessage);
        return(0);
    }
} 
//--------------------------------------------------------------------------------------------------
int AcceptToken(READFILE Stream,TokenType Type,char * Value) {

    String Message;

    if (CheckTokenType(Stream,Type) && !strcmp(CurrentToken(Stream)->NameToken,Value)) {
        NextToken(Stream); 
        return(1);
    } else {
        sprintf(Message,"Wrong token type or value, expected %s with value \"%s\"",
TokenTypeToString(Type),Value);
        TokenError(Stream,Message);
        return(0);
    }
} 
//--------------------------------------------------------------------------------------------------
int NextThenAcceptTokenType(READFILE Stream,TokenType Type) {
 
    NextToken(Stream); 
    return(AcceptTokenType(Stream,Type));
} 
//--------------------------------------------------------------------------------------------------
int NextThenAcceptToken(READFILE Stream,TokenType Type,char * Value) {
 
    NextToken(Stream); 
    return(AcceptToken(Stream,Type,Value));
} 
//--------------------------------------------------------------------------------------------------

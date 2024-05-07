//----Check if a connective
                if (CheckTokenType(Stream,unary_connective)) {
//DEBUG NOW printf("unary_connective\n");
//----Need to look ahead to see if a connective term or just a ()ed formula
                    Connective = StringToConnective(CurrentToken(Stream)->
NameToken);
                    AcceptTokenType(Stream,unary_connective);
//DEBUG NOW printf("Took the unary, now %s\n",CurrentToken(Stream)->NameToken);
                    if (CheckToken(Stream,punctuation,")")) {
//----Make a string to parse the connective
                        if ((StringStream = OpenStringReadFile(
ConnectiveToString(Connective))) == NULL) {
                            CodingError("Could not open string stream");
                            return(NULL);
                        }
//DEBUG NOW printf("unary_connective term\n");
                        Formula = ParseAtom(StringStream,Language,Context,applied_connective,
EndOfScope,VariablesMustBeQuantified);
                        CloseReadFile(StringStream);
                    } else {
//DEBUG NOW printf("unary applied\n");
//----Parse the formula and make a unary formula structure
                        Formula = NewFormula();
                        Formula->Type = unary;
                        Formula->FormulaUnion.UnaryFormula.Connective =
Connective;
                        Formula->FormulaUnion.UnaryFormula.Formula = 
ParseFormula(Stream,Language,Context,EndOfScope,1,VariablesMustBeQuantified,
none);
//DEBUG NOW printf("Parsed unary applied now %s\n",CurrentToken(Stream)->NameToken);
                    }
                } else if (CheckTokenType(Stream,binary_connective)) {
//DEBUG NOW printf("binary_connective term\n");
                    Formula = ParseAtom(Stream,Language,Context,applied_connective,EndOfScope,
VariablesMustBeQuantified);
                } else {
//DEBUG NOW printf("bracketed formula\n");
                    Formula = ParseFormula(Stream,Language,Context,EndOfScope,1,
VariablesMustBeQuantified,none);
//DEBUG NOW printf("done bracketed\n");
                }
//DEBUG NOW printf("take )\n");

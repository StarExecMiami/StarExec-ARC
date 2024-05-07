cmake_minimum_required(VERSION 3.17)
project(JJParser C)

set(CMAKE_C_STANDARD 99)

add_executable(TestParsing TestParsing.c Compare.c Examine.c FileUtilities.c Interpret.c List.c ListStatistics.c Modify.c ParseTPTP.c ParseTSTP.c Parsing.c PrintDFG.c PrintKIF.c PrintOtter.c PrintSMT2.c PrintSUMO.c PrintTSTP.c PrintXML.c Signature.c Statistics.c SystemOnTPTP.c Tokenizer.c Tree.c TreeStatistics.c Utilities.c)

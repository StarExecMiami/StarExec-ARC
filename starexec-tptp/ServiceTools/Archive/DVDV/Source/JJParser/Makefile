CC = gcc
CFLAGS = -Wall

OBJS = ListStatistics.o List.o Examine.o Modify.o Tree.o TreeStatistics.o ParseTPTP.o ParseTSTP.o PrintTSTP.o Parsing.o Signature.o Tokenizer.o Utilities.o Compare.o

JJParser: $(OBJS)

TestParsing: $(OBJS) TestParsing.o
	$(CC) -o $@ $(OBJS) TestParsing.o

TestTree: $(OBJS) TestTree.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) TestTree.o

clean:
	rm *.o

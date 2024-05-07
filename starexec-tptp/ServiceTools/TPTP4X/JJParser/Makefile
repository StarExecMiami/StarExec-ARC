#----Set TPTP_HOME if not already imported from environment
TPTP_HOME ?= /home/tptp
# TPTP_HOME = /Users/geoff/MyDocuments/Development/TPTPWorld
JJPARSER = $(TPTP_HOME)/ServiceTools/JJParser

CC = gcc
CFLAGS = -Wall -Wformat-overflow=0 -I/usr/local/include -L/usr/local/lib -I$(JJPARSER) -D TPTP_HOME=\"$(TPTP_HOME)\"
LFLAGS = -lcurl -lm

OBJS = $(JJPARSER)/ListStatistics.o $(JJPARSER)/List.o $(JJPARSER)/Examine.o $(JJPARSER)/Modify.o $(JJPARSER)/Tree.o $(JJPARSER)/TreeStatistics.o $(JJPARSER)/ParseTPTP.o $(JJPARSER)/ParseTSTP.o $(JJPARSER)/PrintTSTP.o $(JJPARSER)/Parsing.o $(JJPARSER)/Signature.o $(JJPARSER)/Tokenizer.o $(JJPARSER)/Utilities.o $(JJPARSER)/Compare.o $(JJPARSER)/Interpret.o $(JJPARSER)/PrintXML.o $(JJPARSER)/PrintSMT2.o $(JJPARSER)/PrintDFG.o $(JJPARSER)/PrintOtter.o $(JJPARSER)/PrintKIF.o $(JJPARSER)/PrintSUMO.o $(JJPARSER)/PrintLP.o $(JJPARSER)/FileUtilities.o $(JJPARSER)/SystemOnTPTP.o $(JJPARSER)/Statistics.o

all: $(OBJS)

TestParsing: $(OBJS) TestParsing.o Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) TestParsing.o $(LFLAGS)

DRSParsing: $(OBJS) DRSParsing.o Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) DRSParsing.o $(LFLAGS)

TestTree: $(OBJS) TestTree.o Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) TestTree.o $(LFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $*.c

clean:
	rm -f *.o TestParsing TestTree

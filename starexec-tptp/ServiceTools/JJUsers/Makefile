#----Set TPTP_HOME if not already imported from environment
TPTP_HOME ?= /home/tptp
JJPARSER = $(TPTP_HOME)/ServiceTools/JJParser

CC = gcc
CFLAGS = -Wall -Wformat-overflow=0 -I/usr/local/include -L/usr/local/lib -I$(JJPARSER) -D TPTP_HOME=\"$(TPTP_HOME)\"
LFLAGS = -lcurl -lm

OBJS = $(JJPARSER)/ListStatistics.o $(JJPARSER)/List.o $(JJPARSER)/Examine.o $(JJPARSER)/Modify.o $(JJPARSER)/Tree.o $(JJPARSER)/TreeStatistics.o $(JJPARSER)/ParseTPTP.o $(JJPARSER)/ParseTSTP.o $(JJPARSER)/PrintTSTP.o $(JJPARSER)/Parsing.o $(JJPARSER)/Signature.o $(JJPARSER)/Tokenizer.o $(JJPARSER)/Utilities.o $(JJPARSER)/Compare.o $(JJPARSER)/Interpret.o $(JJPARSER)/PrintXML.o $(JJPARSER)/PrintSMT2.o $(JJPARSER)/PrintDFG.o $(JJPARSER)/PrintOtter.o $(JJPARSER)/PrintKIF.o $(JJPARSER)/PrintSUMO.o $(JJPARSER)/PrintLP.o $(JJPARSER)/FileUtilities.o $(JJPARSER)/SystemOnTPTP.o $(JJPARSER)/Statistics.o

all: most AxiofyC 

#----Most is for all tools used by other people
most: some SPCForProblem

#----Some is only stuff in ServiceTools
some: MakeTreeStats MakeListStats GetSymbols ProofSummary CheckTyping

install: all install-most
	mv AxiofyC $(TPTP_HOME)/ServiceTools/Axiofier

install-most: install-some
	cp SPCForProblem $(TPTP_HOME)/Systems/SPCForProblem---1.0
	mv SPCForProblem $(TPTP_HOME)/SPCs/SPCForProblem

install-some: some
	mv MakeTreeStats $(TPTP_HOME)/ServiceTools/MakeTreeStats
	mv MakeListStats $(TPTP_HOME)/ServiceTools/MakeListStats
	mv GetSymbols $(TPTP_HOME)/ServiceTools/GetSymbols
	mv ProofSummary $(TPTP_HOME)/ServiceTools/ProofSummary
	mv CheckTyping $(TPTP_HOME)/ServiceTools/CheckTyping

MakeTreeStats: $(OBJS) MakeTreeStats.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) MakeTreeStats.o $(LFLAGS)

MakeListStats: $(OBJS) MakeListStats.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) MakeListStats.o $(LFLAGS)

AxiofyC: $(OBJS) AxiofyC.o
	$(CC) $(CFLAGS) -O6 -o $@ $(OBJS) AxiofyC.o $(LFLAGS)

SPCForProblem: $(OBJS) SPCForProblem.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) SPCForProblem.o $(LFLAGS)

GetSymbols: $(OBJS) GetSymbols.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) GetSymbols.o $(LFLAGS)

CheckTyping: $(OBJS) CheckTyping.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) CheckTyping.o $(LFLAGS)

ProofSummary: $(OBJS) ProofSummary.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) ProofSummary.o $(LFLAGS)

NaprocheProofSummary: $(OBJS) NaprocheProofSummary.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) NaprocheProofSummary.o $(LFLAGS)

CompareFilesOfFormulae: $(OBJS) CompareFilesOfFormulae.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) CompareFilesOfFormulae.o $(LFLAGS)

SortByUsefulInfoField: $(OBJS) SortByUsefulInfoField.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) SortByUsefulInfoField.o $(LFLAGS)

PostOrderTree: $(OBJS) PostOrderTree.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) PostOrderTree.o $(LFLAGS)

TPTP2XML: $(OBJS) TPTP2XML.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) TPTP2XML.o $(LFLAGS)

clean:
	rm -f *.o

#------------------------------------------------------------------------------
# FILE: Makefile
# AUTHOR: Steven Trac
# 
# Makefile for Faust Data Structures.
#------------------------------------------------------------------------------

CC = g++
CFLAGS = -Wall -g

JDIR	= ../JJParser/

JJ_OBJS = 	$(JDIR)ListStatistics.o $(JDIR)List.o $(JDIR)Examine.o $(JDIR)Modify.o $(JDIR)Tree.o $(JDIR)TreeStatistics.o $(JDIR)ParseTPTP.o $(JDIR)ParseTSTP.o $(JDIR)PrintTSTP.o $(JDIR)Parsing.o $(JDIR)Signature.o $(JDIR)Tokenizer.o $(JDIR)Utilities.o 

JJ_HDR = $(JDIR)ListStatistics.h $(JDIR)List.h $(JDIR)Examine.h $(JDIR)Modify.h $(JDIR)Tree.h $(JDIR)TreeStatistics.h $(JDIR)ParseTPTP.h $(JDIR)ParseTSTP.h $(JDIR)PrintTSTP.h $(JDIR)Parsing.h $(JDIR)Signature.h $(JDIR)Tokenizer.h $(JDIR)Utilities.h 

FOF2ECNF: $(JJ_OBJS) ConvertToECNF.o FOF2ECNF.o
	$(CC) $(CFLAGS) -o $@ $(JJ_OBJS) ConvertToECNF.o FOF2ECNF.o

ConvertToECNF.o: ConvertToECNF.h ConvertToECNF.C $(JJ_HDR)
	$(CC) $(CFLAGS) -c ConvertToECNF.C -Wno-deprecated

FOF2ECNF.o: FOF2ECNF.C ConvertToECNF.C ConvertToECNF.h $(JJ_HDR)
	$(CC) $(CFLAGS) -c FOF2ECNF.C -Wno-deprecated

clean:
	rm -f *.o *~ ../JJParser/*.o

lc:
	wc -l *.C *.H *.c *.h

CC = gcc
CFLAGS = -Wall -g -O
JJ_DIR = JJParser/

JJ_OBJS = $(JJ_DIR)ListStatistics.o $(JJ_DIR)List.o $(JJ_DIR)Examine.o $(JJ_DIR)Modify.o $(JJ_DIR)Tree.o $(JJ_DIR)TreeStatistics.o $(JJ_DIR)ParseTPTP.o $(JJ_DIR)ParseTSTP.o $(JJ_DIR)PrintTSTP.o $(JJ_DIR)Parsing.o $(JJ_DIR)Signature.o $(JJ_DIR)Tokenizer.o $(JJ_DIR)Utilities.o $(JJ_DIR)Compare.o 

DV_OBJS = data_structures.o \
	  dvdvIIutils.o \
	  dvdvProcessor.o \
	  structure_check.o \
	  esplit.o \
	  cycles.o

dvdv: $(JJ_OBJS) $(DV_OBJS) dvdv.o
	$(CC) $(CFLAGS) -o $@ $(JJ_OBJS) $(DV_OBJS) dvdv.o

sp2: spider2.o
	$(CC) $(CFLAGS) -o $@ spider2.o
	cp sp2 testing

sp2_t: sp2_tester.o
	$(CC) $(CFLAGS) -o $@ sp2_tester.o
	cp sp2_t testing

sp: dv_spider.o
	$(CC) $(CFLAGS) -o $@ dv_spider.o

clean:
	rm -f *.o *~ $(JJ_DIR)*.o \#*.*\# dvdv

backup:
	echo "Building backup tarball for " `date`; \
	gtar czv *.h *.c HELP Makefile \
	> dvdv-`date +%m`-`date +%d`-`date +%y`.tar.gz;

export:
	echo "Building distribution tarball for " `date`; \
	gtar czv *.h *.c HELP Makefile JJParser/*.c \
	JJParser/*.h DVDV_Files/ \
	> dvdv-EXPORT-`date +%m`-`date +%d`-`date +%y`.tar.gz;

tags:
	etags *.c *.h

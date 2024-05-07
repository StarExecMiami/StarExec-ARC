PCC = gplc
# PFLAGS = -L -static

all: 
	rm -f CompareClauses
	$(MAKE) CompareClauses

install: all

CompareClauses: CompareClauses.pl
	$(PCC) $(PFLAGS) CompareClauses.pl

clean:

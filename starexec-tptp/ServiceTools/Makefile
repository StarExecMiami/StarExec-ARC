clean-install-some: clean install-some

clean-install-most: clean install-most

clean-install: clean install

all: most
	$(MAKE) -C JJUsers all
	$(MAKE) -C CompareClauses all

most: some
	$(MAKE) -C JJUsers most

some:
	$(MAKE) -C JJUsers some
	$(MAKE) -C TPTP4XDir all
	$(MAKE) -C TPIIDir all
	$(MAKE) -C GDVDir all
	$(MAKE) -C Otter2TPTP/Source all

install: all install-most
	$(MAKE) -C JJUsers install
	$(MAKE) -C CompareClauses install

install-most: most install-some
	$(MAKE) -C JJUsers install-most

install-some: some
	$(MAKE) -C JJUsers install-some
	$(MAKE) -C TPTP4XDir install
	$(MAKE) -C TPIIDir install
	$(MAKE) -C GDVDir install
	$(MAKE) -C Otter2TPTP/Source install

clean:
	$(MAKE) -C JJParser clean
	$(MAKE) -C TPTP4XDir clean
	$(MAKE) -C TPIIDir clean
	$(MAKE) -C JJUsers clean
	$(MAKE) -C GDVDir clean
	$(MAKE) -C Otter2TPTP/Source clean
	$(MAKE) -C CompareClauses clean

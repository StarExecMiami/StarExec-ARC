#############################################################################
#
#  Makefile for building Otter 3.3.  There is no configuration script
#  or higher-level make.  Edit this file to configure compilation of
#  Otter.  There are three things you may need to change:
#
#    DFLAGS  - to control conditional compilation to enable/disable things
#    CC      - to specify the C compiler (usually cc or gcc)
#    CFLAGS  - to specify optimization, debugging, and profiling
#
#  This should work as is for recent versions of Linux.
#
#  To compile Otter2TPTP, "make" and cross your fingers!
#  The binary will be left in this directory.  There is no man page.
#
#  !!!NOTE!!!  On Solaris, you'll probably want to add -DTP_NO_CLOCKS
#  to the DFLAGS line.  If you don't, Otter might run VERY slowly.
#
#############################################################################

#############################################################################
#
#  The DFLAGS symbol, defined after this section of comments, controls
#  conditional compilation; it enables or disables various features.
#
#  Enable features:
#
#    -DTP_NAMES will get username, hostname.
#        Don't use if you get errors about gethostname, getuid, getpwuid.
#    -DTP_SIGNAL will cause some signals to be caught.
#        Don't use if you get errors about signal, SIGINT, SIGSEGV.
#    -DTP_FORK will allow interactive forks and case splitting.
#        Don't use if you get errors about fork, wait.
#    -DTP_RUSAGE for calls to getrusage() (user time, system time).
#        Don't use if you get errors about rusage, getrusage, RUSAGE_SELF.
#
#  Disable features:
#
#    -DTP_NO_CLOCKS disables most timing---this can save a lot of system
#        CPU time, because many operations are timed.
#        This should definitely be used on FreeBSD (2.1.0), which seems
#        to have a REALLY SLOW getrusage() system call.
#    -DTP_ABSOLUTELY_NO_CLOCKS disables all of the timing.
#        Use this as a last resort for timing or clock errrors.
#
#  The default settings, containing the full set of features:
#
#  DFLAGS = -DTP_NAMES -DTP_SIGNAL -DTP_FORK -DTP_RUSAGE
#
###############
#
#  Here are some notes about which features work on various OSs:
#
#  Solaris (SunOS 5.7) - has a very slow getrusage() system call, so use
#
#  DFLAGS = -DTP_NAMES -DTP_SIGNAL -DTP_FORK -DTP_RUSAGE -DTP_NO_CLOCKS
#
###############

# OK, here is where to define the DFLAGS:

DFLAGS = -DTP_NAMES -DTP_SIGNAL -DTP_FORK -DTP_RUSAGE $(XFLAGS)

#############################################################################
#
# Specify the C compiler.  I recommend gcc (GNU C Compiler) if you have it.
# In many Linux environments, cc is just a symlink to gcc.

CC = gcc

#############################################################################
#
# Specify the compiler flags; include DFLAGS (above) -- Pick one of these
#
# optimized

CFLAGS = -O $(DFLAGS)

#
# check for strict ANSI conformance with Solaris cc:
#
# CFLAGS = -Xc $(DFLAGS)
#
# various checks for gcc:
#
# CFLAGS = -Wall $(DFLAGS)
# CFLAGS = -ansi -pedantic -Wall $(DFLAGS)
# CFLAGS = -Wtraditional -Wpointer-arith -Wcast-qual -Wcast-align $(DFLAGS)
# CFLAGS = -Wconversion -Wstrict-prototypes -Wmissing-prototypes\
#      -Wmissing-declarations -Wredundant-decls -Wnested-externs  $(DFLAGS)
#
# save symbols for debuggers
# CFLAGS = -g $(DFLAGS)
#
# optimized, debugging
# CFLAGS = -O -g $(DFLAGS)
#
# gprof profiling
# CFLAGS = -pg -O $(DFLAGS)
#
#############################################################################

OBJECTS = av.o io.o share.o fpa.o clocks.o unify.o demod.o weight.o\
    imd.o is.o clause.o options.o resolve.o index.o paramod.o\
    formula.o process.o misc.o lrpo.o linkur.o linkhyp.o foreign.o\
    geometry.o hot.o nonport.o check.o hints.o hints2.o attrib.o\
    case.o lisp.o ivy.o pickdiff.o overbeek.o multijust.o lists.o

#############################################################################

all: Otter2TPTP 

install:
	mv Otter2TPTP ..

Otter2TPTP: main.o libotter.a
	$(CC) $(CFLAGS) main.o libotter.a -o Otter2TPTP

libotter.a: $(OBJECTS)
	$(AR) rs libotter.a $(OBJECTS)

main.o $(OBJECTS): header.h types.h macros.h cos.h proto.h foreign.h lisp.h

clean:
	/bin/rm -f *.o *.a

realclean:
	/bin/rm -f *.o *.a Otter2TPTP *~

prototypes:
	/bin/csh make-prototypes main.c $(OBJECTS)


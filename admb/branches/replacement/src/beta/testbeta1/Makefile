.SUFFIXES: .tpl
.PHONY: CLEAN RULES


# by default targets are placed in the bin sub-directory of the users home directory
BIN_DIR = .

ADMB_HOME=/home/jsibert/admb/branches/replacement/build/dists/admb_gcc411_fedora8

NEWFLAGS=-m64  -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable  -DUSE_LAPLACE -DSAFE_ALL -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I/home/other/cephes/double -I$(ADMB_HOME)/include 


#CFLAGS =  -Wno-deprecated -fpermissive -c -O3 -I. -I$(ADMB_HOME)/include -D__GNUDOS__ -DOPT_LIB -Dlinux -DUSE_LAPLACE
#CFLAGS =  -Wno-deprecated -fpermissive -c -O3 -I. -I../cephes-beta -I../df1b2-separable -I$(ADMB_HOME)/include -D__GNUDOS__ -DOPT_LIB -Dlinux -DUSE_LAPLACE
#CFLAGS =  -Wno-deprecated -fpermissive -c -O3 -I. -I../cephes-beta -I$(ADMB_HOME)/include -D__GNUDOS__ -DOPT_LIB -Dlinux -DUSE_LAPLACE

CFLAGS =  -Wno-deprecated -fpermissive -c -O3 -I. -I/home/other/cephes/double -I$(ADMB_HOME)/include -D__GNUDOS__ -DOPT_LIB -Dlinux -DUSE_LAPLACE
LFLAGS=-lm -L$(ADMB_HOME)/lib -ldf1b2o -ladmod -ladt -lads -ldf1b2o -ladmod -ladt -lads -lstdc++ -lm -lads -ladt 

CC=g++
LL=$(CC)

OBJECTS= testbeta.o df13tester.o df33tester.o

testbeta: $(OBJECTS)
	$(LL) -o$@ $(DEBUG) $^ $(LFLAGS)

.cpp.o:
	$(CC) $(NEWFLAGS) $<

.tpl.cpp:
	$(ADMB_HOME)/bin/tpl2rem $*

RULES:
	@echo "BIN_DIR  = "$(BIN_DIR)
	@echo "ADMB_HOME   = "$(ADMB_HOME)
	@echo "CC       = "$(CC)
	@echo "LL       = "$(LL)
	@echo "CFLAGS   = "$(CFLAGS)
	@echo "LFLAGS   = "$(LFLAGS)
	@echo "EXE      = "$(EXE)
	@echo "STRIP    = "$(STRIP)

CLEAN:
	rm -vf $(OBJECTS)
	rm -vf testbeta.cpp
	rm -vf testbeta


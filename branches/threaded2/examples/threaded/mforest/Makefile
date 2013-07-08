#$Id: Makefile 3054M 2013-01-11 20:32:12Z (local) $
#
# identify some extra file name suffixes
.SUFFIXES: .tpl .cpp .o .obj

# tell make not to delete these intermediate targets
.PRECIOUS: %.cpp %.o %.obj

# make some special targets
.PHONY: all rules

export ADMB_HOME=/home/jsibert/admb/threaded2/build/dists/admb_gcc411_fedora8
CC=/usr/local/gcc-4.8.0/bin/g++
LL = $(CC)

CFLAGS = -c -pthread -fpermissive -m64 -Wall -Wno-deprecated -ggdb -I. -I$(ADMB_HOME)/include -I$(ADMB_HOME)/contrib -D__GNUDOS__ -Dlinux -DUSE_LAPLACE -DSAFE_ARRAYS
#CFLAGS = -c -pthread -fpermissive -m64 -Wall -Wno-deprecated -ggdb -I. -I$(ADMB_HOME)/include -I$(ADMB_HOME)/contrib -D__GNUDOS__ -Dlinux -DUSE_LAPLACE -DOPT_LIB


LFLAGS = -L$(ADMB_HOME)/lib -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -lpthread
#LFLAGS = -L$(ADMB_HOME)/lib -ldf1b2s -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -lpthread


#all: mforest

mforest: mforest.o
	@echo
	@echo ------- Link $@
	$(LL) -o $@ $^ $(LFLAGS)
	@echo ------- Done

mforest-nothreads: mforest-nothreads.o dfqromb.o
	@echo
	@echo ------- Link $@
	$(LL) $^ $(LFLAGS) -o $@ 
	@echo ------- Done

# compile the C++ into an object file
%.o:%.cpp;
	@echo
	@echo ------- Compile $<
	$(CC) $(CFLAGS)  -o $@ $<
	@echo ------- Done

# translate the ADMB template into C++ code
%.cpp:%.tpl;
	@echo
	@echo ------- Making $@
	@echo ------- Translate $<
	$(ADMB_HOME)/bin/tpl2cpp $*
	@echo ------- Done

%.htp:%.tpl;
	@echo
	@echo ------- Making $@
	@echo ------- Translate $<
	$(ADMB_HOME)/bin/tpl2cpp $*

# generate some information about what your are doing
rules:
	@echo
	@echo PWD = $(PWD)
	@echo OBJECTS = $(OBJECTS)
	@echo OSTYPE = $(OSTYPE)
	@echo OS     = $(OS)
	@echo ADMB_HOME = $(ADMB_HOME)
	@echo CC = $(CC)
	$(CC) --version
	@echo LL = $(LL)
	@echo CFLAGS = $(CFLAGS)
	@echo LFLAGS = $(LFLAGS)

clean:
	rm -fv mforest.cpp
	rm -fv mforest
	rm -fv mforest-nothreads.cpp
	rm -fv mforest-nothreads
	rm -fv *.o
	rm -fv *.htp
	rm -fv *.log
	rm -fv *.std
	rm -fv *.cov
	rm -fv *.cor
	rm -fv *.par
	rm -fv *.hes
	rm -fv *.eva
	rm -fv *.bar
	rm -fv *.rep
	rm -fv derivatives
	rm -fv variance
	rm -fv eigv.rpt
	rm -fv make.out
	rm -fv *master
	rm -fv log*

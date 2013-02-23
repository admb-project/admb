#$Id: Makefile 3054M 2013-01-11 20:32:12Z (local) $
#
# identify some extra file name suffixes
.SUFFIXES: .tpl .cpp .o .obj

# tell make not to delete these intermediate targets
.PRECIOUS: %.cpp %.o %.obj

# make some special targets
.PHONY: all rules

ifeq ($(HOSTNAME),katsuo)
  export ADMB_HOME=/home/jsibert/admb-threaded2/build/dists/admb_gcc411_fedora8
else
  export ADMB_HOME=/home/jsibert/admb/admb-threaded2/build/dists/admb_gcc411_fedora8
endif
CC = g++
LL = g++

CFLAGS = -c -pthread -fpermissive -m64 -Wall -Wno-deprecated -ggdb -I. -I$(ADMB_HOME)/include -I$(ADMB_HOME)/contrib -D__GNUDOS__ -Dlinux -DUSE_LAPLACE -DSAFE_ARRAYS


LFLAGS = -L$(ADMB_HOME)/lib -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -lpthread

OBJECTS=adpthread_manager.o msimple.o simple_thread.o

# link the object file into the executable 
msimple: $(OBJECTS) 
	@echo
	@echo ------- Link $@
	$(LL) -o $@ $^ $(LFLAGS)
	@echo ------- Done

simple_thread.o: simple_thread.cpp msimple.tpl msimple.htp
	@echo
	@echo ------- Compile $<
	sed -i '/class model_data : public ad_comm{/a\
          public:' msimple.htp
	sed -i '{s/^private/public/}' msimple.htp
	$(CC) $(CFLAGS)  -o $@ $<
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
#cp -v $@ $(OBJ_DIR)
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
	rm -fv msimple.cpp
	rm -fv msimple
	rm -fv *.o
	rm -fv *.htp
	rm -fv *.log
	rm -fv derivatives
	rm -fv variance
	rm -fv eigv.rpt
	rm -fv make.out

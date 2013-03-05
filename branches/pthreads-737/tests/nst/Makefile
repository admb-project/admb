# make some special targets
.PHONY: all rules

ifeq ($(HOSTNAME),katsuo)
  export ADMB_HOME=/home/davef/admb-threaded/build/admb-linux-gcc4.8.0-64bit
endif
ifeq ($(HOSTNAME),kihikihi)
  export ADMB_HOME=/home/jsibert/admb/pthreads-737/build/admb-linux-gcc4.7.2-64bit
endif
CC = g++
LL = g++
#${CXX}  -pthread -ggdb -Wall -fpermissive -DUSE_PTHREADS -DUSE_LAPLACE -Dlinux 
CFLAGS = -pthread -ggdb -Wall -fpermissive -DUSE_PTHREADS -DUSE_LAPLACE -Dlinux -c -I. -I$(ADMB_HOME)/include -I$(ADMB_HOME)/contrib
#CFLAGS = -c -pthread -fpermissive -m64 -Wall -Wno-deprecated -ggdb -I. -I$(ADMB_HOME)/include -I$(ADMB_HOME)/contrib -D__GNUDOS__ -Dlinux -DUSE_PTHREADS -DUSE_LAPLACE -DSAFE_ARRAYS

#LFLAGS = -L$(ADMB_HOME)/lib -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -lpthread
LFLAGS = -L${ADMB_HOME}/lib -L/usr/lib -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s -lpthread

# generates multiple definition linker errors
#OBJECTS=adpthread_manager.o admb_thread.o nst.o
OBJECTS=thread_stuff.o admb_thread.o nst.o

# link the object file into the executable 
nst: $(OBJECTS) 
	@echo
	@echo ------- Link $@
	$(LL) -o $@ $^ $(LFLAGS)
	@echo ------- Done

admb_thread.o: admb_thread.cpp nst.tpl nst.htp
	@echo
	@echo ------- Compile $<
	sed -i '/class model_data : public ad_comm{/a\
          public:' nst.htp
	sed -i '{s/^private/public/}' nst.htp
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
	@echo ------- Done

%.htp:%.tpl;
	@echo
	@echo ------- Making $@
	@echo ------- Translate $<
	$(ADMB_HOME)/bin/tpl2cpp $*

# make Dave's new_sim_thread3
new_sim_thread3:
	$(CC) -pthread -ggdb -Wall -fpermissive -DUSE_PTHREADS -DUSE_LAPLACE -Dlinux \
  -D__GNUDOS__ -o new_sim_thread3 new_sim_thread3.cpp  \
   -I${ADMB_HOME}/include -I. -I/usr/include \
  -L${ADMB_HOME}/lib -L/usr/lib \
  -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s \
  -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s

all: nst new_sim_thread3

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
	rm -fv nst.cpp
	rm -fv nst
	rm -fv *.o
	rm -fv *.htp
	rm -fv *.log
	rm -fv derivatives
	rm -fv variance
	rm -fv eigv.rpt
	rm -fv make.out
	rm -fv zzz-nst
	rm -fv new_sim_thread3
	rm -fv *tmp*

#ADMB_HOME=~/admodel
ADMB_HOME=/home/jsibert/admb/Dave-pthread/admb-apr26-13/build/dists/admb_gcc411_fedora8

#CC= my_gcc
CC=/usr/local/gcc-4.8.0/bin/g++
.SUFFIXES: .cpp .o
.SUFFIXES: .cpp .o

.cpp.o : 
	 $(CC) -ggdb3 -O0 -w -femit-class-debug-always   -pthread -o$*.o  -fpermissive  -c   \
     -DTHREAD_SAFE -Dlinux -DUSE_LAPLACE -DUSE_ADMBTHREAD -DUSE_PTHREADS -D__GNUDOS__ -I. \
     -I/home/dave/admb11-united/build/admb-linux-gccdbg/include \
     -I${ADMB_HOME}/include \
     -I/usr/local/include  $<

#		*List Macros*
EXE_dependencies =  \
 ythread_stuff.o \
 xthread_stuff.o \
 thread_stuff.o \
 thread_stuff2.o \
 thread_stuff3.o \
 thread_stuff4.o \
 thread_stuff5.o \
 thread_stuff6.o \
 thread_stuff7.o \
 thread_stuff8.o \
 newertpl.o 


#		*Explicit Rules*
#mfcl: $(EXE_dependencies) tploop.cpp
newertol: $(EXE_dependencies)
	$(CC) -ggdb3  -v -pthread  *.o -o newertpl  \
  -L${ADMB_HOME}/lib \
  -L/home/dave/admb11-united/build/admb-linux-gccdbg/lib \
  -L/usr/lib \
  -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s \
  -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s \
  -ladt -lads -lstdc++ 

newertpl.cpp: newertpl.tpl
	tpl2cpp newertpl

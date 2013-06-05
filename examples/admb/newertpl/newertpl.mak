ADMB_HOME=~/admodel

CC= my_gcc
.SUFFIXES: .cpp .l64
.SUFFIXES: .cpp .l64

.cpp.l64 : 
	 $(CC) -ggdb3 -O0 -w -femit-class-debug-always   -pthread -o$*.l64  -fpermissive  -c   \
     -DTHREAD_SAFE -Dlinux -DUSE_LAPLACE -DUSE_ADMBTHREAD -DUSE_PTHREADS -D__GNUDOS__ -I. \
     -I/home/dave/admb11-united/build/admb-linux-gccdbg/include \
     -I/usr/local/include  $<

#		*List Macros*
EXE_dependencies =  \
 ythread_stuff.l64 \
 xthread_stuff.l64 \
 thread_stuff.l64 \
 thread_stuff2.l64 \
 thread_stuff3.l64 \
 thread_stuff4.l64 \
 thread_stuff5.l64 \
 thread_stuff6.l64 \
 thread_stuff7.l64 \
 thread_stuff8.l64 \
 newertpl.l64 


#		*Explicit Rules*
mfcl: $(EXE_dependencies) tploop.cpp
	$(CC) -ggdb3  -v -pthread  *.l64 -o newertpl  \
  -L${ADMB_HOME}/lib \
  -L/home/dave/admb11-united/build/admb-linux-gccdbg/lib \
  -L/usr/lib \
  -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s \
  -ladt -lads -ladmod -ldf1b2s -ladt -lads -ladmod -ldf1b2s \
  -ladt -lads -lstdc++ 

newertpl.cpp: newertpl.tpl
	tpl2cpp newertpl

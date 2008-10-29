#macros for making optimized library for DJGPP
CC = gcc
LL = tlib

FLAGS = -Dlinux -fpermissive -x c++ -O3 -c -I. -I../nh99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = cyg-gcc295o
LIBNAME = libado.a
LIBDIR = lib
INCLDIR= include
DISKDIR= f:/gcc2953-cygwin
BINDIR= bin
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp *.h $(DISKDIR)/$(INCLDIR)
	cp *.hpp $(DISKDIR)/$(INCLDIR)


#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3
$(LIBPATH)/$(LIBNAME) :  $(OBJ0)  $(OBJ1)  $(OBJ2)  $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)


$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

all: disk $(LIBPATH)/$(LIBNAME) 


disk: 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)  ; \
	cp adpvm2.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx001.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx001a.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx002.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx003.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx004.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx005.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx005a.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx006.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx007.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx008.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx009.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx010.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx011.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx012.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx013.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx014.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx015.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx016.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx017.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx018.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp fvar.hpp $(DISKDIR)/$(INCLUDEDIR) ; \
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR) ; \

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

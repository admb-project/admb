#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS = -x c++ -O2 -c -I. -I../linad99 -I../tools99 -I../nh99 -D __ADSGI__ -D __GNUDOS__ -D OPT_LIB
#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.o -D __GNUDOS__ -D OPT_LIB
LIBPATH = gcco
LIBNAME = libado.a
LIBDIR = lib
INCLDIR= include
DISKDIR= d:\gccdisk
vpath %.o $(LIBPATH)$

.SUFFIXES: .o .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

disk: $(LIBPATH)/$(LIBNAME) 
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR)
	copy insx001.h $(DISKDIR)\$(INCLDIR)
	copy insx001a.h $(DISKDIR)\$(INCLDIR)
	copy insx002.h $(DISKDIR)\$(INCLDIR)
	copy insx003.h $(DISKDIR)\$(INCLDIR)
	copy insx004.h $(DISKDIR)\$(INCLDIR)
	copy insx005.h $(DISKDIR)\$(INCLDIR)
	copy insx005a.h $(DISKDIR)\$(INCLDIR)
	copy insx006.h $(DISKDIR)\$(INCLDIR)
	copy insx007.h $(DISKDIR)\$(INCLDIR)
	copy insx008.h $(DISKDIR)\$(INCLDIR)
	copy insx009.h $(DISKDIR)\$(INCLDIR)
	copy insx010.h $(DISKDIR)\$(INCLDIR)
	copy insx011.h $(DISKDIR)\$(INCLDIR)
	copy insx012.h $(DISKDIR)\$(INCLDIR)
	copy insx013.h $(DISKDIR)\$(INCLDIR)
	copy insx014.h $(DISKDIR)\$(INCLDIR)
	copy insx015.h $(DISKDIR)\$(INCLDIR)
	copy insx016.h $(DISKDIR)\$(INCLDIR)
	copy insx017.h $(DISKDIR)\$(INCLDIR)
	copy insx018.h $(DISKDIR)\$(INCLDIR)
	copy fvar.hpp $(DISKDIR)\$(INCLDIR)
	copy trunc.hpp $(DISKDIR)\$(INCLDIR)
	
#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.o

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)

$(OBJ0): %.o: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)

$(OBJ1): %.o: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)

$(OBJ2): %.o: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)

$(OBJ3): %.o: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)


all: $(LIBPATH)/$(LIBNAME) 




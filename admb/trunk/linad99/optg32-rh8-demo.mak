


#macros for making optimized library for DJGPP
CC = gcc
SHELL=sh
LL = tlib
FLAGS = ${OPTIONS} -DOPT_LIB -DAD_DEMO -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../tools99  
LIBPATH =gcc32-rh8o
FLAGS1 = -g -DOPT_LIB -DAD_DEMO -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../tools99  
LIBPATH =gcc32-rh8o-demo
LIBNAME = libado.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /g/g32-rh8-demo
DRIVECHANGE=fff.bat
SRCDIR =  src
.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$


.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj

fvar1.obj: fvar1.cpp
	$(CC) $(FLAGS1) $<
	mv $*.o $(LIBPATH)/$*.obj


all: $(LIBPATH)/$(LIBNAME)  disk


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp fvar.hpp $(DISKDIR)/$(INCLDIR)
	cp adpvm2.h $(DISKDIR)/$(INCLDIR)
	cp trunc.hpp $(DISKDIR)/$(INCLDIR)

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.o  rm *.a

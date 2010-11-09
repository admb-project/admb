

#macros for making optimized library for DJGPP

CC = /usr/bin/gcc-3.2.2/bin/gcc
LL = tlib
FLAGS = -g -fpermissive -O -c -I. -I../linad99 -I../tools99 -D__SPDLL__\
 -D__GNUDOS__ -Dlinux -DOPT_LIB
LIBPATH =gcc32-vg-rh8lp
LIBNAME = libadt.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /g/g32-rh8
SRCDIR =  src
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

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


all: $(LIBPATH)/$(LIBNAME)  disk


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp adoption.hpp $(DISKDIR)/$(INCLDIR)
	cp adstring.hpp $(DISKDIR)/$(INCLDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLDIR)
	cp clist.h $(DISKDIR)/$(INCLDIR)

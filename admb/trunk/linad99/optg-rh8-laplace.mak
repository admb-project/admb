
#macros for making optimized library for DJGPP
CC = gcc
SHELL=sh
LL = tlib

FLAGS =  ${OPTIONS} -I/usr/src/ATLAS/include -DOPT_LIB -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../tools99 -D__SPDLL__ 
FLAGS1 = ${OPTIONS} -I/usr/src/ATLAS/include -g -DOPT_LIB -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../tools99 -D__SPDLL__ 
LIBPATH =gcc32-rh8olp
LIBNAME = libado.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /g/g32-rh8-laplace
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
	cp trunc.hpp $(DISKDIR)/$(INCLDIR)

clean:
	cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

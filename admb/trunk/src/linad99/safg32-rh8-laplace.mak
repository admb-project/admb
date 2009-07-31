
CC = gcc
SHELL=sh
LL = tlib
FLAGS =  ${OPTIONS} -I/usr/src/ATLAS/include ${PVMOPTION} -w -DUSE_LAPLACE -DSAFE_ALL -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../tools99 -I../df1b2-separable

LIBPATH =gcc32-rh8o
FLAGS1 = ${OPTIONS} -I/usr/src/ATLAS/include ${PVMOPTION} -g -DUSE_LAPLACE -DSAFE_ALL -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../tools99 -I../df1b2-separable
LIBPATH =gcc32-rh8slp
LIBNAME = libads.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /g/g32-rh8-laplace
DISKDIR1= \g295dsk
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

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

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
	cp fvar.hpp $(DISKDIR)/$(INCLDIR)
	cp trunc.hpp $(DISKDIR)/$(INCLDIR)
clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.o ; rm *.a


#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS1 = -g -Dlinux -DUSE_LAPLACE -fpermissive -O3 -c -I. -I../linad99 -I../tools99  \
  -D __GNUDOS__ -D OPT_LIB
FLAGS = -Dlinux -fpermissive -DUSE_LAPLACE -O3 -c -I. -I../linad99 -I../tools99  \
  -D __GNUDOS__ -D OPT_LIB
LIBPATH =gcc296-rh73olp
LIBNAME = libadt.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /g/g296-rh73-laplace
DISKDIR1= \g295dsk
DRIVECHANGE=fff.bat
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

cifstrem.obj: cifstrem.cpp
	$(CC) $(FLAGS1) $<
	mv $*.o $(LIBPATH)/$*.obj

all: $(LIBPATH)/$(LIBNAME)  disk


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp adoption.hpp $(DISKDIR)/$(INCLDIR)
	cp adstring.hpp $(DISKDIR)/$(INCLDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLDIR)
	cp clist.h $(DISKDIR)/$(INCLDIR)

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

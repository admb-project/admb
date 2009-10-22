
#macros for making optimized library for DJGPP
CC = gcc
SHELL=sh
LL = tlib

#FLAGS = -fdiagnostics-show-option ${OPTIONS} -fno-for-scope -Wall -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -DOPT_LIB -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../df1b2-separable -I../tools99
FLAGS = ${OPTIONS} -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -DOPT_LIB -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../df1b2-separable -I../tools99

#FLAGS1 = -fdiagnostics-show-option ${OPTIONS} -w ${PVMOPTION} -DUSE_LAPLACE -DOPT_LIB -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../df1b2-separable -I../tools99
FLAGS1 = ${OPTIONS} -w ${PVMOPTION} -DUSE_LAPLACE -DOPT_LIB -D__GNUDOS__ -Dlinux -fpermissive -O3 -c -I. -I../nh99 -I../df1b2-separable -I../tools99

LIBPATH =gcc32-rh8olp
LIBNAME = libado.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /g/g32-rh8-laplace
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

dvec_io1.obj ddlist.obj gradchk.obj ivect11.obj model49.obj multiindex.obj gradstrc.obj dvect26.obj derch.obj dvsort.obj fvar_fn2.obj lvector.obj ivect6.obj dmat42.obj imat10.obj dfsdmat.obj sgradclc.obj newfmin.obj makesub.obj: %.obj: %.cpp
	$(CC) $(FLAGS1)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS1) -o $(LIBPATH)/$(@F) $<

$(filter-out ddlist.obj gradchk.obj ivect11.obj model49.obj multiindex.obj gradstrc.obj dvect26.obj ivect11.obj lvector.obj ivect6.obj dmat42.obj dfsdmat.obj, $(OBJ0)): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(filter-out dvec_io1.obj, $(OBJ1)): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(filter-out derch.obj dvsort.obj fvar_fn2.obj imat10.obj sgradclc.obj newfmin.obj, $(OBJ2)): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj

$(filter-out makesub.obj, $(OBJ3)): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj

all: $(LIBPATH)/$(LIBNAME)  disk


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp fvar.hpp $(DISKDIR)/$(INCLDIR)
	cp dfpool.h $(DISKDIR)/$(INCLDIR)
	cp trunc.hpp $(DISKDIR)/$(INCLDIR)

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.o  rm *.a

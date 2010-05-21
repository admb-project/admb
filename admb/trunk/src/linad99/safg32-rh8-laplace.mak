CC = gcc
SHELL=sh
LL = tlib

CFLAGS=-O3
ifdef DEBUG
CFLAGS=-g
endif

FLAGS = $(CFLAGS) ${OPTIONS} -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -DSAFE_ALL -D__GNUDOS__ -Dlinux -fpermissive -c -I. -I../nh99 -I../tools99 -I../df1b2-separable

FLAGS1 = $(CFLAGS) ${OPTIONS} -w ${PVMOPTION} -g -DUSE_LAPLACE -DSAFE_ALL -D__GNUDOS__ -Dlinux -fpermissive -c -I. -I../nh99 -I../tools99 -I../df1b2-separable

LIBNAME = libads.a
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
	$(CC) $(FLAGS1) $< -o $(LIBPATH)/$*.obj

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS1) -o $(LIBPATH)/$(@F) $<

$(filter-out ddlist.obj gradchk.obj ivect11.obj model49.obj multiindex.obj gradstrc.obj dvect26.obj lvector.obj ivect6.obj dmat42.obj dfsdmat.obj, $(OBJ0)): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

$(filter-out dvec_io1.obj, $(OBJ1)): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

$(filter-out fvar_fn2.obj derch.obj dvsort.obj imat10.obj sgradclc.obj newfmin.obj, $(OBJ2)): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

$(filter-out makesub.obj, $(OBJ3)): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

all: $(LIBPATH)/$(LIBNAME)  disk


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp fvar.hpp $(DISKDIR)/include
	cp trunc.hpp $(DISKDIR)/include
clean:
	rm -rvf $(LIBPATH)

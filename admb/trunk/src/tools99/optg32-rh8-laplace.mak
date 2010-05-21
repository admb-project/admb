CC = gcc
LL = tlib

CFLAGS=-O3
ifdef DEBUG
CFLAGS=-g
endif

FLAGS = $(CFLAGS) -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-format -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -fpermissive -c -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -Dlinux -DOPT_LIB

#FLAGS = -fdiagnostics-show-option -fno-for-scope -Wall -Wno-format -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -fpermissive -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -Dlinux -DOPT_LIB

FLAGS1 = $(CFLAGS) -w ${PVMOPTION} -DUSE_LAPLACE -fpermissive -c -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -Dlinux -DOPT_LIB

LIBPATH =gcc32-rh8olp
LIBNAME = libadt.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

$(filter-out cifstrem.obj, $(OBJ0)): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

cifstrem.obj: %.obj: %.cpp
	$(CC) $(FLAGS1) $< -o $(LIBPATH)/$*.obj

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj


all: $(LIBPATH)/$(LIBNAME)  disk


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp adoption.hpp $(DISKDIR)/include
	cp adstring.hpp $(DISKDIR)/include
	cp cifstrem.h $(DISKDIR)/include
	cp clist.h $(DISKDIR)/include

clean:
	rm -rvf $(LIBPATH)

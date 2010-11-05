CC = gcc
LL = tlib

CFLAGS=-O3
ifdef DEBUG
CFLAGS=-g
endif

FLAGS = $(CFLAGS) -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-format -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -fpermissive -c -I. -I..\linad99 -I..\tools99 -D__SPDLL__ -D__GNUDOS__ -Dlinux -DOPT_LIB

FLAGS1 = $(CFLAGS) -w ${PVMOPTION} -DUSE_LAPLACE -fpermissive -c -I. -I..\linad99 -I..\tools99 -D__SPDLL__ -D__GNUDOS__ -Dlinux -DOPT_LIB

LIBPATH =gcc32-rh8olp
LIBNAME = libadt.a
SRCDIR =  src
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: disk
include objects.lst

$(LIBPATH)\$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	cmd /C "cd $(LIBPATH)& ar -rs $(LIBNAME) *.obj"

$(filter-out cifstrem.obj, $(OBJ0)): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)\$*.obj

cifstrem.obj: %.obj: %.cpp
	$(CC) $(FLAGS1) $< -o $(LIBPATH)\$*.obj

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)\$*.obj

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)\$*.obj

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)\$*.obj


all: $(LIBPATH)\$(LIBNAME)  disk


disk: $(LIBPATH)\$(LIBNAME) 
	cmd /C "copy $(LIBPATH)\\$(LIBNAME) $(DISKDIR)\lib"
	cmd /C "copy adoption.hpp $(DISKDIR)\include"
	cmd /C "copy adstring.hpp $(DISKDIR)\include"
	cmd /C "copy cifstrem.h $(DISKDIR)\include"
	cmd /C "copy clist.h $(DISKDIR)\include"

clean:
	if exist $(LIBPATH) rmdir /S /Q $(LIBPATH)

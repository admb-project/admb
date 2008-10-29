#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS = -w -x c++ -O3 -c -I. -I../linad99 -I../tools99 -D __SPDLL__ \
  -D __GNUDOS__ -D OPT_LIB
LIBPATH =egcso
LIBNAME = libadt.a
LIBDIR = lib
INCLDIR= include
DISKDIR= g:\egcsdisk
DISKDIR1= \egcsdisk
DRIVECHANGE=ggg.bat
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
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR)
	copy insx018.h $(DISKDIR)\$(INCLDIR)
	copy adoption.hpp $(DISKDIR)\$(INCLDIR)
	copy adstring.hpp $(DISKDIR)\$(INCLDIR)
	copy cifstrem.h $(DISKDIR)\$(INCLDIR)
	copy clist.h $(DISKDIR)\$(INCLDIR)
	$(DRIVECHANGE) 
	cd $(DISKDIR1) 
	del ad_build.exe 
	del ad_build.zip 
	pkzip -r -p ad_build 
	zip2exe ad_build 
	del ad_build.zip

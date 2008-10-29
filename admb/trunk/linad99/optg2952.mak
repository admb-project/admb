#macros for making optimized library for DJGPP
CC = gcc
SHELL=sh
LL = tlib
FLAGS1 = -fpermissive -g -O3 -c -I. -I../nh99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB 
FLAGS = -fpermissive -O3 -c -I. -I../nh99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB 
LIBPATH =gcc2952o
LIBNAME = libado.a
LIBDIR = lib
INCLDIR= include
DISKDIR= f:\g295dsk
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
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR)
	copy insx001.h $(DISKDIR)\$(INCLDIR)
	copy insx001a.h $(DISKDIR)\$(INCLDIR)
	copy insx002.h $(DISKDIR)\$(INCLDIR)
	copy insx003.h $(DISKDIR)\$(INCLDIR)
	copy insx004.h $(DISKDIR)\$(INCLDIR)
	copy insx005.h $(DISKDIR)\$(INCLDIR)
	copy insx005a.h $(DISKDIR)\$(INCLDIR)
	copy insx006.h $(DISKDIR)\$(INCLDIR)
	copy insx007.h $(DISKDIR)\$(INCLDIR)
	copy insx008.h $(DISKDIR)\$(INCLDIR)
	copy insx009.h $(DISKDIR)\$(INCLDIR)
	copy insx010.h $(DISKDIR)\$(INCLDIR)
	copy insx011.h $(DISKDIR)\$(INCLDIR)
	copy insx012.h $(DISKDIR)\$(INCLDIR)
	copy insx013.h $(DISKDIR)\$(INCLDIR)
	copy insx014.h $(DISKDIR)\$(INCLDIR)
	copy insx015.h $(DISKDIR)\$(INCLDIR)
	copy insx016.h $(DISKDIR)\$(INCLDIR)
	copy insx017.h $(DISKDIR)\$(INCLDIR)
	copy insx018.h $(DISKDIR)\$(INCLDIR)
	copy fvar.hpp $(DISKDIR)\$(INCLDIR)
	copy trunc.hpp $(DISKDIR)\$(INCLDIR)
	$(DRIVECHANGE) 
	cd $(DISKDIR1) 
	del ad_build.exe 
	del ad_build.zip 
	pkzip -r -p ad_build 
	zip2exe ad_build 
	del ad_build.zip

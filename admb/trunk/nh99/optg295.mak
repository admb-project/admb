
#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
#FLAGS = -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB 
FLAGS = -fpermissive -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB 
LIBPATH =gcc295o
LIBNAME = libadmod.a
LIBDIR = lib
INCLDIR= include
DISKDIR= f:\g295dsk
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
	copy admodel.h $(DISKDIR)\$(INCLDIR)
	copy spcomm.h $(DISKDIR)\$(INCLDIR)
	copy adsplus.h $(DISKDIR)\$(INCLDIR)
	copy newredef.h $(DISKDIR)\$(INCLDIR)
	copy s.h $(DISKDIR)\$(INCLDIR)
	$(DRIVECHANGE) 
	cd $(DISKDIR1)
	del ad_build.exe 
	del ad_build.zip 
	pkzip -r -p ad_build 
	zip2exe ad_build 
	del ad_build.zip

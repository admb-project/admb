#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc5s
FLAGS = /c -I. -D__MSVC32__ -DSAFE_ALL /O2 -I../tools99 -Ig:/msvc50/include 
LIBNAME = ads32.lib 
LIBRARIAN = tlib
DRIVECHANGE=fff.bat
DISKDIR= f:\adms5.m32
DISKDIR1= \adms5.m32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo /OUT:$(LIBNAME)  > $(LIBPATH)\t.rsp
	cd $(LIBPATH) 
	ls *.obj >> t.rsp
	lib @t.rsp
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 
	copy gccmanip.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx001.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx001a.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx002.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx003.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx004.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx005.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx005a.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx006.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx007.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx008.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx009.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx010.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx011.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx012.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx013.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx014.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx015.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx016.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx017.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx018.h $(DISKDIR)\$(INCLUDEDIR)
	copy fvar.hpp $(DISKDIR)\$(INCLUDEDIR)
	copy d4arr.hpp $(DISKDIR)\$(INCLUDEDIR)
	cd $(DISKDIR1)
	del mscdisk.exe
	del mscdisk.zip
	pkzip -r -p mscdisk
	zip2exe mscdisk
	del mscdisk.zip




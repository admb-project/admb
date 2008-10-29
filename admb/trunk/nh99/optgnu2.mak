

#macros for making optimized library for BORLAND 4.0
CC = gcc
FLAGS = -x c++ -O3 -c -D __GNUDOS__ -D SAFE_ALL 
LIBPATH = gccs
LIBNAME = libads.a 
vpath %.obj $(LIBPATH)$

LIBPATH = gccs
LIBNAME = libads.a 
LIBRARIAN = ar
DISKDIR= e:\admdisk.gnu
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo $(LIBPATH)/$(LIBNAME)  > $(LIBPATH)\t.rsp
	ls $(LIBPATH)/*.obj >> $(LIBPATH)\t.rsp
	sed -f libcmd $(LIBPATH)/t.rsp > tmp
	cp tmp $(LIBPATH)/t.rsp 
	cd $(LIBPATH) 
	ar -rs $(LIBNAME)  *.obj
	cd ..
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 

$(OBJ0): %.obj: %.cpp
	$(CC) -o gccs/$*.obj $(FLAGS) $<

$(OBJ1): %.obj: %.cpp
	$(CC) -o gccs/$*.obj $(FLAGS) $<

$(OBJ2): %.obj: %.cpp
	$(CC) -o gccs/$*.obj $(FLAGS) $<

$(OBJ3): %.obj: %.cpp
	$(CC) -o gccs/$*.obj $(FLAGS) $<

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
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

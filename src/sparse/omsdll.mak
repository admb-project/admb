#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc5o
FLAGS = /W3 /c /MD /I. -D__SPDLL__ -D__MSVC32__ -DOPT_LIB /O2 
LIBNAME = adt32.lib 
LIBRARIAN = tlib
DISKDIR= g:\admsdll5.m32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) :  fvar.hpp $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
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
fvar.hpp:

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	copy clist.h $(DISKDIR)\$(INCLUDEDIR)
	copy cifstrem.h $(DISKDIR)\$(INCLUDEDIR)
	copy adstring.hpp $(DISKDIR)\$(INCLUDEDIR)
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 





#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc32do
FLAGS = /MD /c /I. -D__MSVC32__ -D__SPDLL__ -DOPT_LIB /O2 
#FLAGS = /MD /c /I. -D__MSVC32__ -DOPT_LIB /O2 
LIBNAME = admod32.lib 
LIBRARIAN = tlib
DISKDIR= i:\admdll.m32
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
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 

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
	copy admodel.h $(DISKDIR)\$(INCLUDEDIR)
	copy s.h $(DISKDIR)\$(INCLUDEDIR)
	copy newredef.h $(DISKDIR)\$(INCLUDEDIR)

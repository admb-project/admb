
#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc5o
FLAGS = /MD /c /W3 /I. -D__SPDLL__ -D__MSVC32__ -DOPT_LIB /O2 
LIBNAME = admod32.lib 
LIBRARIAN = tlib
DISKDIR= g:\admsdll5.m32
SRCDIR =  src
LIBDIR =  lib
BINDIR =  bin
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) :  fvar.hpp $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 
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

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       
fvar.hpp:

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	copy admodel.h $(DISKDIR)\$(INCLUDEDIR)
	copy adsplus.h $(DISKDIR)\$(INCLUDEDIR)
	copy spcomm.h $(DISKDIR)\$(INCLUDEDIR)
	copy s.h $(DISKDIR)\$(INCLUDEDIR)
	copy newredef.h $(DISKDIR)\$(INCLUDEDIR)
	$(CC) mylex.c
	copy mylex.exe $(DISKDIR)\$(BINDIR)\tpl2cpp.exe
	$(CC) dlllex.c
	copy dlllex.exe $(DISKDIR)\$(BINDIR)\tpl2dll.exe
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 


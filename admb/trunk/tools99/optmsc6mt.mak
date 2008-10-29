#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc6mto
FLAGS = /MT /W3 /c  /I. -D__MSVC32__ -DOPT_LIB /O2 /I../linad99 /I../tools99
LIBNAME = adt32.lib 
LIBRARIAN = tlib
DISKDIR= f:/adms6mt.m32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) :  fvar.hpp $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	rm $(LIBPATH)/t.rsp ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH) ; \
	ls *.obj >> t.rsp ; \
	lib @t.rsp ; \
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
	cp clist.h $(DISKDIR)/$(INCLUDEDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLUDEDIR)
	cp adstring.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 



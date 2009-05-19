
#macros for making optimized library for MS         
CC = f:/intelcpp/ia32/bin/icl
LL = tlib
LIBPATH = intel7-vc71o

ifdef demo
FLAGS =  -DAD_DEMO /Qvc7.1 /G6 /W3 /c  /I. -D__MSVC32__=7 -DOPT_LIB /O2 /I../linad99 /I../tools99 /Ig:/vc7/include /Ig:/vc7/platformsdk/include
else
FLAGS =  /Qvc7.1 /G6 /W3 /c  /I. -D__MSVC32__=7 -DOPT_LIB /O2 /I../linad99 /I../tools99 /Ig:/vc7/include /Ig:/vc7/platformsdk/include
endif

LIBNAME = adt32.lib 
LIBRARIAN = tlib

ifdef demo
DISKDIR= f:/intel7-vc71-demo
else
DISKDIR= f:/intel7-vc71
endif


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

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

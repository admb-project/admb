
#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = -Vd -Ox -5 -H -Hc -DDOS386;OPT_LIB -I.;../linad99 -c -f
#FLAGS = -Ox -5 -H -Hc -DDOS386;OPT_LIB -I.;../linad99 -c -f
LIBPATH = b32po54
LIBNAME = adt32.lib 
LIBRARIAN = tlib
DISKDIR= g:\admbbor.54
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	cd $(LIBPATH) 
	echo $(LIBNAME)  > t.rsp
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmp
	cp tmp $(LIBPATH)/t.rsp 
	cd $(LIBPATH) 
	tlib @t.rsp
	cd ..
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<


disk: 
	copy adstring.hpp $(DISKDIR)\$(INCLUDEDIR)
	copy cifstrem.h $(DISKDIR)\$(INCLUDEDIR)
	copy clist.h $(DISKDIR)\$(INCLUDEDIR)
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 

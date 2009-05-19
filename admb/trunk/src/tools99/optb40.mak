#macros for making optimized library for BORLAND 4.0

CC = d:\bc4\bin\bcc32

LL = tlib

FLAGS = -O2 -H -Hc -DDOS386;OPT_LIB -I.;d:\bc4\include;e:\tools94;h:\h94 -3 -c -f

LIBPATH = b32o40

LIBNAME = adt32.lib 

LIBRARIAN = tlib

DISKDIR= e:\admdisk.b32

SRCDIR =  src

LIBDIR =  lib

INCLUDEDIR = include 



.SUFFIXES: .obj .cpp

vpath %.obj $(LIBPATH)$



include objects.lst



$(LIBPATH)/$(LIBNAME) :  $(OBJ0)  

	echo $(LIBPATH)/$(LIBNAME)  > $(LIBPATH)\t.rsp

	ls $(LIBPATH)/*.obj >> $(LIBPATH)\t.rsp

	sed -f libcmd $(LIBPATH)/t.rsp > tmp

	cp tmp $(LIBPATH)/t.rsp 

	cd $(LIBPATH) 

	tlib @t.rsp

	cd ..

	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 

	copy cifstrem.h $(DISKDIR)\$(INCLUDEDIR) 

	copy clist.h $(DISKDIR)\$(INCLUDEDIR) 

	copy adstring.hpp $(DISKDIR)\$(INCLUDEDIR) 



$(OBJ0): %.obj: %.cpp

	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<




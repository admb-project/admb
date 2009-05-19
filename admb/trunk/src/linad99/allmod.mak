#macros for making 32 bit library for BORLAND 4.0

CC = bcc32

LL = tlib

FLAGS = -O2 -H -Hc -DDOS386;OPT_LIB -I.;d:\bc4\include;e:\tools94;e:\hl94prof -3 -c -f

LIBPATH = b32o

LIBNAME = ad32o.lib 

LIBRARIAN = tlib



.SUFFIXES: .obj .cpp

vpath %.obj $(LIBPATH)$

vpath %.obj .



include objects.lst



$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 

	echo $(LIBPATH)/$(LIBNAME) > $(LIBPATH)\t.rsp

	ls $(LIBPATH)/*.obj >> $(LIBPATH)\t.rsp

	sed -f libcmd $(LIBPATH)/t.rsp > tmp

	cp tmp $(LIBPATH)/t.rsp 

	cd $(LIBPATH) 

	$(LL) @t.rsp

	cd ..



$(OBJ0): %.obj: %.cpp

	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<


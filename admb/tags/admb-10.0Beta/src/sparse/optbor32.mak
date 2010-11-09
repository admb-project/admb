#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = ${OPTIONS} -Vd -Ox -5 -H -Hc -DDOS386 -DOPT_LIB -I. -I../linad99 -c -f
LIBPATH = b32po
LIBNAME = adt32.lib 
LIBRARIAN = tlib
DISKDIR= j:/admbbor.50
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; \
	del *.lib ; \
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; \
	tlib /P1024 @t.rsp
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<


disk: 
	cp adstring.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLUDEDIR)
	cp clist.h $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

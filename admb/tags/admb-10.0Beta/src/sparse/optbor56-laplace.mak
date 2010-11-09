#macros for making optimized library for BORLAND 4.0
CC = f:/bc56/bin/bcc32
LL = tlib
FLAGS = -vG -Vd -O2 -DUSE_LAPLACE -6 -H -Hc -DDOS386 -DOPT_LIB -I. -I../linad99 -c 
#FLAGS = -Ox -5 -H -Hc -DDOS386;OPT_LIB -I.;../linad99 -c -f
LIBPATH = b32po56lp
LIBNAME = adt32.lib 
LIBRARIAN = tlib
DISKDIR= f:/borland-56-laplace
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJSPLUS)
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; \
	rm *.lib ; \
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; \
	tlib /P256 @t.rsp 
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

disk: 
	cp adstring.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLUDEDIR)
	cp clist.h $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
clean:
	- cd $(LIBPATH);  rm *obj; rm *lib

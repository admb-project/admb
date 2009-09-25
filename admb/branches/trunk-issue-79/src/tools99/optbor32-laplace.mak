
#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = -q -w -I\\Borland\\BCC55\\Include ${OPTIONS} -O2 -DUSE_LAPLACE -6 -DDOS386 -DOPT_LIB -I. -I../linad99 -c -f
LIBPATH = b32polp
LIBNAME = adt32.lib 
LIBRARIAN = tlib
DISKDIR= f:/borland-50-laplace
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
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; \
	tlib /P256 @t.rsp 
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -w-8071 -w-8004 -w-8057 -w-8060 -o$(LIBPATH)/$* $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

disk: 
	cp adstring.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLUDEDIR)
	cp clist.h $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
clean:
	-rm -f bor502-win32olp/*
	-rm -f bor502-win32slp/*
	-rm -f tmpfile

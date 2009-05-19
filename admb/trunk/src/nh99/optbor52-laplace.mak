
#macros for making optimized library for BORLAND 4.0
#CC = bcc32i
CC = bcc32
LL = tlib
FLAGS = -DUSE_LAPLACE -Vd -O2 -DOPT_LIB -I../linad99 -I../df1b2-separable -DDOS386 -I. -6 -c -f
LIBPATH = b32po52lp
STUBPATH = b32po52lp-stub
LIBNAME = admod32.lib 
BINDIR=bin
LIBRARIAN = tlib
DISKDIR= f:/borland-52-laplace
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp .dir

vpath %.obj $(LIBPATH)$

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk stub


$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJSPLUS)
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; \
	del *.lib ; \
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
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR)
	bcc32 mylex.c
	cp mylex.exe $(DISKDIR)/$(BINDIR)/tpl2cpp.exe
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR) 

stub: df1b2stub.cpp
	$(CC) $(FLAGS) -o$(STUBPATH)/df1b2stub.obj df1b2stub.cpp
	echo df1b2stub.lib  > $(STUBPATH)/t.rsp
	cd $(STUBPATH) ; \
	rm *.lib ; \
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(STUBPATH)/t.rsp > tmpfile
	cp tmpfile $(STUBPATH)/t.rsp 
	cd $(STUBPATH) ; \
	tlib @t.rsp
	cp $(STUBPATH)/df1b2stub.lib $(DISKDIR)/$(LIBDIR) 

clean:
	- cd $(LIBPATH);  rm *obj; rm *lib

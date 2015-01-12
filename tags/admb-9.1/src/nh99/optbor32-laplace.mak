

#macros for making optimized library for BORLAND 4.0
#CC = bcc32i
CC = bcc32
LL = tlib
FLAGS = -DADMB_VERSION=${ADMB_VERSION} -I\\Borland\\BCC55\\Include ${OPTIONS} -I../df1b2-separable -I../tools99 -I../linad99 -Vd -O2 -H -Hc -DUSE_LAPLACE -DOPT_LIB -DDOS386 -I. -6 -c -f

#FLAGS = -H -Hc -O2 -DOPT_LIB -DDOS386 -I. -6 -c -f
LIBPATH = bor502-win32olp
STUBPATH = bor502-win32olp-stub
LIBNAME = admod32.lib 
BINDIR=bin
LIBRARIAN = tlib
DISKDIR= f:/borland-50-laplace
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
	rm *.lib ; \
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; \
	tlib /P1024 @t.rsp
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

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
	cd ..
disk: stub
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR)
	flex < tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp.c
	bcc32 -I\\Borland\\BCC55\\Include -L\\Borland\\BCC55\\Lib tpl2cpp.c
	cp tpl2cpp.exe $(DISKDIR)/$(BINDIR)/
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
	cp $(STUBPATH)/df1b2stub.lib $(DISKDIR)/$(LIBDIR) 
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR) 

clean:
	rm -f tmpfile
	rm -f tpl2cpp.exe
	rm -f tpl2cpp.tds
	rm -f lex.yy.c
	- cd $(LIBPATH);  rm -f *obj; rm -f *lib; rm -f *.rsp
	- cd $(STUBPATH);  rm -f *obj; rm -f *lib; rm -f *.rsp

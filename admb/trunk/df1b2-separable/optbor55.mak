#macros for making optimized library for BORLAND 4.0
#CC = bcc32i
CC = bcc32
LL = tlib
FLAGS = -DUSE_LAPLACE  -Vd -O2 -H -Hc -DOPT_LIB -DDOS386 -I. -6 -c -f
#FLAGS = -H -Hc -O2 -DOPT_LIB -DDOS386 -I. -5 -c -f
LIBPATH = b32po55
LIBNAME = adf1b2o.lib 
BINDIR=bin
LIBRARIAN = tlib
DISKDIR= j:/binaries/borland-551
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp .dir

vpath %.obj $(LIBPATH)$

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk


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
	cp adpool.h adrndeff.h df1b2fun.h smartbuf.h $(DISKDIR)/$(INCLUDEDIR)
	bcc32 tpl2rem.c
	cp tpl2rem.exe $(DISKDIR)/$(BINDIR)/tpl2rem.exe
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 


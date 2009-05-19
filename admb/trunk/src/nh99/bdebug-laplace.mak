#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
#FLAGS = ${OPTIONS} -v -r- -Vd -Od -DUSE_LAPLACE -I../df1b2-separable -DUSE_ADPVM -DOS386 -5 -c 
FLAGS = ${OPTIONS} -DOPT_LIB -v -r- -Vd -Od -DUSE_LAPLACE -I../df1b2-separable -DUSE_ADPVM -DOS386 -5 -c 
#FLAGS =  -Hc -O2 -DOPT_LIB -DDOS386 -I. -5 -c -f
LIBPATH = b32podlp
LIBNAME = admod32.lib 
BINDIR=bin
STUBPATH = b32podlp-stub
LIBRARIAN = tlib
DISKDIR= c:\admdisk.b32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp .dir

vpath %.obj $(LIBPATH)$

include objects.lst

all: $(LIBPATH)/$(LIBNAME) stub

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJSPLUS)
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; rm *.lib ; ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; tlib /P512 @t.rsp
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib

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
disk: 
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR)


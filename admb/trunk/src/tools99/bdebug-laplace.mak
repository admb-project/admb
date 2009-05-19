#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = ${OPTIONS} -v -r- -Vd -Od -DUSE_LAPLACE -DUSE_ADPVM -Hc -DOS386 -5 -c 
#FLAGS =  -Hc -O2 -DOPT_LIB -DDOS386 -I. -5 -c -f
LIBPATH = b32podlp
LIBNAME = adt32.lib 
BINDIR=bin
LIBRARIAN = tlib
DISKDIR= c:\admdisk.b32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp .dir

vpath %.obj $(LIBPATH)$

include objects.lst

all: $(LIBPATH)/$(LIBNAME) 

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJSPLUS)
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; rm *.lib ; ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; tlib /P256 @t.rsp
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib

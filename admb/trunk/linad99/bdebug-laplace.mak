#macros for making optimized library for BORLAND 4.0
#CC = bcc32i
CC = bcc32
LL = tlib
FLAGS =  ${OPTIONS} -v -DUSE_LAPLACE -DUSE_ADPVM -Od -r- -Vd -H=e:/temp/precomp -Hc -DSAFE_ALL -DWIN32 -I. -I../sparse -5 -c 
LIBPATH = b32podlp
LIBNAME = ado32.lib 
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

$(LIBPATH)/$(LIBNAME) :  $(OBJSPARSE) $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  $(OBJSPLUS)
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; rm *.lib ; ls *.obj >> t.rsp
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; tlib /P1024 @t.rsp
	cd ..

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

$(OBJ4): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib


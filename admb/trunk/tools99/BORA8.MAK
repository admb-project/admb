

#macros for making optimized library for BORLAND 5.0
#CC = bcc32i
CC = bcc32
LL = tlib
#FLAGS = -Vd -O2 -OI -OM -5 -H=Hc -DDOS386;OPT_LIB -I. -c -f
FLAGS = -a8 -Vd -O2 -5 -H=Hc -DDOS386;OPT_LIB -I. -c -f

LIBPATH =b32a8
LIBNAME = ado32.lib
LIBRARIAN = tlib
DISKDIR= c:\admdisk.b32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include OBJECTS.LST

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo $(LIBNAME)  > $(LIBPATH)\t.rsp
	cd $(LIBPATH) 
	ls *.obj >> t.rsp
	cd ..
	c:\bin\sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmp
	cp tmp $(LIBPATH)/t.rsp 
	cd $(LIBPATH) 
	tlib /P32 @t.rsp
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

all: $(LIBPATH)/$(LIBNAME) 




#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = -WX -O2 -H -Hc -DDOS386;OPT_LIB -I.;c:\bc45\include;c:\ntools -3 -c -f
LIBPATH = b45o
LIBNAME = ado32.lib 
LIBRARIAN = tlib
DISKDIR= c:\adm45.b32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo $(LIBPATH)/$(LIBNAME)  > $(LIBPATH)\t.rsp
	ls $(LIBPATH)/*.obj >> $(LIBPATH)\t.rsp
	sed -f libcmd $(LIBPATH)/t.rsp > tmp
	cp tmp $(LIBPATH)/t.rsp 
	tlib @t.rsp
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<

all: $(LIBPATH)/$(LIBNAME) disk


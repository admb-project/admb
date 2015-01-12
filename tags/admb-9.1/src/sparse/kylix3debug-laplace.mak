
#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = -v -r- -Vd -Od -DUSE_LAPLACE -DUSE_ADPVM -Hc -DOS386 -5 -c 
#FLAGS =  -Hc -O2 -DOPT_LIB -DDOS386 -I. -5 -c -f
LIBPATH = b32podlp
LIBNAME = libadt.a 
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
	- cd $(LIBPATH) ; rm *.a 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib

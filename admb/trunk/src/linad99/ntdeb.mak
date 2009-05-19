

#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = -v -H -Hc -DOPT_LIB -DDOS386 -I.;c:/bc45/include;c:/ntools -5 -c -f
LIBPATH = 
LIBNAME = admod32.lib 
LIBRARIAN = tlib
DISKDIR= c:\admdisk.b32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp .dir
vpath %.obj $(LIBPATH)$
vpath %.obj .

include objects.lst

$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<

# this is a kludge to copy the cpp files over to the disk image
#$(OBJ0:.obj=.dir): %.dir: %.cpp
#	cp $< $(DISKDIR)\$(SRCDIR)



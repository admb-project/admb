
#macros for making safe library for DJGPP
CC = gcc
LL = tlib
FLAGS = -g -w -I. -I../nh99 -I../linad99 -fpermissive  -x c++ -O1 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ 
LIBPATH = cyg-gcc32sd
LIBNAME = libadt.a
DISKDIR = /cygdrive/i/cygdisk
INCLDIR = include
LIBDIR = lib

.SUFFIXES: .obj .cpp .CPP
vpath %.obj $(LIBPATH)$
vpath %.cpp /c/tools94

include objects.lst

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLDIR)
	cp clist.h $(DISKDIR)/$(INCLDIR)
	cp adstring.hpp $(DISKDIR)/$(INCLDIR)
	
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj


$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<


all: disk $(LIBPATH)/$(LIBNAME) 

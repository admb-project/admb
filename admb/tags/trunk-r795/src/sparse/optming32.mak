
#macros for making safe library for DJGPP
CC = f:/mingw/bin/gcc
LL = tlib
FLAGS = -I. -I../nh99 -I../linad99 -fpermissive  -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB 
LIBPATH = mingw-gcc32o
LIBNAME = libadt.a
DISKDIR = g:/mingw-g32
INCLDIR = include
LIBDIR = lib

.SUFFIXES: .obj .cpp .CPP
vpath %.obj $(LIBPATH)$

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

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp adoption.hpp $(DISKDIR)/$(INCLDIR)
	cp adstring.hpp $(DISKDIR)/$(INCLDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLDIR)
	cp clist.h $(DISKDIR)/$(INCLDIR)

#macros for making safe library for DJGPP
CC = gcc
LL = tlib
FLAGS = -I. -I../nh99 -I../linad99 -O3 -c -D __GNUDOS__ -D OPT_LIB 
LIBPATH = gcco
LIBNAME = libadt.a
DISKDIR = d:\gccdisk
INCLDIR = include
LIBDIR = lib

.SUFFIXES: .obj .cpp .CPP
vpath %.obj $(LIBPATH)$
vpath %.cpp /c/tools94

include objects.lst

disk: $(LIBPATH)/$(LIBNAME) 
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR)
	copy cifstrem.h $(DISKDIR)\$(INCLDIR)
	copy clist.h $(DISKDIR)\$(INCLDIR)
	copy adstring.hpp $(DISKDIR)\$(INCLDIR)
	
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj


$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<


all: disk $(LIBPATH)/$(LIBNAME) 

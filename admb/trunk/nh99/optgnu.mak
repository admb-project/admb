#macros for making optimized library for DJGPP
CC = gcc
LL = tlib

FLAGS = -O3 -c -I. -I../linad99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = gcco
LIBNAME = libadmod.a
LIBDIR = lib
INCLDIR= include
DISKDIR= d:\gccdisk
BINDIR= bin
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

disk: $(LIBPATH)/$(LIBNAME) tplgcc.exe
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR)
	copy admodel.h $(DISKDIR)\$(INCLDIR)
	copy tplgcc.exe $(DISKDIR)\$(BINDIR)\tpl2cpp.exe

tplgcc.exe : xtmod19
	gcomptpl

#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

all: disk $(LIBPATH)/$(LIBNAME) 

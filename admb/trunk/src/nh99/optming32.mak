
#macros for making optimized library for DJGPP
CC = f:/mingw/bin/gcc
LL = tlib

FLAGS =  -x c++ -O3 -c -I. -I../linad99 -I ../tools99 -fpermissive -D __GNUDOS__ -D OPT_LIB

#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = mingw-gcc32o
LIBNAME = libadmod.a
LIBDIR = lib
INCLDIR= include
DISKDIR= g:/mingw-g32
BINDIR= bin
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
.PHONY: tpl2cpp

include objects.lst

disk: $(LIBPATH)/$(LIBNAME) tpl2cpp
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp admodel.h $(DISKDIR)/$(INCLDIR)
	cp tpl2cpp.exe $(DISKDIR)/$(BINDIR)/tpl2cpp.exe


#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)

tpl2cpp:
	$(CC) -I. -DUX mylex.c -otpl2cpp.exe

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

all: disk $(LIBPATH)/$(LIBNAME) 

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp admodel.h $(DISKDIR)/$(INCLDIR)
	cp spcomm.h $(DISKDIR)/$(INCLDIR)
	cp adsplus.h $(DISKDIR)/$(INCLDIR)
	cp newredef.h $(DISKDIR)/$(INCLDIR)
	cp s.h $(DISKDIR)/$(INCLDIR)
	cp tpl2cpp.exe $(DISKDIR)/$(BINDIR)     

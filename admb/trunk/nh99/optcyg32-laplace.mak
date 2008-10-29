#macros for making optimized library for DJGPP
CC = gcc
LL = tlib

FLAGS = -O3 -DUSE_LAPLACE -g -Dlinux -x c++ -O3 -c -I. -I../df1b2 -I../linad99 -I ../tools99 -fpermissive -D __GNUDOS__ -D OPT_LIB

#FLAGS = -g -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = cyg-gcc32olp
LIBNAME = libadmod.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /cygdrive/i/cygdisk
BINDIR= bin
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

#disk: $(LIBPATH)/$(LIBNAME) 
#	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
#	cp admodel.h $(DISKDIR)/$(INCLDIR)
#	cp tpl2cpp.exe $(DISKDIR)/$(BINDIR)/tpl2cpp.exe


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

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

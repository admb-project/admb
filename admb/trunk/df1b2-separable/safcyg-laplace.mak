
#macros for making optimized library for DJGPP
CC = gcc
LL = tlib

FLAGS = -DUSE_LAPLACE -g -O3 -Dlinux -x c++ -c -I. -I../nh99 -I../linad99 -I ../tools99 -fpermissive -D __GNUDOS__ -D OPT_LIB

#FLAGS = -g -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = cyg-gcc295slp
LIBNAME = libdf1b2s.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /cygdrive/g/cyg-g2953-laplace
BINDIR= bin
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

all: disk tpl2rem

tpl2rem:
	gcc -DUX tpl2rem.c -o tpl2rem

disk: $(LIBPATH)/$(LIBNAME)  tpl2rem
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp adpool.h $(DISKDIR)/$(INCLDIR)
	cp adrndeff.h $(DISKDIR)/$(INCLDIR)
	cp df1b2fun.h $(DISKDIR)/$(INCLDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLDIR)
	cp df1b2test.h $(DISKDIR)/$(INCLDIR)
	cp smartbuf.h $(DISKDIR)/$(INCLDIR)
	cp tpl2rem.exe $(DISKDIR)/$(BINDIR)/tpl2cpp.exe


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
	cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

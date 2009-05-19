
#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS1 = ${OPTIONS} -m64 -fpermissive -O3 -c -I. -I../linad99 -I../tools99  \
-D__GNUDOS__ -DOPT_LIB -Dlinux
FLAGS = ${OPTIONS} -w -m64 -fpermissive  -c -I. -I../linad99 -I../tools99 -I../nh99 \
-D__GNUDOS__ -DOPT_LIB -Dlinux
LIBPATH =gcc343-amd64o
LIBNAME = libdf1b2o.a
LIBDIR = lib
BINDIR = bin
INCLDIR= include
DISKDIR= /tmp/g32-gentoo
DRIVECHANGE=fff.bat
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
.PHONY: admodel.cpp
.PHONY: tpl2cpp

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) tpl2cpp 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

admodel.obj : admodel.cpp
	$(CC) $(FLAGS1)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

fvar1.obj : fvar1.cpp
	$(CC) $(FLAGS1) $<
	mv $*.o $(LIBPATH)/$*.obj


all: $(LIBPATH)/$(LIBNAME)  xtpl2cpp disk

xtpl2rem:
	gcc -I. -DUX tpl2rem.c -otpl2rem

disk: 
	cp df1b2fnl.h df32fun.h df3fun.h adpool.h adrndeff.h df1b2fun.h smartbuf.h $(DISKDIR)/$(INCLDIR)
	gcc -DUX -otpl2rem tpl2rem.c
	cp tpl2rem $(DISKDIR)/$(BINDIR)/tpl2rem
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- rm tpl2rem ;  cd $(LIBPATH) ; rm *.obj ; rm *.o ;  rm *.a

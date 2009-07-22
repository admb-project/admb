#macros for making optimized library for DJGPP

CC = gcc
LL = tlib
FLAGS1 = ${OPTIONS} -I/usr/src/ATLAS/include ${PVMOPTION} -DOPT_LIB -g -DUSE_LAPLACE -fpermissive -O3 -c -I. -I../nh99 -I../linad99 -I../tools99 -D__GNUDOS__
FLAGS = ${OPTIONS} -I/usr/src/ATLAS/include ${PVMOPTION} -DOPT_LIB  -fpermissive -DUSE_LAPLACE -O3 -c -I. -I../nh99 -I../linad99 -I../tools99  -Dlinux -D__GNUDOS__
LIBPATH =gcc32-rh8olp
LIBNAME = libdf1b2o.a
LIBDIR = lib
BINDIR = bin
INCLDIR= include
DISKDIR= /g/g32-rh8-laplace
DRIVECHANGE=fff.bat
SRCDIR =  src
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj


disk: $(LIBPATH)/$(LIBNAME) tpl2rem
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp adpool.h $(DISKDIR)/$(INCLDIR)
	cp adrndeff.h $(DISKDIR)/$(INCLDIR)
	cp df1b2fun.h $(DISKDIR)/$(INCLDIR)
	cp df3fun.h $(DISKDIR)/$(INCLDIR)
	cp df1b2fnl.h $(DISKDIR)/$(INCLDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLDIR)
	cp smartbuf.h $(DISKDIR)/$(INCLDIR)
	cp tpl2rem $(DISKDIR)/$(BINDIR)
	cp sed* $(DISKDIR)/$(BINDIR)

tpl2rem.c: tpl2rem.lex
	flex tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem.c

tpl2rem: tpl2rem.c
	gcc tpl2rem.c -o tpl2rem
	cp sed* $(DISKDIR)/$(BINDIR)

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a
	- rm tpl2rem





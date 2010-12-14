#macros for making optimized library for DJGPP

CC = gcc
LL = tlib
FLAGS1 = -w ${OPTIONS} ${PVMOPTION} -DOPT_LIB  -fpermissive -DUSE_LAPLACE -O3 -c -I. -I../nh99 -I../linad99 -I../tools99  -Dlinux -D__GNUDOS__
#FLAGS = -fdiagnostics-show-option -fno-for-scope -Wall -Wno-comment -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${OPTIONS} ${PVMOPTION} -DOPT_LIB  -fpermissive -DUSE_LAPLACE -O3 -c -I. -I../nh99 -I../linad99 -I../tools99  -Dlinux -D__GNUDOS__
FLAGS = -fno-for-scope -Wall -Wno-non-virtual-dtor -Wno-comment -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${OPTIONS} ${PVMOPTION} -DOPT_LIB  -fpermissive -DUSE_LAPLACE -O3 -c -I. -I../nh99 -I../linad99 -I../tools99  -Dlinux -D__GNUDOS__
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

$(filter-out df1b2f24.obj df1b2fn2.obj df1b2f19.obj df1b2fun.obj df1b2pow.obj df1b2ghmult.obj df1b2gh.obj  df1b2im5.obj df1b2im3f.obj df1b2lp6.obj df1b2lp8.obj df1b2f14.obj df1b2f13.obj df1b2f10.obj f1b2lapqd.obj df1b2fnl.obj df3fun.obj df1fun.obj dflocmin.obj df1b2lap.obj, $(OBJ0)): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

df1b2f24.obj df1b2fn2.obj df1b2f19.obj df1b2fun.obj df1b2pow.obj df1b2ghmult.obj df1b2gh.obj df1b2im5.obj df1b2im3f.obj df1b2lp6.obj df1b2lp8.obj df1b2f14.obj df1b2f13.obj df1b2f10.obj f1b2lapqd.obj df1b2fnl.obj df3fun.obj df1fun.obj dflocmin.obj df1b2lap.obj: %.obj: %.cpp
	$(CC) $(FLAGS1)  $<
	mv $*.o $(LIBPATH)/$*.obj

disk: $(LIBPATH)/$(LIBNAME) tpl2rem
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp adpool.h $(DISKDIR)/$(INCLDIR)
	cp adrndeff.h $(DISKDIR)/$(INCLDIR)
	cp df1b2fun.h $(DISKDIR)/$(INCLDIR)
	cp df1fun.h $(DISKDIR)/$(INCLDIR)
	cp df3fun.h $(DISKDIR)/$(INCLDIR)
	cp df1b2fnl.h $(DISKDIR)/$(INCLDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLDIR)
	cp smartbuf.h $(DISKDIR)/$(INCLDIR)
	- cp tpl2rem tpl2rem.exe $(DISKDIR)/$(BINDIR)
	cp sed* $(DISKDIR)/$(BINDIR)

tpl2rem.c: tpl2rem.lex
	flex tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem.c

tpl2rem: tpl2rem.c
	gcc tpl2rem.c -o tpl2rem
	cp sed* $(DISKDIR)/$(BINDIR)

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a
	- rm -f tpl2rem
	- rm -f tpl2rem.c





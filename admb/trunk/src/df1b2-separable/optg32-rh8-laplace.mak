CC = gcc
LL = tlib

CFLAGS=-O3
ifdef DEBUG
CFLAGS=-g
endif

FLAGS1 = $(CFLAGS) -w ${OPTIONS} ${PVMOPTION} -DOPT_LIB  -fpermissive -DUSE_LAPLACE -c -I. -I../nh99 -I../linad99 -I../tools99  -Dlinux -D__GNUDOS__
#FLAGS = -fdiagnostics-show-option -fno-for-scope -Wall -Wno-comment -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${OPTIONS} ${PVMOPTION} -DOPT_LIB  -fpermissive -DUSE_LAPLACE -O3 -c -I. -I../nh99 -I../linad99 -I../tools99  -Dlinux -D__GNUDOS__
FLAGS = $(CFLAGS) -fno-for-scope -Wall -Wno-non-virtual-dtor -Wno-comment -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${OPTIONS} ${PVMOPTION} -DOPT_LIB  -fpermissive -DUSE_LAPLACE -c -I. -I../nh99 -I../linad99 -I../tools99  -Dlinux -D__GNUDOS__
LIBPATH =gcc32-rh8olp
LIBNAME = libdf1b2o.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

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
	$(CC) $(FLAGS)  $< -o $(LIBPATH)/$*.obj

df1b2f24.obj df1b2fn2.obj df1b2f19.obj df1b2fun.obj df1b2pow.obj df1b2ghmult.obj df1b2gh.obj df1b2im5.obj df1b2im3f.obj df1b2lp6.obj df1b2lp8.obj df1b2f14.obj df1b2f13.obj df1b2f10.obj f1b2lapqd.obj df1b2fnl.obj df3fun.obj df1fun.obj dflocmin.obj df1b2lap.obj: %.obj: %.cpp
	$(CC) $(FLAGS1)  $< -o $(LIBPATH)/$*.obj

disk: $(LIBPATH)/$(LIBNAME) tpl2rem
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp adpool.h $(DISKDIR)/include
	cp adrndeff.h $(DISKDIR)/include
	cp df1b2fun.h $(DISKDIR)/include
	cp df1fun.h $(DISKDIR)/include
	cp df3fun.h $(DISKDIR)/include
	cp df1b2fnl.h $(DISKDIR)/include
	cp df1b2loc.h $(DISKDIR)/include
	cp smartbuf.h $(DISKDIR)/include
	cp tpl2rem $(DISKDIR)/bin
	cp sed* $(DISKDIR)/bin

tpl2rem.c: tpl2rem.lex
	flex tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem.c

tpl2rem: tpl2rem.c
	gcc tpl2rem.c -o tpl2rem
	cp sed* $(DISKDIR)/bin

clean:
	rm -rvf $(LIBPATH)
	rm -vf tpl2rem

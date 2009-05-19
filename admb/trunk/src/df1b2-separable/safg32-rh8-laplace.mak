CC = gcc
LL = tlib
FLAGS1 = ${OPTIONS} -I/usr/src/ATLAS/include ${PVMOPTION} -g -DSAFE_ALL -DUSE_LAPLACE -fpermissive -O3 -c -I. -I../nh99 -I../linad99 -I../tools99  \
  -D __GNUDOS__ 

FLAGS = ${OPTIONS} -I/usr/src/ATLAS/include ${PVMOPTION} -DSAFE_ALL -fpermissive -DUSE_LAPLACE -O3 -c -I. -I../nh99 -I../linad99 -I../tools99 -Dlinux -D __GNUDOS__

LIBPATH =gcc32-rh8slp
LIBNAME = libdf1b2s.a
LIBDIR = lib
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


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp adpool.h $(DISKDIR)/$(INCLDIR)
	cp adrndeff.h $(DISKDIR)/$(INCLDIR)
	cp df1b2fun.h $(DISKDIR)/$(INCLDIR)
	cp df3fun.h $(DISKDIR)/$(INCLDIR)
	cp df32fun.h $(DISKDIR)/$(INCLDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLDIR)
	cp smartbuf.h $(DISKDIR)/$(INCLDIR)

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a





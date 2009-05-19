
#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS1 = -g -DUSE_LAPLACE -fpermissive -O3 -c -I. -I../nh99 -I../linad99 -I../tools99  \
  -D __GNUDOS__ -D OPT_LIB
FLAGS = -fpermissive -DUSE_LAPLACE -O3 -c -I. -I../nh99 -I../linad99 -I../tools99  \
  -D __GNUDOS__ -D OPT_LIB
LIBPATH =gcc296-rh73olp
LIBNAME = libdf1b2o.a
LIBDIR = lib
INCLDIR= include
DISKDIR= /g/g296-rh73-laplace
DISKDIR1= \g295dsk
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
	cp df1b2fnl.h $(DISKDIR)/$(INCLDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLDIR)
	cp smartbuf.h $(DISKDIR)/$(INCLDIR)
	cp sedcmd $(DISKDIR)/bin
	cp sedcmd2 $(DISKDIR)/bin
	cp sedcmd3 $(DISKDIR)/bin
	cp seddf1b2 $(DISKDIR)/bin
	cp seddf1b3 $(DISKDIR)/$(BINDIR)
	cp seddf1b4 $(DISKDIR)/$(BINDIR)
	cp sedf1b2a $(DISKDIR)/bin
	cp sedf1b2c $(DISKDIR)/bin
	cp sedf1b2d $(DISKDIR)/bin
	gcc -DUX tpl2rem.c -otpl2rem
	cp tpl2rem $(DISKDIR)/bin


clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a




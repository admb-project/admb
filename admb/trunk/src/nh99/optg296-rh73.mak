

#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS1 = -fpermissive -g -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB -Dlinux
FLAGS = -fpermissive -O3 -c -I. -I../df1b2 -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB -Dlinux
LIBPATH =gcc296-rh73o
LIBNAME = libadmod.a
LIBDIR = lib
BINDIR = bin
INCLDIR= include
DISKDIR=/g/g296-rh73
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

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

admodel.obj : admodel.cpp
	$(CC) $(FLAGS1)  $<
	mv $*.o $(LIBPATH)/$*.obj


all: $(LIBPATH)/$(LIBNAME)  tpl2cpp disk

tpl2cpp:
	gcc -I. -DUX mylex.c -otpl2cpp

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp admodel.h $(DISKDIR)/$(INCLDIR)
	cp spcomm.h $(DISKDIR)/$(INCLDIR)
	cp adsplus.h $(DISKDIR)/$(INCLDIR)
	cp newredef.h $(DISKDIR)/$(INCLDIR)
	cp s.h $(DISKDIR)/$(INCLDIR)
	cp tpl2cpp $(DISKDIR)/$(BINDIR)     

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a


#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS1 = -g -fpermissive -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB -Dlinux
FLAGS = -w -DAD_DEMO -fpermissive -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB -Dlinux
LIBPATH =gcc32-rh8o-demo
LIBNAME = libadmod.a
LIBDIR = lib
BINDIR = bin
INCLDIR= include
DISKDIR=/g/g32-rh8-demo
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

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj


fvar1.obj : fvar1.cpp
	$(CC) $(FLAGS1) $<
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
	- rm tpl2cpp ;  cd $(LIBPATH) ; rm *.obj ; rm *.o ;  rm *.a

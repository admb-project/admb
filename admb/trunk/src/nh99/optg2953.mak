
#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
#FLAGS = -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB 
FLAGS1 = -g -fpermissive -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB -Dlinux
FLAGS = -fpermissive -O3 -c -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB -Dlinux
LIBPATH =gcc2953o
LIBNAME = libadmod.a
LIBDIR = lib
BINDIR = bin
INCLDIR= include
DISKDIR= f:/g2953dsk
DISKDIR1= \g2953dsk
DRIVECHANGE=fff.bat
SRCDIR =  src
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
.PHONY: admodel.cpp

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
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


all: $(LIBPATH)/$(LIBNAME)  tpl2cpp disk

tpl2cpp:
	gcc -I. mylex.c -otpl2cpp.exe

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp admodel.h $(DISKDIR)/$(INCLDIR)
	cp spcomm.h $(DISKDIR)/$(INCLDIR)
	cp adsplus.h $(DISKDIR)/$(INCLDIR)
	cp newredef.h $(DISKDIR)/$(INCLDIR)
	cp s.h $(DISKDIR)/$(INCLDIR)
	cp tpl2cpp.exe $(DISKDIR)/$(BINDIR)     
	cd $(DISKDIR)  ; \
	rm ad_build.exe ; \
	rm ad_build.zip ; \
	pkzip -r -p ad_build ; \
	zip2exe ad_build ; \
	rm ad_build.zip

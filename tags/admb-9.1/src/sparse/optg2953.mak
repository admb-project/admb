

#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS = -g -fpermissive -O3 -c -I. -I../linad99 -I../tools99 -D __SPDLL__ \
  -D __GNUDOS__ -D OPT_LIB
LIBPATH =gcc2953o
LIBNAME = libadt.a
LIBDIR = lib
INCLDIR= include
DISKDIR= f:/g2953dsk
DISKDIR1= /g2953dsk
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

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj


all: $(LIBPATH)/$(LIBNAME)  disk


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp adoption.hpp $(DISKDIR)/$(INCLDIR)
	cp adstring.hpp $(DISKDIR)/$(INCLDIR)
	cp cifstrem.h $(DISKDIR)/$(INCLDIR)
	cp clist.h $(DISKDIR)/$(INCLDIR)
	cd $(DISKDIR) ;\
	rm ad_build.exe ; \
	rm ad_build.zip ; \
	pkzip -r -p ad_build ; \
	zip2exe ad_build ; \
	rm ad_build.zip

#macros for making optimized library for DJGPP
CC = gcc
SHELL=sh
LL = tlib
FLAGS1 = -g -fpermissive -O3 -c -I. -I../nh99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DSAFE_ALL  -Dlinux
FLAGS =  -fpermissive -O3 -c -I. -I../nh99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DSAFE_ALL  -Dlinux
LIBPATH =gcc2953s
LIBNAME = libads.a
LIBDIR = lib
INCLDIR= include
DISKDIR= f:/g2953dsk
DISKDIR1= /g2953dsk
DRIVECHANGE=fff.bat
SRCDIR =  src
.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$


.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
.PHONY: fvar1.obj
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
fvar1.obj: fvar1.cpp
	$(CC) $(FLAGS1) $<
	mv $*.o $(LIBPATH)/$*.obj


all: $(LIBPATH)/$(LIBNAME)  disk


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp insx001.h $(DISKDIR)/$(INCLDIR)
	cp insx001a.h $(DISKDIR)/$(INCLDIR)
	cp insx002.h $(DISKDIR)/$(INCLDIR)
	cp insx003.h $(DISKDIR)/$(INCLDIR)
	cp insx004.h $(DISKDIR)/$(INCLDIR)
	cp insx005.h $(DISKDIR)/$(INCLDIR)
	cp insx005a.h $(DISKDIR)/$(INCLDIR)
	cp insx006.h $(DISKDIR)/$(INCLDIR)
	cp insx007.h $(DISKDIR)/$(INCLDIR)
	cp insx008.h $(DISKDIR)/$(INCLDIR)
	cp insx009.h $(DISKDIR)/$(INCLDIR)
	cp insx010.h $(DISKDIR)/$(INCLDIR)
	cp insx011.h $(DISKDIR)/$(INCLDIR)
	cp insx012.h $(DISKDIR)/$(INCLDIR)
	cp insx013.h $(DISKDIR)/$(INCLDIR)
	cp insx014.h $(DISKDIR)/$(INCLDIR)
	cp insx015.h $(DISKDIR)/$(INCLDIR)
	cp insx016.h $(DISKDIR)/$(INCLDIR)
	cp insx017.h $(DISKDIR)/$(INCLDIR)
	cp insx018.h $(DISKDIR)/$(INCLDIR)
	cp fvar.hpp $(DISKDIR)/$(INCLDIR)
	cp trunc.hpp $(DISKDIR)/$(INCLDIR)
	cd $(DISKDIR1)  ; \
	rm ad_build.exe  ; \
	rm ad_build.zip  ; \
	pkzip -r -p ad_build  ; \
	zip2exe ad_build  ; \
	rm ad_build.zip

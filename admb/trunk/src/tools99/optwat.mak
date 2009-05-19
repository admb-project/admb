#macros for making safe library for WATCOM
CC = wcl386 
LL = tlib
FLAGS = /fh=wathead /i\watcom\h\win /c /fp5 /oneatx /zp4 /5  /i. /dOPT_LIB /d__WAT32__
LIBPATH = optwat
DISKDIR= g:\watdisk
LIBNAME = adt32.lib
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include

vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk

#echo $(LIBNAME)  > $(LIBPATH)\t.rsp
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	cd $(LIBPATH) 
	ls *.obj > t.rsp
	cd ..
	c:\bin\sed -e '1,$$s/^/+/' $(LIBPATH)/t.rsp > tmp
	cp tmp $(LIBPATH)/t.rsp 
	cd $(LIBPATH) 
	del *.lib
	wlib -b -c $(LIBNAME) @t.rsp
	cd ..

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)

disk: 
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 
	copy adstring.hpp $(DISKDIR)\$(INCLUDEDIR)
	copy cifstrem.h $(DISKDIR)\$(INCLUDEDIR)
	copy clist.h $(DISKDIR)\$(INCLUDEDIR)
	copy mycif.h $(DISKDIR)\$(INCLUDEDIR)
	copy prn_t.h $(DISKDIR)\$(INCLUDEDIR)
	copy safe_mem.h $(DISKDIR)\$(INCLUDEDIR)
	copy tescl.h $(DISKDIR)\$(INCLUDEDIR)


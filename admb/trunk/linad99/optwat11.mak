#macros for making safe library for WATCOM
CC = wcl386 
LL = tlib
#FLAGS = /fh=wathead /i\watcom\h\win /c /fp5 /oneatx /zp4 /5  /i. /dOPT_LIB /d__WAT32__
FLAGS = /fh=wathead /i\watcom\h\nt /c /fp5 /oneatx /zp4 /5  /i. /dOPT_LIB /d__WAT32__
LIBPATH = optwat11
DISKDIR= g:\watdisk.11
LIBNAME = admod32.lib
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include
BINDIR = bin

vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk

	echo $(LIBNAME)  > $(LIBPATH)\t.rsp
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJSPLUS)  
	cd $(LIBPATH) 
	ls *.obj > t.rsp
	cd ..
	c:\bin\sed  -e '1,$$s/^/+/'  $(LIBPATH)/t.rsp > tmp
	cp tmp $(LIBPATH)/t.rsp 
	cd $(LIBPATH) 
	wlib -b -c $(LIBNAME) @t.rsp
	cd ..

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)

#$(CC) $(FLAGS) /fo$(LIBPATH)\\$*.obj $<
$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)  	

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)  	


disk: 
	wcl386 mylex.c
	copy mylex.exe $(DISKDIR)\$(BINDIR)\tpl2cpp.exe
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 
	copy ad3d.h $(DISKDIR)\$(INCLUDEDIR)
	copy admod2.h $(DISKDIR)\$(INCLUDEDIR)
	copy admodel.h $(DISKDIR)\$(INCLUDEDIR)
	copy admodhd.h $(DISKDIR)\$(INCLUDEDIR)
	copy adsplus.h $(DISKDIR)\$(INCLUDEDIR)
	copy spcomm.h $(DISKDIR)\$(INCLUDEDIR)


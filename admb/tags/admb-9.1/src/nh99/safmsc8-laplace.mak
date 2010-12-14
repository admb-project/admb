
#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc8slp
STUBPATH = msc8slp-stub
STUBLIBNAME = df1b2stubs.lib
FLAGS = /nologo /W4 /wd4258 /wd4700 /wd4288 /wd4018 /wd4505 /wd4239 /wd4512 /wd4511 /wd4804 /wd4100 /wd4996 /wd4127 /wd4190 /wd4706 /wd4701 /wd4068 /wd4244 /wd4101 /wd4189 /wd4717 ${OPTIONS} ${PVMOPTION} /GF /EHsc -DUSE_LAPLACE -DWIN32 /c -I. -I../df1b2-separable -I../linad99 -I../tools99 -D__MSVC32__=8  -DSAFE_ALL /Ox -DADMB_VERSION=${ADMB_VERSION}
LIBNAME = admod32s.lib 
LIBRARIAN = tlib
SRCDIR =  src
LIBDIR =  lib
BINDIR =  bin
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 
$(LIBPATH)/$(LIBNAME) :  fvar.hpp $(OBJECTS)
	rm -f $(LIBPATH)/$(LIBNAME)   ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH) ; \
	cat t.rsp  ; \
	ls $(filter-out pvmvar1.obj para3.obj, $(OBJECTS)) >> t.rsp  ; \
	lib /NOLOGO @t.rsp ; \
	cd ..
	
$(OBJGUI): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       
fvar.hpp:

all: $(LIBPATH)/$(LIBNAME) stub disk

stub: df1b2stub.cpp
	$(CC) $(FLAGS) df1b2stub.cpp
	mv df1b2stub.obj $(STUBPATH)       
	echo /OUT:$(STUBLIBNAME)  > $(STUBPATH)/t.rsp ; \
	cd $(STUBPATH) ; \
	cat t.rsp  ; \
	ls *.obj >> t.rsp  ; \
	lib /NOLOGO @t.rsp  


disk: 
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR)
	cp adsplus.h $(DISKDIR)/$(INCLUDEDIR)
	cp spcomm.h $(DISKDIR)/$(INCLUDEDIR)
	cp s.h $(DISKDIR)/$(INCLUDEDIR)
	cp newredef.h $(DISKDIR)/$(INCLUDEDIR)
	$(CC) /nologo /wd4996 tpl2cpp.c
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
	- cp $(STUBPATH)/$(STUBLIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a
	- cd $(STUBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

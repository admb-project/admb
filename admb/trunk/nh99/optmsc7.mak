#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc7o
FLAGS = ${OPTIONS} -Ig:/vc7/include/sys -Ig:/vc7/include -DWIN32 /c /W3 /I. /I../linad99 /I../tools99 -D__MSVC32__=7 -DOPT_LIB /Ox  /G7
LIBNAME = admod32.lib 
LIBRARIAN = tlib
DISKDIR= g:/adms7.m32
SRCDIR =  src
LIBDIR =  lib
BINDIR =  bin
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) :  fvar.hpp $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 
	rm $(LIBPATH)/t.rsp ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH) ; \
	cat t.rsp  ; \
	ls *.obj >> t.rsp  ; \
	lib @t.rsp ; \
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

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR)
	cp adsplus.h $(DISKDIR)/$(INCLUDEDIR)
	cp spcomm.h $(DISKDIR)/$(INCLUDEDIR)
	cp s.h $(DISKDIR)/$(INCLUDEDIR)
	cp newredef.h $(DISKDIR)/$(INCLUDEDIR)
	$(CC) mylex.c -I. -Ig:/vs/vc98/include /link /libpath:g:/vs/vc98/lib 
	cp mylex.exe $(DISKDIR)/$(BINDIR)/tpl2cpp.exe
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib

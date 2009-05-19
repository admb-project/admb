


#macros for making optimized library for MS         
CC = g:/vc7/bin/cl
LL = tlib
STUBPATH = msc7slp-stub
STUBLIBNAME = df1b2stubs.lib
LIBPATH = msc7slp
FLAGS = ${OPTIONS} ${PVMOPTION} -DUSE_LAPLACE /EHsc -Ig:/vc7/include -DWIN32 /c /W3 /I. /I../linad99 /I../df1b2-separable /I../tools99 -D__MSVC32__=7 -DSAFE_ALL /Ox 
LIBNAME = admod32s.lib 
LIBRARIAN = tlib
DISKDIR= g:/adms7lp.m32
SRCDIR =  src
LIBDIR =  lib
BINDIR =  bin
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) :  fvar.hpp $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 
	- rm $(LIBPATH)/t.rsp ; \
	rm $(LIBPATH)/$(LIBNAME)   ; \
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

all: $(LIBPATH)/$(LIBNAME) stub disk

disk: 
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR)
	cp adsplus.h $(DISKDIR)/$(INCLUDEDIR)
	cp spcomm.h $(DISKDIR)/$(INCLUDEDIR)
	cp s.h $(DISKDIR)/$(INCLUDEDIR)
	cp newredef.h $(DISKDIR)/$(INCLUDEDIR)
	$(CC) mylex.c -I. -Ig:/vc7/include /link /libpath:g:/vc7/include 
	cp mylex.exe $(DISKDIR)/$(BINDIR)/tpl2cpp.exe
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
	cp $(STUBPATH)/$(STUBLIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a
	- cd $(STUBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a


stub: df1b2stub.cpp
	$(CC) $(FLAGS) df1b2stub.cpp
	mv df1b2stub.obj $(STUBPATH)       
	echo /OUT:$(STUBLIBNAME)  > $(STUBPATH)/t.rsp ; \
	cd $(STUBPATH) ; \
	cat t.rsp  ; \
	ls *.obj >> t.rsp  ; \
	lib @t.rsp 
	rm $(STUBPATH)/t.rsp ; \

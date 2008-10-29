

#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc8olp
STUBPATH = msc8olp-stub
STUBLIBNAME = df1b2stubo.lib
FLAGS = ${OPTIONS} ${PVMOPTION} -Ik:/temp/ATLAS/include /GF /EHsc -DUSE_LAPLACE -DWIN32 /c -I. -I../df1b2-separable -I../linad99 -I../tools99 -D__MSVC32__=8  -DOPT_LIB /Ox -Ih:/vs8/vc/include -Ih:/vs8/VC/PlatformSDK/Include
LIBNAME = admod32.lib 
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

stub: df1b2stub.cpp
	$(CC) $(FLAGS) df1b2stub.cpp
	mv df1b2stub.obj $(STUBPATH)       
	echo /OUT:$(STUBLIBNAME)  > $(STUBPATH)/t.rsp ; \
	cd $(STUBPATH) ; \
	cat t.rsp  ; \
	ls *.obj >> t.rsp  ; \
	lib @t.rsp 
	-rm $(STUBPATH)/t.rsp ; \


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

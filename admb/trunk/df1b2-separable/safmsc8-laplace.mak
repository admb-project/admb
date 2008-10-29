

#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc8slp
FLAGS = ${OPTIONS} ${PVMOPTION} -Ik:/temp/ATLAS/include /GF /EHsc -DUSE_LAPLACE -DWIN32 /c -I. -I../linad99 -I../nh99 -I../tools99 -D__MSVC32__=8  -DSAFE_ALL /Ox -Ih:/vs8/vc/include -Ih:/vs8/VC/PlatformSDK/Include
LIBNAME = df1b2s.lib 
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
	cp df1b2fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp adpool.h $(DISKDIR)/$(INCLUDEDIR)
	cp adrndeff.h $(DISKDIR)/$(INCLUDEDIR)
	cp df1b2fnl.h $(DISKDIR)/$(INCLUDEDIR)
	cp df3fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp df32fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc6olp
FLAGS =  ${PVMOPTION} -I../linad99 -Ih:/vc6/include -DWIN32 /c /W3 /I. /I../nh99  /I../tools99 -D__MSVC32__ -DUSE_LAPLACE -DOPT_LIB /Ox 
LIBNAME = df1b2o.lib 
LIBRARIAN = tlib
DISKDIR= f:/adms6lp.m32
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

all: $(LIBPATH)/$(LIBNAME) disk xtpl2rem

xtpl2rem: tpl2rem.c
	- cl -DWIN32 -Ih:/vc6/include tpl2rem.c -o tpl2rem.exe  /link /LIBPATH:h:/vc6/lib
	- cp tpl2rem.exe $(DISKDIR)/$(BINDIR)

disk: 
	cp sed* $(DISKDIR)/$(BINDIR)
	cp df1b2fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp adpool.h $(DISKDIR)/$(INCLUDEDIR)
	cp adrndeff.h $(DISKDIR)/$(INCLUDEDIR)
	cp df1b2fnl.h $(DISKDIR)/$(INCLUDEDIR)
	cp df3fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp df32fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp df33fun.h $(DISKDIR)/$(INCLUDEDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

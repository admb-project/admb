#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc8olp
FLAGS = /nologo /W4 /wd4018 /wd4552 /wd4189 /wd4101 /wd4505 /wd4715 /wd4700 /wd4239 /wd4702 /wd4702 /wd4511 /wd4512 /wd4100 /wd4127 /wd4706 /wd4996 /wd4244 /wd4146 /wd4701 ${OPTIONS} ${PVMOPTION} /GF /EHsc -DUSE_LAPLACE -DWIN32 /c -I. -I../linad99 -I../nh99 -I../tools99 -D__MSVC32__=8  -DOPT_LIB /Ox
LIBNAME = df1b2o.lib 
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
	rm $(LIBPATH)/t.rsp ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH) ; \
	cat t.rsp  ; \
	ls $(filter-out df1b2lp12.obj, $(OBJECTS)) >> t.rsp  ; \
	lib /NOLOGO /IGNORE:4006 @t.rsp ; \
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

all: $(LIBPATH)/$(LIBNAME) disk tpl2rem

tpl2rem: tpl2rem.lex
	flex -w tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem.c
	cl /nologo /W4 /wd4049 /wd4700 /wd4702 /wd4018 /wd4996 /wd4131 /wd4127 /wd4244 /wd4101 /wd4189 -DWIN32 tpl2rem.c
	cp tpl2rem.exe $(DISKDIR)/$(BINDIR)

disk: 
	cp sed* $(DISKDIR)/$(BINDIR)
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
	- rm -f tpl2rem.c

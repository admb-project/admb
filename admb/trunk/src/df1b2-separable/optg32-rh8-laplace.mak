CFLAGS=-O3
ifdef DEBUG
CFLAGS=-g
endif

LIBPATH =gcc32-rh8olp
LIBNAME = libdf1b2o.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

.PHONY: disk
include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS)  $< -o $(LIBPATH)/$*.obj

disk: $(LIBPATH)/$(LIBNAME) tpl2rem
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp adpool.h $(DISKDIR)/include
	cp adrndeff.h $(DISKDIR)/include
	cp df1b2fun.h $(DISKDIR)/include
	cp df1fun.h $(DISKDIR)/include
	cp df3fun.h $(DISKDIR)/include
	cp df1b2fnl.h $(DISKDIR)/include
	cp df1b2loc.h $(DISKDIR)/include
	cp smartbuf.h $(DISKDIR)/include
	cp tpl2rem $(DISKDIR)/bin
	cp sed* $(DISKDIR)/bin

tpl2rem.c: tpl2rem.lex
	flex tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem.c

tpl2rem: tpl2rem.c
	gcc tpl2rem.c -o tpl2rem
	cp sed* $(DISKDIR)/bin

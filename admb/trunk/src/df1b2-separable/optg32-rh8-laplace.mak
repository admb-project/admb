LIBPATH =gcc32-rh8olp
LIBNAME = libdf1b2o.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

.PHONY: disk tpl2rem
include objects.lst

all: disk

disk: $(DISKDIR)/lib/$(LIBNAME) $(DISKDIR)/bin/tpl2rem
	cp adpool.h $(DISKDIR)/include
	cp adrndeff.h $(DISKDIR)/include
	cp df1b2fun.h $(DISKDIR)/include
	cp df1fun.h $(DISKDIR)/include
	cp df3fun.h $(DISKDIR)/include
	cp df1b2fnl.h $(DISKDIR)/include
	cp df1b2loc.h $(DISKDIR)/include
	cp smartbuf.h $(DISKDIR)/include
	cp sedcmd sedcmd2 sedcmd3 seddf1b2 seddf1b3 seddf1b4 sedf1b2a sedf1b2c sedf1b2d sedflex $(DISKDIR)/bin

$(DISKDIR)/lib/$(LIBNAME): $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $@ $(LIBPATH)/*.obj

$(DISKDIR)/bin/tpl2rem:
	$(CC) tpl2rem.c -o $@

tpl2rem.c: tpl2rem.lex
	flex tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem.c

%.obj: %.cpp
	$(CXX) $(CXXFLAGS)  $< -o $(LIBPATH)/$*.obj

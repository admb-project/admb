CFLAGS=-O3
ifdef DEBUG
CFLAGS=-g
endif

LIBPATH =gcc32-rh8slp
LIBNAME = libdf1b2s.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

.PHONY: disk
include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS)  $< -o $(LIBPATH)/$*.obj

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp adpool.h $(DISKDIR)/include
	cp adrndeff.h $(DISKDIR)/include
	cp df1b2fun.h $(DISKDIR)/include
	cp df1fun.h $(DISKDIR)/include
	cp df3fun.h $(DISKDIR)/include
	cp df32fun.h $(DISKDIR)/include
	cp df1b2loc.h $(DISKDIR)/include
	cp smartbuf.h $(DISKDIR)/include

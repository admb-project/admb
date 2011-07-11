.SUFFIXES: .obj .cpp
.PHONY: disk

LIBNAME = libdf1b2s.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

include objects.lst

all: disk

disk: $(DISKDIR)/lib/$(LIBNAME) 
	cp adpool.h $(DISKDIR)/include
	cp adrndeff.h $(DISKDIR)/include
	cp df1b2fun.h $(DISKDIR)/include
	cp df1fun.h $(DISKDIR)/include
	cp df3fun.h $(DISKDIR)/include
	cp df32fun.h $(DISKDIR)/include
	cp df1b2loc.h $(DISKDIR)/include
	cp smartbuf.h $(DISKDIR)/include

$(DISKDIR)/lib/$(LIBNAME): $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $@ $(LIBPATH)/*.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS)  $< -o $(LIBPATH)/$*.obj

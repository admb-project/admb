.PHONY: disk
.SUFFIXES: .obj .cpp

LIBPATH =gcc32-rh8olp
LIBNAME = libadt.a
vpath %.obj $(LIBPATH)

include objects.lst

all: disk

disk: $(DISKDIR)/lib/$(LIBNAME) 
	cp adoption.hpp $(DISKDIR)/include
	cp adstring.hpp $(DISKDIR)/include
	cp cifstrem.h $(DISKDIR)/include
	cp clist.h $(DISKDIR)/include
	cp admb_messages.h $(DISKDIR)/include

$(DISKDIR)/lib/$(LIBNAME): $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $@ $(LIBPATH)/*.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

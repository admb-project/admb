.PHONY: disk

LIBPATH =gcc32-rh8olp
LIBNAME = libadt.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

include objects.lst

all: $(LIBNAME)  disk

$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBNAME) $(LIBPATH)/*.obj

disk: $(LIBNAME) 
	cp $(LIBNAME) $(DISKDIR)/lib
	cp adoption.hpp $(DISKDIR)/include
	cp adstring.hpp $(DISKDIR)/include
	cp cifstrem.h $(DISKDIR)/include
	cp clist.h $(DISKDIR)/include
	cp admb_messages.h $(DISKDIR)/include

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

.PHONY: disk

LIBNAME = libads.a
SRCDIR =  src
.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE)
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

$(OBJSPARSE): %.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/hs_sparse.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) -o $(LIBPATH)/$(@F) $<

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp fvar.hpp $(DISKDIR)/include
	cp trunc.hpp $(DISKDIR)/include

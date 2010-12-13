.PHONY: disk

LIBNAME = libads.a
SRCDIR =  src
.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)

include objects.lst

all: $(LIBNAME) disk

$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE)
	ar -rs $(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ0))
	ar -rs $(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ1))
	ar -rs $(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ2))
	ar -rs $(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ3))
	ar -rs $(LIBNAME) $(LIBPATH)/hs_sparse.obj

$(OBJSPARSE): %.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/hs_sparse.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) -o $(LIBPATH)/$(@F) $<

disk: $(LIBNAME) 
	cp $(LIBNAME) $(DISKDIR)/lib
	cp fvar.hpp $(DISKDIR)/include
	cp trunc.hpp $(DISKDIR)/include

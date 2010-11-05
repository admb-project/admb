.PHONY: disk

LIBNAME = libado.a
SRCDIR =  src
.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE)
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ0))
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ1))
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ2))
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ3))
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/hs_sparse.obj

$(OBJSPARSE): %.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/hs_sparse.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp fvar.hpp $(DISKDIR)/include
	cp dfpool.h $(DISKDIR)/include
	cp trunc.hpp $(DISKDIR)/include

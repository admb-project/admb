.PHONY: disk
.SUFFIXES: .obj .cpp

LIBNAME = libado.a
vpath %.obj $(LIBPATH)

include objects.lst

all: disk

disk: $(DISKDIR)/lib/$(LIBNAME) 
	cp fvar.hpp $(DISKDIR)/include
	cp dfpool.h $(DISKDIR)/include
	cp trunc.hpp $(DISKDIR)/include

$(DISKDIR)/lib/$(LIBNAME): $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE)
	ar -rs $@ $(addprefix $(LIBPATH)/, $(OBJ0))
	ar -rs $@ $(addprefix $(LIBPATH)/, $(OBJ1))
	ar -rs $@ $(addprefix $(LIBPATH)/, $(OBJ2))
	ar -rs $@ $(addprefix $(LIBPATH)/, $(OBJ3))
	ar -rs $@ $(LIBPATH)/hs_sparse.obj

$(OBJSPARSE): %.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/hs_sparse.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

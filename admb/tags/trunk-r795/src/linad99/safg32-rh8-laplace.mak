.PHONY: disk
.SUFFIXES: .obj .cpp

LIBNAME = libads.a
vpath %.obj $(LIBPATH)

include objects.lst

all: $(LIBPATH)/$(LIBNAME) disk

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE)
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ0))
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ1))
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ2))
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, $(OBJ3))
	ar -rs $(LIBPATH)/$(LIBNAME) $(addprefix $(LIBPATH)/, hs_sparse.obj)

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) -o $(LIBPATH)/$(@F) $<

$(OBJSPARSE): %.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/hs_sparse.obj

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp fvar.hpp $(DISKDIR)/include
	cp trunc.hpp $(DISKDIR)/include

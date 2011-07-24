.PHONY: disk

LIBNAME = libstats.a
SRCDIR =  cotrib/statslib
.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)

include objects.lst

all: disk

disk: $(DISKDIR)/lib/$(LIBNAME) 
	cp statsLib.hpp $(DISKDIR)/include

$(DISKDIR)/lib/$(LIBNAME): $(OBJ0)
	ar -rs $@ $(addprefix $(LIBPATH)/, $(OBJ0))

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) -o $(LIBPATH)/$(@F) $<

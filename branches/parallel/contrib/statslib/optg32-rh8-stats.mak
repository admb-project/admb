.PHONY: disk
.SUFFIXES: .obj .cpp

LIBPATH =gcc32-rh8olp
LIBNAME = libstats.a
vpath %.obj $(LIBPATH)

include objects.lst

all: disk

disk: $(DISKDIR)/lib/$(LIBNAME) 
	cp ../../contrib/statslib/statsLib.h $(DISKDIR)/include

$(DISKDIR)/lib/$(LIBNAME): $(OBJECTS)
	ar -rs $@ $(LIBPATH)/*.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

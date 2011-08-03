.PHONY: all
.SUFFIXES: .obj .cpp

vpath %.obj $(LIBPATH)

include objects.lst

all: $(OBJECTS)
	cp ecolib.h $(DISKDIR)

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

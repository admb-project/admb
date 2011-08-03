.PHONY: all
.SUFFIXES: .obj .cpp

vpath %.obj $(LIBPATH)

include objects.lst

all: $(OBJECTS)

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

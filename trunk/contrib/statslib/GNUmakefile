.PHONY: all
.SUFFIXES: .obj .cpp

vpath %.obj $(LIBPATH)

include objects.lst

all: $(OBJECTS)
ifeq ($(CXX),g++.exe)
	copy statsLib.h $(DISKDIR)
else
	cp statsLib.h $(DISKDIR)
endif

clean:

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

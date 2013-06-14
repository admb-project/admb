.PHONY: all
.SUFFIXES: .obj .cpp

include objects.lst

all: $(OBJECTS)
	copy ..\..\..\..\contrib\ecolib\ecolib.h $(DISKDIR)

clean:

{..\..\..\..\contrib\ecolib}.cpp.obj:
	$(CXX) -c $(CXXFLAGS) -I"..\..\dist\include" $<

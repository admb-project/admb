.PHONY: all
.SUFFIXES: .obj .cpp

include objects.lst

all: $(OBJECTS)
  echo $(DISKDIR)
	copy ..\..\..\..\contrib\ecolib\ecolib.h $(DISKDIR)

clean:

{..\..\..\..\contrib\ecolib}.cpp.obj:
	$(CXX) -c $(CXXFLAGS) -I"..\..\dist\include" $<

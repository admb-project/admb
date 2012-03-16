.PHONY: all
.SUFFIXES: .obj .cpp

include objects.lst

all: $(OBJECTS)
  echo $(DISKDIR)
	copy ..\..\..\..\contrib\statslib\statsLib.h $(DISKDIR)

clean:

{..\..\..\..\contrib\statslib}.cpp.obj:
  pwd 
	$(CXX) -c $(CXXFLAGS) -I"..\..\dist\include" $<

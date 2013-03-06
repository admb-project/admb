.PHONY: all
.SUFFIXES: .obj .cpp

include objects.lst

all: $(OBJECTS)
	copy ..\..\..\contrib\statslib\statsLib.h $(DISKDIR)

clean:

{..\..\..\contrib\statslib}.cpp.obj:
	$(CXX) -c $(CXXFLAGS) -I"..\..\dist\include" $<

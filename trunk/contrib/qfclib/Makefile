.PHONY: all
.SUFFIXES: .obj .cpp

include objects.lst

all: $(OBJECTS)
	copy ..\..\..\..\contrib\qfclib\qfclib.h $(DISKDIR)

clean:

{..\..\..\..\contrib\qfclib}.cpp.obj:
	$(CXX) -c $(CXXFLAGS) -I"..\..\dist\include" $<

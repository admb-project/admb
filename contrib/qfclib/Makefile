.PHONY: all
.SUFFIXES: .obj .cpp

include objects.lst

all: $(OBJECTS)
  echo $(DISKDIR)
	copy ..\..\..\..\contrib\qfclib\qfclib.h $(DISKDIR)

clean:

{..\..\..\..\contrib\qfclib}.cpp.obj:
  pwd 
	$(CXX) -c $(CXXFLAGS) -I"..\..\dist\include" $<

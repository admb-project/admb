include objects.lst

all: $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/saflp-df1b2-separable-$*.obj

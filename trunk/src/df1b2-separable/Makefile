include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3))

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<

clean:

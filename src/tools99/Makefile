include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0))

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<

include objects.lst

all: $(sort $(addprefix $(PREFIX_OBJ), $(OBJ7)))

$(PREFIX_OBJ)%.obj: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

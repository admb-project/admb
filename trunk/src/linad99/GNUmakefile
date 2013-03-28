include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)) $(PREFIX_OBJ)hs_sparse.obj

$(PREFIX_OBJ)hs_sparse.obj: ../sparse/hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

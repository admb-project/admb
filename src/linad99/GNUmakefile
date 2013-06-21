include objects.lst

all: all1 all2

all1: $(sort $(addprefix $(PREFIX_OBJ), $(OBJ1) $(OBJ2))) $(PREFIX_OBJ)hs_sparse.obj
all2: $(sort $(addprefix $(PREFIX_OBJ), $(OBJ3) $(OBJ4)))

$(PREFIX_OBJ)hs_sparse.obj: ../sparse/hs_sparse.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJECTS))

clean:

$(PREFIX_OBJ)%.obj: %.cpp
ifeq ($(CXX),cl)
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<
else
	$(CXX) -c $(CXXFLAGS) -o$@ $<
endif

all: $(addprefix $(PREFIX_OBJ), gdbprintlib.obj)

clean:

$(PREFIX_OBJ)%.obj: %.cpp
ifeq ($(CXX),cl)
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<
else
	$(CXX) -c $(CXXFLAGS) -o$@ $<
endif

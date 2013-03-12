include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJECTS))
ifeq ($(SHELL),sh.exe)
	copy statsLib.h $(DISK)\contrib
else
	cp statsLib.h $(DISK)/contrib
endif

clean:

$(PREFIX_OBJ)%.obj: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

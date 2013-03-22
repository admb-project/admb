include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJECTS))
ifeq ($(SHELL),sh.exe)
	copy statsLib.h $(ADMB_HOME)\contrib\include
else
	cp statsLib.h $(ADMB_HOME)/contrib/include
endif

clean:

$(PREFIX_OBJ)%.obj: %.cpp
ifeq ($(CXX),cl)
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<
else
	$(CXX) -c $(CXXFLAGS) -o$@ $<
endif


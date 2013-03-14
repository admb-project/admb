all: $(addprefix $(PREFIX_OBJ), sample.obj) test
	cp sample.h $(DISK)/contrib

test:
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" admb simple.tpl
	./simple

clean:
	@rm -vf sample.obj

$(PREFIX_OBJ)%.obj: %.cpp
	@#adcomp CXXFLAGS="-o $@" $<
	$(CXX) $(CXXFLAGS) -o $@ $<

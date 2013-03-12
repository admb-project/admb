include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJECTS))
ifeq ($(SHELL),sh.exe)
	copy qfclib.h $(DISK)\contrib
else
	cp qfclib.h $(DISK)/contrib
endif

test:
	make --directory=tests

clean:
ifneq ($(SHELL),sh.exe)
	@rm -vf tests/testfunction.htp
	@rm -vf tests/testfunction
	@rm -vf tests/nf1b2list1
	@rm -vf tests/variance
	@rm -vf tests/f1b2list12
	@rm -vf tests/f1b2list13
	@rm -vf tests/testfunctionre.log
	@rm -vf tests/testfunctionre.cpp
	@rm -vf tests/eigv.rpt
	@rm -vf tests/testfunction.log
	@rm -vf tests/testfunction.cpp
	@rm -vf tests/testfunctionre.htp
	@rm -vf tests/nf1b2list12
	@rm -vf tests/f1b2list1
	@rm -vf tests/nf1b2list13
	@rm -vf tests/fmin.log
	@rm -vf tests/testfunctionre
endif

$(PREFIX_OBJ)%.obj: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: all test
.SUFFIXES: .obj .cpp

vpath %.obj $(LIBPATH)

include objects.lst

all: $(OBJECTS)
ifeq ($(CXX),g++.exe)
	copy ecolib.h $(DISKDIR)
else
	cp ecolib.h $(DISKDIR)
endif

test:
	make --directory=test

clean:
	@rm -vf test/tests.log
	@rm -vf test/tests.cpp
	@rm -vf test/admodel.hes
	@rm -vf test/tests.par
	@rm -vf test/tests.cor
	@rm -vf test/tests.pin
	@rm -vf test/variance
	@rm -vf test/admodel.cov
	@rm -vf test/tests.std
	@rm -vf test/tests.htp
	@rm -vf test/eigv.rpt
	@rm -vf test/tests
	@rm -vf test/tests.bar
	@rm -vf test/tests.dat
	@rm -vf test/fmin.log
	@rm -vf test/tests.eva
	@rm -vf test/admodel.dep

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

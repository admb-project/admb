.PHONY: all test
.SUFFIXES: .obj .cpp

vpath %.obj $(LIBPATH)

include objects.lst

all: $(OBJECTS)
	cp qfc_est.cpp $(DISKDIR)
	cp qfc_sim.cpp $(DISKDIR)
	cp qfclib.h $(DISKDIR)

test:
	make --directory=test

clean:
	@rm -vf test/testfunction.htp
	@rm -vf test/testfunction
	@rm -vf test/nf1b2list1
	@rm -vf test/variance
	@rm -vf test/f1b2list12
	@rm -vf test/f1b2list13
	@rm -vf test/testfunctionre.log
	@rm -vf test/testfunctionre.cpp
	@rm -vf test/eigv.rpt
	@rm -vf test/testfunction.log
	@rm -vf test/testfunction.cpp
	@rm -vf test/testfunctionre.htp
	@rm -vf test/nf1b2list12
	@rm -vf test/f1b2list1
	@rm -vf test/nf1b2list13
	@rm -vf test/fmin.log
	@rm -vf test/testfunctionre

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

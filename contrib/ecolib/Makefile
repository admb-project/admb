.PHONY: all test
.SUFFIXES: .obj .cpp

vpath %.obj $(LIBPATH)

include objects.lst

all: $(OBJECTS)
	cp ecolib.h $(DISKDIR)
	cp Gompertz.cpp $(DISKDIR)
	cp Hassell.cpp $(DISKDIR)
	cp Hill.cpp $(DISKDIR)
	cp HollingII.cpp $(DISKDIR)
	cp HollingIII.cpp $(DISKDIR)
	cp HollingIV.cpp $(DISKDIR)
	cp Michaelis_Menten1.cpp $(DISKDIR)
	cp Michaelis_Menten2.cpp $(DISKDIR)
	cp Ricker.cpp $(DISKDIR)
	cp Shepherd.cpp $(DISKDIR)
	cp generalized_Ricker1.cpp $(DISKDIR)
	cp generalized_Ricker2.cpp $(DISKDIR)
	cp logistic.cpp $(DISKDIR)
	cp logistic3.cpp $(DISKDIR)
	cp logisticK.cpp $(DISKDIR)
	cp monomolecular.cpp $(DISKDIR)
	cp nonrectangular_hyperbola.cpp $(DISKDIR)
	cp pow_vectorized_RE.cpp $(DISKDIR)
	cp theta_logistic.cpp $(DISKDIR)

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

GTEST_DIR=googletest-read-only

OPENMP_FLAG=-pthread -fopenmp

GTESTS=\
 test_omp.cpp\
 main.cpp

all: clean gtest-all
	./gtest-all

test_omp.obj: test_omp.cpp
	CXXFLAGS="$(OPENMP_FLAG) -I$(GTEST_DIR)/include" ../../admb -c -r -g $^

gtest-all: gtest-all.obj $(GTESTS)
	LDFLAGS="$(OPENMP_FLAG)" CXXFLAGS="$(OPENMP_FLAG) -I$(GTEST_DIR)/include" ../../admb -g -r $^

gtest-all.obj: googletest-read-only
	$(CXX) -c -g $(OPENMP_FLAG) -I$(GTEST_DIR)/include -I$(GTEST_DIR) -o $@ $(GTEST_DIR)/src/gtest-all.cc

googletest-read-only:
	svn checkout http://googletest.googlecode.com/svn/trunk/ googletest-read-only

clean:
	@rm -vf *.obj

all: simple.o tests

simple.o:
	make --directory=simple

gtest-all.o:
	g++ -c -std=c++11 -pthread -I../googletest-read-only -I../googletest-read-only/include  ../googletest-read-only/src/gtest-all.cc

tests: gtest-all.o tests_threaded_hessian_routine.cpp function_minimizer-hess_routine_threaded.cpp
	CXXFLAGS="-std=c++11 -I../googletest-read-only/include -Isimple" admb tests_threaded_hessian_routine.cpp gtest-all.o function_minimizer-hess_routine_threaded.cpp
	./tests_threaded_hessian_routine

clean:
	make --directory=simple clean
	rm -vf admodel.cov admodel.dep admodel.hes eigv.rpt fmin.log simple.log tests_threaded_hessian_routine variance

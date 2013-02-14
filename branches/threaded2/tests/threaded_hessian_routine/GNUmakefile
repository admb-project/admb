all: simple.o tests

simple.o:
	make --directory=simple

gtest-all.o:
	g++ -g -c -std=c++11 -pthread -I../googletest-read-only -I../googletest-read-only/include  ../googletest-read-only/src/gtest-all.cc

tests: clean gtest-all.o tests_threaded_hessian_routine.cpp function_minimizer-hess_routine_threaded.cpp
	CXXFLAGS="-g -std=c++11 -I../googletest-read-only/include -Isimple" admb tests_threaded_hessian_routine.cpp gtest-all.o function_minimizer-hess_routine_threaded.cpp
	./tests_threaded_hessian_routine

clean2:
	rm -vf *.tmp *.par *.std *.log *.bar *.cor *.cov *.hes
	rm -vf simple/*.log
	rm -vf simple/*.cor
	rm -vf simple/*.std
	rm -vf simple/*.eva
	rm -vf simple/*.par
	rm -vf simple/*.bar
	rm -vf simple/*.dep
	rm -vf simple/*.cov
	rm -vf simple/*.hes

clean: clean2
	#make --directory=simple clean
	rm -vf admodel.cov admodel.dep admodel.hes eigv.rpt fmin.log simple.log tests_threaded_hessian_routine variance

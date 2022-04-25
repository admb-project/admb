all: simple.dat
	CXXFLAGS=-I../include ../../../admb -c -o model_parameters.obj ../include/model_parameters.cpp
	CXXFLAGS=-I../include ../../../admb simple.cpp model_parameters.obj
	./simple

simple.dat:
	@cp ../../../examples/admb/simple/simple.dat .
	@cp ../../../examples/admb/simple/simple.dat simple.tpl

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf simple
	@rm -vf simple.bar
	@rm -vf simple.cor
	@rm -vf simple.eva
	@rm -vf simple.log
	@rm -vf simple.obj
	@rm -vf simple.out
	@rm -vf simple.par
	@rm -vf simple.std
	@rm -vf simple.dat
	@rm -vf simple.tpl
	@rm -vf model_parameters.obj

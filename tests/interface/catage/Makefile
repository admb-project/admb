all: catage.dat
	CXXFLAGS=-I../model_parameters ../../../admb catage.cpp ../model_parameters/model_parameters.cpp
	./catage

catage.dat:
	cp ../../../examples/admb/catage/catage.dat .

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf catage
	@rm -vf catage.dat
	@rm -vf catage.b01
	@rm -vf catage.b02
	@rm -vf catage.bar
	@rm -vf catage.cor
	@rm -vf catage.eva
	@rm -vf catage.log
	@rm -vf catage.p01
	@rm -vf catage.p02
	@rm -vf catage.par
	@rm -vf catage.r01
	@rm -vf catage.r02
	@rm -vf catage.rep
	@rm -vf catage.std
	@rm -vf catage.obj
	@rm -vf model_parameters.obj
	@rm -vf fmin.log

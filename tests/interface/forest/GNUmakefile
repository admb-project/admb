all:
	CXXFLAGS=-I../include ../../../admb -c -o model_parameters.obj ../include/model_parameters.cpp
	CXXFLAGS=-I../include ../../../admb forest.cpp model_parameters.obj
	$(MAKE) run

run: forest.dat
	./forest -output 1

forest.dat:
	cp ../../../examples/admb/forest/forest.dat .

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf forest
	@rm -vf forest.tpl
	@rm -vf forest.dat
	@rm -vf forest.b01
	@rm -vf forest.b02
	@rm -vf forest.bar
	@rm -vf forest.cor
	@rm -vf forest.eva
	@rm -vf forest.log
	@rm -vf forest.p01
	@rm -vf forest.p02
	@rm -vf forest.par
	@rm -vf forest.r01
	@rm -vf forest.r02
	@rm -vf forest.rep
	@rm -vf forest.std
	@rm -vf forest.obj
	@rm -vf model_parameters.obj
	@rm -vf fmin.log

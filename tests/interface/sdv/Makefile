all: sdv.dat
	CXXFLAGS=-I../model_parameters ../../../admb sdv.cpp
	./sdv

sdv.dat:
	cp ../../../examples/admb-re/sdv/sdv.dat .
	cp ../../../examples/admb-re/sdv/sdv.tpl .

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf sdv
	@rm -vf sdv.dat
	@rm -vf sdv.b01
	@rm -vf sdv.b02
	@rm -vf sdv.bar
	@rm -vf sdv.cor
	@rm -vf sdv.eva
	@rm -vf sdv.log
	@rm -vf sdv.p01
	@rm -vf sdv.p02
	@rm -vf sdv.par
	@rm -vf sdv.r01
	@rm -vf sdv.r02
	@rm -vf sdv.rep
	@rm -vf sdv.std
	@rm -vf sdv.obj
	@rm -vf model_parameters.obj
	@rm -vf fmin.log
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf sdv.bgs
	@rm -vf sdv.htp
	@rm -vf sdv.luu
	@rm -vf sdv.rhes
	@rm -vf sdv.tpl

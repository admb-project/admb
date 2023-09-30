all:
	$(MAKE) sdv.out
	$(MAKE) dev.out

dev.out:
	../../../admb -o dev model_parameters.cpp main.cpp
	cp ../../../examples/admb-re/sdv/sdv.dat dev.dat
	./dev > dev.out

sdv.out:
	cp ../../../examples/admb-re/sdv/sdv.dat .
	cp ../../../examples/admb-re/sdv/sdv.tpl .
	../../../admb sdv.tpl
	./sdv > sdv.out

diff:
	diff dev.cor sdv.cor
	diff dev.eva sdv.eva
	diff dev.log sdv.log
	diff dev.out sdv.out
	diff dev.p01 sdv.p01
	diff dev.par sdv.par
	diff dev.rhes sdv.rhes
	diff dev.std sdv.std

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf dev
	@rm -vf dev.b01
	@rm -vf dev.bar
	@rm -vf dev.bgs
	@rm -vf dev.cor
	@rm -vf dev.dat
	@rm -vf dev.eva
	@rm -vf dev.log
	@rm -vf dev.luu
	@rm -vf dev.out
	@rm -vf dev.p01
	@rm -vf dev.par
	@rm -vf dev.r01
	@rm -vf dev.rep
	@rm -vf dev.rhes
	@rm -vf dev.std
	@rm -vf fmin.log
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf main.obj
	@rm -vf model_parameters.obj
	@rm -vf sdv.out
	@rm -vf sdv
	@rm -vf sdv.b01
	@rm -vf sdv.bar
	@rm -vf sdv.bgs
	@rm -vf sdv.cor
	@rm -vf sdv.dat
	@rm -vf sdv.eva
	@rm -vf sdv.htp
	@rm -vf sdv.cpp
	@rm -vf sdv.log
	@rm -vf sdv.luu
	@rm -vf sdv.obj
	@rm -vf sdv.p01
	@rm -vf sdv.par
	@rm -vf sdv.r01
	@rm -vf sdv.rep
	@rm -vf sdv.rhes
	@rm -vf sdv.std
	@rm -vf sdv.tpl

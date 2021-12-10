all: sdv.dat
	../../../admb -o sdv model_parameters.cpp main.cpp
	./sdv

sdv.dat:
	cp ../../../examples/admb-re/sdv/sdv.dat .
	cp ../../../examples/admb-re/sdv/sdv.tpl .

diff:
	$(MAKE) --directory ../../../examples sdv
	-diff -w admodel.dep ../../../examples/admb-re/sdv/admodel.dep
	-diff -w sdv.log ../../../examples/admb-re/sdv/sdv.log
	-diff -w sdv.eva ../../../examples/admb-re/sdv/sdv.eva
	-diff -w hesscheck ../../../examples/admb-re/sdv/hesscheck
	-diff -w sdv.par ../../../examples/admb-re/sdv/sdv.par

diffs:
	diff -w sdv.rhes ../../../examples/admb-re/sdv/sdv.rhes
	diff -w sdv.p01 ../../../examples/admb-re/sdv/sdv.p01
	diff -w sdv.std ../../../examples/admb-re/sdv/sdv.std
	diff -w sdv.cor ../../../examples/admb-re/sdv/sdv.cor

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf main.obj
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

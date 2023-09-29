all:
	$(MAKE) fpe_test
	$(MAKE) fpe_test2
	$(MAKE) run

run:
	gdb --command=fpe_check.gdb fpe_test
	gdb --command=fpe_check2.gdb fpe_test2

fpe_test: fpe_test.dat
	../../admb -g fpe_test.tpl fpe_check.cpp

fpe_test2: fpe_test2.dat
	../../admb -g fpe_test2.tpl

fpe_test.dat:
	cp ../../examples/admb/simple/simple.dat fpe_test.dat

fpe_test2.dat:
	cp ../../examples/admb/simple/simple.dat fpe_test2.dat

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf cmpdiff1.tmp
	@rm -vf fmin.log
	@rm -vf fpe_check.obj
	@rm -vf fpe_test
	@rm -vf fpe_test.bar
	@rm -vf fpe_test.cor
	@rm -vf fpe_test.cpp
	@rm -vf fpe_test.dat
	@rm -vf fpe_test.eva
	@rm -vf fpe_test.htp
	@rm -vf fpe_test.log
	@rm -vf fpe_test.obj
	@rm -vf fpe_test.par
	@rm -vf fpe_test.std
	@rm -vf fpe_test2
	@rm -vf fpe_test2.cpp
	@rm -vf fpe_test2.dat
	@rm -vf fpe_test2.htp
	@rm -vf fpe_test2.log
	@rm -vf fpe_test2.obj
	@rm -vf gdb.output
	@rm -vf gdb.output2
	@rm -vf gradfil12.tmp
	@rm -vf gradfil22.tmp
	@rm -vf varssave2.tmp

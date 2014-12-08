all: simple
	$(MAKE) run

run: simple
	./simple
	mv simple.par simple.par.save
	./simple -lprof
	mv simple.par simple.par.lprof
	./simple -lprof -ainp simple.par.save
	cat simple.par simple.par.save simple.par.lprof

simple: simple.tpl simple.dat
	../../admb -g simple.tpl

simple.dat:
	cp ../../examples/admb/simple/simple.dat .

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf simple
	@rm -vf simple.dat
	@rm -vf simple.bar
	@rm -vf simple.cor
	@rm -vf simple.cpp
	@rm -vf simple.eva
	@rm -vf simple.htp
	@rm -vf simple.log
	@rm -vf simple.obj
	@rm -vf simple.par
	@rm -vf simple.par.save
	@rm -vf simple.par.lprof
	@rm -vf simple.std
	@rm -vf simple.prf
	@rm -vf variance
	@rm -vf dgs2
	@rm -vf diags
	@rm -vf est_a.plt
	@rm -vf est_b.plt
	@rm -vf cmpdiff.tmp gradfil1.tmp gradfil2.tmp varssave.tmp

get-outputs:
	cat dgs2
	cat diags
	cat est_a.plt
	cat est_b.plt
	cat simple.cor
	cat simple.dat
	cat simple.eva
	cat simple.log
	cat simple.par
	cat simple.prf
	cat simple.std

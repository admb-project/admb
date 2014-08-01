all: simple gdb.py
	gdb --python gdb.py

simple: simple.tpl simple.dat
	../../admb -g simple.tpl

simple.dat:
	cp ../../examples/admb/simple/simple.dat .

simple.tpl:
	cp ../../examples/admb/simple/simple.tpl .

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf simple
	@rm -vf simple.bar
	@rm -vf simple.cor
	@rm -vf simple.cpp
	@rm -vf simple.dat
	@rm -vf simple.eva
	@rm -vf simple.htp
	@rm -vf simple.log
	@rm -vf simple.obj
	@rm -vf simple.par
	@rm -vf simple.std
	@rm -vf simple.tpl
	@rm -vf variance

all:
	cp ../../../examples/admb/simple/simple.dat .
	../../../admb simple simple-functions.cpp
	time ./simple
clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf simple
	@rm -vf simple-functions.obj
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

all:
	$(MAKE) v5
	$(MAKE) v4
	$(MAKE) v3
	$(MAKE) v2
	$(MAKE) v1
v5:
	cp ../../../examples/admb/simple/simple.dat .
	../../../admb simple simple-functions-v5.cpp
	time ./simple
v4:
	cp ../../../examples/admb/simple/simple.dat .
	../../../admb simple simple-functions-v4.cpp
	time ./simple
v3:
	cp ../../../examples/admb/simple/simple.dat .
	../../../admb simple simple-functions-v3.cpp
	time ./simple
v2:
	cp ../../../examples/admb/simple/simple.dat .
	../../../admb simple simple-functions-v2.cpp
	time ./simple
v1:
	cp ../../../examples/admb/simple/simple.dat .
	../../../admb simple simple-functions-v1.cpp
	time ./simple
clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
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
	@rm -vf simple-functions-v1.obj
	@rm -vf simple-functions-v2.obj
	@rm -vf simple-functions-v3.obj
	@rm -vf simple-functions-v4.obj
	@rm -vf simple-functions-v5.obj

all:
	$(MAKE) v1
	$(MAKE) v2
	-$(MAKE) v3
	$(MAKE) v4dev
	$(MAKE) v4
v4dev:
	CXXFLAGS=-DDEV ../../../admb -g forest8 forest-functions-v4.cpp
	cp ../../../examples/admb/forest/forest.dat forest8.dat
	time ./forest8
v4:
	../../../admb -g forest8 forest-functions-v4.cpp
	cp ../../../examples/admb/forest/forest.dat forest8.dat
	time ./forest8
v3:
	../../../admb -g forest8 forest-functions-v3.cpp
	cp ../../../examples/admb/forest/forest.dat forest8.dat
	time ./forest8
v2:
	../../../admb forest8 forest-functions-v2.cpp
	cp ../../../examples/admb/forest/forest.dat forest8.dat
	time ./forest8
v1:
	../../../admb forest8 forest-functions-v1.cpp
	cp ../../../examples/admb/forest/forest.dat forest8.dat
	time ./forest8
clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf forest8
	@rm -vf forest8.b01
	@rm -vf forest8.bar
	@rm -vf forest8.cor
	@rm -vf forest8.cpp
	@rm -vf forest8.dat
	@rm -vf forest8.eva
	@rm -vf forest8.htp
	@rm -vf forest8.log
	@rm -vf forest8.obj
	@rm -vf forest8.out
	@rm -vf forest8.p01
	@rm -vf forest8.par
	@rm -vf forest8.r01
	@rm -vf forest8.rep
	@rm -vf forest8.std
	@rm -vf forest-functions-v1.obj
	@rm -vf forest-functions-v2.obj
	@rm -vf forest-functions-v3.obj
	@rm -vf forest-functions-v4.obj

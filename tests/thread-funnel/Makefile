default:
	$(MAKE) run8
all:
	$(MAKE) run0
	$(MAKE) run
	$(MAKE) run8
run0:
	cp ../../examples/admb/forest/forest.dat forest0.dat
	../../admb forest0
	time ./forest0
run:
	cp ../../examples/admb/forest/forest.dat .
	cp ../../examples/admb/forest/forest.tpl .
	../../admb forest
	time ./forest

run8:
	cp ../../examples/admb/forest/forest.dat forest8.dat
	../../admb forest8
	time ./forest8

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf forest
	@rm -vf forest.b01
	@rm -vf forest.bar
	@rm -vf forest.cor
	@rm -vf forest.cpp
	@rm -vf forest.dat
	@rm -vf forest.eva
	@rm -vf forest.htp
	@rm -vf forest.log
	@rm -vf forest.obj
	@rm -vf forest.out
	@rm -vf forest.p01
	@rm -vf forest.par
	@rm -vf forest.r01
	@rm -vf forest.rep
	@rm -vf forest.std
	@rm -vf forest.tpl
	@rm -vf forest0
	@rm -vf forest0.b01
	@rm -vf forest0.bar
	@rm -vf forest0.cor
	@rm -vf forest0.cpp
	@rm -vf forest0.dat
	@rm -vf forest0.eva
	@rm -vf forest0.htp
	@rm -vf forest0.log
	@rm -vf forest0.obj
	@rm -vf forest0.out
	@rm -vf forest0.p01
	@rm -vf forest0.par
	@rm -vf forest0.r01
	@rm -vf forest0.rep
	@rm -vf forest0.std

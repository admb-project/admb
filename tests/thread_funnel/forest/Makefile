
dev: run8j
run8j: thread_funnel5.h
	@cp ../../../examples/admb/forest/forest.dat .
	../../../admb forest.tpl thread_funnel5.cpp
	time ./forest &> forest.out

clean:
	@rm -vf forest.dat
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf forest
	@rm -vf forest.b01
	@rm -vf forest.bar
	@rm -vf forest.cor
	@rm -vf forest.cpp
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
	@rm -vf thread_funnel5.obj

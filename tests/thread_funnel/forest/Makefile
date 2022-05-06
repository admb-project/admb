
dev: run8j
run8j: thread_funnel5.h
	@cp ../../../examples/admb/forest/forest.dat .
	CXXFLAGS=-I../../interface/forest ../../../admb -g forest.tpl thread_funnel5.cpp
	time ./forest

	diff forest.par ~/admb-github/examples/admb/forest/forest.par
	diff forest.std ~/admb-github/examples/admb/forest/forest.std
	diff forest.rep ~/admb-github/examples/admb/forest/forest.rep
	diff forest.cor ~/admb-github/examples/admb/forest/forest.cor
	diff forest.eva ~/admb-github/examples/admb/forest/forest.eva

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
	@rm -vf cmpdiff1.tmp
	@rm -vf cmpdiff2.tmp
	@rm -vf cmpdiff3.tmp
	@rm -vf cmpdiff4.tmp
	@rm -vf gradfil11.tmp
	@rm -vf gradfil12.tmp
	@rm -vf gradfil13.tmp
	@rm -vf gradfil14.tmp
	@rm -vf gradfil21.tmp
	@rm -vf gradfil22.tmp
	@rm -vf gradfil23.tmp
	@rm -vf gradfil24.tmp
	@rm -vf varssave1.tmp
	@rm -vf varssave2.tmp
	@rm -vf varssave3.tmp
	@rm -vf varssave4.tmp
	@rm -vf cmpdiff.tmp
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf varssave.tmp

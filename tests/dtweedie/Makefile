all:
	$(MAKE) clean
	$(MAKE) R
	$(MAKE) tweedie

tweedie: tweedie.tpl dtweedie.cpp
	~/admb-github/build/admb/bin/admb -g tweedie.tpl dtweedie.cpp
	./tweedie

R:
	Rscript Tweedie_demo.R

clean:
	@rm -vf tweedie
	@rm -vf Tweedie_demo.o
	@rm -vf Tweedie_demo.so
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf tweedie.bar
	@rm -vf tweedie.cor
	@rm -vf tweedie.cpp
	@rm -vf tweedie.eva
	@rm -vf tweedie.htp
	@rm -vf tweedie.log
	@rm -vf tweedie.obj
	@rm -vf tweedie.par
	@rm -vf tweedie.std
	@rm -vf dtweedie.obj

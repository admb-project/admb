all:
	$(CXX) -o dat dat.cpp
	./dat > issue108.dat
	../../admb issue108.tpl
	./issue108
clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf core.113843
	@rm -vf fmin.log
	@rm -vf issue108
	@rm -vf dat
	@rm -vf issue108.bar
	@rm -vf issue108.cor
	@rm -vf issue108.cpp
	@rm -vf issue108.dat
	@rm -vf issue108.eva
	@rm -vf issue108.htp
	@rm -vf issue108.log
	@rm -vf issue108.obj
	@rm -vf issue108.par
	@rm -vf issue108.std

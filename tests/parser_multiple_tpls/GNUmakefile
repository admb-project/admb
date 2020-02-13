all:
	../../build/admb/bin/tpl2cpp forest.tpl h.tpl
	../../admb forest.cpp
	cp ../../examples/admb/forest/forest.dat .
	./forest

	$(MAKE) clean
all2:

	../../build/admb/bin/tpl2cpp forest h.tpl
	../../admb forest.cpp
	cp ../../examples/admb/forest/forest.dat .
	./forest
clean:
	rm -vf forest.dat admodel.cov admodel.dep admodel.hes fmin.log forest forest.b01 forest.bar forest.cor forest.cpp forest.eva forest.htp forest.log forest.obj forest.p01 forest.par forest.r01 forest.rep forest.std forest.tpl.cpp forest.tpl.htp

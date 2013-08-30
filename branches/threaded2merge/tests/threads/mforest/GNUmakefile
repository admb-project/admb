all: run

mforest: mforest.tpl
	../../../admb -g mforest

run: mforest
	-./mforest

clean:
	@rm -vf mforest
	@rm -vf variance
	@rm -vf log_master
	@rm -vf eigv.rpt
	@rm -vf mforest.log
	@rm -vf log_slave_6
	@rm -vf mforest.cpp
	@rm -vf fmin.log
	@rm -vf mforest.htp
	@rm -vf log_slave_*
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf mforest.b01
	@rm -vf mforest.bar
	@rm -vf mforest.p01
	@rm -vf mforest.par
	@rm -vf mforest.r01
	@rm -vf mforest.rep
	@rm -vf *.o

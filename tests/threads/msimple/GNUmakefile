msimple: msimple.tpl
	CXXFLAGS=-pthread LDFLAGS=-pthread ../../../admb -g msimple
	-./msimple
clean:
	@rm -vf msimple.log
	@rm -vf msimple.cpp
	@rm -vf variance
	@rm -vf log_slave_1
	@rm -vf log_master
	@rm -vf eigv.rpt
	@rm -vf msimple.htp
	@rm -vf fmin.log

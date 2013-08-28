mexample: mexample.tpl
	PATH=../../../build/dist/bin:$PATH CXXFLAGS=-pthread LDFLAGS=-pthread admb -g mexample

run:
	-./mexample

clean:
	@rm -vf variance
	@rm -vf mexample.log
	@rm -vf mexample.cpp
	@rm -vf gradfil2.tmp
	@rm -vf varssave.tmp
	@rm -vf log_slave_1
	@rm -vf log_slave_2
	@rm -vf log_master
	@rm -vf eigv.rpt
	@rm -vf mexample.htp
	@rm -vf mexample
	@rm -vf fmin.log
	@rm -vf gradfil1.tmp

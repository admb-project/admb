all:
	$(MAKE) run
	$(MAKE) run2
	$(MAKE) run3
	$(MAKE) run4

run:
	cp ../../examples/admb/simple/simple.dat .
	cp ../../examples/admb/simple/simple.tpl .
	../../admb simple &> /dev/null
	time ./simple &> simple.out
run2:
	cp ../../examples/admb/simple/simple.dat simple2.dat
	../../admb simple2 &> /dev/null
	time ./simple2 &> simple2.out
run3:
	cp ../../examples/admb/simple/simple.dat simple3.dat
	../../admb simple3 &> /dev/null
	time ./simple3 &> simple3.out
run4:
	cp ../../examples/admb/simple/simple.dat simple4.dat
	../../admb simple4 &> /dev/null
	time ./simple4 &> simple4.out
clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf simple3
	@rm -vf simple3.bar
	@rm -vf simple3.cor
	@rm -vf simple3.cpp
	@rm -vf simple3.eva
	@rm -vf simple3.htp
	@rm -vf simple3.log
	@rm -vf simple3.obj
	@rm -vf simple3.par
	@rm -vf simple3.std
	@rm -vf simple3.dat

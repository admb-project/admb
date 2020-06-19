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
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf simple
	@rm -vf simple.bar
	@rm -vf simple.cor
	@rm -vf simple.cpp
	@rm -vf simple.dat
	@rm -vf simple.eva
	@rm -vf simple.htp
	@rm -vf simple.log
	@rm -vf simple.obj
	@rm -vf simple.out
	@rm -vf simple.par
	@rm -vf simple.std
	@rm -vf simple.tpl
	@rm -vf simple2
	@rm -vf simple2.bar
	@rm -vf simple2.cor
	@rm -vf simple2.cpp
	@rm -vf simple2.dat
	@rm -vf simple2.eva
	@rm -vf simple2.htp
	@rm -vf simple2.log
	@rm -vf simple2.obj
	@rm -vf simple2.out
	@rm -vf simple2.par
	@rm -vf simple2.std
	@rm -vf simple3
	@rm -vf simple3.bar
	@rm -vf simple3.cor
	@rm -vf simple3.cpp
	@rm -vf simple3.dat
	@rm -vf simple3.eva
	@rm -vf simple3.htp
	@rm -vf simple3.log
	@rm -vf simple3.obj
	@rm -vf simple3.out
	@rm -vf simple3.par
	@rm -vf simple3.std
	@rm -vf simple4
	@rm -vf simple4.bar
	@rm -vf simple4.cor
	@rm -vf simple4.cpp
	@rm -vf simple4.dat
	@rm -vf simple4.eva
	@rm -vf simple4.htp
	@rm -vf simple4.log
	@rm -vf simple4.obj
	@rm -vf simple4.out
	@rm -vf simple4.par
	@rm -vf simple4.std

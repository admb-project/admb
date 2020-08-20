all:
	$(MAKE) run0
	$(MAKE) run
	$(MAKE) run2
	$(MAKE) run3
	$(MAKE) run4
	$(MAKE) run5
	$(MAKE) run6
	$(MAKE) run6a
	$(MAKE) run6b
	$(MAKE) run6c
	$(MAKE) run6d
	$(MAKE) run6e
	$(MAKE) run7
	$(MAKE) run8
run0:
	cp ../../examples/admb/forest/forest.dat forest0.dat
	../../admb forest0 &> /dev/null
	time ./forest0 &> forest0.out
run:
	cp ../../examples/admb/forest/forest.dat .
	cp ../../examples/admb/forest/forest.tpl .
	../../admb forest &> /dev/null
	time ./forest &> forest.out

run2:
	../../admb forest2 &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest2.dat
	time ./forest2 &> forest2.out
run3:
	../../admb forest3 &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest3.dat
	time ./forest3 &> forest3.out
run4:
	../../admb forest4 &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest4.dat
	time ./forest4 &> forest4.out
run5:
	../../admb forest5 &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest5.dat
	time ./forest5 &> forest5.out
run6:
	 ../../admb forest6 &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest6.dat
	time ./forest6 &> forest6.out
run6a:
	../../admb forest6a &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest6a.dat
	time ./forest6a &> forest6a.out
run6b:
	../../admb forest6b &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest6b.dat
	time ./forest6b &> forest6b.out
run6c:
	../../admb forest6c &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest6c.dat
	time ./forest6c &> forest6c.out
run6d:
	../../admb forest6d &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest6d.dat
	time ./forest6d &> forest6d.out
run6e:
	../../admb forest6e &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest6e.dat
	time ./forest6e &> forest6e.out
run7:
	../../admb forest7 &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest7.dat
	time ./forest7 &> forest7.out
run8:
	../../admb forest8 &> /dev/null
	cp ../../examples/admb/forest/forest.dat forest8.dat
	time ./forest8 &> forest8.out
clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf forest
	@rm -vf forest.b01
	@rm -vf forest.bar
	@rm -vf forest.cor
	@rm -vf forest.cpp
	@rm -vf forest.dat
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
	@rm -vf forest.tpl
	@rm -vf forest0
	@rm -vf forest0.b01
	@rm -vf forest0.bar
	@rm -vf forest0.cor
	@rm -vf forest0.cpp
	@rm -vf forest0.dat
	@rm -vf forest0.eva
	@rm -vf forest0.htp
	@rm -vf forest0.log
	@rm -vf forest0.obj
	@rm -vf forest0.out
	@rm -vf forest0.p01
	@rm -vf forest0.par
	@rm -vf forest0.r01
	@rm -vf forest0.rep
	@rm -vf forest0.std

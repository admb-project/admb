all:
	$(MAKE) run0
	$(MAKE) run
	$(MAKE) run8
	$(MAKE) run8b
	$(MAKE) run8c
	$(MAKE) run8d
	$(MAKE) run8e
	$(MAKE) run8f
	$(MAKE) run8g
	$(MAKE) run8h
	$(MAKE) run8i
	$(MAKE) run8i4
	$(MAKE) run8j

run0:
	@cp ../../examples/admb/forest/forest.dat forest0.dat
	../../admb forest0
	time ./forest0 &> forest0.out
run:
	@cp ../../examples/admb/forest/forest.dat .
	../../admb forest
	time ./forest &> forest.out

run8:
	@cp ../../examples/admb/forest/forest.dat forest8.dat
	../../admb forest8
	time ./forest8 &> forest8.out

run8b:
	@cp ../../examples/admb/forest/forest.dat forest8b.dat
	../../admb forest8b
	time ./forest8b &> forest8b.out

run8c:
	@cp ../../examples/admb/forest/forest.dat forest8c.dat
	../../admb forest8c
	time ./forest8c &> forest8c.out

run8d:
	@cp ../../examples/admb/forest/forest.dat forest8d.dat
	../../admb forest8d
	time ./forest8d &> forest8d.out

run8e:
	@cp ../../examples/admb/forest/forest.dat forest8e.dat
	../../admb forest8e
	time ./forest8e &> forest8e.out

run8f:
	@cp ../../examples/admb/forest/forest.dat forest8f.dat
	../../admb forest8f
	time ./forest8f &> forest8f.out
run8g:
	@cp ../../examples/admb/forest/forest.dat forest8g.dat
	../../admb forest8g thread-funnel.cpp
	time ./forest8g &> forest8g.out

run8h:
	@cp ../../examples/admb/forest/forest.dat forest8h.dat
	../../admb forest8h thread_funnel.cpp
	time ./forest8h &> forest8h.out

run8i:
	@cp ../../examples/admb/forest/forest.dat forest8i.dat
	../../admb forest8i thread_funnel3.cpp
	time ./forest8i &> forest8i.out

run8i4: thread_funnel4.h
	@cp ../../examples/admb/forest/forest.dat forest8i4.dat
	../../admb forest8i4.tpl thread_funnel4.cpp
	time ./forest8i4 &> forest8i4.out
	cat forest8i4.out

dev: run8j
run8j: thread_funnel5.h
	@cp ../../examples/admb/forest/forest.dat forest8j.dat
	../../admb forest8j.tpl thread_funnel5.cpp
	time ./forest8j &> forest8j.out
	cat forest8j.out

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
	@rm -vf forest8
	@rm -vf forest8.b01
	@rm -vf forest8.bar
	@rm -vf forest8.cor
	@rm -vf forest8.cpp
	@rm -vf forest8.dat
	@rm -vf forest8.eva
	@rm -vf forest8.htp
	@rm -vf forest8.log
	@rm -vf forest8.obj
	@rm -vf forest8.out
	@rm -vf forest8.p01
	@rm -vf forest8.par
	@rm -vf forest8.r01
	@rm -vf forest8.rep
	@rm -vf forest8.std
	@rm -vf forest8b
	@rm -vf forest8b.b01
	@rm -vf forest8b.bar
	@rm -vf forest8b.cor
	@rm -vf forest8b.cpp
	@rm -vf forest8b.dat
	@rm -vf forest8b.eva
	@rm -vf forest8b.htp
	@rm -vf forest8b.log
	@rm -vf forest8b.obj
	@rm -vf forest8b.out
	@rm -vf forest8b.p01
	@rm -vf forest8b.par
	@rm -vf forest8b.r01
	@rm -vf forest8b.rep
	@rm -vf forest8b.std
	@rm -vf forest8c
	@rm -vf forest8c.b01
	@rm -vf forest8c.bar
	@rm -vf forest8c.cor
	@rm -vf forest8c.cpp
	@rm -vf forest8c.dat
	@rm -vf forest8c.eva
	@rm -vf forest8c.htp
	@rm -vf forest8c.log
	@rm -vf forest8c.obj
	@rm -vf forest8c.out
	@rm -vf forest8c.p01
	@rm -vf forest8c.par
	@rm -vf forest8c.r01
	@rm -vf forest8c.rep
	@rm -vf forest8c.std
	@rm -vf forest8d
	@rm -vf forest8d.b01
	@rm -vf forest8d.bar
	@rm -vf forest8d.cor
	@rm -vf forest8d.cpp
	@rm -vf forest8d.dat
	@rm -vf forest8d.eva
	@rm -vf forest8d.htp
	@rm -vf forest8d.log
	@rm -vf forest8d.obj
	@rm -vf forest8d.out
	@rm -vf forest8d.p01
	@rm -vf forest8d.par
	@rm -vf forest8d.r01
	@rm -vf forest8d.rep
	@rm -vf forest8d.std
	@rm -vf forest8e
	@rm -vf forest8e.b01
	@rm -vf forest8e.bar
	@rm -vf forest8e.cor
	@rm -vf forest8e.cpp
	@rm -vf forest8e.dat
	@rm -vf forest8e.eva
	@rm -vf forest8e.htp
	@rm -vf forest8e.log
	@rm -vf forest8e.obj
	@rm -vf forest8e.out
	@rm -vf forest8e.p01
	@rm -vf forest8e.par
	@rm -vf forest8e.r01
	@rm -vf forest8e.rep
	@rm -vf forest8e.std
	@rm -vf forest8f
	@rm -vf forest8f.b01
	@rm -vf forest8f.bar
	@rm -vf forest8f.cor
	@rm -vf forest8f.cpp
	@rm -vf forest8f.dat
	@rm -vf forest8f.eva
	@rm -vf forest8f.htp
	@rm -vf forest8f.log
	@rm -vf forest8f.obj
	@rm -vf forest8f.out
	@rm -vf forest8f.p01
	@rm -vf forest8f.par
	@rm -vf forest8f.r01
	@rm -vf forest8f.rep
	@rm -vf forest8f.std
	@rm -vf forest8g
	@rm -vf forest8g.b01
	@rm -vf forest8g.bar
	@rm -vf forest8g.cor
	@rm -vf forest8g.cpp
	@rm -vf forest8g.dat
	@rm -vf forest8g.eva
	@rm -vf forest8g.htp
	@rm -vf forest8g.log
	@rm -vf forest8g.obj
	@rm -vf forest8g.out
	@rm -vf forest8g.p01
	@rm -vf forest8g.par
	@rm -vf forest8g.r01
	@rm -vf forest8g.rep
	@rm -vf forest8g.std
	@rm -vf cmpdiff.tmp
	@rm -vf cmpdiff1.tmp
	@rm -vf cmpdiff2.tmp
	@rm -vf cmpdiff3.tmp
	@rm -vf gradfil1.tmp
	@rm -vf gradfil11.tmp
	@rm -vf gradfil12.tmp
	@rm -vf gradfil13.tmp
	@rm -vf gradfil2.tmp
	@rm -vf gradfil21.tmp
	@rm -vf gradfil22.tmp
	@rm -vf gradfil23.tmp
	@rm -vf varssave.tmp
	@rm -vf varssave1.tmp
	@rm -vf varssave2.tmp
	@rm -vf varssave3.tmp
	@rm -vf cmpdiff4.tmp
	@rm -vf forest8h
	@rm -vf forest8h.b01
	@rm -vf forest8h.bar
	@rm -vf forest8h.cor
	@rm -vf forest8h.cpp
	@rm -vf forest8h.dat
	@rm -vf forest8h.eva
	@rm -vf forest8h.htp
	@rm -vf forest8h.log
	@rm -vf forest8h.obj
	@rm -vf forest8h.out
	@rm -vf forest8h.p01
	@rm -vf forest8h.par
	@rm -vf forest8h.r01
	@rm -vf forest8h.rep
	@rm -vf forest8h.std
	@rm -vf gradfil14.tmp
	@rm -vf gradfil24.tmp
	@rm -vf varssave4.tmp
	@rm -vf forest8i
	@rm -vf forest8i.b01
	@rm -vf forest8i.bar
	@rm -vf forest8i.cor
	@rm -vf forest8i.cpp
	@rm -vf forest8i.dat
	@rm -vf forest8i.eva
	@rm -vf forest8i.htp
	@rm -vf forest8i.log
	@rm -vf forest8i.obj
	@rm -vf forest8i.out
	@rm -vf forest8i.p01
	@rm -vf forest8i.par
	@rm -vf forest8i.r01
	@rm -vf forest8i.rep
	@rm -vf forest8i.std
	@rm -vf thread_funnel.obj
	@rm -vf thread_funnel2.obj
	@rm -vf thread_funnel3.obj
	@rm -vf thread-funnel.obj
	@rm -vf forest8i4
	@rm -vf forest8i4.b01
	@rm -vf forest8i4.bar
	@rm -vf forest8i4.cor
	@rm -vf forest8i4.dat
	@rm -vf forest8i4.eva
	@rm -vf forest8i4.log
	@rm -vf forest8i4.out
	@rm -vf forest8i4.p01
	@rm -vf forest8i4.par
	@rm -vf forest8i4.r01
	@rm -vf forest8i4.rep
	@rm -vf forest8i4.std
	@rm -vf thread_funnel4.obj
	@rm -vf forest8i4.cpp
	@rm -vf forest8i4.htp
	@rm -vf forest8i4.obj
	@rm -vf forest8j
	@rm -vf forest8j.b01
	@rm -vf forest8j.bar
	@rm -vf forest8j.cor
	@rm -vf forest8j.cpp
	@rm -vf forest8j.dat
	@rm -vf forest8j.eva
	@rm -vf forest8j.htp
	@rm -vf forest8j.log
	@rm -vf forest8j.obj
	@rm -vf forest8j.out
	@rm -vf forest8j.p01
	@rm -vf forest8j.par
	@rm -vf forest8j.r01
	@rm -vf forest8j.rep
	@rm -vf forest8j.std
	@rm -vf thread_funnel5.obj

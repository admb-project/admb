all:
	$(MAKE) clean
	../../../admb s1.cpp
	../../../admb simple.cpp fcomp_s.cpp
	../../../admb simple2.cpp fcomp_s.cpp
	../../../admb simp1.cpp fcomp_s.cpp
	$(MAKE) run

run:
	./s1
	./simple
	./simple2
	./simp1

clean:
	@rm -vf *.obj
	@rm -vf s1
	@rm -vf simple
	@rm -vf simp1
	@rm -vf simple2
	@rm -vf fmin.log

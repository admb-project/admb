GTEST_DIR=../../googletest-read-only

all: clean run

msimple.cpp: msimple.tpl
	../../../admb -g msimple

tests_msimple: msimple.cpp tests_msimple.cpp
	cp $(GTEST_DIR)/gtest-all.o .
	CXXFLAGS="-I$(GTEST_DIR)/include" ../../../admb -g tests_msimple.cpp main.cpp gtest-all.o

run: tests_msimple
	-./tests_msimple

clean:
	@rm -vf msimple.log
	@rm -vf msimple.cpp
	@rm -vf variance
	@rm -vf log_slave_*
	@rm -vf log_master
	@rm -vf eigv.rpt
	@rm -vf msimple.htp
	@rm -vf msimple
	@rm -vf fmin.log
	@rm -vf tests_msimple
	@rm -vf msimple.eva
	@rm -vf admodel.hes
	@rm -vf admodel.dep
	@rm -vf msimple.par
	@rm -vf msimple.cor
	@rm -vf admodel.cov
	@rm -vf msimple.rep
	@rm -vf msimple.std
	@rm -vf msimple.bar
	@rm -vf *.o
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf varssave.tmp

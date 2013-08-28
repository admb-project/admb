GTEST_DIR=../../googletest-read-only

all: tests_msimple

msimple.cpp: msimple.tpl
	PATH=../../../build/dist/bin:$(PATH) CXXFLAGS=-pthread LDFLAGS=-pthread admb -g msimple

tests_msimple: msimple.cpp tests_msimple.cpp
	cp $(GTEST_DIR)/gtest-all.o .
	CXXFLAGS="-pthread -I$(GTEST_DIR)/include" LDFLAGS=-pthread ../../../admb -g tests_msimple.cpp main.cpp gtest-all.o

run:
	-./tests_msimple

clean:
	@rm -vf msimple.log
	@rm -vf msimple.cpp
	@rm -vf variance
	@rm -vf log_slave_1
	@rm -vf log_master
	@rm -vf eigv.rpt
	@rm -vf msimple.htp
	@rm -vf msimple
	@rm -vf fmin.log
	@rm -vf tests_msimple

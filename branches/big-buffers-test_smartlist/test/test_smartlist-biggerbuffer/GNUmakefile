.PHONY: run

GTEST_DIR=/home/johnoel/googletest-read-only

TARGET=biggerbuffer
TARGET_TPL=binomial

all: clean $(TARGET_TPL) tests_$(TARGET) run_tests

gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	g++ -c -g -DGTEST_HAS_PTHREAD=0 -I$(GTEST_DIR)/include -I$(GTEST_DIR) $(GTEST_DIR)/src/gtest-all.cc

tests_$(TARGET): tests_$(TARGET).o gtest-all.o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; adlink -g ${OPTIONS} tests_$(TARGET) gtest-all.o

tests_$(TARGET).o: tests_$(TARGET).cpp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS="-I$(GTEST_DIR) -I$(GTEST_DIR)/include" adcomp -g ${OPTIONS} tests_$(TARGET)

$(TARGET_TPL): $(TARGET_TPL).tpl $(TARGET_TPL).pin
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -r -s -g $(TARGET_TPL)

run:
	@printf "Started run:\n"
	@#./$(TARGET) -ams 10000000 -ind subset.dat -gbs 1000000000 -noinit -ilmn 5 -l1 200000000000 -nl1 10000000000
	@#./$(TARGET) -ams 10000000 -ind subset.dat -gbs 1000000000 -noinit -ilmn 5 -l1 10000000 -nl1 10000000
	@printf "Finished run.\n"

run_tests:
	@printf "Started run tests:\n"
	./tests_$(TARGET)
	@printf "Finished run tests.\n"

clean:
	@rm -vf $(TARGET_TPL)
	@rm -vf admodel.*
	@rm -vf *.o
	@rm -vf variance
	@rm -vf fmin.log
	@rm -vf $(TARGET_TPL).eva
	@rm -vf $(TARGET_TPL).bar
	@rm -vf $(TARGET_TPL).bgs
	@rm -vf $(TARGET_TPL).cor
	@rm -vf $(TARGET_TPL).log
	@rm -vf $(TARGET_TPL).o
	@rm -vf $(TARGET_TPL).cpp
	@rm -vf $(TARGET_TPL).htp
	@rm -vf $(TARGET_TPL).par
	@rm -vf $(TARGET_TPL).std
	@rm -vf $(TARGET_TPL).luu
	@rm -vf $(TARGET_TPL).rep
	@rm -vf $(TARGET_TPL).rhes
	@rm -vf tests_$(TARGET).o
	@rm -vf tests_$(TARGET)
	@rm -vf eigv.rpt
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf nf1b2list12
	@rm -vf f1b2list1
	@rm -vf nf1b2list13
	@rm -vf nf1b2list1
	@rm -vf minto.rhes
	@rm -vf f1b2list12
	@rm -vf f1b2list13
	@rm -vf beta_deviate.log

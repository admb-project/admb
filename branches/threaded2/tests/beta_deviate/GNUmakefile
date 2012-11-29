.PHONY: run

TARGET=minto

all: clean $(TARGET) run tests_$(TARGET) run_tests

tests_$(TARGET): tests_$(TARGET).o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; LDFLAGS=" `gtest-config --ldflags --libs` " adlink -g ${OPTIONS} tests_$(TARGET)

tests_$(TARGET).o: $(TARGET).cpp $(TARGET).htp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; adcomp -g ${OPTIONS} tests_$(TARGET)

$(TARGET): $(TARGET).tpl $(TARGET).dat
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -r -s -g $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET)
	@printf "Finished run.\n"

run_tests:
	@printf "Started run tests:\n"
	./tests_$(TARGET)
	@printf "Finished run tests.\n"

clean:
	@rm -vf $(TARGET)
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf fmin.log
	@rm -vf $(TARGET).eva
	@rm -vf $(TARGET).htp
	@rm -vf $(TARGET).bar
	@rm -vf $(TARGET).bgs
	@rm -vf $(TARGET).cor
	@rm -vf $(TARGET).cpp
	@rm -vf $(TARGET).log
	@rm -vf $(TARGET).o
	@rm -vf $(TARGET).par
	@rm -vf $(TARGET).std
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

.PHONY: run

TARGET=beta1

all: clean $(TARGET) run test_$(TARGET) run_tests

test_$(TARGET): test_$(TARGET).o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; LDFLAGS=" `gtest-config --ldflags --libs` " adlink -g ${OPTIONS} test_$(TARGET)

test_$(TARGET).o: $(TARGET).cpp $(TARGET).htp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; adcomp -g ${OPTIONS} test_$(TARGET)

$(TARGET): $(TARGET).tpl $(TARGET).dat
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -s -g $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET)
	@printf "Finished run.\n"

run_tests:
	@printf "Started run tests:\n"
	./test_$(TARGET)
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
	@rm -vf test_$(TARGET).o
	@rm -vf test_$(TARGET)
	@rm -vf eigv.rpt

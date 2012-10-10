.PHONY: clean run

TARGET=adstring_array

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -s $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET)
	@printf "Finished run.\n"

clean:
	@rm -f admodel.cov
	@rm -f admodel.hes
	@rm -f fmin.log
	@rm -f $(TARGET)
	@rm -f $(TARGET).cor
	@rm -f $(TARGET).eva
	@rm -f $(TARGET).log
	@rm -f $(TARGET).par
	@rm -f $(TARGET).std
	@rm -f sims
	@rm -f admodel.dep
	@rm -f eigv.rpt
	@rm -f $(TARGET).bar
	@rm -f $(TARGET).cpp
	@rm -f $(TARGET).htp
	@rm -f $(TARGET).o
	@rm -f $(TARGET).psv
	@rm -f variance

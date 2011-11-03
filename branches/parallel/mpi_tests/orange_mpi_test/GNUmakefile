.PHONY: run

TARGET=orange

all: clean $(TARGET) run

debug: clean $(TARGET)-g

$(TARGET)-g: $(TARGET).tpl $(TARGET).dat
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -g -r $(TARGET)


$(TARGET): $(TARGET).tpl $(TARGET).dat
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -s -r $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET)
	@printf "Finished run.\n"
	@printf "Type './orange -master' to run using MPI.\n"

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
	@rm -vf $(TARGET).rhes
	@rm -vf $(TARGET).p01
	@rm -vf $(TARGET).b01
	@rm -vf $(TARGET).r01
	@rm -vf $(TARGET).rep
	@rm -vf eigv.rpt
	@rm -vf cmpdiff.*
	@rm -vf gradfil1.*
	@rm -vf hesscheck
	@rm -vf hessian.bin

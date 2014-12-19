.PHONY: run

TARGET=dfsolve2

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl $(TARGET).dat
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -r -s $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET) -nohess; cat $(TARGET).par $(TARGET).rep > $(TARGET).temp; mv $(TARGET).temp $(TARGET).par
	@printf "Finished run.\n"

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
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).rhes
	@rm -vf $(TARGET).rep
	@rm -vf eigv.rpt
	@rm -vf hesscheck
	@rm -vf hessian.bin

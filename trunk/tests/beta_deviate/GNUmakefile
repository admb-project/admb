TARGET=minto

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl $(TARGET).dat
	../../admb -r -g $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET)
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
	@rm -vf $(TARGET).obj
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

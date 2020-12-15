.PHONY: clean run

TARGET=simple

all: clean
	$(MAKE) run

$(TARGET):
	../../admb -g $(TARGET)

run: $(TARGET)
	@printf "Started run:\n"
	cp ../../examples/admb/simple/simple.dat .
	./$(TARGET)
	@printf "Finished run.\n"

clean:
	@rm -vf header.tmp
	@rm -vf xxalloc.tmp
	@rm -vf xxglobal.tmp
	@rm -vf xxhtop.tmp
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf fmin.log
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf $(TARGET)
	@rm -vf $(TARGET).bar
	@rm -vf $(TARGET).bgs
	@rm -vf $(TARGET).cor
	@rm -vf $(TARGET).cpp
	@rm -vf $(TARGET).ecm
	@rm -vf $(TARGET).eva
	@rm -vf $(TARGET).hst
	@rm -vf $(TARGET).htp
	@rm -vf $(TARGET).log
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).mc2
	@rm -vf $(TARGET).mcm
	@rm -vf $(TARGET).obj
	@rm -vf $(TARGET).par
	@rm -vf $(TARGET).psv
	@rm -vf $(TARGET).rhes
	@rm -vf $(TARGET).std
	@rm -vf $(TARGET).dat
	@rm -vf sims

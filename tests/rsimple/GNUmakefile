.PHONY: clean run

TARGET=rsimple

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
	../../admb -g $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET) -mcmc 10000 -mcsave 100
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
	@rm -vf rsimple
	@rm -vf rsimple.bar
	@rm -vf rsimple.bgs
	@rm -vf rsimple.cor
	@rm -vf rsimple.cpp
	@rm -vf rsimple.ecm
	@rm -vf rsimple.eva
	@rm -vf rsimple.hst
	@rm -vf rsimple.htp
	@rm -vf rsimple.log
	@rm -vf rsimple.luu
	@rm -vf rsimple.mc2
	@rm -vf rsimple.mcm
	@rm -vf rsimple.obj
	@rm -vf rsimple.par
	@rm -vf rsimple.psv
	@rm -vf rsimple.rhes
	@rm -vf rsimple.std
	@rm -vf sims

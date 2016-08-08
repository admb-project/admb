ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=theta

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET) -nonit -mcmc 1000 -mcsave 10
else
	./$(TARGET) -nonit -mcmc 1000 -mcsave 10
endif

clean:
ifeq ($(SHELL),cmd)
	@del hybrid_seed
	@del theta.obj
	@del admodel.cov
	@del admodel.hes
	@del fmin.log
	@del theta
	@del theta.exe
	@del theta.cor
	@del theta.eva
	@del theta.log
	@del theta.par
	@del theta.std
	@del sims
	@del admodel.dep
	@del eigv.rpt
	@del theta.bar
	@del theta.cpp
	@del theta.htp
	@del theta.o
	@del theta.psv
	@del variance
	@del hessian.bin
	@del theta.hst
	@del theta.mc2
	@del theta.rhes
	@del hesscheck
	@del theta.bgs
	@del theta.ecm
	@del theta.luu
	@del theta.mcm
else
	@rm -f hybrid_seed
	@rm -f theta.obj
	@rm -f admodel.cov
	@rm -f admodel.hes
	@rm -f fmin.log
	@rm -f theta
	@rm -f theta.cor
	@rm -f theta.eva
	@rm -f theta.log
	@rm -f theta.par
	@rm -f theta.std
	@rm -f sims
	@rm -f admodel.dep
	@rm -f eigv.rpt
	@rm -f theta.bar
	@rm -f theta.cpp
	@rm -f theta.htp
	@rm -f theta.o
	@rm -f theta.psv
	@rm -f variance
	@rm -f hessian.bin
	@rm -f theta.hst
	@rm -f theta.mc2
	@rm -f theta.rhes
	@rm -f hesscheck
	@rm -f theta.bgs
	@rm -f theta.ecm
	@rm -f theta.luu
	@rm -f theta.mcm
endif

ifeq ($(TERM),cygwin)
else
ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif
endif

TARGET=simple_mcmc

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET) -mcmc 1000 -mcsave 10
	$(TARGET) -mceval
else
	./$(TARGET) -mcmc 1000 -mcsave 10
	./$(TARGET) -mceval
endif

clean:
ifeq ($(SHELL),cmd)
	@del admodel.cov
	@del admodel.hes
	@del fmin.log
	@del $(TARGET).cor
	@del $(TARGET).eva
	@del $(TARGET).log
	@del $(TARGET).par
	@del $(TARGET).std
	@del sims
	@del admodel.dep
	@del eigv.rpt
	@del $(TARGET).bar
	@del $(TARGET).cpp
	@del $(TARGET).htp
	@del $(TARGET).o
	@del $(TARGET).obj
	@del $(TARGET).psv
	@del variance
	@del posteriors.rep
	@del $(TARGET).ecm
	@del $(TARGET).hst
	@del $(TARGET).mc2
	@del $(TARGET).mcm
	@del $(TARGET).exe
	@del $(TARGET)
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del eigv.rpt
	@del fmin.log
	@del posteriors.rep
	@del simple_mcmc.bar
	@del simple_mcmc.cor
	@del simple_mcmc.cpp
	@del simple_mcmc.ecm
	@del simple_mcmc.eva
	@del simple_mcmc.exe
	@del simple_mcmc.hst
	@del simple_mcmc.htp
	@del simple_mcmc.log
	@del simple_mcmc.mc2
	@del simple_mcmc.mcm
	@del simple_mcmc.obj
	@del simple_mcmc.par
	@del simple_mcmc.psv
	@del simple_mcmc.std
	@del sims
	@del variance
else
	@rm -f admodel.cov
	@rm -f admodel.hes
	@rm -f fmin.log
	@rm -vf $(TARGET)
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
	@rm -f $(TARGET).obj
	@rm -f $(TARGET).psv
	@rm -f variance
	@rm -f posteriors.rep
	@rm -f $(TARGET).ecm
	@rm -f $(TARGET).hst
	@rm -f $(TARGET).mc2
	@rm -f $(TARGET).mcm
	@rm -f $(TARGET)
endif

get-outputs:
ifeq ($(SHELL),cmd)
	type simple_mcmc.cor
	type simple_mcmc.eva
	type simple_mcmc.par
	type simple_mcmc.std
	type sims
else
	cat simple_mcmc.cor
	cat simple_mcmc.eva
	cat simple_mcmc.par
	cat simple_mcmc.std
	cat sims
endif

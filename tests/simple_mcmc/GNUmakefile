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
	@del admodel.cov 2>nul
	@del admodel.hes 2>nul
	@del fmin.log 2>nul
	@del $(TARGET).cor 2>nul
	@del $(TARGET).eva 2>nul
	@del $(TARGET).log 2>nul
	@del $(TARGET).par 2>nul
	@del $(TARGET).std 2>nul
	@del sims 2>nul
	@del admodel.dep 2>nul
	@del eigv.rpt 2>nul
	@del $(TARGET).bar 2>nul
	@del $(TARGET).cpp 2>nul
	@del $(TARGET).htp 2>nul
	@del $(TARGET).o 2>nul
	@del $(TARGET).obj 2>nul
	@del $(TARGET).psv 2>nul
	@del variance 2>nul
	@del posteriors.rep 2>nul
	@del $(TARGET).ecm 2>nul
	@del $(TARGET).hst 2>nul
	@del $(TARGET).mc2 2>nul
	@del $(TARGET).mcm 2>nul
	@del $(TARGET).exe 2>nul
	@del $(TARGET) 2>nul
	@del admodel.cov 2>nul
	@del admodel.dep 2>nul
	@del admodel.hes 2>nul
	@del eigv.rpt 2>nul
	@del fmin.log 2>nul
	@del posteriors.rep 2>nul
	@del simple_mcmc.bar 2>nul
	@del simple_mcmc.cor 2>nul
	@del simple_mcmc.cpp 2>nul
	@del simple_mcmc.ecm 2>nul
	@del simple_mcmc.eva 2>nul
	@del simple_mcmc.exe 2>nul
	@del simple_mcmc.hst 2>nul
	@del simple_mcmc.htp 2>nul
	@del simple_mcmc.log 2>nul
	@del simple_mcmc.mc2 2>nul
	@del simple_mcmc.mcm 2>nul
	@del simple_mcmc.obj 2>nul
	@del simple_mcmc.par 2>nul
	@del simple_mcmc.psv 2>nul
	@del simple_mcmc.std 2>nul
	@del sims 2>nul
	@del variance 2>nul
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

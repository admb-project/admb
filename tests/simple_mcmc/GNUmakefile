ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  endif
endif

TARGET=simple_mcmc

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb$(EXT) $(TARGET)
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
else
	@rm -f admodel.cov
	@rm -f admodel.hes
	@rm -f fmin.log
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

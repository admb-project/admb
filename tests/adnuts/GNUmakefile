TARGET=adnuts

ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring sh.exe,$(shell where sh.exe 2>&1 | findstr sh.exe)),sh.exe)
      EXT=.sh
    else
      SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
endif

all:
	$(MAKE) clean
	$(MAKE) run

run: $(TARGET) output_psv
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -nuts -hbf -mcmc 2000 -mcseed 12
	output_psv adnuts.psv > adnuts_psv.txt
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest -mcseed 141
	output_psv adnuts.psv >> adnuts_psv.txt
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1 -mcseed 532
	output_psv adnuts.psv >> adnuts_psv.txt
	$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest -mcseed 123
	output_psv adnuts.psv >> adnuts_psv.txt
else
	./$(TARGET) -nuts -hbf -mcmc 2000 -mcseed 12
	./output_psv adnuts.psv > adnuts_psv.txt
	./$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest -mcseed 141
	./output_psv adnuts.psv >> adnuts_psv.txt
	./$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1 -mcseed 532
	./output_psv adnuts.psv >> adnuts_psv.txt
	./$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest -mcseed 123
	./output_psv adnuts.psv >> adnuts_psv.txt
endif

$(TARGET): $(TARGET).tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb.cmd $(TARGET) $(SRCS)
else
	../../admb$(EXT) $(TARGET) $(SRCS)
endif

output_psv: output_psv.cpp
	$(CXX) -o $@ $^

clean2:
ifeq ($(CMDSHELL),cmd)
	@del adaptation.csv
	@del adapted_metric.txt
	@del adnuts.mc2
	@del adnuts.mcm
	@del adnuts.psv
	@del adnuts_psv.txt
	@del output_psv
	@del rwm_lp.txt
	@del sims
	@del unbounded.csv
else
	@rm -vf adaptation.csv
	@rm -vf adapted_metric.txt
	@rm -vf adnuts.mc2
	@rm -vf adnuts.mcm
	@rm -vf adnuts.psv
	@rm -vf adnuts_psv.txt
	@rm -vf output_psv
	@rm -vf rwm_lp.txt
	@rm -vf sims
	@rm -vf unbounded.csv
endif

clean: clean2
ifeq ($(CMDSHELL),cmd)
	@del $(TARGET) 2>nul
	@del variance 2>nul
	@del fmin.log 2>nul
	@del $(TARGET).rep 2>nul
	@del $(TARGET).eva 2>nul
	@del $(TARGET).exe 2>nul
	@del $(TARGET).htp 2>nul
	@del $(TARGET).bar 2>nul
	@del $(TARGET).bgs 2>nul
	@del $(TARGET).cor 2>nul
	@del $(TARGET).cpp 2>nul
	@del $(TARGET).log 2>nul
	@del $(TARGET).o 2>nul
	@del $(TARGET).obj 2>nul
	@del $(TARGET).par 2>nul
	@del $(TARGET).std 2>nul
	@del tests_$(TARGET).o 2>nul
	@del tests_$(TARGET) 2>nul
	@del eigv.rpt 2>nul
	@del admodel.cov 2>nul
	@del admodel.dep 2>nul
	@del admodel.hes 2>nul
	@del $(TARGET).luu 2>nul
	@del $(TARGET).rhes 2>nul
	@del hesscheck 2>nul
	@del hessian.bin 2>nul
else
	@rm -vf $(TARGET)
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf hessian.bin
	@rm -vf hesscheck
	@rm -vf fmin.log
	@rm -vf $(TARGET).rep
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
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).rhes
	@rm -vf $(TARGET).[bpr]01
	@rm -vf eigv.rpt
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).rhes
	@rm -vf hesscheck
	@rm -vf hessian.bin
endif

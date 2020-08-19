TARGET=adnuts

default: $(TARGET)
	$(MAKE) _run

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

ifneq ($(CMDSHELL),cmd)
_PATH=./
endif

_run: output_psv
	$(_PATH)$(TARGET) -nuts -hbf -mcmc 2000 -mcseed 12
	./output_psv adnuts.psv > adnuts_psv.txt
	$(_PATH)$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest -mcseed 141
	./output_psv adnuts.psv >> adnuts_psv.txt
	$(_PATH)$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1 -mcseed 532
	./output_psv adnuts.psv >> adnuts_psv.txt
	$(_PATH)$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest -mcseed 123
	./output_psv adnuts.psv >> adnuts_psv.txt

output_psv: output_psv.cpp
	$(CXX) -o $@ $^

_clean: clean
	@rm -vf adaptation.csv
	@rm -vf adapted_metric.txt
	@rm -vf adnuts.mc2
	@rm -vf adnuts.mcm
	@rm -vf adnuts.psv
	@rm -vf adnuts_psv.txt
	@rm -vf output_psv
	@rm -vf output_psv.cpp
	@rm -vf rwm_lp.txt
	@rm -vf sims
	@rm -vf unbounded.csv

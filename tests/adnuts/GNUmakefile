TARGET=adnuts
OVERRIDE=all

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

ifeq ($(CMDSHELL),cmd)
run: $(TARGET) output_psv.exe
else
run: $(TARGET) output_psv
endif
	$(_PATH)$(TARGET) -nuts -hbf -mcmc 2000 -mcseed 12
	$(_PATH)output_psv adnuts.psv > adnuts_psv.txt
	$(_PATH)$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest -mcseed 141
	$(_PATH)output_psv adnuts.psv >> adnuts_psv.txt
	$(_PATH)$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1 -mcseed 532
	$(_PATH)output_psv adnuts.psv >> adnuts_psv.txt
	$(_PATH)$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest -mcseed 123
	$(_PATH)output_psv adnuts.psv >> adnuts_psv.txt

ifeq ($(CMDSHELL),cmd)
output_psv.exe: output_psv.cpp
else
output_psv: output_psv.cpp
endif
	$(CXX) -o $@ $^

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist adaptation.csv type adaptation.csv
	@if exist adapted_metric.txt type adapted_metric.txt
	@if exist adnuts_psv.txt type adnuts_psv.txt
	@if exist rwm_lp.txt type rwm_lp.txt
	@if exist sims type sims
	@if exist unbounded.csv type unbounded.csv
else
	@if [ -e adaptation.csv ]; then cat adaptation.csv; fi
	@if [ -e adapted_metric.txt ]; then cat adapted_metric.txt; fi
	@if [ -e adnuts_psv.txt ]; then cat adnuts_psv.txt; fi
	@if [ -e rwm_lp.txt ]; then cat rwm_lp.txt; fi
	@if [ -e sims ]; then cat sims; fi
	@if [ -e unbounded.csv ]; then cat unbounded.csv; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist adaptation.csv del /Q adaptation.csv
	@if exist adapted_metric.txt del /Q adapted_metric.txt
	@if exist adnuts.mc2 del /Q adnuts.mc2
	@if exist adnuts.mcm del /Q adnuts.mcm
	@if exist adnuts.psv del /Q adnuts.psv
	@if exist adnuts_psv.txt del /Q adnuts_psv.txt
	@if exist output_psv.exe del /Q output_psv.exe
	@if exist output_psv.obj del /Q output_psv.obj
	@if exist rwm_lp.txt del /Q rwm_lp.txt
	@if exist sims del /Q sims
	@if exist unbounded.csv del /Q unbounded.csv
else
	@rm -vf adaptation.csv
	@rm -vf adapted_metric.txt
	@rm -vf adnuts.mc2
	@rm -vf adnuts.mcm
	@rm -vf adnuts.psv
	@rm -vf adnuts_psv.txt
	@rm -vf output_psv
	@rm -vf output_psv.obj
	@rm -vf rwm_lp.txt
	@rm -vf sims
	@rm -vf unbounded.csv
endif
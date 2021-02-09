TARGET=adnuts
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET) output_psv.exe
	$(TARGET) -nuts -hbf -mcmc 2000 -mcseed 12
	output_psv adnuts.psv > adnuts_psv.txt
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest -mcseed 141
	output_psv adnuts.psv >> adnuts_psv.txt
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1 -mcseed 532
	output_psv adnuts.psv >> adnuts_psv.txt
	$(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest -mcseed 123
	output_psv adnuts.psv >> adnuts_psv.txt

output_psv.exe: output_psv.cpp
	$(CXX) /Feoutput_psv.exe output_psv.cpp

get-outputs: _get-outputs
        @if exist adaptation.csv type adaptation.csv
        @if exist adapted_metric.txt type adapted_metric.txt
        @if exist adnuts_psv.txt type adnuts_psv.txt
        @if exist rwm_lp.txt type rwm_lp.txt
        @if exist sims type sims
        @if exist unbounded.csv type unbounded.csv

clean: _clean
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

TARGET=adnuts

all: run

run: $(TARGET).exe output_psv.exe
	$(TARGET) -nuts -hbf -mcmc 2000 -mcseed 12
	output_psv adnuts.psv > adnuts_psv.txt
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass -noest -mcseed 141
	output_psv adnuts.psv >> adnuts_psv.txt
	$(TARGET) -nuts -mcmc 2000 -mcdiag -adapt_mass_dense -noest -verbose_adapt_mass -refresh -1 -mcseed 532
	output_psv adnuts.psv >> adnuts_psv.txt
	(TARGET) -rwm -mcmc 2000 -mcsave 1 -noest -mcseed 123
	output_psv adnuts.psv >> adnuts_psv.txt

$(TARGET).exe: $(TARGET).tpl
	..\\..\\admb.cmd $(TARGET) $(SRCS)

output_psv: output_psv.cpp
	$(CXX) -o $@ $^

clean2:
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

clean: clean2
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

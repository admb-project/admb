.PHONY: run

TARGET=SS3

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; admb -s $(TARGET)

run:
	@printf "Started run:\n"
	./$(TARGET)
	@printf "Finished run.\n"

clean:
	@del ss3.b01
	@del ss3.bar
	@del ss3.cor
	@del ss3.eva
	@del ss3.log
	@del ss3.p01
	@del ss3.r01
	@del ss3.rep
	@del ss3.std
	@del ss3.par
	@del wtatage.ss_new
	@del ParmTrace.SSO
	@del Starter.SS_New
	@del Forecast-report.SSO
	@del CumReport.SSO
	@del checkup.SSO
	@del ss3.b02
	@del ss3.b03
	@del ss3.b04
	@del runnumber.SS
	@del echoinput.SSO
	@del Forecast.SS_New
	@del Data.SS_New
	@del ss3.p02
	@del warning.SSO
	@del ss3.p03
	@del ss3.p04
	@del ss3.r02
	@del ss3.r03
	@del ss3.r04
	@del CoVar.SSO
	@del Control.SS_New
	@del Report.SSO
	@del a
	@del betareg.p02
	@del betareg.par
	@del betareg.b02
	@del betareg.r02
	@del b1 b2 s1 s2
	@del $(TARGET)
	@del admodel.*
	@del variance
	@del fmin.log
	@del $(TARGET).eva
	@del $(TARGET).htp
	@del $(TARGET).bar
	@del $(TARGET).bgs
	@del $(TARGET).cor
	@del $(TARGET).cpp
	@del $(TARGET).log
	@del $(TARGET).luu
	@del $(TARGET).b01
	@del $(TARGET).psv
	@del $(TARGET).r01
	@del $(TARGET).o
	@del $(TARGET).p01
	@del $(TARGET).std
	@del $(TARGET).rep
	@del $(TARGET).rhes
	@del f1b2list13
	@del hesscheck
	@del data
	@del sims
	@del eigv.rpt
	@del hessian.bin
	@del f1b2list1 gradfil1.tmp nf1b2list12
	@del f1b2list12 gradfil2.tmp nf1b2list13
	@del cmpdiff.tmp f1b2list1 nf1b2list1 varssave.tmp

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
	@rm -vf ss3.par
	@rm -vf wtatage.ss_new
	@rm -vf ParmTrace.SSO
	@rm -vf Starter.SS_New
	@rm -vf Forecast-report.SSO
	@rm -vf CumReport.SSO
	@rm -vf checkup.SSO
	@rm -vf ss3.b02
	@rm -vf ss3.b03
	@rm -vf ss3.b04
	@rm -vf runnumber.SS
	@rm -vf echoinput.SSO
	@rm -vf Forecast.SS_New
	@rm -vf Data.SS_New
	@rm -vf ss3.p02
	@rm -vf warning.SSO
	@rm -vf ss3.p03
	@rm -vf ss3.p04
	@rm -vf ss3.r02
	@rm -vf ss3.r03
	@rm -vf ss3.r04
	@rm -vf CoVar.SSO
	@rm -vf Control.SS_New
	@rm -vf Report.SSO
	@rm -vf a
	@rm -vf betareg.p02
	@rm -vf betareg.par
	@rm -vf betareg.b02
	@rm -vf betareg.r02
	@rm -vf b1 b2 s1 s2
	@rm -vf $(TARGET)
	@rm -vf admodel.*
	@rm -vf variance
	@rm -vf fmin.log
	@rm -vf $(TARGET).eva
	@rm -vf $(TARGET).htp
	@rm -vf $(TARGET).bar
	@rm -vf $(TARGET).bgs
	@rm -vf $(TARGET).cor
	@rm -vf $(TARGET).cpp
	@rm -vf $(TARGET).log
	@rm -vf $(TARGET).luu
	@rm -vf $(TARGET).b01
	@rm -vf $(TARGET).psv
	@rm -vf $(TARGET).r01
	@rm -vf $(TARGET).o
	@rm -vf $(TARGET).p01
	@rm -vf $(TARGET).std
	@rm -vf $(TARGET).rep
	@rm -vf $(TARGET).rhes
	@rm -vf f1b2list13
	@rm -vf hesscheck
	@rm -vf data
	@rm -vf sims
	@rm -vf eigv.rpt
	@rm -vf hessian.bin
	@rm -vf f1b2list1 gradfil1.tmp nf1b2list12
	@rm -vf f1b2list12 gradfil2.tmp nf1b2list13
	@rm -vf cmpdiff.tmp f1b2list1 nf1b2list1 varssave.tmp

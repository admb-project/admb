ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

TARGET=SS3

all: clean $(TARGET) run

$(TARGET): $(TARGET).tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $(TARGET)
else
	../../admb$(EXT) $(TARGET)
endif

run:
ifeq ($(SHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
endif

clean:
ifeq ($(SHELL),cmd)
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
	@del $(TARGET).exe
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
	@del SS3.b02
	@del SS3.b03
	@del SS3.b04
	@del SS3.obj
	@del SS3.p02
	@del SS3.p03
	@del SS3.p04
	@del SS3.par
	@del SS3.r02
	@del SS3.r03
	@del SS3.r04
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
else
	@rm -vf ss3.b01
	@rm -vf ss3.bar
	@rm -vf ss3.cor
	@rm -vf ss3.eva
	@rm -vf ss3.log
	@rm -vf ss3.p01
	@rm -vf ss3.r01
	@rm -vf ss3.rep
	@rm -vf ss3.std
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
	@rm -vf SS3.b02
	@rm -vf SS3.b03
	@rm -vf SS3.b04
	@rm -vf SS3.obj
	@rm -vf SS3.p02
	@rm -vf SS3.p03
	@rm -vf SS3.p04
	@rm -vf SS3.par
	@rm -vf SS3.r02
	@rm -vf SS3.r03
	@rm -vf SS3.r04
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
endif

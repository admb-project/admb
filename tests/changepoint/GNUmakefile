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

TARGET=changepoint

all:
	$(MAKE) changepoint.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb changepoint.tpl
else
	../../admb$(EXT) changepoint.tpl
endif
	$(MAKE) run

run: changepoint.dat
ifeq ($(SHELL),cmd)
	changepoint
else
	./changepoint
endif

changepoint.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL > changepoint.tpl

changepoint.dat:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/doc/changepoint.dat > changepoint.dat

clean:
ifeq ($(SHELL),cmd)
	@del $(TARGET) 2>nul
	@del variance 2>nul
	@del fmin.log 2>nul
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
	@del changepoint.rep 2>nul
else
	@rm -vf changepoint changepoint.cpp changepoint.htp changepoint.obj
	@rm -vf Echo.Out
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf changepoint.b01
	@rm -vf changepoint.bar
	@rm -vf changepoint.cor
	@rm -vf changepoint.eva
	@rm -vf changepoint.log
	@rm -vf changepoint.p01
	@rm -vf changepoint.par
	@rm -vf changepoint.r01
	@rm -vf changepoint.rep
	@rm -vf changepoint.std
	@rm -vf cmpdiff.tmp
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf variance
	@rm -vf varssave.tmp
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf changepoint.rep
endif

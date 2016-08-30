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
	@del $(TARGET)
	@del variance
	@del fmin.log
	@del $(TARGET).eva
	@del $(TARGET).exe
	@del $(TARGET).htp
	@del $(TARGET).bar
	@del $(TARGET).bgs
	@del $(TARGET).cor
	@del $(TARGET).cpp
	@del $(TARGET).log
	@del $(TARGET).o
	@del $(TARGET).obj
	@del $(TARGET).par
	@del $(TARGET).std
	@del tests_$(TARGET).o
	@del tests_$(TARGET)
	@del eigv.rpt
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del changepoint.rep
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

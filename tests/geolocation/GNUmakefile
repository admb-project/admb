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

ifndef ADMB_HOME
ADMB_HOME=../../../build/dist
endif

all:
ifeq ($(SHELL),cmd)
	$(MAKE) MAKEDIR=.. --file=Makefile all
else
	$(MAKE) kfsst/kfsst kftrack/kftrack trackit/trackit ukfsst/ukfsst
	$(MAKE) run
endif

kfsst/kfsst: kfsst
ifeq ($(EXT),.sh)
	cd kfsst; ../../../admb.sh kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp; cd ..
else
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=kfsst
endif

kftrack/kftrack: kftrack
ifeq ($(EXT),.sh)
	cd kftrack; ../../../admb.sh kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp; cd ..
	cd kftrack; ../../../admb.sh twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp; cd ..
else
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=kftrack
endif

trackit/trackit: trackit
ifeq ($(EXT),.sh)
	cd trackit; ../../../admb.sh ukf; cd ..
	cd trackit; ../../../admb.sh prepro; cd ..
else
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=trackit
endif

ukfsst/ukfsst: ukfsst
ifeq ($(EXT),.sh)
	cd ukfsst; ../../../admb.sh ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp; cd ..
else
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=ukfsst
endif

kfsst:
	svn checkout https://github.com/positioning/kalmanfilter/trunk/kfsst/kfsst/source kfsst
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/kfsst/kfsst.dat > kfsst/kfsst.dat
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/kfsst/sst.dat > kfsst/sst.dat

kftrack:
	svn checkout https://github.com/positioning/kalmanfilter/trunk/kftrack/inst/admb/src kftrack
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/kftrack/kftrack.dat > kftrack/kftrack.dat

trackit:
	svn checkout https://github.com/positioning/kalmanfilter/trunk/trackit/inst/admb/src trackit
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/trackit/ukf.dat > trackit/ukf.dat
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/trackit/sstsim.dat > trackit/sstsim.dat
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/trackit/model.cfg > trackit/model.cfg

ukfsst:
	svn checkout https://github.com/positioning/kalmanfilter/trunk/ukfsst/inst/admb/src ukfsst
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/ukfsst/ukfsst.dat > ukfsst/ukfsst.dat
	svn export https://github.com/positioning/kalmanfilter/trunk/testdir/ukfsst/sst_files ukfsst/sst_files

run:
ifeq ($(SHELL),cmd)
	$(MAKE) --file=Makefile run
else
	cd kfsst; ./kfsst; cd ..
	cd kftrack; ./kftrack; cd ..
	cd trackit; ./ukf; cd ..
	cd ukfsst; ./ukfsst; cd ..
endif

total-clean:
ifeq ($(SHELL),cmd)
else
	@rm -rvf ukfsst
	@rm -rvf trackit
	@rm -rvf kftrack
	@rm -rvf kfsst
endif

clean:
ifeq ($(SHELL),cmd)
else
ifeq (cygwin,$(TERM))
else
	if [ -e kfsst/Makefile ]; then $(MAKE) --directory=kfsst clean; fi;
	if [ -e kftrack/Makefile ]; then $(MAKE) --directory=kftrack clean; fi;
	if [ -e trackit/Makefile ]; then $(MAKE) --directory=trackit clean; fi;
	if [ -e ukfsst/Makefile ]; then $(MAKE) --directory=ukfsst clean; fi;
endif
	@rm -vf kfsst/admodel.cov
	@rm -vf kfsst/admodel.dep
	@rm -vf kfsst/admodel.hes
	@rm -vf kfsst/check.dat
	@rm -vf kfsst/eigv.rpt
	@rm -vf kfsst/fmin.log
	@rm -vf kfsst/gmt_111011110%F3-9%C3%D6%C8.dat
	@rm -vf kfsst/kfsst.b01
	@rm -vf kfsst/kfsst.b02
	@rm -vf kfsst/kfsst.bar
	@rm -vf kfsst/kfsst.cor
	@rm -vf kfsst/kfsst.eva
	@rm -vf kfsst/kfsst.log
	@rm -vf kfsst/kfsst.p01
	@rm -vf kfsst/kfsst.p02
	@rm -vf kfsst/kfsst.par
	@rm -vf kfsst/kfsst.r01
	@rm -vf kfsst/kfsst.r02
	@rm -vf kfsst/kfsst.rep
	@rm -vf kfsst/kfsst.std
	@rm -vf kfsst/kftrack.log
	@rm -vf kfsst/mpt_111011110%F3-9%C3%D6%C8.dat
	@rm -vf kfsst/variance
	@rm -vf kftrack/admodel.cov
	@rm -vf kftrack/admodel.dep
	@rm -vf kftrack/admodel.hes
	@rm -vf kftrack/eigv.rpt
	@rm -vf kftrack/fmin.log
	@rm -vf kftrack/gmt.dat
	@rm -vf kftrack/kftrack.b01
	@rm -vf kftrack/kftrack.b02
	@rm -vf kftrack/kftrack.bar
	@rm -vf kftrack/kftrack.cor
	@rm -vf kftrack/kftrack.eva
	@rm -vf kftrack/kftrack.log
	@rm -vf kftrack/kftrack.p01
	@rm -vf kftrack/kftrack.p02
	@rm -vf kftrack/kftrack.par
	@rm -vf kftrack/kftrack.r01
	@rm -vf kftrack/kftrack.r02
	@rm -vf kftrack/kftrack.rep
	@rm -vf kftrack/kftrack.std
	@rm -vf kftrack/mpt.dat
	@rm -vf kftrack/variance
	@rm -vf trackit/admodel.cov
	@rm -vf trackit/admodel.dep
	@rm -vf trackit/admodel.hes
	@rm -vf trackit/eigv.rpt
	@rm -vf trackit/fmin.log
	@rm -vf trackit/program.log
	@rm -vf trackit/ukf.b01
	@rm -vf trackit/ukf.b02
	@rm -vf trackit/ukf.b03
	@rm -vf trackit/ukf.bar
	@rm -vf trackit/ukf.cor
	@rm -vf trackit/ukf.eva
	@rm -vf trackit/ukf.log
	@rm -vf trackit/ukf.p01
	@rm -vf trackit/ukf.p02
	@rm -vf trackit/ukf.p03
	@rm -vf trackit/ukf.par
	@rm -vf trackit/ukf.r01
	@rm -vf trackit/ukf.r02
	@rm -vf trackit/ukf.r03
	@rm -vf trackit/ukf.rep
	@rm -vf trackit/ukf.std
	@rm -vf trackit/variance
	@rm -vf ukfsst/admodel.cov
	@rm -vf ukfsst/admodel.dep
	@rm -vf ukfsst/admodel.hes
	@rm -vf ukfsst/eigv.rpt
	@rm -vf ukfsst/fmin.log
	@rm -vf ukfsst/mpt.out
	@rm -vf ukfsst/pred.out
	@rm -vf ukfsst/time.out
	@rm -vf ukfsst/ukfsst.b01
	@rm -vf ukfsst/ukfsst.b02
	@rm -vf ukfsst/ukfsst.bar
	@rm -vf ukfsst/ukfsst.cor
	@rm -vf ukfsst/ukfsst.eva
	@rm -vf ukfsst/ukfsst.log
	@rm -vf ukfsst/ukfsst.p01
	@rm -vf ukfsst/ukfsst.p02
	@rm -vf ukfsst/ukfsst.par
	@rm -vf ukfsst/ukfsst.r01
	@rm -vf ukfsst/ukfsst.r02
	@rm -vf ukfsst/ukfsst.rep
	@rm -vf ukfsst/ukfsst.std
	@rm -vf ukfsst/variance
endif

clean-kfsst:
	$(MAKE) --file=Makefile clean-kfsst

clean-kftrack:
	$(MAKE) --file=Makefile clean-kftrack

clean-trackit:
	$(MAKE) --file=Makefile clean-trackit

clean-ukfsst:
	$(MAKE) --file=Makefile clean-ukfsst

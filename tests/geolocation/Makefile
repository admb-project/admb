all: kfsst\\kfsst.exe kftrack\\kftrack.exe trackit\\trackit.exe ukfsst\\ukfsst.exe

kfsst\\kfsst.exe: kfsst
	pushd kfsst& ..\\..\\..\\admb kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp

kftrack\\kftrack.exe: kftrack
	pushd kftrack& ..\\..\\..\\admb kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	pushd kftrack& ..\\..\\..\\admb twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp

trackit\\trackit.exe: trackit
	pushd trackit& ..\\..\\..\\admb ukf
	pushd trackit& ..\\..\\..\\admb prepro

ukfsst\\ukfsst.exe: ukfsst
	pushd ukfsst& ..\\..\\..\\admb ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp

kfsst:
	if not exist kfsst svn export https://github.com/positioning/kalmanfilter/trunk/kfsst/kfsst/source kfsst
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/kfsst/kfsst.dat > kfsst\\kfsst.dat
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/kfsst/sst.dat > kfsst\\sst.dat

kftrack:
	if not exist kftrack svn export https://github.com/positioning/kalmanfilter/trunk/kftrack/inst/admb/src kftrack
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/kftrack/kftrack.dat > kftrack\\kftrack.dat

trackit:
	if not exist trackit svn export https://github.com/positioning/kalmanfilter/trunk/trackit/inst/admb/src trackit
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/trackit/ukf.dat > trackit\\ukf.dat
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/trackit/sstsim.dat > trackit\\sstsim.dat
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/trackit/model.cfg > trackit\\model.cfg

ukfsst:
	if not exist ukfsst svn export https://github.com/positioning/kalmanfilter/trunk/ukfsst/inst/admb/src ukfsst
	svn cat https://github.com/positioning/kalmanfilter/trunk/testdir/ukfsst/ukfsst.dat > ukfsst\\ukfsst.dat
	if not exist ukfsst\\sst_files svn export https://github.com/positioning/kalmanfilter/trunk/testdir/ukfsst/sst_files ukfsst\\sst_files

run:
	pushd kfsst& kfsst
	pushd kftrack& kftrack
	pushd trackit& ukf
	pushd ukfsst& ukfsst

total-clean:
	@if exist ukfsst rmdir /s /q ukfsst
	@if exist trackit rmdir /s /q trackit
	@if exist kftrack rmdir /s /q kftrack
	@if exist kfsst rmdir /s /q kfsst

clean:
	if exist kfsst $(MAKE) clean-kfsst
	if exist kftrack $(MAKE) clean-kftrack
	if exist trackit $(MAKE) clean-trackit
	if exist ukfsst $(MAKE) clean-ukfsst

clean-kfsst:
	@del kfsst\\admodel.cov
	@del kfsst\\admodel.dep
	@del kfsst\\admodel.hes
	@del kfsst\\check.dat
	@del kfsst\\eigv.rpt
	@del kfsst\\fmin.log
	@del kfsst\\kfsst.b01
	@del kfsst\\kfsst.b02
	@del kfsst\\kfsst.bar
	@del kfsst\\kfsst.cor
	@del kfsst\\kfsst.eva
	@del kfsst\\kfsst.log
	@del kfsst\\kfsst.p01
	@del kfsst\\kfsst.p02
	@del kfsst\\kfsst.par
	@del kfsst\\kfsst.r01
	@del kfsst\\kfsst.r02
	@del kfsst\\kfsst.rep
	@del kfsst\\kfsst.std
	@del kfsst\\kftrack.log
	@del kfsst\\variance
	@del kfsst\\azimuth.obj
	@del kfsst\\banner.obj
	@del kfsst\\kfsst.cpp
	@del kfsst\\kfsst.dat
	@del kfsst\\kfsst.exe
	@del kfsst\\kfsst.htp
	@del kfsst\\kfsst.obj
	@del kfsst\\solstice.obj
	@del kfsst\\sst.dat
	@del kfsst\\yrmonday.obj

clean-kftrack:
	@del kftrack\\admodel.cov
	@del kftrack\\admodel.dep
	@del kftrack\\admodel.hes
	@del kftrack\\eigv.rpt
	@del kftrack\\fmin.log
	@del kftrack\\gmt.dat
	@del kftrack\\kftrack.b01
	@del kftrack\\kftrack.b02
	@del kftrack\\kftrack.bar
	@del kftrack\\kftrack.cor
	@del kftrack\\kftrack.eva
	@del kftrack\\kftrack.log
	@del kftrack\\kftrack.p01
	@del kftrack\\kftrack.p02
	@del kftrack\\kftrack.par
	@del kftrack\\kftrack.r01
	@del kftrack\\kftrack.r02
	@del kftrack\\kftrack.rep
	@del kftrack\\kftrack.std
	@del kftrack\\mpt.dat
	@del kftrack\\variance
	@del kftrack\\azimuth.obj
	@del kftrack\\banner.obj
	@del kftrack\\kftrack.cpp
	@del kftrack\\kftrack.dat
	@del kftrack\\kftrack.exe
	@del kftrack\\kftrack.htp
	@del kftrack\\kftrack.obj
	@del kftrack\\solstice.obj
	@del kftrack\\twosegtrack.cpp
	@del kftrack\\twosegtrack.exe
	@del kftrack\\twosegtrack.htp
	@del kftrack\\twosegtrack.obj
	@del kftrack\\yrmonday.obj

clean-trackit:
	@del trackit\\admodel.cov
	@del trackit\\admodel.dep
	@del trackit\\admodel.hes
	@del trackit\\eigv.rpt
	@del trackit\\fmin.log
	@del trackit\\program.log
	@del trackit\\ukf.b01
	@del trackit\\ukf.b02
	@del trackit\\ukf.b03
	@del trackit\\ukf.bar
	@del trackit\\ukf.cor
	@del trackit\\ukf.eva
	@del trackit\\ukf.log
	@del trackit\\ukf.p01
	@del trackit\\ukf.p02
	@del trackit\\ukf.p03
	@del trackit\\ukf.par
	@del trackit\\ukf.r01
	@del trackit\\ukf.r02
	@del trackit\\ukf.r03
	@del trackit\\ukf.rep
	@del trackit\\ukf.std
	@del trackit\\variance
	@del trackit\\model.cfg
	@del trackit\\prepro.cpp
	@del trackit\\prepro.exe
	@del trackit\\prepro.htp
	@del trackit\\prepro.obj
	@del trackit\\sstsim.dat
	@del trackit\\ukf.cpp
	@del trackit\\ukf.dat
	@del trackit\\ukf.htp

clean-ukfsst:
	@del ukfsst\\admodel.cov
	@del ukfsst\\admodel.dep
	@del ukfsst\\admodel.hes
	@del ukfsst\\eigv.rpt
	@del ukfsst\\fmin.log
	@del ukfsst\\mpt.out
	@del ukfsst\\pred.out
	@del ukfsst\\time.out
	@del ukfsst\\ukfsst.b01
	@del ukfsst\\ukfsst.b02
	@del ukfsst\\ukfsst.bar
	@del ukfsst\\ukfsst.cor
	@del ukfsst\\ukfsst.eva
	@del ukfsst\\ukfsst.log
	@del ukfsst\\ukfsst.p01
	@del ukfsst\\ukfsst.p02
	@del ukfsst\\ukfsst.par
	@del ukfsst\\ukfsst.r01
	@del ukfsst\\ukfsst.r02
	@del ukfsst\\ukfsst.rep
	@del ukfsst\\ukfsst.std
	@del ukfsst\\variance
	@del ukfsst\\azimuth.obj
	@del ukfsst\\banner.obj
	@del ukfsst\\solstice.obj
	@del ukfsst\\ukfsst.cpp
	@del ukfsst\\ukfsst.dat
	@del ukfsst\\ukfsst.exe
	@del ukfsst\\ukfsst.htp
	@del ukfsst\\ukfsst.obj
	@del ukfsst\\yrmonday.obj

all: kfsst\\kfsst.exe kftrack\\kftrack.exe trackit\\trackit.exe ukfsst\\ukfsst.exe

kfsst\\kfsst.exe: kfsst
	$(MAKE) --directory=kfsst PATH="$(CURDIR)/../..;$(PATH)"

kftrack\\kftrack.exe: kftrack
	$(MAKE) --directory=kftrack PATH="$(CURDIR)/../..;$(PATH)"

trackit\\trackit.exe: trackit
	$(MAKE) --directory=trackit PATH="$(CURDIR)/../..;$(PATH)"

ukfsst\\ukfsst.exe: ukfsst
	$(MAKE) --directory=ukfsst PATH="$(CURDIR)/../..;$(PATH)"

kfsst:
	if not exist kfsst svn export http://geolocation.googlecode.com/svn/trunk/kfsst/kfsst/source kfsst
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kfsst/kfsst.dat > kfsst\\kfsst.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kfsst/sst.dat > kfsst\\sst.dat

kftrack:
	if not exist kftrack svn export http://geolocation.googlecode.com/svn/trunk/kftrack/inst/admb/src kftrack
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kftrack/kftrack.dat > kftrack\\kftrack.dat

trackit:
	if not exist trackit svn export http://geolocation.googlecode.com/svn/trunk/trackit/inst/admb/src trackit
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/ukf.dat > trackit\\ukf.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/sstsim.dat > trackit\\sstsim.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/model.cfg > trackit\\model.cfg

ukfsst:
	if not exist ukfsst svn export http://geolocation.googlecode.com/svn/trunk/ukfsst/inst/admb/src ukfsst
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/ukfsst/ukfsst.dat > ukfsst\\ukfsst.dat
	if not exist ukfsst\\sst_files svn export http://geolocation.googlecode.com/svn/trunk/testdir/ukfsst/sst_files ukfsst\\sst_files

run:
	pushd kfsst & kfsst
	pushd kftrack & kftrack
	pushd trackit & ukf
	pushd ukfsst & ukfsst

clean:
	$(MAKE) --directory=kfsst clean
	@del kfsst/admodel.cov
	@del kfsst/admodel.dep
	@del kfsst/admodel.hes
	@del kfsst/check.dat
	@del kfsst/eigv.rpt
	@del kfsst/fmin.log
	@del kfsst/gmt_111011110%F3-9%C3%D6%C8.dat
	@del kfsst/kfsst.b01
	@del kfsst/kfsst.b02
	@del kfsst/kfsst.bar
	@del kfsst/kfsst.cor
	@del kfsst/kfsst.eva
	@del kfsst/kfsst.log
	@del kfsst/kfsst.p01
	@del kfsst/kfsst.p02
	@del kfsst/kfsst.par
	@del kfsst/kfsst.r01
	@del kfsst/kfsst.r02
	@del kfsst/kfsst.rep
	@del kfsst/kfsst.std
	@del kfsst/kftrack.log
	@del kfsst/mpt_111011110%F3-9%C3%D6%C8.dat
	@del kfsst/variance
	$(MAKE) --directory=kftrack clean
	@del kftrack/admodel.cov
	@del kftrack/admodel.dep
	@del kftrack/admodel.hes
	@del kftrack/eigv.rpt
	@del kftrack/fmin.log
	@del kftrack/gmt.dat
	@del kftrack/kftrack.b01
	@del kftrack/kftrack.b02
	@del kftrack/kftrack.bar
	@del kftrack/kftrack.cor
	@del kftrack/kftrack.eva
	@del kftrack/kftrack.log
	@del kftrack/kftrack.p01
	@del kftrack/kftrack.p02
	@del kftrack/kftrack.par
	@del kftrack/kftrack.r01
	@del kftrack/kftrack.r02
	@del kftrack/kftrack.rep
	@del kftrack/kftrack.std
	@del kftrack/mpt.dat
	@del kftrack/variance
	$(MAKE) --directory=trackit clean
	@del trackit/admodel.cov
	@del trackit/admodel.dep
	@del trackit/admodel.hes
	@del trackit/eigv.rpt
	@del trackit/fmin.log
	@del trackit/program.log
	@del trackit/ukf.b01
	@del trackit/ukf.b02
	@del trackit/ukf.b03
	@del trackit/ukf.bar
	@del trackit/ukf.cor
	@del trackit/ukf.eva
	@del trackit/ukf.log
	@del trackit/ukf.p01
	@del trackit/ukf.p02
	@del trackit/ukf.p03
	@del trackit/ukf.par
	@del trackit/ukf.r01
	@del trackit/ukf.r02
	@del trackit/ukf.r03
	@del trackit/ukf.rep
	@del trackit/ukf.std
	@del trackit/variance
	$(MAKE) --directory=ukfsst clean
	@del ukfsst/admodel.cov
	@del ukfsst/admodel.dep
	@del ukfsst/admodel.hes
	@del ukfsst/eigv.rpt
	@del ukfsst/fmin.log
	@del ukfsst/mpt.out
	@del ukfsst/pred.out
	@del ukfsst/time.out
	@del ukfsst/ukfsst.b01
	@del ukfsst/ukfsst.b02
	@del ukfsst/ukfsst.bar
	@del ukfsst/ukfsst.cor
	@del ukfsst/ukfsst.eva
	@del ukfsst/ukfsst.log
	@del ukfsst/ukfsst.p01
	@del ukfsst/ukfsst.p02
	@del ukfsst/ukfsst.par
	@del ukfsst/ukfsst.r01
	@del ukfsst/ukfsst.r02
	@del ukfsst/ukfsst.rep
	@del ukfsst/ukfsst.std
	@del ukfsst/variance

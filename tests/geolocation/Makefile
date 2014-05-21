all: kfsst kftrack trackit ukfsst

kfsst:
	$(MAKE) --directory=svn-kfsst PATH="$(CURDIR)/../..;$(PATH)"

kftrack:
	$(MAKE) --directory=svn-kftrack PATH="$(CURDIR)/../..;$(PATH)"

trackit:
	$(MAKE) --directory=svn-trackit PATH="$(CURDIR)/../..;$(PATH)"

ukfsst:
	$(MAKE) --directory=svn-ukfsst PATH="$(CURDIR)/../..;$(PATH)"

svn:
	if not exist svn-kfsst svn export http://geolocation.googlecode.com/svn/trunk/kfsst/kfsst/source svn-kfsst
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kfsst/kfsst.dat > svn-kfsst\\kfsst.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kfsst/sst.dat > svn-kfsst\\sst.dat
	if not exist svn-kftrack svn export http://geolocation.googlecode.com/svn/trunk/kftrack/inst/admb/src svn-kftrack
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kftrack/kftrack.dat > svn-kftrack\\kftrack.dat
	if not exist svn-trackit svn export http://geolocation.googlecode.com/svn/trunk/trackit/inst/admb/src svn-trackit
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/ukf.dat > svn-trackit\\ukf.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/sstsim.dat > svn-trackit\\sstsim.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/model.cfg > svn-trackit\\model.cfg
	if not exist svn-ukfsst svn export http://geolocation.googlecode.com/svn/trunk/ukfsst/inst/admb/src svn-ukfsst
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/ukfsst/ukfsst.dat > svn-ukfsst\\ukfsst.dat
	if not exist svn-ukfsst\\sst_files svn export http://geolocation.googlecode.com/svn/trunk/testdir/ukfsst/sst_files svn-ukfsst\\sst_files

run:
	pushd svn-kfsst & kfsst
	pushd svn-kftrack & kftrack
	pushd svn-trackit & ukf
	pushd svn-ukfsst & ukfsst

clean:
	if exist svn-kfsst rd /S /Q svn-kfsst
	if exist svn-kftrack rd /S /Q svn-kftrack
	if exist svn-trackit rd /S /Q svn-trackit
	if exist svn-ukfsst rd /S /Q svn-ukfsst

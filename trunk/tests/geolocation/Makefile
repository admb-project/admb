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
	if not exist svn-ukfsst svn export http://geolocation.googlecode.com/svn/trunk/ukfsst/inst/admb/src svn-ukfsst
	if not exist svn-trackit svn export http://geolocation.googlecode.com/svn/trunk/trackit/inst/admb/src svn-trackit
	if not exist svn-kftrack svn export http://geolocation.googlecode.com/svn/trunk/kftrack/inst/admb/src svn-kftrack
	if not exist svn-kfsst svn export http://geolocation.googlecode.com/svn/trunk/kfsst/kfsst/source svn-kfsst

clean:
	if exist svn-kfsst rd /S /Q svn-kfsst
	if exist svn-kftrack rd /S /Q svn-kftrack
	if exist svn-trackit rd /S /Q svn-trackit
	if exist svn-ukfsst rd /S /Q svn-ukfsst

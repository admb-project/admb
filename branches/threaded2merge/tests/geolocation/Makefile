all: kfsst kftrack trackit ukfsst

kfsst:
	if exist svn-kfsst pushd kfsst & $(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" & popd

kftrack:
	if exist svn-kftrack pushd kftrack & $(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" & popd

trackit:
	if exist svn-trackit pushd trackit & $(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" & popd

ukfsst:
	if exist svn-ukfsst pushd svn-ukfsst & $(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" & popd

svn:
	if not exist ukfsst svn export http://geolocation.googlecode.com/svn/trunk/ukfsst/inst/admb/src svn-ukfsst
	if not exist trackit svn export http://geolocation.googlecode.com/svn/trunk/trackit/inst/admb/src svn-trackit
	if not exist kftrack svn export http://geolocation.googlecode.com/svn/trunk/kftrack/inst/admb/src svn-kftrack
	if not exist kfsst svn export http://geolocation.googlecode.com/svn/trunk/kfsst/inst/admb/src svn-kfsst

clean:
	if exist svn-kfsst rd /S /Q svn-kfsst
	if exist svn-kftrack rd /S /Q svn-kftrack
	if exist svn-trackit rd /S /Q svn-trackit
	if exist svn-ukfsst rd /S /Q svn-ukfsst

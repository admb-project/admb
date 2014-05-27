ifndef ADMB_HOME
ADMB_HOME=../../../build/dist
endif

all:
	$(MAKE) svn
	$(MAKE) kfsst kftrack trackit ukfsst
	$(MAKE) run

kfsst:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --file=Makefile kfsst
else
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=svn-kfsst
endif

kftrack:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --file=Makefile kftrack
else
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=svn-kftrack
endif

trackit:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --file=Makefile trackit
else
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=svn-trackit
endif

ukfsst:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --file=Makefile ukfsst
else
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=svn-ukfsst
endif

svn: clean
ifeq ($(SHELL),sh.exe)
	$(MAKE) --file=Makefile svn
else
	svn checkout http://geolocation.googlecode.com/svn/trunk/kfsst/kfsst/source svn-kfsst
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kfsst/kfsst.dat > svn-kfsst/kfsst.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kfsst/sst.dat > svn-kfsst/sst.dat
	svn checkout http://geolocation.googlecode.com/svn/trunk/kftrack/inst/admb/src svn-kftrack
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/kftrack/kftrack.dat > svn-kftrack/kftrack.dat
	svn checkout http://geolocation.googlecode.com/svn/trunk/trackit/inst/admb/src svn-trackit
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/ukf.dat > svn-trackit/ukf.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/sstsim.dat > svn-trackit/sstsim.dat
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/trackit/model.cfg > svn-trackit/model.cfg
	svn checkout http://geolocation.googlecode.com/svn/trunk/ukfsst/inst/admb/src svn-ukfsst
	svn cat http://geolocation.googlecode.com/svn/trunk/testdir/ukfsst/ukfsst.dat > svn-ukfsst/ukfsst.dat
	rm -rvf svn-ukfsst/sst_files
	svn export http://geolocation.googlecode.com/svn/trunk/testdir/ukfsst/sst_files svn-ukfsst/sst_files
endif

run:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --file=Makefile run
else
	pushd svn-kfsst; ./kfsst; popd
	pushd svn-kftrack; ./kftrack; popd
	pushd svn-trackit; ./ukf; popd
	pushd svn-ukfsst; ./ukfsst; popd
endif

clean:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --file=Makefile clean
else
	@rm -rvf svn-kfsst
	@rm -rvf svn-kftrack
	@rm -rvf svn-trackit
	@rm -rvf svn-ukfsst
endif

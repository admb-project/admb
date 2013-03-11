all: kfsst kftrack trackit ukfsst

kfsst:
ifndef COMSPEC
	-test -d svn-kfsst && ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=svn-kfsst
else
	$(MAKE) --file=Makefile kfsst
endif

kftrack:
ifndef COMSPEC
	-test -d svn-kftrack && ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=svn-kftrack
else
	$(MAKE) --file=Makefile kftrack
endif

trackit:
ifndef COMSPEC
	-test -d svn-trackit && ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=svn-trackit
else
	$(MAKE) --file=Makefile trackit
endif

ukfsst:
ifndef COMSPEC
	-test -d svn-ukfsst && ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=svn-ukfsst
else
	$(MAKE) --file=Makefile ukfsst
endif

svn:
ifndef COMSPEC
	test -d svn-kfsst || svn export http://geolocation.googlecode.com/svn/trunk/kfsst/kfsst/source svn-kfsst
	test -d svn-kftrack || svn export http://geolocation.googlecode.com/svn/trunk/kftrack/inst/admb/src svn-kftrack
	test -d svn-trackit || svn export http://geolocation.googlecode.com/svn/trunk/trackit/inst/admb/src svn-trackit
	test -d svn-ukfsst || svn export http://geolocation.googlecode.com/svn/trunk/ukfsst/inst/admb/src svn-ukfsst
else
	$(MAKE) --file=Makefile svn
endif

clean:
ifndef COMSPEC
	rm -rvf svn-kfsst svn-kftrack svn-trackit svn-ukfsst
else
	$(MAKE) --file=Makefile clean
endif

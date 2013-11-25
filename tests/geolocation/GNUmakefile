ifndef ADMB_HOME
ADMB_HOME=../../../build/dist
endif

all: kfsst kftrack trackit ukfsst

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
	svn export http://geolocation.googlecode.com/svn/trunk/kfsst/kfsst/source svn-kfsst
	svn export http://geolocation.googlecode.com/svn/trunk/kftrack/inst/admb/src svn-kftrack
	svn export http://geolocation.googlecode.com/svn/trunk/trackit/inst/admb/src svn-trackit
	svn export http://geolocation.googlecode.com/svn/trunk/ukfsst/inst/admb/src svn-ukfsst
endif

clean:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --file=Makefile clean
else
	rm -rvf svn-kfsst svn-kftrack svn-trackit svn-ukfsst
endif

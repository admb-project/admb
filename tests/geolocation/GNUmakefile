ifdef COMSPEC
SHELL=$(COMSPEC)
endif

all:
ifdef COMSPEC
	if not exist geolocation svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	pushd geolocation & $(MAKE) & popd
else
	test  -d geolocation || svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	$(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" --directory=geolocation
endif

clean:
ifdef COMSPEC
	if exist geolocation rd /S /Q geolocation
else
	rm -rvf geolocation
endif

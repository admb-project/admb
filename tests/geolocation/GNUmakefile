all:
ifeq (sh.exe,$(SHELL))
	if not exist geolocation svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	pushd geolocation & $(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" & popd
else
	test  -d geolocation || svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	$(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" --directory=geolocation
endif

clean:
ifeq (sh.exe,$(SHELL))
	if exist geolocation rd /S /Q geolocation
else
	rm -rvf geolocation
endif

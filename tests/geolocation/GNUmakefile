all:
	test  -d geolocation || svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	$(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" --directory=geolocation

clean:
	rm -rvf geolocation

all-cmd:
	if not exist geolocation svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	pushd geolocation & $(MAKE) & popd

clean-cmd:
	if exist geolocation rd /S /Q geolocation

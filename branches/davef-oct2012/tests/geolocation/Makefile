all: 
	if not exist geolocation svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	pushd geolocation & $(MAKE) & popd

clean:
	if exist geolocation rd /S /Q geolocation

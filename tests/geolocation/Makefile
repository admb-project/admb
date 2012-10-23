.PHONY: clean geolocation-read-only

all: geolocation-read-only
	make --always-make --directory=geolocation-read-only

geolocation-read-only: clean
	svn export http://geolocation.googlecode.com/svn/trunk/ $@

clean:
	if exist geolocation-read-only rd /S /Q geolocation-read-only

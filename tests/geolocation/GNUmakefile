.PHONY: clean geolocation-read-only

all: geolocation-read-only
	make --always-make --directory=geolocation-read-only

geolocation-read-only:
	svn export http://geolocation.googlecode.com/svn/trunk/ $@

clean:
	@rm -rvf geolocation-read-only

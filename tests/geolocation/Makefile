.PHONY: clean geolocation-read-only

all: geolocation-read-only

all2:
	make --always-make --directory=geolocation-read-only

geolocation-read-only: clean
	svn export http://geolocation.googlecode.com/svn/trunk/ $@

clean:
	@rm -rvf geolocation-read-only

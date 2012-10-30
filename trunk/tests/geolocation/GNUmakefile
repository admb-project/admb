.PHONY: clean geolocation-read-only

all:
	ADMB_HOME=$(ADMB_HOME) PATH=$(ADMB_HOME)/bin:$(PATH) make --always-make --directory=geolocation-read-only

geolocation-read-only: clean
	svn export http://geolocation.googlecode.com/svn/trunk/ $@

clean:
	rm -rvf geolocation-read-only

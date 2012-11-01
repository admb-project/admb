all:
	test  -d geolocation || svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" $(MAKE) --directory=geolocation

clean:
	rm -rvf geolocation

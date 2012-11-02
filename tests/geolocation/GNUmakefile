all:
	test  -d geolocation || svn export http://geolocation.googlecode.com/svn/trunk/ geolocation
	$(MAKE) ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)/bin:$(PATH)" --directory=geolocation

clean:
	rm -rvf geolocation

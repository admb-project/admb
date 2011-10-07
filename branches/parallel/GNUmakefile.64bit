.PHONY: tpl2cpp tpl2rem docs test
MPICF =  -DUSE_ADMPI $(shell mpic++ --showme:compile)


all:
	CC=gcc CXX=g++ CXXFLAGS="-m64 -ggdb ${MPICF} -DUSE_ADMPI" LIBPATH=../build/admb-10.1-linux-gcc4.4.3-64bit/objects DISK=../build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit ADMB_CONFIGURE=1 make --directory=src --file=linux.mak
	rm -rf `find build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit -type d -name .svn`
	@printf "\nBuild completed for admb-10.1-linux-gcc4.4.3-64bit\n"
	@printf "To install ADMB to '/usr/local/bin' and '/usr/local/admb', type 'make install'\n"

tpl2cpp:
	make --directory=src/nh99 --file=optg32-rh8-laplace.mak tpl2cpp.c

tpl2rem:
	make --directory=src/df1b2-separable --file=optg32-rh8-laplace.mak tpl2rem.c

debug:
	DEBUG=1 CC=gcc CXX=g++ CXXFLAGS="-m64" LIBPATH=../build/admb-10.1-linux-gcc4.4.3-64bit/objects DISK=../build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit ADMB_CONFIGURE=1 make --directory=src --file=linux.mak
	rm -rf `find build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit -type d -name .svn`
	@printf "\nBuild completed for admb-10.1-linux-gcc4.4.3-64bit\n"
	@printf "To install ADMB to '/usr/local/bin' and '/usr/local/admb', type 'make install'\n"

docs:
	make --directory=docs

dist:
	mkdir -p build/dist
	rm -rf build/dist/admb-10.1
	svn export . build/dist/admb-10.1
	rm -rf build/dist/admb-10.1/test
	cp configure build/dist/admb-10.1
	cd build/dist && zip -r admb-10.1.zip admb-10.1

verify:
	DISK=../build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit ADMB_CXXFLAGS=-m64 ADMB_LDFLAGS=-m64 make --directory=src --file=linux.mak verify

install:
	install -d -m 755 /usr/local/admb/bin /usr/local/admb/include /usr/local/admb/lib /usr/local/admb/docs /usr/local/admb/examples
	install -m 755 build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit/bin/* /usr/local/admb/bin
	install -m 644 build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit/include/* /usr/local/admb/include
	install -m 644 build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit/lib/* /usr/local/admb/lib
	install -m 644 LICENSE /usr/local/admb
	install -m 644 README.txt /usr/local/admb
	install -m 644 Makefile /usr/local/admb
	install -m 644 scripts/admb/admb-bin /usr/local/admb/bin
	cp -Rf build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit/docs/* /usr/local/admb/docs
	cp -Rf build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit/examples/* /usr/local/admb/examples

zip:
	cd build/admb-10.1-linux-gcc4.4.3-64bit; zip -r admb-10.1-linux-gcc4.4.3-64bit.zip admb-10.1-linux-gcc4.4.3-64bit

dmg:
	

test:
	export ADMB_HOME=${PWD}/build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit; export PATH=${PWD}/build/admb-10.1-linux-gcc4.4.3-64bit/admb-10.1-linux-gcc4.4.3-64bit/bin:$(PATH); make --directory=test

clean:
	rm -rvf build/admb-10.1-linux-gcc4.4.3-64bit
	make --directory=src --file=linux.mak clean
	make --directory=test clean
	make --directory=scripts/configure clean

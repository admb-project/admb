.PHONY: tpl2cpp tpl2rem docs test
MPICF =  -DUSE_ADMPI $(shell mpicc --showme:compile)

all:
	CC=gcc CXX=mpicxx CXXFLAGS="-ggdb ${MPICF} -DUSE_ADMPI" LIBPATH=../build/unix/objects DISK=../build/unix/unix ADMB_CONFIGURE=1 make --directory=src --file=linux.mak
	rm -rf `find build/unix/unix -type d -name .svn`
	@printf "\nBuild completed for unix\n"
	@printf "To install ADMB to '/usr/local/bin' and '/usr/local/admb', type 'make install'\n"

tpl2cpp:
	make --directory=src/nh99 --file=optg32-rh8-laplace.mak tpl2cpp.c

tpl2rem:
	make --directory=src/df1b2-separable --file=optg32-rh8-laplace.mak tpl2rem.c

debug:
	DEBUG=1 CC=gcc CXX=mpicxx CXXFLAGS="-ggdb ${MPICF} -DUSE_ADMPI" LIBPATH=../build/unix/objects DISK=../build/unix/unix ADMB_CONFIGURE=1 make --directory=src --file=linux.mak
	rm -rf `find build/unix/unix -type d -name .svn`
	@printf "\nBuild completed for unix\n"
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
	DISK=../build/unix/unix ADMB_CXXFLAGS=-m32 ADMB_LDFLAGS=-m32 make --directory=src --file=linux.mak verify

install:
	install -d -m 755 /usr/local/admb/bin /usr/local/admb/include /usr/local/admb/lib /usr/local/admb/docs /usr/local/admb/examples
	install -m 755 build/unix/unix/bin/* /usr/local/admb/bin
	install -m 644 build/unix/unix/include/* /usr/local/admb/include
	install -m 644 build/unix/unix/lib/* /usr/local/admb/lib
	install -m 644 LICENSE /usr/local/admb
	install -m 644 README.txt /usr/local/admb
	install -m 644 Makefile /usr/local/admb
	install -m 644 scripts/admb/admb-bin /usr/local/admb/bin
	cp -Rf build/unix/unix/docs/* /usr/local/admb/docs
	cp -Rf build/unix/unix/examples/* /usr/local/admb/examples

zip:
	cd build/unix; zip -r unix.zip unix

dmg:
	

test:
	export ADMB_HOME=${PWD}/build/unix/unix; export PATH=${PWD}/build/unix/unix/bin:$(PATH); make --directory=test

clean:
	rm -rvf build/unix
	make --directory=src --file=linux.mak clean
	make --directory=test clean
	make --directory=scripts/configure clean

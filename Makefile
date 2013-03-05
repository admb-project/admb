.PHONY: tests

all: $(CXX)
dist: $(CXX)-dist
contrib: $(CXX)-contrib
verify: $(CXX)-verify
tests: $(CXX)-tests

installer:
	rm -f admb.zip admb
	ln -sf build/dist/ admb
	zip -r admb admb/*

clean:
	$(MAKE) --directory=contrib clean
	$(MAKE) --directory=tests clean

#MinGW
mingw: mingw-dist mingw-contrib
mingw-dist:
	$(MAKE) --directory=src --file=mingw.mak dists
mingw-contrib:
	$(MAKE) --directory=src --file=mingw.mak contrib
mingw-verify:
	$(MAKE) --directory=src --file=mingw.mak verify
mingw-tests:
	$(MAKE) --directory=src --file=mingw.mak tests

#Borland 5.5
bcc: bcc-dist bcc-contrib
bcc-dist:
	$(MAKE) --directory=src --file=bcc.mak dist
bcc-contrib:
	$(MAKE) --directory=src --file=bcc.mak contrib
bcc-verify:
	$(MAKE) --directory=src --file=bcc.mak verify
bcc-tests:
	$(MAKE) --directory=src --file=bcc.mak tests

#Microsoft Visual C++
cl: cl-dist cl-contrib
cl-dist:
	cd src& nmake /f cl.mak dist
cl-contrib:
	cd src& nmake /f cl.mak contrib
cl-verify:
	cd src& nmake /f cl.mak verify
cl-tests:
	cd tests& nmake /f cl.mak tests

#Oracle Solaris Studio
CC: CC-dist CC-contrib
CC-dist:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC dist
CC-contrib:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC contrib 
CC-verify:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC verify
CC-tests:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC tests

#Intel
icpc: icpc-dist icpc-contrib
icpc-dist:
	source /opt/intel/bin/compilervars.sh intel64& $(MAKE) --directory=src --file=linux.mak CXX=icpc CC=icc dist
icpc-contrib:
	source /opt/intel/bin/compilervars.sh intel64& $(MAKE) --directory=src --file=linux.mak CXX=icpc CC=icc contrib
icpc-verify:
	source /opt/intel/bin/compilervars.sh intel64& $(MAKE) --directory=src --file=linux.mak CXX=icpc CC=icc verify
icpc-tests:
	source /opt/intel/bin/compilervars.sh intel64& $(MAKE) --directory=src --file=linux.mak CXX=icpc CC=icc tests

#GNU
g++: g++-dist g++-contrib
g++-dist:
	$(MAKE) --directory=src --file=linux.mak CC=gcc CXX=g++ dist
g++-contrib:
	$(MAKE) --directory=src --file=linux.mak CC=gcc CXX=g++ contrib
g++-verify:
	$(MAKE) --directory=src --file=linux.mak CC=gcc CXX=g++ verify
g++-tests:
	$(MAKE) --directory=src --file=linux.mak CC=gcc CXX=g++ tests

#MacOS clang
c++: c++-dist c++-contrib
c++-dist:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=c++ dist
c++-contrib:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=c++ contrib
c++-verify:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=c++ verify
c++-tests:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=c++ tests

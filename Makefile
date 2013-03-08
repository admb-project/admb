#default targets depending on compiler
all: $(CXX)
dist: $(CXX)-dist
contrib: $(CXX)-contrib
verify: $(CXX)-verify
test: $(CXX)-tests
clean: $(CXX)-clean

installer:
	rm -f admb.zip admb
	ln -sf build/dist/ admb
	zip -r admb admb/*

#MinGW
mingw: mingw-dist mingw-contrib
mingw-dist:
	$(MAKE) --directory=src --file=mingw.mak dist
mingw-contrib:
	$(MAKE) --directory=src --file=mingw.mak contrib
mingw-verify:
	$(MAKE) --directory=src --file=mingw.mak verify
mingw-tests:
	$(MAKE) --directory=src --file=mingw.mak tests
mingw-clean:
	$(MAKE) --directory=src --file=mingw.mak clean

#Borland 5.5
bcc: bcc-dist bcc-contrib
bcc-dist:
	cd src& $(MAKE) -fbcc.mak dist
bcc-contrib:
	cd src& $(MAKE) -fbcc.mak contrib
bcc-verify:
	cd src& $(MAKE) -fbcc.mak verify
bcc-tests:
	cd src& $(MAKE) -fbcc.mak tests
bcc-clean:
	cd src& $(MAKE) -fbcc.mak clean

#Microsoft Visual C++
cl: cl-dist cl-contrib
cl-dist:
	cd src& nmake dist
cl-contrib:
	cd src& nmake contrib
cl-verify:
	cd src& nmake verify
cl-tests:
	cd src& nmake tests
cl-clean:
	cd src& nmake clean

#Oracle Solaris Studio
CC: CC-dist CC-contrib
CC-dist:
	$(MAKE) --directory=src CC=cc CXX=CC dist
CC-contrib:
	$(MAKE) --directory=src CC=cc CXX=CC contrib 
CC-verify:
	$(MAKE) --directory=src CC=cc CXX=CC verify
CC-tests:
	$(MAKE) --directory=src CC=cc CXX=CC tests
CC-clean:
	$(MAKE) --directory=src CC=cc CXX=CC clean

#Intel
icpc: icpc-dist icpc-contrib
icpc-dist:
	$(MAKE) --directory=src CXX=icpc CC=icc dist
icpc-contrib:
	$(MAKE) --directory=src CXX=icpc CC=icc contrib
icpc-verify:
	$(MAKE) --directory=src CXX=icpc CC=icc verify
icpc-tests:
	$(MAKE) --directory=src CXX=icpc CC=icc tests
icpc-clean:
	$(MAKE) --directory=src CXX=icpc CC=icc clean

#GNU
g++: g++-dist g++-contrib
g++-dist:
	$(MAKE) --directory=src CC=gcc CXX=g++ dist
g++-contrib:
	$(MAKE) --directory=src CC=gcc CXX=g++ contrib
g++-verify:
	$(MAKE) --directory=src CC=gcc CXX=g++ verify
g++-tests:
	$(MAKE) --directory=src CC=gcc CXX=g++ tests
g++-clean:
	$(MAKE) --directory=src CC=gcc CXX=g++ clean

#MacOS clang
c++: c++-dist c++-contrib
c++-dist:
	$(MAKE) --directory=src CC=cc CXX=c++ dist
c++-contrib:
	$(MAKE) --directory=src CC=cc CXX=c++ contrib
c++-verify:
	$(MAKE) --directory=src CC=cc CXX=c++ verify
c++-tests:
	$(MAKE) --directory=src CC=cc CXX=c++ tests
c++-clean:
	$(MAKE) --directory=src CC=cc CXX=c++ clean

#default targets depending on compiler
all: $(CXX)-all
verify: $(CXX)-verify
install: $(CXX)-install
clean: $(CXX)-clean

#Microsoft Visual C++
cl: cl-all
cl-all:
	cd src& nmake all
cl-verify:
	cd src& nmake verify
cl-install:
	cd src& nmake install
cl-clean:
	cd src& nmake clean

#GNU
g++: g++-all
g++-all:
	$(MAKE) --directory=src CC=gcc CXX=g++ all
g++-verify:
	$(MAKE) --directory=src CC=gcc CXX=g++ verify
g++-install:
	$(MAKE) --directory=src CC=gcc CXX=g++ install
g++-clean:
	$(MAKE) --directory=src CC=gcc CXX=g++ clean

#MacOS clang
clang++: c++-all
clang++-all: c++-all
clang++-verify: c++-verify
clang++-install: c++-install
clang++-clean: c++-clean

#default c++
c++: c++-all
c++-all:
	$(MAKE) --directory=src CC=cc CXX=c++ all
c++-verify:
	$(MAKE) --directory=src CC=cc CXX=c++ verify
c++-install:
	$(MAKE) --directory=src CC=cc CXX=c++ install
c++-clean:
	$(MAKE) --directory=src CC=cc CXX=c++ clean

#Oracle Solaris Studio
CC: CC-all
CC-all:
	$(MAKE) --directory=src CC=cc CXX=CC all
CC-verify:
	$(MAKE) --directory=src CC=cc CXX=CC verify
CC-install:
	$(MAKE) --directory=src CC=cc CXX=CC install
CC-clean:
	$(MAKE) --directory=src CC=cc CXX=CC clean

#Intel
icpc: icpc-all
icpc-all:
	$(MAKE) --directory=src CC=icc CXX=icpc all
icpc-verify:
	$(MAKE) --directory=src CC=icc CXX=icpc verify
icpc-install:
	$(MAKE) --directory=src CC=icc CXX=icpc install
icpc-clean:
	$(MAKE) --directory=src CC=icc CXX=icpc clean


#Unsupported Borland 5.5
bcc: bcc-all
bcc-all:
	cd src& $(MAKE) -fbcc.mak all
bcc-verify:
	cd src& $(MAKE) -fbcc.mak verify
bcc-install:
	cd src& $(MAKE) -fbcc.mak install
bcc-clean:
	cd src& $(MAKE) -fbcc.mak clean

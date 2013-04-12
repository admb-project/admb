#default targets depending on compiler
all: $(CXX)-all
verify: $(CXX)-verify
test: $(CXX)-test
install: $(CXX)-install
clean: $(CXX)-clean

help:
	@echo "Help"
	@echo "\tFor Clang C++ compiler,"
	@echo "\tmake clang++\n"
	@echo "\tFor GNU C++ compiler,"
	@echo "\tmake g++\n"
	@echo "\tFor Solaris Studio C++ compiler,"
	@echo "\tmake icpc\n"
	@echo "\tFor Intel C++ compiler,"
	@echo "\tmake CC\n"

installer:
	rm -f admb.zip admb
	ln -sf build/dist/ admb
	zip -r admb admb/*

#Microsoft Visual C++
cl: cl-all
cl-all:
	cd src& nmake all
cl-verify:
	cd src& nmake verify
cl-test:
	cd src& nmake tests
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
g++-test:
	$(MAKE) --directory=src CC=gcc CXX=g++ tests
g++-install:
	$(MAKE) --directory=src CC=gcc CXX=g++ install
g++-clean:
	$(MAKE) --directory=src CC=gcc CXX=g++ clean

#clang
clang++: clang++-all
clang++-all:
	$(MAKE) --directory=src CC=clang CXX=clang++ all
clang++-verify:
	$(MAKE) --directory=src CC=clang CXX=clang++ verify
clang++-test:
	$(MAKE) --directory=src CC=clang CXX=clang++ test
clang++-install:
	$(MAKE) --directory=src CC=clang CXX=clang++ install
clang++-clean:
	$(MAKE) --directory=src CC=clang CXX=clang++ clean

#default c++
c++: c++-all
c++-all:
	$(MAKE) --directory=src CC=cc CXX=c++ all
c++-verify:
	$(MAKE) --directory=src CC=cc CXX=c++ verify
c++-test:
	$(MAKE) --directory=src CC=cc CXX=c++ tests
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
CC-test:
	$(MAKE) --directory=src CC=cc CXX=CC tests
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
icpc-test:
	$(MAKE) --directory=src CC=icc CXX=icpc tests
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
bcc-test:
	cd src& $(MAKE) -fbcc.mak tests
bcc-install:
	cd src& $(MAKE) -fbcc.mak install
bcc-clean:
	cd src& $(MAKE) -fbcc.mak clean

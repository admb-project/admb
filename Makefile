#default targets depending on compiler
all: $(CXX)-all
src: $(CXX)-src
debug: $(CXX)-debug
contrib: $(CXX)-contrib
test: $(CXX)-test
verify: $(CXX)-verify
doc: $(CXX)-docs
shared: g++-shared
install: $(CXX)-install
clean: $(CXX)-clean

help:
	@echo "Help"
	@echo "\tFor GNU C++ compiler,"
	@echo "\tmake g++\n"
	@echo "\tFor Microsoft C++ compiler,"
	@echo "\tnmake cl\n"
	@echo "\tFor Clang C++ compiler,"
	@echo "\tmake clang++\n"
	@echo "\tFor Solaris Studio C++ compiler,"
	@echo "\tmake icpc\n"
	@echo "\tFor Intel C++ compiler,"
	@echo "\tmake CC\n"
	@echo "\tFor AMD C++ compiler(experimental),"
	@echo "\tmake openCC\n"

installer:
	rm -vf admb.zip build/admb
	cd build && ln -sf dist/ admb
	cd build && zip -r ../admb admb

#Microsoft Visual C++
cl: cl-all
cl-all: 
	nmake cl-src
	nmake cl-contrib
cl-debug:
	cd src& nmake DEBUG=1 all
	cd contrib& nmake DEBUG=1 all
cl-src:
	cd src& nmake all
cl-contrib:
	cd contrib& nmake all
cl-docs:
	cd docs& nmake all
cl-test:
	cd tests & nmake all
cl-verify:
	cd examples& nmake copy
	cd tests& nmake verify
cl-install:
	cd src& nmake install
cl-clean:
	cd src& nmake clean
	cd contrib& nmake clean

#GNU
g++: g++-all
g++-all: 
	$(MAKE) g++-src
	$(MAKE) g++-contrib
g++-debug:
	$(MAKE) g++-all DEBUG=1
g++-src:
	$(MAKE) --directory=src CC=gcc CXX=g++ all
g++-contrib:
	$(MAKE) --directory=contrib CC=gcc CXX=g++ all
g++-docs:
	$(MAKE) --directory=docs CC=gcc CXX=g++ all
g++-test:
	$(MAKE) --directory=tests CC=gcc CXX=g++ all
g++-verify:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=tests CC=gcc CXX=g++ verify
g++-shared:
	$(MAKE) --directory=src CC=gcc CXX=g++ BUILD_SHARED_LIBRARY=1 all shared
g++-install:
	$(MAKE) --directory=src CC=gcc CXX=g++ install
g++-clean:
	$(MAKE) --directory=src CC=gcc CXX=g++ clean
	$(MAKE) --directory=contrib CC=gcc CXX=g++ clean

#clang
clang++: clang++-all
clang++-all:
	$(MAKE) clang++-src
	$(MAKE) clang++-contrib
clang++-debug:
	$(MAKE) clang++-all DEBUG=1
clang++-src:
	$(MAKE) --directory=src CC=clang CXX=clang++ all
clang++-contrib:
	$(MAKE) --directory=contrib CC=clang CXX=clang++ all
clang++-docs:
	$(MAKE) --directory=docs CC=clang CXX=clang++ all
clang++-test:
	$(MAKE) --directory=tests CC=clang CXX=clang++ all
clang++-verify:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=tests CC=clang CXX=clang++ verify
clang++-install:
	$(MAKE) --directory=src CC=clang CXX=clang++ install
clang++-clean:
	$(MAKE) --directory=src CC=clang CXX=clang++ clean
	$(MAKE) --directory=contrib CC=clang CXX=clang++ clean

#default c++
c++: c++-all
c++-all:
	$(MAKE) c++-src
	$(MAKE) c++-contrib
c++-debug:
	$(MAKE) c++-all DEBUG=1
c++-src:
	$(MAKE) --directory=src CC=cc CXX=c++ all
c++-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=c++ all
c++-docs:
	$(MAKE) --directory=docs CC=cc CXX=c++ all
c++-test:
	$(MAKE) --directory=tests CC=cc CXX=c++ all
c++-verify:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=tests CC=cc CXX=c++ verify
c++-install:
	$(MAKE) --directory=src CC=cc CXX=c++ install
c++-clean:
	$(MAKE) --directory=src CC=cc CXX=c++ clean
	$(MAKE) --directory=contrib CC=cc CXX=c++ clean

#Oracle Solaris Studio
CC: CC-all
CC-all:
	$(MAKE) CC-src
	$(MAKE) CC-contrib
CC-debug:
	$(MAKE) CC-all DEBUG=1
CC-src:
	$(MAKE) --directory=src CC=cc CXX=CC all
CC-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=CC all
CC-docs:
	$(MAKE) --directory=docs CC=cc CXX=CC all
CC-test:
	$(MAKE) --directory=tests CC=cc CXX=CC all
CC-verify:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=tests CC=cc CXX=CC verify
CC-install:
	$(MAKE) --directory=src CC=cc CXX=CC install
CC-clean:
	$(MAKE) --directory=src CC=cc CXX=CC clean
	$(MAKE) --directory=contrib CC=cc CXX=CC clean

#Intel
icpc: icpc-all
icpc-all:
	$(MAKE) icpc-src 
	$(MAKE) icpc-contrib
icpc-debug:
	$(MAKE) icpc-all DEBUG=1
icpc-src:
	$(MAKE) --directory=src CC=icc CXX=icpc all
icpc-contrib:
	$(MAKE) --directory=contrib CC=icc CXX=icpc all
icpc-docs:
	$(MAKE) --directory=docs CC=icc CXX=icpc all
icpc-test:
	$(MAKE) --directory=tests CC=icc CXX=icpc all
icpc-verify:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=tests CC=icc CXX=icpc verify
icpc-install:
	$(MAKE) --directory=src CC=icc CXX=icpc install
icpc-clean:
	$(MAKE) --directory=src CC=icc CXX=icpc clean
	$(MAKE) --directory=contrib CC=icc CXX=icpc clean

#AMD
openCC: openCC-all
openCC-all: 
	$(MAKE) openCC-src
	$(MAKE) openCC-contrib
openCC-debug:
	$(MAKE) openCC-all DEBUG=1
openCC-src:
	$(MAKE) --directory=src CC=opencc CXX=openCC all
openCC-contrib:
	$(MAKE) --directory=contrib CC=opencc CXX=openCC all
openCC-docs:
	$(MAKE) --directory=docs CC=opencc CXX=openCC all
openCC-test:
	$(MAKE) --directory=tests CC=opencc CXX=openCC all
openCC-verify:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=tests CC=opencc CXX=openCC verify
openCC-install:
	$(MAKE) --directory=src CC=opencc CXX=openCC install
openCC-clean:
	$(MAKE) --directory=src CC=opencc CXX=openCC clean
	$(MAKE) --directory=contrib CC=opencc CXX=openCC clean

#Unsupported Borland 5.5
bcc: bcc-all
bcc-all: bcc-src
bcc-src:
	cd src& $(MAKE) -fbcc.mak all
bcc-debug:
bcc-verify:
	cd src& $(MAKE) -fbcc.mak verify
bcc-test:
	cd src& $(MAKE) -fbcc.mak tests
bcc-install:
	cd src& $(MAKE) -fbcc.mak install
bcc-clean:
	cd src& $(MAKE) -fbcc.mak clean

check:
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"

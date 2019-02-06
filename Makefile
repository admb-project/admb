#default targets depending on compiler
#DEBUG=yes

all:
	$(MAKE) $(CXX)-all DEBUG=$(DEBUG)
	@echo ADMB build completed.
dist: $(CXX)-dist
	@echo ADMB build dist completed.
src: $(CXX)-src
debug:
	$(MAKE) $(CXX)-all DEBUG=yes
	@echo ADMB debug build completed.
contrib: $(CXX)-contrib
test: verify
	$(MAKE) $(CXX)-test DEBUG=$(DEBUG)
verify:
	$(MAKE) $(CXX)-verify DEBUG=$(DEBUG)
doc: $(CXX)-docs
shared: $(CXX)-shared
install: $(CXX)-install
check: $(CXX)-check
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"
clean: $(CXX)-clean
coverage: $(CXX)-coverage

help:
	@echo Read INSTALL.txt for installation help.

installer:
	rm -vf admb.zip build/admb
	cd build && ln -sf dist/ admb
	cd build && zip -9 -r ../admb admb

#Microsoft Visual C++
cl: cl-all
cl-all: 
	nmake cl-src
	nmake cl-contrib
	nmake cl-shared
cl-dist: 
	nmake cl-src
	nmake cl-contrib
cl-debug:
	pushd src& nmake DEBUG=yes all
	pushd contrib& nmake DEBUG=yes all
cl-src:
	pushd src& nmake all
cl-contrib:
	pushd contrib& nmake all
cl-docs:
	pushd docs& nmake all
cl-test:
	pushd tests & nmake all
cl-verify:
	pushd tests& nmake verify
cl-shared:
	pushd src& nmake shared
	pushd contrib& nmake shared
cl-install:
	pushd src& nmake install
cl-check:
	pushd src& nmake check
cl-clean:
	pushd src& nmake clean
	pushd contrib& nmake clean
	pushd scripts& nmake clean
	pushd tests& nmake clean

#GNU
g++: g++-all
g++-all: 
	$(MAKE) g++-src
	$(MAKE) g++-contrib
	$(MAKE) g++-shared
g++-dist: 
	$(MAKE) g++-src
	$(MAKE) g++-contrib
g++-debug:
	$(MAKE) g++-all DEBUG=yes
g++-src:
	$(MAKE) --directory=src CC=gcc CXX=g++ all
g++-contrib:
	$(MAKE) --directory=contrib CC=gcc CXX=g++ all
g++-docs:
	$(MAKE) --directory=docs CC=gcc CXX=g++ all
g++-test:
	$(MAKE) --directory=tests CC=gcc CXX=g++ all
g++-coverage:
	$(MAKE) --directory=src CC=gcc CXX=g++ COVERAGE=yes dist
	$(MAKE) --directory=tests CC=gcc CXX=g++ coverage
g++-verify:
	$(MAKE) --directory=tests CC=gcc CXX=g++ verify
g++-shared:
	$(MAKE) --directory=src CC=gcc CXX=g++ SHARED=-shared shared
	$(MAKE) --directory=contrib CC=gcc CXX=g++ SHARED=-shared shared
g++-install:
	$(MAKE) --directory=src CC=gcc CXX=g++ install
g++-check:
	$(MAKE) --directory=src CC=gcc CXX=g++ check
g++-clean:
	$(MAKE) --directory=src CC=gcc CXX=g++ clean
	$(MAKE) --directory=contrib CC=gcc CXX=g++ clean
	$(MAKE) --directory=scripts CC=gcc CXX=g++ clean
	$(MAKE) --directory=tests CC=gcc CXX=g++ clean

#clang
clang++: clang++-all
clang++-all:
	$(MAKE) clang++-src
	$(MAKE) clang++-contrib
	$(MAKE) clang++-shared
clang++-dist:
	$(MAKE) clang++-src
	$(MAKE) clang++-contrib
clang++-debug:
	$(MAKE) clang++-all DEBUG=yes
clang++-src:
	$(MAKE) --directory=src CC=clang CXX=clang++ all
clang++-contrib:
	$(MAKE) --directory=contrib CC=clang CXX=clang++ all
clang++-docs:
	$(MAKE) --directory=docs CC=clang CXX=clang++ all
clang++-test:
	$(MAKE) --directory=tests CC=clang CXX=clang++ all
clang++-coverage:
	$(MAKE) --directory=src CC=clang CXX=clang++ COVERAGE=yes dist
	$(MAKE) --directory=tests CC=clang CXX=clang++ coverage
clang++-verify:
	$(MAKE) --directory=tests CC=clang CXX=clang++ verify
clang++-shared:
	$(MAKE) --directory=src CC=clang CXX=clang++ SHARED=-shared shared
	$(MAKE) --directory=contrib CC=clang CXX=clang++ SHARED=-shared shared
clang++-install:
	$(MAKE) --directory=src CC=clang CXX=clang++ install
clang++-check:
	$(MAKE) --directory=src CC=clang CXX=clang++ check
clang++-clean:
	$(MAKE) --directory=src CC=clang CXX=clang++ clean
	$(MAKE) --directory=contrib CC=clang CXX=clang++ clean
	$(MAKE) --directory=scripts CC=clang CXX=clang++ clean
	$(MAKE) --directory=tests CC=clang CXX=clang++ clean

#default c++
c++: c++-all
c++-all:
	$(MAKE) c++-src
	$(MAKE) c++-contrib
	$(MAKE) c++-shared
c++-dist:
	$(MAKE) c++-src
	$(MAKE) c++-contrib
c++-debug:
	$(MAKE) c++-all DEBUG=yes
c++-src:
	$(MAKE) --directory=src CC=cc CXX=c++ all
c++-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=c++ all
c++-docs:
	$(MAKE) --directory=docs CC=cc CXX=c++ all
c++-coverage:
	$(MAKE) --directory=src CC=cc CXX=c++ COVERAGE=yes dist
	$(MAKE) --directory=tests CC=cc CXX=c++ coverage
c++-test:
	$(MAKE) --directory=tests CC=cc CXX=c++ all
c++-verify:
	$(MAKE) --directory=tests CC=cc CXX=c++ verify
c++-shared:
	$(MAKE) --directory=src CC=cc CXX=c++ SHARED=-shared shared
	$(MAKE) --directory=contrib CC=cc CXX=c++ SHARED=-shared shared
c++-install:
	$(MAKE) --directory=src CC=cc CXX=c++ install
c++-check:
	$(MAKE) --directory=src CC=cc CXX=c++ check 
c++-clean:
	$(MAKE) --directory=src CC=cc CXX=c++ clean
	$(MAKE) --directory=contrib CC=cc CXX=c++ clean
	$(MAKE) --directory=scripts CC=cc CXX=c++ clean
	$(MAKE) --directory=tests CC=cc CXX=c++ clean

#Oracle Solaris Studio
CC: CC-all
CC-all:
	$(MAKE) CC-src
	$(MAKE) CC-contrib
	$(MAKE) CC-shared
CC-dist:
	$(MAKE) CC-src
	$(MAKE) CC-contrib
CC-debug:
	$(MAKE) CC-all DEBUG=yes
CC-src:
	$(MAKE) --directory=src CC=cc CXX=CC all
CC-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=CC all
CC-docs:
	$(MAKE) --directory=docs CC=cc CXX=CC all
CC-test:
	$(MAKE) --directory=tests CC=cc CXX=CC all
CC-verify:
	$(MAKE) --directory=tests CC=cc CXX=CC verify
CC-shared:
	$(MAKE) --directory=src CC=cc CXX=CC SHARED=-shared shared
	$(MAKE) --directory=contrib CC=cc CXX=CC SHARED=-shared shared
CC-install:
	$(MAKE) --directory=src CC=cc CXX=CC install
CC-check:
	$(MAKE) --directory=src CC=cc CXX=CC check
CC-clean:
	$(MAKE) --directory=src CC=cc CXX=CC clean
	$(MAKE) --directory=contrib CC=cc CXX=CC clean
	$(MAKE) --directory=scripts CC=cc CXX=CC clean
	$(MAKE) --directory=tests CC=cc CXX=CC clean

#Intel
icpc: icpc-all
icpc-all:
	$(MAKE) icpc-src 
	$(MAKE) icpc-contrib
	$(MAKE) icpc-shared
icpc-dist:
	$(MAKE) icpc-src 
	$(MAKE) icpc-contrib
icpc-debug:
	$(MAKE) icpc-all DEBUG=yes
icpc-src:
	$(MAKE) --directory=src CC=icc CXX=icpc all
icpc-contrib:
	$(MAKE) --directory=contrib CC=icc CXX=icpc all
icpc-docs:
	$(MAKE) --directory=docs CC=icc CXX=icpc all
icpc-test:
	$(MAKE) --directory=tests CC=icc CXX=icpc all
icpc-verify:
	$(MAKE) --directory=tests CC=icc CXX=icpc verify
icpc-shared:
	$(MAKE) --directory=src CC=icc CXX=icpc SHARED=-shared shared
	$(MAKE) --directory=contrib CC=icc CXX=icpc SHARED=-shared shared
icpc-install:
	$(MAKE) --directory=src CC=icc CXX=icpc install
icpc-check:
	$(MAKE) --directory=src CC=icc CXX=icpc check
icpc-clean:
	$(MAKE) --directory=src CC=icc CXX=icpc clean
	$(MAKE) --directory=contrib CC=icc CXX=icpc clean
	$(MAKE) --directory=scripts CC=icc CXX=icpc clean
	$(MAKE) --directory=tests CC=icc CXX=icpc clean

#AMD
openCC: openCC-all
openCC-all: 
	$(MAKE) openCC-src
	$(MAKE) openCC-contrib
	$(MAKE) openCC-shared
openCC-dist: 
	$(MAKE) openCC-src
	$(MAKE) openCC-contrib
openCC-debug:
	$(MAKE) openCC-all DEBUG=yes
openCC-src:
	$(MAKE) --directory=src CC=opencc CXX=openCC all
openCC-contrib:
	$(MAKE) --directory=contrib CC=opencc CXX=openCC all
openCC-docs:
	$(MAKE) --directory=docs CC=opencc CXX=openCC all
openCC-test:
	$(MAKE) --directory=tests CC=opencc CXX=openCC all
openCC-verify:
	$(MAKE) --directory=tests CC=opencc CXX=openCC verify
openCC-shared:
	$(MAKE) --directory=src CC=opencc CXX=openCC SHARED=-shared shared
	$(MAKE) --directory=contrib CC=opencc CXX=openCC SHARED=-shared shared
openCC-install:
	$(MAKE) --directory=src CC=opencc CXX=openCC install
openCC-check:
	$(MAKE) --directory=src CC=opencc CXX=openCC check
openCC-clean:
	$(MAKE) --directory=src CC=opencc CXX=openCC clean
	$(MAKE) --directory=contrib CC=opencc CXX=openCC clean
	$(MAKE) --directory=scripts CC=opencc CXX=openCC clean
	$(MAKE) --directory=tests CC=opencc CXX=openCC clean

#Unsupported Borland 5.5
bcc: bcc-all
bcc-all: bcc-src
bcc-dist: bcc-src
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

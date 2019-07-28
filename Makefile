#default targets depending on compiler
#DEBUG=yes

all:
	$(MAKE) $(CXX)-all DEBUG=$(DEBUG)
	@echo ADMB build all completed.
	@echo Check README.txt for usage and installation information.
dist:
	$(MAKE) $(CXX)-dist DEBUG=$(DEBUG)
	@echo ADMB build dist completed.
	@echo Check README.txt for usage and installation information.
core:
	$(MAKE) $(CXX)-core DEBUG=$(DEBUG)
	@echo ADMB build core completed.
debug:
	$(MAKE) $(CXX)-all DEBUG=yes
	@echo ADMB build debug completed.
	@echo Check README.txt for usage and installation information.
contrib:
	$(MAKE) $(CXX)-contrib DEBUG=$(DEBUG)
test: verify
	$(MAKE) $(CXX)-test DEBUG=$(DEBUG)
gtests:
	$(MAKE) $(CXX)-gtests DEBUG=$(DEBUG)
verify:
	$(MAKE) $(CXX)-verify DEBUG=$(DEBUG)
doc: $(CXX)-docs
shared: $(CXX)-shared
	$(MAKE) $(CXX)-shared DEBUG=$(DEBUG)
	@echo ADMB build shared completed.
	@echo Check README.txt for usage and installation information.
install: $(CXX)-install
check: $(CXX)-check
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"
clean: $(CXX)-clean
coverage:
	$(MAKE) $(CXX)-coverage DEBUG=$(DEBUG)

help:
	@echo Read INSTALL.txt for installation help.

installer:
	rm -vf admb.zip build/admb
	cd build && ln -sf dist/ admb
	cd build && zip -9 -r ../admb admb

#Microsoft Visual C++
cl: cl-all
cl-all: 
	nmake cl-dist
	nmake cl-shared
cl-dist: 
	nmake cl-core
	nmake cl-contrib
cl-debug:
	pushd src& nmake DEBUG=yes all
	pushd contrib& nmake DEBUG=yes all
cl-core:
	pushd src& nmake all
cl-contrib:
	pushd contrib& nmake all
cl-docs:
	pushd docs& nmake all
cl-test:
	pushd tests & nmake all
cl-gtests:
	pushd tests & nmake test-gtests
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
	$(MAKE) g++-dist
	$(MAKE) g++-shared
g++-dist: 
	$(MAKE) g++-core
	$(MAKE) g++-contrib
g++-debug:
	$(MAKE) g++-all DEBUG=yes
g++-core:
	$(MAKE) --directory=src CC=gcc CXX=g++ all
g++-contrib:
	$(MAKE) --directory=contrib CC=gcc CXX=g++ all
g++-docs:
	$(MAKE) --directory=docs CC=gcc CXX=g++ all
g++-test:
	$(MAKE) --directory=tests CC=gcc CXX=g++ all
g++-gtests:
	$(MAKE) --directory=tests CC=gcc CXX=g++ all-gtests
g++-coverage:
	$(MAKE) --directory=src CC=gcc CXX=g++ SAFE_ONLY=yes dist
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
	$(MAKE) clang++-dist
	$(MAKE) clang++-shared
clang++-dist:
	$(MAKE) clang++-core
	$(MAKE) clang++-contrib
clang++-debug:
	$(MAKE) clang++-all DEBUG=yes
clang++-core:
	$(MAKE) --directory=src CC=clang CXX=clang++ all
clang++-contrib:
	$(MAKE) --directory=contrib CC=clang CXX=clang++ all
clang++-docs:
	$(MAKE) --directory=docs CC=clang CXX=clang++ all
clang++-test:
	$(MAKE) --directory=tests CC=clang CXX=clang++ all
clang++-gtests:
	$(MAKE) --directory=tests CC=clang CXX=clang++ all-gtests
clang++-coverage:
	$(MAKE) --directory=src CC=clang CXX=clang++ SAFE_ONLY=yes dist
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
	$(MAKE) c++-dist
	$(MAKE) c++-shared
c++-dist:
	$(MAKE) c++-core
	$(MAKE) c++-contrib
c++-debug:
	$(MAKE) c++-all DEBUG=yes
c++-core:
	$(MAKE) --directory=src CC=cc CXX=c++ all
c++-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=c++ all
c++-docs:
	$(MAKE) --directory=docs CC=cc CXX=c++ all
c++-coverage:
	$(MAKE) --directory=src CC=cc CXX=c++ SAFE_ONLY=yes dist
	$(MAKE) --directory=tests CC=cc CXX=c++ coverage
c++-test:
	$(MAKE) --directory=tests CC=cc CXX=c++ all
c++-gtests:
	$(MAKE) --directory=tests CC=cc CXX=c++ all-gtests
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
	$(MAKE) CC-dist
	$(MAKE) CC-shared
CC-dist:
	$(MAKE) CC-core
	$(MAKE) CC-contrib
CC-debug:
	$(MAKE) CC-all DEBUG=yes
CC-core:
	$(MAKE) --directory=src CC=cc CXX=CC all
CC-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=CC all
CC-docs:
	$(MAKE) --directory=docs CC=cc CXX=CC all
CC-test:
	$(MAKE) --directory=tests CC=cc CXX=CC all
CC-gtests:
	$(MAKE) --directory=tests CC=cc CXX=CC all-gtests
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
	$(MAKE) icpc-dist
	$(MAKE) icpc-shared
icpc-dist:
	$(MAKE) icpc-core
	$(MAKE) icpc-contrib
icpc-debug:
	$(MAKE) icpc-all DEBUG=yes
icpc-core:
	$(MAKE) --directory=src CC=icc CXX=icpc all
icpc-contrib:
	$(MAKE) --directory=contrib CC=icc CXX=icpc all
icpc-docs:
	$(MAKE) --directory=docs CC=icc CXX=icpc all
icpc-test:
	$(MAKE) --directory=tests CC=icc CXX=icpc all
icpc-gtests:
	$(MAKE) --directory=tests CC=icc CXX=icpc all-gtests
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
	$(MAKE) openCC-dist
	$(MAKE) openCC-shared
openCC-dist: 
	$(MAKE) openCC-core
	$(MAKE) openCC-contrib
openCC-debug:
	$(MAKE) openCC-all DEBUG=yes
openCC-core:
	$(MAKE) --directory=src CC=opencc CXX=openCC all
openCC-contrib:
	$(MAKE) --directory=contrib CC=opencc CXX=openCC all
openCC-docs:
	$(MAKE) --directory=docs CC=opencc CXX=openCC all
openCC-test:
	$(MAKE) --directory=tests CC=opencc CXX=openCC all
openCC-gtests:
	$(MAKE) --directory=tests CC=opencc CXX=openCC all-gtests
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

#scan-build
analyze-c++: analyze-c++-all
analyze-c++-all:
	$(MAKE) analyze-c++-dist
	$(MAKE) analyze-c++-shared
analyze-c++-dist:
	$(MAKE) analyze-c++-core
	$(MAKE) analyze-c++-contrib
analyze-c++-debug:
	$(MAKE) analyze-c++-all DEBUG=yes
analyze-c++-core:
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ all
analyze-c++-contrib:
	$(MAKE) --directory=contrib CC=analyze-cc CXX=analyze-c++ all
analyze-c++-docs:
	$(MAKE) --directory=docs CC=analyze-cc CXX=analyze-c++ all
analyze-c++-coverage:
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ SAFE_ONLY=yes dist
	$(MAKE) --directory=tests CC=analyze-cc CXX=analyze-c++ coverage
analyze-c++-test:
	$(MAKE) --directory=tests CC=analyze-cc CXX=analyze-c++ all
analyze-c++-gtests:
	$(MAKE) --directory=tests CC=analyze-cc CXX=analyze-c++ all-gtests
analyze-c++-verify:
	$(MAKE) --directory=tests CC=analyze-cc CXX=analyze-c++ verify
analyze-c++-shared:
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ SHARED=-shared shared
	$(MAKE) --directory=contrib CC=analyze-cc CXX=analyze-c++ SHARED=-shared shared
analyze-c++-install:
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ install
analyze-c++-check:
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ check 
analyze-c++-clean:
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ clean
	$(MAKE) --directory=contrib CC=analyze-cc CXX=analyze-c++ clean
	$(MAKE) --directory=scripts CC=analyze-cc CXX=analyze-c++ clean
	$(MAKE) --directory=tests CC=analyze-cc CXX=analyze-c++ clean

#Unsupported Borland 5.5
bcc: bcc-all
bcc-all: bcc-src
bcc-dist: bcc-src
bcc-src:
	cd src& $(MAKE) -fbcc.mak all
bcc-debug:
bcc-verify:
	cd src& $(MAKE) -fbcc.mak verify
bcc-gtests:
bcc-test:
	cd src& $(MAKE) -fbcc.mak tests
bcc-install:
	cd src& $(MAKE) -fbcc.mak install
bcc-clean:
	cd src& $(MAKE) -fbcc.mak clean

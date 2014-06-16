#default targets depending on compiler
#DEBUG=yes

all:
	$(MAKE) $(CXX)-all DEBUG=$(DEBUG)
	@echo ADMB build completed.
src: $(CXX)-src
debug:
	$(MAKE) $(CXX)-all DEBUG=yes
	@echo ADMB debug build completed.
contrib: $(CXX)-contrib
test: verify
	$(MAKE) $(CXX)-test DEBUG=$(DEBUG)
copy: $(CXX)-copy
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

help:
	@echo Read INSTALL.txt for installation help.

installer:
	rm -vf admb.zip build/admb
	cd build && ln -sf dist/ admb
	cd build && zip -r ../admb admb

#Microsoft Visual C++
cl: cl-all
cl-all: 
	nmake cl-src
	nmake cl-contrib
	nmake cl-copy
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
cl-copy:
	pushd examples& nmake copy
	pushd contrib& nmake copy
cl-verify:
	pushd tests& nmake verify
cl-shared:
	pushd src& nmake shared
	pushd contrib& nmake shared
	nmake cl-copy
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
	$(MAKE) g++-copy
g++-debug:
	$(MAKE) g++-all DEBUG=yes
g++-src:
	$(MAKE) --directory=src CC=gcc CXX=g++ all
	$(MAKE) --directory=src CC=gcc CXX=g++ SHARED=-shared libs
g++-contrib:
	$(MAKE) --directory=contrib CC=gcc CXX=g++ all
	$(MAKE) --directory=contrib CC=gcc CXX=g++ SHARED=-shared libs
g++-docs:
	$(MAKE) --directory=docs CC=gcc CXX=g++ all
g++-test:
	$(MAKE) --directory=tests CC=gcc CXX=g++ all
g++-copy:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=contrib copy
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
	$(MAKE) clang++-copy
clang++-debug:
	$(MAKE) clang++-all DEBUG=yes
clang++-src:
	$(MAKE) --directory=src CC=clang CXX=clang++ all
	$(MAKE) --directory=src CC=clang CXX=clang++ SHARED=-shared libs
clang++-contrib:
	$(MAKE) --directory=contrib CC=clang CXX=clang++ all
	$(MAKE) --directory=contrib CC=clang CXX=clang++ SHARED=-shared libs
clang++-docs:
	$(MAKE) --directory=docs CC=clang CXX=clang++ all
clang++-test:
	$(MAKE) --directory=tests CC=clang CXX=clang++ all
clang++-copy:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=contrib copy
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
	$(MAKE) c++-copy
c++-debug:
	$(MAKE) c++-all DEBUG=yes
c++-src:
	$(MAKE) --directory=src CC=cc CXX=c++ all
	$(MAKE) --directory=src CC=cc CXX=c++ SHARED=-shared libs
c++-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=c++ all
	$(MAKE) --directory=contrib CC=cc CXX=c++ SHARED=-shared libs
c++-docs:
	$(MAKE) --directory=docs CC=cc CXX=c++ all
c++-test:
	$(MAKE) --directory=tests CC=cc CXX=c++ all
c++-copy:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=contrib copy
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
	$(MAKE) CC-copy
CC-debug:
	$(MAKE) CC-all DEBUG=yes
CC-src:
	$(MAKE) --directory=src CC=cc CXX=CC all
	$(MAKE) --directory=src CC=cc CXX=CC SHARED=-shared libs
CC-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=CC all
	$(MAKE) --directory=contrib CC=cc CXX=CC SHARED=-shared libs
CC-docs:
	$(MAKE) --directory=docs CC=cc CXX=CC all
CC-test:
	$(MAKE) --directory=tests CC=cc CXX=CC all
CC-copy:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=contrib copy
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
	$(MAKE) icpc-copy
icpc-debug:
	$(MAKE) icpc-all DEBUG=yes
icpc-src:
	$(MAKE) --directory=src CC=icc CXX=icpc all
	$(MAKE) --directory=src CC=icc CXX=icpc SHARED=-shared libs
icpc-contrib:
	$(MAKE) --directory=contrib CC=icc CXX=icpc all
	$(MAKE) --directory=contrib CC=icc CXX=icpc SHARED=-shared libs
icpc-docs:
	$(MAKE) --directory=docs CC=icc CXX=icpc all
icpc-test:
	$(MAKE) --directory=tests CC=icc CXX=icpc all
icpc-copy:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=contrib copy
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
	$(MAKE) openCC-copy
openCC-debug:
	$(MAKE) openCC-all DEBUG=yes
openCC-src:
	$(MAKE) --directory=src CC=opencc CXX=openCC all
	$(MAKE) --directory=src CC=opencc CXX=openCC SHARED=-shared libs
openCC-contrib:
	$(MAKE) --directory=contrib CC=opencc CXX=openCC all
	$(MAKE) --directory=contrib CC=opencc CXX=openCC SHARED=-shared libs
openCC-docs:
	$(MAKE) --directory=docs CC=opencc CXX=openCC all
openCC-test:
	$(MAKE) --directory=tests CC=opencc CXX=openCC all
openCC-copy:
	$(MAKE) --directory=examples copy
	$(MAKE) --directory=contrib copy
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

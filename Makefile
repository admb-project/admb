#default targets depending on compiler
#DEBUG=yes

dist:
	$(MAKE) $(CXX)-dist DEBUG=$(DEBUG)
	@echo ADMB build dist completed.
	@echo Check README.txt for usage and installation information.
all:
	$(MAKE) $(CXX)-all DEBUG=$(DEBUG)
	@echo ADMB build all completed.
	@echo Check README.txt for usage and installation information.
core:
	$(MAKE) $(CXX)-core DEBUG=$(DEBUG)
	@echo ADMB build core completed.
debug:
	$(MAKE) $(CXX)-all DEBUG=yes
	@echo ADMB build debug completed.
contribs:
	$(MAKE) $(CXX)-contribs DEBUG=$(DEBUG)
	@echo ADMB build contribs completed.
test: verify
gtests:
	$(MAKE) $(CXX)-gtests DEBUG=$(DEBUG)
verify:
	$(MAKE) $(CXX)-verify DEBUG=$(DEBUG)
doc: $(CXX)-docs
shared: $(CXX)-shared
	$(MAKE) $(CXX)-shared DEBUG=$(DEBUG)
	@echo ADMB build shared completed.
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

installer: zip

zip: $(CXX)-zip

#Microsoft Visual C++
cl: cl-all
cl-all: 
	nmake /nologo cl-dist
	nmake /nologo cl-shared
	pushd src& nmake /nologo copy
cl-dist: 
	nmake /nologo cl-contribs
cl-debug:
	pushd src& nmake /nologo DEBUG=!DEBUG! all
	pushd contrib& nmake /nologo DEBUG=yes all
cl-core:
	pushd src& nmake /nologo all
cl-contribs: cl-core
	pushd contrib& nmake /nologo all
cl-docs:
	pushd docs& nmake /nologo all
cl-gtests:
	pushd tests & nmake /nologo test-gtests
cl-verify:
	pushd tests& nmake /nologo verify
cl-shared:
	pushd src& nmake /nologo shared
	pushd contrib& nmake /nologo shared
cl-install:
	pushd src& nmake /nologo install
cl-check:
	pushd src& nmake /nologo check
cl-clean:
	pushd src& nmake /nologo clean
	pushd contrib& nmake /nologo clean
	pushd scripts& nmake /nologo clean
	pushd tests& nmake /nologo clean
	pushd examples& nmake /nologo clean
cl-zip:
	pushd src& nmake /nologo zip

#GNU
g++: g++-all
g++-all: 
	$(MAKE) g++-dist
	$(MAKE) g++-shared
	$(MAKE) --directory=src CC=gcc CXX=g++ copy
g++-dist: 
	$(MAKE) g++-core
	$(MAKE) g++-contribs
g++-debug:
	$(MAKE) g++-all DEBUG=yes
g++-core:
	$(MAKE) --directory=src CC=gcc CXX=g++ all
g++-contribs: g++-core
	$(MAKE) --directory=contrib CC=gcc CXX=g++ all
g++-docs:
	$(MAKE) --directory=docs CC=gcc CXX=g++ all
g++-gtests:
	$(MAKE) --directory=tests CC=gcc CXX=g++ unit-gtests
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
	$(MAKE) --directory=examples CC=gcc CXX=g++ clean
g++-zip:
	$(MAKE) --directory=src CC=gcc CXX=g++ zip

#clang
clang++: clang++-all
clang++-all:
	$(MAKE) clang++-dist
	$(MAKE) clang++-shared
	$(MAKE) --directory=src CC=clang CXX=clang++ copy
clang++-dist:
	$(MAKE) clang++-contribs
clang++-debug:
	$(MAKE) clang++-all DEBUG=yes
clang++-core:
	$(MAKE) --directory=src CC=clang CXX=clang++ all
clang++-contribs: clang++-core
	$(MAKE) --directory=contrib CC=clang CXX=clang++ all
clang++-docs:
	$(MAKE) --directory=docs CC=clang CXX=clang++ all
clang++-gtests:
	$(MAKE) --directory=tests CC=clang CXX=clang++ unit-gtests
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
	$(MAKE) --directory=examples CC=clang CXX=clang++ clean
clang++-zip:
	$(MAKE) --directory=src CC=clang CXX=clang++ zip

#default c++
c++: c++-all
c++-all:
	$(MAKE) c++-dist
	$(MAKE) c++-shared
	$(MAKE) --directory=src CC=cc CXX=c++ copy
c++-dist:
	$(MAKE) c++-contribs
c++-debug:
	$(MAKE) c++-all DEBUG=yes
c++-core:
	$(MAKE) --directory=src CC=cc CXX=c++ all
c++-contribs: c++-core
	$(MAKE) --directory=contrib CC=cc CXX=c++ all
c++-docs:
	$(MAKE) --directory=docs CC=cc CXX=c++ all
c++-coverage:
	$(MAKE) --directory=src CC=cc CXX=c++ SAFE_ONLY=yes dist
	$(MAKE) --directory=tests CC=cc CXX=c++ coverage
c++-gtests:
	$(MAKE) --directory=tests CC=cc CXX=c++ unit-gtests
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
	$(MAKE) --directory=examples CC=cc CXX=c++ clean
c++-zip:
	$(MAKE) --directory=src CC=cc CXX=c++ zip

#Oracle Solaris Studio
CC: CC-all
CC-all:
	$(MAKE) CC-dist
	$(MAKE) CC-shared
	$(MAKE) --directory=src CC=cc CXX=CC copy
CC-dist:
	$(MAKE) CC-contribs
CC-debug:
	$(MAKE) CC-all DEBUG=yes
CC-core:
	$(MAKE) --directory=src CC=cc CXX=CC all
CC-contribs: CC-core
	$(MAKE) --directory=contrib CC=cc CXX=CC all
CC-docs:
	$(MAKE) --directory=docs CC=cc CXX=CC all
CC-gtests:
	$(MAKE) --directory=tests CC=cc CXX=CC unit-gtests
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
	$(MAKE) --directory=examples CC=cc CXX=CC clean
CC-zip:
	$(MAKE) --directory=src CC=cc CXX=CC zip

#Intel
icpc: icpc-all
icpc-all:
	$(MAKE) icpc-dist
	$(MAKE) icpc-shared
	$(MAKE) --directory=src CC=icc CXX=icpc copy
icpc-dist:
	$(MAKE) icpc-contribs
icpc-debug:
	$(MAKE) icpc-all DEBUG=yes
icpc-core:
	$(MAKE) --directory=src CC=icc CXX=icpc all
icpc-contribs: icpc-core
	$(MAKE) --directory=contrib CC=icc CXX=icpc all
icpc-docs:
	$(MAKE) --directory=docs CC=icc CXX=icpc all
icpc-gtests:
	$(MAKE) --directory=tests CC=icc CXX=icpc unit-gtests
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
	$(MAKE) --directory=examples CC=icc CXX=icpc clean
icpc-zip:
	$(MAKE) --directory=src CC=icc CXX=icpc zip

#AMD
openCC: openCC-all
openCC-all: 
	$(MAKE) openCC-dist
	$(MAKE) openCC-shared
	$(MAKE) --directory=src CC=opencc CXX=openCC copy
openCC-dist: 
	$(MAKE) openCC-contribs
openCC-debug:
	$(MAKE) openCC-all DEBUG=yes
openCC-core:
	$(MAKE) --directory=src CC=opencc CXX=openCC all
openCC-contribs: openCC-core
	$(MAKE) --directory=contrib CC=opencc CXX=openCC all
openCC-docs:
	$(MAKE) --directory=docs CC=opencc CXX=openCC all
openCC-gtests:
	$(MAKE) --directory=tests CC=opencc CXX=openCC unit-gtests
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
	$(MAKE) --directory=examples CC=opencc CXX=openCC clean
openCC-zip:
	$(MAKE) --directory=src CC=opencc CXX=openCC zip

#scan-build
analyze-c++: analyze-c++-all
analyze-c++-all:
	$(MAKE) analyze-c++-dist
	$(MAKE) analyze-c++-shared
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ copy
analyze-c++-dist:
	$(MAKE) analyze-c++-contribs
analyze-c++-debug:
	$(MAKE) analyze-c++-all DEBUG=yes
analyze-c++-core:
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ all
analyze-c++-contribs: analyze-c++-core
	$(MAKE) --directory=contrib CC=analyze-cc CXX=analyze-c++ all
analyze-c++-docs:
	$(MAKE) --directory=docs CC=analyze-cc CXX=analyze-c++ all
analyze-c++-coverage:
	$(MAKE) --directory=src CC=analyze-cc CXX=analyze-c++ SAFE_ONLY=yes dist
	$(MAKE) --directory=tests CC=analyze-cc CXX=analyze-c++ coverage
analyze-c++-gtests:
	$(MAKE) --directory=tests CC=analyze-cc CXX=analyze-c++ unit-gtests
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
	$(MAKE) --directory=examples CC=analyze-cc CXX=analyze-c++ clean
analyze-c++-zip:

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
bcc-install:
	cd src& $(MAKE) -fbcc.mak install
bcc-clean:
	cd src& $(MAKE) -fbcc.mak clean

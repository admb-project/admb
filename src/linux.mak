.PHONY: dist verify
SHELL = /bin/bash

ifndef DISK
DISK=../build/dists/admb_gcc411_fedora8
endif

PWD=$(shell pwd)
NOW=$(shell date)

ifndef LIBPATH
CCVERSION=gcc411
OSVERSION=fedorar8
LIBPATH=../build/${CCVERSION}-${OSVERSION}
endif

ifndef ADMB_HOME
ADMB_HOME=${PWD}/${DISK}
endif

CXXFLAGS:=-DADMB_VERSION=$(shell cat ../VERSION) $(CXXFLAGS)

ifndef ADMB_REVISION
ADMB_REVISION=$(shell test -e ../REVISION && cat ../REVISION)
endif

ifneq ($(ADMB_REVISION),)
CXXFLAGS:=-DADMB_REVISION=$(ADMB_REVISION) $(CXXFLAGS)
ADMB_REVISION:=-r$(ADMB_REVISION)
endif

CXXFLAGS_INCLUDES:=-I../df1b2-separable -I../nh99 -I../linad99 -I../tools99
ifeq ($(CXX),CC)
CXXFLAGS:=-D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE $(CXXFLAGS)
else
CXXFLAGS:=-Wall -D__GNUDOS__ -Dlinux -D__SPDLL__ -DUSE_LAPLACE $(CXXFLAGS)
endif

ifdef DEBUG
CXXFLAGS:=-c -g $(CXXFLAGS)
else
CXXFLAGS:=-c -O3 $(CXXFLAGS)
endif

dist:
	mkdir -p ${DISK}/{bin,docs/manuals,examples,include,lib}
	mkdir -p ${LIBPATH}/linad99-olp
	mkdir -p ${LIBPATH}/linad99-slp
	mkdir -p ${LIBPATH}/df1b2-separable-olp
	mkdir -p ${LIBPATH}/df1b2-separable-slp
	mkdir -p ${LIBPATH}/nh99-olp
	mkdir -p ${LIBPATH}/tools99-olp
	$(MAKE) --directory=linad99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" LIBPATH=../${LIBPATH}/linad99-olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=linad99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_INCLUDES)" LIBPATH=../${LIBPATH}/linad99-slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak disk
	$(MAKE) --directory=df1b2-separable CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" LIBPATH=../${LIBPATH}/df1b2-separable-olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=df1b2-separable CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL $(CXXFLAGS_INCLUDES)" LIBPATH=../${LIBPATH}/df1b2-separable-slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak disk
	$(MAKE) --directory=nh99 CC=$(CC) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" LIBPATH=../${LIBPATH}/nh99-olp ADMB_CONFIGURE=${ADMB_CONFIGURE} DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=tools99 CXX=$(CXX) CXXFLAGS="$(CXXFLAGS) -DOPT_LIB $(CXXFLAGS_INCLUDES)" LIBPATH=../${LIBPATH}/tools99-olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	cp -vf ../LICENSE ${DISK}
	cp -vf ../README.txt ${DISK}
	cp ../scripts/admb/admb ${DISK}/bin
	cp ../scripts/$(CXX)/adcomp ${DISK}/bin
	cp ../scripts/$(CXX)/adlink ${DISK}/bin
	cp ../scripts/g++/Makefile ${DISK}/examples
        ifeq ($(CXX),g++)
	  cp ../scripts/admb/admb.bat ${DISK}/bin
	  cp ../scripts/$(CXX)/adcomp.bat ${DISK}/bin
	  cp ../scripts/$(CXX)/adlink.bat ${DISK}/bin
	  cp ../scripts/mingw/set-admb-mingw.bat ${DISK}/bin
        endif
	cp -R ../examples/admb ${DISK}/examples/admb
	cp -R ../examples/admb-re ${DISK}/examples/admb-re
	rm -f ${DISK}/bin/sed.exe

verify:
	ADMB_HOME="${ADMB_HOME}" PATH="${ADMB_HOME}"/bin:$(PATH) CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" SAFE_OPTION=1 $(MAKE) -C ${DISK}/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks$(ADMB_REVISION)-saf.txt"
	ADMB_HOME="${ADMB_HOME}" PATH="${ADMB_HOME}"/bin:$(PATH) CXXFLAGS="${ADMB_CXXFLAGS}" LDFLAGS="${ADMB_LDFLAGS}" $(MAKE) -C ${DISK}/examples all
	-../scripts/get-outputs.sh ${DISK}/examples/ > "../benchmarks$(ADMB_REVISION)-opt.txt"

check-admb2r:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); $(MAKE) -C ../test/admb2r gcc

clean:
	@rm -rvf linad99/${LIBPATH}-olp
	@rm -rvf linad99/${LIBPATH}-slp
	@rm -rvf nh99/${LIBPATH}-olp
	@rm -rvf tools99/${LIBPATH}olp
	@rm -rvf df1b2-separable/${LIBPATH}-olp
	@rm -rvf df1b2-separable/${LIBPATH}-slp
	@rm -f nh99/lex.yy.c
	@rm -f df1b2-separable/lex.yy.c
	@rm -f nh99/tpl2cpp
	@rm -f df1b2-separable/tpl2rem

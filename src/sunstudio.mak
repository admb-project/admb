.PHONY: dist
SHELL = /bin/bash

DISK=../build/dists/admb_gcc411_fedora8
PWD=$(shell pwd)
NOW=$(shell date)
ADMB_VERSION=$(shell cat ../VERSION)
ADMB_REVISION=$(shell svnversion ..)

CCVERSION=gcc411
OSVERSION=fedorar8

CXXFLAGS= -c ${ARCH_CXXFLAGS} -O3 -DUSE_LAPLACE -I../df1b2-separable -I../nh99 -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__  -Dlinux

dist:
	rm -rf ${DISK}
	mkdir -p ${DISK}/{bin,lib,include,docs,docs/manuals,examples}
	mkdir -p linad99/${CCVERSION}-${OSVERSION}olp 
	mkdir -p linad99/${CCVERSION}-${OSVERSION}slp 
	mkdir -p nh99/${CCVERSION}-${OSVERSION}olp 
	mkdir -p nh99/${CCVERSION}-${OSVERSION}olp-stub 
	mkdir -p tools99/${CCVERSION}-${OSVERSION}olp 
	mkdir -p df1b2-separable/${CCVERSION}-${OSVERSION}slp 
	mkdir -p df1b2-separable/${CCVERSION}-${OSVERSION}olp 
	$(MAKE) --directory=linad99 CXX=CC CXXFLAGS="$(CXXFLAGS) -DOPT_LIB" LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=linad99 CXX=CC CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL" LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak disk 
	$(MAKE) --directory=nh99 CXX=CC CXXFLAGS="$(CXXFLAGS) -DOPT_LIB" STUBPATH=${CCVERSION}-${OSVERSION}olp-stub LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=tools99 CXX=CC CXXFLAGS="$(CXXFLAGS) -DOPT_LIB" LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=df1b2-separable CXX=CC CXXFLAGS="$(CXXFLAGS) -DOPT_LIB" LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak disk
	$(MAKE) --directory=df1b2-separable CXX=CC CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL" LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak disk 
	cp ../scripts/bash/link* ${DISK}/bin
	cp ../scripts/bash/m* ${DISK}/bin
	cp ../scripts/sunstudio/admb ${DISK}/bin
	cp ../scripts/sunstudio/adcomp ${DISK}/bin
	cp ../scripts/sunstudio/adlink ${DISK}/bin
	cp ../scripts/bash/Makefile ${DISK}
	cp -R ../examples/admb ${DISK}/examples/admb
	cp -R ../examples/admb-re ${DISK}/examples/admb-re
	cp -f ../LICENSE ${DISK}
	cp -f ../README.txt ${DISK}
	cp -f ../scripts/bash/mygcc* ${DISK}/bin 
	#make -C docs/manuals
	#cp -vf docs/manuals/autodif.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb-re.pdf ${DISK}/docs/manuals

dist-64bit: dist
	cp ../scripts/sunstudio/adcomp-64bit ${DISK}/bin/adcomp
	cp ../scripts/sunstudio/adlink-64bit ${DISK}/bin/adlink

verify:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); cd ${DISK}; make all
	export ADMB_HOME=${PWD}/${DISK}; ../scripts/get-outputs.sh ../build/dists/admb_gcc411_fedora8/examples > "../benchmarks-${NOW}-r${ADMB_REVISION}.txt"

check-admb2r:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); make --directory=../test/admb2r gcc

clean:
	@rm -rf linad99/SunWS_cache
	@rm -rf nh99/SunWS_cache
	@rm -rf tools99/SunWS_cache
	@rm -rf df1b2-separable/SunWS_cache
	@rm -f linad99/gcc411-fedorar8olp/*
	@rm -f linad99/gcc411-fedorar8slp/*
	@rm -f nh99/gcc411-fedorar8olp/*
	@rm -f nh99/gcc411-fedorar8slp/*
	@rm -f tools99/gcc411-fedorar8olp/*
	@rm -f df1b2-separable/gcc411-fedorar8olp/*
	@rm -f df1b2-separable/gcc411-fedorar8slp/*
	@rm -f df1b2-separable/tpl2rem
	@rm -f nh99/tpl2cpp
	@rm -f nh99/lex.yy.c
	@rm -f nh99/tpl2cpp.c
	@rm -f nh99/gcc411-fedorar8olp-stub/libdf1b2stub.a



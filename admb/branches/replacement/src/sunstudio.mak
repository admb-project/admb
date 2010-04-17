.PHONY: dist
SHELL = /bin/bash

DISK=../build/dists/admb_gcc411_fedora8
PWD=$(shell pwd)

CCVERSION=gcc411
OSVERSION=fedorar8
COMP=CC

dist:
	rm -rf ${DISK}
	- mkdir -p ${DISK}/{bin,lib,include,docs,docs/manuals,examples}
	cp ../scripts/bash/link* ${DISK}/bin
	cp ../scripts/bash/m* ${DISK}/bin
	cp ../scripts/sunstudio/admb ${DISK}/bin
	cp ../scripts/sunstudio/adcomp ${DISK}/bin
	cp ../scripts/sunstudio/adlink ${DISK}/bin
	cp ../scripts/bash/check-expected-results ${DISK}/bin
	cp ../scripts/sunstudio/Makefile ${DISK}
	cp -R ../examples/admb ${DISK}/examples/admb
	cp -R ../examples/admb-re ${DISK}/examples/admb-re
	rm -rf ${DISK}/examples/admb/SS3
	rm -rf ${DISK}/examples/admb/SS3-Simple
	- cd ./linad99; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir -p ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir -p ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./tools99; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./df1b2-separable; mkdir -p ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak disk 
	cd ./nh99;    $(MAKE)  CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optsunstudio.mak disk
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak disk
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak disk 
	cp -f ../LICENSE ${DISK}
	cp -f ../README ${DISK}
	cp -f ../scripts/bash/mygcc* ${DISK}/bin 
	#make -C docs/manuals
	#cp -vf docs/manuals/autodif.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb-re.pdf ${DISK}/docs/manuals

verify:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); cd ${DISK}; make all

check-admb2r:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); make --directory ../ADMB2R gcc

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



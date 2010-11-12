.PHONY: dist verify
SHELL = /bin/bash

ifndef DISK
  DISK=../build/dists/admb_gcc411_fedora8
endif

PWD=$(shell pwd)
NOW=$(shell date)
ADMB_REVISION=$(shell svnversion ..)

ifndef LIBPATH
  CCVERSION=gcc411
  OSVERSION=fedorar8
  LIBPATH=../build/${CCVERSION}-${OSVERSION}
endif

ifdef DEBUG
CXXFLAGS:=$(CXXFLAGS) -g
else
CXXFLAGS:=$(CXXFLAGS) -O3
endif

CXXFLAGS:=-c $(CXXFLAGS) -Wall -Wno-deprecated -DUSE_LAPLACE -fpermissive -I../df1b2-separable -I../nh99 -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -Dlinux

dist:
	rm -rf ${DISK}
	mkdir -p ${DISK}/{bin,lib,include,docs,docs/manuals,examples}
	mkdir -p ${LIBPATH}/linad99-olp 
	mkdir -p ${LIBPATH}/linad99-slp 
	mkdir -p ${LIBPATH}/nh99-olp 
	mkdir -p ${LIBPATH}/nh99-olp-stub 
	mkdir -p ${LIBPATH}/tools99-olp 
	mkdir -p ${LIBPATH}/df1b2-separable-slp 
	mkdir -p ${LIBPATH}/df1b2-separable-olp 
	$(MAKE) --directory=df1b2-separable CC=gcc CXXFLAGS="$(CXXFLAGS) -DOPT_LIB" LIBPATH=../${LIBPATH}/df1b2-separable-olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=df1b2-separable CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL" LIBPATH=../${LIBPATH}/df1b2-separable-slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak disk 
	$(MAKE) --directory=linad99 CXX=g++ CXXFLAGS="$(CXXFLAGS) -DOPT_LIB" LIBPATH=../${LIBPATH}/linad99-olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=linad99 CXX=g++ CXXFLAGS="$(CXXFLAGS) -DSAFE_ALL" LIBPATH=../${LIBPATH}/linad99-slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak disk 
	$(MAKE) --directory=nh99 CC=gcc CXXFLAGS="$(CXXFLAGS) -DOPT_LIB" STUBPATH=../${LIBPATH}/nh99-olp-stub LIBPATH=../${LIBPATH}/nh99-olp ADMB_CONFIGURE=${ADMB_CONFIGURE} DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  disk
	$(MAKE) --directory=tools99 CXXFLAGS="$(CXXFLAGS) -DOPT_LIB" LIBPATH=../${LIBPATH}/tools99-olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	cp -vf ../LICENSE ${DISK}
	cp -vf ../README.txt ${DISK}
	cp -vf ../scripts/bash/mygcc* ${DISK}/bin 
	cp ../scripts/bash/link* ${DISK}/bin
	cp ../scripts/bash/m* ${DISK}/bin
	cp ../scripts/bash/admb ${DISK}/bin
	cp ../scripts/bash/adcomp ${DISK}/bin
	cp ../scripts/bash/adlink ${DISK}/bin
	cp ../scripts/bash/check-expected-results ${DISK}/bin
	cp ../scripts/bash/Makefile ${DISK}
	cp -R ../examples/admb ${DISK}/examples/admb
	cp -R ../examples/admb-re ${DISK}/examples/admb-re


	#make -C docs/manuals
	#cp -vf docs/manuals/autodif.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb-re.pdf ${DISK}/docs/manuals
	#- rm -f ${DISK}.tar* 
	#tar -cvf ${DISK}.tar ${DISK}
	#bzip2 ${DISK}.tar 

dist-64bit: dist
	cp ../scripts/bash/adcomp-64bit ${DISK}/bin/adcomp
	cp ../scripts/bash/adlink-64bit ${DISK}/bin/adlink

verify:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); make -C ${DISK} all
	-export ADMB_HOME=${PWD}/${DISK}; ../scripts/get-outputs.sh ${DISK}/examples > "../benchmarks-${NOW}-r${ADMB_REVISION}-opt.txt"
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); SAFE_OPTION=1 make -C ${DISK} all
	-export ADMB_HOME=${PWD}/${DISK}; ../scripts/get-outputs.sh ${DISK}/examples > "../benchmarks-${NOW}-r${ADMB_REVISION}-saf.txt"

check-admb2r:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); make -C ../test/admb2r gcc

clean:
	@rm -rvf linad99/${LIBPATH}-olp
	@rm -rvf linad99/${LIBPATH}-slp
	@rm -rvf nh99/${LIBPATH}-olp
	@rm -rvf nh99/${LIBPATH}-olp-stub
	@rm -rvf tools99/${LIBPATH}olp
	@rm -rvf df1b2-separable/${LIBPATH}-olp
	@rm -rvf df1b2-separable/${LIBPATH}-slp
	@rm -f nh99/lex.yy.c
	@rm -f nh99/gcc411-fedorar8olp-stub/libdf1b2stub.a
	@rm -f df1b2-separable/lex.yy.c
	@rm -f nh99/tpl2cpp
	@rm -f df1b2-separable/tpl2rem

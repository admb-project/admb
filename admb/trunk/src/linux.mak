.PHONY: dist verify
SHELL = /bin/bash

DISK=../build/dists/admb_gcc411_fedora8
PWD=$(shell pwd)
NOW=$(shell date)
ADMB_VERSION=$(shell cat ../VERSION)
ADMB_REVISION=$(shell svnversion ..)

CCVERSION=gcc411
OSVERSION=fedorar8
COMP=g++
COMP64BIT="g++ -m64"
#CXXFLAGS_NH99_OPT =-c -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-comment -Wno-parentheses -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -fpermissive -I../df1b2-separable -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -DOPT_LIB -Dlinux

MYCXX=$(CXXFLAGS) -c -O3 -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-comment -Wno-parentheses -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable -DUSE_LAPLACE -fpermissive -I../df1b2-separable -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -DOPT_LIB -Dlinux

CXXFLAGS_DF_OPT = $(CXXFLAGS) -fno-for-scope -Wall -Wno-non-virtual-dtor -Wno-comment -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${OPTIONS} ${PVMOPTION} -DOPT_LIB  -fpermissive -DUSE_LAPLACE -c -I. -I../nh99 -I../linad99 -I../tools99  -Dlinux -D__GNUDOS__
CXXFLAGS_DF_SAF = $(CXXFLAGS) -fno-for-scope -Wall -Wno-non-virtual-dtor -Wno-comment -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${OPTIONS} ${PVMOPTION} -DSAFE_ALL -fpermissive -DUSE_LAPLACE -c -I. -I../nh99 -I../linad99 -I../tools99 -Dlinux -D __GNUDOS__
CXXFLAGS_LIN_OPT = $(CXXFLAGS) -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -DOPT_LIB -D__GNUDOS__ -Dlinux -fpermissive -c -I. -I../nh99 -I../df1b2-separable -I../tools99
CXXFLAGS_LIN_SAF= $(CXXFLAGS) -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -DSAFE_ALL -D__GNUDOS__ -Dlinux -fpermissive -c -I. -I../nh99 -I../tools99 -I../df1b2-separable
CXXFLAGS_TOOLS_OPT = $(CXXFLAGS) -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-format -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -fpermissive -c -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -Dlinux -DOPT_LIB

dist:
	rm -rf ${DISK}
	- mkdir -p ${DISK}/{bin,lib,include,docs,docs/manuals,examples}
	- cd ./linad99; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir -p ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir -p ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./tools99; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./df1b2-separable; mkdir -p ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	$(MAKE) --directory=df1b2-separable CXXFLAGS="$(CXXFLAGS_DF_OPT)" LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=df1b2-separable CXXFLAGS="$(CXXFLAGS_DF_SAF)" LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak disk 
	$(MAKE) --directory=linad99 CXX=g++ CXXFLAGS="$(CXXFLAGS_LIN_OPT)" LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	$(MAKE) --directory=linad99 CXX=g++ CXXFLAGS="$(CXXFLAGS_LIN_SAF)" LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak disk 
	$(MAKE) --directory=nh99 CXXFLAGS="$(MYCXX)" STUBPATH=${CCVERSION}-${OSVERSION}olp-stub LIBPATH=${CCVERSION}-${OSVERSION}olp ADMB_VERSION=${ADMB_VERSION} ADMB_REVISION=${ADMB_REVISION} DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  disk
	$(MAKE) --directory=tools99 CXXFLAGS="$(CXXFLAGS_TOOLS_OPT)" LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	cp -vf ../LICENSE ${DISK}
	cp -vf ../README ${DISK}
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
	rm -rvf ${DISK}/examples/admb/SS3
	rm -rvf ${DISK}/examples/admb/SS3-Simple

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
	../scripts/get-outputs.sh ../build/dists/admb_gcc411_fedora8/examples > "../benchmarks-${NOW}-r${ADMB_REVISION}.txt"

check-admb2r:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); make -C ../ADMB2R gcc

clean:
	rm -rvf linad99/${CCVERSION}-${OSVERSION}olp
	rm -rvf linad99/${CCVERSION}-${OSVERSION}slp
	rm -rvf nh99/${CCVERSION}-${OSVERSION}olp
	rm -rvf nh99/${CCVERSION}-${OSVERSION}olp-stub
	rm -rvf tools99/${CCVERSION}-${OSVERSION}olp
	rm -rvf df1b2-separable/${CCVERSION}-${OSVERSION}olp
	rm -rvf df1b2-separable/${CCVERSION}-${OSVERSION}slp
	@rm -f nh99/lex.yy.c
	@rm -f nh99/gcc411-fedorar8olp-stub/libdf1b2stub.a
	@rm -f df1b2-separable/lex.yy.c

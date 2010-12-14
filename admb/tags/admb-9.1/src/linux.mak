.PHONY: dist
SHELL = /bin/bash

DISK=../build/dists/admb_gcc411_fedora8
PWD=$(shell pwd)

CCVERSION=gcc411
OSVERSION=fedorar8
COMP=g++
COMP64BIT="g++ -m64"

dist:
	rm -rf ${DISK}
	- mkdir -p ${DISK}/{bin,lib,include,docs,docs/manuals,examples}
	cp ../scripts/bash/link* ${DISK}/bin
	cp ../scripts/bash/m* ${DISK}/bin
	cp ../scripts/bash/admb ${DISK}/bin
	cp ../scripts/bash/adcomp ${DISK}/bin
	cp ../scripts/bash/adlink ${DISK}/bin
	cp ../scripts/bash/check-expected-results ${DISK}/bin
	cp ../scripts/bash/Makefile ${DISK}
	svn export ../examples/admb ${DISK}/examples/admb
	svn export ../examples/admb-re ${DISK}/examples/admb-re
	rm -rvf ${DISK}/examples/admb/SS3
	rm -rvf ${DISK}/examples/admb/SS3-Simple
	- cd ./linad99; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir -p ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir -p ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./tools99; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./df1b2-separable; mkdir -p ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak disk 
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  disk
	cp -vf ../LICENSE ${DISK}
	cp -vf ../README ${DISK}
	cp -vf ../scripts/bash/mygcc* ${DISK}/bin 
	#make -C docs/manuals
	#cp -vf docs/manuals/autodif.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb-re.pdf ${DISK}/docs/manuals
	- rm -f ${DISK}.tar* 
	tar -cvf ${DISK}.tar ${DISK}
	bzip2 ${DISK}.tar 

dist-64bit:
	rm -rf ${DISK}
	- mkdir -p ${DISK}/{bin,lib,include,docs,docs/manuals,examples}
	cp ../scripts/bash/link* ${DISK}/bin
	cp ../scripts/bash/m* ${DISK}/bin
	cp ../scripts/bash/admb ${DISK}/bin/admb
	cp ../scripts/bash/adcomp-64bit ${DISK}/bin/adcomp
	cp ../scripts/bash/adlink-64bit ${DISK}/bin/adlink
	cp ../scripts/bash/check-expected-results ${DISK}/bin
	cp ../scripts/bash/Makefile ${DISK}
	svn export ../examples/admb ${DISK}/examples/admb
	svn export ../examples/admb-re ${DISK}/examples/admb-re
	rm -rvf ${DISK}/examples/admb/SS3
	rm -rvf ${DISK}/examples/admb/SS3-Simple
	- cd ./linad99; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir -p ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir -p ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./tools99; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	- cd ./df1b2-separable; mkdir -p ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable; mkdir -p ${CCVERSION}-${OSVERSION}olp 
	cd ./df1b2-separable; $(MAKE) CC=${COMP64BIT} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=${COMP64BIT} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak disk 
	cd ./linad99; $(MAKE)  CC=${COMP64BIT} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=${COMP64BIT} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  CC=${COMP64BIT} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  CC=${COMP64BIT} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  disk
	cp -vf ../LICENSE ${DISK}
	cp -vf ../README ${DISK}
	cp -vf ../scripts/bash/mygcc* ${DISK}/bin 
	#make -C docs/manuals
	#cp -vf docs/manuals/autodif.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb.pdf ${DISK}/docs/manuals
	#cp -vf docs/manuals/admb-re.pdf ${DISK}/docs/manuals
	#- rm -f ${DISK}.tar* 
	#tar -cvf ${DISK}.tar ${DISK}
	#bzip2 ${DISK}.tar 

verify:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); make -C ${DISK} all

check-admb2r:
	export ADMB_HOME=${PWD}/${DISK}; export PATH=${PWD}/${DISK}/bin:$(PATH); make -C ../ADMB2R gcc

clean:
	@cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak clean
	@cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak  clean 
	@cd ./nh99;    $(MAKE)  CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	@cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	@cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak  clean
	@cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak clean 
	@rm -f nh99/lex.yy.c
	@rm -f nh99/tpl2cpp.c
	@rm -f nh99/gcc411-fedorar8olp-stub/libdf1b2stub.a
	@rm -f df1b2-separable/lex.yy.c

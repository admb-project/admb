
DISK=build/dists/admb_gcc411_fedora8

CCVERSION=gcc411
OSVERSION=fedorar8
COMP=g++

dist:
	rm -rf ${DISK}
	- mkdir -p ${DISK}/{bin,lib,include,docs,docs/manuals,examples}
	cp scripts/bash/link* ${DISK}/bin
	cp scripts/bash/m* ${DISK}/bin
	cp scripts/bash/Makefile ${DISK}
	svn export examples/admb ${DISK}/examples/admb
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./tools99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}olp 
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak disk 
	cp -vf LICENSE ${DISK}
	cp -vf README ${DISK}
	cp -vf scripts/bash/mygcc* ${DISK}/bin 
	make -C docs/manuals
	cp -vf docs/manuals/autodif.pdf ${DISK}/docs/manuals
	cp -vf docs/manuals/admb.pdf ${DISK}/docs/manuals
	cp -vf docs/manuals/admb-re.pdf ${DISK}/docs/manuals
	- rm ${DISK}.tar* 
	tar -cvf ${DISK}.tar ${DISK}
	bzip2 ${DISK}.tar 

clean:
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak clean
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak  clean 
	cd ./nh99;    $(MAKE)  CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak clean 

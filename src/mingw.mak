DISK=../build/dists/admb_gcc345_mingw32
PWD=$(shell pwd)

CCVERSION=gcc345mingw
OSVERSION=win32
COMP="g++ -Wall"

dist:
	rm -rf ${DISK}
	- mkdir -p ${DISK}
	- cd ${DISK}; mkdir bin; mkdir lib; mkdir include
	cp ../scripts/mingw/*.bat ${DISK}/bin
	cp ../LICENSE ${DISK}
	cp ../README ${DISK}
	svn export ../examples ${DISK}/examples
	cp ../scripts/mingw/Makefile ${DISK}
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./tools99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}olp 
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f  safg32-rh8-laplace.mak disk 
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} PVMOPTION=-Dlinux -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f optg32-rh8-laplace.mak  disk
	#- rm ${DISK}.tar* 
	#tar -cvf ${DISK}.tar ${DISK}
	#bzip2 ${DISK}.tar 

verify:
	make -C ${DISK}

clean:
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak clean
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak  clean 
	cd ./nh99;    $(MAKE)  CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak clean 

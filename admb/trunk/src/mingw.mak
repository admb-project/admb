DISK=../build/dists/admb_gcc345_mingw32
PWD=$(shell pwd)

CCVERSION=gcc345mingw
OSVERSION=win32
COMP="g++ -Wall"

dist:
	rm -rf ${DISK}
	- mkdir.exe -p ${DISK}
	- mkdir.exe -p ${DISK}/bin
	mkdir.exe -p ${DISK}/lib
	mkdir.exe -p ${DISK}/include
	cp ../scripts/mingw/*.bat ${DISK}/bin
	cp ../LICENSE ${DISK}
	cp ../README ${DISK}
	cp -R ../examples ${DISK}/examples
	cp ../scripts/mingw/Makefile ${DISK}
	- mkdir.exe -p linad99/${CCVERSION}-${OSVERSION}olp 
	- mkdir.exe -p linad99/${CCVERSION}-${OSVERSION}slp 
	- mkdir.exe -p nh99/${CCVERSION}-${OSVERSION}olp 
	- mkdir.exe -p nh99/${CCVERSION}-${OSVERSION}olp-stub 
	- mkdir.exe -p tools99/${CCVERSION}-${OSVERSION}olp 
	- mkdir.exe -p df1b2-separable/${CCVERSION}-${OSVERSION}slp 
	- mkdir.exe -p df1b2-separable/${CCVERSION}-${OSVERSION}olp 
	$(MAKE) -C df1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f  optg32-rh8-laplace.mak  disk
	$(MAKE) -C df1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f  safg32-rh8-laplace.mak disk 
	$(MAKE) -C linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f optg32-rh8-laplace.mak disk
	$(MAKE) -C linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f safg32-rh8-laplace.mak  disk 
	$(MAKE)  -C nh99 CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} PVMOPTION=-Dlinux -f optg32-rh8-laplace.mak  disk
	$(MAKE)  -C tools99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} PVMOPTION=-Dlinux -f optg32-rh8-laplace.mak  disk
	
verify:
	make -C ${DISK}

clean:
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak clean
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak  clean 
	cd ./nh99;    $(MAKE)  CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE) CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak clean 

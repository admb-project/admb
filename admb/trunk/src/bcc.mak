DISK=../build/dists/admb_b502_win32
PWD=$(shell pwd)
WINADMB_HOME=$(shell cygpath --windows ${PWD}/${DISK})
BORLAND_HOME=$(shell cygpath --unix $(BCC55_HOME))

CCVERSION=bor502
OSVERSION=win32
COMP=bcc32

dist:
	rm -rf ${DISK}
	- mkdir -p ${DISK}
	- cd ${DISK}; mkdir bin; mkdir lib; mkdir include; mkdir -p examples
	cp ../scripts/borland/*.bat ${DISK}/bin
	cp ../scripts/mingw/admb.bat ${DISK}/bin
	cp ../LICENSE ${DISK}
	cp ../README ${DISK}
	svn export ../examples/admb ${DISK}/examples/admb
	svn export ../examples/admb-re ${DISK}/examples/admb-re
	cp ../scripts/borland/Makefile ${DISK}/examples
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./tools99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}olp 
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp STUBPATH=${CCVERSION}-${OSVERSION}olp-stub DISKDIR=../${DISK} -f optbor32-laplace.mak all
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optbor32-laplace.mak all
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optbor32-laplace.mak all
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safbor32-laplace.mak all
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK}  -f optbor32-laplace.mak all
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK}  -f safbor32-laplace.mak all
	#- rm ${DISK}.tar* 
	#tar -cvf ${DISK}.tar ${DISK}
	#bzip2 ${DISK}.tar 

verify:
	cd ${DISK}\examples && ADMB_HOME="${WINADMB_HOME}" PATH="$(BCC55_HOME)\\bin;${WINADMB_HOME}\\bin;%PATH%" $(BORLAND_HOME)/bin/make 

clean:
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optbor32-laplace.mak clean
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safbor32-laplace.mak clean
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optbor32-laplace.mak clean
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optbor32-laplace.mak clean
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optbor32-laplace.mak clean
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safbor32-laplace.mak clean

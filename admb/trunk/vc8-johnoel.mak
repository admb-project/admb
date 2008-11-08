DISKDIR= h:/adms8lp.m32

DISK= ../admb_vc8_win32

CCVERSION=vc8
OSVERSION=win32
COMP=cl

all:
	- mkdir ${DISK}
	- cd ${DISK}; mkdir bin; mkdir lib; mkdir include
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./tools99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}olp 
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak all
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak all
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak all
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak all
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak all
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak all
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak all
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak all
	- rm ${DISK}.tar* 
	tar -cvf ${DISK}.tar ${DISK}
	bzip2 ${DISK}.tar 

clean:
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean



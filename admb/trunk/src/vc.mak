COMP=cl

all:
	rm -rf ${DISK}
	- mkdir -p ${DISK}
	- cd ${DISK}; mkdir bin; mkdir lib; mkdir include
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./linad99; mkdir ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}slp 
	- cd ./nh99;    mkdir ${CCVERSION}-${OSVERSION}olp-stub 
	- cd ./nh99;    mkdir msc8slp-stub
	- cd ./tools99; mkdir ${CCVERSION}-${OSVERSION}olp 
	- cd ./tools99; mkdir ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}slp 
	- cd ./df1b2-separable;mkdir  ${CCVERSION}-${OSVERSION}olp 
	cp ../scripts/vc/*.bat ${DISK}/bin
	cp ../scripts/mingw/admb.bat ${DISK}/bin
	cp ../LICENSE ${DISK}
	cp ../README ${DISK}
	svn export ../examples ${DISK}/examples
	cp ../scripts/vc/Makefile ${DISK}/examples
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -I\"${MSSDK}\"/Include" -f optmsc8-laplace.mak all
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -I\"${MSSDK}\"/Include" -f safmsc8-laplace.mak all
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -I\"${MSSDK}\"/Include" -f optmsc8-laplace.mak all
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -I\"${MSSDK}\"/Include" -f safmsc8-laplace.mak all
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -I\"${MSSDK}\"/Include" -f optmsc8-laplace.mak all
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -I\"${MSSDK}\"/Include" -f safmsc8-laplace.mak all
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -I\"${MSSDK}\"/Include" -f optmsc8-laplace.mak all
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -I\"${MSSDK}\"/Include" -f safmsc8-laplace.mak all
	#- rm ${DISK}.tar* 
	#tar -cvf ${DISK}.tar ${DISK}
	#bzip2 ${DISK}.tar 

clean:
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	cd ./linad99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	cd ./nh99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	cd ./tools99; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	cd ./df1b2-separable; $(MAKE)  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	rm -rvf tools99/vc7-win32olp
	rm -rvf tools99/vc7-win32slp
	rm -vf nh99/t.rsp
	rm -rvf nh99/vc7-win32olp
	rm -rvf nh99/vc7-win32slp
	rm -rvf nh99/vc7-win32olp-stub
	rm -vf nh99/tpl2cpp.obj
	rm -vf nh99/tpl2cpp.lib
	rm -vf nh99/tpl2cpp.exe
	rm -rvf nh99/msc8slp-stub
	rm -rvf linad99/vc7-win32olp
	rm -rvf linad99/vc7-win32slp
	rm -rvf df1b2-separable/vc7-win32olp
	rm -rvf df1b2-separable/vc7-win32slp
	rm -vf df1b2-separable/tpl2rem.obj
	rm -vf df1b2-separable/tpl2rem.exe

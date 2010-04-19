DISK=../build
CCVERSION=vc10
OSVERSION=win7
COMP=cl
PWD=$(shell pwd)
WINADMB_HOME=$(shell cygpath --windows ${PWD}/${DISK})
BORLAND_HOME=$(shell cygpath --unix $(BCC55_HOME))

ifdef MSSDK
PVM_OPTION=${MSSDK}
export PVM_OPTION
endif

all:
	rm -rf ${DISK}
	- mkdir.exe -p ${DISK}/bin
	- mkdir.exe -p ${DISK}/lib
	- mkdir.exe -p ${DISK}/include
	- mkdir.exe -p linad99/${CCVERSION}-${OSVERSION}olp 
	- mkdir.exe -p linad99/${CCVERSION}-${OSVERSION}slp 
	- mkdir.exe -p nh99/${CCVERSION}-${OSVERSION}olp 
	- mkdir.exe -p nh99/${CCVERSION}-${OSVERSION}slp 
	- mkdir.exe -p nh99/${CCVERSION}-${OSVERSION}olp-stub 
	- mkdir.exe -p nh99/msc8slp-stub
	- mkdir.exe -p tools99/${CCVERSION}-${OSVERSION}olp 
	- mkdir.exe -p tools99/${CCVERSION}-${OSVERSION}slp 
	- mkdir.exe -p df1b2-separable/${CCVERSION}-${OSVERSION}slp 
	- mkdir.exe -p df1b2-separable/${CCVERSION}-${OSVERSION}olp 
	cp ../scripts/vc/*.bat ${DISK}/bin
	cp ../scripts/mingw/admb.bat ${DISK}/bin
	cp ../LICENSE ${DISK}
	cp ../README ${DISK}
	cp -R ../examples ${DISK}/examples
	cp ../scripts/vc/Makefile ${DISK}/examples
	$(MAKE)  --directory=linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optmsc8-laplace.mak all
	$(MAKE)  --directory=linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safmsc8-laplace.mak all
	$(MAKE) --directory=nh99  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optmsc8-laplace.mak all
	$(MAKE)  --directory=nh99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safmsc8-laplace.mak all
	$(MAKE) --directory=tools99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optmsc8-laplace.mak all
	$(MAKE) --directory=tools99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safmsc8-laplace.mak all
	$(MAKE) --directory=df1b2-separable  CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optmsc8-laplace.mak all
	$(MAKE)  --directory=df1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safmsc8-laplace.mak all

verify:

clean:
	$(MAKE) --directory=linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	$(MAKE)  --directory=linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	$(MAKE)  --directory=nh99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	$(MAKE)  --directory=nh99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	$(MAKE)  --directory=tools99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	$(MAKE)  --directory=tools99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
	$(MAKE)  --directory=df1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f optmsc8-laplace.mak clean
	$(MAKE)  --directory=df1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include" -f safmsc8-laplace.mak clean
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

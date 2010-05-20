.PHONY: dist verify

SHELL:=$(COMSPEC)
DISK=..\build\dists\admb_gcc345_mingw32
PWD=$(shell pwd)

CCVERSION=gcc345mingw
OSVERSION=win32
COMP=g++

dist:
	if exist ${DISK} rmdir /S /Q ${DISK}
	mkdir $(DISK)\bin
	mkdir $(DISK)\lib
	mkdir $(DISK)\include

	copy ..\scripts\mingw\*.bat ${DISK}\bin
	copy ..\LICENSE ${DISK}
	copy ..\README ${DISK}
	copy ..\scripts\mingw\Makefile ${DISK}

	mkdir ${DISK}\examples
	xcopy ..\examples ${DISK}\examples /S

	if not exist linad99\${CCVERSION}-${OSVERSION}olp mkdir linad99\${CCVERSION}-${OSVERSION}olp 
	if not exist linad99\${CCVERSION}-${OSVERSION}slp mkdir linad99\${CCVERSION}-${OSVERSION}slp 
	if not exist nh99\${CCVERSION}-${OSVERSION}olp mkdir nh99\${CCVERSION}-${OSVERSION}olp 
	if not exist nh99\${CCVERSION}-${OSVERSION}olp-stub -mkdir nh99\${CCVERSION}-${OSVERSION}olp-stub 
	if not exist tools99\${CCVERSION}-${OSVERSION}olp mkdir tools99\${CCVERSION}-${OSVERSION}olp 
	if not exist df1b2-separable\${CCVERSION}-${OSVERSION}olp mkdir df1b2-separable\${CCVERSION}-${OSVERSION}olp 
	if not exist df1b2-separable\${CCVERSION}-${OSVERSION}slp mkdir df1b2-separable\${CCVERSION}-${OSVERSION}slp 

	$(MAKE) -C df1b2-separable CC=g++ LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-optg32-rh8-laplace.mak disk
	$(MAKE) -C df1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-safg32-rh8-laplace.mak disk 
	$(MAKE) -C linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-optg32-rh8-laplace.mak disk
	$(MAKE) -C linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-safg32-rh8-laplace.mak  disk 
	$(MAKE)  -C nh99 CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-optg32-rh8-laplace.mak  disk
	$(MAKE)  -C tools99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-optg32-rh8-laplace.mak  disk
	
verify:
	set ADMB_HOME=%CD%\$(DISK)& set PATH=%CD%\$(DISK)\bin;$(PATH)& set& $(MAKE) -C ${DISK} all

clean:
	$(MAKE) -Clinad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak clean
	$(MAKE) -Clinad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f safg32-rh8-laplace.mak  clean 
	$(MAKE) -Cnh99 CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	$(MAKE) -Ctools99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f optg32-rh8-laplace.mak  clean
	$(MAKE) -Cdf1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=../${DISK} -f  optg32-rh8-laplace.mak  clean
	$(MAKE) -Cdf1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=../${DISK} -f  safg32-rh8-laplace.mak clean 

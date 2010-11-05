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

	if not exist linad99\${CCVERSION}-${OSVERSION}olp mkdir linad99\${CCVERSION}-${OSVERSION}olp 
	if not exist linad99\${CCVERSION}-${OSVERSION}slp mkdir linad99\${CCVERSION}-${OSVERSION}slp 
	if not exist nh99\${CCVERSION}-${OSVERSION}olp mkdir nh99\${CCVERSION}-${OSVERSION}olp 
	if not exist nh99\${CCVERSION}-${OSVERSION}olp-stub mkdir nh99\${CCVERSION}-${OSVERSION}olp-stub 
	if not exist tools99\${CCVERSION}-${OSVERSION}olp mkdir tools99\${CCVERSION}-${OSVERSION}olp 
	if not exist df1b2-separable\${CCVERSION}-${OSVERSION}olp mkdir df1b2-separable\${CCVERSION}-${OSVERSION}olp 
	if not exist df1b2-separable\${CCVERSION}-${OSVERSION}slp mkdir df1b2-separable\${CCVERSION}-${OSVERSION}slp 

	$(MAKE) -C df1b2-separable CC=g++ LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-optg32-rh8-laplace.mak disk
	$(MAKE) -C df1b2-separable CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-safg32-rh8-laplace.mak disk 
	$(MAKE) -C linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-optg32-rh8-laplace.mak disk
	$(MAKE) -C linad99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}slp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-safg32-rh8-laplace.mak  disk 
	$(MAKE)  -C nh99 CC=${COMP} STUBPATH=${CCVERSION}-${OSVERSION}olp-stub   LIBPATH=${CCVERSION}-${OSVERSION}olp  DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-optg32-rh8-laplace.mak  disk
	$(MAKE)  -C tools99 CC=${COMP} LIBPATH=${CCVERSION}-${OSVERSION}olp DISKDIR=..\${DISK} PVMOPTION=-Dlinux -f mingw-optg32-rh8-laplace.mak  disk

	copy ..\scripts\mingw\*.bat ${DISK}\bin
	copy ..\LICENSE ${DISK}
	copy ..\README.txt ${DISK}
	copy ..\scripts\mingw\Makefile ${DISK}

	mkdir ${DISK}\examples
	xcopy ..\examples ${DISK}\examples /S
	
verify:
	set ADMB_HOME=%CD%\$(DISK)& set PATH=%CD%\$(DISK)\bin;$(PATH)& set& $(MAKE) -C ${DISK} all

clean:
	if exist linad99\\${CCVERSION}-${OSVERSION}olp rmdir /S /Q linad99\\${CCVERSION}-${OSVERSION}olp
	if exist linad99\${CCVERSION}-${OSVERSION}slp rmdir /S /Q linad99\${CCVERSION}-${OSVERSION}slp
	if exist nh99\${CCVERSION}-${OSVERSION}olp rmdir /S /Q nh99\${CCVERSION}-${OSVERSION}olp
	if exist nh99\${CCVERSION}-${OSVERSION}olp-stub rmdir /S /Q nh99\${CCVERSION}-${OSVERSION}olp-stub
	if exist tools99\${CCVERSION}-${OSVERSION}olp rmdir /S /Q tools99\${CCVERSION}-${OSVERSION}olp
	if exist df1b2-separable\${CCVERSION}-${OSVERSION}olp rmdir /S /Q df1b2-separable\${CCVERSION}-${OSVERSION}olp
	if exist df1b2-separable\${CCVERSION}-${OSVERSION}slp rmdir /S /Q df1b2-separable\${CCVERSION}-${OSVERSION}slp
	if exist df1b2-separable\tpl2rem.exe del /Q df1b2-separable\tpl2rem.exe
	if exist nh99\tpl2cpp.exe del /Q nh99\tpl2cpp.exe
	if exist nh99\lex.yy.c del /Q nh99\lex.yy.c

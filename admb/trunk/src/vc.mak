#.PHONY: dist verify

DISK=..\build
CCVERSION=vc
OSVERSION=win

#ifdef MSSDK
#PVMOPTION=-I"${MSSDK}/include"
#export PVMOPTION
#endif

default: all

all:
	IF EXIST $(DISK) rmdir /S /Q $(DISK)
	mkdir $(DISK)\bin
	mkdir $(DISK)\lib
	mkdir $(DISK)\include
	IF NOT EXIST linad99\$(CCVERSION)-$(OSVERSION)olp mkdir linad99\$(CCVERSION)-$(OSVERSION)olp 
	IF NOT EXIST linad99\$(CCVERSION)-$(OSVERSION)slp mkdir linad99\$(CCVERSION)-$(OSVERSION)slp 
	IF NOT EXIST nh99\$(CCVERSION)-$(OSVERSION)olp mkdir nh99\$(CCVERSION)-$(OSVERSION)olp 
	IF NOT EXIST nh99\$(CCVERSION)-$(OSVERSION)slp mkdir nh99\$(CCVERSION)-$(OSVERSION)slp 
	IF NOT EXIST nh99\$(CCVERSION)-$(OSVERSION)olp-stub mkdir nh99\$(CCVERSION)-$(OSVERSION)olp-stub 
	IF NOT EXIST tools99\$(CCVERSION)-$(OSVERSION)olp mkdir tools99\$(CCVERSION)-$(OSVERSION)olp 
	IF NOT EXIST tools99\$(CCVERSION)-$(OSVERSION)slp mkdir tools99\$(CCVERSION)-$(OSVERSION)slp 
	IF NOT EXIST df1b2-separable\$(CCVERSION)-$(OSVERSION)slp mkdir df1b2-separable\$(CCVERSION)-$(OSVERSION)slp 
	IF NOT EXIST df1b2-separable\$(CCVERSION)-$(OSVERSION)olp mkdir df1b2-separable\$(CCVERSION)-$(OSVERSION)olp 
	cd df1b2-separable\$(CCVERSION)-$(OSVERSION)olp& $(MAKE) DISKDIR=..\..\$(DISK) /f ..\optmsc8-laplace.mak all
	cd df1b2-separable\$(CCVERSION)-$(OSVERSION)slp& $(MAKE) DISKDIR=..\..\$(DISK) /f ..\safmsc8-laplace.mak all
	cd linad99\$(CCVERSION)-$(OSVERSION)olp& $(MAKE) DISKDIR=..\..\$(DISK) /f ..\optmsc8-laplace.mak all
	cd linad99\$(CCVERSION)-$(OSVERSION)slp& $(MAKE) DISKDIR=..\..\$(DISK) /f ..\safmsc8-laplace.mak all
	cd nh99\$(CCVERSION)-$(OSVERSION)olp& $(MAKE) DISKDIR=..\..\$(DISK) /f ..\optmsc8-laplace.mak all
	cd nh99\$(CCVERSION)-$(OSVERSION)slp& $(MAKE) DISKDIR=..\..\$(DISK) /f ..\safmsc8-laplace.mak all
	cd tools99\$(CCVERSION)-$(OSVERSION)olp& $(MAKE) DISKDIR=..\..\$(DISK) /f ..\optmsc8-laplace.mak all
	cd tools99\$(CCVERSION)-$(OSVERSION)slp& $(MAKE) DISKDIR=..\..\$(DISK) /f ..\safmsc8-laplace.mak all
	copy ..\scripts\vc\*.bat $(DISK)\bin
	copy ..\scripts\mingw\admb.bat $(DISK)\bin
	copy ..\LICENSE $(DISK)
	copy ..\README $(DISK)
	mkdir $(DISK)\examples
	xcopy ..\examples $(DISK)\examples /S
	copy ..\scripts\vc\Makefile $(DISK)\examples
	cd $(DISK)& cscript ..\scripts\create-admb-shortcut.vbs

verify:
	set ADMB_HOME=$(MAKEDIR)\$(DISK)
	set PATH=$(MAKEDIR)\$(DISK)\bin;$(PATH)
	cd $(MAKEDIR)\$(DISK)\examples& nmake /f Makefile all

clean:
	IF EXIST linad99\$(CCVERSION)-$(OSVERSION)olp rmdir /S /Q linad99\$(CCVERSION)-$(OSVERSION)olp
	IF EXIST linad99\$(CCVERSION)-$(OSVERSION)slp rmdir /S /Q linad99\$(CCVERSION)-$(OSVERSION)slp
	IF EXIST nh99\$(CCVERSION)-$(OSVERSION)olp rmdir /S /Q nh99\$(CCVERSION)-$(OSVERSION)olp
	IF EXIST nh99\$(CCVERSION)-$(OSVERSION)olp-stub rmdir /S /Q nh99\$(CCVERSION)-$(OSVERSION)olp-stub
	IF EXIST nh99\$(CCVERSION)-$(OSVERSION)slp rmdir /S /Q nh99\$(CCVERSION)-$(OSVERSION)slp
	IF EXIST tools99\$(CCVERSION)-$(OSVERSION)olp rmdir /S /Q tools99\$(CCVERSION)-$(OSVERSION)olp
	IF EXIST tools99\$(CCVERSION)-$(OSVERSION)slp rmdir /S /Q tools99\$(CCVERSION)-$(OSVERSION)slp
	IF EXIST df1b2-separable\$(CCVERSION)-$(OSVERSION)olp rmdir /S /Q df1b2-separable\$(CCVERSION)-$(OSVERSION)olp
	IF EXIST df1b2-separable\$(CCVERSION)-$(OSVERSION)slp rmdir /S /Q df1b2-separable\$(CCVERSION)-$(OSVERSION)slp

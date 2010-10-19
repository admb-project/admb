#.PHONY: dist verify

CXXFLAGS=/nologo /W4 /wd4018 /wd4552 /wd4189 /wd4101 /wd4505 /wd4715 /wd4700 /wd4239 /wd4702 /wd4702 /wd4511 /wd4512 /wd4100 /wd4127 /wd4706 /wd4996 /wd4244 /wd4146 /wd4701 /GF /EHsc /DUSE_LAPLACE /DWIN32 /I..\df1b2-separable /I..\linad99 /I..\nh99 /I..\tools99 /D__MSVC32__=8 /Ox


#DISK=..\build
#CCVERSION=vc
#OSVERSION=win

#ifdef MSSDK
#PVMOPTION=-I"${MSSDK}/include"
#export PVMOPTION
#endif

default: all

all:
	IF EXIST $(DEST) rmdir /S /Q $(DEST)
	mkdir $(DEST)
	mkdir $(DEST)\dist
	mkdir $(DEST)\dist\bin
	mkdir $(DEST)\dist\lib
	mkdir $(DEST)\dist\include
	mkdir $(DEST)\objects
	mkdir $(DEST)\objects\linad99-olp 
	mkdir $(DEST)\objects\linad99-slp 
	mkdir $(DEST)\objects\nh99-olp 
	mkdir $(DEST)\objects\nh99-slp 
	mkdir $(DEST)\objects\nh99-olp-stub 
	mkdir $(DEST)\objects\tools99-olp 
	mkdir $(DEST)\objects\tools99-slp 
	mkdir $(DEST)\objects\df1b2-separable-slp 
	mkdir $(DEST)\objects\df1b2-separable-olp 
	cd df1b2-separable && $(MAKE) CXXFLAGS="$(CXXFLAGS) /DOPT_LIB" DIST_DEST=..\$(DEST)\dist OBJECTS_DEST=..\$(DEST)\objects\df1b2-separable-olp /f optmsc8-laplace.mak all

all2:
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

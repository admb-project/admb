DISK=..\build\admb-bcc5.5-32bit
CXXFLAGS:=$(CXXFLAGS) -DADMB_VERSION=$(shell cat ../VERSION)

OPT_CXXFLAGS ="-c -q -f -WC -O2 -5 -I${BCC55_HOME}\Include -DADMB_VERSION=11 -DUSE_LAPLACE -DDOS386 -DOPT_LIB -I..\linad99 -I..\nh99 -I..\df1b2-separable -I..\tools99"
SAFE_CXXFLAGS ="-c -q -f -WC -O2 -5 -I${BCC55_HOME}\Include -DADMB_VERSION=11 -DUSE_LAPLACE -DDOS386 -DSAFE_ALL -I..\linad99 -I..\nh99 -I..\df1b2-separable -I..\tools99"

all: dist

dist:
	IF NOT EXIST $(DISK)\dist\bin md $(DISK)\dist\bin
	IF NOT EXIST $(DISK)\dist\lib md $(DISK)\dist\lib
	IF NOT EXIST $(DISK)\dist\include md $(DISK)\dist\include
	IF NOT EXIST $(DISK)\objects\linad99-olp md $(DISK)\objects\linad99-olp
	IF NOT EXIST $(DISK)\objects\linad99-slp md $(DISK)\objects\linad99-slp
	cd linad99
	$(MAKE) CC=bcc32 CXXFLAGS=$(OPT_CXXFLAGS) LIBPATH=..\$(DISK)\objects\linad99-olp DISKDIR=..\$(DISK) -f optbor32-laplace.mak all
	$(MAKE) CC=bcc32 CXXFLAGS=$(SAFE_CXXFLAGS) LIBPATH=..\$(DISK)\objects\linad99-slp DISKDIR=..\$(DISK) -f safbor32-laplace.mak all
	cd ..
	IF NOT EXIST $(DISK)\objects\tools99-olp md $(DISK)\objects\tools99-olp
	IF NOT EXIST $(DISK)\objects\tools99-slp md $(DISK)\objects\tools99-slp
	cd tools99
	$(MAKE) CC=bcc32 CXXFLAGS=$(OPT_CXXFLAGS) LIBPATH=..\$(DISK)\objects\tools99-olp DISKDIR=..\$(DISK) -f optbor32-laplace.mak all
	$(MAKE) CC=bcc32 CXXFLAGS=$(SAFE_CXXFLAGS) LIBPATH=..\$(DISK)\objects\tools99-slp DISKDIR=..\$(DISK) -f safbor32-laplace.mak all
	cd ..
	IF NOT EXIST $(DISK)\objects\df1b2-separable-olp md $(DISK)\objects\df1b2-separable-olp
	IF NOT EXIST $(DISK)\objects\df1b2-separable-slp md $(DISK)\objects\df1b2-separable-slp
	cd df1b2-separable
	$(MAKE) CC=bcc32 CXXFLAGS=$(OPT_CXXFLAGS) LIBPATH=..\$(DISK)\objects\df1b2-separable-olp DISKDIR=..\$(DISK) -f optbor32-laplace.mak all
	$(MAKE) CC=bcc32 CXXFLAGS=$(SAFE_CXXFLAGS) LIBPATH=..\$(DISK)\objects\df1b2-separable-slp DISKDIR=..\$(DISK) -f safbor32-laplace.mak all
	cd ..
	IF NOT EXIST $(DISK)\objects\nh99-olp md $(DISK)\objects\nh99-olp
	IF NOT EXIST $(DISK)\objects\nh99-slp md $(DISK)\objects\nh99-slp
	cd nh99
	$(MAKE) CC=bcc32 CXXFLAGS=$(OPT_CXXFLAGS) LIBPATH=..\$(DISK)\objects\nh99-olp DISKDIR=..\$(DISK) -f optbor32-laplace.mak all
	$(MAKE) CC=bcc32 CXXFLAGS=$(SAFE_CXXFLAGS) LIBPATH=..\$(DISK)\objects\nh99-slp DISKDIR=..\$(DISK) -f safbor32-laplace.mak all
	cd ..
	copy ..\LICENSE.txt $(DISK)\dist
	copy ..\README.txt $(DISK)\dist
	copy ..\CHANGES.txt $(DISK)\dist
	copy ..\VERSION $(DISK)\dist
	copy ..\utilities\sed.exe $(DISK)\dist\bin
	copy ..\scripts\bcc32\contrib.h $(DISK)\dist\include
	copy ..\scripts\bcc32\adcomp.bat $(DISK)\dist\bin
	copy ..\scripts\bcc32\adlink.bat $(DISK)\dist\bin
	copy ..\scripts\bcc32\set-admb-bcc551.bat $(DISK)\dist\bin
	copy ..\scripts\admb\admb.bat $(DISK)\dist\bin
	IF NOT EXIST $(DISK)\dist\examples md $(DISK)\dist\examples
	xcopy ..\examples $(DISK)\dist\examples /S /Y

verify:
	cd $(DISK)\dist
	cmd /C "set ADMB_HOME=%CD%& set PATH=%CD%\bin;$(PATH)& cd examples& make all"
	-..\..\..\scripts\get-outputs.bat > ..\..\..\benchmarks-opt.txt
	cmd /C "set ADMB_HOME=%CD%& set PATH=%CD%\bin;$(PATH)& cd examples& make OPTION=-s all"
	-..\..\..\scripts\get-outputs.bat > ..\..\..\benchmarks-saf.txt

clean:
	IF EXIST $(DISK) rd /S /Q ..\build

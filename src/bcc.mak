DISK=..\build\admb-10.0-bcc5.5-32bit

OPT_CXXFLAGS ="-q -I${BCC55_HOME}\Include -DUSE_LAPLACE -WC -O2 -5 -DDOS386 -DOPT_LIB -I..\linad99 -c -f -I..\sparse -I..\nh99 -I..\df1b2-separable -I..\tools99"
SAFE_CXXFLAGS ="-q -I${BCC55_HOME}\Include -DUSE_LAPLACE -WC -O2 -5 -DDOS386 -DSAFE_ALL -I..\linad99 -c -f -I..\sparse -I..\nh99 -I..\df1b2-separable -I..\tools99"

all: dist

dist:
	IF NOT EXIST $(DISK)\dist\bin mkdir $(DISK)\dist\bin
	IF NOT EXIST $(DISK)\dist\lib mkdir $(DISK)\dist\lib
	IF NOT EXIST $(DISK)\dist\include mkdir $(DISK)\dist\include
	IF NOT EXIST $(DISK)\objects\linad99-olp mkdir $(DISK)\objects\linad99-olp
	IF NOT EXIST $(DISK)\objects\linad99-slp mkdir $(DISK)\objects\linad99-slp
	cd linad99
	$(MAKE) CC=bcc32 CXXFLAGS=$(OPT_CXXFLAGS) LIBPATH=..\$(DISK)\objects\linad99-olp DISKDIR=..\$(DISK) -f optbor32-laplace.mak all
	$(MAKE) CC=bcc32 CXXFLAGS=$(SAFE_CXXFLAGS) LIBPATH=..\$(DISK)\objects\linad99-slp DISKDIR=..\$(DISK) -f safbor32-laplace.mak all
	cd ..
	IF NOT EXIST $(DISK)\objects\tools99-olp mkdir $(DISK)\objects\tools99-olp
	IF NOT EXIST $(DISK)\objects\tools99-slp mkdir $(DISK)\objects\tools99-slp
	cd tools99
	$(MAKE) CC=bcc32 CXXFLAGS=$(OPT_CXXFLAGS) LIBPATH=..\$(DISK)\objects\tools99-olp DISKDIR=..\$(DISK) -f optbor32-laplace.mak all
	$(MAKE) CC=bcc32 CXXFLAGS=$(SAFE_CXXFLAGS) LIBPATH=..\$(DISK)\objects\tools99-slp DISKDIR=..\$(DISK) -f safbor32-laplace.mak all
	cd ..
	IF NOT EXIST $(DISK)\objects\df1b2-separable-olp mkdir $(DISK)\objects\df1b2-separable-olp
	IF NOT EXIST $(DISK)\objects\df1b2-separable-slp mkdir $(DISK)\objects\df1b2-separable-slp
	cd df1b2-separable
	$(MAKE) CC=bcc32 CXXFLAGS=$(OPT_CXXFLAGS) LIBPATH=..\$(DISK)\objects\df1b2-separable-olp DISKDIR=..\$(DISK) -f optbor32-laplace.mak all
	$(MAKE) CC=bcc32 CXXFLAGS=$(SAFE_CXXFLAGS) LIBPATH=..\$(DISK)\objects\df1b2-separable-slp DISKDIR=..\$(DISK) -f safbor32-laplace.mak all
	cd ..
	IF NOT EXIST $(DISK)\objects\nh99-olp mkdir $(DISK)\objects\nh99-olp
	IF NOT EXIST $(DISK)\objects\nh99-slp mkdir $(DISK)\objects\nh99-slp
	cd nh99
	$(MAKE) CC=bcc32 CXXFLAGS=$(OPT_CXXFLAGS) LIBPATH=..\$(DISK)\objects\nh99-olp DISKDIR=..\$(DISK) -f optbor32-laplace.mak all
	$(MAKE) CC=bcc32 CXXFLAGS=$(SAFE_CXXFLAGS) LIBPATH=..\$(DISK)\objects\nh99-slp DISKDIR=..\$(DISK) -f safbor32-laplace.mak all
	cd ..
	copy ..\LICENSE $(DISK)\dist
	copy ..\README.txt $(DISK)\dist
	copy ..\scripts\bcc32\adcomp.bat $(DISK)\dist\bin
	copy ..\scripts\bcc32\adlink.bat $(DISK)\dist\bin
	copy ..\scripts\bcc32\set-admb-bcc551.bat $(DISK)\dist\bin
	copy ..\scripts\admb\admb.bat $(DISK)\dist\bin
	IF NOT EXIST $(DISK)\dist\examples mkdir $(DISK)\dist\examples
	xcopy ..\examples $(DISK)\dist\examples /S /Y
	copy ..\scripts\cl\Makefile $(DISK)\dist\examples

verify:
	cd $(DISK)\dist
	cmd /C "set ADMB_HOME=%CD%& set PATH=%CD%\bin;$(PATH)& cd examples& make all"
	-..\..\..\scripts\get-outputs.bat > ..\..\..\benchmarks-opt.txt
	cmd /C "set ADMB_HOME=%CD%& set PATH=%CD%\bin;$(PATH)& cd examples& make OPTION=-s all"
	-..\..\..\scripts\get-outputs.bat > ..\..\..\benchmarks-saf.txt

clean:
	IF EXIST $(DISK) rmdir /S /Q $(DISK)

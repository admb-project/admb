DISK=..\build\admb-10.0-vc10-32bit
#DISK=..\build\admb-10.0-vc10-64bit

#ifdef MSSDK
#PVMOPTION=-I"${MSSDK}/include"
#export PVMOPTION
#endif

all:
	mkdir $(DISK)\dist\bin
	mkdir $(DISK)\dist\lib
	mkdir $(DISK)\dist\include
	IF NOT EXIST $(DISK)\objects\df1b2-separable-olp mkdir $(DISK)\objects\df1b2-separable-olp
	IF NOT EXIST $(DISK)\objects\df1b2-separable-slp mkdir $(DISK)\objects\df1b2-separable-slp
	cd df1b2-separable& $(MAKE) DISK=..\..\$(DISK) /f optmsc8-laplace.mak all
	cd df1b2-separable& $(MAKE) DISK=..\..\$(DISK) /f safmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\linad99-olp mkdir $(DISK)\objects\linad99-olp 
	IF NOT EXIST $(DISK)\objects\linad99-slp mkdir $(DISK)\objects\linad99-slp 
	cd linad99& $(MAKE) DISK=..\..\$(DISK) /f optmsc8-laplace.mak all
	cd linad99& $(MAKE) DISK=..\..\$(DISK) /f safmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\nh99-olp mkdir $(DISK)\objects\nh99-olp 
	IF NOT EXIST $(DISK)\objects\nh99-slp mkdir $(DISK)\objects\nh99-slp 
	cd nh99& $(MAKE) DISK=..\..\$(DISK) /f optmsc8-laplace.mak all
	cd nh99& $(MAKE) DISK=..\..\$(DISK) /f safmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\tools99-olp mkdir $(DISK)\objects\tools99-olp 
	IF NOT EXIST $(DISK)\objects\tools99-slp mkdir $(DISK)\objects\tools99-slp 
	cd tools99& $(MAKE) DISK=..\..\$(DISK) /f optmsc8-laplace.mak all
	cd tools99& $(MAKE) DISK=..\..\$(DISK) /f safmsc8-laplace.mak all
	copy ..\scripts\cl\adlink.bat $(DISK)\dist\bin
	copy ..\scripts\cl\adcomp.bat $(DISK)\dist\bin
	copy ..\scripts\admb\admb.bat $(DISK)\dist\bin
	copy ..\LICENSE $(DISK)\dist
	copy ..\README.txt $(DISK)\dist
	IF NOT EXIST $(DISK)\dist\examples mkdir $(DISK)\dist\examples
	xcopy ..\examples $(DISK)\dist\examples /S
	copy ..\scripts\vc\Makefile $(DISK)\dist\examples
	cd $(DISK)\dist& cscript ..\scripts\create-admb-shortcut.vbs

verify:
	set ADMB_HOME=$(MAKEDIR)\$(DISK)\dist
	set PATH=$(MAKEDIR)\$(DISK)\dist\bin;$(PATH)
	cd $(MAKEDIR)\$(DISK)\dist\examples& nmake /f Makefile all
	-..\scripts\get-outputs.bat > "..\benchmarks-opt.txt"
	cd $(MAKEDIR)\$(DISK)\dist\examples& nmake /f Makefile OPTION=-s all
	-..\scripts\get-outputs.bat > "..\benchmarks-saf.txt"

clean:
	IF EXIST $(DISK) rmdir /S /Q $(DISK)

DISK=..\build\admb-10.0-vc10-32bit
#DISK=..\build\admb-10.0-vc10-64bit

all:
	IF NOT EXIST $(DISK) mkdir $(DISK)
	IF NOT EXIST $(DISK)\dist mkdir $(DISK)\dist
	IF NOT EXIST $(DISK)\dist\bin mkdir $(DISK)\dist\bin
	IF NOT EXIST $(DISK)\dist\lib mkdir $(DISK)\dist\lib
	IF NOT EXIST $(DISK)\dist\include mkdir $(DISK)\dist\include
	IF NOT EXIST $(DISK)\objects mkdir $(DISK)\objects
	IF NOT EXIST $(DISK)\objects\df1b2-separable-slp mkdir $(DISK)\objects\df1b2-separable-slp 
	IF NOT EXIST $(DISK)\objects\df1b2-separable-olp mkdir $(DISK)\objects\df1b2-separable-olp 
	cd $(DISK)\objects\df1b2-separable-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\df1b2-separable\safmsc8-laplace.mak all
	cd $(DISK)\objects\df1b2-separable-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\df1b2-separable\optmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\linad99-olp mkdir $(DISK)\objects\linad99-olp 
	IF NOT EXIST $(DISK)\objects\linad99-slp mkdir $(DISK)\objects\linad99-slp 
	cd $(DISK)\objects\linad99-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\linad99\optmsc8-laplace.mak all
	cd $(DISK)\objects\linad99-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\linad99\safmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\nh99-olp mkdir $(DISK)\objects\nh99-olp 
	IF NOT EXIST $(DISK)\objects\nh99-slp mkdir $(DISK)\objects\nh99-slp 
	cd $(DISK)\objects\nh99-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\nh99\optmsc8-laplace.mak all
	cd $(DISK)\objects\nh99-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\nh99\safmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\tools99-olp mkdir $(DISK)\objects\tools99-olp 
	IF NOT EXIST $(DISK)\objects\tools99-slp mkdir $(DISK)\objects\tools99-slp 
	cd $(DISK)\objects\tools99-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\tools99\optmsc8-laplace.mak all
	cd $(DISK)\objects\tools99-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\tools99\safmsc8-laplace.mak all
	copy ..\scripts\cl\*.bat $(DISK)\dist\bin
	copy ..\scripts\admb\admb.bat $(DISK)\dist\bin
	copy ..\LICENSE $(DISK)\dist
	copy ..\README.txt $(DISK)\dist
	IF NOT EXIST $(DISK)\dist\examples mkdir $(DISK)\dist\examples
	xcopy ..\examples $(DISK)\dist\examples /S /Y
	copy ..\scripts\cl\Makefile $(DISK)\dist\examples
	cd $(DISK)\dist& cscript ..\..\..\scripts\create-admb-shortcut.vbs

verify:
	cmd /C "set ADMB_HOME=$(MAKEDIR)\$(DISK)\dist& set PATH=$(MAKEDIR)\$(DISK)\dist\bin;$(PATH)& cd $(MAKEDIR)\$(DISK)\dist\examples& nmake all"
	-cd $(MAKEDIR)\$(DISK)\dist& ..\..\..\scripts\get-outputs.bat > "..\..\..\benchmarks-opt.txt"
	cmd /C "set ADMB_HOME=$(MAKEDIR)\$(DISK)\dist& set PATH=$(MAKEDIR)\$(DISK)\dist\bin;$(PATH)& cd $(MAKEDIR)\$(DISK)\dist\examples& nmake OPTION=-s all"
	-cd $(MAKEDIR)\$(DISK)\dist& ..\..\..\scripts\get-outputs.bat > "..\..\..\benchmarks-saf.txt"

clean:
	IF EXIST $(DISK) rmdir /S /Q $(DISK)

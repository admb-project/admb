DISK=..\build\admb-vc10

all: admb contrib

admb:
	IF NOT EXIST $(DISK) md $(DISK)
	IF NOT EXIST $(DISK)\dist md $(DISK)\dist
	IF NOT EXIST $(DISK)\dist\bin md $(DISK)\dist\bin
	IF NOT EXIST $(DISK)\dist\lib md $(DISK)\dist\lib
	IF NOT EXIST $(DISK)\dist\include md $(DISK)\dist\include
	IF NOT EXIST $(DISK)\objects md $(DISK)\objects

	IF NOT EXIST $(DISK)\objects\df1b2-separable-slp md $(DISK)\objects\df1b2-separable-slp
	IF NOT EXIST $(DISK)\objects\df1b2-separable-olp md $(DISK)\objects\df1b2-separable-olp
	cd $(DISK)\objects\df1b2-separable-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\df1b2-separable\safmsc8-laplace.mak all
	cd $(DISK)\objects\df1b2-separable-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\df1b2-separable\optmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\linad99-olp md $(DISK)\objects\linad99-olp
	IF NOT EXIST $(DISK)\objects\linad99-slp md $(DISK)\objects\linad99-slp
	cd $(DISK)\objects\linad99-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\linad99\optmsc8-laplace.mak all
	cd $(DISK)\objects\linad99-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\linad99\safmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\nh99-olp md $(DISK)\objects\nh99-olp
	IF NOT EXIST $(DISK)\objects\nh99-slp md $(DISK)\objects\nh99-slp
	cd $(DISK)\objects\nh99-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\nh99\optmsc8-laplace.mak all
	cd $(DISK)\objects\nh99-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\nh99\safmsc8-laplace.mak all
	IF NOT EXIST $(DISK)\objects\tools99-olp md $(DISK)\objects\tools99-olp
	IF NOT EXIST $(DISK)\objects\tools99-slp md $(DISK)\objects\tools99-slp
	cd $(DISK)\objects\tools99-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\tools99\optmsc8-laplace.mak all
	cd $(DISK)\objects\tools99-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\src\tools99\safmsc8-laplace.mak all

	copy ..\scripts\cl\*.bat $(DISK)\dist\bin
	copy ..\scripts\admb\admb.bat $(DISK)\dist\bin
	copy ..\utilities\sed.exe $(DISK)\dist\bin
	copy ..\LICENSE.txt $(DISK)\dist
	copy ..\NEWS.txt $(DISK)\dist
	copy ..\README.txt $(DISK)\dist
	IF NOT EXIST $(DISK)\dist\examples md $(DISK)\dist\examples
	xcopy ..\examples $(DISK)\dist\examples /S /Y
	copy ..\scripts\cl\Makefile $(DISK)\dist\examples
	cd $(DISK)\dist& cscript ..\..\..\scripts\create-admb-shortcut.vbs

contrib:
  IF NOT EXIST $(DISK)\dist\contrib md $(DISK)\dist\contrib
  IF NOT EXIST $(DISK)\objects\contrib-olp md $(DISK)\objects\contrib-olp
  IF NOT EXIST $(DISK)\objects\contrib-slp md $(DISK)\objects\contrib-slp
	cd $(DISK)\objects\contrib-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\contrib\Makefile statslib-opt
	cd $(DISK)\objects\contrib-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\contrib\Makefile statslib-saf
	cd $(DISK)\objects\contrib-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\contrib\Makefile ecolib-opt
	cd $(DISK)\objects\contrib-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\contrib\Makefile ecolib-saf
	rem cd $(DISK)\objects\contrib-olp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\contrib\Makefile qfclib-opt
	rem cd $(DISK)\objects\contrib-slp& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\contrib\Makefile qfclib-saf
	cd $(DISK)\dist\contrib& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\contrib\Makefile contribo.lib
	cd $(DISK)\dist\contrib& $(MAKE) DISKDIR=..\..\dist /f ..\..\..\..\contrib\Makefile contribs.lib

verify:
	cmd /C "set ADMB_HOME=$(MAKEDIR)\$(DISK)\dist& set PATH=$(MAKEDIR)\$(DISK)\dist\bin;$(PATH)& cd $(MAKEDIR)\$(DISK)\dist\examples& nmake all"
	-cd $(MAKEDIR)\$(DISK)\dist& ..\..\..\scripts\get-outputs.bat > "..\..\..\benchmarks-opt.txt"
	cmd /C "set ADMB_HOME=$(MAKEDIR)\$(DISK)\dist& set PATH=$(MAKEDIR)\$(DISK)\dist\bin;$(PATH)& cd $(MAKEDIR)\$(DISK)\dist\examples& nmake OPTION=-s all"
	-cd $(MAKEDIR)\$(DISK)\dist& ..\..\..\scripts\get-outputs.bat > "..\..\..\benchmarks-saf.txt"

clean:
	IF EXIST $(DISK) rd /S /Q $(DISK)

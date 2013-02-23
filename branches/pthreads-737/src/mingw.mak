.PHONY: dist verify

SHELL:=$(COMSPEC)
DISK=..\build\mingw
LIBPATH=..\build\objects\mingw

CCVERSION=mingw
OSVERSION=win
CXX=g++.exe

all: dist contrib

dist:
	if exist $(DISK) rd /S /Q $(DISK)
	md $(DISK)\bin
	md $(DISK)\include
	md $(DISK)\lib
	if exist $(LIBPATH) rd /S /Q $(LIBPATH)
	md $(LIBPATH)
	md $(LIBPATH)\df1b2-separable-olp
	md $(LIBPATH)\df1b2-separable-slp
	md $(LIBPATH)\linad99-olp
	md $(LIBPATH)\linad99-slp
	md $(LIBPATH)\nh99-olp
	md $(LIBPATH)\tools99-olp
	$(MAKE) -C df1b2-separable CC=$(CXX) LIBPATH=..\$(LIBPATH)\df1b2-separable-olp DISKDIR=..\$(DISK) -f mingw-optg32-rh8-laplace.mak disk
	$(MAKE) -C df1b2-separable CC=$(CXX) LIBPATH=..\$(LIBPATH)\df1b2-separable-slp DISKDIR=..\$(DISK) -f mingw-safg32-rh8-laplace.mak disk
	$(MAKE) -C linad99 CC=$(CXX) LIBPATH=..\$(LIBPATH)\linad99-olp DISKDIR=..\$(DISK) -f mingw-optg32-rh8-laplace.mak disk
	$(MAKE) -C linad99 CC=$(CXX) LIBPATH=..\$(LIBPATH)\linad99-slp DISKDIR=..\$(DISK) PVMOPTION=-Dlinux -f mingw-safg32-rh8-laplace.mak disk
	$(MAKE) -C nh99 CC=$(CXX) LIBPATH=..\$(LIBPATH)\nh99-olp DISKDIR=..\$(DISK) -f mingw-optg32-rh8-laplace.mak disk
	$(MAKE) -C tools99 CC=$(CXX) LIBPATH=..\$(LIBPATH)\tools99-olp DISKDIR=..\$(DISK) -f mingw-optg32-rh8-laplace.mak disk
	copy ..\LICENSE.txt $(DISK)
	copy ..\NEWS.txt $(DISK)
	copy ..\README.txt $(DISK)
	copy ..\VERSION $(DISK)
	copy ..\scripts\mingw\Makefile $(DISK)
	copy ..\scripts\mingw\*.bat $(DISK)\bin
	copy ..\scripts\admb\*.bat $(DISK)\bin
	copy "..\scripts\g++"\*.bat $(DISK)\bin
	md ${DISK}\examples
	xcopy ..\examples $(DISK)\examples /S

contrib:
	$(MAKE) -C ..\contrib CXX=g++.exe LIBPATH=$(LIBPATH) DISK=$(DISK)

verify:
	cmd /C "set ADMB_HOME=%CD%\$(DISK)& set PATH=%CD%\$(DISK)\bin;$(PATH)& $(MAKE) -C ${DISK} all"

tests:
	cmd /C "set ADMB_HOME=%CD%\$(DISK)& set PATH=%CD%\$(DISK)\bin;$(PATH)& $(MAKE) -C ..\tests"

clean:
	if exist df1b2-separable\${CCVERSION}-${OSVERSION}olp rd /S /Q df1b2-separable\${CCVERSION}-${OSVERSION}olp
	if exist df1b2-separable\${CCVERSION}-${OSVERSION}slp rd /S /Q df1b2-separable\${CCVERSION}-${OSVERSION}slp
	if exist linad99\\${CCVERSION}-${OSVERSION}olp rd /S /Q linad99\\${CCVERSION}-${OSVERSION}olp
	if exist linad99\${CCVERSION}-${OSVERSION}slp rd /S /Q linad99\${CCVERSION}-${OSVERSION}slp
	if exist nh99\${CCVERSION}-${OSVERSION}olp rd /S /Q nh99\${CCVERSION}-${OSVERSION}olp
	if exist tools99\${CCVERSION}-${OSVERSION}olp rd /S /Q tools99\${CCVERSION}-${OSVERSION}olp
	if exist df1b2-separable\lex.yy.c del df1b2-separable\lex.yy.c
	if exist df1b2-separable\tpl2rem.c del df1b2-separable\tpl2rem.c
	if exist df1b2-separable\tpl2rem.exe del df1b2-separable\tpl2rem.exe
	if exist nh99\lex.yy.c del nh99\lex.yy.c
	if exist nh99\tpl2cpp.c del nh99\tpl2cpp.c
	if exist nh99\tpl2cpp.exe del nh99\tpl2cpp.exe

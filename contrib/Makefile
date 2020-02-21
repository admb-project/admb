!IF ([cl /? 2>&1 | findstr /C:"Compiler Version 19." > nul] == 0)
CXXVERSION=-cl19
!ELSE
CXXVERSION=-cl
!ENDIF
!IF ([cl /? 2>&1 | findstr /C:" x64" > nul] == 0)
OSNAME=win64
!ELSEIF ([cl /? 2>&1 | findstr /C:" x86" > nul] == 0)
OSNAME=win32
!ELSE
OSNAME=vs
!ENDIF

DESTDIR=..\build\admb
!IFDEF DEBUG
_DEBUG=-debug
!ENDIF
OBJDESTDIR=..\build\objects\$(OSNAME)$(CXXVERSION)$(_DEBUG)

all:
	$(MAKE) /nologo contrib-includes
	$(MAKE) /nologo contrib-libs
	$(MAKE) /nologo contrib-ad2csv
	
shared:
	IF EXIST $(DESTDIR)\lib\admb-contrib$(_DEBUG).dll del $(DESTDIR)\lib\admb-contrib$(_DEBUG).dll
	pushd $(OBJDESTDIR)& link /DLL /OUT:..\..\$(DESTDIR)\lib\admb-contrib$(_DEBUG).dll /NOLOGO /IGNORE:4006 ..\..\$(DESTDIR)\lib\admb-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib contrib-saflp-*.obj
!IFNDEF SAFE_ONLY
	IF EXIST $(DESTDIR)\lib\admb-contribo-$(OSNAME)$(CXXVERSION)$(_DEBUG).dll del $(DESTDIR)\lib\admb-contribo-$(OSNAME)$(CXXVERSION)$(_DEBUG).dll
	pushd $(OBJDESTDIR)& link /DLL /OUT:..\..\$(DESTDIR)\lib\admb-contribo$(_DEBUG).dll /NOLOGO /IGNORE:4006 ..\..\$(DESTDIR)\lib\admbo-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib contrib-optlp-*.obj
!ENDIf

contrib-includes: contrib-dirs
	pushd ecolib& $(MAKE) /nologo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd gdbprintlib& $(MAKE) /nologo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd qfclib& $(MAKE) /nologo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd statslib& $(MAKE) /nologo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd src& $(MAKE) /nologo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes

contrib-dirs:
	IF NOT EXIST $(DESTDIR)\include\contrib md $(DESTDIR)\include\contrib
	IF NOT EXIST $(OBJDESTDIR) md $(OBJDESTDIR)

contrib-libs: contrib-ecolib contrib-gdbprintlib contrib-qfclib contrib-statslib contrib-src
	IF EXIST $(DESTDIR)\lib\admb-contrib-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib del $(DESTDIR)\lib\admb-contrib-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib
	copy $(DESTDIR)\lib\admb-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib $(DESTDIR)\lib\admb-contrib-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib
	pushd $(OBJDESTDIR)& lib ..\..\$(DESTDIR)\lib\admb-contrib-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib /NOLOGO /IGNORE:4006 contrib-saflp-*.obj
!IFNDEF SAFE_ONLY
	IF EXIST $(DESTDIR)\lib\admb-contribo-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib del $(DESTDIR)\lib\admb-contribo-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib
	copy $(DESTDIR)\lib\admbo-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib $(DESTDIR)\lib\admb-contribo-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib
	pushd $(OBJDESTDIR)& lib ..\..\$(DESTDIR)\lib\admb-contribo-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib /NOLOGO /IGNORE:4006 contrib-optlp-*.obj
!ENDIF

contrib-ad2csv:
	pushd ad2csv& $(MAKE) /nologo

contrib-ecolib:
	pushd ecolib& $(MAKE) /nologo

contrib-gdbprintlib:
	pushd gdbprintlib& $(MAKE) /nologo

contrib-qfclib:
	pushd qfclib& $(MAKE) /nologo

contrib-statslib:
	pushd statslib& $(MAKE) /nologo

contrib-src:
	pushd src& $(MAKE) /nologo

test:
	pushd ecolib& $(MAKE) /nologo test
	pushd qfclib& $(MAKE) /nologo test

clean:
	pushd ecolib& $(MAKE) /nologo clean
	pushd gdbprintlib& $(MAKE) /nologo clean
	pushd qfclib& $(MAKE) /nologo clean
	pushd statslib& $(MAKE) /nologo clean
	pushd src& $(MAKE) /nologo clean
	pushd ad2csv& $(MAKE) /nologo clean

copy:
	IF NOT EXIST $(DESTDIR)\contrib xcopy /I /E /Y ..\contrib $(DESTDIR)\contrib
	pushd $(DESTDIR)\contrib& $(MAKE) /nologo clean& popd

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
	$(MAKE) contrib-includes
	$(MAKE) contrib-libs
	$(MAKE) contrib-ad2csv
	
shared:
	IF EXIST $(DESTDIR)\lib\admb-contrib$(_DEBUG).dll del $(DESTDIR)\lib\admb-contrib$(_DEBUG).dll
	pushd $(OBJDESTDIR)& link /DLL /OUT:..\..\$(DESTDIR)\lib\admb-contrib$(_DEBUG).dll /NOLOGO /IGNORE:4006 ..\..\$(DESTDIR)\lib\admb$(OSNAME)$(CXXVERSION)$(_DEBUG).lib contrib-saflp-*.obj
!IFNDEF SAFE_ONLY
	IF EXIST $(DESTDIR)\lib\admb-contribo-$(OSNAME)$(CXXVERSION)$(_DEBUG).dll del $(DESTDIR)\lib\admb-contribo-$(OSNAME)$(CXXVERSION)$(_DEBUG).dll
	pushd $(OBJDESTDIR)& link /DLL /OUT:..\..\$(DESTDIR)\lib\admb-contribo$(_DEBUG).dll /NOLOGO /IGNORE:4006 ..\..\$(DESTDIR)\lib\admbo-$(OSNAME)$(CXXVERSION)$(_DEBUG).lib contrib-optlp-*.obj
!ENDIf

contrib-includes: contrib-dirs
	pushd ecolib& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd gdbprintlib& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd qfclib& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd statslib& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd src& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes

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
	pushd ad2csv& $(MAKE)

contrib-ecolib:
	pushd ecolib& $(MAKE)

contrib-gdbprintlib:
	pushd gdbprintlib& $(MAKE)

contrib-qfclib:
	pushd qfclib& $(MAKE)

contrib-statslib:
	pushd statslib& $(MAKE)

contrib-src:
	pushd src& $(MAKE)

test:
	pushd ecolib& $(MAKE) test
	pushd qfclib& $(MAKE) test

clean:
	pushd ecolib& $(MAKE) clean
	pushd gdbprintlib& $(MAKE) clean
	pushd qfclib& $(MAKE) clean
	pushd statslib& $(MAKE) clean
	pushd src& $(MAKE) clean
	pushd ad2csv& $(MAKE) clean

copy:
	IF NOT EXIST $(DESTDIR)\contrib xcopy /I /E /Y ..\contrib $(DESTDIR)\contrib
	pushd $(DESTDIR)\contrib& $(MAKE) clean& popd

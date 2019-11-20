!IF ([cl /? 2>&1 | findstr /C:"Compiler Version 19." > nul] == 0)
CXXVERSION=-cl19
!ELSE
CXXVERSION=-cl
!ENDIF
!IF ([cl /? 2>&1 | findstr /C:" x64" > nul] == 0)
OSNAME=-vsx64
!ELSEIF ([cl /? 2>&1 | findstr /C:" x86" > nul] == 0)
OSNAME=-vsx86
!ELSE
OSNAME=-vs
!ENDIF

!IF DEFINED(DEBUG)
DESTDIR=..\build\debug
OBJDESTDIR=..\build\objects$(OSNAME)$(CXXVERSION)\debug
!ELSE
DESTDIR=..\build\dist
OBJDESTDIR=..\build\objects$(OSNAME)$(CXXVERSION)\dist
!ENDIf
all:
	$(MAKE) /nlogo contrib-includes
	$(MAKE) /nlogo contrib-libs
	$(MAKE) /nlogo contrib-ad2csv
	
shared:
	IF EXIST $(DESTDIR)\lib\admb-contrib.dll del $(DESTDIR)\lib\admb-contrib.dll
	pushd $(OBJDESTDIR)& link /DLL /OUT:..\..\$(DESTDIR)\lib\admb-contrib.dll /NOLOGO /IGNORE:4006 ..\..\$(DESTDIR)\lib\admb$(OSNAME)$(CXXVERSION).lib contrib-saflp-*.obj
!IFNDEF SAFE_ONLY
	IF EXIST $(DESTDIR)\lib\admb-contribo$(OSNAME)$(CXXVERSION).dll del $(DESTDIR)\lib\admb-contribo$(OSNAME)$(CXXVERSION).dll
	pushd $(OBJDESTDIR)& link /DLL /OUT:..\..\$(DESTDIR)\lib\admb-contribo.dll /NOLOGO /IGNORE:4006 ..\..\$(DESTDIR)\lib\admbo$(OSNAME)$(CXXVERSION).lib contrib-optlp-*.obj
!ENDIf

contrib-includes: contrib-dirs
	pushd ecolib& $(MAKE) /nlogo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd gdbprintlib& $(MAKE) /nlogo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd qfclib& $(MAKE) /nlogo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd statslib& $(MAKE) /nlogo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes
	pushd src& $(MAKE) /nlogo CONTRIB_INCLUDE=..\$(DESTDIR)\include\contrib includes

contrib-dirs:
	IF NOT EXIST $(DESTDIR)\include\contrib md $(DESTDIR)\include\contrib
	IF NOT EXIST $(OBJDESTDIR) md $(OBJDESTDIR)

contrib-libs: contrib-ecolib contrib-gdbprintlib contrib-qfclib contrib-statslib contrib-src
	IF EXIST $(DESTDIR)\lib\admb-contrib$(OSNAME)$(CXXVERSION).lib del $(DESTDIR)\lib\admb-contrib$(OSNAME)$(CXXVERSION).lib
	copy $(DESTDIR)\lib\admb$(OSNAME)$(CXXVERSION).lib $(DESTDIR)\lib\admb-contrib$(OSNAME)$(CXXVERSION).lib
	pushd $(OBJDESTDIR)& lib ..\..\$(DESTDIR)\lib\admb-contrib$(OSNAME)$(CXXVERSION).lib /NOLOGO /IGNORE:4006 contrib-saflp-*.obj
!IFNDEF SAFE_ONLY
	IF EXIST $(DESTDIR)\lib\admb-contribo$(OSNAME)$(CXXVERSION).lib del $(DESTDIR)\lib\admb-contribo$(OSNAME)$(CXXVERSION).lib
	copy $(DESTDIR)\lib\admbo$(OSNAME)$(CXXVERSION).lib $(DESTDIR)\lib\admb-contribo$(OSNAME)$(CXXVERSION).lib
	pushd $(OBJDESTDIR)& lib ..\..\$(DESTDIR)\lib\admb-contribo$(OSNAME)$(CXXVERSION).lib /NOLOGO /IGNORE:4006 contrib-optlp-*.obj
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

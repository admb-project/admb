!IF DEFINED(DEBUG)
DESTDIR=..\build\debug
OBJDESTDIR=..\build\objects\debug
!ELSE
DESTDIR=..\build\dist
OBJDESTDIR=..\build\objects\dist
!ENDIf
all:
	$(MAKE) contrib-includes
	$(MAKE) contrib-libs
	$(MAKE) contrib-ad2csv
	
shared:
	IF EXIST $(DESTDIR)\lib\admb-contrib.dll del $(DESTDIR)\lib\admb-contrib.dll
	pushd $(OBJDESTDIR)& link /DLL /OUT:..\..\$(DESTDIR)\lib\admb-contrib.dll /NOLOGO /IGNORE:4006 ..\..\$(DESTDIR)\lib\admb.lib contrib-saflp-*.obj
!IFNDEF SAFE_ONLY
	IF EXIST $(DESTDIR)\lib\admb-contribo.dll del $(DESTDIR)\lib\admb-contribo.dll
	pushd $(OBJDESTDIR)& link /DLL /OUT:..\..\$(DESTDIR)\lib\admb-contribo.dll /NOLOGO /IGNORE:4006 ..\..\$(DESTDIR)\lib\admbo.lib contrib-optlp-*.obj
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
	IF EXIST $(DESTDIR)\lib\admb-contrib.lib del $(DESTDIR)\lib\admb-contrib.lib
	copy $(DESTDIR)\lib\admb.lib $(DESTDIR)\lib\admb-contrib.lib
	pushd $(OBJDESTDIR)& lib ..\..\$(DESTDIR)\lib\admb-contrib.lib /NOLOGO /IGNORE:4006 contrib-saflp-*.obj
!IFNDEF SAFE_ONLY
	IF EXIST $(DESTDIR)\lib\admb-contribo.lib del $(DESTDIR)\lib\admb-contribo.lib
	copy $(DESTDIR)\lib\admbo.lib $(DESTDIR)\lib\admb-contribo.lib
	pushd $(OBJDESTDIR)& lib ..\..\$(DESTDIR)\lib\admb-contribo.lib /NOLOGO /IGNORE:4006 contrib-optlp-*.obj
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

DESTDIR=..\build\dist
OBJDESTDIR=..\build\objects\contrib
all:
	$(MAKE) contrib-includes
	$(MAKE) contrib-libs
	$(MAKE) contrib-ad2csv
	@echo ADMB contrib build completed.
	
shared: all
	IF EXIST $(DESTDIR)\contrib\lib\contrib.dll del $(DESTDIR)\contrib\lib\contrib.dll
	link /DLL /OUT:$(DESTDIR)\contrib\lib\contrib.dll /NOLOGO /IGNORE:4006 $(OBJDESTDIR)\saflp-contrib*.obj $(DESTDIR)\lib\admb.lib
	IF EXIST $(DESTDIR)\contrib\lib\contribo.dll del $(DESTDIR)\contrib\lib\contribo.dll
	link /DLL /OUT:$(DESTDIR)\contrib\lib\contribo.dll /NOLOGO /IGNORE:4006 $(OBJDESTDIR)\optlp-contrib*.obj $(DESTDIR)\lib\admbo.lib
	@echo ADMB contrib shared build completed.

contrib-includes: contrib-dirs
	pushd ecolib& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\contrib\include includes
	pushd gdbprintlib& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\contrib\include includes
	pushd qfclib& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\contrib\include includes
	pushd statslib& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\contrib\include includes
	pushd src& $(MAKE) CONTRIB_INCLUDE=..\$(DESTDIR)\contrib\include includes

contrib-dirs:
	IF NOT EXIST $(DESTDIR)\contrib md $(DESTDIR)\contrib
	IF NOT EXIST $(DESTDIR)\contrib\bin md $(DESTDIR)\contrib\bin
	IF NOT EXIST $(DESTDIR)\contrib\include md $(DESTDIR)\contrib\include
	IF NOT EXIST $(DESTDIR)\contrib\lib md $(DESTDIR)\contrib\lib
	IF NOT EXIST $(OBJDESTDIR) md $(OBJDESTDIR)

contrib-libs: contrib-ecolib contrib-gdbprintlib contrib-qfclib contrib-statslib contrib-src
	IF EXIST $(DESTDIR)\contrib\lib\contrib.lib del $(DESTDIR)\contrib\lib\contrib.lib
	lib /OUT:$(DESTDIR)\contrib\lib\contrib.lib /NOLOGO /IGNORE:4006 $(OBJDESTDIR)\saflp-contrib*.obj
	IF EXIST $(DESTDIR)\contrib\lib\contribo.lib del $(DESTDIR)\contrib\lib\contribo.lib
	lib /OUT:$(DESTDIR)\contrib\lib\contribo.lib /NOLOGO /IGNORE:4006 $(OBJDESTDIR)\optlp-contrib*.obj

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

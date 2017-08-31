ifeq ($(TERM),cygwin)
else
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL = cmd
  endif
endif

all:
	ide-components.bat
	ide-distribution.bat
	$(MAKE) admb-ide-116-win64.zip
	$(MAKE) admb-ide-116-win64.exe

admb-ide-116-win64.zip:
	ide-zipfile.bat

admb-ide-116-win64.exe:
	iscc ide-installer.iss

clean:
ifeq ($(SHELL),cmd)
	del admb-ide-116-win64.exe
	del admb-ide-116-win64.zip
	@if exist components rmdir /s /q components
	@if exist adistribution rmdir /s /q distribution
else
	$(RM) admb-ide-116-win64.exe
	$(RM) admb-ide-116-win64.zip
	$(RM) -r components
	$(RM) -r distribution
endif

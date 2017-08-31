ifeq ($(TERM),cygwin)
else
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL = cmd
  endif
endif

all:
ifeq ($(SHELL),cmd)
	ide-components.bat
	ide-distribution.bat
else
	./ide-components.bat
	./ide-distribution.bat
endif
	$(MAKE) admb-ide-116-win64.zip
	$(MAKE) admb-ide-116-win64.exe

admb-ide-116-win64.zip:
ifeq ($(SHELL),cmd)
	ide-zipfile.bat
else
	./ide-zipfile.bat
endif

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

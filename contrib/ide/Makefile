ifeq ($(TERM),cygwin)
else
ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
SHELL = cmd
endif
endif

all: clean

admb-ide.zip: clean
ifeq ($(SHELL),cmd)
	win64\admb-ide-build.bat
else
	win64/admb-ide-build.bat
endif

admb-ide.exe: clean
ifeq ($(SHELL),cmd)
	iscc win64\admb-ide-build.iss
else
	iscc win64/admb-ide-build.iss
endif

clean:
ifeq ($(SHELL),cmd)
	del win64\admb-ide.exe
	del admb-ide.zip
	@if exist admb-ide rmdir /s /q admb-ide
else
	$(RM) win64/admb-ide.exe
	$(RM) admb-ide.zip
	$(RM) -r admb-ide
endif

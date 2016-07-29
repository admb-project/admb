ifeq ($(TERM),cygwin)
else
ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
SHELL = cmd
endif
endif

all:
	$(MAKE) clean
	$(MAKE) admb-ide.zip

admb-ide.zip:
ifeq ($(SHELL),cmd)
	win64\admb-ide-build.bat
else
	win64/admb-ide-build.bat
endif

clean:
	$(RM) admb-ide.zip
	$(RM) admb-ide.exe
	$(RM) -r admb-ide

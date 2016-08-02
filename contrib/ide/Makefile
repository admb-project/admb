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
	$(RM) admb-ide.zip
ifeq ($(SHELL),cmd)
	$(RM) win64\admb-ide.exe
else
	$(RM) win64/admb-ide.exe
endif
	$(RM) -r admb-ide

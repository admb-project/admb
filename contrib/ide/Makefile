ifeq ($(TERM),cygwin)
else
ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
SHELL = cmd
endif
endif

all: admb-ide.zip

admb-ide.zip:
ifeq ($(SHELL),cmd)
	win64\admb-ide-build.bat
else
	win64/admb-ide-build.bat
endif

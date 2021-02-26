ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring sh.exe,$(shell where sh.exe 2>&1 | findstr sh.exe)),sh.exe)
      EXT=.sh
    else
      SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
endif

all: clean
	$(MAKE) dirs
ifeq ($(CMDSHELL),cmd)
	pushd src & ..\\..\\..\\admb -o ..\\bin\\simple.exe simple.tpl
	pushd run & ..\\src\\simple.exe
else
	cd src && ../../../admb$(EXT) -o ../bin/simple simple.tpl
	cd run && ../bin/simple
endif

dirs:
ifeq ($(CMDSHELL),cmd)
	md run
	md src
	md bin
else
	mkdir run
	mkdir src
	mkdir bin
endif
	$(MAKE) simple.dat simple.tpl

simple.dat:
ifeq ($(CMDSHELL),cmd)
	copy ..\..\examples\admb\simple\simple.dat run
else
	cp ../../examples/admb/simple/simple.dat run 
endif

simple.tpl:
ifeq ($(CMDSHELL),cmd)
	copy ..\..\examples\admb\simple\simple.tpl src
else
	cp ../../examples/admb/simple/simple.tpl src
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@if exist bin rmdir /S /Q bin
	@if exist src rmdir /S /Q src
	@if exist run rmdir /S /Q run
else
	@rm -rvf bin src run
endif

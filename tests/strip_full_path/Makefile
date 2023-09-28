all: clean
	$(MAKE) dirs
	pushd src & ..\\..\\..\\admb -o ..\\bin\\simple.exe simple.tpl
	pushd run & ..\\bin\\simple.exe

dirs:
	md run
	md src
	md bin
	$(MAKE) simple.dat simple.tpl

simple.dat:
	copy ..\..\examples\admb\simple\simple.dat run

simple.tpl:
	copy ..\..\examples\admb\simple\simple.tpl src

clean:
	@if exist bin rmdir /S /Q bin
	@if exist src rmdir /S /Q src
	@if exist run rmdir /S /Q run

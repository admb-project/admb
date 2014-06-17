all:

clean:
ifeq ($(OS),Windows_NT)
	$(MAKE) --file=Makefile
else
	@rm -rvf installers/packagemaker/ADMBTerminal.dmg
	@rm -rvf installers/packagemaker/build
endif

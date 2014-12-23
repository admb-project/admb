all:

clean:
ifeq ($(OS),Windows_NT)
	$(MAKE) --file=Makefile clean
else
	@rm -vf installers/packagemaker/ADMBTerminal.dmg
	@rm -rvf installers/packagemaker/build
	$(MAKE) --directory=installers/dpkg clean
endif

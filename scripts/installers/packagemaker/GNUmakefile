ifndef ADMB_VER
  ADMB_VER=admb
endif

CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker

all: clean
	$(MAKE) ../../../$(ADMB_VER)-macos.dmg

../../../$(ADMB_VER)-macos.dmg: build/ADMBTerminal.app
	cp -vf QuickStartMacOS.md build/INSTALL.txt
	cp -rvf ../../../build/$(ADMB_VER) build/ADMBTerminal.app/
	pushd build && ln -sf ADMBTerminal.app/$(ADMB_VER)/README.txt README.txt && popd
	pushd build && ln -sf ADMBTerminal.app/$(ADMB_VER)/LICENSE.txt LICENSE.txt && popd
	pushd build && ln -sf ADMBTerminal.app/$(ADMB_VER)/CHANGES.txt CHANGES.txt && popd
	cp -rvf ../../../examples build/
	hdiutil create $@ -volname "ADMBTerminal" -srcfolder build -ov -debug

build/ADMBTerminal.app: ADMBTerminal.scpt
	mkdir -p build
	osacompile -o $@ $^
	cp -vf applet.icns build/ADMBTerminal.app/Contents/Resources

build/ADMBTerminal.pkg:
	$(CC) --verbose --title "ADMBTerminal" --root build --id www.admb-project.org --resources build/ADMBTerminal.app/Contents/Resources --out $@

clean:
	rm -rvf build
	rm -rvf $(ADMB_VER)-macos.dmg

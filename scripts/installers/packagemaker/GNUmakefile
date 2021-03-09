ifndef ADMB_VER
  ADMB_VER=admb
endif

CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker
BUILD_DIR=../../../build

all: clean
	$(MAKE) $(BUILD_DIR)/$(ADMB_VER)-macos.dmg

$(BUILD_DIR)/$(ADMB_VER)-macos.dmg: $(BUILD_DIR)/ADMBTerminal.app
	mkdir -p build
	cp -vf QuickStartMacOS.md build/INSTALL.txt
	cp -rvf ../../../build/$(ADMB_VER) build/ADMBTerminal.app/
	pushd build && ln -sf ADMBTerminal.app/$(ADMB_VER)/README.txt README.txt && popd
	pushd build && ln -sf ADMBTerminal.app/$(ADMB_VER)/LICENSE.txt LICENSE.txt && popd
	pushd build && ln -sf ADMBTerminal.app/$(ADMB_VER)/CHANGES.txt CHANGES.txt && popd
	cp -rvf ../../../examples build/
	hdiutil create $@ -volname "ADMBTerminal" -srcfolder build -ov -debug

../../../build/ADMBTerminal.app: ADMBTerminal.scpt
	osacompile -o $@ $^
	cp -vf applet.icns $@/Contents/Resources

build/ADMBTerminal.pkg:
	$(CC) --verbose --title "ADMBTerminal" --root build --id www.admb-project.org --resources build/ADMBTerminal.app/Contents/Resources --out $@

clean:
	rm -rvf build
	rm -rvf $(ADMB_VER)-macos.dmg

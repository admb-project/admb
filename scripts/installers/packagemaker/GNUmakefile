ifndef ADMB_VER
  ADMB_VER=admb
endif

CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker
BUILD_DIR=../../../build

all: clean
	mkdir -p $(BUILD_DIR)/dmg
	$(MAKE) $(BUILD_DIR)/$(ADMB_VER)-macos.dmg

$(BUILD_DIR)/$(ADMB_VER)-macos.dmg: $(BUILD_DIR)/dmg/ADMBTerminal.app
	cp -vf QuickStartMacOS.md $(BUILD_DIR)/dmg/INSTALL.txt
	cp -rvf ../../../build/$(ADMB_VER) $(BUILD_DIR)/dmg/ADMBTerminal.app/
	pushd $(BUILD_DIR)/dmg && ln -sf ADMBTerminal.app/$(ADMB_VER)/README.txt README.txt && popd
	pushd $(BUILD_DIR)/dmg && ln -sf ADMBTerminal.app/$(ADMB_VER)/LICENSE.txt LICENSE.txt && popd
	pushd $(BUILD_DIR)/dmg && ln -sf ADMBTerminal.app/$(ADMB_VER)/CHANGES.txt CHANGES.txt && popd
	cp -rvf ../../../examples $(BUILD_DIR)
	hdiutil create $@ -volname "ADMBTerminal" -srcfolder $(BUILD_DIR)/dmg -ov -debug

$(BUILD_DIR)/dmg/ADMBTerminal.app: ADMBTerminal.scpt
	osacompile -o $@ $^
	cp -vf applet.icns $@/Contents/Resources

clean:
	rm -rvf $(BUILD_DIR)/dmg
	rm -rvf $(BUILD_DIR)/$(ADMB_VER)-macos.dmg

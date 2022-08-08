ifdef USE_ADMB_VER
  ADMB_VER=-13.0
endif

CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker
BUILD_DIR=../../../build

all: clean
	mkdir -p $(BUILD_DIR)/dmg
	$(MAKE) $(BUILD_DIR)/admb$(ADMB_VER)-macos.dmg

$(BUILD_DIR)/admb$(ADMB_VER)-macos.dmg: $(BUILD_DIR)/dmg/ADMB$(ADMB_VER)-Terminal.app
	cp -vf QuickStartMacOS.md $(BUILD_DIR)/dmg/INSTALL.txt
	cp -rvf ../../../build/admb $(BUILD_DIR)/dmg/ADMB$(ADMB_VER)-Terminal.app/admb$(ADMB_VER)
	rm  -rvf $(BUILD_DIR)/dmg/ADMB$(ADMB_VER)-Terminal.app/admb$(ADMB_VER)/examples
	pushd $(BUILD_DIR)/dmg && ln -sf ADMB$(ADMB_VER)-Terminal.app/admb$(ADMB_VER)/README.txt README.txt && popd
	pushd $(BUILD_DIR)/dmg && ln -sf ADMB$(ADMB_VER)-Terminal.app/admb$(ADMB_VER)/LICENSE.txt LICENSE.txt && popd
	pushd $(BUILD_DIR)/dmg && ln -sf ADMB$(ADMB_VER)-Terminal.app/admb$(ADMB_VER)/CHANGES.txt CHANGES.txt && popd
	cp -rvf ../../../examples $(BUILD_DIR)
	hdiutil create $@ -volname "ADMBTerminal" -srcfolder $(BUILD_DIR)/dmg -ov -debug

$(BUILD_DIR)/dmg/ADMB$(ADMB_VER)-Terminal.app: ADMBTerminal.scpt
	osacompile -o $@ $^
	cp -vf applet.icns $@/Contents/Resources

clean:
	rm -rvf $(BUILD_DIR)/dmg
	rm -rvf $(BUILD_DIR)/admb$(ADMB_VER)-macos.dmg

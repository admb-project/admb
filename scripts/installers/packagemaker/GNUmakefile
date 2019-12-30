CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker

all:
	$(MAKE) clean
	$(MAKE) ADMBTerminal.dmg

ADMBTerminal.dmg: build/ADMBTerminal.app
	cp -vf QuickStartADMBTerminal.md build/README.txt
	cp -rvf ../../../build/admb build/ADMBTerminal.app/admb
	cp -rvf ../../../examples build
	hdiutil create $@ -volname "ADMBTerminal" -srcfolder build -ov -debug

build/ADMBTerminal.app: ADMBTerminal.scpt
	mkdir -p build
	osacompile -o $@ $^
	cp -vf applet.icns build/ADMBTerminal.app/Contents/Resources

build/ADMBTerminal.pkg:
	$(CC) --verbose --title "ADMBTerminal" --root build --id www.admb-project.org --resources build/ADMBTerminal.app/Contents/Resources --out $@

clean:
	rm -rvf build
	rm -rvf ADMBTerminal.dmg

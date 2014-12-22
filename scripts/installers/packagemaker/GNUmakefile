CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker

all:
	$(MAKE) clean
	$(MAKE) ADMBTerminal.dmg

ADMBTerminal.dmg: build/ADMBTerminal.app
	cp -vf README.txt build
	cp -rvf ../../../build/dist build/ADMBTerminal.app/admb
	touch build/.Trash
	hdiutil create $@ -volname "ADMBTerminal" -srcfolder build -ov -debug

build/ADMBTerminal.app: ADMBTerminal.scpt
	mkdir -p build
	osacompile -o $@ $^

build/ADMBTerminal.pkg:
	$(CC) --verbose --title "ADMBTerminal" --root build --id www.admb-project.org --resources build/ADMBTerminal.app/Contents/Resources --out $@

clean:
	rm -rvf rawADMBTerminal.dmg
	rm -rvf build
	rm -rvf ADMBTerminal.dmg

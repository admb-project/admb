CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker

all: ADMBTerminal.dmg

build/ADMBTerminal.app/Contents/admb:
	mkdir -p build/ADMBTerminal.app/
	cp -Rvf ADMBTerminal.app/Contents build/ADMBTerminal.app/
	cp -Rvf ../../../build/dist $@

build/ADMBTerminal.pkg:
	$(CC) --verbose --title "ADMBTerminal" --root build --id www.admb-project.org --resources build/ADMBTerminal.app/Contents/Resources --out $@

build/examples/simple:
	mkdir -p $@
	cp -vf build/ADMBTerminal.app/Contents/admb/examples/admb/simple/simple.dat build/examples/simple/
	cp -vf build/ADMBTerminal.app/Contents/admb/examples/admb/simple/simple.tpl build/examples/simple/

ADMBTerminal.dmg: build/ADMBTerminal.app/Contents/admb build/examples/simple
	hdiutil create $@ -volname "ADMBTerminal" -srcfolder build/

clean:
	rm -rvf build
	rm -vf ADMBTerminal.dmg

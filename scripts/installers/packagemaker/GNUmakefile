CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker

all: ADMBTerminal.dmg

ADMBTerminal.dmg: build/ADMBTerminal.app/Contents/Resources/Scripts/main.scpt
	cp -vf README.txt build
	rm -vf raw$@
	hdiutil create raw$@ -volname "ADMBTerminal" -srcfolder build/
	rm -vf $@
	hdiutil convert raw$@ -format UDBZ -o $@

build/ADMBTerminal.app/Contents/Resources/Scripts/main.scpt: build/ADMBTerminal.app/Contents
	mkdir -p build/ADMBTerminal.app/Contents/Resources/Scripts
	osacompile -o $@ main.scpt

build/ADMBTerminal.app/Contents:
	mkdir -p build
	cp -Rvf ../../../build/dist build/ADMBTerminal.app
	cp -Rvf Contents build/ADMBTerminal.app

build/ADMBTerminal.pkg:
	$(CC) --verbose --title "ADMBTerminal" --root build --id www.admb-project.org --resources build/ADMBTerminal.app/Contents/Resources --out $@

build/examples/simple:
	mkdir -p $@
	cp -vf build/ADMBTerminal.app/Contents/admb/examples/admb/simple/simple.dat build/examples/simple/
	cp -vf build/ADMBTerminal.app/Contents/admb/examples/admb/simple/simple.tpl build/examples/simple/


clean:
	rm -rvf build/ADMBTerminal.app
	rm -rvf build
	rm -vf ADMBTerminal.dmg

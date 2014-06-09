CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker

all: ADMBTerminal.dmg

ADMBTerminal.dmg: build/ADMBTerminal.app
	cp -vf README.txt build
	cp -rvf ../../../build/dist build/ADMBTerminal.app/admb
	rm -vf raw$@
	hdiutil create build/raw$@ -volname "ADMBTerminal" -srcfolder build/
	rm -vf $@
	hdiutil convert build/raw$@ -format UDBZ -o $@

build/ADMBTerminal.app:
	mkdir -p build
	osacompile -o $@ ADMBTerminal.scpt

build/ADMBTerminal.pkg:
	$(CC) --verbose --title "ADMBTerminal" --root build --id www.admb-project.org --resources build/ADMBTerminal.app/Contents/Resources --out $@

clean:
	rm -rvf build/rawADMBTerminal.dmg
	rm -rvf build
	rm -rvf ADMBTerminal.dmg

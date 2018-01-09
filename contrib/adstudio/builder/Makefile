all:
	ide-components.bat
	ide-distribution.bat
	$(MAKE) admb-ide-116-win64.zip
	$(MAKE) admb-ide-116-win64.exe

admb-ide-116-win64.zip:
	ide-zipfile.bat

admb-ide-116-win64.exe:
	iscc ide-installer.iss

clean:
	@del admb-ide-116-win64.exe
	@del admb-ide-116-win64.zip
	@if exist components rmdir /s /q components
	@if exist adistribution rmdir /s /q distribution

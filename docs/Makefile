all: _api _manuals installs

_api:
	$(MAKE) --directory=api

_manuals:
	$(MAKE) --directory=manuals

installs:
	$(MAKE) --directory=install

copy:
ifeq ($(SHELL),sh.exe)
	if not exist $(DIST)\docs md $(DIST)\docs
	xcopy ..\docs $(DIST)\docs /S /Y /D
else
	cp -R ../docs ${DIST} 
endif

clean:
	$(MAKE) --directory=install clean

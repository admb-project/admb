all: api

api:
	$(MAKE) --directory=api

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

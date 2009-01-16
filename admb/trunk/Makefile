VERSION=`cat VERSION.txt`

all: admb-windows-setup

dists:
	cd build/dists; ../../scripts/dists/make-dist.sh
	$(INNOSETUP_HOME)/iscc scripts\admb-win32-setup\admb-win32-setup.iss

admb-windows-setup:
	@echo $(VERSION)
	$(INNOSETUP_HOME)/iscc scripts\admb-windows-setup\admb-windows-setup.iss
	mv build/admb-windows-setup.exe build/admb-$(VERSION).exe

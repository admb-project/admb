VERSION=11.6pre

all:
	$(MAKE) clean
	$(MAKE) admb_$(VERSION).deb

check:
	lintian -v -i admb_$(VERSION).deb

admb_$(VERSION).deb: admb_$(VERSION)
	dpkg-deb --build $^

admb_$(VERSION): control
	mkdir --mode=755 -p $@/usr/local/bin
	cp -Rvf ../../../build/dist $@/usr/local/admb
	cd $@/usr/local/bin; ln -sf ../admb/bin/admb admb; cd ..
	ls -al $@/usr/local/bin/*
	mkdir --mode=755 -p $@/DEBIAN
	cp -pvf control $@/DEBIAN

clean:
	rm -rvf admb_$(VERSION)*

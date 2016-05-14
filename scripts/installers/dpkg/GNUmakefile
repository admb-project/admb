VERSION=11.5

all:
	$(MAKE) clean
	$(MAKE) admb_$(VERSION).deb

check:
	lintian -v -i admb_$(VERSION).deb

admb_$(VERSION).deb: admb_$(VERSION)
	dpkg-deb --build $^

admb_$(VERSION): control
	mkdir -p $@/usr/local/bin
	cp -Rvf ../../../build/dist $@/usr/local/admb
	cd $@/usr/local/bin; ln -sf ../admb/bin/admb admb; cd ..
	ls -al $@/usr/local/bin/*
	mkdir -p $@/DEBIAN
	cp -pvf control $@/DEBIAN

clean:
	rm -rvf admb_$(VERSION)*

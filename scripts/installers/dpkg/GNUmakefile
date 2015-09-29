VERSION=11.4

all:
	$(MAKE) clean
	$(MAKE) admb_$(VERSION).deb
	lintian -v -i admb_$(VERSION).deb


admb_$(VERSION).deb: admb_$(VERSION)
	dpkg-deb --build $^

admb_$(VERSION): control
	mkdir -p $@/usr/local/bin
	cp -Rvf ../../../build/dist $@/usr/local/admb
	cd $@/usr/local/bin; ln -sf ../admb/bin/admb admb; cd ..
	ls -al $@/usr/local/bin/*
	mkdir -p $@/DEBIAN
	cp -vf control $@/DEBIAN

clean:
	rm -rvf admb_$(VERSION)*

all:
	$(MAKE) clean
	$(MAKE) admb_11.2.deb

admb_11.2.deb: admb_11.2
	dpkg-deb --build $^

admb_11.2: control
	mkdir -p $@/usr/local/bin
	cp -Rvf ../../../build/dist $@/usr/local/admb
	cd $@/usr/local/bin; ln -sf ../admb/bin/admb admb; cd ..
	ls -al $@/usr/local/bin/*
	mkdir -p $@/DEBIAN
	cp -vf control $@/DEBIAN

clean:
	rm -rvf admb_11.2
	rm -rvf admb_11.2.deb

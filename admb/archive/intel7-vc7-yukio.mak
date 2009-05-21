all:
	cd linad99; MAKE -f optintel7-vc7-yukio.mak  all
	cd linad99; MAKE -f safintel7-vc7-yukio.mak  all

clean:
	cd linad99; MAKE -f optintel7-vc7-yukio.mak  clean
	cd linad99; MAKE -f safintel7-vc7-yukio.mak   clean
	cd tools99; MAKE -f intel7-vc71-yukio.mak  clean

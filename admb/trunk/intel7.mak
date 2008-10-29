all:
	cd linad99; MAKE -f optintel7.mak  all
	cd linad99; MAKE -f safintel7.mak  all
	cd tools99; MAKE -f intel7.mak  all
	cd nh99; MAKE -f intel7.mak  all

clean:
	cd linad99; MAKE -f optintel7.mak  clean
	cd linad99; MAKE -f safintel7.mak   clean
	cd tools99; MAKE -f intel7.mak   clean
	cd nh99; MAKE -f intel7.mak   clean

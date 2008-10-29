all:
	cd linad99; MAKE -f optintel7-vc7.mak   all
	cd linad99; MAKE -f safintel7-vc7.mak   all
	cd tools99; MAKE -f intel7-vc71.mak   all
	cd nh99; MAKE -f intel7-vc71.mak   all

demo:
	cd linad99; MAKE -f optintel7-vc7.mak  demo=1 all
	cd linad99; MAKE -f safintel7-vc7.mak  demo=1 all
	cd tools99; MAKE -f intel7-vc71.mak  demo=1 all
	cd nh99; MAKE -f intel7-vc71.mak  demo=1 all

clean:
	cd linad99; MAKE -f optintel7-vc7.mak  clean
	cd linad99; MAKE -f safintel7-vc7.mak   clean
	cd tools99; MAKE -f intel7-vc71.mak   clean
	cd nh99; MAKE -f intel7-vc71.mak   clean

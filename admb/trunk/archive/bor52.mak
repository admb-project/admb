
all:
	cd linad99; MAKE -f optbor52.mak 
	cd linad99; MAKE -f safbor52.mak 
	cd tools99; MAKE -f optbor52.mak 
	cd nh99; MAKE -f optbor52.mak 

clean:
	cd linad99; MAKE -f optbor52.mak  clean
	cd linad99; MAKE -f safbor52.mak   clean
	cd tools99; MAKE -f optbor52.mak   clean
	cd nh99; MAKE -f optbor52.mak   clean

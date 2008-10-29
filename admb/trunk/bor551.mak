all:
	cd linad99; MAKE -f optbor55.mak 
	cd linad99; MAKE -f safbor55.mak 
	cd tools99; MAKE -f optbor55.mak 
	cd nh99; MAKE -f optbor55.mak 

clean:
	cd linad99; MAKE -f optbor55.mak  clean
	cd linad99; MAKE -f safbor55.mak   clean
	cd tools99; MAKE -f optbor55.mak   clean
	cd nh99; MAKE -f optbor55.mak   clean

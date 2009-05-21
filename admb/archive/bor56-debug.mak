
#	cd nh99; MAKE "OPTIONS = -v -vG -DUSE_ADPVM" -f optbor56.mak 

all:
	cd linad99; MAKE "OPTIONS = -v -vG -DUSE_ADPVM"  -f optbor56.mak 
	cd linad99; MAKE "OPTIONS = -v -vG -DUSE_ADPVM"  -f safbor56.mak 
	cd tools99; MAKE "OPTIONS = -v -vG -DUSE_ADPVM"  -f optbor56.mak 

clean:
	cd linad99; MAKE -f optbor56.mak  clean
	cd linad99; MAKE -f safbor56.mak   clean
	cd tools99; MAKE -f optbor56.mak   clean
	cd nh99; MAKE -f optbor56.mak   clean

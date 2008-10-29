
	
all:
	cd linad99; MAKE -f optbor56-laplace.mak 
	cd linad99; MAKE -f safbor56-laplace.mak 
	cd df1b2-separable; MAKE -f safbor56-laplace.mak 
	cd df1b2-separable; MAKE -f optbor56-laplace.mak 
	cd tools99; MAKE -f optbor56-laplace.mak 
	cd nh99; MAKE -f optbor56-laplace.mak 

clean:
	cd linad99; MAKE -f optbor56-laplace.mak  clean
	cd linad99; MAKE -f safbor56-laplace.mak   clean
	cd df1b2-separable; MAKE -f safbor56-laplace.mak   clean
	cd df1b2-separable; MAKE -f optbor56-laplace.mak   clean
	cd tools99; MAKE -f optbor56-laplace.mak   clean
	cd nh99; MAKE -f optbor56-laplace.mak   clean

debug:
	cd linad99; MAKE "OPTIONS = -v -vG" -f optbor56-laplace.mak 
	cd linad99; MAKE "OPTIONS = -v -vG" -f safbor56-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS = -v -vG" -f safbor56-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS = -v -vG" -f optbor56-laplace.mak 
	cd tools99; MAKE "OPTIONS = -v -vG" -f optbor56-laplace.mak 
	cd nh99; MAKE "OPTIONS = -v -vG" -f optbor56-laplace.mak 


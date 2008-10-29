
all:
	cd linad99; MAKE -f optcyg-laplace.mak 
	- cd linad99; MAKE -f safcyg-laplace.mak 
	- cd df1b2-separable; MAKE -f safcyg-laplace.mak 
	cd df1b2-separable; MAKE -f optcyg-laplace.mak 
	cd tools99; MAKE -f optcyg-laplace.mak 
	cd nh99; MAKE -f optcyg-laplace.mak 

clean:
	cd linad99; MAKE -f optcyg-laplace.mak  clean
	- cd linad99; MAKE -f safcyg-laplace.mak   clean
	- cd df1b2-separable; MAKE -f safcyg-laplace.mak   clean
	cd df1b2-separable; MAKE -f optcyg-laplace.mak   clean
	cd tools99; MAKE -f optcyg-laplace.mak   clean
	cd nh99; MAKE -f optcyg-laplace.mak   clean

DISKDIR= f:/borland-52-laplace

all:
	cd df1b2-separable; MAKE -f optbor52-laplace.mak 
	cd df1b2-separable; MAKE -f safbor52-laplace.mak 
	cd linad99; MAKE -f optbor52-laplace.mak 
	cd linad99; MAKE -f safbor52-laplace.mak 
	cd tools99; MAKE -f optbor52-laplace.mak 
	cd nh99; MAKE -f optbor52-laplace.mak 

clean:
	cd linad99; MAKE -f optbor52-laplace.mak  clean
	cd linad99; MAKE -f safbor52-laplace.mak   clean
	cd tools99; MAKE -f optbor52-laplace.mak   clean
	cd nh99; MAKE -f optbor52-laplace.mak   clean
	cd df1b2-separable; MAKE -f optbor52-laplace.mak clean
	cd df1b2-separable; MAKE -f safbor52-laplace.mak clean

hanscopy:
	- cd $(DISKDIR) ; rm ad_build.zip ; \
        cfind . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/real-experimental/borland-52


DISKDIR= j:/borland-551-laplace

all:
	cd linad99; MAKE  -f optbor55-laplace.mak 
	cd linad99; MAKE  -f safbor55-laplace.mak 
	cd df1b2-separable; MAKE  -f safbor55-laplace.mak 
	cd df1b2-separable; MAKE  -f optbor55-laplace.mak 
	cd tools99; MAKE  -f optbor55-laplace.mak 
	cd nh99; MAKE  -f optbor55-laplace.mak 

debug:
	cd linad99; MAKE "OPTIONS= -v" -f optbor55-laplace.mak 
	cd linad99; MAKE "OPTIONS= -v" -f safbor55-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS= -v" -f safbor55-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS= -v" -f optbor55-laplace.mak 
	cd tools99; MAKE "OPTIONS= -v" -f optbor55-laplace.mak 
	cd nh99; MAKE "OPTIONS= -v" -f optbor55-laplace.mak 


clean:
	cd linad99; MAKE -f optbor55-laplace.mak  clean
	cd linad99; MAKE -f safbor55-laplace.mak   clean
	cd df1b2-separable; MAKE -f safbor55-laplace.mak   clean
	cd df1b2-separable; MAKE -f optbor55-laplace.mak   clean
	cd tools99; MAKE -f optbor55-laplace.mak   clean
	cd nh99; MAKE -f optbor55-laplace.mak   clean

redemoall:
	cd linad99; MAKE "OPTIONS= -DADMB_REDEMO  "  -f optbor55-laplace.mak 
	cd linad99; MAKE "OPTIONS= -DADMB_REDEMO  "  -f safbor55-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS= -DADMB_REDEMO  " -f safbor55-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS= -DADMB_REDEMO  "  -f optbor55-laplace.mak 
	cd tools99; MAKE "OPTIONS= -DADMB_REDEMO  " -f optbor55-laplace.mak 
	cd nh99; MAKE "OPTIONS= -DADMB_REDEMO  "  -f optbor55-laplace.mak 


hanscopy:
	- cd $(DISKDIR) ; rm ad_build.exe ; rm *.zip ; \
        cfind . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/real-experimental/borland-55


redemonh99:
	cd nh99; MAKE "OPTIONS= -DADMB_REDEMO "  -f optbor55-laplace.mak 

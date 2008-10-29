DISKDIR= j:/borland-50-laplace
all:
	cd linad99; MAKE -f optbor32.mak  all
	cd linad99; MAKE  -f safbor32.mak  all
	cd tools99; MAKE  -f optbor32.mak 
	cd nh99; MAKE -f optbor32.mak 

demoall:
	cd linad99; MAKE "OPTIONS=-DADMB_REDEMO" -f optbor32.mak  all
	cd linad99; MAKE "OPTIONS=-DADMB_REDEMO" -f safbor32.mak  all
	cd tools99; MAKE "OPTIONS=-DADMB_REDEMO" -f optbor32.mak 
	cd nh99; MAKE "OPTIONS=-DADMB_REDEMO" -f optbor32.mak 


clean:
	cd linad99; MAKE -f optbor32.mak  clean
	cd linad99; MAKE -f safbor32.mak   clean
	cd tools99; MAKE -f optbor32.mak   clean
	cd nh99; MAKE -f optbor32.mak   clean

pvmall:
	cd newdoubledouble; MAKE OPTIONS=-DUSE_ADPVM -f optbor32.mak 
	cd linad99; MAKE OPTIONS=-DUSE_ADPVM -f optbor32.mak  all
	cd linad99; MAKE OPTIONS=-DUSE_ADPVM -f safbor32.mak  all
	cd tools99; MAKE OPTIONS=-DUSE_ADPVM -f optbor32.mak 
	cd nh99; MAKE OPTIONS=-DUSE_ADPVM -f optbor32.mak 


hanscopy:
	- cd $(DISKDIR) ; rm ad_build.zip ; \
        find . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/borland-50
	

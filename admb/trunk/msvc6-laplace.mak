


CMD=bash

DEMODISKDIR=f:/adms6lp-demo.m32 

DISKDIR= j:/adms6lp.m32 
 

all:
	cd nh99; MAKE  DISKDIR=j:/adms6lp.m32 -f optmsc6-laplace.mak  all
	cd linad99; MAKE  DISKDIR=j:/adms6lp.m32 -f optmsc6-laplace.mak  all
	cd linad99; MAKE  DISKDIR=j:/adms6lp.m32 -f safmsc6-laplace.mak  all
	cd tools99; MAKE  DISKDIR=j:/adms6lp.m32 -f optmsc6-laplace.mak  all
	cd df1b2-separable; MAKE  DISKDIR=j:/adms6lp.m32 -f optmsc6-laplace.mak  all
	cd df1b2-separable; MAKE  DISKDIR=j:/adms6lp.m32 -f safmsc6-laplace.mak  all

pvmall:
	
	cd linad99; MAKE PVMOPTION=-DUSE_ADPVM  DISKDIR=j:/adms6lp.m32 -f optmsc6-laplace.mak  all
	cd linad99; MAKE PVMOPTION=-DUSE_ADPVM DISKDIR=j:/adms6lp.m32 -f safmsc6-laplace.mak  all
	cd tools99; MAKE PVMOPTION=-DUSE_ADPVM DISKDIR=j:/adms6lp.m32 -f optmsc6-laplace.mak  all
	cd df1b2-separable; MAKE PVMOPTION=-DUSE_ADPVM DISKDIR=j:/adms6lp.m32 -f optmsc6-laplace.mak  all
	cd df1b2-separable; MAKE PVMOPTION=-DUSE_ADPVM DISKDIR=j:/adms6lp.m32 -f safmsc6-laplace.mak  all
	cd nh99; MAKE PVMOPTION=-DUSE_ADPVM DISKDIR=j:/adms6lp.m32 -f optmsc6-laplace.mak  all

clean:
	cd df1b2-separable; MAKE -f optmsc6-laplace.mak clean 
	cd df1b2-separable; MAKE -f safmsc6-laplace.mak clean 
	cd linad99; MAKE -f optmsc6-laplace.mak  clean
	cd linad99; MAKE -f safmsc6-laplace.mak   clean
	cd tools99; MAKE -f optmsc6-laplace.mak   clean
	cd nh99; MAKE -f optmsc6-laplace.mak   clean
netdemo:
	cd nh99; MAKE LIBPATH=msc6olp-demo PVMOPTION=-DADMB_REDEMO DISKDIR=f:/adms6lp-demo.m32 -f optmsc6-laplace.mak  all

	cd linad99; MAKE LIBPATH=msc6olp-demo PVMOPTION=-DADMB_REDEMO DISKDIR=f:/adms6lp-demo.m32 -f optmsc6-laplace.mak  all
	cd linad99; MAKE LIBPATH=msc6slp-demo PVMOPTION=-DADMB_REDEMO DISKDIR=f:/adms6lp-demo.m32 -f safmsc6-laplace.mak  all
	cd tools99; MAKE LIBPATH=msc6olp-demo PVMOPTION=-DADMB_REDEMO DISKDIR=f:/adms6lp-demo.m32 -f optmsc6-laplace.mak  all
	cd df1b2-separable; MAKE LIBPATH=msc6olp-demo PVMOPTION=-DADMB_REDEMO DISKDIR=f:/adms6lp-demo.m32 -f optmsc6-laplace.mak  all
	cd df1b2-separable; MAKE LIBPATH=msc6slp-demo PVMOPTION=-DADMB_REDEMO DISKDIR=f:/adms6lp-demo.m32 -f safmsc6-laplace.mak  all


hanscopy:
	- cd $(DISKDIR) ; rm ad_build.zip ; \
        cfind . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/real-experimental/msvc6

hansdemocopy:
	- cd $(DEMODISKDIR) ; rm ad_build.zip ; \
        cfind . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/experimental/msvc6-demo


democlean:
	cd df1b2-separable; MAKE LIBPATH=msc6olp-demo -f optmsc6-laplace.mak clean 
	cd df1b2-separable; MAKE LIBPATH=msc6slp-demo -f safmsc6-laplace.mak clean 
	cd linad99; MAKE LIBPATH=msc6olp-demo -f optmsc6-laplace.mak  clean
	cd linad99; MAKE LIBPATH=msc6slp-demo -f safmsc6-laplace.mak   clean
	cd tools99; MAKE LIBPATH=msc6olp-demo -f optmsc6-laplace.mak   clean
	cd nh99; MAKE LIBPATH=msc6olp-demo -f optmsc6-laplace.mak   clean

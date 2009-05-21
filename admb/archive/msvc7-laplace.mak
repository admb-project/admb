

DISKDIR= g:/adms7lp.m32

all:
	cd linad99; MAKE -f safmsc7-laplace.mak  all
	cd linad99; MAKE -f optmsc7-laplace.mak  all
	cd nh99; MAKE -f safmsc7-laplace.mak  all
	cd nh99; MAKE -f optmsc7-laplace.mak  all
	cd tools99; MAKE -f safmsc7-laplace.mak  all
	cd tools99; MAKE -f optmsc7-laplace.mak  all
	cd df1b2-separable; MAKE -f optmsc7-laplace.mak  all
	cd df1b2-separable; MAKE -f safmsc7-laplace.mak  all

pvmall:
	
	cd linad99; MAKE DISKDIR=j:/adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc7-laplace.mak  all
	cd linad99; MAKE DISKDIR=j:/adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc7-laplace.mak  all
	cd tools99; MAKE DISKDIR=j:/adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc7-laplace.mak  all
	cd tools99; MAKE DISKDIR=j:/adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc7-laplace.mak  all
	cd df1b2-separable; MAKE DISKDIR=j:/adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc7-laplace.mak  all
	cd df1b2-separable; MAKE DISKDIR=j:/adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc7-laplace.mak  all
	cd nh99; MAKE DISKDIR=j:/adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc7-laplace.mak  all
	cd nh99; MAKE DISKDIR=j:/adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc7-laplace.mak  all

clean:
	cd df1b2-separable; MAKE -f optmsc7-laplace.mak clean 
	cd df1b2-separable; MAKE -f safmsc7-laplace.mak clean 
	cd linad99; MAKE -f optmsc7-laplace.mak  clean
	cd linad99; MAKE -f safmsc7-laplace.mak   clean
	cd tools99; MAKE -f optmsc7-laplace.mak   clean
	cd tools99; MAKE -f safmsc7-laplace.mak   clean
	cd nh99; MAKE -f optmsc7-laplace.mak   clean
	cd nh99; MAKE -f safmsc7-laplace.mak   clean

hanscopy:
	- cd $(DISKDIR) ; rm admodel.zip ; \
        cfind . |  zip -@ admodel.zip ; \
        scp admodel.zip root@192.168.1.1:/home/skaug/real-experimental/msvc7

redemoall:
	cd linad99; MAKE LIBPATH=msc7olp-demo DISKDIR=f:/admb-vc7.1-demo "OPTIONS=-DADMB_REDEMO" -f optmsc7-laplace.mak  all
	cd linad99; MAKE LIBPATH=msc7slp-demo DISKDIR=f:/admb-vc7.1-demo "OPTIONS=-DADMB_REDEMO" -f safmsc7-laplace.mak  all
	cd tools99; MAKE LIBPATH=msc7olp-demo DISKDIR=f:/admb-vc7.1-demo "OPTIONS=-DADMB_REDEMO" -f optmsc7-laplace.mak  all
	cd tools99; MAKE LIBPATH=msc7slp-demo DISKDIR=f:/admb-vc7.1-demo "OPTIONS=-DADMB_REDEMO" -f safmsc7-laplace.mak  all
	cd df1b2-separable; MAKE LIBPATH=msc7olp-demo DISKDIR=f:/admb-vc7.1-demo "OPTIONS=-DADMB_REDEMO" -f optmsc7-laplace.mak  all
	cd df1b2-separable; MAKE LIBPATH=msc7slp-demo DISKDIR=f:/admb-vc7.1-demo "OPTIONS=-DADMB_REDEMO" -f safmsc7-laplace.mak  all
	cd nh99; MAKE LIBPATH=msc7olp-demo "OPTIONS=-DADMB_REDEMO" DISKDIR=f:/admb-vc7.1-demo -f optmsc7-laplace.mak  all
	cd nh99; MAKE LIBPATH=msc7slp-demo "OPTIONS=-DADMB_REDEMO" DISKDIR=f:/admb-vc7.1-demo -f safmsc7-laplace.mak  all

yukio_pvm_all:
	cd linad99; MAKE "OPTIONS= /G7 /arch:SSE2" DISKDIR=j:/yukio_adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc7-laplace.mak  all
	cd linad99; MAKE "OPTIONS= /G7 /arch:SSE2" DISKDIR=j:/yukio_adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc7-laplace.mak  all
	cd tools99; MAKE "OPTIONS= /G7 /arch:SSE2" DISKDIR=j:/yukio_adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc7-laplace.mak  all
	cd tools99; MAKE "OPTIONS= /G7 /arch:SSE2" DISKDIR=j:/yukio_adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc7-laplace.mak  all
	cd df1b2-separable; MAKE "OPTIONS= /G7 /arch:SSE2" DISKDIR=j:/yukio_adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc7-laplace.mak  all
	cd df1b2-separable; MAKE "OPTIONS= /G7 /arch:SSE2" DISKDIR=j:/yukio_adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc7-laplace.mak  all
	cd nh99; MAKE "OPTIONS= /G7 /arch:SSE2" DISKDIR=j:/yukio_adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc7-laplace.mak  all
	cd nh99; MAKE "OPTIONS= /G7 /arch:SSE2" DISKDIR=j:/yukio_adms7lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc7-laplace.mak  all

redemoclean:
	cd linad99; MAKE LIBPATH=msc7olp-demo "OPTIONS=-DADMB_REDEMO" -f optmsc7-laplace.mak  clean
	cd linad99; MAKE LIBPATH=msc7slp-demo "OPTIONS=-DADMB_REDEMO" -f safmsc7-laplace.mak  clean
	cd tools99; MAKE LIBPATH=msc7olp-demo "OPTIONS=-DADMB_REDEMO" -f optmsc7-laplace.mak  clean
	cd tools99; MAKE LIBPATH=msc7slp-demo "OPTIONS=-DADMB_REDEMO" -f safmsc7-laplace.mak  clean
	cd df1b2-separable; MAKE LIBPATH=msc7olp-demo "OPTIONS=-DADMB_REDEMO" -f optmsc7-laplace.mak  clean
	cd df1b2-separable; MAKE LIBPATH=msc7slp-demo "OPTIONS=-DADMB_REDEMO" -f safmsc7-laplace.mak  clean
	cd nh99; MAKE LIBPATH=msc7olp-demo "OPTIONS=-DADMB_REDEMO" -f optmsc7-laplace.mak  clean
	cd nh99; MAKE LIBPATH=msc7slp-demo "OPTIONS=-DADMB_REDEMO" -f safmsc7-laplace.mak  clean
	

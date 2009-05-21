DISKDIR=borland-50-laplace-ex
DEMODISKDIR=j:/borland-50-laplace-demo
DEMODISKDIR1=/cygdrive/f/borland-50-laplace-demo
DEMOTPLDIR=l:/openssl-stuff
DEMOTPLDIR1=/cygdrive/l/openss~1
#SHELL=/l/msys/bin/sh.exe

all:
	mkdir $(DISKDIR); mkdir $(DISKDIR)/lib; mkdir $(DISKDIR)/bin; mkdir $(DISKDIR)/include;
	cd linad99; mkdir b32polp; MAKE "DISKDIR=../borland-50-laplace-ex" -f optbor32-laplace.mak  all
	cd nh99; mkdir b32polp; mkdir b32polp-stub; mkdir $(DISKDIR)/bin; MAKE "DISKDIR=../borland-50-laplace-ex" -f optbor32-laplace.mak 
	cd df1b2-separable; mkdir b32polp; MAKE "DISKDIR=../borland-50-laplace-ex" -f optbor32-laplace.mak 
	cd df1b2-separable; mkdir b32pslp; MAKE "DISKDIR=../borland-50-laplace-ex" -f safbor32-laplace.mak 
	cd linad99; mkdir b32pslp; mkdir b32polp; MAKE "DISKDIR=../borland-50-laplace-ex" -f safbor32-laplace.mak  all
	cd tools99; mkdir b32polp; MAKE "DISKDIR=../borland-50-laplace-ex" -f optbor32-laplace.mak 

prodfromscratch: clean all hanscopy

demofromscratch: clean redemoall hansdemocopy

redemoall:
	cd nh99; MAKE "OPTIONS=-DADMB_REDEMO " " DISKDIR=f:/borland-50-laplace-demo" -f optbor32-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS=-DADMB_REDEMO " " DISKDIR=f:/borland-50-laplace-demo" -f optbor32-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS=-DADMB_REDEMO " " DISKDIR=f:/borland-50-laplace-demo" -f safbor32-laplace.mak 
	cd linad99; MAKE "OPTIONS=-DADMB_REDEMO " " DISKDIR=f:/borland-50-laplace-demo" -f optbor32-laplace.mak  all
	cd linad99; MAKE "OPTIONS=-DADMB_REDEMO " " DISKDIR=f:/borland-50-laplace-demo" -f safbor32-laplace.mak  all
	cd tools99; MAKE "OPTIONS=-DADMB_REDEMO " " DISKDIR=f:/borland-50-laplace-demo" -f optbor32-laplace.mak 

clean:
	cd linad99; MAKE -f optbor32-laplace.mak  clean
	cd linad99; MAKE -f safbor32-laplace.mak   clean
	cd tools99; MAKE -f optbor32-laplace.mak   clean
	cd nh99; MAKE -f optbor32-laplace.mak   clean
	cd df1b2-separable; MAKE -f optbor32-laplace.mak clean
	cd df1b2-separable; MAKE -f safbor32-laplace.mak clean


hansdemocopy:
	- echo $(SHELL)
	- cd $(DEMODISKDIR) ; rm ad_build.zip ; \
	- rm $(DEMODISKDIR)/bin/tpl2rem.exe ; \ 	
	- rm $(DEMODISKDIR)/bin/tpl2cpp.exe ; \ 	
	- copy $(DEMOTPLDIR1)/dtplcpp.exe $(DEMODISKDIR1)/bin/demotpl2cpp.exe ; \ 	
	- copy $(DEMOTPLDIR1)/dtplrem.exe $(DEMODISKDIR1)/bin/demotpl2rem.exe ; \ 	
	- cd $(DEMODISKDIR) ; cfind . |  zip -@ ad_build ; 
	cd $(DEMODISKDIR) ; scp ad_build.zip root@192.168.1.1:/home/skaug/borland-50-demo

hanscopy:
	- cd $(DISKDIR) ; rm ad_build.zip ; \
        cfind . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/real-experimental/borland-50

hansholistic:
	- cd $(DISKDIR) ; rm ad_build.zip ; \
        cfind . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/holistic/borland-50

df1b2clean:
	cd df1b2-separable; MAKE -f optbor32-laplace.mak clean
	cd df1b2-separable; MAKE -f safbor32-laplace.mak clean


linadclean:
	cd linad99; MAKE -f optbor32-laplace.mak  clean
	cd linad99; MAKE -f safbor32-laplace.mak   clean

toolsclean:
	cd tools99; MAKE -f optbor32-laplace.mak   clean

nh99clean:
	cd nh99; MAKE -f optbor32-laplace.mak   clean

	

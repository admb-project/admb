DISKDIR= h:/adms8lp.m32

	cd nh99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all

all64:
	cd nh99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak all
	cd nh99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak all
	cd linad99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak all
	cd linad99; MAKE DISKDIR=c:/adms8lp.m32 LIBPATH=msc8slp64 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " -f safmsc8-laplace.mak all
	cd tools99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak all
	cd tools99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak all
	cd df1b2-separable; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak all
	cd df1b2-separable; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak all
	cd newdd; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak all
	cd newdd; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak all
	cd newquad; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak all
	cd newquad; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak all

all32noqd:
	cd linad99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd linad99; MAKE DISKDIR=j:/adms8lp1.m32 LIBPATH=msc8slp32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " -f safmsc8-laplace.mak all
	cd nh99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd nh99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd tools99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd tools99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all

all32:
	cd linad99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd linad99; MAKE DISKDIR=j:/adms8lp1.m32 LIBPATH=msc8slp32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " -f safmsc8-laplace.mak all
	cd nh99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd nh99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd tools99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd tools99; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd newdd; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd newdd; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd newquad; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd newquad; MAKE DISKDIR=j:/adms8lp1.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all


test:
	cd nh99; MAKE DISKDIR=h:/adms8lp.m32 -f safmsc8-laplace.mak  all
	cd nh99; MAKE DISKDIR=h:/adms8lp.m32 -f optmsc8-laplace.mak  all
	cd df1b2-separable; MAKE DISKDIR=h:/adms8lp.m32 -f safmsc8-laplace.mak  all
	cd tools99; MAKE DISKDIR=h:/adms8lp.m32 -f safmsc8-laplace.mak  all
	cd linad99; MAKE DISKDIR=h:/adms8lp.m32 -f safmsc8-laplace.mak  all
	cd linad99; MAKE DISKDIR=h:/adms8lp.m32 -f safmsc8-laplace.mak  all
	cd linad99; MAKE DISKDIR=h:/adms8lp.m32 -f optmsc8-laplace.mak  all
	cd df1b2-separable; MAKE DISKDIR=h:/adms8lp.m32 -f optmsc8-laplace.mak  all
	cd tools99; MAKE DISKDIR=h:/adms8lp.m32 -f optmsc8-laplace.mak  all

all:
	cd linad99; MAKE -f safmsc8-laplace.mak  all
	cd linad99; MAKE -f optmsc8-laplace.mak  all
	cd nh99; MAKE -f safmsc8-laplace.mak  all
	cd nh99; MAKE -f optmsc8-laplace.mak  all
	cd tools99; MAKE -f safmsc8-laplace.mak  all
	cd tools99; MAKE -f optmsc8-laplace.mak  all
	cd df1b2-separable; MAKE -f optmsc8-laplace.mak  all
	cd df1b2-separable; MAKE -f safmsc8-laplace.mak  all

pvmall:
	cd linad99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL- /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f optmsc8-laplace.mak  all
	cd linad99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL- /EHsc    -DUSE_ADPVM -Ie:/psdk/Include " -f safmsc8-laplace.mak  all
	cd nh99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL- /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f optmsc8-laplace.mak  all
	cd nh99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL- /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f safmsc8-laplace.mak  all
	cd newquad; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL-   /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f safmsc8-laplace.mak  all
	cd newquad; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL-   /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f optmsc8-laplace.mak  all
	cd newdd; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL-   /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f optmsc8-laplace.mak  all
	cd newdd; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL-   /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f safmsc8-laplace.mak  all
	cd tools99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL- /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f optmsc8-laplace.mak  all
	cd tools99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /GL- /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " -f safmsc8-laplace.mak  all
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /EHsc  /GL- -DUSE_ADPVM -Ie:/psdk/Include " -f optmsc8-laplace.mak  all
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /G7 /arch:SSE2 /EHsc  /GL- -DUSE_ADPVM -Ie:/psdk/Include " -f safmsc8-laplace.mak  all

clean:
	cd df1b2-separable; MAKE -f optmsc8-laplace.mak clean 
	cd df1b2-separable; MAKE -f safmsc8-laplace.mak clean 
	cd linad99; MAKE -f optmsc8-laplace.mak  clean
	cd linad99; MAKE -f safmsc8-laplace.mak   clean
	cd tools99; MAKE -f optmsc8-laplace.mak   clean
	cd tools99; MAKE -f safmsc8-laplace.mak   clean
	cd nh99; MAKE -f optmsc8-laplace.mak   clean
	cd nh99; MAKE -f safmsc8-laplace.mak   clean

hanscopy:
	- cd $(DISKDIR) ; rm admodel.zip ; \
        cfind . |  zip -@ admodel.zip ; \
        scp admodel.zip root@192.168.1.1:/home/skaug/real-experimental/msvc8

redemoall:
	cd linad99; MAKE LIBPATH=msc8olp-demo DISKDIR=f:/admb-vc8.1-demo "OPTIONS=-DADMB_REDEMO" -f optmsc8-laplace.mak  all
	cd linad99; MAKE LIBPATH=msc8slp-demo DISKDIR=f:/admb-vc8.1-demo "OPTIONS=-DADMB_REDEMO" -f safmsc8-laplace.mak  all
	cd tools99; MAKE LIBPATH=msc8olp-demo DISKDIR=f:/admb-vc8.1-demo "OPTIONS=-DADMB_REDEMO" -f optmsc8-laplace.mak  all
	cd tools99; MAKE LIBPATH=msc8slp-demo DISKDIR=f:/admb-vc8.1-demo "OPTIONS=-DADMB_REDEMO" -f safmsc8-laplace.mak  all
	cd df1b2-separable; MAKE LIBPATH=msc8olp-demo DISKDIR=f:/admb-vc8.1-demo "OPTIONS=-DADMB_REDEMO" -f optmsc8-laplace.mak  all
	cd df1b2-separable; MAKE LIBPATH=msc8slp-demo DISKDIR=f:/admb-vc8.1-demo "OPTIONS=-DADMB_REDEMO" -f safmsc8-laplace.mak  all
	cd nh99; MAKE LIBPATH=msc8olp-demo "OPTIONS=-DADMB_REDEMO" DISKDIR=f:/admb-vc8.1-demo -f optmsc8-laplace.mak  all
	cd nh99; MAKE LIBPATH=msc8slp-demo "OPTIONS=-DADMB_REDEMO" DISKDIR=f:/admb-vc8.1-demo -f safmsc8-laplace.mak  all

yukio_pvm_all:
	cd linad99; MAKE "OPTIONS= /G8 /arch:SSE2" DISKDIR=j:/yukio_adms8lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc8-laplace.mak  all
	cd linad99; MAKE "OPTIONS= /G8 /arch:SSE2" DISKDIR=j:/yukio_adms8lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc8-laplace.mak  all
	cd tools99; MAKE "OPTIONS= /G8 /arch:SSE2" DISKDIR=j:/yukio_adms8lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc8-laplace.mak  all
	cd tools99; MAKE "OPTIONS= /G8 /arch:SSE2" DISKDIR=j:/yukio_adms8lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc8-laplace.mak  all
	cd df1b2-separable; MAKE "OPTIONS= /G8 /arch:SSE2" DISKDIR=j:/yukio_adms8lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc8-laplace.mak  all
	cd df1b2-separable; MAKE "OPTIONS= /G8 /arch:SSE2" DISKDIR=j:/yukio_adms8lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc8-laplace.mak  all
	cd nh99; MAKE "OPTIONS= /G8 /arch:SSE2" DISKDIR=j:/yukio_adms8lp.m32 PVMOPTION=-DUSE_ADPVM -f optmsc8-laplace.mak  all
	cd nh99; MAKE "OPTIONS= /G8 /arch:SSE2" DISKDIR=j:/yukio_adms8lp.m32 PVMOPTION=-DUSE_ADPVM -f safmsc8-laplace.mak  all

redemoclean:
	cd linad99; MAKE LIBPATH=msc8olp-demo "OPTIONS=-DADMB_REDEMO" -f optmsc8-laplace.mak  clean
	cd linad99; MAKE LIBPATH=msc8slp-demo "OPTIONS=-DADMB_REDEMO" -f safmsc8-laplace.mak  clean
	cd tools99; MAKE LIBPATH=msc8olp-demo "OPTIONS=-DADMB_REDEMO" -f optmsc8-laplace.mak  clean
	cd tools99; MAKE LIBPATH=msc8slp-demo "OPTIONS=-DADMB_REDEMO" -f safmsc8-laplace.mak  clean
	cd df1b2-separable; MAKE LIBPATH=msc8olp-demo "OPTIONS=-DADMB_REDEMO" -f optmsc8-laplace.mak  clean
	cd df1b2-separable; MAKE LIBPATH=msc8slp-demo "OPTIONS=-DADMB_REDEMO" -f safmsc8-laplace.mak  clean
	cd nh99; MAKE LIBPATH=msc8olp-demo "OPTIONS=-DADMB_REDEMO" -f optmsc8-laplace.mak  clean
	cd nh99; MAKE LIBPATH=msc8slp-demo "OPTIONS=-DADMB_REDEMO" -f safmsc8-laplace.mak  clean
	
all64clean:
	cd linad99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd linad99; MAKE DISKDIR=c:/adms8lp.m32 LIBPATH=msc8slp64 "PVMOPTION= /GL- -Ic:/psdk/Include " -f safmsc8-laplace.mak clean
	cd tools99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd tools99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd df1b2-separable; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd df1b2-separable; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd nh99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd nh99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -DUSE_ADPVM -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd newdd; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd newdd; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd newquad; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd newquad; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean

all32sse2:
	cd nh99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd nh99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -DUSE_ADPVM -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd linad99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd linad99; MAKE DISKDIR=j:/adms8lp.m32 LIBPATH=msc8slp32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " -f safmsc8-laplace.mak all
	cd tools99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd tools99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd newdd; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all
	cd newdd; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd newquad; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak all
	cd newquad; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /arch:SSE2 /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak all

all32clean:
	cd nh99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak clean
	cd nh99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak clean
	cd linad99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak clean
	cd linad99; MAKE DISKDIR=j:/adms8lp.m32 LIBPATH=msc8slp32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " -f safmsc8-laplace.mak clean
	cd tools99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak clean
	cd tools99; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak clean
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak clean
	cd df1b2-separable; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak clean
	cd newdd; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak clean
	cd newdd; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak clean
	cd newquad; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8slp32 -f safmsc8-laplace.mak clean
	cd newquad; MAKE DISKDIR=j:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ie:/psdk/Include " LIBPATH=msc8olp32 -f optmsc8-laplace.mak clean

all64clean:
	cd nh99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd nh99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -DUSE_ADPVM -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd linad99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd linad99; MAKE DISKDIR=c:/adms8lp.m32 LIBPATH=msc8slp64 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " -f safmsc8-laplace.mak clean
	cd tools99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd tools99; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd df1b2-separable; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd df1b2-separable; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd newdd; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean
	cd newdd; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd newquad; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8slp64 -f safmsc8-laplace.mak clean
	cd newquad; MAKE DISKDIR=c:/adms8lp.m32 "PVMOPTION= /GL- /EHsc  -Ic:/psdk/Include " LIBPATH=msc8olp64 -f optmsc8-laplace.mak clean


test:
	cd ./newdoubledouble; $(MAKE) LIBNAME=libaddo.a DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-DUSE_DD -DUSE_ADPVM" -f optg32-rh8.mak  disk

all:
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp -f optg32-rh8.mak disk
	cd ./nh99;    $(MAKE) DISKDIR=/g32-rh8-nolp -f optg32-rh8.mak  disk
	cd ./tools99; $(MAKE) DISKDIR=/g32-rh8-nolp -f optg32-rh8.mak  disk
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp -f safg32-rh8.mak  disk

gcc4all:
	cd ./linad99; $(MAKE) "CC=gcc4" DISKDIR=/g40-rh8-nolp -f optg32-rh8.mak disk
	cd ./nh99;    $(MAKE) "CC=gcc4" DISKDIR=/g40-rh8-nolp -f optg32-rh8.mak  disk
	cd ./tools99; $(MAKE) "CC=gcc4" DISKDIR=/g40-rh8-nolp -f optg32-rh8.mak  disk
	cd ./linad99; $(MAKE) "CC=gcc4" DISKDIR=/g40-rh8-nolp -f safg32-rh8.mak  disk

alldbg:
	cd ./linad99; $(MAKE) "OPTIONS= -g " -f optg32-rh8.mak disk
	cd ./nh99;    $(MAKE) "OPTIONS= -g " -f optg32-rh8.mak  disk
	cd ./tools99; $(MAKE) "OPTIONS= -g " -f optg32-rh8.mak  disk
	cd ./linad99; $(MAKE) "OPTIONS= -g " -f safg32-rh8.mak  disk

arclean:
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-DUSE_ADPVM " -f optg32-rh8.mak arclean
	cd ./nh99;    $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f optg32-rh8.mak arclean 
	cd ./tools99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f optg32-rh8.mak  arclean
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f safg32-rh8.mak  arclean

pvmall:
	cd ./newdoubledouble; $(MAKE) LIBNAME=libaddo.a DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-DUSE_DD -DUSE_ADPVM" -f optg32-rh8.mak  disk
	cd ./newdoubledouble; $(MAKE) LIBNAME=libadds.a DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-DUSE_DD -DUSE_ADPVM" -f safg32-rh8.mak  disk
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-DUSE_ADPVM " -f optg32-rh8.mak disk
	cd ./nh99;    $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f optg32-rh8.mak all
	cd ./tools99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f optg32-rh8.mak  disk
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f safg32-rh8.mak  disk

pvmalldbg:
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-g -DUSE_ADPVM " -f optg32-rh8.mak disk
	cd ./nh99;    $(MAKE) DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-g -DUSE_ADPVM " -f optg32-rh8.mak all
	cd ./tools99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-g -DUSE_ADPVM " -f optg32-rh8.mak  disk
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-g -DUSE_ADPVM " -f safg32-rh8.mak  disk

clean:
	cd ./linad99; $(MAKE) -f optg32-rh8.mak clean
	cd ./nh99;    $(MAKE) -f optg32-rh8.mak  clean
	cd ./tools99; $(MAKE) -f optg32-rh8.mak  clean
	cd ./linad99; $(MAKE) -f safg32-rh8.mak  clean

cleanlinad99:
	cd ./linad99; $(MAKE) -f safg32-rh8.mak  clean

pvmallclean:
	cd ./newdoubledouble; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-DUSE_ADPVM " -f optg32-rh8.mak clean
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm "OPTIONS=-DUSE_ADPVM " -f optg32-rh8.mak clean
	cd ./nh99;    $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f optg32-rh8.mak clean
	cd ./tools99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f optg32-rh8.mak  clean
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-nolp-pvm OPTIONS=-DUSE_ADPVM -f safg32-rh8.mak  clean

amd64pvmall:
	cd ./linad99; $(MAKE) LIBPATH=gcc346-amd64o DISKDIR=/g346-amd64-nolp-pvm "OPTIONS=-DUSE_ADPVM -g " -f optg32-rh8.mak disk
	cd ./nh99;    $(MAKE) LIBPATH=gcc346-amd64o DISKDIR=/g346-amd64-nolp-pvm "OPTIONS=-DUSE_ADPVM -g " -f optg32-rh8.mak disk
	cd ./tools99; $(MAKE) LIBPATH=gcc346-amd64o DISKDIR=/g346-amd64-nolp-pvm "OPTIONS=-DUSE_ADPVM -g " -f optg32-rh8.mak  disk
	cd ./linad99; $(MAKE) LIBPATH=gcc346-amd64s DISKDIR=/g346-amd64-nolp-pvm "OPTIONS=-DUSE_ADPVM -g " -f safg32-rh8.mak  disk

amd64pvmclean:
	cd ./linad99; $(MAKE) LIBPATH=gcc346-amd64o DISKDIR=/g346-amd64-nolp-pvm "OPTIONS=-DUSE_ADPVM " -f optg32-rh8.mak clean
	cd ./nh99;    $(MAKE) LIBPATH=gcc346-amd64o DISKDIR=/g346-amd64-nolp-pvm "OPTIONS=-DUSE_ADPVM " -f optg32-rh8.mak clean
	cd ./tools99; $(MAKE) LIBPATH=gcc346-amd64o DISKDIR=/g346-amd64-nolp-pvm "OPTIONS=-DUSE_ADPVM " -f optg32-rh8.mak  clean
	cd ./linad99; $(MAKE) LIBPATH=gcc346-amd64s DISKDIR=/g346-amd64-nolp-pvm "OPTIONS=-DUSE_ADPVM " -f safg32-rh8.mak  clean




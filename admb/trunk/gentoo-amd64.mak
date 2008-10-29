
pvmgcc34all:
	cd ./linad99; $(MAKE) CC=gcc34 DISKDIR=/usr/local/bin/admodel OPTIONS="-DUSE_ADPVM -g" -f optg32-gentoo-amd64.mak disk
	cd ./nh99;    $(MAKE) CC=gcc34 DISKDIR=/usr/local/bin/admodel OPTIONS="-DUSE_ADPVM -g" -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) CC=gcc34 DISKDIR=/usr/local/bin/admodel OPTIONS="-DUSE_ADPVM -g" -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) CC=gcc34 DISKDIR=/usr/local/bin/admodel OPTIONS="-DUSE_ADPVM -g" -f optg32-gentoo-amd64.mak  disk

pvmall1:
	cd ./nh99;    $(MAKE) CC=gcc32 OPTIONS="    -O3 -DUSE_ADPVM   " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) CC=gcc32 OPTIONS="    -O3 -DUSE_ADPVM   " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) CC=gcc32 OPTIONS="    -O3 -DUSE_ADPVM   " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) CC=gcc32 OPTIONS="    -O3 -DUSE_ADPVM   " -f safg32-gentoo-amd64.mak  disk



all:
	cd ./linad99; $(MAKE) OPTIONS=" -msse2 -funroll-loops -ffast-math -fexpensive-optimizations " -f safg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) OPTIONS=" -msse2 -funroll-loops -ffast-math -fexpensive-optimizations " -f optg32-gentoo-amd64.mak disk
	cd ./nh99;    $(MAKE) OPTIONS=" -msse2 -funroll-loops -ffast-math -fexpensive-optimizations " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) OPTIONS=" -msse2 -funroll-loops -ffast-math -fexpensive-optimizations " -f optg32-gentoo-amd64.mak disk

pvmall:
	cd ./linad99; $(MAKE) DISKDIR=/usr/local/bin/admodel OPTIONS="-DUSE_ADPVM -g" -f optg32-gentoo-amd64.mak disk
	cd ./nh99;    $(MAKE) DISKDIR=/usr/local/bin/admodel OPTIONS="-DUSE_ADPVM -g" -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) DISKDIR=/usr/local/bin/admodel OPTIONS="-DUSE_ADPVM -g" -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) DISKDIR=/usr/local/bin/admodel OPTIONS="-DUSE_ADPVM -g" -f optg32-gentoo-amd64.mak  disk

gcc342-pvmall:
	cd ./linad99; $(MAKE) OPTIONS="-DUSE_ADPVM -O3 -march=opteron" DISKDIR=/tmp/g34-gentoo LIBNAME=libado.a LIBPATH=gcc342-amd64o CC=/usr/local/bin/gcc -f optg32-gentoo-amd64.mak disk
	cd ./nh99;    $(MAKE) OPTIONS="-DUSE_ADPVM -O3 -march=opteron" DISKDIR=/tmp/g34-gentoo LIBNAME=libadmod.a LIBPATH=gcc342-amd64o CC=/usr/local/bin/gcc -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) OPTIONS="-DUSE_ADPVM -O3 -march=opteron" DISKDIR=/tmp/g34-gentoo LIBNAME=libadt.a LIBPATH=gcc342-amd64o CC=/usr/local/bin/gcc -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) OPTIONS="-DUSE_ADPVM -O3 -march=opteron" DISKDIR=/tmp/g34-gentoo LIBPATH=gcc342-amd64s CC=/usr/local/bin/gcc -f safg32-gentoo-amd64.mak  disk

clean:
	cd ./linad99; $(MAKE) -f optg32-gentoo-amd64.mak clean
	cd ./nh99;    $(MAKE) -f optg32-gentoo-amd64.mak  clean
	cd ./tools99; $(MAKE) -f optg32-gentoo-amd64.mak  clean
	cd ./linad99; $(MAKE) -f optg32-gentoo-amd64.mak  clean

gcc342-clean:
	cd ./linad99; $(MAKE) OPTIONS="-DUSE_ADPVM -O3 -march=opteron" DISKDIR=/tmp/g34-gentoo LIBNAME=libado.a LIBPATH=gcc342-amd64o CC=/usr/local/bin/gcc -f optg32-gentoo-amd64.mak clean
	cd ./nh99;    $(MAKE) OPTIONS="-DUSE_ADPVM -O3 -march=opteron" DISKDIR=/tmp/g34-gentoo LIBNAME=libadmod.a LIBPATH=gcc342-amd64o CC=/usr/local/bin/gcc -f optg32-gentoo-amd64.mak clean
	cd ./tools99; $(MAKE) OPTIONS="-DUSE_ADPVM -O3 -march=opteron" DISKDIR=/tmp/g34-gentoo LIBNAME=libadt.a LIBPATH=gcc342-amd64o CC=/usr/local/bin/gcc -f optg32-gentoo-amd64.mak clean
	cd ./linad99; $(MAKE) OPTIONS="-DUSE_ADPVM -O3 -march=opteron" DISKDIR=/tmp/g34-gentoo LIBPATH=gcc342-amd64s CC=/usr/local/bin/gcc -f safg32-gentoo-amd64.mak  clean



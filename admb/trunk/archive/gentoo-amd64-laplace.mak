all64:
	cd ./df1b2-separable; $(MAKE)   OPTIONS="  -O3  -DUSE_LAPLACE " -f optg32-gentoo-amd64.mak all
	cd ./nh99;    $(MAKE) OPTIONS="    -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) OPTIONS="    -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) OPTIONS="    -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./df1b2-separable; $(MAKE) OPTIONS=" -g   -O3  -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak all
	cd ./linad99; $(MAKE) OPTIONS="    -O3  -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak  disk

all32:
	cd ./df1b2-separable; $(MAKE) OPTIONS="  -m32  -O3  -DUSE_LAPLACE " -f optg32-gentoo-amd64.mak all
	cd ./nh99;    $(MAKE) OPTIONS="  -m32  -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) OPTIONS="  -m32  -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) OPTIONS="  -m32  -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./df1b2-separable; $(MAKE) OPTIONS=" -g -m32  -O3  -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak all
	cd ./linad99; $(MAKE) OPTIONS="  -m32  -O3  -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak  disk

pvmall1:
	cd ./df1b2-separable; $(MAKE) CC=gcc32 OPTIONS=" -gdwarf-2   -O3 -DUSE_ADPVM   -DUSE_LAPLACE " -f optg32-gentoo-amd64.mak all
	cd ./nh99;    $(MAKE) CC=gcc32 OPTIONS=" -gdwarf-2   -O3 -DUSE_ADPVM   -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) CC=gcc32 OPTIONS=" -gdwarf-2   -O3 -DUSE_ADPVM   -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) CC=gcc32 OPTIONS=" -gdwarf-2   -O3 -DUSE_ADPVM   -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./df1b2-separable; $(MAKE) CC=gcc32 OPTIONS=" -gdwarf-2   -O3 -DUSE_ADPVM   -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak all
	cd ./linad99; $(MAKE) CC=gcc32 OPTIONS=" -gdwarf-2   -O3 -DUSE_ADPVM   -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak  disk

all1nodebug:
	cd ./df1b2-separable; $(MAKE) CC=gcc32 OPTIONS="     -O3  -DUSE_LAPLACE " -f optg32-gentoo-amd64.mak all
	cd ./nh99;    $(MAKE) CC=gcc32 OPTIONS="     -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) CC=gcc32 OPTIONS="     -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) CC=gcc32 OPTIONS="     -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./df1b2-separable; $(MAKE) CC=gcc32 OPTIONS="     -O3  -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak all
	cd ./linad99; $(MAKE) CC=gcc32 OPTIONS="     -O3  -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak  disk

all1:
	cd ./df1b2-separable; $(MAKE) DISKDIR=/tmp/g32-gentoo-debug CC=gcc32 OPTIONS=" -gdwarf-2   -O3  -DUSE_LAPLACE " -f optg32-gentoo-amd64.mak all
	cd ./nh99;    $(MAKE) DISKDIR=/tmp/g32-gentoo-debug CC=gcc32 OPTIONS=" -gdwarf-2   -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) DISKDIR=/tmp/g32-gentoo-debug CC=gcc32 OPTIONS=" -gdwarf-2   -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) DISKDIR=/tmp/g32-gentoo-debug CC=gcc32 OPTIONS=" -gdwarf-2   -O3  -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./df1b2-separable; $(MAKE) DISKDIR=/tmp/g32-gentoo-debug CC=gcc32 OPTIONS=" -gdwarf-2   -O3  -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak all
	cd ./linad99; $(MAKE) DISKDIR=/tmp/g32-gentoo-debug  CC=gcc32 OPTIONS=" -gdwarf-2   -O3  -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak  disk

newall:
	cd ./df1b2-separable; $(MAKE) LIBPATH=/usr/bin/admb/df1b2-separable OPTIONS=" -g -DUSE_LAPLACE " -f optg32-gentoo-amd64.mak all
	cd ./nh99;    $(MAKE) LIBPATH=/usr/bin/admb/nh99 OPTIONS=" -g -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) LIBPATH=/usr/bin/admb/tools99 OPTIONS=" -g -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) LIBPATH=/usr/bin/admb/linad99 OPTIONS=" -g -DUSE_LAPLACE  " -f optg32-gentoo-amd64.mak disk
	cd ./df1b2-separable; $(MAKE) LIBPATH=/usr/bin/admb/df1b2-separable-safe  OPTIONS=" -g -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak all
	cd ./linad99; $(MAKE) LIBPATH=/usr/bin/admb/linad99-safe OPTIONS=" -g -DUSE_LAPLACE " -f safg32-gentoo-amd64.mak  disk
pvmall:
	cd ./nh99;    $(MAKE) OPTIONS=" -g -DUSE_LAPLACE -DUSE_ADPVM " -f optg32-gentoo-amd64.mak disk
	cd ./tools99; $(MAKE) OPTIONS=" -g -DUSE_LAPLACE -DUSE_ADPVM " -f optg32-gentoo-amd64.mak disk
	cd ./linad99; $(MAKE) OPTIONS=" -g -DUSE_LAPLACE -DUSE_ADPVM " -f optg32-gentoo-amd64.mak disk
	cd ./df1b2-separable; $(MAKE) OPTIONS=" -g -DUSE_LAPLACE -DUSE_ADPVM " -f optg32-gentoo-amd64.mak all
	cd ./df1b2-separable; $(MAKE) OPTIONS=" -g -DUSE_LAPLACE -DUSE_ADPVM " -f safg32-gentoo-amd64.mak all
	cd ./linad99; $(MAKE) OPTIONS=" -g -DUSE_LAPLACE -DUSE_ADPVM " -f safg32-gentoo-amd64.mak  disk

clean:
	cd ./nh99;    $(MAKE) -f optg32-gentoo-amd64.mak  clean
	cd ./tools99; $(MAKE) -f optg32-gentoo-amd64.mak  clean
	cd ./linad99; $(MAKE) -f optg32-gentoo-amd64.mak clean
	cd ./linad99; $(MAKE) -f safg32-gentoo-amd64.mak  clean
	cd ./df1b2-separable; $(MAKE) -f optg32-gentoo-amd64.mak clean
	cd ./df1b2-separable; $(MAKE) -f safg32-gentoo-amd64.mak  clean

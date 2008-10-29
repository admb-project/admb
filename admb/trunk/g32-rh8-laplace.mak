DISKDIR= /g32-rh8


gcc345all:
	- cd ./linad99; mkdir gcc345-fc4olp 
	- cd ./linad99; mkdir gcc345-fc4slp 
	- cd ./nh99;    mkdir gcc345-fc4olp 
	- cd ./nh99;    mkdir gcc345-fc4olp-stub 
	- cd ./tools99; mkdir gcc345-fc4olp 
	- cd ./df1b2-separable; mkdir gcc345-fc4olp 
	- cd ./df1b2-separable;  mkdir gcc345-fc4slp 
	cd ./linad99; $(MAKE)  CC=gcc3 LIBPATH=gcc345-fc4olp DISKDIR=/g345-fc4 -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=gcc3 LIBPATH=gcc345-fc4slp DISKDIR=/g345-fc4 -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  CC=gcc3 STUBPATH=gcc345-fc4olp-stub LIBPATH=gcc345-fc4olp DISKDIR=/g345-fc4 -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  CC=gcc3 LIBPATH=gcc345-fc4olp DISKDIR=/g345-fc4 -f optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=gcc3 LIBPATH=gcc345-fc4olp DISKDIR=/g345-fc4 -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=gcc3 LIBPATH=gcc345-fc4slp DISKDIR=/g345-fc4 -f  safg32-rh8-laplace.mak disk 

gcc346all:
	- cd ./linad99; mkdir gcc346-fc4olp 
	- cd ./linad99; mkdir gcc346-fc4slp 
	- cd ./nh99;    mkdir gcc346-fc4olp 
	- cd ./nh99;    mkdir gcc346-fc4olp-stub 
	- cd ./tools99; mkdir gcc346-fc4olp 
	- cd ./df1b2-separable; mkdir gcc346-fc4olp 
	- cd ./df1b2-separable;  mkdir gcc346-fc4slp 
	cd ./linad99; $(MAKE)  CC=gcc3 LIBPATH=gcc346-fc4olp DISKDIR=/g346-lp-fc4 -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=gcc3 LIBPATH=gcc346-fc4slp DISKDIR=/g346-lp-fc4 -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  CC=gcc3 STUBPATH=gcc346-fc4olp-stub LIBPATH=gcc346-fc4olp DISKDIR=/g346-lp-fc4 -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  CC=gcc3 LIBPATH=gcc346-fc4olp DISKDIR=/g346-lp-fc4 -f optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=gcc3 LIBPATH=gcc346-fc4olp DISKDIR=/g346-lp-fc4 -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=gcc3 LIBPATH=gcc346-fc4slp DISKDIR=/g346-lp-fc4 -f  safg32-rh8-laplace.mak disk 

gcc402fc4all:
	- cd ./linad99; mkdir gcc402-fc4olp 
	- cd ./linad99; mkdir gcc402-fc4slp 
	- cd ./nh99;    mkdir gcc402-fc4olp 
	- cd ./nh99;    mkdir gcc402-fc4olp-stub 
	- cd ./tools99; mkdir gcc402-fc4olp 
	- cd ./df1b2-separable; mkdir gcc402-fc4olp 
	- cd ./df1b2-separable;  mkdir gcc402-fc4slp 
	cd ./linad99; $(MAKE)  CC=/usr/bin/gcc LIBPATH=gcc402-fc4olp DISKDIR=/g402-fc4 -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=/usr/bin/gcc LIBPATH=gcc402-fc4slp DISKDIR=/g402-fc4 -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  CC=/usr/bin/gcc STUBPATH=gcc402-fc4olp-stub LIBPATH=gcc402-fc4olp DISKDIR=/g402-fc4 -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  CC=/usr/bin/gcc LIBPATH=gcc402-fc4olp DISKDIR=/g402-fc4 -f optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=/usr/bin/gcc LIBPATH=gcc402-fc4olp DISKDIR=/g402-fc4 -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) CC=/usr/bin/gcc LIBPATH=gcc402-fc4slp DISKDIR=/g402-fc4 -f  safg32-rh8-laplace.mak disk 


gcc411all:
	cd ./linad99; $(MAKE)  LIBPATH=gcc411-fc5olp DISKDIR=/g411-fc5 -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  LIBPATH=gcc411-fc5slp DISKDIR=/g411-fc5 -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  LIBPATH=gcc411-fc5olp DISKDIR=/g411-fc5 -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  LIBPATH=gcc411-fc5olp DISKDIR=/g411-fc5 -f optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; LIBPATH=gcc411-fc5olp $(MAKE) DISKDIR=/g411-fc5 -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; LIBPATH=gcc411-fc5slp $(MAKE) DISKDIR=/g411-fc5 -f  safg32-rh8-laplace.mak disk 

gcc411clean:
	cd ./linad99; $(MAKE)  LIBPATH=gcc411-fc5olp DISKDIR=/g411-fc5 -f optg32-rh8-laplace.mak clean
	cd ./linad99; $(MAKE)  LIBPATH=gcc411-fc5slp DISKDIR=/g411-fc5 -f safg32-rh8-laplace.mak  clean 
	cd ./nh99;    $(MAKE)  LIBPATH=gcc411-fc5olp DISKDIR=/g411-fc5 -f optg32-rh8-laplace.mak  clean
	cd ./tools99; $(MAKE)  LIBPATH=gcc411-fc5olp DISKDIR=/g411-fc5 -f optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; LIBPATH=gcc411-fc5olp $(MAKE) DISKDIR=/g411-fc5 -f  optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; LIBPATH=gcc411-fc5slp $(MAKE) DISKDIR=/g411-fc5 -f  safg32-rh8-laplace.mak clean 

rh8all:
	cd ./linad99; $(MAKE)  DISKDIR=/g32-rh8 -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  DISKDIR=/g32-rh8 -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  DISKDIR=/g32-rh8 -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  DISKDIR=/g32-rh8 -f optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) DISKDIR=/g32-rh8 -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) DISKDIR=/g32-rh8 -f  safg32-rh8-laplace.mak disk 


qdall:
	cd ./df1b2-separable; $(MAKE) "OPTIONS=-DUSE_DDOUBLE" DISKDIR=/g34-fc3-qd -f  optg32-rh8-laplace.mak  disk
	cd ./linad99; $(MAKE)  "OPTIONS=-DUSE_DDOUBLE" DISKDIR=/g34-fc3-qd -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  "OPTIONS=-DUSE_DDOUBLE" DISKDIR=/g34-fc3-qd -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  "OPTIONS=-DUSE_DDOUBLE" DISKDIR=/g34-fc3-qd -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  "OPTIONS=-DUSE_DDOUBLE" DISKDIR=/g34-fc3-qd -f optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) "OPTIONS=-DUSE_DDOUBLE" DISKDIR=/g34-fc3-qd -f  safg32-rh8-laplace.mak disk 


rh8lfsall:
	cd ./linad99; $(MAKE)  "OPTIONS=-D_FILE_OFFSET_BITS=64" DISKDIR=/g32-rh8lfs -f optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  "OPTIONS=-D_FILE_OFFSET_BITS=64" DISKDIR=/g32-rh8lfs -f safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  "OPTIONS=-D_FILE_OFFSET_BITS=64" DISKDIR=/g32-rh8lfs -f optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  "OPTIONS=-D_FILE_OFFSET_BITS=64" DISKDIR=/g32-rh8lfs -f optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) "OPTIONS=-D_FILE_OFFSET_BITS=64" DISKDIR=/g32-rh8lfs -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) "OPTIONS=-D_FILE_OFFSET_BITS=64" DISKDIR=/g32-rh8lfs -f  safg32-rh8-laplace.mak disk 

debug:
	cd ./df1b2-separable; $(MAKE) DISKDIR=/g32-rh8-dbg "OPTIONS=  -gdwarf-2 -pg -D__CHECK_MEMORY__"  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) DISKDIR=/g32-rh8-dbg "OPTIONS= -gdwarf-2 -pg -D__CHECK_MEMORY__" -f  safg32-rh8-laplace.mak disk 
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-dbg " OPTIONS= -gdwarf-2 -pg"  -f  optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE) DISKDIR=/g32-rh8-dbg " OPTIONS=-gdwarf-2 -pg"   -f  safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE) DISKDIR=/g32-rh8-dbg " OPTIONS=-gdwarf-2 -pg"   -f  optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE) DISKDIR=/g32-rh8-dbg " OPTIONS=-gdwarf-2 -pg"   -f  optg32-rh8-laplace.mak  disk

newall:
	cd ./nh99;    $(MAKE)  -f  optg32-rh8-laplace.mak  disk
	cd ./linad99; $(MAKE)  -f  optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  -f  safg32-rh8-laplace.mak  disk 
	cd ./tools99; $(MAKE)  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE)  OPTIONS= -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE)  OPTIONS= -f  safg32-rh8-laplace.mak disk 

all:
	cd ./linad99; $(MAKE)  CC=/usr/bin/gcc-3.2.2/bin/gcc -f  optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE)  CC=/usr/bin/gcc-3.2.2/bin/gcc  -f  safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE)  CC=/usr/bin/gcc-3.2.2/bin/gcc  -f  optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  CC=/usr/bin/gcc-3.2.2/bin/gcc  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE)  CC=/usr/bin/gcc-3.2.2/bin/gcc  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE)  CC=/usr/bin/gcc-3.2.2/bin/gcc  -f  safg32-rh8-laplace.mak disk 

pvmall:
	cd ./linad99; $(MAKE) DISKDIR=/g/g32-rh8-gcc323-laplace-pvm  PVMOPTION=-DUSE_ADPVM  -f  optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE) DISKDIR=/g/g32-rh8-gcc323-laplace-pvm  PVMOPTION=-DUSE_ADPVM   -f  safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE) DISKDIR=/g/g32-rh8-gcc323-laplace-pvm  PVMOPTION=-DUSE_ADPVM   -f  optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  DISKDIR=/g/g32-rh8-gcc323-laplace-pvm PVMOPTION=-DUSE_ADPVM  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE)  DISKDIR=/g/g32-rh8-gcc323-laplace-pvm PVMOPTION=-DUSE_ADPVM  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE)  DISKDIR=/g/g32-rh8-gcc323-laplace-pvm PVMOPTION=-DUSE_ADPVM  -f  safg32-rh8-laplace.mak disk 

pvmatlasall:

	cd ./linad99; $(MAKE) DISKDIR=/g/g32-rh8-gcc323-laplace-pvm-atlas OPTIONS=-DUSE_ATLAS PVMOPTION=-DUSE_ADPVM  -f  optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE) DISKDIR=/g/g32-rh8-gcc323-laplace-pvm-atlas OPTIONS=-DUSE_ATLAS PVMOPTION=-DUSE_ADPVM   -f  safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE) DISKDIR=/g/g32-rh8-gcc323-laplace-pvm-atlas OPTIONS=-DUSE_ATLAS PVMOPTION=-DUSE_ADPVM   -f  optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE)  DISKDIR=/g/g32-rh8-gcc323-laplace-pvm-atlas OPTIONS=-DUSE_ATLAS PVMOPTION=-DUSE_ADPVM  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE)  DISKDIR=/g/g32-rh8-gcc323-laplace-pvm-atlas OPTIONS=-DUSE_ATLAS PVMOPTION=-DUSE_ADPVM  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE)  DISKDIR=/g/g32-rh8-gcc323-laplace-pvm-atlas OPTIONS=-DUSE_ATLAS PVMOPTION=-DUSE_ADPVM  -f  safg32-rh8-laplace.mak disk 

clean:
	cd ./linad99; $(MAKE) -i -f  optg32-rh8-laplace.mak clean
	cd ./nh99;    $(MAKE) -i -f  optg32-rh8-laplace.mak  clean
	cd ./tools99; $(MAKE) -i -f  optg32-rh8-laplace.mak  clean
	cd ./linad99; $(MAKE) -i -f  safg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE) -i -f  optg32-rh8-laplace.mak clean 
	cd ./df1b2-separable; $(MAKE) -i -f  safg32-rh8-laplace.mak clean 


hanscopy:
	- cd $(DISKDIR) ; rm ad_build.zip ; \
	pwd ; \
        find . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/real-experimental/redhat-80

hanscopy-fc3:
	- cd $(DISKDIR) ; rm ad_build.zip ; \
	pwd ; \
        find . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/real-experimental/fc3

df1b2clean:
	cd ./df1b2-separable; $(MAKE) -i -f  optg32-rh8-laplace.mak clean 
	cd ./df1b2-separable; $(MAKE) -i -f  safg32-rh8-laplace.mak clean 

linadclean:
	cd ./linad99; $(MAKE) -i -f  optg32-rh8-laplace.mak clean
	cd ./linad99; $(MAKE) -i -f  safg32-rh8-laplace.mak  clean

nh99clean:
	cd ./nh99;    $(MAKE) -i -f  optg32-rh8-laplace.mak  clean

tools99clean:
	cd ./tools99; $(MAKE) -i -f  optg32-rh8-laplace.mak  clean

df1b2stub:
	cd ./nh99;    $(MAKE)  -f  optg32-rh8-laplace.mak  df1b2stub

hanspvmcopy:
	- cd /g/g32-rh8-gcc323-laplace-pvm ; rm ad_build.zip ; \
	pwd ; \
	rm *.zip ; \
        find . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/redhat-80-pvm

	

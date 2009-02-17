
DISKDIR=/tmp/g32-rhel3-laplace

gcc343clean:
	cd ./df1b2-separable; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc LIBPATH=gcc343-rhel8o "OPTIONS=  -ggdb  -D__CHECK_MEMORY__"  -f  optg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc LIBPATH=gcc343-rhel8s "OPTIONS= -ggdb  -D__CHECK_MEMORY__" -f  safg32-rh8-laplace.mak clean 
	cd ./linad99; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc " OPTIONS= -ggdb " LIBPATH=gcc343-rhel8o -f  optg32-rh8-laplace.mak clean
	cd ./linad99; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc " OPTIONS=-ggdb " LIBPATH=gcc343-rhel8s   -f  safg32-rh8-laplace.mak  clean 
	cd ./nh99;    $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc " OPTIONS=-ggdb "  LIBPATH=gcc343-rhel8o  -f  optg32-rh8-laplace.mak  clean
	cd ./tools99; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc " OPTIONS=-ggdb "  LIBPATH=gcc343-rhel8o  -f  optg32-rh8-laplace.mak  clean

gcc343:
	cd ./df1b2-separable; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc LIBPATH=gcc343-rhel8o "OPTIONS=  -ggdb  -D__CHECK_MEMORY__"  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc LIBPATH=gcc343-rhel8s "OPTIONS= -ggdb  -D__CHECK_MEMORY__" -f  safg32-rh8-laplace.mak disk 
	cd ./linad99; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc " OPTIONS= -ggdb " LIBPATH=gcc343-rhel8o -f  optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc " OPTIONS=-ggdb " LIBPATH=gcc343-rhel8s   -f  safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc " OPTIONS=-ggdb "  LIBPATH=gcc343-rhel8o  -f  optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE) DISKDIR=/tmp/g343-rhel3-laplace CC=/usr/local/bin/gcc " OPTIONS=-ggdb "  LIBPATH=gcc343-rhel8o  -f  optg32-rh8-laplace.mak  disk

debug:
	cd ./df1b2-separable; $(MAKE) DISKDIR=/tmp/g32-rhel3-laplace LIBPATH=gcc32-rhel8o "OPTIONS=  -ggdb  -D__CHECK_MEMORY__"  -f  optg32-rh8-laplace.mak  disk
	cd ./df1b2-separable; $(MAKE) DISKDIR=/tmp/g32-rhel3-laplace LIBPATH=gcc32-rhel8s "OPTIONS= -ggdb  -D__CHECK_MEMORY__" -f  safg32-rh8-laplace.mak disk 
	cd ./linad99; $(MAKE) DISKDIR=/tmp/g32-rhel3-laplace " OPTIONS= -ggdb " LIBPATH=gcc32-rhel8o -f  optg32-rh8-laplace.mak disk
	cd ./linad99; $(MAKE) DISKDIR=/tmp/g32-rhel3-laplace " OPTIONS=-ggdb " LIBPATH=gcc32-rhel8s   -f  safg32-rh8-laplace.mak  disk 
	cd ./nh99;    $(MAKE) DISKDIR=/tmp/g32-rhel3-laplace " OPTIONS=-ggdb "  LIBPATH=gcc32-rhel8o  -f  optg32-rh8-laplace.mak  disk
	cd ./tools99; $(MAKE) DISKDIR=/tmp/g32-rhel3-laplace " OPTIONS=-ggdb "  LIBPATH=gcc32-rhel8o  -f  optg32-rh8-laplace.mak  disk

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

rhel3clean:
	cd ./linad99; $(MAKE) LIBPATH=gcc32-rhel8s    -i -f  optg32-rh8-laplace.mak clean
	cd ./nh99;    $(MAKE) LIBPATH=gcc32-rhel8o     -i -f  optg32-rh8-laplace.mak  clean
	cd ./tools99; $(MAKE) LIBPATH=gcc32-rhel8o      -i -f  optg32-rh8-laplace.mak  clean
	cd ./linad99; $(MAKE)  LIBPATH=gcc32-rhel8s     -i -f  safg32-rh8-laplace.mak  clean
	cd ./df1b2-separable; $(MAKE)  LIBPATH=gcc32-rhel8o     -i -f  optg32-rh8-laplace.mak clean 
	cd ./df1b2-separable; $(MAKE)  LIBPATH=gcc32-rhel8s     -i -f  safg32-rh8-laplace.mak clean 

hanscopy:
	- cd $(DISKDIR) ; rm ad_build.zip ; \
	pwd ; \
        find . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/redhat-80

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

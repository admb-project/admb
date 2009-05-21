all:
	cd linad99; MAKE DISKDIR=j:/adms6.m32 -f optmsc6.mak  all
	cd linad99; MAKE DISKDIR=j:/adms6.m32 -f safmsc6.mak  all
	cd tools99; MAKE DISKDIR=j:/adms6.m32 -f optmsc6.mak  all
	cd nh99; MAKE DISKDIR=j:/adms6.m32 -f optmsc6.mak  all

pvmall:
	cd linad99; MAKE  DISKDIR=e:/adms6.m32 OPTIONS=-DUSE_ADPVM -f optmsc6.mak  all
	cd linad99; MAKE  DISKDIR=e:/adms6.m32 OPTIONS=-DUSE_ADPVM -f safmsc6.mak  all
	cd tools99; MAKE  DISKDIR=e:/adms6.m32 OPTIONS=-DUSE_ADPVM -f optmsc6.mak  all
	cd nh99; MAKE  DISKDIR=e:/adms6.m32 OPTIONS=-DUSE_ADPVM -f optmsc6.mak  all

clean:
	cd linad99; MAKE -f optmsc6.mak  clean
	cd linad99; MAKE -f safmsc6.mak   clean
	cd tools99; MAKE -f optmsc6.mak   clean
	cd nh99; MAKE -f optmsc6.mak   clean


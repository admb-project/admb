ntest:
	cd newdd; MAKE "OPTIONS= -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd newquad; MAKE "OPTIONS= -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd linad99; MAKE "OPTIONS=-Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -H -Hc  -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd admbthreads; MAKE "OPTIONS= -DTHREAD_SAFE-H -Hc -H=precomp -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd tools99; MAKE "OPTIONS= -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DUSE_ADPVM " -f bdebug.mak 
	cd nh99; MAKE "OPTIONS=-Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DUSE_ADPVM " -f bdebug.mak 
#	cd linad99-threadsafe; MAKE "OPTIONS=-Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -H -Hc  -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 

all:
	cd nh99; MAKE "OPTIONS= "  -f bdebug.mak 
	cd linad99; MAKE "OPTIONS= -DSAFE_ALL"  -f bdebug.mak 
	cd tools99; MAKE "OPTIONS= "  -f bdebug.mak 
#	cd linad99-threadsafe; MAKE "OPTIONS=-Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -H -Hc  -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 

pvmall:
	cd admbthreads; MAKE "OPTIONS= -H -Hc -H=precomp -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd linad99; MAKE "OPTIONS= -H -Hc -H=precomp -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd tools99; MAKE "OPTIONS=  -DUSE_ADPVM " -f bdebug.mak 
	cd nh99; MAKE "OPTIONS= -DUSE_ADPVM " -f bdebug.mak 
	cd newdd; MAKE "OPTIONS= -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd newquad; MAKE "OPTIONS= -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 

clean:
	cd linad99; MAKE -f bdebug.mak  clean
	cd tools99; MAKE -f bdebug.mak   clean
	cd nh99; MAKE -f bdebug.mak   clean

linad99-pvmall:
	cd linad99; MAKE "OPTIONS=-DUSE_ADPVM" -f bdebug.mak 

threadpvmall:
	cd newdd; MAKE "OPTIONS=-Ij:/admb07/linad99-threadsafe -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd newquad; MAKE "OPTIONS=-Ij:/admb07/linad99-threadsafe -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd linad99-threadsafe; MAKE "OPTIONS=-Ij:/admb07/linad99-threadsafe -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd admbthreads; MAKE "OPTIONS=-Ij:/admb07/linad99-threadsafe  -DTHREAD_SAFE-H -Hc -H=precomp -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd tools99; MAKE "OPTIONS=-Ij:/admb07/linad99-threadsafe  -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DUSE_ADPVM " -f bdebug.mak 
	cd nh99; MAKE "OPTIONS=-Ij:/admb07/linad99-threadsafe -Ie:/pthreads/pthreads.2 -DTHREAD_SAFE -DUSE_ADPVM " -f bdebug.mak 

clean:
	cd admbthreads; MAKE -f bdebug.mak  clean
	cd newdd; MAKE -f bdebug.mak  clean
	cd newquad; MAKE -f bdebug.mak  clean
	cd linad99; MAKE -f bdebug.mak  clean
	cd tools99; MAKE -f bdebug.mak   clean
	cd nh99; MAKE -f bdebug.mak   clean

threadclean:
	cd linad99-threadsafe; MAKE "OPTIONS=-DTHREAD_SAFE -H -Hc -H=precomp -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak  clean
	cd admbthreads; MAKE "OPTIONS= -DTHREAD_SAFE-H -Hc -H=precomp -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak   clean
	cd tools99; MAKE "OPTIONS= -DTHREAD_SAFE -DUSE_ADPVM " -f bdebug.mak   clean
	cd nh99; MAKE "OPTIONS=-DTHREAD_SAFE -DUSE_ADPVM " -f bdebug.mak   clean


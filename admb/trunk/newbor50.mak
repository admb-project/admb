
all:
	cd nh99; MAKE "OPTIONS= "  -f bdebug.mak 
	cd linad99; MAKE "OPTIONS= -DSAFE_ALL"  -f bdebug.mak 
	cd tools99; MAKE "OPTIONS= "  -f bdebug.mak 

pvmall:
	cd linad99; MAKE "OPTIONS= -DSAFE_ALL  -DUSE_ADPVM" -f bdebug.mak 
	cd tools99; MAKE "OPTIONS=  -DUSE_ADPVM " -f bdebug.mak 
	cd nh99; MAKE "OPTIONS= -DUSE_ADPVM " -f bdebug.mak 

clean:
	cd linad99; MAKE -f bdebug.mak  clean
	cd tools99; MAKE -f bdebug.mak   clean
	cd nh99; MAKE -f bdebug.mak   clean

linad99-pvmall:
	cd linad99; MAKE "OPTIONS=-DUSE_ADPVM" -f bdebug.mak 

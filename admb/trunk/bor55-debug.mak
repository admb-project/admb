
all:
	cd linad99; MAKE -f bdebug55.mak 
	cd tools99; MAKE -f bdebug55.mak 
	cd nh99; MAKE -f bdebug55.mak 

clean:
	cd linad99; MAKE -f bdebug55.mak  clean
	cd tools99; MAKE -f bdebug55.mak   clean
	cd nh99; MAKE -f bdebug55.mak   clean


all:
	cd df1b2-separable; MAKE "OPTIONS=+c:\bc5\bor50lpdex.cfg -D__MINI_MAX__  -H=e:/temp/precomp1"  -f bdebug-laplace.mak 
	cd linad99; MAKE "OPTIONS=+c:\bc5\bor50lpdex.cfg -I../sparse -D__MINI_MAX__ " -f bdebug-laplace.mak 
	cd tools99; MAKE "OPTIONS=+c:\bc5\bor50lpdex.cfg -D__MINI_MAX__ " -f bdebug-laplace.mak 
	cd nh99; MAKE "OPTIONS=+c:\bc5\bor50lpdex.cfg -D__MINI_MAX__ -H=e:/temp/precomp2  " -f bdebug-laplace.mak 

redemoall:
	cd linad99; MAKE "OPTIONS=-DADMB_REDEMO" -f bdebug-laplace.mak 
	cd df1b2-separable; MAKE "OPTIONS=-DADMB_REDEMO" -f bdebug-laplace.mak 
	cd tools99; MAKE "OPTIONS=-DADMB_REDEMO" -f bdebug-laplace.mak 
	cd nh99; MAKE "OPTIONS=-DADMB_REDEMO" -f bdebug-laplace.mak 

atlasall:
	cd linad99; MAKE -f bdebug-laplace.mak 
	cd df1b2-separable; MAKE OPTIONS=-DUSE_ATLAS -f bdebug-laplace.mak 
	cd tools99; MAKE -f bdebug-laplace.mak 
	cd nh99; MAKE -f bdebug-laplace.mak 

clean:
	cd linad99; MAKE -f bdebug-laplace.mak  clean
	cd df1b2-separable; MAKE -f bdebug-laplace.mak clean
	cd tools99; MAKE -f bdebug-laplace.mak   clean
	cd nh99; MAKE -f bdebug-laplace.mak   clean

df1b2clean:
	cd df1b2-separable; MAKE -f bdebug-laplace.mak clean

threadsafe:
	cd linad99-threadsafe; MAKE "OPTIONS=+c:\bc5\bor50lpdex.cfg -D__MINI_MAX__ " -f bdebug-laplace.mak 

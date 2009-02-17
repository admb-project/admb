all:
	cd linad99; MAKE "CC=j:/mingw342/bin/gcc" -f optming-gcc32.mak 
	cd linad99; MAKE -f safming-gcc32.mak 
	cd tools99; MAKE -f optming-gcc32.mak 
	cd nh99; MAKE -f optming-gcc32.mak 

clean:
	cd linad99; MAKE -f optming-gcc32.mak  clean
	cd linad99; MAKE -f safming-gcc32.mak   clean
	cd tools99; MAKE -f optming-gcc32.mak   clean
	cd nh99; MAKE -f optming-gcc32.mak   clean
	cd df1b2-separable; MAKE LIBPATH=ming-demo-gcc342s  -f safming-gcc32.mak  clean

	cd df1b2-separable; MAKE LIBPATH=ming-demo-gcc342o  -f optming-gcc32.mak  clean

lp342all:
	cd nh99; MAKE DISKDIR=h:/gcc342-ming "OPTIONS =  -DUSE_LAPLACE -Ij:/mingw342/include  -I../df1b2-separable" LIBPATH=ming342o  CC=j:/mingw342/bin/mingw32-c++.exe -f optming-gcc32.mak  all
	cd linad99; MAKE DISKDIR=h:/gcc342-ming "OPTIONS =   -DUSE_LAPLACE -Ij:/mingw342/include  " LIBPATH=ming342o  CC=j:/mingw342/bin/mingw32-c++.exe -f optming-gcc32.mak 
	cd linad99; MAKE DISKDIR=h:/gcc342-ming "OPTIONS =  -DUSE_LAPLACE -Ij:/mingw342/include  " LIBPATH=ming342s  CC=j:/mingw342/bin/mingw32-c++.exe -f safming-gcc32.mak 
	cd tools99; MAKE DISKDIR=h:/gcc342-ming "OPTIONS =  -DUSE_LAPLACE -Ij:/mingw342/include -I../df1b2-separable" LIBPATH=ming342o  CC=j:/mingw342/bin/mingw32-c++.exe -f optming-gcc32.mak 
	cd df1b2-separable; MAKE DISKDIR=h:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw342/include  -I../linad99" LIBNAME=libdf1b2s.a LIBPATH=ming342s  CC=j:/mingw342/bin/mingw32-c++.exe -f safming-gcc32.mak 
	cd df1b2-separable; MAKE DISKDIR=h:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw342/include  -I../linad99" LIBNAME=libdf1b2o.a LIBPATH=ming342o  CC=j:/mingw342/bin/mingw32-c++.exe -f optming-gcc32.mak 

lp345all:
	cd nh99; MAKE DISKDIR=h:/gcc345-ming "OPTIONS =  -DUSE_LAPLACE -Ie:/mingw345/include  -I../df1b2-separable" LIBPATH=ming345o  CC=e:/mingw345/bin/mingw32-c++.exe -f optming-gcc32.mak  all
	cd linad99; MAKE DISKDIR=h:/gcc345-ming "OPTIONS =   -DUSE_LAPLACE -Ie:/mingw345/include  " LIBPATH=ming345o  CC=e:/mingw345/bin/mingw32-c++.exe -f optming-gcc32.mak 
	cd linad99; MAKE DISKDIR=h:/gcc345-ming "OPTIONS =  -DUSE_LAPLACE -Ie:/mingw345/include  " LIBPATH=ming345s  CC=e:/mingw345/bin/mingw32-c++.exe -f safming-gcc32.mak 
	cd tools99; MAKE DISKDIR=h:/gcc345-ming "OPTIONS =  -DUSE_LAPLACE -Ie:/mingw345/include -I../df1b2-separable" LIBPATH=ming345o  CC=e:/mingw345/bin/mingw32-c++.exe -f optming-gcc32.mak 
	cd df1b2-separable; MAKE DISKDIR=h:/gcc345-ming "OPTIONS = -DUSE_LAPLACE -Ie:/mingw345/include  -I../linad99" LIBNAME=libdf1b2s.a LIBPATH=ming345s  CC=e:/mingw345/bin/mingw32-c++.exe -f safming-gcc32.mak 
	cd df1b2-separable; MAKE DISKDIR=h:/gcc345-ming "OPTIONS = -DUSE_LAPLACE -Ie:/mingw345/include  -I../linad99" LIBNAME=libdf1b2o.a LIBPATH=ming345o  CC=e:/mingw345/bin/mingw32-c++.exe -f optming-gcc32.mak 

demolp342all:
	cd tools99; MAKE DISKDIR=h:/gcc342-demo-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw342/include -DADMB_REDEMO -I../df1b2-separable" LIBPATH=ming-demo-gcc342o  CC=j:/mingw342/bin/mingw32-c++.exe -f optming-gcc32.mak 
	cd df1b2-separable; MAKE DISKDIR=h:/gcc342-demo-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw342/include -DADMB_REDEMO -I../linad99" LIBNAME=libdf1b2s.a LIBPATH=ming-demo-gcc342s  CC=j:/mingw342/bin/mingw32-c++.exe -f safming-gcc32.mak 
	cd df1b2-separable; MAKE DISKDIR=h:/gcc342-demo-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw342/include -DADMB_REDEMO -I../linad99" LIBNAME=libdf1b2o.a LIBPATH=ming-demo-gcc342o  CC=j:/mingw342/bin/mingw32-c++.exe -f optming-gcc32.mak 
	cd nh99; MAKE DISKDIR=h:/gcc342-demo-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw342/include -DADMB_REDEMO -I../df1b2-separable" LIBPATH=ming-demo-gcc342o  CC=j:/mingw342/bin/mingw32-c++.exe -f optming-gcc32.mak 
	cd linad99; MAKE DISKDIR=h:/gcc342-demo-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw342/include -DADMB_REDEMO " LIBPATH=ming-demo-gcc342s CC=j:/mingw342/bin/mingw32-c++.exe -f safming-gcc32.mak 
	cd linad99; MAKE DISKDIR=h:/gcc342-demo-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw342/include -DADMB_REDEMO " LIBPATH=ming-demo-gcc342o CC=j:/mingw342/bin/mingw32-c++.exe -f optming-gcc32.mak 

demolpall:
	cd linad99; MAKE "OPTIONS = -DUSE_LAPLACE -DADMB_REDEMO " LIBPATH=ming-demo-gcc323o  -f optming-gcc32.mak 
#	cd linad99; MAKE -f safming-gcc32.mak 
#	cd tools99; MAKE -f optming-gcc32.mak 
#	cd nh99; MAKE -f optming-gcc32.mak 

demolp342clean:
	cd tools99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include -DADMB_REDEMO -I../df1b2-separable" LIBPATH=ming-demo-gcc342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak  clean
	cd df1b2-separable; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include -DADMB_REDEMO -I../linad99" LIBNAME=libdf1b2s.a LIBPATH=ming-demo-gcc342s  CC=j:/mingw32/bin/mingw32-c++.exe -f safming-gcc32.mak   clean
	cd df1b2-separable; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include -DADMB_REDEMO -I../linad99" LIBNAME=libdf1b2o.a LIBPATH=ming-demo-gcc342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean
	cd nh99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include -DADMB_REDEMO -I../df1b2-separable" LIBPATH=ming-demo-gcc342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean
	cd linad99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include -DADMB_REDEMO " LIBPATH=ming-demo-gcc342s  CC=j:/mingw32/bin/mingw32-c++.exe -f safming-gcc32.mak   clean
	cd linad99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include -DADMB_REDEMO " LIBPATH=ming-demo-gcc342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean

hanscopy:
	- cd h:/gcc342-ming ; rm *.zip ; \
        cfind . |  zip -@ ad_build ; \
        scp ad_build.zip root@192.168.1.1:/home/skaug/real-experimental/mingw342

lp342clean:
	cd tools99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include -I../df1b2-separable" LIBPATH=ming342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak  clean
	cd df1b2-separable; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  -I../linad99" LIBNAME=libdf1b2s.a LIBPATH=ming342s  CC=j:/mingw32/bin/mingw32-c++.exe -f safming-gcc32.mak   clean
	cd df1b2-separable; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  -I../linad99" LIBNAME=libdf1b2o.a LIBPATH=ming342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean
	cd nh99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  -I../df1b2-separable" LIBPATH=ming342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean
	cd linad99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  " LIBPATH=ming342s  CC=j:/mingw32/bin/mingw32-c++.exe -f safming-gcc32.mak   clean
	cd linad99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  " LIBPATH=ming342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean

lp345clean:
	cd tools99; MAKE DISKDIR=e:/gcc345-ming "OPTIONS = -DUSE_LAPLACE -Ie:/mingw32/include -I../df1b2-separable" LIBPATH=ming345o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak  clean
	cd df1b2-separable; MAKE DISKDIR=e:/gcc345-ming "OPTIONS = -DUSE_LAPLACE -Ie:/mingw32/include  -I../linad99" LIBNAME=libdf1b2s.a LIBPATH=ming345s  CC=j:/mingw32/bin/mingw32-c++.exe -f safming-gcc32.mak   clean
	cd df1b2-separable; MAKE DISKDIR=e:/gcc345-ming "OPTIONS = -DUSE_LAPLACE -Ie:/mingw32/include  -I../linad99" LIBNAME=libdf1b2o.a LIBPATH=ming345o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean
	cd nh99; MAKE DISKDIR=e:/gcc345-ming "OPTIONS = -DUSE_LAPLACE -Ie:/mingw32/include  -I../df1b2-separable" LIBPATH=ming345o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean
	cd linad99; MAKE DISKDIR=e:/gcc345-ming "OPTIONS = -DUSE_LAPLACE -Ie:/mingw32/include  " LIBPATH=ming345s  CC=j:/mingw32/bin/mingw32-c++.exe -f safming-gcc32.mak   clean
	cd linad99; MAKE DISKDIR=e:/gcc345-ming "OPTIONS = -DUSE_LAPLACE -Ie:/mingw32/include  " LIBPATH=ming345o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean

test:
	cd nh99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  -I../df1b2-separable" LIBPATH=ming-gcc342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak  all

smallclean:
	cd df1b2-separable; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  -I../linad99" LIBNAME=libdf1b2s.a LIBPATH=ming342s  CC=j:/mingw32/bin/mingw32-c++.exe -f safming-gcc32.mak   clean
	cd df1b2-separable; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  -I../linad99" LIBNAME=libdf1b2o.a LIBPATH=ming342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean
	cd nh99; MAKE DISKDIR=j:/gcc342-ming "OPTIONS = -DUSE_LAPLACE -Ij:/mingw32/include  -I../df1b2-separable" LIBPATH=ming342o  CC=j:/mingw32/bin/mingw32-c++.exe -f optming-gcc32.mak   clean


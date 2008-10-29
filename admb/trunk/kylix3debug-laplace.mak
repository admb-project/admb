
all:
	cd tools99; ${MAKE} DISKDIR=f:\kylix3-rh8 CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak "FLAGS = -Dlinux -I../linad99 -I../nh99 -I/usr/i386-glibc21-linux/include -I/home/dave/kylix3/include/vcl -I/home/dave/kylix3/include/stlport -I/home/dave/kylix3/include  -v -DUSE_LAPLACE  -Od -r- -Vd -Hc -DSAFE_ALL -DWIN32 -I. -5 -c " LIBPATH=k3odlp 
	cd df1b2-separable; ${MAKE} "FLAGS = -DUSE_LAPLACE  -Dlinux -I../linad99 -I../nh99 -I../tools99 -I/usr/i386-glibc21-linux/include -I/home/dave/kylix3/include/vcl -I/home/dave/kylix3/include/stlport -I/home/dave/kylix3/include -v -Od -r- -Vd -Hc -DSAFE_ALL -DWIN32 -I. -5 -c" DISKDIR=f:\kylix3-rh8 LIBPATH=k3odlp CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak 
	cd linad99; ${MAKE} "FLAGS = -Dlinux -I../nh99 -I../tools99 -I/usr/i386-glibc21-linux/include -I/home/dave/kylix3/include/vcl -I/home/dave/kylix3/include/stlport -I/home/dave/kylix3/include -v -DUSE_LAPLACE  -Od -r- -Vd -Hc -DSAFE_ALL -DWIN32 -I. -5 -c" DISKDIR=f:\kylix3-rh8 LIBPATH=k3odlp CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak 
	cd nh99; ${MAKE} DISKDIR=f:\kylix3-rh8 LIBPATH=k3odlp CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak "FLAGS = -Dlinux -I../df1b2-separable -I/home/dave/kylix3/include/stlport -I../tools99 -I../linad99 -I/usr/i386-glibc21-linux/include -I/home/dave/kylix3/include -v -DUSE_LAPLACE -Od -r- -Vd -Hc -DSAFE_ALL -DWIN32 -I. -5 -c" 


atlasall:
	cd linad99; ${MAKE} LIBPATH=k3odlp CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak "FLAGS = -I/home/dave/kylix3/include -v -DUSE_LAPLACE -DUSE_ATLAS -DUSE_ADPVM -Od -r- -Vd -Hc -DSAFE_ALL -DWIN32 -I. -5 -c" 
	cd df1b2-separable; ${MAKE} LIBPATH=k3odlp OPTIONS=-DUSE_ATLAS CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak "FLAGS = -I/home/dave/kylix3/include -v -DUSE_LAPLACE -DUSE_ATLAS -DUSE_ADPVM -Od -r- -Vd -Hc -DSAFE_ALL -DWIN32 -I. -5 -c" 
	cd tools99; ${MAKE} LIBPATH=k3odlp CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak "FLAGS = -I/home/dave/kylix3/include -v -DUSE_LAPLACE -DUSE_ATLAS -DUSE_ADPVM -Od -r- -Vd -Hc -DSAFE_ALL -DWIN32 -I. -5 -c" 
	cd nh99; ${MAKE} LIBPATH=k3odlp CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak"FLAGS = -I/home/dave/kylix3/include -v -DUSE_LAPLACE -DUSE_ATLAS -DUSE_ADPVM -Od -r- -Vd -Hc -DSAFE_ALL -DWIN32 -I. -5 -c"  

clean:
	cd linad99; ${MAKE} LIBPATH=k3odlp DISKDIR=f:\kylix3-rh8 CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak  clean
	cd df1b2-separable; ${MAKE} LIBPATH=k3odlp DISKDIR=f:\kylix3-rh8 CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak clean
	cd tools99; ${MAKE} LIBPATH=k3odlp DISKDIR=f:\kylix3-rh8 CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak   clean
	cd nh99; ${MAKE} LIBPATH=k3odlp DISKDIR=f:\kylix3-rh8 CC=/home/dave/kylix3/bin/bc++ -f kylix3debug-laplace.mak   clean

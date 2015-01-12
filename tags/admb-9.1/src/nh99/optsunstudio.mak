
#macros for making optimized library for DJGPP
CC = gcc
LL = tli3
FLAGS1 = ${OPTIONS} -w -I/usr/src/ATLAS/include ${PVMOPTION} -g -DUSE_LAPLACE -fpermissive -O3 -c -I../df1b2-separable -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB -Dlinux -DADMB_VERSION=${ADMB_VERSION}

FLAGS =  ${OPTIONS} -I/usr/src/ATLAS/include ${PVMOPTION} -w -DUSE_LAPLACE -fpermissive -O3 -c -I../df1b2-separable -I. -I../linad99 -I../tools99 -D__SPDLL__ \
-D__GNUDOS__ -DOPT_LIB -Dlinux -DADMB_VERSION=${ADMB_VERSION}
LIBPATH =gcc32-rh8olp
STUBPATH =gcc32-rh8olp-stub
STUBNAME = libdf1b2stub.a
LIBNAME = libadmod.a
LIBDIR = lib
BINDIR = bin
INCLDIR= include
DISKDIR=/g/g32-rh8-laplace
DRIVECHANGE=fff.bat
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
.PHONY: admodel.cpp

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(filter-out dfqromb.obj, $(OBJ0)) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

%.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

all: $(LIBPATH)/$(LIBNAME)  tpl2cpp disk  

df1b2stub:
	$(CC) $(FLAGS) -o $(STUBPATH)/df1b2stub.o df1b2stub.cpp
	 cd $(STUBPATH); ar -rs ${STUBNAME}  df1b2stub.o

tpl2cpp.c: tpl2cpp.lex
	flex tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp.c

tpl2cpp: tpl2cpp.c
	gcc tpl2cpp.c -o $@

disk: $(LIBPATH)/$(LIBNAME)  df1b2stub tpl2cpp
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp admodel.h $(DISKDIR)/$(INCLDIR)
	cp spcomm.h $(DISKDIR)/$(INCLDIR)
	cp adsplus.h $(DISKDIR)/$(INCLDIR)
	cp newredef.h $(DISKDIR)/$(INCLDIR)
	cp s.h $(DISKDIR)/$(INCLDIR)
	- cp tpl2cpp $(DISKDIR)/$(BINDIR)     
	cp sed* $(DISKDIR)/$(BINDIR)     
	cp $(STUBPATH)/${STUBNAME} $(DISKDIR)/$(LIBDIR)

clean:
	- rm tpl2cpp ;  cd $(LIBPATH) ; rm *.obj ; rm *.o ;  rm *.a

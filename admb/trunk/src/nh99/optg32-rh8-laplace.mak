
#macros for making optimized library for DJGPP
CC = gcc
LL = tli3

FLAGS =  ${OPTIONS} -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-comment -Wno-parentheses -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -fpermissive -O3 -c -I../df1b2-separable -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -DOPT_LIB -Dlinux -DADMB_VERSION=${ADMB_VERSION}

FLAGS1 =  ${OPTIONS} -w ${PVMOPTION} -DUSE_LAPLACE -fpermissive -O3 -c -I../df1b2-separable -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -DOPT_LIB -Dlinux -DADMB_VERSION=${ADMB_VERSION}

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

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

model52.obj hybmcmc.obj randeff.obj cnstrs.obj xmodelm3.obj xxmcmc.obj lmnewton.obj: %.obj: %.cpp
	$(CC) $(FLAGS1)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(filter-out model52.obj hybmcmc.obj randeff.obj cnstrs.obj xmodelm3.obj xxmcmc.obj lmnewton.obj, $(OBJ0)): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)/$*.obj

all: $(LIBPATH)/$(LIBNAME)  tpl2cpp disk  

df1b2stub:
	$(CC) $(FLAGS) -o $(STUBPATH)/df1b2stub.o df1b2stub.cpp
	 cd $(STUBPATH); ar -rs ${STUBNAME}  df1b2stub.o

tpl2cpp.c: tpl2cpp.lex
	flex -w tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp.c

tpl2cpp: tpl2cpp.c
	gcc -Wno-format tpl2cpp.c -o $@

disk: $(LIBPATH)/$(LIBNAME)  df1b2stub tpl2cpp
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp admodel.h $(DISKDIR)/$(INCLDIR)
	cp spcomm.h $(DISKDIR)/$(INCLDIR)
	cp adsplus.h $(DISKDIR)/$(INCLDIR)
	cp newredef.h $(DISKDIR)/$(INCLDIR)
	cp s.h $(DISKDIR)/$(INCLDIR)
	- cp tpl2cpp tpl2cpp.exe $(DISKDIR)/$(BINDIR)     
	cp sed* $(DISKDIR)/$(BINDIR)     
	cp $(STUBPATH)/${STUBNAME} $(DISKDIR)/$(LIBDIR)

clean:
	- rm tpl2cpp ;  cd $(LIBPATH) ; rm *.obj ; rm *.o ;  rm *.a

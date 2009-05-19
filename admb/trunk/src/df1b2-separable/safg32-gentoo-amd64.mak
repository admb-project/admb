


#macros for making optimized library for DJGPP
CC = gcc
LL = tlib
FLAGS1 = ${OPTIONS} -m64 -fpermissive -O3 -c -I. -I../linad99 -I../tools99  -DSAFE_ALL \
-D__GNUDOS__  -Dlinux
FLAGS = ${OPTIONS} -w -m64 -fpermissive -O3 -c -I. -I../linad99 -I../tools99 -I../nh99  \
-D__GNUDOS__  -Dlinux -DSAFE_ALL
LIBPATH =gcc343-amd64s
LIBNAME = libdf1b2s.a
LIBDIR = lib
BINDIR = bin
INCLDIR= include
DISKDIR= /tmp/g32-gentoo
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
.PHONY: tpl2cpp

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) tpl2cpp 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

admodel.obj : admodel.cpp
	$(CC) $(FLAGS1)  $<
	mv $*.o $(LIBPATH)/$*.obj

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.o $(LIBPATH)/$*.obj


all: $(LIBPATH)/$(LIBNAME)  tpl2cpp disk

tpl2rem:
	gcc -I. -DUX tpl2rem.c -otpl2rem

disk: 
	cp adpool.h adrndeff.h df1b2fun.h smartbuf.h $(DISKDIR)/$(INCLUDEDIR)
	gcc -I. -DUX tpl2rem.c -otpl2rem
	cp tpl2rem.exe $(DISKDIR)/$(BINDIR)/tpl2rem.exe
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- rm tpl2cpp ;  cd $(LIBPATH) ; rm *.obj ; rm *.o ;  rm *.a

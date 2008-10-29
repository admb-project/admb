#macros for making optimized library for DJGPP
CC = gcc
LL = tlib

FLAGS = -v -x c++ -O3 -c -I. -I../linad99 -I ../tools99 -fpermissive -D __GNUDOS__ -D OPT_LIB

#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = cyg-gcc295o
LIBNAME = libadmod.a
LIBDIR = lib
INCLDIR= include
DISKDIR= f:/gcc2953-cygwin
BINDIR= bin
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp admodel.h $(DISKDIR)/$(INCLDIR)
	cp tpl2cpp.exe $(DISKDIR)/$(BINDIR)/tpl2cpp.exe


#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

all: disk $(LIBPATH)/$(LIBNAME) 

disk: 
	cp admodel.h $(DISKDIR)/$(INCLUDEDIR)
	cp adsplus.h $(DISKDIR)/$(INCLUDEDIR)
	cp spcomm.h $(DISKDIR)/$(INCLUDEDIR)
	cp s.h $(DISKDIR)/$(INCLUDEDIR)
	cp newredef.h $(DISKDIR)/$(INCLUDEDIR)
	$(CC) mylex.c  
	cp mylex.exe $(DISKDIR)/$(BINDIR)/tpl2cpp.exe
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

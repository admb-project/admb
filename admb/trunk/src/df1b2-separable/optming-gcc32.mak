#macros for making optimized library for DJGPP

CC = /cygdrive/f/gcc323-mingw32/bin/gcc
LL = tlib

FLAGS = ${OPTIONS} -Dlinux -fpermissive -x c++ -O3 -c -I. -I../nh99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

FLAGS1 = -g ${OPTIONS} -Dlinux -fpermissive -x c++ -O3 -c -I. -I../nh99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = ming-gcc323o
LIBNAME = libdf1b2o.a
LIBDIR = lib
INCLDIR= include
DISKDIR= f:/gcc323-ming
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
	- cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	- cp *.h $(DISKDIR)/$(INCLDIR)
	- cp *.hpp $(DISKDIR)/$(INCLDIR)
	- cp sed* $(DISKDIR)/$(BINDIR)
	cp df1b2fun.h $(DISKDIR)/$(INCLDIR)
	cp adpool.h $(DISKDIR)/$(INCLDIR)
	cp adrndeff.h $(DISKDIR)/$(INCLDIR)
	cp df1b2fnl.h $(DISKDIR)/$(INCLDIR)
	cp df3fun.h $(DISKDIR)/$(INCLDIR)
	cp df1b2loc.h $(DISKDIR)/$(INCLDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 


#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3
$(LIBPATH)/$(LIBNAME) :  $(OBJ0)  $(OBJ1)  $(OBJ2)  $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)


$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

fvar1.obj: fvar1.cpp
	$(CC) $(FLAGS1) -o$(LIBPATH)/$*.obj $<

all: disk $(LIBPATH)/$(LIBNAME) 



clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

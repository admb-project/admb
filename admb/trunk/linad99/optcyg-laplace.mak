
#macros for making optimized library for DJGPP
CC = gcc
LL = tlib

FLAGS = -DUSE_LAPLACE -O3 -pg -g -O3 -Dlinux -fpermissive -x c++ -c -I. -I../nh99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = cyg-gcc295olp
LIBNAME = libado.a
LIBDIR = lib
INCLDIR= include
DISKDIR= g:/cyg-g2953-laplace
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
	cp *.h $(DISKDIR)/$(INCLDIR)
	cp *.hpp $(DISKDIR)/$(INCLDIR)


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

all: disk $(LIBPATH)/$(LIBNAME) 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

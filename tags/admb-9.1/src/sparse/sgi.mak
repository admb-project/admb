
#macros for making optimized library for DJGPP
CC = CC
LL = tlib
FLAGS = -w -x c++ -D__ADSGI__ -Dlinux -O2 -c -I. -I../linad99 -I../tools99 -D__GNUDOS__ -DOPT_LIB
#FLAGS = -x c++ -O3 -c -D __GNUDOS__ -D OPT_LIB
LIBPATH = sgio
LIBNAME = libadt.a
LIBDIR = lib
INCLUDEDIR= include
DISKDIR= d:\gccdisk
vpath %.o $(LIBPATH)$

.SUFFIXES: .o .cpp

.PHONY: t0
.PHONY: t1
.PHONY: t2
.PHONY: t3
.PHONY: disk
include objects.lst

disk: $(LIBPATH)/$(LIBNAME) 

#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.o

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)

$(OBJ0): %.o: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)

$(OBJ1): %.o: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)

$(OBJ2): %.o: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)

$(OBJ3): %.o: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.o $(LIBPATH)


all: $(LIBPATH)/$(LIBNAME) 




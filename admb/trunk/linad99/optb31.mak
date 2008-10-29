



#macros for making safe library for DJGPP

CC = bcc

LL = tlib

FLAGS =  -ml -f287 -3 -DOPT_LIB -O2 -c -o$(LIBPATH)/$*.obj

LIBPATH = bc31o

LIBNAME =  admodel.lib

vpath %.obj $(LIBPATH)$



.SUFFIXES: .obj .cpp



.PHONY: t0

.PHONY: t1

.PHONY: t2

.PHONY: t3

include objects.lst



#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3 

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 



t0: objects.lst  $(OBJ0) 



t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1) 



t2: objects.lst  $(OBJ2)



t3: objects.lst  $(OBJ3)



.cpp.obj: 

	$(CC) $(FLAGS) $<




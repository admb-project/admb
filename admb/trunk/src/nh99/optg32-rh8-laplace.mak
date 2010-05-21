.PHONY: disk
CC = g++

CFLAGS=-O3
ifdef DEBUG
CFLAGS=-g
endif

FLAGS:=-c $(CFLAGS) ${OPTIONS} -fno-for-scope -Wall -Wno-conversion -Wno-non-virtual-dtor -Wno-comment -Wno-parentheses -Wno-strict-aliasing -Wno-write-strings -Wno-unused-function -Wno-unknown-pragmas -Wno-sign-compare -Wno-missing-braces -Wno-cast-qual -Wno-uninitialized -Wno-reorder -Wno-deprecated -Wno-unused-label -Wno-unused-variable ${PVMOPTION} -DUSE_LAPLACE -fpermissive -I../df1b2-separable -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -DOPT_LIB -Dlinux

FLAGS1:=-c $(CFLAGS) ${OPTIONS} -w ${PVMOPTION} -DUSE_LAPLACE -fpermissive -I../df1b2-separable -I. -I../linad99 -I../tools99 -D__SPDLL__ -D__GNUDOS__ -DOPT_LIB -Dlinux

ifneq ($(strip $(ADMB_VERSION)),)
  FLAGS+=-DADMB_VERSION=${ADMB_VERSION}
  FLAGS1+=-DADMB_VERSION=${ADMB_VERSION}
endif

ifneq ($(strip $(ADMB_REVISION)),)
  ifneq ('$(strip $(ADMB_REVISION))', 'exported')
    FLAGS+=-DADMB_REVISION=${ADMB_REVISION}
    FLAGS1+=-DADMB_REVISION=${ADMB_REVISION}
  endif
endif

LIBPATH =gcc32-rh8olp
STUBPATH =gcc32-rh8olp-stub
STUBNAME = libdf1b2stub.a
LIBNAME = libadmod.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp


include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

model52.obj hybmcmc.obj randeff.obj cnstrs.obj xmodelm3.obj xxmcmc.obj lmnewton.obj: %.obj: %.cpp
	$(CC) $(FLAGS1)  $< -o $(LIBPATH)/$*.obj

$(filter-out model52.obj hybmcmc.obj randeff.obj cnstrs.obj xmodelm3.obj xxmcmc.obj lmnewton.obj, $(OBJ0)): %.obj: %.cpp
	$(CC) $(FLAGS)  $< -o $(LIBPATH)/$*.obj

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $< -o $(LIBPATH)/$*.obj

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) $< -o $(LIBPATH)/$*.obj

all: $(LIBPATH)/$(LIBNAME)  tpl2cpp disk  

df1b2stub:
	$(CC) $(FLAGS) -o $(STUBPATH)/df1b2stub.o df1b2stub.cpp
	ar -rs $(STUBPATH)/${STUBNAME} $(STUBPATH)/df1b2stub.o

tpl2cpp.c: tpl2cpp.lex
	flex -w tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp.c

tpl2cpp: tpl2cpp.c
	gcc -Wno-format tpl2cpp.c -o $@

disk: $(LIBPATH)/$(LIBNAME)  df1b2stub tpl2cpp
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp admodel.h $(DISKDIR)/include
	cp spcomm.h $(DISKDIR)/include
	cp adsplus.h $(DISKDIR)/include
	cp newredef.h $(DISKDIR)/include
	cp s.h $(DISKDIR)/include
	cp tpl2cpp $(DISKDIR)/bin
	cp sed* $(DISKDIR)/bin
	cp $(STUBPATH)/${STUBNAME} $(DISKDIR)/lib

clean:
	rm -f tpl2cpp
	rm -rvf $(LIBPATH)

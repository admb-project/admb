#macros for making optimized library for DJGPP
CC = /cygdrive/f/gcc323-mingw32/bin/gcc

LL = tlib

FLAGS = ${OPTIONS} -Dlinux -fpermissive -x c++ -O3 -c -I. -I../linad99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

FLAGS1 = ${OPTIONS} -g -Dlinux -fpermissive -x c++ -O3 -c -I. -I../linad99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = ming-gcc323o
STUBLIBPATH = ming-gcc323o-stub
LIBNAME = libadmod.a
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
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp *.h $(DISKDIR)/$(INCLDIR)
	cp *.hpp $(DISKDIR)/$(INCLDIR)


#$(LIBPATH)/$(LIBNAME) : t0 t1 t2 t3
$(LIBPATH)/$(LIBNAME) :  $(OBJ0)  $(OBJ1)  $(OBJ2)  $(OBJ3) 
	- rm $(LIBPATH)/$(LIBNAME) 
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

admodel.obj: admodel.cpp

df1b2stub.obj: df1b2stub.cpp
	$(CC) $(FLAGS) -o$(STUBLIBPATH)/$*.obj $<

all: disk $(LIBPATH)/$(LIBNAME) libdf1b2stub.a 


disk: $(LIBPATH)/$(LIBNAME) 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp admodel.h $(DISKDIR)/$(INCLDIR)
	cp spcomm.h $(DISKDIR)/$(INCLDIR)
	cp adsplus.h $(DISKDIR)/$(INCLDIR)
	cp newredef.h $(DISKDIR)/$(INCLDIR)
	cp s.h $(DISKDIR)/$(INCLDIR)
	cp tpl2cpp.exe $(DISKDIR)/$(BINDIR)     

libdf1b2stub.a:  df1b2stub.obj
	cd ${STUBLIBPATH} ; ar -rs libdf1b2stub.a df1b2stub.obj ; \
	cp libdf1b2stub.a $(DISKDIR)/$(LIBDIR) ; \
#	rm df1b2stub.obj ; \
#	rm libdf1b2stub.a

df1b2.obj: admodel.cpp
	$(CC) $(FLAGS1) -o$(LIBPATH)/$*.obj $<
clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

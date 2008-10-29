#macros for making optimized library for DJGPP

CC = /cygdrive/f/gcc323-mingw32/bin/gcc
LL = tlib

FLAGS = ${OPTIONS} -Dlinux -fpermissive -x c++ -O3 -c -I. -I../df1b2-separable -I../nh99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

FLAGS1 = -g ${OPTIONS} -Dlinux -fpermissive -x c++ -O3 -c -I../df1b2-separable -I. -I../nh99 -I../tools99 -D __GNUDOS__ -D OPT_LIB

#FLAGS = -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB
LIBPATH = ming-gcc323o
LIBNAME = libado.a
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
$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  $(OBJSPARSE)
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

t0: objects.lst  $(OBJ0)

t1: objects.lst  $(SPECIAL_OBJ) $(OBJ1)

t2: objects.lst  $(OBJ2)

t3: objects.lst  $(OBJ3)

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<


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


disk: 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)  ; \
	cp adpvm2.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx001.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx001a.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx002.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx003.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx004.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx005.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx005a.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx006.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx007.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx008.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx009.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx010.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx011.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx012.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx013.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx014.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx015.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx016.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx017.h $(DISKDIR)/$(INCLDIR) ; \
	cp insx018.h $(DISKDIR)/$(INCLDIR) ; \
	cp fvar.hpp $(DISKDIR)/$(INCLDIR) ; \
	cp d4arr.hpp $(DISKDIR)/$(INCLDIR) ; \
	cp dfpool.h $(DISKDIR)/$(INCLDIR) ; \

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

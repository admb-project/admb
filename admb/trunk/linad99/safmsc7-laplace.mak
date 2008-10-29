

#macros for making optimized library for MS         
CC = g:/vc7/bin/cl
LL = tlib
LIBPATH = msc7slp
FLAGS = ${OPTIONS} ${PVMOPTION} -Ik:/temp/ATLAS/include /EHsc -DUSE_LAPLACE -DWIN32 /c -I. -I../df1b2-separable -I../nh99 -I../tools99 -D__MSVC32__=7 -DSAFE_ALL -Ig:/vc7/include 
FLAGS1 = ${OPTIONS} ${PVMOPTION} -DUSE_LAPLACE -I../nh99 -DWIN32 /c -I. /EHsc -D__MSVC32__=7 -I../df1b2-separable -I../tools99 -DSAFE_ALL /O1 -Ig:/vc7/include 
LIBNAME = ads32.lib 
LIBRARIAN = tlib
DRIVECHANGE=
#DRIVECHANGE=g.bat
DISKDIR= g:/adms7lp.m32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	rm t.rsp ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH) ; \
	ls *.obj >> t.rsp ; \
	lib @t.rsp ; \
	cd ..

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS1) $<
	mv $*.obj $(LIBPATH)       

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)  ; \
	cp insx001.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx001a.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx002.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx003.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx004.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx005.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx005a.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx006.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx007.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx008.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx009.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx010.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx011.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx012.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx013.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx014.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx015.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx016.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx017.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx018.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp fvar.hpp $(DISKDIR)/$(INCLUDEDIR) ; \
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR) ; \
	cp dfpool.h  $(DISKDIR)/$(INCLUDEDIR) ; \
	cd $(DISKDIR) ; 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

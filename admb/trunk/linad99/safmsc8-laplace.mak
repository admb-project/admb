#macros for making optimized library for MS         
CC = cl
LL = tlib
LIBPATH = msc8slp

FLAGS = ${OPTIONS} ${PVMOPTION} -Ik:/temp/ATLAS/include /GF /EHsc -DUSE_LAPLACE -DWIN32 /c -I. -I../df1b2-separable -I../nh99 -I../tools99 -D__MSVC32__=8  -DSAFE_ALL /Ox -Ih:/vs8/vc/include -Ih:/vs8/VC/PlatformSDK/Include
FLAGS1 = ${OPTIONS} ${PVMOPTION} /GF -I../nh99 -DWIN32 /c /EHsc -I. -D__MSVC32__=8  -DSAFE_ALL /Ox -I../df1b2-separable -I../tools99  -Ih:/vs8/vc/include -Ih:/vs8/VC/PlatformSDK/Include

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

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  $(OBJSPARSE)
	rm t.rsp ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH) ; \
	ls *.obj >> t.rsp ; \
	lib @t.rsp ; \
	cd ..

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS) /Fo$(LIBPATH)/$(@F) $<

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

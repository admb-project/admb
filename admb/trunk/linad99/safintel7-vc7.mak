
#macros for making optimized library for MS         
SHELL=sh
CC = f:/intelcpp/ia32/bin/icl
LL = tlib
LIBPATH = intel7-vc71s

ifdef demo
FLAGS =  -DAD_DEMO -Qvc7.1 -DWIN32 /c -I. -I../nh99 -I../tools99 -D__MSVC32__=7 /G6 -DSAFE_ALL /Ox -Ig:/vc7/include -Ig:/vc7/platformsdk/include
FLAGS1 = -DAD_DEMO -Qvc7.1 -DWIN32 /c -I. -D__MSVC32__=7 /G6 -DOPT_LIB /Ox -I../tools99  -Ig:/vc7/include
else
FLAGS =  -Qvc7.1 -DWIN32 /c -I. -I../nh99 -I../tools99 -D__MSVC32__=7 /G6 -DSAFE_ALL /Ox -Ig:/vc7/include -Ig:/vc7/platformsdk/include
FLAGS1 = -Qvc7.1 -DWIN32 /c -I. -D__MSVC32__=7 /G6 -DOPT_LIB /Ox -I../tools99  -Ig:/vc7/include
endif

LIBNAME = ads32.lib 
LIBRARIAN = tlib
DRIVECHANGE=
#DRIVECHANGE=g.bat
ifdef demo
DISKDIR= f:/intel7-vc71-demo
else
DISKDIR= f:/intel7-vc71
endif

SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) : $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	rm $(LIBPATH)/t.rsp ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH); \
	ls *.obj >> t.rsp ; \
	lib @t.rsp ; 
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
	cd $(DISKDIR1) 
clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

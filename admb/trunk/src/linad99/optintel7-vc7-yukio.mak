
#macros for making optimized library for MS         
SHELL=sh
CC = f:/intelcpp/ia32/bin/icl
LL = f:/intelcpp/ia32/bin/xilib
LIBPATH = intel7-vc71o-yukio
 
FLAGS1 =  -D__MSVC32__=7 -DWIN32 /MLd /GX /DDEBUG /ZI /Od /RTCsu -Qvc7.1 /c -I. -I../nh99 -I../tools99 -Ig:/vc7/include -Ig:/vc7/platformsdk/include
FLAGS =  -D__MSVC32__=7 -DWIN32 /MLd /GX /DDEBUG /ZI /Od /RTCsu -Qvc7.1 /c -I. -I../nh99 -I../tools99 -Ig:/vc7/include -Ig:/vc7/platformsdk/include
LIBNAME = ado32.lib 
LIBRARIAN = tlib
DRIVECHANGE=
#DRIVECHANGE=g.bat
DISKDIR= f:/intel7-vc71-yukio
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) : $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	- rm $(LIBPATH)/t.rsp ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH); \
	ls *.obj >> t.rsp ; \
	$(LL) @t.rsp ; 
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
	cp adpvm2.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp fvar.hpp $(DISKDIR)/$(INCLUDEDIR) ; \
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR) ; \
	cd $(DISKDIR1) 
clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

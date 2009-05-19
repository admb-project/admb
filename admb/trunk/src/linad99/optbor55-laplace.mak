#macros for making optimized library for BORLAND 5.0
#CC = bcc32i
CC = bcc32
#SHELL=cmd.exe
LL = tlib
#FLAGS = -Vd -O2 -OI -OM -5 -H=Hc -DDOS386;OPT_LIB -I. -c
FLAGS = -Vd -W- -O2 -6 -H=Hc -I../nh99 -I../tools99 -I../df1b2-separable -DUSE_LAPLACE -DDOS386 -DOPT_LIB -DWIN32 -I. -c

LIBPATH =b32po55lp
LIBNAME = ado32.lib
LIBRARIAN = tlib
DRIVECHANGE=fff.bat
DISKDIR= j:/borland-551-laplace
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include OBJECTS.LST

all: $(LIBPATH)/$(LIBNAME) disk

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  $(OBJSPARSE)
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; \
	rm *.lib ; \
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; \
	tlib /P1024 @t.rsp
	cd ..

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$(@F) $<

$(OBJ0): %.obj: %.cpp
	$(CC) $(OPTIONS) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(OPTIONS) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(OPTIONS) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(OPTIONS) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJ4): %.obj: %.cpp
	$(CC) $(OPTIONS) $(FLAGS) -o$(LIBPATH)/$* $<

$(OBJSPLUS): %.obj: %.cpp
	$(CC) $(OPTIONS) $(FLAGS) -o$(LIBPATH)/$* $<


disk: 
	cp insx001.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx001a.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx002.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx003.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx004.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx005.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx005a.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx006.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx007.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx008.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx009.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx010.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx011.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx012.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx013.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx014.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx015.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx016.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx017.h $(DISKDIR)/$(INCLUDEDIR)
	cp insx018.h $(DISKDIR)/$(INCLUDEDIR)
	cp fvar.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp dfpool.h $(DISKDIR)/$(INCLUDEDIR)
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
	cd $(DISKDIR) ; del ad_build.zip ; \
        cfind . |  zip -@ ad_build ; 
clean:
	- cd $(LIBPATH);  rm *obj; rm *lib

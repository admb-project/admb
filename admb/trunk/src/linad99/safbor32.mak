#macros for making optimized library for BORLAND 5.0
CC = bcc32
#CC = bcc32i
LL = tlib
#FLAGS = -Vd -O2 -OI -OM -5 -H=Hc -DDOS386;SAFE_ALL -I. -c -f
FLAGS = ${OPTIONS} -Vd -O2 -5 -H=Hcd -DDOS386 -DSAFE_ALL -I. -c -f
LIBPATH =b32ps
LIBNAME = ads32.lib
LIBRARIAN = tlib
DRIVECHANGE=fff.bat
DISKDIR= j:/admbbor.50
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include OBJECTS.LST

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; \
	del *.lib ; \
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; \
	tlib /P1024 @t.rsp
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	cp adpvm2.h $(DISKDIR)/$(INCLUDEDIR)
	cp pvm3.h $(DISKDIR)/$(INCLUDEDIR)
	cp pvmwin.h $(DISKDIR)/$(INCLUDEDIR)
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
	cp adpvm2.h $(DISKDIR)/$(INCLUDEDIR)
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
	cd $(DISKDIR) ; del ad_build.exe ; \
	del ad_build.zip ; \
	find . |  zip -@ ad_build ; 

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

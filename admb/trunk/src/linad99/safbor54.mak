#macros for making optimized library for BORLAND 5.0
CC = bcc32
SHELL=cmd.exe
#CC = bcc32i
LL = tlib
#FLAGS = -Vd -O2 -OI -OM -5 -H=Hc -DDOS386;SAFE_ALL -I. -c -f
FLAGS = -Vd -O2 -5 -H=Hcd -DUSE_ECEPTIONS;DOS386;SAFE_ALL -I. -c -f
LIBPATH =b32ps54
LIBNAME = ads32.lib
LIBRARIAN = tlib
DRIVECHANGE=ggg.bat
DISKDIR1= \admbbor.54
DISKDIR= g:\admbbor.54
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include OBJECTS.LST

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo $(LIBNAME)  > $(LIBPATH)\t.rsp
	cd $(LIBPATH) 
	ls *.obj >> t.rsp
	cd ..
	c:\bin\sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmp
	cp tmp $(LIBPATH)/t.rsp 
	cd $(LIBPATH) 
	tlib /P64 @t.rsp
	cd ..
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 

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
	copy gccmanip.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx001.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx001a.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx002.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx003.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx004.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx005.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx005a.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx006.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx007.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx008.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx009.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx010.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx011.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx012.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx013.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx014.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx015.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx016.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx017.h $(DISKDIR)\$(INCLUDEDIR)
	copy insx018.h $(DISKDIR)\$(INCLUDEDIR)
	copy fvar.hpp $(DISKDIR)\$(INCLUDEDIR)
	copy d4arr.hpp $(DISKDIR)\$(INCLUDEDIR)
	copy indextyp.hpp $(DISKDIR)\$(INCLUDEDIR)
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 
	$(DRIVECHANGE)
	cd $(DISKDIR1)
	del ad_build.exe
	del ad_build.zip
	pkzip -r -p ad_build
	zip2exe ad_build
	del ad_build.zip

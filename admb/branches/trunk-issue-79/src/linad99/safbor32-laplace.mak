
#macros for making optimized library for BORLAND 5.0
CC = bcc32
#CC = bcc32i
LL = tlib
#FLAGS = -Vd -O2 -OI -OM -5 -H=Hc -DDOS386;SAFE_ALL -I. -c -f
FLAGS = -q -w -I\\Borland\\BCC55\\Include ${OPTIONS} -DUSE_LAPLACE -O2 -6 -DUSE_ECEPTIONS -DDOS386 -DSAFE_ALL -I. -c -f -I..\\tools99 -I..\\sparse -I..\\nh99 -I..\\df1b2-separable 
LIBPATH =b32pslp
LIBNAME = ads32.lib
LIBRARIAN = tlib
DRIVECHANGE=fff.bat
DISKDIR= f:\borland-50-laplace
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include OBJECTS.LST

$(LIBPATH)/$(LIBNAME) :  $(OBJSPARSE) $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  $(OBJSPLUS)
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; rm *.lib ; ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	#cp tmpfile $(LIBPATH)/t.rsp ; cd $(LIBPATH) ; tlib /P1024 @t.rsp
	cd ..

$(LIBPATH)/$(LIBNAME) :  $(OBJSPARSE) $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  $(OBJSPLUS)

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS) -w-8057 -w-8084 -w-8001 -w-8004 -w-8008 -w-8066 -w-8013 -w-8012 -o$(LIBPATH)/$(@F) $<

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -w-8057 -w-8084 -w-8001 -w-8004 -w-8008 -w-8066 -w-8013 -w-8012 -o$(LIBPATH)/$(@F) $<

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS) -w-8057 -w-8084 -w-8001 -w-8004 -w-8008 -w-8066 -w-8013 -w-8012 -o$(LIBPATH)/$(@F) $<

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) -w-8057 -w-8084 -w-8001 -w-8004 -w-8008 -w-8066 -w-8013 -w-8012 -o$(LIBPATH)/$(@F) $<

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS) -w-8057 -w-8084 -w-8001 -w-8004 -w-8008 -w-8066 -w-8013 -w-8012 -o$(LIBPATH)/$(@F) $<

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	cp dfpool.h $(DISKDIR)/$(INCLUDEDIR)
	cp fvar.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR)
	#cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	make -f optbor32-laplace.mak clean

#macros for making optimized library for BORLAND 5.0
#CC = bcc32i
CC = bcc32
LL = tlib
#FLAGS = -Vd -O2 -OI -OM -5 -H=Hc -DDOS386;OPT_LIB -I. -c -f
FLAGS = -I\\Borland\\BCC55\\Include ${OPTIONS} -DUSE_LAPLACE -Vd -W- -O2 -5 -H=Hc -DDOS386 -DOPT_LIB -I. -c -f -I..\\sparse -I..\\nh99 -I..\\df1b2-separable

LIBPATH =b32polp
LIBNAME = ado32.lib
LIBRARIAN = tlib
DRIVECHANGE=fff.bat
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
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp ; cd $(LIBPATH) ; tlib /P1024 @t.rsp
	cd ..

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

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	cp fvar.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp dfpool.h $(DISKDIR)/$(INCLUDEDIR)
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 

clean:
	rm -f tmpfile
	rm -f Hc
	rm -f Hcd
	rm -f Hc.*
	rm -f Hcd.*
	- cd $(LIBPATH) ; rm -f *.obj ; rm -f *.lib ; rm -f *.o ; rm -f *.a; rm -f *.rsp

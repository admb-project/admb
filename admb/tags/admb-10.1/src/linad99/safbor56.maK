

#macros for making optimized library for BORLAND 5.0
CC = bcc32
LL = tlib
FLAGS = ${OPTIONS} -Vd -O2 -6 -DUSE_ECEPTIONS  -DDOS386 -DSAFE_ALL -I. -c 
LIBPATH =b32ps56
LIBNAME = ads32.lib
LIBRARIAN = tlib
DRIVECHANGE=fff.bat
DISKDIR= f:/binaries/borland-556
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 
vpath %.obj $(LIBPATH)$

.SUFFIXES: .obj .cpp

include OBJECTS.LST

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo $(LIBNAME)  > $(LIBPATH)/t.rsp
	cd $(LIBPATH) ; \
	ls *.obj >> t.rsp 
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmp
	cp tmp $(LIBPATH)/t.rsp 
	cd $(LIBPATH) ; \
	tlib /P64 @t.rsp 
	cd ..
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
	cp gccmanip.h $(DISKDIR)/$(INCLUDEDIR)
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
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp indextyp.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR) 
	$(DRIVECHANGE)

clean:
	cd $(LIBPATH);  rm *obj; rm *lib
  

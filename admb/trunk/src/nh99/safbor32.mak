#macros for making optimized library for BORLAND 4.0
CC = bcc32
LL = tlib
FLAGS = ${OPTIONS} -Vd -OI -OM -O2 -H -Hc -DOPT_LIB -DDOS386 -I. -5 -c -f
LIBPATH = b32po
LIBNAME = admod32.lib 
LIBRARIAN = tlib
DISKDIR= c:\admdisk.b32
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp .dir

vpath %.obj $(LIBPATH)$

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	echo $(LIBNAME)  > $(LIBPATH)\t.rsp
	cd $(LIBPATH) 
	ls *.obj >> t.rsp
	cd ..
	sed -e ' 1,$$s/$$/ \&/' -e '2,$$s/^/+-/' -e ' $$s/ \&//' -e ' s/b32o\///' $(LIBPATH)/t.rsp > tmpfile
	cp tmpfile $(LIBPATH)/t.rsp 
	cd $(LIBPATH) 
	tlib @t.rsp
	cd ..
	copy $(LIBPATH)\$(LIBNAME) $(DISKDIR)\$(LIBDIR) 

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$* $<
	copy $< $(DISKDIR)\$(SRCDIR) 

# this is a kludge to copy the cpp files over to the disk image
#$(OBJ0:.obj=.dir): %.dir: %.cpp
#	cp $< $(DISKDIR)\$(SRCDIR)

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	copy admodel.h $(DISKDIR)\$(INCLUDEDIR)



#macros for making optimized library for MS         
CC = cl
LL = tlib

FLAGS = /nologo /W4 /wd4258 /wd4068 /wd4389 /wd4288 /wd4700 /wd4018 /wd4505 /wd4701 /wd4102 /wd4189 /wd4101 /wd4702 /wd4512 /wd4511 /wd4005 /wd4717 /wd4239 /wd4238 /wd4100 /wd4996 /wd4127 /wd4244 /wd4190 /wd4099 ${OPTIONS} ${PVMOPTION} /GF /EHsc -DUSE_LAPLACE -DWIN32 /c -I. -I../df1b2-separable -I../nh99 -I../tools99 -D__MSVC32__=8  -DSAFE_ALL /Ox /EHsc
FLAGS1 = /nologo /W4 /wd4258 /wd4068 /wd4389 /wd4288 /wd4700 /wd4018 /wd4505 /wd4701 /wd4102 /wd4189 /wd4101 /wd4702 /wd4512 /wd4511 /wd4005 /wd4717 /wd4239 /wd4238 /wd4100 /wd4996 /wd4127 /wd4244 /wd4190 /wd4099 ${OPTIONS} ${PVMOPTION} /GF -I../nh99 -DWIN32 /c /EHsc -I. -D__MSVC32__=8  -DSAFE_ALL /Ox -I../df1b2-separable -I../tools99

LIBNAME = ads32.lib 
LIBRARIAN = tlib
DRIVECHANGE=
#DRIVECHANGE=g.bat
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  $(OBJSPARSE) 
$(LIBPATH)/$(LIBNAME) : $(OBJECTS)
	cd $(LIBPATH) && lib /OUT:$(LIBNAME) /NOLOGO $(filter-out ../sparse/hs_sparse.obj, $(OBJECTS)) hs_sparse.obj

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
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)
	cp fvar.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR)
	cp dfpool.h  $(DISKDIR)/$(INCLUDEDIR)
	cd $(DISKDIR)

clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a

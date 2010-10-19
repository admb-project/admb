.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /nologo /W4 /wd4258 /wd4068 /wd4389 /wd4288 /wd4700 /wd4018 /wd4505 /wd4701 /wd4102 /wd4189 /wd4101 /wd4702 /wd4512 /wd4511 /wd4005 /wd4717 /wd4239 /wd4238 /wd4100 /wd4996 /wd4127 /wd4244 /wd4190 /wd4099 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I.. /I..\..\df1b2-separable /I..\..\nh99 /I..\..\tools99 /D__MSVC32__=8  /DSAFE_ALL /Ox /EHsc
FLAGS1 = /nologo /W4 /wd4258 /wd4068 /wd4389 /wd4288 /wd4700 /wd4018 /wd4505 /wd4701 /wd4102 /wd4189 /wd4101 /wd4702 /wd4512 /wd4511 /wd4005 /wd4717 /wd4239 /wd4238 /wd4100 /wd4996 /wd4127 /wd4244 /wd4190 /wd4099 $(OPTIONS) $(PVMOPTION) /GF /I../../nh99 /DWIN32 /c /EHsc /I.. /D__MSVC32__=8  /DSAFE_ALL /Ox /I../../df1b2-separable /I../../tools99

LIBNAME = ads32.lib 
SRCDIR =  src

#vpath %.obj $(LIBPATH)$

include ..\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE) hs_sparse.obj 

$(LIBNAME) : $(OBJECTS)
	lib /OUT:$(LIBNAME) /NOLOGO *.obj

../sparse/hs_sparse.obj:

hs_sparse.obj: ..\..\sparse\hs_sparse.cpp
	$(CC) $(FLAGS) ..\..\sparse\hs_sparse.cpp

{..}.cpp.obj:
	$(CC) $(FLAGS) $<

#$(OBJ3): %.obj: %.cpp
#	$(CC) $(FLAGS1) $<
#	mv $*.obj $(LIBPATH)       

all: $(LIBNAME) disk

disk: 
	copy $(LIBNAME) $(DISKDIR)\lib
	copy ..\fvar.hpp $(DISKDIR)\include
	copy ..\d4arr.hpp $(DISKDIR)\include
	copy ..\dfpool.h  $(DISKDIR)\include

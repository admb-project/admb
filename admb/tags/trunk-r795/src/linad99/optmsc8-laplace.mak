.SUFFIXES: .obj .cpp

CC = cl
LL = tlib

FLAGS = /nologo /W4 /wd4258 /wd4068 /wd4389 /wd4288 /wd4505 /wd4700 /wd4701 /wd4018 /wd4101 /wd4189 /wd4102 /wd4189 /wd4702 /wd4512 /wd4511 /wd4005 /wd4717 /wd4239 /wd4238 /wd4100 /wd4996 /wd4127 /wd4244 /wd4190 /wd4099 $(OPTIONS) $(PVMOPTION)  /DUSE_LAPLACE /DWIN32 /c /I.. /I..\..\df1b2-separable /I..\..\nh99 /I..\..\tools99 /D__MSVC32__=8  /DOPT_LIB /Ox /EHsc

FLAGS1 = /nologo /W4 /wd4258 /wd4068 /wd4389 /wd4288 /wd4505 /wd4700 /wd4701 /wd4018 /wd4101 /wd4189 /wd4102 /wd4189 /wd4702 /wd4512 /wd4511 /wd4005 /wd4717 /wd4239 /wd4238 /wd4100 /wd4996 /wd4127 /wd4244 /wd4190 /wd4099 $(OPTIONS) $(PVMOPTION) /GF -I../nh99 /DWIN32 /c /EHsc -I. /D__MSVC32__=8  /DOPT_LIB /Ox -I../df1b2-separable -I../tools99

LIBNAME = ado32.lib 

#vpath %.obj $(LIBPATH)

include ..\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE) hs_sparse.obj

$(LIBNAME) : $(OBJECTS)
	lib /OUT:$(LIBNAME) /NOLOGO *.obj

cnorlogmix.obj:
ad_atlas.obj:
d3arr11.obj:
dmat_acc.obj:
dmat32.obj:
dmat8.obj:
dvec_acc.obj:
dvect21.obj:
f3arr12.obj:
f3arr18.obj:
imat2.obj:
imat1.obj:
fvar_m48.obj:
model49.obj:
lmat2.obj:
lmat1.obj:
i3arr1.obj:
fvma_acc.obj:
fvar_ma8.obj:
f3arr19.obj:
fvar_a52.obj:
../sparse/hs_sparse.obj:

hs_sparse.obj: ..\..\sparse\hs_sparse.cpp
	$(CC) $(FLAGS) ..\..\sparse\hs_sparse.cpp

{..}.cpp.obj:
	$(CC) $(FLAGS) $<

all: $(LIBNAME) disk

disk: 
	copy ..\fvar.hpp $(DISKDIR)\include
	copy ..\d4arr.hpp $(DISKDIR)\include
	copy ..\dfpool.h $(DISKDIR)\include
	copy $(LIBNAME) $(DISKDIR)\lib

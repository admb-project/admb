.SUFFIXES: .obj .cpp

CC = cl
LL = tlib

FLAGS = /nologo /W4 $(OPTIONS) $(PVMOPTION) /DUSE_LAPLACE /DWIN32 /c /I..\..\..\..\src\df1b2-separable /I..\..\..\..\src\linad99 /I..\..\..\..\src\nh99 /I..\..\..\..\src\tools99 /D__MSVC32__=8  /DOPT_LIB /Ox /EHsc

LIBNAME = ado32.lib 

include ..\..\..\..\src\linad99\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE) hs_sparse.obj

all: $(DISKDIR)\lib\$(LIBNAME)
	copy ..\..\..\..\src\linad99\fvar.hpp $(DISKDIR)\include
	copy ..\..\..\..\src\linad99\d4arr.hpp $(DISKDIR)\include
	copy ..\..\..\..\src\linad99\dfpool.h $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(OBJECTS)
	lib /OUT:$@ /NOLOGO *.obj

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

hs_sparse.obj: ..\..\..\..\src\sparse\hs_sparse.cpp
	$(CC) $(FLAGS) /Fo$@ ..\..\..\..\src\sparse\hs_sparse.cpp

{..\..\..\..\src\linad99}.cpp.obj:
	$(CC) $(FLAGS) $<

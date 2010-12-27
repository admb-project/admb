.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I..\..\..\..\src\df1b2-separable /I..\..\..\..\src\linad99 /I..\..\..\..\src\nh99 /I..\..\..\..\src\tools99 /D__MSVC32__=8  /DSAFE_ALL /Ox /EHsc

LIBNAME = ads32.lib 

include ..\..\..\..\src\linad99\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPARSE) hs_sparse.obj 

all: $(DISKDIR)\lib\$(LIBNAME)
	copy ..\..\..\..\src\linad99\fvar.hpp $(DISKDIR)\include
	copy ..\..\..\..\src\linad99\d4arr.hpp $(DISKDIR)\include
	copy ..\..\..\..\src\linad99\dfpool.h  $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(OBJECTS)
	lib /OUT:$@ /NOLOGO *.obj

../sparse/hs_sparse.obj:

hs_sparse.obj: ..\..\..\..\src\sparse\hs_sparse.cpp
	$(CC) $(FLAGS) /Fo$@ ..\..\..\..\src\sparse\hs_sparse.cpp

{..\..\..\..\src\linad99}.cpp.obj:
	$(CC) $(FLAGS) $<


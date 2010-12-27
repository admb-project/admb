.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I..\..\..\..\src\df1b2-separable /I..\..\..\..\src\nh99 /I..\..\..\..\src\linad99 /I..\..\..\..\src\tools99 /D__MSVC32__=8  /DSAFE_ALL /Ox

include ..\..\..\..\src\tools99\objects.lst

LIBNAME = adt32s.lib 

all: $(DISKDIR)\lib\$(LIBNAME)
	copy ..\..\..\..\src\tools99\clist.h $(DISKDIR)\include
	copy ..\..\..\..\src\tools99\cifstrem.h $(DISKDIR)\include
	copy ..\..\..\..\src\tools99\adstring.hpp $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	lib /OUT:$@ /NOLOGO *.obj

{..\..\..\..\src\tools99}.cpp.obj:
	$(CC) $(FLAGS) $<

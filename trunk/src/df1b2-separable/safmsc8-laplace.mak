.SUFFIXES: .obj .cpp

FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I..\..\..\..\src\df1b2-separable /I..\..\..\..\src\linad99 /I..\..\..\..\src\nh99 /I..\..\..\..\src\tools99 /D__MSVC32__=8 /DSAFE_ALL /Ox

include ..\..\..\..\src\df1b2-separable\objects.lst

LIBNAME=df1b2s.lib  

OBJECTS=$(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

all: $(DISKDIR)\lib\$(LIBNAME)
	copy ..\..\..\..\src\df1b2-separable\df1b2fun.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\adpool.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\adrndeff.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\df1b2fnl.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\df3fun.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\df32fun.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\df1b2loc.h $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(OBJECTS)
	lib /OUT:$@ /NOLOGO /IGNORE:4006 *.obj

{..\..\..\..\src\df1b2-separable}.cpp.obj:
	$(CC) $(FLAGS) $<

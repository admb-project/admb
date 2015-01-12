.SUFFIXES: .obj .cpp

FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I..\..\..\..\src\df1b2-separable /I..\..\..\..\src\linad99 /I..\..\..\..\src\nh99 /I..\..\..\..\src\tools99 /D__MSVC32__=8  /DOPT_LIB /Ox
LIBNAME = df1b2o.lib 

include ..\..\..\..\src\df1b2-separable\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

all: $(DISKDIR)\lib\$(LIBNAME) $(DISKDIR)\bin\tpl2rem.exe
	copy ..\..\..\..\src\df1b2-separable\df1b2fun.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\adpool.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\adrndeff.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\df1b2fnl.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\df3fun.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\df32fun.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\df1b2loc.h $(DISKDIR)\include
	copy ..\..\..\..\src\df1b2-separable\sed* $(DISKDIR)\bin

$(DISKDIR)\lib\$(LIBNAME): $(OBJECTS)
	lib /OUT:$@ /NOLOGO /IGNORE:4006 *.obj
	
{..\..\..\..\src\df1b2-separable}.cpp.obj:
	$(CC) $(FLAGS) $<

tpl2rem-winflex.c: ..\..\..\..\src\df1b2-separable\tpl2rem.lex
	flex -w $<
	sed -f ..\..\..\..\src\df1b2-separable\sedflex lex.yy.c > tpl2rem-winflex.c

$(DISKDIR)\bin\tpl2rem.exe:
	cl /nologo /W4 /wd4049 /wd4700 /wd4702 /wd4018 /wd4996 /wd4131 /wd4127 /wd4244 /wd4101 /wd4189 /DWIN32 /Fe$(DISKDIR)\bin\$@ ..\..\..\..\src\df1b2-separable\tpl2rem-winflex.c

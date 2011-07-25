.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I..\..\..\..\src\df1b2-separable /I..\..\..\..\src\nh99 /I..\..\..\..\src\linad99 /I..\..\..\..\src\tools99 /I..\..\..\..\contrib\statslib /I..\..\..\..\contrib\priorslib /D__MSVC32__=8  /DSAFE_ALL /Ox

include ..\..\..\..\contrib\priorslib\objects.lst

LIBNAME = priors.lib 

all: $(DISKDIR)\lib\$(LIBNAME)
	copy ..\..\..\..\contrib\priorslib\priorsLib.h $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(OBJ0)
	lib /OUT:$@ /NOLOGO *.obj

priors.obj:
like.obj:

{..\..\..\..\contrib\priorslib}.cpp.obj:
	$(CC) $(FLAGS) $<


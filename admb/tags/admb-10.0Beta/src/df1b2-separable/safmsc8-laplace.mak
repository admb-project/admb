.SUFFIXES: .obj .cpp

FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I.. /I..\..\linad99 /I..\..\nh99 /I..\..\tools99 /D__MSVC32__=8 /DSAFE_ALL /Ox

include ..\objects.lst

OBJECTS=$(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

LIBNAME=df1b2s.lib  

$(LIBNAME): $(OBJECTS)
	lib /OUT:$(LIBNAME) /NOLOGO /IGNORE:4006 *.obj
	
{..}.cpp.obj:
	$(CC) $(FLAGS) $<

all: $(LIBNAME) disk

disk: 
	copy ..\df1b2fun.h $(DISKDIR)\include
	copy ..\adpool.h $(DISKDIR)\include
	copy ..\adrndeff.h $(DISKDIR)\include
	copy ..\df1b2fnl.h $(DISKDIR)\include
	copy ..\df3fun.h $(DISKDIR)\include
	copy ..\df32fun.h $(DISKDIR)\include
	copy ..\df1b2loc.h $(DISKDIR)\include
	copy $(LIBNAME) $(DISKDIR)\lib

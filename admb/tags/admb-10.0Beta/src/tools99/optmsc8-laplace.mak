.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I.. /I..\..\df1b2-separable /I..\..\nh99 /I..\..\linad99 /D__MSVC32__=8  /DOPT_LIB /Ox

LIBNAME = adt32.lib 

include ..\objects.lst

$(LIBNAME): $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  
	lib /OUT:$(LIBNAME) /NOLOGO *.obj

{..}.cpp.obj:
	$(CC) $(FLAGS) $<

all: $(LIBNAME) disk

disk: 
	copy ..\clist.h $(DISKDIR)\include
	copy ..\cifstrem.h $(DISKDIR)\include
	copy ..\adstring.hpp $(DISKDIR)\include
	copy $(LIBNAME) $(DISKDIR)\lib

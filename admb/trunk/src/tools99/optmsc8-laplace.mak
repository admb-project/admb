.SUFFIXES: .obj .cpp

CC = cl

FLAGS = /nologo /W4 /wd4018 /wd4189 /wd4512 /wd4511 /wd4100 /wd4244 /wd4068 /wd4996 /wd4127 /wd4706 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I.. /I..\..\df1b2-separable /I..\..\nh99 /I..\..\linad99 /D__MSVC32__=8  /DOPT_LIB /Ox

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

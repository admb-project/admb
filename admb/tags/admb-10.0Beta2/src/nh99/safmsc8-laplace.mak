.SUFFIXES: .obj .cpp

CC = cl
STUBLIBNAME = df1b2stubs.lib
FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I.. /I../../df1b2-separable /I../../linad99 /I../../tools99 /D__MSVC32__=8  /DSAFE_ALL /Ox 
#/DADMB_VERSION=$(ADMB_VERSION)
LIBNAME = admod32s.lib 

include ..\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

$(LIBNAME):  $(OBJECTS)
	lib /NOLOGO /OUT:$(LIBNAME) *.obj
	
{..}.cpp.obj:
	$(CC) $(FLAGS)  $<

all: $(LIBNAME) $(STUBLIBNAME) disk

$(STUBLIBNAME): ..\df1b2stub.cpp
	$(CC) $(FLAGS) ..\df1b2stub.cpp
	lib /OUT:$(STUBLIBNAME) /NOLOGO df1b2stub.obj

disk: 
	copy ..\admodel.h $(DISKDIR)\include
	copy ..\adsplus.h $(DISKDIR)\include
	copy ..\spcomm.h $(DISKDIR)\include
	copy ..\s.h $(DISKDIR)\include
	copy ..\newredef.h $(DISKDIR)\include
	copy ..\param_init_bounded_number_matrix.h $(DISKDIR)\include
	copy $(LIBNAME) $(DISKDIR)\lib
	copy $(STUBLIBNAME) $(DISKDIR)\lib

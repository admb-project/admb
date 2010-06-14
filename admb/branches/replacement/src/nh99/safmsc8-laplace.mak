.SUFFIXES: .obj .cpp

CC = cl
STUBLIBNAME = df1b2stubs.lib
FLAGS = /nologo /W4 /wd4258 /wd4700 /wd4288 /wd4018 /wd4505 /wd4239 /wd4512 /wd4511 /wd4804 /wd4100 /wd4996 /wd4127 /wd4190 /wd4706 /wd4701 /wd4068 /wd4244 /wd4101 /wd4189 /wd4717 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I.. /I../../df1b2-separable /I../../linad99 /I../../tools99 /D__MSVC32__=8  /DSAFE_ALL /Ox 
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
	copy $(LIBNAME) $(DISKDIR)\lib
	copy $(STUBLIBNAME) $(DISKDIR)\lib

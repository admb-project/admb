.SUFFIXES: .obj .cpp

CC = cl

STUBPATH = $(LIBPATH)-stub
STUBLIBNAME = df1b2stubo.lib
FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I.. /I../../df1b2-separable /I../../linad99 /I../../tools99 /D__MSVC32__=8  /DOPT_LIB /Ox 

#/DADMB_VERSION=$(ADMB_VERSION)

LIBNAME = admod32.lib 

include ..\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

$(LIBNAME): $(OBJECTS)
	lib /NOLOGO /OUT:$(LIBNAME) *.obj
	
{..}.cpp.obj:
	$(CC) $(FLAGS) $<

all: $(LIBNAME) $(STUBLIBNAME) disk

$(STUBLIBNAME): ..\df1b2stub.cpp
	$(CC) $(FLAGS) ..\df1b2stub.cpp
	lib /OUT:$(STUBLIBNAME) /NOLOGO df1b2stub.obj

tpl2cpp-winflex.c: tpl2cpp.lex 
	flex -w tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp-winflex.c

tpl2cpp:
	cl /nologo /wd4996 ..\tpl2cpp-winflex.c

disk: tpl2cpp
	copy ..\admodel.h $(DISKDIR)\include
	copy ..\adsplus.h $(DISKDIR)\include
	copy ..\spcomm.h $(DISKDIR)\include
	copy ..\s.h $(DISKDIR)\include
	copy ..\newredef.h $(DISKDIR)\include
	copy ..\param_init_bounded_number_matrix.h $(DISKDIR)\include
	copy $(LIBNAME) $(DISKDIR)\lib
	copy $(STUBLIBNAME) $(DISKDIR)\lib
	copy tpl2cpp-winflex.exe $(DISKDIR)\bin\tpl2cpp.exe

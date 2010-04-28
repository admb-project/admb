.SUFFIXES: .obj .cpp

FLAGS = /nologo /W4 /wd4018 /wd4552 /wd4189 /wd4101 /wd4505 /wd4715 /wd4700 /wd4239 /wd4702 /wd4702 /wd4511 /wd4512 /wd4100 /wd4127 /wd4706 /wd4996 /wd4244 /wd4146 /wd4701 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c /I.. /I..\..\linad99 /I..\..\nh99 /I..\..\tools99 /D__MSVC32__=8  /DOPT_LIB /Ox
LIBNAME = df1b2o.lib 

include ..\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

$(LIBNAME): $(OBJECTS)
	lib /OUT:$(LIBNAME) /NOLOGO /IGNORE:4006 *.obj
	
{..}.cpp.obj:
	$(CC) $(FLAGS) $<

all: $(LIBNAME) tpl2rem disk

..\tpl2rem-winflex.c: ..\tpl2rem.lex
	flex -w ..\tpl2rem.lex
	sed -f ..\sedflex lex.yy.c > ..\tpl2rem-winflex.c

tpl2rem: ..\tpl2rem-winflex.c
	cl /nologo /W4 /wd4049 /wd4700 /wd4702 /wd4018 /wd4996 /wd4131 /wd4127 /wd4244 /wd4101 /wd4189 /DWIN32 ..\tpl2rem-winflex.c

disk: 
	copy ..\df1b2fun.h $(DISKDIR)\include
	copy ..\adpool.h $(DISKDIR)\include
	copy ..\adrndeff.h $(DISKDIR)\include
	copy ..\df1b2fnl.h $(DISKDIR)\include
	copy ..\df3fun.h $(DISKDIR)\include
	copy ..\df32fun.h $(DISKDIR)\include
	copy ..\df1b2loc.h $(DISKDIR)\include
	copy $(LIBNAME) $(DISKDIR)\lib
	copy ..\sed* $(DISKDIR)\bin
	copy tpl2rem-winflex.exe $(DISKDIR)\bin\tpl2rem.exe

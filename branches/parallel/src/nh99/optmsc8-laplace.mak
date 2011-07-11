.SUFFIXES: .obj .cpp

CC = cl

STUBPATH = $(LIBPATH)-stub
STUBLIBNAME = df1b2stubo.lib
FLAGS = /nologo /W4 /GF /EHsc /DUSE_LAPLACE /DWIN32 /c  /I..\..\..\..\src\df1b2-separable /I..\..\..\..\src\linad99 /I..\..\..\..\src\nh99 /I..\..\..\..\src\tools99 /D__MSVC32__=8  /DOPT_LIB /Ox 

#/DADMB_VERSION=$(ADMB_VERSION)

LIBNAME = admod32.lib 

include ..\..\..\..\src\nh99\objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

all: $(DISKDIR)\lib\$(LIBNAME) $(DISKDIR)\bin\tpl2cpp.exe
	copy ..\..\..\..\src\nh99\admodel.h $(DISKDIR)\include
	copy ..\..\..\..\src\nh99\adsplus.h $(DISKDIR)\include
	copy ..\..\..\..\src\nh99\spcomm.h $(DISKDIR)\include
	copy ..\..\..\..\src\nh99\s.h $(DISKDIR)\include
	copy ..\..\..\..\src\nh99\newredef.h $(DISKDIR)\include
	copy ..\..\..\..\src\nh99\param_init_bounded_number_matrix.h $(DISKDIR)\include

$(DISKDIR)\lib\$(LIBNAME): $(OBJECTS)
	lib /NOLOGO /OUT:$@ *.obj

$(STUBLIBNAME): ..\df1b2stub.cpp
	$(CC) $(FLAGS) ..\df1b2stub.cpp
	lib /OUT:$(STUBLIBNAME) /NOLOGO df1b2stub.obj

$(DISKDIR)\bin\tpl2cpp.exe:
	cl /nologo /wd4996 /Fe$@ ..\..\..\..\src\nh99\tpl2cpp-winflex.c

tpl2cpp-winflex.c: tpl2cpp.lex 
	flex -w tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp-winflex.c

{..\..\..\..\src\nh99}.cpp.obj:
	$(CC) $(FLAGS) $<

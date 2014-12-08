.SUFFIXES: .obj .cpp
.PATH.obj = $(LIBPATH)

LIBNAME = admod32.lib

!include objects.lst

all: $(LIBNAME) $(DISKDIR)\dist\bin\tpl2cpp.exe disk

$(LIBNAME): $(OBJ0)
	cd $(LIBPATH)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a $(OBJ0)
	cd ..\..\..\..\src\nh99

.cpp.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\$*.obj $<

$(DISKDIR)\dist\bin\tpl2cpp.exe: tpl2cpp-winflex.c
	bcc32 -Ic:\\Borland\\BCC55\\Include -Lc:\\Borland\\BCC55\\Lib -e$(DISKDIR)\dist\bin\tpl2cpp.exe tpl2cpp-winflex.c

flex:
	flex < tpl2cpp.lex
	..\..\utilities\sed -f sedflex lex.yy.c > tpl2cpp.c
	bcc32 -Ic:\\Borland\\BCC55\\Include -Lc:\\Borland\\BCC55\\Lib -etpl2cpp.exe tpl2cpp-winflex.c
	cp tpl2cpp.exe $(DISKDIR)\dist\bin

disk:
	copy admodel.h $(DISKDIR)\dist\include
	copy param_init_bounded_number_matrix.h $(DISKDIR)\dist\include

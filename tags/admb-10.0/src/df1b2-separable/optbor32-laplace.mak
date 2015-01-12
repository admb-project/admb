.SUFFIXES: .obj .cpp
.PATH.obj = $(LIBPATH)

LIBNAME = df1b2o.lib 

!include objects.lst

all: $(LIBNAME) $(DISKDIR)\dist\bin\tpl2rem.exe disk

$(LIBNAME) :  $(OBJ0)
	cd $(LIBPATH)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a $(OBJ0)
	cd ..\..\..\..\src\df1b2-separable

.cpp.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\$*.obj $<

disk: 
	copy adpool.h $(DISKDIR)\dist\include
	copy adrndeff.h $(DISKDIR)\dist\include
	copy df1b2fun.h $(DISKDIR)\dist\include
	copy smartbuf.h $(DISKDIR)\dist\include
	copy df1b2fnl.h $(DISKDIR)\dist\include
	copy df1b2loc.h $(DISKDIR)\dist\include
	copy df32fun.h $(DISKDIR)\dist\include
	copy df3fun.h $(DISKDIR)\dist\include
	copy f1b2locl.h $(DISKDIR)\dist\include
	copy sedcmd $(DISKDIR)\dist\bin
	copy sedcmd2 $(DISKDIR)\dist\bin
	copy sedcmd3 $(DISKDIR)\dist\bin
	copy seddf1b2 $(DISKDIR)\dist\bin
	copy seddf1b3 $(DISKDIR)\dist\bin
	copy seddf1b4 $(DISKDIR)\dist\bin
	copy sedf1b2a $(DISKDIR)\dist\bin
	copy sedf1b2c $(DISKDIR)\dist\bin
	copy sedf1b2d $(DISKDIR)\dist\bin

$(DISKDIR)\dist\bin\tpl2rem.exe: tpl2rem-winflex.c
	bcc32 -DWIN32 -Ic:\\Borland\\BCC55\\Include -Lc:\\Borland\\BCC55\\Lib -e$(DISKDIR)\dist\bin\tpl2rem.exe tpl2rem-winflex.c

flex:
	flex < tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem.c
	bcc32 -DWIN32 -Ic:\\Borland\\BCC55\\Include -Lc:\\Borland\\BCC55\\Lib -etpl2rem.exe tpl2rem-winflex.c
	cp tpl2rem.exe $(DISKDIR)\dist\bin\tpl2rem.exe

.SUFFIXES: .obj .cpp
.PATH.obj = $(LIBPATH)

LIBNAME = df1b2s.lib 

!include objects.lst

all: $(LIBNAME)

$(LIBNAME) :  $(OBJ0)
	cd $(LIBPATH)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a $(OBJ0)
	cd ..\..\..\..\src\df1b2-separable

.cpp.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\$*.obj $<

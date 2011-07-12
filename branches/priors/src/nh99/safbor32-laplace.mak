.SUFFIXES: .obj .cpp
.PATH.obj = $(LIBPATH)

LIBNAME = admod32s.lib 

!include objects.lst

all: $(LIBNAME)

$(LIBNAME): $(OBJ0) $(OBJPRIORS)
	cd $(LIBPATH)
	tlib ..\..\dist\lib\$(LIBNAME) /a $(OBJ0)
	tlib ..\..\dist\lib\$(LIBNAME) /a $(OBJPRIORS)
	cd ..\..\..\..\src\nh99

.cpp.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\$*.obj $<

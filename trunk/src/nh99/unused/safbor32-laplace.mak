.SUFFIXES: .obj .cpp
.PATH.obj = $(LIBPATH)

LIBNAME = admod32s.lib

!include objects.lst

all: $(LIBNAME)

$(LIBNAME): $(OBJ0)
	cd $(LIBPATH)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a $(OBJ0)
	cd ..\..\..\..\src\nh99

.cpp.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\$*.obj $<

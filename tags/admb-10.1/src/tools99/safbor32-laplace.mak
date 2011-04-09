.SUFFIXES: .obj .cpp
.PATH.obj = $(LIBPATH)

LIBNAME = adt32s.lib 

!include objects.lst

all: $(LIBNAME)

$(LIBNAME): $(OBJ0) $(OBJSPLUS)
	cd $(LIBPATH)
	tlib ..\..\dist\lib\$(LIBNAME) /a $(OBJ0) $(OBJSPLUS)
	cd ..\..\..\..\src\tools99

.cpp.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\$*.obj $<

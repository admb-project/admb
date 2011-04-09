.SUFFIXES: .obj .cpp
.PATH.obj = $(LIBPATH)

LIBNAME = adt32.lib 

!include objects.lst

all: $(LIBNAME) disk

$(LIBNAME): $(OBJ0) $(OBJSPLUS)
	cd $(LIBPATH)
	tlib ..\..\dist\lib\$(LIBNAME) /a $(OBJ0) $(OBJSPLUS)
	cd ..\..\..\..\src\tools99

.cpp.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\$*.obj $<

disk: 
	copy adstring.hpp $(DISKDIR)\dist\include
	copy cifstrem.h $(DISKDIR)\dist\include
	copy clist.h $(DISKDIR)\dist\include

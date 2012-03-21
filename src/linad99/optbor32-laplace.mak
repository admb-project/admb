.SUFFIXES: .obj .cpp
.PATH.obj = $(LIBPATH)
.PATH.cpp = ..\sparse;.

LIBNAME = ado32.lib

!include objects.lst

all: $(LIBNAME) disk

$(LIBNAME): $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) hs_sparse.obj
	cd $(LIBPATH)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a $(OBJ0)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a $(OBJ1)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a $(OBJ2)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a $(OBJ3)
	tlib /P128 ..\..\dist\lib\$(LIBNAME) /a hs_sparse.obj
	cd ..\..\..\..\src\linad99

hs_sparse.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\hs_sparse.obj ..\sparse\hs_sparse.cpp

.cpp.obj:
	$(CC) $(CXXFLAGS) -o$(.PATH.obj)\$*.obj $<

disk:
	copy fvar.hpp $(DISKDIR)\dist\include
	copy dfpool.h $(DISKDIR)\dist\include
	copy d4arr.hpp $(DISKDIR)\dist\include
	copy factors.h $(DISKDIR)\dist\include

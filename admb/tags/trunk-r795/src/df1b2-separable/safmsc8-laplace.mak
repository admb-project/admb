.SUFFIXES: .obj .cpp


include ..\objects.lst

OBJECTS=$(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

LIBNAME=df1b2s.lib  

all: $(LIBNAME) disk

$(LIBNAME): $(OBJECTS)
	lib /OUT:$(LIBNAME) /NOLOGO /IGNORE:4006 *.obj
	
.cpp.obj:
	$(CC) $(FLAGS) $<

dist: 
	copy ..\df1b2fun.h $(DISKDIR)\include
	copy ..\adpool.h $(DISKDIR)\include
	copy ..\adrndeff.h $(DISKDIR)\include
	copy ..\df1b2fnl.h $(DISKDIR)\include
	copy ..\df3fun.h $(DISKDIR)\include
	copy ..\df32fun.h $(DISKDIR)\include
	copy ..\df1b2loc.h $(DISKDIR)\include

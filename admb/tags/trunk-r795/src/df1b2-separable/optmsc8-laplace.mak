.SUFFIXES: .obj .cpp

LIB=$(DIST_DEST)\lib\df1b2o.lib 
TPL2REM=$(DIST_DEST)\bin\tpl2rem.exe

include objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJSPLUS) 

all: $(LIB) dist

$(LIB): $(OBJECTS)
	lib /OUT:$(LIB) /NOLOGO /IGNORE:4006 *.obj
	
.cpp.obj:
	$(CXX) /c $(CXXFLAGS) $<

$(TPL2REM):
	$(CC) /nologo /W4 /wd4049 /wd4700 /wd4702 /wd4018 /wd4996 /wd4131 /wd4127 /wd4244 /wd4101 /wd4189 /DWIN32 tpl2rem-winflex.c

tpl2rem-winflex.c: tpl2rem.lex
	flex -w tpl2rem.lex
	sed -f sedflex lex.yy.c > tpl2rem-winflex.c

dist: 
	copy df1b2fun.h $(DIST_DEST)\include
	copy adpool.h $(DIST_DEST)\include
	copy adrndeff.h $(DIST_DEST)\include
	copy df1b2fnl.h $(DIST_DEST)\include
	copy df3fun.h $(DIST_DEST)\include
	copy df32fun.h $(DIST_DEST)\include
	copy df1b2loc.h $(DIST_DEST)\include
	copy sed* $(DIST_DEST)\bin

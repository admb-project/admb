include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0) $(OBJSPLUS))

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<

.cpp.obj:
	$(CXX) $(CXXFLAGS) /Fo$@ $<

tpl2cpp:
	$(CC) /nologo /wd4996 /Fe$(DESTDIR)\bin\$@ tpl2cpp-winflex.c

#tpl2cpp-winflex.c: tpl2cpp.lex
#	flex -w tpl2cpp.lex
#	..\..\utilities\sed -f sedflex lex.yy.c > tpl2cpp-winflex.c

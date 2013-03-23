include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0) $(OBJSPLUS))

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<

bins: $(DESTDIR)\bin\tpl2cpp.exe

$(DESTDIR)\bin\tpl2cpp.exe: tpl2cpp-winflex.c
	$(CC) /nologo /TC /Fe$@ tpl2cpp-winflex.c

tpl2cpp-winflex.c: tpl2cpp.lex
	..\..\utilities\flex tpl2cpp.lex
	..\..\utilities\sed -f sedflex lex.yy.c > tpl2cpp-winflex.c

clean:
	del lex.yy.c
	del tpl2cpp-winflex.obj

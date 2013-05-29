include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0) $(OBJSPLUS))

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<

bins: tpl2cpp.exe
	move tpl2cpp.exe $(DESTDIR)\bin\tpl2cpp.exe

tpl2cpp.exe: tpl2cpp.c
	$(CC) /nologo /TC /Fe$@ tpl2cpp.c

tpl2cpp.c: tpl2cpp.lex
	..\..\utilities\flex tpl2cpp.lex
	..\..\utilities\sed -f sedflex lex.yy.c > tpl2cpp.c

clean:
	del lex.yy.c
	del tpl2cpp.obj

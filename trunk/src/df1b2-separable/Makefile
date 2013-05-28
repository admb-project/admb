include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3))

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<

bins: 
	move tpl2rem.exe $(DESTDIR)\bin\tpl2rem.exe

tpl2rem.exe: tpl2rem.c
	$(CC) /nologo /TC /Fe$@ tpl2rem.c

tpl2rem.c: tpl2rem.lex
	..\..\utilities\flex -w tpl2rem.lex 
	..\..\utilities\sed -f sedflex lex.yy.c > $@

clean:

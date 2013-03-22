include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3))

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) /c $(CXXFLAGS) /Fo$@ $<

tpl2rem:
	$(CC) /nologo /W4 /wd4049 /wd4700 /wd4702 /wd4018 /wd4996 /wd4131 /wd4127 /wd4244 /wd4101 /wd4189 /DWIN32 /Fe$(DESTDIR)\bin\$@ tpl2rem-winflex.c

not:
	..\..\utilities\flex -w $<
	..\..\utilities\sed -f sedflex lex.yy.c > tpl2rem-winflex.c

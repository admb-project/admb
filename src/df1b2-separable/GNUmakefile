include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)) $(DISKDIR)/bin/tpl2rem

$(DISKDIR)/bin/tpl2rem: tpl2rem.c
	$(CC) $(CFLAGS) -o $@ $<

tpl2rem.c: tpl2rem.lex
	flex $<
	sed -f sedflex lex.yy.c > $@

$(PREFIX_OBJ)%.obj:%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

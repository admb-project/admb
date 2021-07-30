ifeq ($(OS),Windows_NT)
  ifeq ($(CMDSHELL),cmd)
PATH:=..\..\utilities;$(PATH);..\..\utilities\shared
bins: $(DIST)\bin\tpl2rem.exe
$(DIST)\bin\tpl2rem.exe: ..\..\build\tpl2rem\tpl2rem.c
  else
PATH:=../../utilities:$(PATH);../../utilities/shared
bins: $(DIST)/bin/tpl2rem.exe
$(DIST)/bin/tpl2rem.exe: ../../build/tpl2rem/tpl2rem.c
  endif
else
bins: $(DIST)/bin/tpl2rem
$(DIST)/bin/tpl2rem: ../../build/tpl2rem/tpl2rem.c
endif
	$(CC) $(CFLAGS) -o $@ $<

ifeq ($(CMDSHELL),cmd)
..\..\build\tpl2rem\tpl2rem.c: ..\..\build\tpl2rem\lex.yy.c
	sed -f sedflex ..\..\build\tpl2rem\lex.yy.c > $@
else
../../build/tpl2rem/tpl2rem.c: ../../build/tpl2rem/lex.yy.c
	rm -vf $@
	if [ "`cat $^ | wc -l`" -eq 0 ]; then echo "Error: lex.yy.c is empty."; exit 1; fi
	sed -f sedflex ../../build/tpl2rem/lex.yy.c > $@
endif

ifeq ($(CMDSHELL),cmd)
..\..\build\tpl2rem\lex.yy.c: tpl2rem.lex
	flex -v -w -o..\..\build\tpl2rem\lex.yy.c $^
else
../../build/tpl2rem/lex.yy.c: tpl2rem.lex
	rm -vf $@
	echo "$(PATH)"
	@if [ -z "`command -v flex`" ]; then echo "Error: Unable to find flex."; exit 1; fi
	flex -v -w -o../../build/tpl2rem/lex.yy.c $^
endif

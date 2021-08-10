ifeq ($(OS),Windows_NT)
  ifeq ($(CMDSHELL),cmd)
PATH:=..\..\utilities;$(PATH);..\..\utilities\shared
bins: $(DIST)\bin\tpl2cpp.exe
$(DIST)\bin\tpl2cpp.exe: ..\..\build\tpl2cpp\tpl2cpp.c
  else
PATH:=../../utilities:$(PATH);../../utilities/shared
bins: $(DIST)/bin/tpl2cpp.exe
$(DIST)/bin/tpl2cpp.exe: ../../build/tpl2cpp/tpl2cpp.c
  endif
else
bins: $(DIST)/bin/tpl2cpp
$(DIST)/bin/tpl2cpp: ../../build/tpl2cpp/tpl2cpp.c
endif

ifeq ("$(CC)","cc")
	$(CC) -o $@ $<
else
	$(CC) $(CFLAGS) -Wno-format -o $@ $<
endif

ifeq ($(CMDSHELL),cmd)
..\..\build\tpl2cpp\tpl2cpp.c: ..\..\build\tpl2cpp\lex.yy.c
	sed -f sedflex ..\..\build\tpl2cpp\lex.yy.c > $@
else
../../build/tpl2cpp/tpl2cpp.c: ../../build/tpl2cpp/lex.yy.c
	rm -vf $@
	if [ "`cat $^ | wc -l`" -eq 0 ]; then echo "Error: lex.yy.c is empty."; exit 1; fi
	sed -f sedflex ../../build/tpl2cpp/lex.yy.c > $@
endif

ifeq ($(CMDSHELL),cmd)
..\..\build\tpl2cpp\lex.yy.c: tpl2cpp.lex
	flex -v -w -o..\..\build\tpl2cpp\lex.yy.c  $^
else
../../build/tpl2cpp/lex.yy.c: tpl2cpp.lex
	rm -vf $@
	if [ -z "`command -v flex`" ]; then echo "Error: Unable to find flex."; exit 1; fi
	flex -v -w -o../../build/tpl2cpp/lex.yy.c  $^
endif

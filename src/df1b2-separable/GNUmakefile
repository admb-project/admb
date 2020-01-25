ifeq ($(OS),Windows_NT)
  ifneq ($(findstring bash.exe,$(shell where bash.exe 2>&1 | findstr /C:"bash.exe")),bash.exe)
PATH:=$(PATH):..\..\utilities
bins: $(DIST)\bin\tpl2rem.exe
$(DIST)\bin\tpl2rem.exe: tpl2rem.c
  else
PATH:=$(PATH):../../utilities
bins: $(DIST)/bin/tpl2rem.exe
$(DIST)/bin/tpl2rem.exe: tpl2rem.c
  endif
else
bins: $(DIST)/bin/tpl2rem
$(DIST)/bin/tpl2rem: tpl2rem.c
endif
	$(CC) $(CFLAGS) -o $@ $<

tpl2rem.c: lex.yy.c
ifneq ($(OS),Windows_NT)
	rm -vf $@
	if [ "`cat $^ | wc -l`" -eq 0 ]; then echo "Error: lex.yy.c is empty."; exit 1; fi
endif
	sed -f sedflex $^ > $@

lex.yy.c: tpl2rem.lex
ifneq ($(OS),Windows_NT)
	rm -vf $@
	@if [ -z "`command -v flex`" ]; then echo "Error: Unable to find flex."; exit 1; fi
endif
	flex -v -w $^

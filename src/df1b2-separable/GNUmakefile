ifeq ($(OS)_$(TERM),Windows_NT_)
PATH:=$(PATH):..\..\utilities
endif

ifeq ($(OS),Windows_NT)
bins: $(DIST)\bin\tpl2rem.exe
$(DIST)\bin\tpl2rem.exe: tpl2rem.c
else
bins: $(DIST)/bin/tpl2rem
$(DIST)/bin/tpl2rem: tpl2rem.c
endif
	$(CC) $(CFLAGS) -o $@ $<

tpl2rem.c: lex.yy.c
ifeq ($(OS)_$(TERM),Windows_NT_)
	sed -f sedflex lex.yy.c > $@
else
	rm -vf $@
	if [ "`cat $^ | wc -l`" -ne 0 ]; then sed -f sedflex $^ > $@; fi
	@#if [ ! -f $@ ]; then cp -vf tpl2rem-unixflex.c $@; fi
endif

lex.yy.c: tpl2rem.lex
ifeq ($(OS)_$(TERM),Windows_NT_)
	flex -w tpl2rem.lex
else
	rm -vf $@
	if [ -z "`command -v flex`" ]; then echo "Error: Unable to find flex."; exit 1; fi
	flex -v -w $^
endif

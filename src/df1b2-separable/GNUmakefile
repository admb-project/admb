ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
bins: $(DIST)\bin\tpl2rem.exe

$(DIST)\bin\tpl2rem.exe: tpl2rem.c
	$(CC) $(CFLAGS) -o $@ $<

tpl2rem.c: lex.yy.c
	sed -f sedflex lex.yy.c > $@

lex.yy.c: tpl2rem.lex
	flex -w tpl2rem.lex

else
bins: $(DIST)/bin/tpl2rem

$(DIST)/bin/tpl2rem: tpl2rem.c
	$(CC) $(CFLAGS) -o $@ $<

tpl2rem.c: lex.yy.c
	rm -vf $@
	if [ "`cat $^ | wc -l`" -ne 0 ]; then sed -f sedflex $^ > $@; fi
	@#if [ ! -f $@ ]; then cp -vf tpl2rem-unixflex.c $@; fi

lex.yy.c: tpl2rem.lex
	rm -vf $@
	if [ -z "`command -v flex`" ]; then echo "Error: Unable to find flex."; exit 1; fi
	flex -v -w $^
endif

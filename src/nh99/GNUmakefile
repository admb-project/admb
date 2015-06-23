ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
bins: $(DIST)\bin\tpl2cpp.exe

$(DIST)\bin\tpl2cpp.exe: tpl2cpp.c
	$(CC) $(CFLAGS) -Wno-format -o $@ $<

tpl2cpp.c: lex.yy.c
	sed -f sedflex lex.yy.c > $@

lex.yy.c: tpl2cpp.lex
	flex tpl2cpp.lex
else
bins: $(DIST)/bin/tpl2cpp

$(DIST)/bin/tpl2cpp: tpl2cpp.c
ifeq ("$(CC)","cc")
	$(CC) -o $@ $<
else
	$(CC) $(CFLAGS) -Wno-format -o $@ $<
endif

tpl2cpp.c: lex.yy.c
	rm -vf $@
	if [ "`cat $^ | wc -l`" -ne 0 ]; then sed -f sedflex $^ > $@; fi
	@#if [ ! -f $@ ]; then cp -vf tpl2cpp-unixflex.c $@; fi

lex.yy.c: tpl2cpp.lex
	rm -vf $@
	if [ -z "`command -v flex`" ]; then echo "Error: Unable to find flex."; exit 1; fi
	flex -v -w $^

endif

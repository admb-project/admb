ifneq ($(SHELL),sh.exe)
bins: $(DISKDIR)/bin/tpl2rem

$(DISKDIR)/bin/tpl2rem: tpl2rem.c
	$(CC) $(CFLAGS) -o $@ $<

tpl2rem.c: lex.yy.c
	if [ "`cat $^ | wc -l`" -ne 0 ]; then sed -f sedflex $^ > $@; else rm -vf $@; fi
	if [ ! -f $@ ]; then cp -vf tpl2rem-unixflex.c $@; fi

lex.yy.c: tpl2rem.lex
	if [ `command -v flex` ]; then flex -v -w $^; else rm -vf $@; fi
	if [ ! -f $@ ]; then touch $@; fi
else
bins: $(DISKDIR)\bin\tpl2rem.exe

$(DISKDIR)\bin\tpl2rem.exe: tpl2rem-winflex.c
	$(CC) $(CFLAGS) -o $@ $<
endif

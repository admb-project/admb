ifeq ($(OS),Windows_NT)
PATH:=$(PATH):..\..\utilities
bins: $(DIST)\bin\tpl2cpp.exe
$(DIST)\bin\tpl2cpp.exe: tpl2cpp.c
else
bins: $(DIST)/bin/tpl2cpp
$(DIST)/bin/tpl2cpp: tpl2cpp.c
endif
ifeq ("$(CC)","cc")
	$(CC) -o $@ $<
else
	$(CC) $(CFLAGS) -Wno-format -o $@ $<
endif

tpl2cpp.c: lex.yy.c
ifneq ($(OS),Windows_NT)
	rm -vf $@
	if [ "`cat $^ | wc -l`" -eq 0 ]; then echo "Error: lex.yy.c is empty."; exit 1; fi
	@#if [ ! -f $@ ]; then cp -vf tpl2cpp-unixflex.c $@; fi
endif
	sed -f sedflex lex.yy.c > $@

lex.yy.c: tpl2cpp.lex
ifneq ($(OS),Windows_NT)
	rm -vf $@
	if [ -z "`command -v flex`" ]; then echo "Error: Unable to find flex."; exit 1; fi
endif
	flex -v -w $^

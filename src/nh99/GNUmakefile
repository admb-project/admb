ifeq ($(OS),Windows_NT)
  ifdef TERM
    ifeq ("$(TERM)","xterm")
      TERMINAL=cygwin
    endif
    ifeq ("$(TERM)","cygwin")
      TERMINAL=cygwin
    endif
  else
    TERMINAL=dos
    PATH:=$(PATH);..\..\utilities;..\..\utilities\mingw\bin
  endif
endif

ifeq ($(TERMINAL),dos)
bins: $(DISKDIR)\bin\tpl2cpp.exe

$(DISKDIR)\bin\tpl2cpp.exe: tpl2cpp.c
	$(CC) $(CFLAGS) -Wno-format -o $@ $<

tpl2cpp.c: lex.yy.c
	sed -f sedflex lex.yy.c > $@

lex.yy.c: tpl2cpp.lex
	flex tpl2cpp.lex
else
bins: $(DISKDIR)/bin/tpl2cpp

$(DISKDIR)/bin/tpl2cpp: tpl2cpp.c
ifeq ("$(CC)","cc")
	$(CC) -o $@ $<
else
	$(CC) $(CFLAGS) -Wno-format -o $@ $<
endif

tpl2cpp.c: lex.yy.c
	if [ "`cat $^ | wc -l`" -ne 0 ]; then sed -f sedflex $^ > $@; else rm -vf $@; fi
	if [ ! -f $@ ]; then cp -vf tpl2cpp-unixflex.c $@; fi
lex.yy.c: tpl2cpp.lex
	if [ `command -v flex` ]; then flex -v -w $^; else rm -vf $@; fi
	if [ ! -f $@ ]; then touch $@; fi
endif

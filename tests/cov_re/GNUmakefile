TARGET=cov_re

default: $(TARGET) cov_re_sep
	$(MAKE) run2

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

cov_re: cov_re.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -r $@
else
	../../admb$(EXT) -r $@
endif

cov_re_sep: cov_re_sep.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -r $@
else
	../../admb$(EXT) -r $@
endif

run2:
ifeq ($(CMDSHELL),cmd)
	cov_re
	cov_re_sep
	cov_re_sep -shess
else
	./cov_re
	./cov_re_sep
	./cov_re_sep -shess
endif

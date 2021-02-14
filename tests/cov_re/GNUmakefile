TARGET=cov_re
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET) cov_re_sep
ifeq ($(CMDSHELL),cmd)
	cov_re
	cov_re_sep
	cov_re_sep -shess
else
	./cov_re
	./cov_re_sep
	./cov_re_sep -shess
endif

cov_re_sep: cov_re_sep.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $@
else
	../../admb$(EXT) $@
endif

get-outputs: _get-outputs

clean: _clean

TARGET=cov_re
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	cov_re
else
	./cov_re
endif
	$(MAKE) --file=cov_re_sep.mak run

get-outputs: _get-outputs
	$(MAKE) --file=cov_re_sep.mak get-outputs

clean: _clean
	$(MAKE) --file=cov_re_sep.mak clean

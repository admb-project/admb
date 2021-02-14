TARGET=cov_re
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET) cov_re_sep
	cov_re
	cov_re_sep
	cov_re_sep -shess

cov_re_sep: cov_re_sep.tpl
	..\\..\\admb $@

get-outputs: _get-outputs

clean: _clean

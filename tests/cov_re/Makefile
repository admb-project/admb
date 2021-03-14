TARGET=cov_re
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET) cov_re_sep
	$(TARGET)
	$(MAKE) /fcov_re_sep.nmak run

get-outputs: _get-outputs
	$(MAKE) /fcov_re_sep.nmak get-outputs

clean: _clean
	$(MAKE) /fcov_re_sep.nmak clean

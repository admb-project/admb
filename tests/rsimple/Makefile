TARGET=rsimple
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	@echo Started run:
	$(TARGET) -mcmc 10000 -mcsave 100
	@echo Finished run.

get-outputs: _get-outputs

clean: _clean

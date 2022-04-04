TARGET=simple_mcmc
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET) -mcmc 1000 -mcsave 10
	$(TARGET) -mcmc 1000 -mcsave 10 -mcr
	$(TARGET) -mceval

get-outputs: _get-outputs

clean: _clean

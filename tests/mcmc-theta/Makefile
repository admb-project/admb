TARGET=theta
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET) -nonit -mcmc 1000 -mcsave 10

get-outputs: _get-outputs

clean: _clean

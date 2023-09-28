TARGET=theta
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -nonit -mcmc 1000 -mcsave 10
else
	./$(TARGET) -nonit -mcmc 1000 -mcsave 10
endif

get-outputs: _get-outputs

clean: _clean

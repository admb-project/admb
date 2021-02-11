TARGET=rsimple

!include <..\test-rules.nmake>

run: $(TARGET)
	@printf "Started run:\n"
	./$(TARGET) -mcmc 10000 -mcsave 100
	@printf "Finished run.\n"

get-outputs: _get-outputs

clean: _clean

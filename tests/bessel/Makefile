TARGET=bessel
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET) > outputs

get-outputs: _get-outputs
        @if exist outputs type outputs

clean: _clean
        @if exist outputs del /Q outputs 2>nul

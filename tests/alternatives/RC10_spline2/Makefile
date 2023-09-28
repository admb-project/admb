TARGET=spline2
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET) & type $(TARGET).par $(TARGET).rep > $(TARGET).temp & move $(TARGET).temp $(TARGET).par

get-outputs: _get-outputs

clean: _clean

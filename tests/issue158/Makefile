TARGET=simple
OVERRIDE=all

!include <..\test-rules.nmake>

run: simple.dat
	$(MAKE) $(TARGET)
	@printf "Started run:\n"
	$(TARGET).exe
	@printf "Finished run.\n"

simple.dat:
	copy ..\\..\\examples\\admb\\simple\\simple.dat .

clean: _clean

get-outputs: _get-outputs

clean: _clean
        @if exist simple.dat del /Q simple.dat 2>nul

TARGET=solve
OVERRIDE=all

ifeq ($(OS),Windows_NT)
SCRIPT_DIR=..\\..\\..\\
include ..\\..\\test-rules.mak
else
SCRIPT_DIR=../../../
include ../../test-rules.mak
endif

run: $(TARGET)
	./$(TARGET); cat $(TARGET).par $(TARGET).rep > $(TARGET).temp; mv $(TARGET).temp $(TARGET).par

get-outputs: _get-outputs

clean: _clean

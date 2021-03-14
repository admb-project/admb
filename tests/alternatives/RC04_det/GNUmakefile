TARGET=det
OVERRIDE=all

ifeq ($(OS),Windows_NT)
SCRIPT_DIR=..\\..\\..\\
include ..\\..\\test-rules.mak
else
SCRIPT_DIR=../../../
include ../../test-rules.mak
endif

run: $(TARGET)
	./$(TARGET) -nohess

get-outputs: _get-outputs

clean: _clean

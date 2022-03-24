TARGET=dsort
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\\..\\test-rules.mak
else
include ../../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
endif

get-outputs: _get-outputs

clean: _clean

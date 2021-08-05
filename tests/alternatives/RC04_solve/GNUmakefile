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
ifeq ($(CMDSHELL),cmd)
	$(TARGET); cat $(TARGET).par $(TARGET).rep > $(TARGET).temp; move $(TARGET).temp $(TARGET).par
else
	./$(TARGET); cat $(TARGET).par $(TARGET).rep > $(TARGET).temp; mv $(TARGET).temp $(TARGET).par
endif

get-outputs: _get-outputs

clean: _clean

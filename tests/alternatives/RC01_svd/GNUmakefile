TARGET=svd
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\\..\\test-rules.mak
else
include ../../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) & type $(TARGET).par $(TARGET).rep > $(TARGET).temp & move $(TARGET).temp $(TARGET).par
else
	./$(TARGET); cat $(TARGET).par $(TARGET).rep > $(TARGET).temp; mv $(TARGET).temp $(TARGET).par
endif

get-outputs: _get-outputs

clean: _clean

TARGET=f1b2vc5
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -nohess
else
	./$(TARGET) -nohess
endif

get-outputs: _get-outputs

clean: _clean

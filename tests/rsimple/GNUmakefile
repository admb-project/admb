TARGET=rsimple
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -mcmc 10000 -mcsave 100
else
	./$(TARGET) -mcmc 10000 -mcsave 100
endif

get-outputs: _get-outputs

clean: _clean

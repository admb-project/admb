TARGET=theta
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -nonit -mcmc 1000 -mcsave 10
else
	./$(TARGET) -nonit -mcmc 1000 -mcsave 10
endif

get-outputs: _get-outputs

clean: _clean

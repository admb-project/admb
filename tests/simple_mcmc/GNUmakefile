TARGET=simple_mcmc
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -mcmc 1000 -mcsave 10
	$(TARGET) -mceval
else
	./$(TARGET) -mcmc 1000 -mcsave 10
	./$(TARGET) -mceval
endif

get-outputs: _get-outputs

clean: _clean

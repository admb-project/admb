TARGET=rsimple
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
	@printf "Started run:\n"
	./$(TARGET) -mcmc 10000 -mcsave 100
	@printf "Finished run.\n"

get-outputs: _get-outputs

clean: _clean

TARGET=bessel
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) > outputs
else
	./$(TARGET) &> outputs
endif


get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist outputs type outputs
else
	@if [ -e outputs ]; then cat outputs; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist outputs del /Q outputs 2>nul
else
	@rm -vf outputs
endif

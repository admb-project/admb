TARGET=simple
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: simple.dat
	$(MAKE) $(TARGET)
	@printf "Started run:\n"
ifeq ($(CMDSHELL),cmd)
	$(TARGET).exe
else
	./$(TARGET)
endif
	@printf "Finished run.\n"

simple.dat:
ifeq ($(CMDSHELL),cmd)
	copy ..\\..\\examples\\admb\\simple\\simple.dat .
else
	cp ../../examples/admb/simple/simple.dat .
endif

clean:

get-outputs: _get-outputs

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist simple.dat del /Q simple.dat 2>nul
else
	@rm -vf simple.dat
endif

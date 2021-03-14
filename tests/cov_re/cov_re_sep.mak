TARGET=cov_re_sep
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET)	
	$(TARGET)cov_re_sep -shess
else
	./$(TARGET)
	./$(TARGET) -shess
endif

get-outputs: _get-outputs

clean: _clean

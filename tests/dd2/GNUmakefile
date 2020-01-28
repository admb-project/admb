TARGET=dd2

default: $(TARGET)
	$(MAKE) run2

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run2:
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -imaxfn 0 -noinit
else
	./$(TARGET) -imaxfn 0 -noinit
endif

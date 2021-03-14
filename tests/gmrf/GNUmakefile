TARGET=gmrf
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -est -ilmn 5 -ind gmrf100.dat -shess -ndi 10000000 -gbs 500000000 -noinit
else
	./$(TARGET) -est -ilmn 5 -ind gmrf100.dat -shess -ndi 10000000 -gbs 500000000 -noinit
endif

run2: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET) -est -ilmn 5 -ind gmrf200.dat -shess -ndi 10000000 -gbs 1500000000 -noinit -nl1 1000000
else
	./$(TARGET) -est -ilmn 5 -ind gmrf200.dat -shess -ndi 10000000 -gbs 1500000000 -noinit -nl1 1000000
endif

get-outputs: _get-outputs
ifeq ($(CMDSHELL),cmd)
	@if exist outputs type outputs
else
	@if [ -e outputs ]; then cat outputs; fi
endif

clean: _clean

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
ifeq ($(CMDSHELL),cmd)
	@if exist f1b2list1 del /Q f1b2list1 2>nul
	@if exist f1b2list12 del /Q f1b2list12 2>nul
	@if exist nf1b2list1 del /Q nf1b2list1 2>nul
	@if exist nf1b2list12 del /Q nf1b2list12 2>nul
	@if exist nf1b2list13 del /Q nf1b2list13 2>nul
else
	@rm -vf f1b2list1
	@rm -vf f1b2list12
	@rm -vf f1b2list13
	@rm -vf nf1b2list1
	@rm -vf nf1b2list12
	@rm -vf nf1b2list13
endif

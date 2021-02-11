TARGET=issue108
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET) $(TARGET).dat
ifeq ($(CMDSHELL),cmd)
	issue108
else
	./issue108
endif

$(TARGET).dat: dat
ifeq ($(CMDSHELL),cmd)
	dat > issue108.dat
else
	./dat > issue108.dat
endif

dat: dat.cpp
	$(CXX) -o dat dat.cpp

get-outputs: _get-output
ifeq ($(CMDSHELL),cmd)
	@if exist $(TARGET).dat type $(TARGET).dat
else
	@if [ -e $(TARGET).dat ]; then cat $(TARGET).dat; fi
endif

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist dat del /Q dat 2>nul
	@if exist $(TARGET).dat del /Q $(TARGET).dat 2>nul
else
	@rm -vf dat
	@rm -vf $(TARGET).dat
endif

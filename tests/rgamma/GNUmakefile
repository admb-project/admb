SRCS=gamm1.cpp
OVERRIDE=all

ifeq ($(OS),Windows_NT)
include ..\test-rules.mak
else
include ../test-rules.mak
endif

run: $(TARGET) testgamm
ifeq ($(CMDSHELL),cmd)
	testgamm
	$(TARGET)
else
	./testgamm
	./$(TARGET)
endif

testgamm: testgamm.cpp
ifeq ($(CMDSHELL),cmd)
	$(SCRIPT_DIR)admb.cmd testgamm.cpp
else
	$(SCRIPT_DIR)admb$(EXT) testgamm.cpp
endif

get-outputs: _get-outputs

clean: _clean

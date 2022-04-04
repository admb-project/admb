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
ifeq ($(CMDSHELL),cmd)
	@if exist testgamm.exe del /Q testgamm.exe 2>nul
	@if exist testgamm.obj del /Q testgamm.obj 2>nul
else
	@rm -vf testgamm
	@rm -vf testgamm.obj
endif

TARGET=gamm1
SRCS=gamm1.cpp
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET) testgamm
	testgamm
	$(TARGET)

testgamm: testgamm.cpp
	$(SCRIPT_DIR)admb.cmd testgamm.cpp

get-outputs: _get-outputs

clean: _clean
	@if exist testgamm.exe del /Q testgamm.exe 2>nul
	@if exist testgamm.obj del /Q testgamm.obj 2>nul

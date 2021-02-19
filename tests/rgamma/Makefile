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

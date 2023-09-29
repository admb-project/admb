TARGET=df33_tester
SRCS=df33_tester.cpp
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET)

get-outputs:
	@..\\..\\scripts\\get-outputs.bat $(TARGET)

clean: _clean
	@if exist df33_tester.exe del /Q df33_tester.exe 2>nul
	@if exist df33_tester.obj del /Q df33_tester.obj 2>nul

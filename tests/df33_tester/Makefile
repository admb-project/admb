SRCS=df33_tester.cpp
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
ifeq ($(CMDSHELL),cmd)
	$(TARGET)
else
	./$(TARGET)
endif

get-outputs: _get-outputs

clean: _clean
ifeq ($(CMDSHELL),cmd)
	@if exist df33_tester.exe del /Q df33_tester.exe 2>nul
	@if exist df33_tester.obj del /Q df33_tester.obj 2>nul
else
	@rm -vf df33_tester
	@rm -vf df33_tester.obj
endif

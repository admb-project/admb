TARGET=dd2
OVERRIDE=all

!include <..\test-rules.nmake>

run: $(TARGET)
	$(TARGET) -imaxfn 0 -noinit > outputs

get-outputs: _get-outputs
        @if exist outputs type outputs

clean: _clean
        @if exist outputs del /Q outputs 2>nul
        @if exist f1b2list1 del /Q f1b2list1 2>nul
        @if exist f1b2list12 del /Q f1b2list12 2>nul
        @if exist nf1b2list1 del /Q nf1b2list1 2>nul
        @if exist nf1b2list12 del /Q nf1b2list12 2>nul
        @if exist nf1b2list13 del /Q nf1b2list13 2>nul
